/*
 *  cmdevicetoken.cpp
 *  MLPlayer
 *
 *  Created by sunjj on 12-6-6.
 *  Copyright 2012 w. All rights reserved.
 *
 */
#include "stdafx.h"
#include "cmdevicetoken.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "cmglobal.h"

CMDeviceToKen::CMDeviceToKen(IMSimpleResultListener* pListener)
{
	m_pListener = pListener;
	m_pSession = NULL;
	m_UserData = NULL;
}

CMDeviceToKen::~CMDeviceToKen()
{
	if (m_pSession) {
		m_pSession->Cancel();
	}
	SAFEDELETE(m_pSession);
}

void CMDeviceToKen::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

//回传设备令牌	该条协议支持匿名访问（iOS专用）
void CMDeviceToKen::SendDeviceToKen(const char* sDeviceToKen)
{
	const CHAR* pDeviceToKen= CMGlobal::TheOne().Encode(sDeviceToKen);
	
	char sParam[200];
	snprintf(sParam,200,"devicetoken=%s", pDeviceToKen);
	SAFEDELETE(pDeviceToKen);
	
	if(!m_pSession)
		m_pSession = new CMSession(this);
    m_pSession->Command(SERVICE_DEVICETOKEN, sParam);
}

void CMDeviceToKen::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	if (nCode == MER_OK)
    {
        //获得根元素res。
        TiXmlElement *pItem = pDoc->RootElement();
		
        if(pItem)
        {
            INT32 nCmdID = 0;
            pItem->QueryIntAttribute("no", &nCmdID);
            INT32 nErr = 0;
            if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
            {
                if (nErr == 0 && nCmdID  ==  SERVICE_DEVICETOKEN)
                {
					m_pListener->OnRequestFinish(m_UserData,TResult::ESuccess);
					return ;
                }
            }
        }
    }
	m_pListener->OnRequestFinish(m_UserData,TResult::EUnknownError);
}
