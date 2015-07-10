// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:socket 客户端接口
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

//当前模块是网络模块
#define FILE_MOD CM_LOGM_NET

#include "stdafx.h"
#include "cmsocketc.h"

#include <Ws2tcpip.h>
#include <connmgr_proxy.h>
#include "cmnetworkmgr.h"
#include "cmnetwork.h"
#include "errordef.h"

extern HWND GetSafeHwnd();

//实现方法
//一个socket一个线程，用来处理异步事件
//此socket的内部行为串行，多socket之间并行
CMSocketC::CMSocketC(IMNotifySocketC* pNotify) : m_pNotify(pNotify),
    m_sk(INVALID_SOCKET), m_status(NOTCONNECTED), m_nPort(0), 
    m_cTimer(this)
{
    m_hEvents[0] = WSACreateEvent(); //recv event
    m_hEvents[1] = WSACreateEvent(); //send event

    memset(&m_params[0], 0, sizeof(WSAOVERLAPPED));
    m_params[0].hEvent = m_hEvents[0];
    memset(&m_params[1], 0, sizeof(WSAOVERLAPPED));
    m_params[1].hEvent = m_hEvents[1];

    m_tAssist = CreateThread(NULL, 0, AssistThread, this, 0, NULL);
    if (!m_tAssist)
    {
        CM_ERR("CreateThread failed");
    }
#ifdef WINCE_OTHER
	m_hRecvEvent = WSACreateEvent();//
	m_hRecv   = CreateThread(NULL, 0, RecvThread, this, CREATE_SUSPENDED, NULL); 
    if (!m_hRecv)
    {
        CM_ERR("CreateThread failed");
    }
	m_bRecv = TRUE;
#endif

    m_nError = 0;
    m_bStopThread = FALSE;
	m_pSendBuf = NULL;
    m_pLocalSendBuf = NULL;
	m_nSendLen = 0;
}

//CMSocketC::CMSocketC(SOCKET sk, STATUS st) : CMSocketC(NULL)
//{
//
//    m_sk = sk;
//    m_status = st;
//}

CMSocketC::~CMSocketC()
{
    m_bStopThread = TRUE;
    Close();

    if (m_pLocalSendBuf)
    {
        SAFEDELETE(m_pLocalSendBuf);
        m_pLocalSendBuf = 0;
    }
    
    WSACloseEvent(m_hEvents[0]);
    WSACloseEvent(m_hEvents[1]);

    CloseHandle(m_tAssist);
#ifdef WINCE_OTHER
	m_bRecv = FALSE;
	if(::WaitForSingleObject(m_hRecvEvent,2000) != WAIT_OBJECT_0)
		::TerminateThread(m_hRecv,1);
	::WSACloseEvent(m_hRecvEvent);
	CloseHandle(m_hRecv);
#endif
}

void CMSocketC::OnTimer(CMTimer &cTimer)
{
    if (m_status == NOTCONNECTED)
    {
        CMNetConnMgr& mgr = CMNetConnMgr::Instance();

        //未连接时OnTimer是因为接入还未成功，
        if (mgr.CurrentType() == CMNetConnMgr::NONE)
        {
            if (mgr.CurrentState() == 1)
            {
                //正在连接中，继续等待
                m_cTimer.Set(3000);   
                m_cTimer.Start();
            }
            else
            {
			    m_pNotify->OnConnect(MERN_INITIALIZE); 
            }
            return;
        }
        else
        {
            //接入成功，开始连接
            Connect();
        }
    }
    else if (m_status == RECVING)
    {
        CM_ERR("Recving timeout");
        Cancel();
        if (m_pNotify)
            m_pNotify->OnRecv(MERN_TIMEOUT, 0);
    }
    else if (m_status == SENDING)
    {
        CM_ERR("Sending timeout");
        Cancel();
        if (m_pNotify)
            m_pNotify->OnSend(MERN_TIMEOUT, 0);
    }
    else if (m_status == CONNECTING)
    {
        CM_ERR("Connecting timeout");
        Cancel();
        if (m_pNotify)
            m_pNotify->OnConnect(MERN_TIMEOUT);
    }
    else
    {
        CM_ERRP("status %d timeout", m_status);
        Cancel();        
		m_pNotify->OnConnect(MERN_TIMEOUT);
    }
}

