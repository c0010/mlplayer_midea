//
//  cmupload.cpp
//  MLPlayer
//
//  Created by wmgwd on 13-11-11.
//  Copyright (c) 2013年 w. All rights reserved.
//

#include "stdafx.h"
#include "cmupload.h"


CMFileUpload* CMFileUpload::m_pTHIS = NULL;

CMFileUpload* CMFileUpload::GetInstance()
{
    if (!m_pTHIS)
    {
        m_pTHIS = new CMFileUpload();
    }

    return m_pTHIS;
}

CMFileUpload::CMFileUpload()
{
    m_lstItem = NULL;

    memset(m_tablename, 0, 64);

    m_bUploaded = FALSE;

    m_pSimpleListener = NULL;
}

CMFileUpload::~CMFileUpload()
{
    if (m_lstItem)
    {
        m_lstItem->clear();
    }
    SAFEDELETE(m_lstItem);
}

void CMFileUpload::SetUserData(void* userData)
{
    m_UserData = userData;
}


void CMFileUpload::SetListener(IMSimpleResultListener *pListener)
{
    m_pSimpleListener = pListener;
}

//加入队列 -1为失败 否则返回列表中当前正在上传文件的index
int CMFileUpload::Append(const CMFileInfo &file)
{
    INT32 nIndex = -1;

    if (!m_lstItem)
    {
        m_lstItem = new CMList<CMFileInfo>;
    }

    if(CMGlobal::TheOne().IsOffline()){//离线
    	if(m_pSimpleListener)
    		m_pSimpleListener->OnRequestFinish(m_UserData, TResult::ENetDisconnect);
    	return  nIndex;
    }

    if (m_lstItem)
    {
//        nIndex = m_lstItem->indexOf(file);

        if (nIndex == -1)
        {
            m_lstItem->push_back(file);

            nIndex = m_lstItem->size() - 1;

            Start(nIndex);
        }
        
    }

    return nIndex;
}

//从队列删除
void CMFileUpload::Delete(int nIndex)
{
    if (m_lstItem && nIndex >= 0 && nIndex < m_lstItem->size())
    {
        m_lstItem->removeAt(nIndex);

        if (nIndex == m_nCurrIndex)
        {
            Start(nIndex);
        }
        else if (nIndex < m_nCurrIndex)
        {
            m_nCurrIndex--;
        }
    }
}

//开始上传
BOOL CMFileUpload::Start(int nIndex)
{
    if (m_lstItem && nIndex >= 0 && nIndex < m_lstItem->size())
    {
        if (!m_pSession)
        {
            m_pSession = new CMSession(this);
        }

        if (m_pSession->IsRunning())
        {
            return FALSE;
        }


        //开始上传任务
        m_bUploaded = FALSE;

        m_nCurrIndex = nIndex;

        CMFileInfo& file = m_lstItem->at(nIndex);
        m_pSession->CommandPost(file.m_nCmdID, file.m_sParm.c_str(), file.m_list);

        return TRUE;
    }

    return FALSE;
}

//暂停上传 保留接口
void CMFileUpload::Stop()
{

}

void CMFileUpload::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    INT32 result = TResult::EUnknownError;

	if (nCode == MER_OK)
	{
        TiXmlElement *pItem = pDoc->RootElement();

		INT32 nErr = -1;
        INT32 nCmdID = 0;

        pItem->QueryIntAttribute("no", &nCmdID);

        if (nCmdID == SERVICE_UPMESSAGEPICTURE || nCmdID == SERVICE_UPGROUPHEADER) {
            const CHAR* urlStr = NULL;

            if(!pItem->NoChildren())
            {

                TiXmlElement* psonItem = pItem->FirstChildElement("item");

                urlStr = psonItem->Attribute("url");
                if(urlStr){
                    url = urlStr;
                }

                urlStr = psonItem->Attribute("thumb_url");
                if(urlStr){
                    thumb_url = urlStr;
                }

            }
        }
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
        {
            if (nErr == 0)
            {
                m_bUploaded = TRUE;

                result = TResult::ESuccess;
            }
            else
            {
                result = nErr;
            }
        }
        else
        {
            result = TResult::EProtocolFormatError;
        }
    }
    else if(nCode == MERN_INITIALIZE)
    {
		result = TResult::ENetDisconnect;
    }
	else if(nCode == MERN_OFFLINE)
    {
		result = TResult::ENotSupportOffline;
    }
	else
    {
		result = TResult::ENetTimeout;
    }



    if(m_nCurrIndex < m_lstItem->size())
    {

//    	CMFileInfo& file = m_lstItem->at(m_nCurrIndex);

//		sMsgCode = file.sMsgCode;


//    	file.OnSimpleResultFinish(result);

        if (m_pSimpleListener)
        	m_pSimpleListener->OnRequestFinish(m_UserData, result);

    }



    //该任务上传成功 从队列移除
//    if (m_bUploaded)
//    {
	Delete(m_nCurrIndex);
//    }
}


BOOL CMFileUpload::DoCreate(sqlite3* db)
{
    return TRUE;
}


BOOL CMFileUpload::DoPutItem(TiXmlElement* pItem, sqlite3* db, CMFileInfo& item)
{    return TRUE;
}

BOOL CMFileUpload::DoGetCacheItems(sqlite3* db)
{
    return TRUE;
}

BOOL CMFileUpload::DoRefresh(CMFileInfo& obj)
{
    return TRUE;
}

BOOL CMFileUpload::DoUpdate(const CMFileInfo &obj)
{
    return TRUE;
}




