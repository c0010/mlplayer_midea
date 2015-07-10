#include "stdafx.h"
#include "cmretrievepass.h"
#include "tinyxml.h"
#include "cmglobal.h"
#include "cmsession.h"
#include "cmsettings.h"
#include "utf8ncpy.h"

CMRetrievePass::CMRetrievePass(IMSimpleResultListener* pListener)
{
	m_pListener = pListener;

	m_pSession = NULL;
	bzero(m_Msg, 300);
}

void CMRetrievePass::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

void CMRetrievePass::Commit(const char* emialorphone)
{
	char sParams[100] = {0};
	sprintf(sParams, "info=%s", emialorphone);
    
	if (m_pSession == NULL) {
		m_pSession = new CMSession(this);
	}
    if (m_pSession) {
			m_pSession->Command(SERVICE_RETRIEVEPASSWD, sParams);
	}
}

void CMRetrievePass::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    if (nCode == MER_OK)
    {
        ASSERT(pDoc);
        TiXmlElement *pItem = pDoc->RootElement();
        
        INT32 nErr = 0;

        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
        {
            if (nErr == 0)
            {
                //成功 保存邮箱地址
                utf8ncpy(m_Msg, pItem->Attribute("mailurl"), 299);
                
                if(m_pListener)
                    m_pListener->OnRequestFinish(m_UserData, TResult::ESuccess);
                return;
            }
            else //if (nErr == MERS_ALTERPSW)
            {
                //失败 保存错误信息
                utf8ncpy(m_Msg, pItem->Attribute("msg"), 299);
                
                CM_ERRP("modify pass failed %d", nErr);
                
                if(m_pListener)
                    m_pListener->OnRequestFinish(m_UserData, nErr);
                return;
            }
        }
    }
    if(m_pListener)
        m_pListener->OnRequestFinish(m_UserData, TResult::EUnknownError);
}

char* CMRetrievePass::getPMsg()
{
	return m_Msg;
}

CMRetrievePass::~CMRetrievePass()
{
	SAFEDELETE(m_pSession);
}
