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

#include <in_sock.h>
#include <arpa/INET.H>
#include <COMMDB.H>
#include <CommDbConnPref.h>
//b #include "cmglobal.h"
//b #include "cmsetting.h"
#include "cmnetworkmgr.h"
#include "errordef.h"


CMSocketC::CMSocketC(IMNotifySocketC* pNotify) : CActive(EPriorityStandard),
    m_pNotify(pNotify), m_status(NOTCONNECTED), m_nPort(0), 
    m_cTimer(this), 
    m_cLen(0), m_pRecvBuf(NULL), m_nBufLen(0), m_nRecived(0), m_pSendBuf(NULL), m_nSendLen(0)
{
    ASSERT(m_pNotify);

    m_cTimer.Set(20000); //超时默认20秒
    CActiveScheduler::Add(this);
    
}

CMSocketC::~CMSocketC()
{
    Close();

    if (m_pRecvBuf)
    {
        delete m_pRecvBuf;
        m_pRecvBuf = NULL;
    }
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
            Connect(m_sHost, m_nPort);
        }
    }
    else if (m_status == RECVING)
    {
        CM_ERR("Recving timeout");
        Cancel();
        m_pNotify->OnRecv(MERN_TIMEOUT, 0);
    }
    else if (m_status == SENDING)
    {
        CM_ERR("Sending timeout");
        Cancel();
        m_pNotify->OnSend(MERN_TIMEOUT, 0);
    }
    else if (m_status == CONNECTING)
    {
        CM_ERR("Connecting timeout");
        Cancel();
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

    if (mgr.CurrentType() == CMNetConnMgr::NONE)
    {
        //未接入，开始接入
        m_cTimer.SetTimerID(1); //使用TimerID来记重复次数
        m_cTimer.Set(3*1000);   //3秒检查
        m_sHost = sHost;
        m_nPort = nPort;
        m_cTimer.Start();
        return;
    }

    if (m_status != NOTCONNECTED)
    {//当前已有连接
//       if (m_sHost == sHost && m_nPort == nPort)
//        {
//            //新连接于原始连接相同，重用
//            if (m_status == CONNECTED)
//            {//取消现有操作
//				CM_ERR("CMSocketC::Connect connect reserved");
//                m_status = CONNECTED;
//                m_pNotify->OnConnect(MER_OK);
//                return;
//            }
//            CM_ERR("CMSocketC::Connect cancel!");
//            Cancel();
			
//       }
       // else
        {
            //关闭连接
            Close();
        }
    }

    CMString sTmp;
    if (!CMUrl::IsIP(sHost))
    {
        CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Connect HostNameToIP %s", (const CHAR*)(CMString)sHost);        
        sTmp = mgr.HostNameToIP(sHost);
        if (sTmp.IsEmpty())
        {
            CM_ERRP("Host %s can't to addr", (const CHAR*)(CMString)sHost);
            m_pNotify->OnConnect(MERN_WRONG_PARAM);
            return;
        }
    }
    else
    {
        sTmp = sHost;
    }
    TInetAddr addr;
    TBuf<20> buf;
    buf = (const UINT16*)((const WCHAR*)(sTmp));
    addr.SetPort(nPort);
    INT32 nErr = addr.Input(buf);
    if (nErr != KErrNone)
    {
        m_pNotify->OnConnect(MERN_WRONG_PARAM);
        return;
    }
    
    CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Connect Open start ip %s, port %d", (const CHAR*)sTmp, nPort);
    nErr = m_sk.Open(mgr.SocketServer(), KAfInet, KSockStream, KProtocolInetTcp
//#if !defined(__WINSCW__)
            , mgr.Connection());
//#else
//            );
//#endif
    
    if (nErr != KErrNone && nErr != KErrAlreadyExists)
    {
        m_pNotify->OnConnect(MERN_INITIALIZE);
        return;            
    }
    
//    iStatus = KErrNone;
    m_sk.Connect(addr, iStatus);
    m_status = CONNECTING;
    m_sHost = sHost;
    m_nPort = nPort;
    m_cTimer.Stop();
    m_cTimer.Set(60 * 1000); //超时默认60秒
    m_cTimer.Start();
    SetActive();
    return;
}


void CMSocketC::Recv(INT8* pBuf, INT32 nLen)
{
    if (m_status == NOTCONNECTED)
    {
        CM_ERR("CMSocketC::Recv status notconnected");
        m_pNotify->OnRecv(MERN_NOT_CONNECTED, 0);
        return;
    }
    else if (m_status == SENDING)
    {
        CM_ERR("CMSocketC::Recv status sending");
        m_pNotify->OnRecv(MERN_SENDING, 0);
        return;
    }
    else if (m_status == RECVING)
    {
        CM_ERR("CMSocketC::Recv status recving");
        m_pNotify->OnRecv(MERN_RECVING, 0);
        return;
    }

    //理论上要求不会出现Active情况
    ASSERT(!IsActive());
    
    if (pBuf == NULL || nLen <= 0)
    {
        m_pNotify->OnRecv(MERN_WRONG_PARAM, 0);
        return;
    }
    
    m_nBufLen = nLen;
    if (m_pRecvBuf)
    {
        delete m_pRecvBuf;
        m_pRecvBuf = NULL;
    }
    //memset(pBuf, 0, nLen);  //无必要，屏蔽掉
    m_pRecvBuf = new TPtr8((UINT8*)pBuf, nLen);
    m_cLen = (TInt)0;
    m_sk.RecvOneOrMore(*m_pRecvBuf, 0, iStatus, m_cLen);
    m_status = RECVING;
    m_cTimer.Stop();
    m_cTimer.Start();
    CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Recv start. len %d", nLen);
    SetActive();

    return;
}

