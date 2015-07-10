/*

 * cmmessage.cpp
 *
 *  Created on: 2015年03月13日
 *      Author: Administrator
 */

#include "stdafx.h"
#include "cmmessage.h"

CMMessage::CMMessage()
{
	sUrl = "";
	sThumbUrl = "";
	m_pSession = NULL;
	m_pSimpleListener = NULL;
}

CMMessage::~CMMessage()
{
	CM_ERR("cancel");
	if(m_pSession)
		m_pSession->Cancel();
}

void CMMessage::SetListener(IMSimpleResultListener* pListener)
{
	m_pSimpleListener = pListener;
}

void CMMessage::SetUserData(void* userdata)
{
	m_pUserData = userdata;
}

CMMessage& CMMessage::operator=(const TiXmlElement* right)
{

}

BOOL CMMessage::UploadPic(const char* filename)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	CMList<FormData> list;

	FormData data;

	if(filename && strlen(filename) > 0)
	{
		data.key = CMString("pic");
		data.value = CMString(filename);
		data.dataType = 2;
		list.push_back(data);
	}
	else
	{
		return FALSE;
	}

	m_pSession->CommandPost(SERVICE_UPMESSAGEPICTURE,"",list,SEQUENCE_CHAT);
	return TRUE;
}

void CMMessage::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;

	CM_ERR("the OnSessionCmd");

	if (nCode == MER_OK)
	{
		TiXmlElement *pItem = pDoc->RootElement();

		INT32 nErr = -1;
		INT32 nCmdID = 0;

		pItem->QueryIntAttribute("no", &nCmdID);

		if (nCmdID == SERVICE_UPMESSAGEPICTURE) {
			const CHAR* urlStr = NULL;

			if(!pItem->NoChildren())
			{
				result = TResult::ESuccess;

				TiXmlElement* psonItem = pItem->FirstChildElement("item");

				urlStr = psonItem->Attribute("url");
				if(urlStr){
					sUrl = urlStr;
				}

				urlStr = psonItem->Attribute("thumb_url");
				if(urlStr){
					sThumbUrl = urlStr;
				}

			}
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


	if(m_pSimpleListener)
		m_pSimpleListener->OnRequestFinish(m_pUserData,result);

}
