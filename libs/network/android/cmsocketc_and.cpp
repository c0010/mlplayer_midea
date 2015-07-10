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
extern "C"
{
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#include <jni.h>
}

#include "errordef.h"
#include "android/env.h"
#include "cmnetworkmgr.h"

void* CMSocketC::ProcFunc(void* arg)
{
	CMSocketC* pSocketC = (CMSocketC*)arg;

    fd_set wset;
    fd_set rset;
    timeval timeout;
    timeout.tv_sec=30;
    timeout.tv_usec=0;
    timeval* pTimeout = &timeout;

    int status;
    JNIEnv* env;
    JavaVM* vm = NULL;
    bool isAttached = false;
    if ((vm = GetJavaVM()) != NULL)
    {
        status = vm->GetEnv((void **) &env, JNI_VERSION_1_4);
        if(status < 0) {
            CM_LOG(CM_LOGL_WARNING, "CMSocketC::ProcFunc:failed to get JNI environment, assuming native thread"); //错误提示行
            status = vm->AttachCurrentThread(&env, NULL);
            if(status < 0) {
            	CM_ERR("failed to attach current thread");
            }
            else
            	isAttached = true;
        }
    }


    pthread_mutex_lock(&pSocketC->m_mutex);
    while(true)
    {
    	CM_LOGP(CM_LOGL_DEBUG, "ProcFunc status %d", pSocketC->m_status);

		if (pSocketC->m_bStopThread)
		{
			pthread_mutex_unlock(&pSocketC->m_mutex);
			break;
		}

		//有可能socket还未创建或者已被关闭，等待
		if (pSocketC->m_status == CLOSING || pSocketC->m_sk < 0)
			pthread_cond_wait(&pSocketC->m_cond, &pSocketC->m_mutex);
    	CM_LOGP(CM_LOGL_DEBUG, "CMSocketC pthread_cond_wait return sk %d status %d", pSocketC->m_sk, pSocketC->m_status);
		if (pSocketC->m_sk < 0)
		{
			//wait后仍然无效
			continue;
		}
	    pthread_mutex_unlock(&pSocketC->m_mutex);

//		if (pSocketC->m_status == CLOSING || pSocketC->m_status == NOTCONNECTED
//				|| pSocketC->m_status == CONNECTED)
//		{
//			//状态不对，
//			CM_ERRP()
//			continue;
//		}


        int iCount = 0;
        while (true)
        {
        	pthread_mutex_lock(&pSocketC->m_mutex);
//            CM_LOGP(CM_LOGL_DEBUG, "select begin sk %d status %d timeout %d", pSocketC->m_sk, pSocketC->m_status, pTimeout->tv_sec);
        	if (pSocketC->m_status == CONNECTING || pSocketC->m_status == SENDING)
        	{
                FD_ZERO(&wset);
                FD_ZERO(&rset);
                FD_SET(pSocketC->m_sk,&wset);
                pTimeout->tv_sec=30;
                pTimeout->tv_usec=0;
                pthread_mutex_unlock(&pSocketC->m_mutex);
        		iCount = select(pSocketC->m_sk+1, 0, &wset, 0, pTimeout);
        	}
        	else if (pSocketC->m_status == RECVING)
        	{
                FD_ZERO(&rset);
                FD_ZERO(&wset);
                FD_SET(pSocketC->m_sk,&rset);
                pTimeout->tv_sec=30;
                pTimeout->tv_usec=0;
                pthread_mutex_unlock(&pSocketC->m_mutex);
                iCount = select(pSocketC->m_sk+1, &rset, 0, 0, pTimeout);
        	}
        	else if (pSocketC->m_status == NOTCONNECTED || pSocketC->m_status == CLOSING)
        	{
        		//连接已关闭
        		break;
        	}
        	else if (pSocketC->m_status == DNSING)
        	{
        	    CMNetConnMgr& mgr = CMNetConnMgr::Instance();

        	    if (!CMUrl::IsIP(pSocketC->m_sHost))
        	    {
        	    	pSocketC->m_sHostIP = mgr.HostNameToIP(pSocketC->m_sHost);
        	        if (pSocketC->m_sHostIP.IsEmpty())
        	        {
        	            CM_ERRP("Host %s can't to addr", (const CHAR*)(CMString)pSocketC->m_sHost);
        	            pthread_mutex_unlock(&pSocketC->m_mutex);
        	            if (pSocketC->m_pNotify)
        	            	pSocketC->m_pNotify->OnConnect(MERN_WRONG_PARAM);
        	            continue;
        	        }
        	    }
        	    else
        	    {
        	    	pSocketC->m_sHostIP = pSocketC->m_sHost;
        	    }

        	    pthread_mutex_unlock(&pSocketC->m_mutex);
        	    pSocketC->Connect();
        	    continue;
        	}
        	else
        	{
        		//CONNECTED,
        		pthread_cond_wait(&pSocketC->m_cond, &pSocketC->m_mutex);
        		pthread_mutex_unlock(&pSocketC->m_mutex);
        		continue;
        	}

//        	CM_LOGP(CM_LOGL_DEBUG, "select returned %d status %d", iCount, pSocketC->m_status);
            if (iCount < 0)
            {
            	CM_LOGP(CM_LOGL_WARNING, "CMSocketC %d select -1 state %d, errno %d",pSocketC->m_sk, pSocketC->m_status, errno);
        		if(pSocketC->m_status == CONNECTING)
        		{
        			pSocketC->m_status = CONNECTED;

        		    if (pSocketC->m_pNotify)
        		    	pSocketC->m_pNotify->OnConnect(MERN_ERROR);
        		}
        		else if (pSocketC->m_status == SENDING)
        		{
        			pSocketC->m_status = CONNECTED;

        		    if (pSocketC->m_pNotify)
        		    	pSocketC->m_pNotify->OnSend(MERN_ERROR, pSocketC->m_nSendLen - pSocketC->m_nLeft);
        		}
        		else if (pSocketC->m_status == RECVING)
        		{
        			pSocketC->m_status = CONNECTED;

        		    if (pSocketC->m_pNotify)
        		    	pSocketC->m_pNotify->OnRecv(MERN_ERROR, pSocketC->m_nBufLen - pSocketC->m_nLeft);
        		}
        		else
        		{
        			CM_ERRP("CMSocketC select wrong state %d", errno);
        		}
            }
            else if (iCount == 0)
            {
            	//timeout
            	CM_LOGP(CM_LOGL_WARNING, "CMSocketC %d select timeout state %d, errno %d",pSocketC->m_sk ,pSocketC->m_status, errno);
        		if(pSocketC->m_status == CONNECTING)
        		{
        			pSocketC->m_status = CONNECTED;

        		    if (pSocketC->m_pNotify)
        		    	pSocketC->m_pNotify->OnConnect(MERN_TIMEOUT);
        		}
        		else if (pSocketC->m_status == SENDING)
        		{
        			pSocketC->m_status = CONNECTED;

        		    if (pSocketC->m_pNotify)
        		    	pSocketC->m_pNotify->OnSend(MERN_TIMEOUT, pSocketC->m_nSendLen - pSocketC->m_nLeft);
        		}
        		else if (pSocketC->m_status == RECVING)
        		{
        			pSocketC->m_status = CONNECTED;

        		    if (pSocketC->m_pNotify)
        		    	pSocketC->m_pNotify->OnRecv(MERN_TIMEOUT, pSocketC->m_nBufLen - pSocketC->m_nLeft);
        		}
        		else
        		{
        			CM_ERRP("timeout wrong state %d", pSocketC->m_status);
        		}
            }
            else
            {
            	if (FD_ISSET(pSocketC->m_sk, &rset))
            	{
            		if (pSocketC->m_status == RECVING)
            		{
    					pSocketC->Recv();
            		}
            		else
            		{
            			CM_ERRP("rset wrong state %d", pSocketC->m_status);
            		}
            	}

            	if (FD_ISSET(pSocketC->m_sk, &wset))
            	{
            		if(pSocketC->m_status == CONNECTING)
            		{
            			pSocketC->m_status = CONNECTED;

            		    if (pSocketC->m_pNotify)
            		    	pSocketC->m_pNotify->OnConnect(MER_OK);
            		}
            		else if (pSocketC->m_status == SENDING)
            		{
    					pSocketC->Send();
            		}
            		else
            		{
            			CM_LOGP(CM_LOGL_WARNING, "wset wrong state %d", pSocketC->m_status);
            		}
            	}
            }
        }
    }

    if(isAttached)
    	vm->DetachCurrentThread();
//	while (true) {
//
//		pthread_cond_wait(&m_cond, &m_mutex);
//		if (pSocketC->m_bStopThread)
//		{
//			//clrear and break
//			// now problem.....................................
//			break;
//		}
//		switch(pSocketC->m_status)
//		{
//		case NOTCONNECTED:
//			//close
//			break;
//		case CONNECTING:
//			pSocketC->Connect();
//			break;
//		case SENDING:
//			pSocketC->Send();
//			break;
//		case RECVING:
//			pSocketC->Recv();
//			break;
//		case STOPING:
//			pSocketC->Recv();
//			break;
//		default:
//			break;
//		}
//		if (pSocketC->m_bStopThread)
//		{
//			//
//			//clear and break
//
//			break;
//		}
//	}

//    pthread_mutex_destroy(&pSocketC->m_mutex);
//    pthread_cond_destroy(&pSocketC->m_cond);
    CM_LOG(CM_LOGL_INFO, "CMSocketC thread exit");

	pthread_exit(NULL);
	return NULL;
}