IMNotifySocketC* CMSocketC::SetNotify(IMNotifySocketC* pNotify)
{
    IMNotifySocketC* pTmp = m_pNotify;
    m_pNotify = pNotify;
    return pTmp;
}

void CMSocketC::Connect(const CMString& sHost, UINT16 nPort)
{
    //网络接入连接检查
    CMNetConnMgr& mgr = CMNetConnMgr::Instance();

    if (m_status != NOTCONNECTED)
    {//当前已有连接
        CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Connect status not NOTCONNECTED, %d", m_status);

        //if (m_sHost == sHost && m_nPort == nPort)
        //{
        //    //新连接于原始连接相同，重用
        //    if (m_status == CONNECTED)
        //    {//取消现有操作
        //        CM_LOG(CM_LOGL_INFO, "CMSocketC::Connect connect reserved");
        //        m_status = CONNECTED;
        //        if (m_pNotify)
        //            m_pNotify->OnConnect(MER_OK);
        //        return;
        //    }

        //    Cancel();
        //}
        //else
        //{
            //因为现在服务器socket超时很短，因此每次都重连
            //关闭连接
            Close();
        //}
    }

    m_sHost = sHost;
    m_nPort = nPort;

    //连接总是用timer，不阻塞主线程
    m_cTimer.Set(100);   
    m_cTimer.Start();
    return;
}

