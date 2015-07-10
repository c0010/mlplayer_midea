// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMHTTPC_H_HEADER_INCLUDED_B5C1376C
#define CMHTTPC_H_HEADER_INCLUDED_B5C1376C

#if defined(PLAT_WINCE) || defined(PLAT_SYMBIAN)
#include "cmsocketc.h"
#include "cmtimer.h"
#endif
#include "cmmap.h"
#include "cmstring.h"
#include <string>
#include "errordef.h"
#if defined(USE_CURL)
struct fcurl_data;
#include <pthread.h>
#endif

//支持的key值
//使用方法
//CMHttpHeader reqHeader;
//reqHeader.AddValue(HH_GET, CMString("wap.someplace.com/somevideo.mp4"));
//reqHeader.AddValue(HH_RANGER, CMString("110-10000"));
//请求
//const CMString HH_GET          = "GET";
const char HH_HOST[]         = "Host";
const char HH_REFERER[]      = "Referer";
const char HH_RANGER[]       = "Range";
const char HH_ATYPE[]        = "Accept";
const char HH_AECODER[]      = "Accept-Encoding";
const char HH_ACHARSET[]     = "Accept-Charset";
const char HH_AGENT[]        = "User-Agent";
const char HH_WAP[]          = "X-Online-Host";
//回应
//const char HH_RSP[]          = "RESP";
const char HH_LOCATION[]     = "location";
const char HH_CTYPE[]        = "content-type";
const char HH_CECODER[]      = "content-encoding";
const char HH_CLENGTH[]      = "content-length";
const char HH_CRANGE[]       = "content-range";
const char HH_CTENCODER[]    = "transfer-encoding";

//http://pro.163.com:110808/html.ng/ntes123?site=netease&affiliate=sports&cat=homepage&type=column735x100&location=4
//-------|**host***| |port||*****path*****||*********************************param*********************************|
//Url解析类
class CMUrl
{
public:
    CMUrl();

    CMUrl(const CMString& sUrl);

    //parse后，下面的函数才有值
    BOOL Parse();

    //返回地址名称
    CMString& Host();
    const CMString& Host() const;
    
    //返回路径，不带地址信息
    CMString& Path();
    const CMString& Path() const;

    //返回参数
    CMString& Param();
    const CMString& Param() const;

    //返回port，如果类型是HTTP，Port默认为80，如果url里没带，且类型不知道，则为0，
    UINT16& Port();
    const UINT16& Port() const;

    //返回原始url
    CMString& Url();
    const CMString& Url() const;

    //重载等于
    CMUrl& operator=(const CMUrl& cUrl);

    //重载等于，输入字符串类型，需要parse才能正常使用
    //CMUrl& operator=(const CMString& sUrl);

    BOOL operator==(const CMUrl& cUrl) const;

    //目前只支持IPV4
    static BOOL IsIP(const CMString& sAddr);

private:
    
    CMString m_sUrl;          //存放输入sUrl
    CMString m_sHost;         //存放parse后的地址
    CMString m_sPath;         //存放parse后的路径
    CMString m_sParam;        //存放parse后的参数
    UINT16   m_nPort;         //存放parse后的端口
};

//Http头的基础类
//暂时不考虑1key多value接口
class CMHttpHeader
{
public:
    CMHttpHeader();

    virtual ~CMHttpHeader();

    //添加字段，如果字段已有，则修改已有值。大小写敏感
    BOOL AddValue(const CMString &sKey, const CMString &sVal);

    BOOL RmvValue(const CMString &sKey);

    //大小写敏感
    BOOL SetValue(const CMString &sKey, const CMString &sVal);

    //大小写不敏感
    BOOL GetValue(const CMString &sKey, CMString &sVal) const;

    virtual void Clean();
	
	CMMap<CMString, CMString>& GetMapValue(){return m_mValues;}

    //CMString ToString() const;

    //virtual CMHttpHeader& operator=(const CMHttpHeader& cHeader);

protected:
    CMMap<CMString, CMString> m_mValues;
};

using namespace std;
class FormData
{
public:
	FormData();
	FormData(const FormData& right);
	FormData& operator=(const FormData& right);
	BOOL operator==(const FormData& right);

    string key;

    string value;//文件的时候就是filename

    int dataType;  //1、data  2、file

};

//Http请求头实现类
class CMHTTPReqHeader : public CMHttpHeader
{
public:
    typedef enum _TYPE {
        GET,
        POST,
        HEAD      //内测
    }TYPE;

    CMHTTPReqHeader(TYPE type = GET);
	virtual ~CMHTTPReqHeader();

    //首先调用他，添加默认信息
    BOOL CreateDefault();
    
    //成功会自动赋值Host头信息
    BOOL SetUrl(const CMString& sUrl);

    //成功会自动赋值Host头信息
    BOOL SetUrl(const CMUrl& cUrl);

    CMUrl& GetUrl();
    
    CMHTTPReqHeader& operator=(const CMHTTPReqHeader& cHeader);

    //对于post类型的。添加post数据，只能加一次，逐渐废弃掉
    void SetPostData(const CHAR* pData, INT32 nLen);

	CHAR* GetPostData() {return (m_mMtd == POST)? m_pPostData:NULL;};
	int GetPostDataLength() {return m_nPostLen;};
	
	void SetType(TYPE type) {m_mMtd = type;};
	TYPE GetType(){return m_mMtd;};	

    //清理post数据
    void ClearPostData();
    
    //需要调用者释放
    CHAR* ToString(INT32 &nLen);

    //传进数据区和数据区长度，返回是否解析成功，如果成功，nLen变成头的长度
//    BOOL Parse(const INT8* pData, INT32& nLen);

    //form操作，和SetPostData不能同时使用
    BOOL SetFormPostData(CMList<FormData>& lstData);
    
