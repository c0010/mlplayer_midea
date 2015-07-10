// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmfeedback.h"
#include "cmglobal.h"
#include "tinyxml.h"
#include "cmsession.h"

CMFeedback::CMFeedback(IMSimpleResultListener* pListener)
{
	m_pListener = pListener;
	m_pSession = NULL;
}

CMFeedback::~CMFeedback()
{
	if (m_pSession) {
		SAFEDELETE(m_pSession);
	}
}

void CMFeedback::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

	/**
	 suggestion 建议文本
	 mode 手机品牌与型号（选填，用户不填该信息不带该参数）
	 **/
void CMFeedback::CommitFeedback(const char* sSuggestion, const char* sModel)
{
    const CHAR* pSuggestion = CMGlobal::TheOne().Encode(sSuggestion);
    const CHAR* pModel = CMGlobal::TheOne().Encode(sModel);

    CMString sParams("suggestion=");
	sParams += pSuggestion;
	sParams += L"&mode=";
	sParams += pModel;

	SAFEDELETE(pSuggestion);
	SAFEDELETE(pModel);
   
	if (m_pSession == NULL) {
		m_pSession = new CMSession(this);
	}	
	//CMSession& session = CMGlobal::TheOne().HttpMgr().GetSession(this);
	
	if (m_pSession) {
		m_pSession->Command(SERVICE_FEEDBACK, sParams);
	}
  
}

//interface from IMNotifySession
void CMFeedback::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;

    if (nCode == MER_OK && SERVICE_FEEDBACK == nCmdID)
    {
        ASSERT(pDoc);
        TiXmlElement *pItem = pDoc->RootElement();

        INT32 nErr = 0;
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
        {
            if (nErr == 0)
            {
            	result = TResult::ESuccess;
            }
            else
            {
                CM_ERRP("send feedback failed %d", nErr);
            }
        }
    }
	else if(nCode == MERN_OFFLINE)
	{
		result = TResult::ENotSupportOffline;
	}

	if(m_pListener)
	{
		m_pListener->OnRequestFinish(m_UserData, result);
	}

}
