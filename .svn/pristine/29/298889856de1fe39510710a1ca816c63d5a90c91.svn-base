// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "cmresetpassword.h"
#include "tinyxml.h"
#include "cmglobal.h"
#include "cmsession.h"
#include "cmsettings.h"
#include "utf8ncpy.h"

CMResetPassword::CMResetPassword(IMSimpleResultListener* pListener)
{
	m_pListener = pListener;
	
	m_pSession = NULL;
}

CMResetPassword::~CMResetPassword()
{
	SAFEDELETE(m_pSession);
}

void CMResetPassword::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

void CMResetPassword::Commit(const char* sOld, const char* sNew)
{
    
    utf8ncpy(m_sNewPass, sNew, 99);
	char sParams[1024] = {0};
	const CHAR* pName = CMGlobal::TheOne().Encode(SETTING.GetUserName());
	const CHAR* pOld = CMGlobal::TheOne().Encode((const CHAR*)CMGlobal::TheOne().EncryptPass(sOld));
	const CHAR* pNew = CMGlobal::TheOne().Encode((const CHAR*)CMGlobal::TheOne().EncryptPass(sNew));
	snprintf(sParams, sizeof(sParams),"loginname=%s&oldpwd=%s&newpwd=%s", pName,pOld,pNew);
	SAFEDELETE(pName);
	SAFEDELETE(pOld);
	SAFEDELETE(pNew);

	CM_ERRP("the url:%s",sParams);

	if (m_pSession == NULL) {
		m_pSession = new CMSession(this);
	}
    if (m_pSession) {
			m_pSession->Command(SERVICE_ALTERPWD, sParams);
	}
   
}

//interface from IMNotifySession
void CMResetPassword::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
          INT32 result = TResult::EUnknownError;
	
    if (nCode == MER_OK)
    {
        ASSERT(pDoc);
        TiXmlElement *pItem = pDoc->RootElement();

        INT32 nErr = 0;
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
        {
            if (nErr == 0)
            {
                //修改成功
				SETTING.SetUserPass(m_sNewPass);
                SETTING.Save();
				
                if(m_pListener)
					m_pListener->OnRequestFinish(m_UserData, TResult::ESuccess);
				return;
            }
            else //if (nErr == MERS_ALTERPSW)
            {
                CM_ERRP("modify pass failed %d", nErr);
            }
        }
    }
    else if(nCode == MERN_OFFLINE)
	{
		result = TResult::ENotSupportOffline;
	 }else
		result = TResult::ENetTimeout;
	if(m_pListener)
		m_pListener->OnRequestFinish(m_UserData, result );
}
