// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmwebimage.h"
#include "cmdownloader.h"
#include "cmfile.h"
#include "cmpath.h"
#include "cmglobal.h"
#include "utf8ncpy.h"

CMWebImage::CMWebImage(IMGetImageListener* pListener)
{
	m_pListener = pListener;
	m_lstPicUrl = NULL;
    m_UserData = NULL;
	m_pDownloader = NULL;
}

CMWebImage::~CMWebImage()
{
	SAFEDELETE(m_pDownloader);

	if(m_lstPicUrl)
	{
		for(CMList<PicUrl*>::iterator i = m_lstPicUrl->begin();i < m_lstPicUrl->end();i++)
	        delete (*i);
		m_lstPicUrl->clear();
	}
	SAFEDELETE(m_lstPicUrl);
}

void CMWebImage::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

BOOL CMWebImage::GetFromUrl(int nID, const char* sUrl)
{
	CMString url = sUrl;
	INT32 pos = 0;
	PicUrl * pPicUrl = NULL;

	if(!sUrl || strlen(sUrl) <= 0)
		goto ret;

    pos = url.ReverseFind(L"/");
    if(pos < 0)
        goto ret;

    if(GetFilePath(sUrl))
		return TRUE;//CMFile::DeleteFile(sFilePath);

	if(m_lstPicUrl)
	{
		for(int i=0; i<m_lstPicUrl->size();i++)
		{
			pPicUrl = (PicUrl *)m_lstPicUrl->at(i);
			if(strcmp(pPicUrl->url, sUrl) == 0)
				goto ret;
		}
	}
	//加入下载列表
	pPicUrl = new PicUrl;
	pPicUrl->id = nID;
    
    utf8ncpy(pPicUrl->url, sUrl, 299);

	if(!m_lstPicUrl)
		m_lstPicUrl = new CMList<PicUrl*>;
	m_lstPicUrl->push_back(pPicUrl);
	
	DownloadNext();

	return FALSE;
ret:
	if(m_pListener)
		m_pListener->OnFinish(m_UserData,TResult::EUnknownError,nID);
	return FALSE;	
}

void CMWebImage::Cancel()
{
	m_pDownloader->Cancel();
}

const char* CMWebImage::GetFilePath(const char* sUrl)
{
    if(sUrl==NULL)
        return NULL;
	FormatFilePath(sUrl);
	if(!CMFile::FileExist(m_sFilePath))
		return NULL;
	return (const char*)m_sFilePath;
}
void CMWebImage::FormatFilePath(const char* sUrl)
{
	m_sFilePath.Empty();
	CMString url = sUrl;
    INT32 pos = url.ReverseFind(L"/");
    if(pos < 0)
        return;
	m_sFilePath = CMPath(CMPath::TEMP_PATH).String() + CMFile::GetTempFileName(url, L"") + "@2x." + CMFile::GetFileExt(url.Mid(pos+1));
}
void CMWebImage::DownloadNext()
{
    if (CMGlobal::TheOne().IsOffline())
	{
		if(m_pListener)
			m_pListener->OnFinish(m_UserData, MERN_OFFLINE, 0);
        return;
	}
    
	if(!m_pDownloader)
	{
		m_pDownloader = new CMDownloader(this);
#if defined(PLAT_IOS) || defined(PLAT_AND)
		m_pDownloader->SetMaxFileSize(1024*1024);
#else
		m_pDownloader->SetMaxFileSize(512*1024);
#endif
	}

	if(m_pDownloader->GetStatus() == CMDownloader::RUNNING)
		return;

	if(m_lstPicUrl->size() > 0)
	{
		PicUrl* pPicUrl = (PicUrl*)m_lstPicUrl->at(0);
		if(pPicUrl)
		{
			FormatFilePath(pPicUrl->url);
			CMString sID;
			CMGlobal::TheOne().GetSessionID(sID);
			CMString url = pPicUrl->url;		
			INT32 pos = url.ReverseFind(L"?");
			if(pos < 0)
				url += L"?sid=";
			else
				url += L"&sid=";
			url += sID;
		
			m_pDownloader->Download(url, m_sFilePath);
		}
	}
}
//nCode 返回值 0 成功
//pDownloader 下载会话的句柄
void CMWebImage::OnDownload(unsigned int nCode, CMDownloader* pDownloader)
{
//	CM_ERRP("CMWebImage::OnDownload:%d",nCode);
	if(m_lstPicUrl->size() > 0)
	{
		PicUrl * pPicUrl = (PicUrl*)m_lstPicUrl->at(0);
		m_lstPicUrl->removeAt(0);
		if(m_lstPicUrl->size() > 0)
			DownloadNext();
		if(pPicUrl && m_pListener)
		{
			int id = pPicUrl->id;
			SAFEDELETE(pPicUrl);
			if(nCode == MER_OK)
			{
				m_pListener->OnFinish(m_UserData,TResult::ESuccess, id);
			}
			else
			{
				m_pListener->OnFinish(m_UserData,TResult::EUnknownError, id);
			}		
		}
	}
}
