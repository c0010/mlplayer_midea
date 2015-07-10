// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMWEBIMAGE_H_HEADER_INCLUDED_B1988E9F
#define CMWEBIMAGE_H_HEADER_INCLUDED_B1988E9F
#include "stdafx.h"
#include "cmcommon.h"
#include "cmstring.h"

class CMDownloader;
template <typename T> class CMList;
class CMWebImage:public IMNotifyDownload
{
  public:
    CMWebImage(IMGetImageListener* pListener);

    virtual ~CMWebImage();

    void SetUserData(void* UserData);

    // 同时只能处理一个URL，第二个以后的压在列表里逐一处理
    BOOL GetFromUrl(int nID, const char* sUrl);

    void Cancel();

    const char* GetFilePath(const char* sUrl);

  private:
  	void DownloadNext();
  	
  	void FormatFilePath(const char* sUrl);
	//nCode 返回值 0 成功
    //pDownloader 下载会话的句柄
    virtual void OnDownload(unsigned int nCode, CMDownloader* pDownloader);

	  struct PicUrl
	  {
		  int id;
		  char url[300];
	  };
    IMGetImageListener* m_pListener;

    void* m_UserData;
 
	CMDownloader* m_pDownloader;

	CMList<PicUrl*>* m_lstPicUrl;

	CMString    m_sFilePath;
};



#endif /* CMWEBIMAGE_H_HEADER_INCLUDED_B1988E9F */
