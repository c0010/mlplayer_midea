// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmqacategory.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"
 CMQACategory* CMQACategory::m_pTHIS=NULL;


CMQACategory::CMQACategory(const CMQACategory& other)
:CMHandler<CMQACategoryItem*>()
{
    *this=other;
}

CMQACategory::CMQACategory()
:CMHandler<CMQACategoryItem*>()
{
    m_lstCategoryItem = NULL;
//	m_lstCategoryItem = m_lstCategoryItem = new CMList<CMQACategoryItem*>();
    m_pSession = NULL;   //初始化

    IsUpdate=false;
}

CMQACategory::~CMQACategory()
{
    if(m_lstCategoryItem)
        Clear(m_lstCategoryItem);
	SAFEDELETE(m_lstCategoryItem);
	SAFEDELETE(m_pSession);
}


CMQACategory* CMQACategory::GetInstance() {
	if (m_pTHIS == NULL)
		m_pTHIS = new CMQACategory();
	return m_pTHIS;
}



void CMQACategory::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

void CMQACategory::SetListener(IMUpdateDataListener* pUpdateDataListener) {
    
	m_pListener = pUpdateDataListener;
    
}



BOOL CMQACategory::UpdateData()                             //ui层调用该函数，向服务器请求数据
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
    
	if(m_pSession->IsRunning())
		return false;
    
    if(!IsUpdate)
    {
        return CMHandler<CMQACategoryItem*>::Request(SERVICE_SEARCHCATEGERY, "flag=qa");   //222接口
    }
    else
    {
        if(m_pListener)
            m_pListener->OnUpdateDataFinish(m_UserData, 0);

        return false;
        
    }
}

void CMQACategory::CancelUpdate()
{
    if(m_pSession)
        m_pSession->Cancel();
}

int CMQACategory::TopItemCount()                  //在ui层调用该函数，获得cell的numberofrows
{
	if(m_lstCategoryItem)
		return m_lstCategoryItem->size();
	else
		return 0;
}

CMQACategoryItem* CMQACategory::GetTopItem(int nIndex)           //在UI层调用该函数，给CMQACategoryItem 赋值
{
	if(m_lstCategoryItem)
		return m_lstCategoryItem->at(nIndex);
	else
		return NULL;
}

void CMQACategory::ClearTree()
{

    IsUpdate = false;
    Clear(m_lstCategoryItem);

}

void CMQACategory::Clear(CMList<CMQACategoryItem*>*plist)
{
	if(plist == NULL)
		return;
	for(CMList<CMQACategoryItem*>::iterator i = plist->begin();i < plist->end();i++)
	{
		CMQACategoryItem *p = (CMQACategoryItem*)*i;
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


void CMQACategory::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    
	INT32 result = TResult::EUnknownError;
    if (nCode == MER_OK)
    {

        IsUpdate=true;


        ASSERT(pDoc);
        TiXmlElement *pItem = pDoc->RootElement();

        INT32 nErr = 0;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no", &nCmdID);
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
		{
            if (nErr == 0)
            {
				if(nCmdID == SERVICE_SEARCHCATEGERY )
				{
					if(!pItem->NoChildren())
					{
						if(m_lstCategoryItem)
							Clear(m_lstCategoryItem);
						else
							m_lstCategoryItem = new CMList<CMQACategoryItem*>();
						CycParser(pItem,NULL);
					}
					if(m_lstCategoryItem && m_lstCategoryItem->size() > 0)
						result = TResult::ESuccess;
					else
						result = TResult::ENothing;
				}
				else
					result = TResult::EProtocolFormatError;        //跑到这里来了
			}
			else
				result = TResult::EUnknownError;
        }
		else
			result = TResult::EProtocolFormatError;
    }
	else if(nCode == MERN_INITIALIZE)
	{
		result = TResult::ENetDisconnect;
	}
	else
		result = TResult::ENetDisconnect;

	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData, result);
}

void CMQACategory::CycParser(TiXmlElement *pItem,CMQACategoryItem* pfather)
{
	if(!pItem)
		return;
	pItem = pItem->FirstChildElement("item");
	CMQACategoryItem *pchild = NULL;
	const CHAR *pStr = NULL;
	while(pItem)
	{
		pchild = new CMQACategoryItem;
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
            utf8ncpy(pchild->sCategoryTitle, pStr, 99);
		else
			pchild->sID[0] = '\0';
		//questioncount
		pItem->QueryIntAttribute("questioncount", &pchild->nQuestioncount);

		if(!pfather)
			m_lstCategoryItem->push_back(pchild);
		else
		{
			if(!pfather->m_lstCategoryItem)
				pfather->m_lstCategoryItem = new CMList<CMQACategoryItem*>;

			pfather->m_lstCategoryItem->push_back(pchild);
		}
		if(!pItem->NoChildren())
			CycParser(pItem,pchild);

		pItem = pItem->NextSiblingElement("item");
	}
}

//CMQACategoryItem/////////////////////////
CMQACategoryItem::CMQACategoryItem()
: m_lstCategoryItem(NULL)
{
	memset(sID, 0, 64);
    memset(sCategoryTitle, 0, 100);
    nQuestioncount = 0;
}


CMQACategoryItem::~CMQACategoryItem()
{
}

int CMQACategoryItem::ChildItemCount()
{
	if(m_lstCategoryItem)
		return m_lstCategoryItem->size();
	else
		return 0;
}

CMQACategoryItem* CMQACategoryItem::GetChildItem(int nIndex)
{
	if(nIndex >= 0 && nIndex < ChildItemCount())
		return m_lstCategoryItem->at(nIndex);
	else
		return NULL;
}




BOOL CMQACategory::DoGetCacheItems(sqlite3* db)
{
    
    return  TRUE;
}

BOOL CMQACategory::DoRefresh(CMQACategoryItem* & obj){
    
    return  TRUE;
}

BOOL CMQACategory::DoUpdate(CMQACategoryItem* const & obj){
    return  TRUE;
}

BOOL CMQACategory::DoCreate(sqlite3* db){
    return TRUE;
}

BOOL CMQACategory::DoPutItem(TiXmlElement* pItem, sqlite3* db,
                               CMQACategoryItem* & item) {
	return TRUE;
    
}


