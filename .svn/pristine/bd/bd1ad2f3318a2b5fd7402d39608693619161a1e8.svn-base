// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCOURSEDOWNLOAD_H_HEADER_INCLUDED_B18384D3
#define CMCOURSEDOWNLOAD_H_HEADER_INCLUDED_B18384D3


#include "stdafx.h"
#include "cmcourseinfo.h"

#include "utf8ncpy.h"
#include "cmcommon.h"

#include <sys/stat.h>
#include <errno.h>
#include <string>
#include <pthread.h>
#include <unzip.h>


#if defined(PLAT_IOS)

#import "cmcoursedownload_iph.h"

#endif


using namespace std;

typedef struct _unzipInfo {
    string src;//zip文件位置
    string dst;//解压后文件夹
}CMUnzipInfo;

template <typename T> class CMList;

// 课程下载管理，同时只下载一个课程的一个课件，按设置好的下载顺序依次自动下载
class CMCourseDownload : public IMNotifyDownload , public CMHandler<CMCourseInfo>
{
  public:
    
    //解压完后,继续下载
    void GoOnDownload();
    
    static CMCourseDownload* GetInstance();

    virtual ~CMCourseDownload();

    void Release();
    
    void SetListener(IMUpdateDataListener* pListener);

    // 返回下载项的index, -1表示添加失败，CMCourseInfo应该是完善的，包含TCoursewareItem
    int Append(const CMCourseInfo& course);

    void Delete(int nCourseIndex);

    // 返回TRUE表示成功开始下载（或正在下载状态）；FALSE表示有正在下载的其他课程，不能开始该课程的下载
    BOOL Start(int nCourseIndex);

    void Stop();

    void CheckCourseware(int nCourseIndex, int nCoursewareIndex);

    void UnCheckCourseware(int nCourseIndex, int nCoursewareIndex);

    int Status(int nCourseIndex);

    //获取当前处理的course Index，状态由Status决定，可能为停止，或者正在下载
    int GetCurrent();

	BOOL isComplete(int nCourseIndex, int nCoursewareIndex);

    // UI层需定时获取状态文本刷新界面。正在下载：108KB/580KB
    // 5.6KB/s；停止下载未完成：108KB/580KB；停止下载已完成：580KB
    const char* GetStatusText(int nCourseIndex);

	const char* GetStatusText(int nCourseIndex, int nCoursewareIndex);

	const static int EStatusError = -1;

    const static int EStatusDownloading = 1;

    const static int EStatusPauseDownload = 2;

    const static int EStatusComplete = 3;

    const static int EStatusInDownloadList = 4;
    
    BOOL IsDonwloaded(const TCoursewareItem& item);
    
    void SetUserData(void* userdata);
    
    void LoadFromFile(); //读取保存下载信息

  protected:
    
    string GetLocalFilePath(const char* CoursewareID);//得到课件的下载文件的本地路径

    static bool ISRUNNING;//标志对象是否析构
    
    pthread_t    m_pt;//新建线程处理解压缩

    
    //解压缩后，获取scorm.xml中的入口html地址,参数dirPath为scorm.xml上层目录
    BOOL GetEntryFilePathFromZip(int classIndex, int coursewareIndex,const char * dirPath);
    
    //解压缩图文课件
    void UnzipCourseware(int classIndex,int coursewareIndex);
    
    //解压缩zip包内的一个文件,只用于内部调用
    static int DoExtractFile(unzFile uf, int opt_extract_without_path, int* popt_overwrite, const char *password,const char* dstPath);
    
    //解压缩刚下载完的zip包,param为CMUnzipInfo类型
    static void* DoExtractPackage(void* param1);
   
#if defined(PLAT_IOS)

    CMCourseDownload_Iph* m_pDownloadIos;
    
#endif
    
    //解压缩信息
    CMUnzipInfo m_pUnipInfo;
    
    //缓存建表
    virtual BOOL DoCreate(sqlite3* db) ;
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, CMCourseInfo& item) ;
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(CMCourseInfo& obj) ;
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(const CMCourseInfo& obj);

    BOOL DoUpdate(const TCoursewareItem& obj);
    /**
     *	保存课件
     *
     *	@param	db	数据库指针
     *	@param	item	要保存的课件item
     *
     *	@return
     */
    BOOL DoGetCourseware(sqlite3* db, TCoursewareItem& item);
    
    BOOL DoGetCacheCourseware(sqlite3* db, CMCourseInfo& item);
    
    BOOL DoUpdateCourseware(sqlite3* db, CMCourseInfo& item);
    
    BOOL DoDelete(const TClassItem& obj);
    
    BOOL DoDeleteCourseware(const TCoursewareItem& obj);

    CMCourseDownload();

    void OnProgress(unsigned int nRate);
    
    virtual void OnDownload(unsigned int nCode, CMDownloader* pDownloader);

    void SaveToFile();   //保存下载信息

  private:
    
    bool isDoingUnzip;//标志是否在解压缩
    
    static CMCourseDownload *m_pTHIS;


	CMDownloader* m_pDownloader;

	//当前正在下载课程，-1没有下载
	int m_nCourseIndex;

	//当前正在下载课件，-1没有下载
	int m_nCoursewareIndex;
    
    IMUpdateDataListener *m_pUpdateListener;
    
    void* m_UserData;
	
	char m_sStatusText[128];
    
    char m_SubTablename[64];//下载的课件表
    
    friend class CMDBHelper;
    
    friend class CMPlayerUtility;


};

#endif /* CMCOURSEDOWNLOAD_H_HEADER_INCLUDED_B18384D3 */