INT32 CMSocketC::Connect()
{
    CMNetConnMgr& mgr = CMNetConnMgr::Instance();

    CMString sTmp;
    if (!CMUrl::IsIP(m_sHost))
    {
        sTmp = mgr.HostNameToIP(m_sHost);
        if (sTmp.IsEmpty())
        {
            CM_ERRP("Host %s can't to addr", (const CHAR*)(CMString)m_sHost);
            if (m_pNotify)
                m_pNotify->OnConnect(MERN_WRONG_PARAM);
            return -1;
        }
    }
    else
    {
        sTmp = m_sHost;
    }

    m_sk = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

    if (m_sk == INVALID_SOCKET)
    {
        CM_ERRP("WSASocket failed, %d", WSAGetLastError());
        if (m_pNotify)
            m_pNotify->OnConnect(MERN_INITIALIZE);
        return -1;
    }

    //bind本地端口
    char hostname[256];
    gethostname(hostname,sizeof(hostname));                      //这一代码是为
    hostent* hos=gethostbyname(hostname);                        //了实现自动获取安
    char* cs=inet_ntoa(*(struct in_addr*)hos->h_addr_list[0]);  // 装程序的主机代码
    sockaddr_in ls;
    ls.sin_family = AF_INET;
    ls.sin_addr = *(struct in_addr*)hos->h_addr_list[0];
    ls.sin_port = 0;
    if (SOCKET_ERROR == bind(m_sk, (sockaddr*)&ls, sizeof(ls)))
    {
        CM_ERRP("bind failed, errorno %d", ::WSAGetLastError());
    }
    else
    {
        CM_LOGP(CM_LOGL_INFO, "bind ip is %s", cs);
    }

    //设置关闭方式,立即关闭，不等待
    linger lg;
    lg.l_onoff = 1;
    lg.l_linger = 0;
    if (SOCKET_ERROR == ::setsockopt(m_sk, SOL_SOCKET, SO_LINGER, (const char*)&lg, sizeof(linger)))
    {
        CM_ERRP("setsockopt  SO_LINGER failed, errorno %d", ::WSAGetLastError());
    }

    //设置保持连接
    BOOL bAlive = TRUE;
    if (SOCKET_ERROR == ::setsockopt(m_sk, SOL_SOCKET, SO_KEEPALIVE, (const char*)&bAlive, sizeof(BOOL)))
    {
        CM_ERRP("setsockopt  SO_KEEPALIVE %d failed, errorno %d", bAlive, ::WSAGetLastError());
    }

    sockaddr_in sockAddrIPv4;
    memset(&sockAddrIPv4, 0, sizeof(sockaddr_in));
    sockAddrIPv4.sin_family = AF_INET;
    INT32 nRet = WSAHtons(m_sk, m_nPort, &(sockAddrIPv4.sin_port));
    sockAddrIPv4.sin_addr.s_addr = inet_addr((const CHAR*)sTmp);

    //nRet = WSAConnect(m_sk, (SOCKADDR*)&sockAddrIPv4, sizeof(sockaddr_in), NULL, NULL, NULL, NULL);
    CM_LOGP(CM_LOGL_INFO, "connect start, to %s:%d", (const CHAR*)sTmp, m_nPort);
    nRet = connect(m_sk, (SOCKADDR*)&sockAddrIPv4, sizeof(sockaddr_in));

    if (nRet == SOCKET_ERROR)
    {
        INT32 nErr = WSAGetLastError();
        UINT32 nRet = MERN_ERROR;
        CM_ERRP("WSAConnect failed, %d", nErr);
        switch (nErr)
        {
        case WSAEWOULDBLOCK:
        {
            INT32 value = 0;
            INT32 valueSize = sizeof(value);
            if (::getsockopt(m_sk, SOL_SOCKET, SO_ERROR, (char *) &value, &valueSize) == 0) {
                if (value == WSAECONNREFUSED) {
                    break;
                }
                if (value == WSAETIMEDOUT) {
                    break;
                }
            }
            break;
        }
        case WSAEFAULT:
            //参数错误
            nRet = MERN_WRONG_PARAM;
            break;
        default:
            break;
        }
        if (m_pNotify)
            m_pNotify->OnConnect(nRet);
        return -1;
    }

    //立即返回
    m_status = CONNECTED;

#ifndef NO_LOG
    {
        sockaddr_in sa;
        int nl = sizeof(sockaddr_in);
        ::getsockname(m_sk, (struct sockaddr*)&sa, &nl);
        CM_LOGP(CM_LOGL_INFO, "connected local ip is %s:%d", inet_ntoa(sa.sin_addr), sa.sin_port);
    }
#endif

    if (m_pNotify)
        m_pNotify->OnConnect(MER_OK);
    return 1;
}

void CMSocketC::Recv(INT8* pBuf, INT32 nLen)
{
    if (m_status == NOTCONNECTED)
    {
        CM_ERR("CMSocketC::Recv status notconnected");
        if (m_pNotify)
            m_pNotify->OnRecv(MERN_NOT_CONNECTED, 0);
        return;
    }
    else if (m_status == SENDING)
    {
        CM_ERR("CMSocketC::Recv status sending");
        if (m_pNotify)
            m_pNotify->OnRecv(MERN_SENDING, 0);
        return;
    }
    else if (m_status == RECVING)
    {
        CM_ERR("CMSocketC::Recv status recving");
        if (m_pNotify)
            m_pNotify->OnRecv(MERN_RECVING, 0);
        return;
    }

    m_status = RECVING;
    //WSABUF tmpBuf;
    m_RcvBuf.len = nLen;
    m_RcvBuf.buf = (CHAR*)pBuf;
    DWORD nRecved = 0;
    //m_param.p = this;
    //INT32 nRet = WSARecv(m_sk, &tmpBuf, 1, &nRecved, 0, (WSAOVERLAPPED*)&m_param, &RecvProc);
    //WSAEVENT tmpEvt = m_param.hEvent;
    //memset(&m_param, 0, sizeof(WSAOVERLAPPED));
    //m_param.hEvent = tmpEvt;
    m_cTimer.Stop();
#ifndef WINCE_OTHER
    INT32 nRet = WSARecv(m_sk, &m_RcvBuf, 1, &nRecved, 0, &m_params[0], NULL);

    if (nRet == SOCKET_ERROR)
    {
        INT32 nErr = WSAGetLastError();
        UINT32 nRet = MERN_ERROR;
        switch (nErr)
        {
        case WSA_IO_PENDING:
        {
            //异步建立成功，直接返回，等待系统回调
            CM_LOGP(CM_LOGL_DEBUG, "WSARecv start. len %d", nLen);
            m_cTimer.Set(60 * 1000);
            m_cTimer.Start();
            //ResumeThread(m_tAssist);
            return;
        }
        case WSAEFAULT:
            //参数错误
            nRet = MERN_WRONG_PARAM;
            break;
        default:
            break;
        }
        //直接回调错误，待处理
        CM_ERRP("WSARecv failed, %d", nErr);
        m_status = CONNECTED;
        if (m_pNotify)
            m_pNotify->OnRecv(nRet, nRecved);
        return;
    }

    //接收成功立即返回，直接调用回调函数
    CM_LOG(CM_LOGL_DEBUG, "WSARecv return Immediately");
    m_status = CONNECTED;
    if (m_pNotify)
        m_pNotify->OnRecv(MER_OK, nRecved);
#else 
	::ResumeThread(m_hRecv);
	WSASetEvent(m_hRecvEvent);
#endif
    return;
}

