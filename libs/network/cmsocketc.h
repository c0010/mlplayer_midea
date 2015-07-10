// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:socket 客户端接口
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSOCKETC_H_HEADER_INCLUDED_B5C1376A
#define CMSOCKETC_H_HEADER_INCLUDED_B5C1376A

#if defined(PLAT_WINCE)
#include "Winsock2.h"
#ifdef WINCE_OTHER
#include <Ras.h>
#endif
#elif defined(PLAT_SYMBIAN)
#include <ES_SOCK.H>
struct SOCKADDR{};
#define SOCKET               RSocket
#define INVALID_SOCKET       -1
#elif defined(PLAT_AND)
#include <pthread.h>
#define SOCKET               int
#define INVALID_SOCKET       -1
#endif

#include "cmstring.h"
#include "cmtimer.h"
#include "cmmap.h"

class IMNotifySocketC
{
public:
    //Connect函数的回调函数，nCode决定成功失败，MERN_CONNECTED也算成功
    virtual void OnConnect(UINT32 nCode) = 0;

    //Recv函数的回调函数，nCode决定错误类型，nLen决定收到多少数据
    //MERN_PART,表示填充了部分数据，已返回，连接保持。由业务层根据数据内容决定是否下载完成
    virtual void OnRecv(UINT32 nCode, INT32 nLen) = 0;

    //Send函数的回调函数，nCode决定错误类型，nLen决定发送了多少数据，nLen可能不是Send所指定的数量
    //一般成功，这里主要提供一个机会做下述操作
    virtual void OnSend(UINT32 nCode, INT32 nLen) = 0;
};

class CMSocketS;

// Socket客户端版本的实现类，异步方式
class CMSocketC
#if defined(PLAT_SYMBIAN)
    : public CActive,IMNotifyTimer
#elif !defined(PLAT_AND)
    : public IMNotifyTimer
