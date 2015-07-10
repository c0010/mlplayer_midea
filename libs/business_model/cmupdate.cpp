// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmupdate.h"
#include "cmglobal.h"
#include "cmdownloader.h"
#include "cmpath.h"
#include "cmfile.h"
#include "utf8ncpy.h"

CMUpdate::CMUpdate(IMUpdateDataListener* pListener)
{
	m_pListener = pListener;
	m_pDownloader = NULL;
}

CMUpdate::~CMUpdate()
{
	SAFEDELETE(m_pDownloader);
}

void CMUpdate::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

BOOL CMUpdate::HasNewVersion()
{
	return !CMGlobal::TheOne().GetUpdateUrl().IsEmpty();
}

BOOL CMUpdate::Update()
{

	if(CMGlobal::TheOne().GetUpdateUrl().IsEmpty())
		return FALSE;
	if(!m_pDownloader)
		m_pDownloader = new CMDownloader(this);

	if(m_pDownloader->GetStatus() == CMDownloader::RUNNING)
		return FALSE;
	CMString sUrl = CMGlobal::TheOne().GetUpdateUrl();
    INT32 pos = sUrl.ReverseFind(L"/");
    if(pos < 0)
        return FALSE;

    CMString sFilePath = CMPath(CMPath::DOWNLOAD_PATH).String() + sUrl.Mid(pos+1);
    if(CMFile::FileExist(sFilePath))
		CMFile::DeleteFile(sFilePath);

	m_pDownloader->SetProgress(TRUE);
	m_pDownloader->Download(CMGlobal::TheOne().GetUpdateUrl(),sFilePath);
	return TRUE;
}

void CMUpdate::Cancel()
{
	if(m_pDownloader)
		m_pDownloader->Cancel();
}
void CMUpdate::OnProgress(unsigned int nRate)
{
	if(m_pListener)
		m_pListener->OnUpdateDataProgress(m_UserData,nRate);
}

//nCode 返回值 0 成功
//pDownloader 下载会话的句柄
void CMUpdate::OnDownload(unsigned int nCode, CMDownloader* pDownloader)
{
	if(nCode == MER_OK)
		m_pListener->OnUpdateDataFinish(m_UserData,TResult::ESuccess);
	else
		m_pListener->OnUpdateDataFinish(m_UserData,TResult::EUnknownError);
		
}
const char* CMUpdate::GetPathName()
{
	if(m_pDownloader)
	{
		CMString str;
		m_pDownloader->GetPathName(str);        
        utf8ncpy(m_path, (const CHAR*)str, 511);
		return m_path;
	}
	return NULL;
}