void CMSocketC::Send(INT8* pBuf, INT32 nLen)
{
    m_pSendBuf = pBuf;
    m_nSendLen = nLen;
    Send();    
}

//void CMSocketC::Send(const INT8* pBuf, INT32 nLen)
//{
//    if (m_pSendBuf)
//    {
//        SAFEDELETE(m_pSendBuf);
//        m_nSendLen = 0;
//    }
//
//    m_pSendBuf = new INT8[nLen];
//    memcpy(m_pSendBuf, pBuf, nLen);
//    m_nSendLen = nLen;
//    Send();    
//}

INT32 CMSocketC::Send()
{
    if (m_status == NOTCONNECTED)
    {
        m_pNotify->OnSend(MERN_NOT_CONNECTED, 0);
        return -1;
    }
    else if (m_status == SENDING)
    {
        m_pNotify->OnSend(MERN_SENDING, 0);
        return -1;
    }
    else if (m_status == RECVING)
    {
        m_pNotify->OnSend(MERN_RECVING, 0);
        return -1;
    }

    //理论上要求不会出现Active情况
    ASSERT(!IsActive());
    
    if (m_pSendBuf == NULL || m_nSendLen <= 0)
    {
        m_pNotify->OnSend(MERN_WRONG_PARAM, 0);
        return -1;
    }
    
    m_nBufLen = m_nSendLen;
    m_cLen = 0;
    m_sk.Send(TPtrC8((const UINT8*)m_pSendBuf, m_nSendLen), 0, iStatus, m_cLen);
    m_status = SENDING;
    m_cTimer.Stop();
    m_cTimer.Start();
    CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Send start. len %d", m_nSendLen);
    SetActive();

    return 0;    
}

CMSocketC::STATUS CMSocketC::GetStatus()
{
    return m_status;
}

void CMSocketC::Cancel()
{
    CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Cancel status %d", m_status);

    m_cTimer.Stop();

    if (m_status == NOTCONNECTED)
    {//未连接状态，直接返回
        return;
    }

//    m_status = CONNECTED;
    CActive::Cancel();
}

void CMSocketC::Close()
{
    CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Close status %d", m_status);
    
    m_cTimer.Stop();
    CActive::Cancel();
    
//    if (m_status == RECVING || m_status == SENDING)
//    {
////        m_status = CLOSING;
//        TRequestStatus aStatus;
//        m_sk.Shutdown(RSocket::ENormal, aStatus);
//        User::WaitForRequest(aStatus);
//        
//        if (aStatus != KErrNone)
//        {
//            CM_ERRP("socket shutdown failed err %d", aStatus.Int());
//        }
////        if(!IsActive())
////            SetActive();   
////        return;
//    }
    
    m_sk.Close();
    m_status = NOTCONNECTED;
    m_sHost = L"";
    m_nPort = 0;
}

void CMSocketC::DoCancel()
{
    if (m_status == CONNECTING)
    {
        m_sk.CancelConnect();
        m_status = NOTCONNECTED;
    }
    else if (m_status == RECVING)
    {
        m_sk.CancelRecv();
        m_status = CONNECTED;
    }
    else if (m_status == SENDING)
    {
        m_sk.CancelSend();
        m_status = CONNECTED;
    }
}