INT32 CMSocketC::Recv()
{
    //No use now
    ASSERT(FALSE);
    return -1;
}

void CMSocketC::Send(INT8* pBuf, INT32 nLen)
{
    m_pSendBuf = pBuf;
    m_nSendLen = nLen;
	Send();
}

void CMSocketC::Send(const INT8* pBuf, INT32 nLen)
{
    if (m_pLocalSendBuf)
    {
        SAFEDELETE(m_pLocalSendBuf);
        m_pLocalSendBuf = 0;
    }

    m_pLocalSendBuf = new INT8[nLen];
    memcpy(m_pLocalSendBuf, pBuf, nLen);
    m_pSendBuf = m_pLocalSendBuf;
    m_nSendLen = nLen;
	Send();
}

INT32 CMSocketC::Send()
{
    if (m_status == NOTCONNECTED)
    {
        if (m_pNotify)
            m_pNotify->OnSend(MERN_NOT_CONNECTED, 0);
        return -1;
    }
    else if (m_status == SENDING)
    {
        if (m_pNotify)
            m_pNotify->OnSend(MERN_SENDING, 0);
        return -1;
    }
    else if (m_status == RECVING)
    {
        if (m_pNotify)
            m_pNotify->OnSend(MERN_RECVING, 0);
        return -1;
    }

    m_status = SENDING;

    WSABUF tmpBuf;
    tmpBuf.len = m_nSendLen;
    tmpBuf.buf = (CHAR*)m_pSendBuf;
    DWORD nSended = 0;
    //memset(&m_param, 0, sizeof(ASYPARAM));
    //m_param.p = this;

    //In Windows CE, the completion object will not be signalled
    //INT32 nRet = WSASend(m_sk, &tmpBuf, 1, &nSended, 0, 0, 0);//(WSAOVERLAPPED*)&m_param, &CMSocketC::SendProc);
    ResumeThread(m_tAssist);
    m_cTimer.Stop();
    INT32 nRet = WSASend(m_sk, &tmpBuf, 1, &nSended, 0, &m_params[1], NULL);
    if (nRet == SOCKET_ERROR)
    {
        INT32 nErr = WSAGetLastError();
        UINT32 nRet = MERN_ERROR;

        switch (nErr)
        {
        case WSA_IO_PENDING:
        {
            //异步建立成功，直接返回，等待系统回调
            CM_LOGP(CM_LOGL_DEBUG, "WSASend start. len %d", m_nSendLen);
            m_cTimer.Set(60 * 1000);
            m_cTimer.Start();
            return 0;
        }
        case WSAEFAULT:
            //参数错误
            nRet = MERN_WRONG_PARAM;
            break;
        default:
            break;
        }
        CM_ERRP("WSASend failed, %d", nErr);
        m_status = CONNECTED;
        //直接回调错误，待处理
        if (m_pNotify)
            m_pNotify->OnSend(nRet, nSended);
        return -1;
    }

    //发送成功立即返回，直接调用回调函数
    m_status = CONNECTED;
    if (m_pNotify)
        m_pNotify->OnSend(MER_OK, nSended);
    return 1;
}