//实现方法
//一个socket一个线程，用来处理异步事件
//此socket的内部行为串行，多socket之间并行
CMSocketC::CMSocketC(IMNotifySocketC* pNotify) : m_pNotify(pNotify),
    m_sk(INVALID_SOCKET), m_status(NOTCONNECTED), m_nPort(80)
{
    m_bStopThread = FALSE;
	m_pSendBuf = NULL;
	m_nSendLen = 0;

	pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init (&m_cond, NULL);

    int iRet = pthread_create(&m_pt, NULL, ProcFunc, (void*)this);

    if (iRet)
    {
        CM_ERR("CreateThread failed");
    }
}

CMSocketC::~CMSocketC()
{
//	CM_ERR("CMSocketC::~CMSocketC");
    m_bStopThread = TRUE;
    Close();

    //使线程继续
    pthread_cond_signal(&m_cond);

    //
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);

//    CM_ERR("CMSocketC::~CMSocketC 2");
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
//    CMNetConnMgr& mgr = CMNetConnMgr::Instance();
//    if (m_status != NOTCONNECTED)
//    {//当前已有连接
//    	CM_ERR("connect 11");
//        CM_LOGP(CM_LOGL_DEBUG, "CMSocketC::Connect status not NOTCONNECTED, %d", m_status);
//
//        //if (m_sHost == sHost && m_nPort == nPort)
//        //{
//        //    //新连接于原始连接相同，重用
//        //    if (m_status == CONNECTED)
//        //    {//取消现有操作
//        //        CM_LOG(CM_LOGL_INFO, "CMSocketC::Connect connect reserved");
//        //        m_status = CONNECTED;
//        //        if (m_pNotify)
//        //            m_pNotify->OnConnect(MER_OK);
//        //        return;
//        //    }
//
//        //    Cancel();
//        //}
//        //else
//        //{
//            //因为现在服务器socket超时很短，因此每次都重连
//            //关闭连接
//    	CM_ERR("connect 12");
//
//            Close();
//        //}
//    }

    m_sHost = sHost;
    m_nPort = nPort;

    ASSERT(m_status == NOTCONNECTED);

    DNS();

    return;
}