    virtual void Clean();

private:
    friend class CMHttpC;

    CMUrl   m_cUrl;       //url
    TYPE    m_mMtd;       //方法,Get or Post
    CHAR*   m_pPostData;  //post数据
    INT32   m_nPostLen;   //post数据长度

    CMList<FormData>  m_lstPost;  //如果需要有效，必须m_pPostData为空
};

//Http响应头实现类
class CMHTTPRspHeader : public CMHttpHeader
{
public:
    CMHTTPRspHeader();

    //传进数据区和数据区长度，返回是否解析成功，如果成功，nLen变成头的长度
    BOOL Parse(const INT8* pData, INT32& nLen);

    CMString ToString() const;

    //返回http响应头的返回值，如果sDisp有值，返回响应头返回值的描述
    UINT32 GetHttpReturn(CMString* sDisp = NULL) const;

    BOOL IsChunked() const {return m_bChunked;}
    
    void SetRet(UINT32 nRet, const CMString& sRet) 
    {
        m_sRet = sRet;
        m_nRet = nRet;
    };
private:
    friend class CMHttpC;

    CMString m_sRet;       //http的返回描述
    UINT32   m_nRet;       //http的返回值
    BOOL     m_bChunked;   //是否是chunked模式传输
};

//http通知接受接口，用户实现
class IMNotifyHttpC
{
public:
    //成功读取结果头，或者错误. CMHttpC应该在此函数或者此函数以后进行调用,
    //错误时pRespHeader为空
    virtual void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader) = 0;
    //完成，缓冲满，或者错误
    virtual void OnRead(UINT32 nCode, INT32 nLen) = 0;
    //完成，缓冲发送完，或者错误
    virtual void OnSend(UINT32 nCode, INT32 nLen) {}
};

//http客户端实现类
class CMHttpC
#if defined(PLAT_WINCE) || defined(PLAT_SYMBIAN)
: public IMNotifySocketC, IMNotifyTimer
#endif
{
public:
    CMHttpC(IMNotifyHttpC* pNotify, BOOL bAutoReloate = TRUE);

    virtual ~CMHttpC();

    //发起请求，有结果了回调OnRequest，pBuf，nLen含义同read。
    void Request(CMHTTPReqHeader &header);
    
    //设定缓冲，开始读数据。pbuf，缓冲区地址，nLen，pbuf的大小
    void Read(INT8* pBuf, INT32 nLen);

    //获取当前的Response头
    const CMHTTPRspHeader& LastResponse() const;

    //取消当前操作，需要重新Request
    void Cancel();

    //内部请求，可以用在自动重定向
    void Request();

    //是否在运行中
    BOOL IsRunning();
    
	CMHTTPReqHeader& GetReqHeader(){return m_cReqHeader;};

	CMHTTPRspHeader& GetRspHeader(){return m_cRspHeader;};
    
private:
    CMHttpC();

    IMNotifyHttpC*  m_pNotify;       //Http通知
    
	CMHTTPReqHeader m_cReqHeader;    //Http请求头

    CMHTTPRspHeader m_cRspHeader;    //Http响应头
#if defined(PLAT_WINCE) || defined(PLAT_SYMBIAN)
    void OnConnect(UINT32 nCode);

    void OnRecv(UINT32 nCode, INT32 nLen);

    void OnSend(UINT32 nCode, INT32 nLen);

    void OnTimer(CMTimer &cTimer);

    CMSocketC       m_cSK;           //Socket

    INT8*           m_pBuf;          //从Read函数参数传的缓冲，不管理生存期
    
    INT32           m_nLen;          //m_pBuf长度
    
    INT8*           m_pCurr;         //当前的写位置
    
    INT32           m_nLeft;         //记录还需读取的长度
    
    INT8*           m_pHeadBuf;      //存放返回头的缓冲区，需要管理生存期

    INT8*           m_pHeadCur;      //返回头缓冲区的当前指针

    INT32           m_nHeaderLeft;   //返回头缓冲剩余未读数据长度
    
    INT8*           m_pSendBuf;      //存放发送内容的缓冲区,需要管理生存期
    
    UINT32          m_nStatus;       //内部状态

    CMTimer         m_cTimer;        //超时/重试定时器

    BOOL            m_bAutoRl;      //是否自动重定向
    //输入： pBuf 读取的数据地址
    INT8*           ReadChunkSize(INT8* pBuf, INT32 nLen);
    void            ChunkProc(INT32 nLen);
    INT8*           m_pChunkBuf;               //chunk数据缓冲，因为本来就是分段返回，暂不考虑大小
    INT8*           m_nChunkCur;               //chunk数据缓冲当前位置
    INT32           m_nChunkBufSize;           //chunk数据缓冲大小
    BOOL            m_bHasMoreChunks;          //是否还有chunks
    INT32           m_nBytesRemainingInChunk;  //当前chunks还剩余长度 -1,还未取到
//#elif defined(PLAT_IOS)
//	void* m_pMidHandleHttp;

#elif defined(USE_CURL)

	fcurl_data*     m_data;
	pthread_mutex_t m_mutex;           //m_data的操作锁
    pthread_t       m_pt;

    BOOL            m_bAutoRl;      //是否自动重定向

    static void* curl_proc(void* param);

    static int older_progress(void *p,
                              double dltotal, double dlnow,
                              double ultotal, double ulnow);

    static size_t head_callback(char *buffer, size_t size, size_t nitems, void *userp);
    static size_t read_callback(char *buffer, size_t size, size_t nitems, void *userp);
    static size_t write_callback(char *buffer, size_t size, size_t nitems, void *userp);

#endif
};

#endif /* CMHTTPC_H_HEADER_INCLUDED_B5C1376C */