CMSocketC::STATUS CMSocketC::GetStatus()
{
    return m_status;
}

void CMSocketC::Cancel()
{
    //目前cancel不了，直接close
    Close();

    //m_cTimer.Stop();

    //if (m_status == NOTCONNECTED)
    //{//未连接状态，直接返回
    //    return;
    //}

    //m_status = CONNECTED;
}

void CMSocketC::Close()
{
#ifdef WINCE_OTHER
	::WSAResetEvent(m_hRecvEvent);
#endif
    m_cTimer.Stop();

    if (m_sk != INVALID_SOCKET)
    {
        shutdown(m_sk, SD_BOTH);
        closesocket(m_sk);
        m_sk = INVALID_SOCKET;
    }
    m_status = NOTCONNECTED;
    m_sHost = L"";
    m_nPort = 0;

    m_nError = 0;
}

DWORD CMSocketC::AssistThread(LPVOID pVoid)
{
    CMSocketC* pSocket = (CMSocketC*)pVoid;

    DWORD nIndex = WSA_WAIT_FAILED;
    do {
        nIndex = WSAWaitForMultipleEvents(2, pSocket->m_hEvents, FALSE, WSA_INFINITE, FALSE);

        switch (nIndex)
        {
        case WSA_WAIT_FAILED:
            CM_ERRP("WSAWaitForMultipleEvents failed %d", WSAGetLastError());
            break;
        //case WSA_WAIT_TIMEOUT:
        //    CM_ERRP("WSAWaitForMultipleEvents failed %d", WSAGetLastError());
        //    break;
        default:
            {
                nIndex -= WSA_WAIT_EVENT_0;
                if (nIndex > 1)
                {
                    //多线程操作，可能重入，临时用法
                    CM_ERRP("WSAWaitForMultipleEvents failed %d, nIndex wrong %d", WSAGetLastError(), nIndex);
                    break;
                }
                DWORD cbTransferred = 0;
                DWORD flag;
                BOOL bRet = WSAResetEvent(pSocket->m_params[nIndex].hEvent);
                bRet = WSAGetOverlappedResult(pSocket->m_sk, &pSocket->m_params[nIndex], &cbTransferred, TRUE, &flag);
                if (bRet)
                {
                    //这里用SendMessage来保证时序
                    SendMessage(GetSafeHwnd(), WM_USER+100+nIndex, cbTransferred, (LPARAM)pSocket);
                }
                else
                {
                    pSocket->m_nError = WSAGetLastError();

                    SendMessage(GetSafeHwnd(), WM_USER+100+nIndex, (WPARAM)-1, (LPARAM)pSocket);
                }
            }
        }

    } while (!pSocket->m_bStopThread);

    CM_LOGP(CM_LOGL_INFO, "AssistThread ended with %d", pSocket->m_bStopThread);
    return 0;
}
void OnNetMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_USER+300)
        CMNetConnMgr::Instance().ProcessConnectionManagerMessage();
    else if (message == WM_USER+102)
    {
        CMSocketS::Notify(wParam, lParam);
    }
	else
    {
		CMSocketC* pSocket = (CMSocketC*)lParam;
		if(pSocket)
			pSocket->OnNetMessage(message, wParam, 0);
	}
}
void CMSocketC::OnNetMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    m_cTimer.Stop();
    if (wParam == (WPARAM)-1)
    {
        //对于主动终止，不通知业务层
        if (m_nError == WSAECONNABORTED)
        {
            CM_LOG(CM_LOGL_WARNING, "CMScreen::OnNetMessage WSAECONNABORTED 10053 happen");
            return;
        }

        //对于socket被终止，当前的pending操作可能返回此错误,
        if (m_nError == WSAENOTSOCK)
        {
            CM_LOG(CM_LOGL_WARNING, "CMScreen::OnNetMessage WSAENOTSOCK 10038 happen");
            m_status = CMSocketC::NOTCONNECTED;
            return;
        }

        CM_ERRP("CMScreen::OnNetMessage recv failed, errno is %d", m_nError);
        m_status = CMSocketC::CONNECTED;
        if (message == WM_USER+100)
            m_pNotify->OnRecv(MERN_RECV_FAILED, wParam);
        else
            m_pNotify->OnSend(MERN_RECV_FAILED, wParam);
    }
    //else if (wParam == 0)
    //{
    //    //网络超时，此时socket已不能恢复，关闭掉
    //    pSocket->Close();
    //    pSocket->m_pNotify->OnRecv(MERN_SOCKET_TIMEOUT, 0);
    //}
    else
    {
        //whatever recv 0，
        m_status = CMSocketC::CONNECTED;
        if (message == WM_USER+100)
            m_pNotify->OnRecv(MER_OK, wParam);
        else
            m_pNotify->OnSend(MER_OK, wParam);
    }    
}
#ifdef WINCE_OTHER
DWORD CMSocketC::RecvThread(LPVOID pVoid)
{
	CMSocketC*pSocket = (CMSocketC*)pVoid;
	if(!pSocket)
		return 0;
	while(WAIT_OBJECT_0 == ::WaitForSingleObject(pSocket->m_hRecvEvent,INFINITE))
	{
		if(!pSocket->m_bRecv)
			break;
		::WSAResetEvent(pSocket->m_hRecvEvent);
		INT32 nRet = ::recv(pSocket->m_sk,(CHAR*)pSocket->m_RcvBuf.buf,pSocket->m_RcvBuf.len,0);
		//nRecved = nRet;
		CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::recv len:%d", nRet);
		if (nRet == SOCKET_ERROR)
		{
			//直接回调错误，待处理
			CM_ERRP("WSARecv failed, %d", nRet);
			pSocket->m_status = CONNECTED;
			//if (pSocket->m_pNotify)
			//	pSocket->m_pNotify->OnRecv(nRet, 0);
	        pSocket->m_nError = WSAGetLastError();
            SendMessage(GetSafeHwnd(), WM_USER+100, (WPARAM)-1, (LPARAM)pSocket);
		}
		else
		{
			//接收成功立即返回，直接调用回调函数
			CM_LOG(CM_LOGL_DEBUG, "WSARecv return Immediately");
			pSocket->m_status = CONNECTED;
			//if (pSocket->m_pNotify)
			//	pSocket->m_pNotify->OnRecv(MER_OK, nRet);
             SendMessage(GetSafeHwnd(), WM_USER+100, nRet, (LPARAM)pSocket);
		}
	}
	return 0;
}
#endif
CMSocketS::CMSocketS(IMNotifySocketS* pNotify)
{
    m_pNotify = pNotify;

    m_hEvent = WSACreateEvent(); //listen event

    m_status = IDLE;

    m_sk = INVALID_SOCKET;
}