void CMSocketC::DNS()
{
	pthread_mutex_lock(&m_mutex);

    m_status = DNSING;

    m_sk = socket(AF_INET, SOCK_STREAM, 0);

    if (m_sk < 0)
    {
    	pthread_mutex_unlock(&m_mutex);
        if (m_pNotify)
            m_pNotify->OnConnect(MERN_INITIALIZE);
        return;
    }

    pthread_cond_signal(&m_cond);
    pthread_mutex_unlock(&m_mutex);
}

INT32 CMSocketC::Connect()
{
	pthread_mutex_lock(&m_mutex);

    m_status = CONNECTING;

//    //设置发送、接收超时30秒
//    INT32  nTimeOut = 30;
//    nRet = setsockopt(m_sk, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nTimeOut, sizeof(INT32));
//    if (nRet == SOCKET_ERROR)
//    {
//    	CM_ERRP("setsockopt SO_RCVTIMEO failed, errno %d", errno);
//    }
//    nRet = setsockopt(m_sk, SOL_SOCKET, SO_SNDTIMEO, (const char*)&nTimeOut, sizeof(INT32));
//    if (nRet == SOCKET_ERROR)
//    {
//    	CM_ERRP("setsockopt SO_SNDTIMEO failed, errno %d", errno);
//    }
    //使用异步io方式connect
    INT32 flags = fcntl(m_sk,F_GETFL,0);
    if (-1 == flags)
    {
    	CM_ERRP("fcntl get flags failed %d", errno);
    }
    INT32 nRet = fcntl(m_sk,F_SETFL, flags | O_NONBLOCK);
    if (-1 == nRet)
    {
    	CM_ERRP("fcntl set nonblock failed %d", errno);
    }

    //设置关闭方式
    linger lg;
    lg.l_onoff = 1;
    lg.l_linger = 0;
    nRet = setsockopt(m_sk, SOL_SOCKET, SO_LINGER, (const char*)&lg, sizeof(linger));
    if (nRet == -1)
    {
    	CM_ERRP("setsockopt SO_LINGER failed, errno %d", errno);
    }

    //设置保持连接
    INT32 bAlive = 1;
    nRet = setsockopt(m_sk, SOL_SOCKET, SO_KEEPALIVE, (const char*)&bAlive, sizeof(INT32));
    if (nRet == -1)
    {
    	CM_ERRP("setsockopt SO_KEEPALIVE failed, errno %d", errno);
    }

//    /*************************************************************/
//    /* Allow socket descriptor to be reuseable                   */
//    /*************************************************************/
//    nRet = setsockopt(m_sk, SOL_SOCKET,  SO_REUSEADDR,
//                    (char *)&on, sizeof(on));
//    if (nRet < 0)
//    {
//       perror("setsockopt() failed");
//       close(listen_sd);
//       exit(-1);
//    }


    sockaddr_in sockAddrIPv4;
    memset(&sockAddrIPv4, 0, sizeof(sockaddr_in));
    sockAddrIPv4.sin_family = AF_INET;
    sockAddrIPv4.sin_port = htons(m_nPort);
    sockAddrIPv4.sin_addr.s_addr = inet_addr((const char*)m_sHostIP);

    CM_LOGP(CM_LOGL_INFO, "connect start addr %s port %d", (const char*)m_sHostIP, m_nPort);

    if (0 == connect(m_sk, (sockaddr*)&sockAddrIPv4, sizeof(sockaddr_in)))
    {
    	CM_LOG(CM_LOGL_INFO, "connect succees");
    	pthread_mutex_unlock(&m_mutex);
    	m_status = CONNECTED;
        if (m_pNotify)
            m_pNotify->OnConnect(MER_OK);
        return 1;
    }

    if (errno != EINPROGRESS)
    {
        CM_ERRP("connect failed, %d", errno);
        close(m_sk);
        pthread_mutex_unlock(&m_mutex);
        if (m_pNotify)
            m_pNotify->OnConnect(MERN_INITIALIZE);
        return -1;
    }

    CM_LOG(CM_LOGL_DEBUG, "connect in progress");
//    //使用信号方式设置超时
//    struct sigaction sact;
//    sigemptyset(&sact.sa_mask);
//    sact.sa_flags = 0;
//    sact.sa_handler = NULL;
//    sigaction(SIGALRM, &sact, NULL);
//    alarm(60);
//
//    CM_LOGP(CM_LOGL_INFO, "connect start, to %s:%d", (const CHAR*)sTmp, m_nPort);
//    nRet = connect(m_sk, (SOCKADDR*)&sockAddrIPv4, sizeof(sockaddr_in));
//
//    if (rc < 0)
//    {
//    	rc = errno;
//        CM_ERRP("connet failed, %d", rc);
//        close(m_sk);
//        if (m_pNotify)
//        {
//        	if (errno == EINTR)
//        	{
//        		m_pNotify->OnConnect(MERN_TIMEOUT);
//        	}
//        	else
//        	{
//        		m_pNotify->OnConnect(MERN_INITIALIZE);
//        	}
//        }
//
//        return;
//    }

//    pthread_cond_signal(&m_cond);
    pthread_mutex_unlock(&m_mutex);
    return 0;
}