#endif
{
public:
    typedef enum _STATUS {
        NOTCONNECTED,           //未连接
#if defined(PLAT_AND)
        DNSING,                 //dns查询中
#endif
        CONNECTING,             //连接中
        CONNECTED,              //已连接
        SENDING,                //发送中
        RECVING,                //接收中
        CLOSING                 //关闭中
    } STATUS;

    CMSocketC(IMNotifySocketC* pNotify);


    virtual ~CMSocketC();
    
    //建立连接，sHost可以是ip或name形式
    void Connect(const CMString& sHost, UINT16 nPort = 80);

    //指定buf和长度进行接收，可能OnRecv返回MER_OK，长度小于pBuf
    void Recv(INT8* pBuf, INT32 nLen);

    //内部拷贝数据
    void Send(const INT8* pBuf, INT32 nLen);

    //直接取用外部的buf，由外部管理释放，需要在OnSend返回之前保证有效
    void Send(INT8* pBuf, INT32 nLen);

    ////设置keepalive属性
    //void SetKeepLive(BOOL bAlive);

    //获取当前的socket状态
    STATUS GetStatus();

    //中断当前操作
    void Cancel();

    //关闭连接
    void Close();

    //void SetTimeOut(UINT32 nInterval) {m_cTimer.Set(nInterval);};

    //设置通知，返回原有通知句柄
    IMNotifySocketC* SetNotify(IMNotifySocketC* pNotify);

#if defined(PLAT_WINCE)
	void OnNetMessage(UINT message, WPARAM wParam, LPARAM lParam);
#endif

private:
    CMSocketC();

    INT32 Send();
    INT32 Recv();
    INT32 Connect();

    IMNotifySocketC* m_pNotify;    //操作响应回调接口

    SOCKET           m_sk;         //内部socket，平台相关

    STATUS           m_status;     //当前socket状态

    CMString         m_sHost;      //当前host ip
    
    UINT16           m_nPort;      //当前host 端口

//    BOOL             m_bCanceling; //是否正在取消操作


    INT8*            m_pSendBuf;
    INT32            m_nSendLen;

    friend class CMSocketS;
#if defined(PLAT_WINCE)
    void OnTimer(CMTimer &cTimer);
    CMTimer          m_cTimer;     //定时器，用于检测操作超时

    HANDLE           m_hEvents[2];  //事件数组， recv, send
    WSAOVERLAPPED    m_params[2];    //
    HANDLE           m_tAssist;
	WSABUF			 m_RcvBuf;
    INT8*            m_pLocalSendBuf;
#ifdef WINCE_OTHER
	HANDLE           m_hRecv;//专门WINCE接收使用
	HANDLE           m_hRecvEvent;
	BOOL             m_bRecv;
	static DWORD RecvThread(LPVOID pVoid);
#endif
    static DWORD AssistThread(LPVOID pVoid);
    INT32            m_bStopThread;

    INT32            m_nError;     //用来在线程之间传递参数

    //消息循环在那里，
    friend class  CMScreen;
    //static void CALLBACK RecvProc(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
    //static void CALLBACK SendProc(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
#elif defined(PLAT_SYMBIAN)    
    void OnTimer(CMTimer &cTimer);
    CMTimer          m_cTimer;     //定时器，用于检测操作超时
    
    TSockXfrLength   m_cLen;       //系统函数接口参数，当前接受、发送大小
    TPtr8*           m_pRecvBuf;   //接收缓冲，从用户输入构造
    INT32            m_nBufLen;    //接受、发送缓冲大小
    INT32            m_nRecived;   //已接受大小
protected:
    virtual void DoCancel();
    virtual void RunL();
#elif defined(PLAT_AND)
    void             DNS();
    CMString         m_sHostIP;

    BOOL             m_bStopThread;
    static void*     ProcFunc(void* arg);

    pthread_t        m_pt;
    pthread_mutex_t  m_mutex;
    pthread_cond_t   m_cond;
    INT8*            m_pRecvBuf;   //接收缓冲，从用户输入构造
    INT32            m_nBufLen;    //接收缓冲大小
    INT8*            m_pCur;       //接收发送缓冲的当前位置
    INT32            m_nLeft;      //接收发送缓冲的剩余大小
#endif
};

class IMNotifySocketS
{
public:
    //Accept函数的回调函数，nCode决定成功失败，pSocketC返回已连接成功的socket
    //要求在此回调里调用CMSocketC::SetNotify设置正确回调函数，才能接收通知消息
    virtual void OnAccept(UINT32 nCode, CMSocketC* pSocketC) = 0;

    ////请求一个socket，如果返回NULL则自行创建。在OnAccept里返回
    //virtual CMSocketC* OnSocket() = 0;
};

//Socket服务器端侦听类，限定网络拨号已成功，如不成功，直接侦听失败
class CMSocketS
#if defined(PLAT_SYMBIAN)
    : public CActive
#endif
{
public:
    typedef enum _STATUS {
        IDLE,           //空闲
        LISTENING,      //侦听中
    } STATUS;
    
    CMSocketS(IMNotifySocketS* pNotify);
    ~CMSocketS();
    
    void Bind(UINT16 nPort);
    void Listen();
    //停止侦听
    void Stop();

protected:
#ifdef PLAT_SYMBIAN
    virtual void DoCancel();
    virtual void RunL();
    CMSocketC*       m_pSocketC;
#elif defined(PLAT_WINCE)
    HANDLE           m_hEvent;
    HANDLE           m_hEventLoop;
    BOOL             m_bStopThread;
    //CMSocketC*       m_pSocketC;
    static DWORD EventLoop(LPVOID pVoid);
public:
    static void Notify(WPARAM wp, LPARAM lp);
#endif
private:
    IMNotifySocketS* m_pNotify;    //操作响应回调接口

    SOCKET           m_sk;         //内部socket，平台相关

    STATUS           m_status;     //当前socket状态

    UINT16           m_nPort;      //当前host 端口

    BOOL             m_bCanceling; //是否正在取消操作
    
};

#endif
