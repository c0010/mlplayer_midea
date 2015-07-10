/*
 * cmversionverify.cpp

 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#include "cmsession.h"
#include "cmversionverify.h"
#include "tinyxml.h"

CMVersionVerify::CMVersionVerify(IMUpdateDataListener* pListener)
{
	m_UserData = NULL;
	m_pSession = NULL;
	m_pUpdateDataListener = pListener;
	bForceUpdate = FALSE;
}

CMVersionVerify::~CMVersionVerify()
{
	if(m_pSession)
		m_pSession->Cancel();
}

void CMVersionVerify::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

void CMVersionVerify::GetVersionMsg()
{
	if(!m_pSession)
		m_pSession = new CMSession(this);

	if(m_pSession && !m_pSession->IsRunning())
		m_pSession->Command(SERVICE_GETVERSIONVERIFY,"");
}

void CMVersionVerify::OnSessionCmd(unsigned int nCmdID, unsigned int nCode,
		TiXmlDocument* pDoc)
{

	INT32 Result = TResult::EUnknownError;

	if(nCode == MER_OK&&pDoc)
	{
		TiXmlElement *pItem = pDoc->RootElement();
		if(pItem)
		{
			INT32 nCmdID = 0;
			pItem->QueryIntAttribute("no", &nCmdID);

			INT32 nErr = 0;
			if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
			{
				if(nErr == 0)
				{
					Result = TResult::ESuccess;

					const char* pStr = NULL;

					pStr = pItem->Attribute("version");
					if(pStr)
						sVerCode = pStr;

					pStr = pItem->Attribute("releasenote");
					if(pStr)
						sVerNode = pStr;

					pStr = pItem->Attribute("downUrl");
					if(pStr)
						sDownUrl = pStr;
					int temp = 0;
					pItem->QueryIntAttribute("forceupdate",&temp);

					bForceUpdate = temp;

				}else
					Result = TResult::EUnknownError;
			}
		}

	}
	else if (nCode == MERN_OFFLINE)
	{
		Result = TResult::ENotSupportOffline;
	}
	else if(nCode == MERN_INITIALIZE)
	{
		Result = TResult::ENetDisconnect;
	}
	else
		Result = TResult::ENetTimeout;

	if(m_pUpdateDataListener)
		m_pUpdateDataListener->OnUpdateDataFinish(m_UserData,Result);

}

void CMVersionVerify::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