void CMSocketC::Recv(INT8* pBuf, INT32 nLen)
{
    if (m_status != CONNECTED)
    {
        CM_ERRP("CMSocketC::Recv status wrong, is %d", m_status);
        if (m_pNotify)
            m_pNotify->OnRecv(MERN_RECVING, 0);
        return;
    }

	m_pRecvBuf = pBuf;
	m_nBufLen = nLen;
    m_pCur = m_pRecvBuf;
    m_nLeft = m_nBufLen;

    Recv();
}

INT32 CMSocketC::Recv()
{
	pthread_mutex_lock(&m_mutex);

	m_status = RECVING;

    INT32 nRecved = 0;
    nRecved = recv(m_sk, m_pCur, m_nLeft, 0);

    if (nRecved >= 0)
    {
//    	CM_LOGP(CM_LOGL_DEBUG, "Recv %d bytes", nRecved);
    	m_pCur += nRecved;
    	m_nLeft -= nRecved;
    }
    else
    {
    	if (errno == EWOULDBLOCK)
    	{
    		//异步发送
//    		CM_LOG(CM_LOGL_DEBUG, "Recv nonblock");
    		pthread_cond_signal(&m_cond);
    		pthread_mutex_unlock(&m_mutex);
    		return 0;
    	}
    	else
    	{
        	CM_ERRP("Recv failed %d", errno);
    		m_status = CONNECTED;

        	pthread_mutex_unlock(&m_mutex);
            if (m_pNotify)
                m_pNotify->OnRecv(MERN_ERROR, m_nBufLen - m_nLeft);
        	return -1;
    	}
    }

//    CM_LOG(CM_LOGL_DEBUG, "Recv succees");
    m_status = CONNECTED;

    pthread_mutex_unlock(&m_mutex);
    if (m_pNotify)
        m_pNotify->OnRecv(MER_OK, m_nBufLen - m_nLeft);
    return 1;
}