CMSocketS::~CMSocketS()
{
    Stop();
    WSACloseEvent(m_hEvent);
}

void CMSocketS::Bind(UINT16 nPort)
{
    m_nPort = nPort;
}

void CMSocketS::Listen()
{
    m_bStopThread = FALSE;
    m_sk = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    WSAEventSelect(m_sk, m_hEvent, FD_ACCEPT);

    m_status = LISTENING;
    m_hEventLoop = CreateThread(NULL, 0, EventLoop, this, 0, NULL);
}

void CMSocketS::Stop()
{
    m_bStopThread = TRUE;

    if (m_sk != INVALID_SOCKET)
    {
        shutdown(m_sk, SD_BOTH);
        closesocket(m_sk);
        m_sk = INVALID_SOCKET;
    }
    m_status = IDLE;
    m_nPort = 0;
}

DWORD CMSocketS::EventLoop(LPVOID pVoid)
{
    CMSocketS* pSocket = (CMSocketS*)pVoid;

    //char hostname[256];
    //gethostname(hostname,sizeof(hostname));                      //这一代码是为
    //hostent* hos=gethostbyname(hostname);                        //了实现自动获取安
    //char* cs=inet_ntoa(*(struct in_addr*)hos->h_addr_list[0]);  // 装程序的主机代码
    const char cs[] = "0.0.0.0";

    sockaddr_in saServer;
    saServer.sin_addr.S_un.S_addr = inet_addr(cs);//宏INADDR_ANY定义的是0
    saServer.sin_family = AF_INET;
    saServer.sin_port = htons(pSocket->m_nPort);
    bind(pSocket->m_sk, (SOCKADDR*)&saServer, sizeof(SOCKADDR));

    listen(pSocket->m_sk, 2);

    CM_LOGP(CM_LOGL_INFO, "server listen ip is %s:%d", cs, pSocket->m_nPort);
    int nIndex = WSA_WAIT_FAILED;
    do {
        nIndex = WSAWaitForMultipleEvents(1, &pSocket->m_hEvent, FALSE, WSA_INFINITE, FALSE);
        if (nIndex == WSA_WAIT_FAILED)
        {
            CM_ERRP("WSAWaitForMultipleEvents failed %d", WSAGetLastError());
        }
        else
        {
            WSANETWORKEVENTS NetworkEvent;
            WSAEnumNetworkEvents(pSocket->m_sk, pSocket->m_hEvent, &NetworkEvent);

            if(NetworkEvent.lNetworkEvents & FD_ACCEPT)
            {
                sockaddr_in addr;
                int len=sizeof(sockaddr);
                SOCKET sk = accept(pSocket->m_sk, (sockaddr*)&addr,&len);
                if (sk != INVALID_SOCKET)
                {
#ifndef NO_LOG
                    {
                        CM_LOGP(CM_LOGL_INFO, "accept ip is %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
                        len=sizeof(sockaddr);
                        ::getsockname(sk, (struct sockaddr*)&addr, &len);
                        CM_LOGP(CM_LOGL_INFO, "connected local ip is %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
                        ::getpeername(sk, (struct sockaddr*)&addr, &len);
                        len=sizeof(sockaddr);
                        CM_LOGP(CM_LOGL_INFO, "connected ip is %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
                    }
#endif
                    //CMSocketC* pSocketC = new CMSocketC(NULL);
                    //pSocketC->m_sk = sk;
                    //pSocketC->m_status = CMSocketC::CONNECTED;

                    SendMessage(GetSafeHwnd(), WM_USER+102, (WPARAM)sk, (LPARAM)pSocket);
                    CM_LOG(CM_LOGL_INFO, "accept success");
                }
                else
                {
                    SendMessage(GetSafeHwnd(), WM_USER+102, (WPARAM)NULL, (LPARAM)pSocket);
                    CM_LOG(CM_LOGL_INFO, "accept failed");
                }

            }
            else
            {
                CM_ERRP("CMSocketS wrong lNetworkEvents %d", NetworkEvent.lNetworkEvents);
                WSAResetEvent(pSocket->m_hEvent);
            }
        }
    }
    while (!pSocket->m_bStopThread);
    
    return 0;
}

void CMSocketS::Notify(WPARAM wp, LPARAM lp)
{
    CMSocketS* pSocketS = (CMSocketS*)lp;
    SOCKET sk = (SOCKET)wp;

    CMSocketC* pSocketC = new CMSocketC(NULL);
    pSocketC->m_sk = sk;
    pSocketC->m_status = CMSocketC::CONNECTED;

    if (pSocketC)
        pSocketS->m_pNotify->OnAccept(MER_OK, pSocketC);
    else
        pSocketS->m_pNotify->OnAccept(MERN_ERROR, NULL);        
}

