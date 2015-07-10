// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMDOWNLOADER_H_HEADER_INCLUDED_B5C1376C
#define CMDOWNLOADER_H_HEADER_INCLUDED_B5C1376C

#include "cmhttpc.h"
#include "tinyxml.h"
using namespace tinyxml;
#include "cmcommoninterface.h"
#include "cmnetwork.h"
#include "cmdatetime.h"

//目前下载状态信息都不持久化
class TDownloadInfo
{
  public:
    CMString sUrl;       //url

    CMString sPath;      //本地路径

    UINT32   nSize;      //大小

    UINT32   nDowned;    //已下载

    UINT32   nCurSpd;    //当前下载速度，单位为字节/每秒

    UINT32   nAvgSpd;    //平均下载速度，单位为字节/每秒

    INT32 dStart;   //下载开始时间

    INT32 dCurrent; //当前时间
};

//下载类，可以直接使用
class CMDownloader  : public IMNotifyHttpC
{
public:
    typedef enum _STATUS {
        NONE,           //未开始
        RUNNING,         //下载中
        PAUSED,         //暂停中
        STOPED,         //已停止
        COMPLETED       //已完成
    } STATUS;

    CMDownloader(IMNotifyDownload* pNotify);
    virtual ~CMDownloader();

    //设置新的回调
    IMNotifyDownload* SetNotify(IMNotifyDownload* pNotify);

    //sPathName则使用Url2DownFileName获取相应文件路径
    void Download(const CMString& sUrl, const CMString& sPathName = "");

    //暂停后http不停
    void Pause();

    //停止后http也停止，
	void Cancel();

	//恢复下载，PAUSED STOPED
	void Resume();
    
	//设置下载缓冲大小，默认200k。在download之前设置有效
    void SetBufferSize(UINT32 nSize);

    //设置是否汇报进度，默认不汇报
    //汇报方式，有变化才报。
    void SetProgress(BOOL bFlag = FALSE);

    void GetUrl(CMString& sUrl);
    void GetPathName(CMString& sPathName);
    const TDownloadInfo& GetCurrentInfo();

    //下载状态
    STATUS  GetStatus();

    //自动计算的url到下载文件名
    CMString  Url2DownFileName(const CMString& sUrl);
    
    //正在下载中删除需要设置
    void SetStatusCompleded();

	void SetMaxFileSize(UINT32 nMaxFileSize){m_nMaxFileSize = nMaxFileSize;};
private:
    void Download();

    //interface from IMNotifyHttpC
    virtual void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader);
    virtual void OnRead(UINT32 nCode, INT32 nLen);

    IMNotifyDownload*  m_pNotify;          //通知类指针
    CMHttpC*           m_pHttp;            //Http实现类
    CMFile*            m_pFile;            //文件类
    UINT32             m_nTotal;           //整个传输大小
    UINT32             m_nSize;            //还需传输文件大小
    UINT32             m_nStart;           //开始位置
    UINT32             m_nEnd;             //结束位置
    INT8*              m_pBuf;             //接受缓冲
    UINT32             m_nBufSize;         //缓冲大小
    STATUS             m_nStatus;          //当前状态
//    CMString           m_sUrl;             //下载地址
//    CMString           m_sPathName;        //文件名称
    CMString           m_sTmpFilaName;     //中间文件
    BOOL               m_bProgress;        //是否报进度
    UINT32             m_nRate;            //进度
	UINT32			   m_nMaxFileSize;
    TDownloadInfo      m_cInfo;
    CMString           m_sRoot;   //download根目录
//    friend class CMHttpMgr;
};

//class CMDownManager;
//
////下载管理通知接收接口，用户实现
//class IMNotifyMutiDownload
//{
//public:
//    //0-100,100表示下载完成，完成先调用OnProgress 再OnDownload，不要在OnProgress里做下载完成的处理
//    virtual void OnProgress(INT32 nID, UINT32 nRate) {};
//    //nCode 返回值 0 成功
//    //pDownloader 下载会话的句柄
//    virtual void OnDownload(INT32 nID, UINT32 nCode, CMDownManager* pManager) = 0;
//};

////下载管理类,nID在进程过程中唯一标示一个下载
//class CMDownManager {
//public:
//	static CMDownManager* Instance();
//	~CMDownManager();
//
//	void Release();
//
//	//<0没成功
//	INT32 CreateDownload(const CMString& sUrl, IMNotifyMutiDownload* pNotify);
//
//	BOOL StartDownload(INT32 nID);
//	BOOL StopDownload(INT32 nID);
//	BOOL PauseDownload(INT32 nID);
//	BOOL DeleteDownload(INT32 nID);
//
//	//只是最大值，可能的总数，可能因为删除掉的
//	INT32 GetDownloadCount();
//	BOOL GetDownloadInfo(INT32 nID, CMString& sName, CMDownloader::STATUS& status, UINT32& nRate);
//	CMDownloader* GetDownloader(INT32 nID);
//
//private:
//	CMDownManager();
//
//	void ReadConfig();
//
//	void SaveConfig();
//
//	CMMap<INT32, CMDownloader*>  m_pDownloaders;
//
//	INT32 m_nMax;
//};

#endif /* CMDOWNLOADER_H_HEADER_INCLUDED_B5C1376C */