void CMSocketC::Send(INT8* pBuf, INT32 nLen)
{
    if (m_status != CONNECTED)
    {
        CM_ERRP("CMSocketC::Send status wrong, is %d", m_status);
        if (m_pNotify)
            m_pNotify->OnRecv(MERN_SENDING, 0);
        return;
    }

    m_pSendBuf = pBuf;
    m_nSendLen = nLen;
    m_pCur = m_pSendBuf;
    m_nLeft = m_nSendLen;

    Send();
}

//void CMSocketC::Send(const INT8* pBuf, INT32 nLen)
//{
//    if (m_status != CONNECTED)
//    {
//        CM_ERRP("CMSocketC::Send status wrong, is %d", m_status);
//        if (m_pNotify)
//            m_pNotify->OnRecv(MERN_SENDING, 0);
//        return;
//    }
//
//    if (m_pSendBuf)
//    {
//        SAFEDELETE(m_pSendBuf);
//        m_nSendLen = 0;
//    }
//    m_pSendBuf = new INT8[nLen];
//    memcpy(m_pSendBuf, pBuf, nLen);
//    m_nSendLen = nLen;
//    m_pCur = m_pSendBuf;
//    m_nLeft = m_nSendLen;
//
//    Send();
//}

INT32 CMSocketC::Send()
{
	pthread_mutex_lock(&m_mutex);

	m_status = SENDING;

    INT32 nSended = 0;
    nSended = send(m_sk, m_pCur, m_nLeft, 0);

    if (nSended >= 0)
    {
//    	CM_LOGP(CM_LOGL_DEBUG, "Send %d bytes", nSended);

    	m_pCur += nSended;
    	m_nLeft -= nSended;
    }
    else
    {
    	if (errno == EWOULDBLOCK)
    	{
    		//异步发送
//    		CM_LOG(CM_LOGL_DEBUG, "Send nonblock");
    		pthread_cond_signal(&m_cond);
    		pthread_mutex_unlock(&m_mutex);
    		return 0;
    	}
    	else
    	{
        	CM_ERRP("Send failed %d", errno);
    		m_status = CONNECTED;

        	pthread_mutex_unlock(&m_mutex);
            if (m_pNotify)
                m_pNotify->OnSend(MERN_ERROR, m_nSendLen - m_nLeft);
        	return -1;
    	}
    }

//    CM_LOG(CM_LOGL_DEBUG, "Send succees");
    m_status = CONNECTED;

    pthread_mutex_unlock(&m_mutex);
    if (m_pNotify)
        m_pNotify->OnSend(MER_OK, m_nSendLen - m_nLeft);
    return 1;
}

CMSocketC::STATUS CMSocketC::GetStatus()
{
    return m_status;
}

void CMSocketC::Cancel()
{
    //直接close
    Close();
}

void CMSocketC::Close()
{
	pthread_mutex_lock(&m_mutex);
    m_status = CLOSING;

    if (m_sk != INVALID_SOCKET)
    {
//    	CM_ERRP("CMSocketC::Close %d", m_sk);
        shutdown(m_sk, SHUT_RDWR);
        close(m_sk);
        m_sk = INVALID_SOCKET;
    }
    m_status = NOTCONNECTED;

    m_sHost = L"";
    m_nPort = 0;
    pthread_mutex_unlock(&m_mutex);
}



