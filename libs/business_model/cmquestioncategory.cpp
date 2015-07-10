// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmquestioncategory.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"

CMQuestionCategory::CMQuestionCategory(IMUpdateDataListener* pListener)
: m_pListener(pListener)
, m_UserData(NULL)
, m_lstCategoryItem(NULL)
, m_pSession(NULL)
{
}


CMQuestionCategory::~CMQuestionCategory()
{
	Clear(m_lstCategoryItem);	
	SAFEDELETE(m_lstCategoryItem);
	SAFEDELETE(m_pSession);
}

void CMQuestionCategory::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

BOOL CMQuestionCategory::Update()
{
	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(!m_pSession->IsRunning())
	{
		CMString sParam;
		m_pSession->Command(SERVICE_GETQUESTIONCATEGORY, sParam);
	}
	else 
		return FALSE;
	return TRUE;
}

void CMQuestionCategory::CancelUpdate()
{
	if(m_pSession)
		m_pSession->Cancel();
}

int CMQuestionCategory::TopItemCount()
{
	if(m_lstCategoryItem)
		return m_lstCategoryItem->size();
	else
		return 0;
}

CMQuestionCategoryItem* CMQuestionCategory::GetTopItem(int nIndex)
{
	if(m_lstCategoryItem)
		return m_lstCategoryItem->at(nIndex);
	else
		return NULL;
}

void CMQuestionCategory::Clear(CMList<CMQuestionCategoryItem*>*plist)
{
	if(plist == NULL)
		return;
	for(CMList<CMQuestionCategoryItem*>::iterator i = plist->begin();i < plist->end();i++)
	{
		CMQuestionCategoryItem *p = (CMQuestionCategoryItem*)*i;
		if(p->m_lstCategoryItem != NULL && p->m_lstCategoryItem->size() > 0)
			Clear(p->m_lstCategoryItem);
		else
		{
			delete p;
			p = NULL;
		}
	}
	plist->clear();
}


void CMQuestionCategory::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
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
				if(nCmdID == SERVICE_GETQUESTIONCATEGORY)
				{
					Clear(m_lstCategoryItem);
					if(!pItem->NoChildren())
					{
						if(m_lstCategoryItem)
							Clear(m_lstCategoryItem);
						else
							m_lstCategoryItem = new CMList<CMQuestionCategoryItem*>();
						CycParser(pItem,NULL);
					}
					if(m_lstCategoryItem && m_lstCategoryItem->size() > 0)
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
	{
		result = TResult::ENetDisconnect;
	}
	else
		result = TResult::ENetTimeout;

	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData, result);
}

void CMQuestionCategory::CycParser(TiXmlElement *pItem,CMQuestionCategoryItem* pfather)
{
	if(!pItem)
		return;
	pItem = pItem->FirstChildElement("item");
	CMQuestionCategoryItem *pchild = NULL;
	const CHAR *pStr = NULL;
	while(pItem)
	{
		pchild = new CMQuestionCategoryItem;
		if(!pchild)
			break;
		//id
		pStr = pItem->Attribute("id");
		if(pStr)
            utf8ncpy(pchild->sID, pStr, 63);
		else
			pchild->sID[0] = '\0';
		//title
		pStr = pItem->Attribute("title");
		if(pStr)
            utf8ncpy(pchild->sTitle, pStr, 99);
		else
			pchild->sID[0] = '\0';
		//questioncount
		pItem->QueryIntAttribute("questioncount", &pchild->nQuestioncount);
		//uncompletecount
		pItem->QueryIntAttribute("uncompletecount",&pchild->nUncompletecount);
		//wrongcount
		pItem->QueryIntAttribute("wrongcount",&pchild->nWrongcount);
		if(pchild->nWrongcount > 0)
		{
			if(!pfather)
				m_lstCategoryItem->push_back(pchild);
			else
			{
				if(!pfather->m_lstCategoryItem)
					pfather->m_lstCategoryItem = new CMList<CMQuestionCategoryItem*>;
	
				pfather->m_lstCategoryItem->push_back(pchild);
			}
		}
		if(!pItem->NoChildren())
			CycParser(pItem,pchild);

		pItem = pItem->NextSiblingElement("item");
	}
}

//CMQuestionCategoryItem/////////////////////////
CMQuestionCategoryItem::CMQuestionCategoryItem()
: m_lstCategoryItem(NULL)
{
	memset(sID, 0, 64);
    memset(sTitle, 0, 100);
    nQuestioncount = 0;
    nUncompletecount = 0;
    nWrongcount = 0;
}


CMQuestionCategoryItem::~CMQuestionCategoryItem()
{
}

int CMQuestionCategoryItem::ChildItemCount()
{
	if(m_lstCategoryItem)
		return m_lstCategoryItem->size();
	else
		return 0;
}

CMQuestionCategoryItem* CMQuestionCategoryItem::GetChildItem(int nIndex)
{
	if(nIndex >= 0 && nIndex < ChildItemCount())
		return m_lstCategoryItem->at(nIndex);
	else
		return NULL;
}