void CMSocketC::RunL()
{
    if (m_status == CONNECTING)
    {
        CM_LOGP(CM_LOGL_DEBUG, "CONNECTING return %d", iStatus.Int());
        if (iStatus == KErrNone)
        {
            m_cTimer.Stop();
            m_status = CONNECTED;
            m_pNotify->OnConnect(MER_OK);
        }
        else
        {
            //也许还要加上close等恢复步骤
            CM_ERRP("CMSocketC connect error %d", iStatus.Int());
            Close();
            m_pNotify->OnConnect(MERN_ERROR);
        }
    }
    else if (m_status == RECVING)
    {
        CM_LOGP(CM_LOGL_DEBUG, "RECVING return %d, len %d", iStatus.Int(), m_cLen());
        if (iStatus == KErrNone)
        {
            m_cTimer.Stop();
            
            m_status = CONNECTED;            
            m_pRecvBuf->SetLength(m_cLen());
            m_pNotify->OnRecv(MER_OK, m_cLen());
        }
        else
        {
            //数据已完，但没有填满，或者连接中断
//            if (iStatus == KErrEof)
//            {
//                m_cTimer.Stop();
//                m_pRecvBuf->SetLength(m_cLen());
//                m_status = CONNECTED; //状态设为连接
//                m_pNotify->OnRecv(MERN_PART, m_cLen());
//            }
//            else
//            {
                CM_ERRP("CMSocketC recv error %d", iStatus.Int());
                Close();
                
                m_pNotify->OnRecv(MERN_ERROR, m_cLen());
//            }
        }
        
    }
    else if (m_status == SENDING)
    {
        CM_LOGP(CM_LOGL_DEBUG, "SENDING return %d, len %d", iStatus.Int(), m_cLen());
        if (iStatus == KErrNone)
        {
            m_cTimer.Stop();
            m_status = CONNECTED;
            m_pNotify->OnSend(MER_OK, m_cLen());
        }
        else
        {
            //
            CM_ERRP("CMSocketC send error %d", iStatus.Int());
            Close();
            m_pNotify->OnSend(MERN_ERROR, m_cLen());
        }
    }
//    else if (m_status == CLOSING)
//    {
//        CM_LOGP(CM_LOGL_DEBUG, "CLOSING return %d", iStatus.Int());
//        if (iStatus == KErrNone)
//        {
//            ASSERT(!IsActive());
//            Close();
//        }
//        else
//        {
//            ASSERT(FALSE);
//        }
//    }
    else
    {
        CM_ERRP("invalid socket operation %d", iStatus.Int());
        ASSERT(FALSE);
    }
}

CMSocketS::CMSocketS(IMNotifySocketS* pNotify) : CActive(EPriorityStandard),
m_pNotify(pNotify), m_status(IDLE), m_nPort(0)
{
    ASSERT(m_pNotify);

    CActiveScheduler::Add(this);
}

CMSocketS::~CMSocketS()
{
    Stop();
}

void CMSocketS::Bind(UINT16 nPort)
{
    m_nPort = nPort;
}

void CMSocketS::Listen()
{
    
    if (m_status != IDLE)
    {
        m_pNotify->OnAccept(MERN_INITIALIZE, NULL);
        return;        
    }
    CMNetConnMgr& mgr = CMNetConnMgr::Instance();

    //网络未接入直接返回失败
    if (mgr.CurrentType() == CMNetConnMgr::NONE)
    {
        //
        m_pNotify->OnAccept(MERN_INITIALIZE, NULL);
    }
    
    //构造本地侦听ip，端口
    RHostResolver hostResolver;
    TNameEntry entry;
    TInetAddr aAddress;
    User::LeaveIfError( hostResolver.Open( mgr.SocketServer(), KAfInet, 
                                          KProtocolInetTcp, mgr.Connection() ));
    CleanupClosePushL( hostResolver );
 
    User::LeaveIfError(hostResolver.GetByName(TPtrC(), entry));
    if (!TInetAddr::Cast(entry().iAddr).IsWildAddr())
    {
        aAddress = TInetAddr::Cast(entry().iAddr);
    }
     CleanupStack::PopAndDestroy(); // hostResolver
     aAddress.SetPort(m_nPort);
     
     
     //开始侦听
     User::LeaveIfError( m_sk.Open( 
             mgr.SocketServer(), KAfInet, KSockStream, KProtocolInetTcp ) );
     User::LeaveIfError( m_sk.Bind( aAddress ) );
     
     User::LeaveIfError( m_sk.Listen( 1 ) );

     CMSocketC* pSocketC = new CMSocketC(NULL);
//     pSocketC->m_status = CMSocketC::CONNECTED;    
 //    if (pSocketC == NULL || pSocketC->GetStatus() != CMSocketC::NOTCONNECTED)
 //    {
 //        m_pNotify->OnAccept(MERN_WRONG_PARAM, NULL);
 //        return;
 //    }
     User::LeaveIfError( pSocketC->m_sk.Open( mgr.SocketServer() ) );
     m_sk.Accept( pSocketC->m_sk, iStatus );    
     m_status = LISTENING;
     m_pSocketC = pSocketC;
     SetActive();
     
}

void CMSocketS::Stop()
{
    if (m_status == LISTENING)
    {
        CActive::Cancel();
    }
    
    m_sk.Close();
    m_status = IDLE;
}

void CMSocketS::DoCancel()
{
    m_sk.CancelAccept();
}

void CMSocketS::RunL()
{
    switch( m_status )
    {    
        case LISTENING:
//            m_sk.Close();
            if (iStatus.Int() == KErrNone)
            {
                m_pNotify->OnAccept(MER_OK, m_pSocketC);
            }
            else
            {
                m_pNotify->OnAccept(MERN_ACCEPT, NULL);
                CM_ERRP("CMSocketS::RunL accept return ", iStatus.Int());
            }
            break;
        default:
            m_pNotify->OnAccept(MERN_ACCEPT, NULL);
            CM_ERRP("CMSocketS::RunL wrong status %d", m_status);
    }
}

