// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMUPDATE_H_HEADER_INCLUDED_B19A7B84
#define CMUPDATE_H_HEADER_INCLUDED_B19A7B84

#include "cmcommon.h"

class CMUpdate:public IMNotifyDownload
{
  public:
    CMUpdate(IMUpdateDataListener* pListener);

    virtual ~CMUpdate();

    void SetUserData(void* UserData);

    BOOL HasNewVersion();

    BOOL Update();

    void Cancel();

	const char* GetPathName();
  private:
	virtual void OnProgress(unsigned int nRate);
    //nCode 返回值 0 成功
    //pDownloader 下载会话的句柄
    virtual void OnDownload(unsigned int nCode, CMDownloader* pDownloader);

  private:
    IMUpdateDataListener* m_pListener;

    void* m_UserData;

	CMDownloader* m_pDownloader;

	char m_path[512];
};



#endif /* CMUPDATE_H_HEADER_INCLUDED_B19A7B84 */
