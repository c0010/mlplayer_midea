// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmsearchhotkey.h"
#include "cmglobal.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"


CMSearchHotKey* CMSearchHotKey::m_pTHIS = NULL;

CMSearchHotKey* CMSearchHotKey::GetInstance()
{
	if(m_pTHIS == NULL)
		m_pTHIS = new CMSearchHotKey();
	return m_pTHIS;
}

CMSearchHotKey::CMSearchHotKey()
{
	m_pListener = NULL;
	m_UserData = NULL;
	m_pSession = NULL;
	
	m_lstHotKey = new CMList<THotKey*>;
}

CMSearchHotKey::~CMSearchHotKey()
{
	Clear();
	SAFEDELETE(m_lstHotKey);
}

void CMSearchHotKey::SetListener(IMUpdateDataListener* pListener)
{
	 m_pListener = pListener;
}

void CMSearchHotKey::Clear()
{
	if (m_lstHotKey) {

		for(CMList<THotKey*>::iterator i = m_lstHotKey->begin();i < m_lstHotKey->end();i++)
		{
			THotKey* pItem = (THotKey*)*i;
			for (CMList<char*>::iterator it1 = pItem->m_lstItem->begin(); it1 != pItem->m_lstItem->end(); it1++)
			{
				const char* pstr = (const char*)*it1;
				SAFEDELETE(pstr);
			}
			pItem->m_lstItem->clear();
			SAFEDELETE(pItem->m_lstItem);
			SAFEDELETE(pItem);
		}
		m_lstHotKey->clear();
		
	}

	SAFEDELETE(m_pSession);
}
void CMSearchHotKey::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

BOOL CMSearchHotKey::GetHotKey()
{
	Clear();
	
	if (!m_pSession) 
		 m_pSession = new CMSession(this);
	   
	if (m_pSession->IsRunning())
		return FALSE;
	
	m_pSession->Command(SERVICE_SEARCH_HOTKEY, ""); 
	
	return TRUE;
}
int CMSearchHotKey::GetItemCount(const char* sflag)
{
	for(CMList<THotKey*>::iterator i = m_lstHotKey->begin();i < m_lstHotKey->end();i++)
	{
		THotKey* pItem = (THotKey*)*i;
		if(pItem)
		{
			if(strcmp(pItem->flag, sflag) == 0 && pItem->m_lstItem)
				return pItem->m_lstItem->size();
		  }
	}
	return 0;
}

const char* CMSearchHotKey::GetItem(const char* sflag,int nIndex)
{
	for(CMList<THotKey*>::iterator i = m_lstHotKey->begin();i < m_lstHotKey->end();i++)
	{
		THotKey* pItem = (THotKey*)*i;
		if(pItem)
		{
			if(strcmp(pItem->flag, sflag) == 0)
			{
				if(nIndex >=0 && nIndex < pItem->m_lstItem->size() && pItem->m_lstItem)
					return pItem->m_lstItem->at(nIndex);
			}
		}
	}
	return NULL;
	
}
//课程热词
int CMSearchHotKey::GetCourseHotKeyItemCount()
{
	return GetItemCount("course");
}

const char* CMSearchHotKey::GetCourseHotKeyItem(int nIndex)
{
	return GetItem("course",nIndex);	
}

//资讯热词
int CMSearchHotKey::GetNewsHotKeyItemCount()
{
	return GetItemCount("news");
}

const char* CMSearchHotKey::GetNewsHotKeyItem(int nIndex)
{
	return GetItem("news",nIndex);	
}

//问答热词
int CMSearchHotKey::GetQaHotKeyItemCount()
{
	return GetItemCount("qa");
}
const char* CMSearchHotKey::GetQaHotKeyItem(int nIndex)
{
	return GetItem("qa",nIndex);
}

void CMSearchHotKey::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;
    if (nCode == MER_OK)
    {
        ASSERT(pDoc);
        TiXmlElement *pItem = pDoc->RootElement();
		
        INT32 nErr = 0;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no", &nCmdID);
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
		{
            if (nErr == 0)
            {
				if(nCmdID == SERVICE_SEARCH_HOTKEY)
				{
					pItem = pItem->FirstChildElement();
					const char* pstr = NULL;
					TiXmlElement* pChild = NULL;
					while (pItem)
					{
						pstr = pItem->Attribute("type");
						if (!pstr)
						{
							pItem = pItem->NextSiblingElement("outline");
							continue;
						}
						THotKey* hotkey = new THotKey;
						memset(hotkey, 0, sizeof(THotKey));
						utf8ncpy(hotkey->flag, pstr, 15);
						
						hotkey->m_lstItem = new CMList<char*>;
						
						pChild = pItem->FirstChildElement("item");
						while (pChild)
						{
							pstr = pChild->GetText();
							char* pkey = new char[strlen(pstr) + 1];
							memset(pkey, 0, strlen(pstr)+1);
                            utf8ncpy(pkey, pstr, strlen(pstr)+1);
							
							hotkey->m_lstItem->push_back(pkey);
							pChild = pChild->NextSiblingElement("item");
						}
						
						m_lstHotKey->push_back(hotkey);
						pItem = pItem->NextSiblingElement("outline");
					}
					if(m_lstHotKey && m_lstHotKey->size() > 0)
						result = TResult::ESuccess;
					else
						result = TResult::ENothing;
				}
				else
					result = TResult::EProtocolFormatError;
			}
			else
				result = TResult::EUnknownError;
        }
		else
			result = TResult::EProtocolFormatError;
    }
    else if (nCode == MERN_OFFLINE)
    {
		result = TResult::ENotSupportOffline;
    }
	else if(nCode == MERN_INITIALIZE)
		result = TResult::ENetDisconnect;
	else
		result = TResult::ENetTimeout;
	
	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData, result);
}
