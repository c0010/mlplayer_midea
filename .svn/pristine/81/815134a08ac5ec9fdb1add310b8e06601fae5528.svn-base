// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmsearch.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "tinyxml.h"
#include "cmfile.h"

CMSearch::CMSearch(IMUpdateDataListener* pListener)
:CMContenthandler()
,m_lstKey(NULL)
{
    SetListener(pListener, NULL);
	LoadKey();
}

CMSearch::~CMSearch()
{
	if(m_lstKey)
	{
		for(int i = 0;i < m_lstKey->size();i++)
		{
			char * k = m_lstKey->at(i);
			if(k)
				delete[] k;
			m_lstKey->removeAt(i);
		}
		delete m_lstKey;
	}
}

BOOL CMSearch::Search(const char* sFlag, const char* skey)
{
	if(!skey)
		return FALSE;

	SaveKey(skey);
    
	char sParam[256];
    const CHAR* pKey = CMGlobal::TheOne().Encode(skey);
    snprintf(sParam,sizeof(sParam),"flag=%s&key=%s", sFlag, pKey);
	SAFEDELETE(pKey);
	SetPaging(TRUE);
	Clear();
	return CMContenthandler::Request(SERVICE_SEARCH,sParam);
}

BOOL CMSearch::QuickSearch(const char* sFlag, const char* skey)
{
    if (IsRunning()) {
        //快速搜索取消上次搜索
        Cancel();
    }
    
    if(!skey)
        return FALSE;
    
  //  SaveKey(skey);
    
    char sParam[256];
    const CHAR* pKey = CMGlobal::TheOne().Encode(skey);
    snprintf(sParam,sizeof(sParam),"flag=%s&key=%s", sFlag, pKey);
    SAFEDELETE(pKey);
    
    Clear();
    return CMContenthandler::Request(SERVICE_SEARCH,sParam);
}


BOOL CMSearch::CategorySearch(const char* sFlag, const char* categoryID, const char* categoryTitle)
{
	if(!categoryID)
		return FALSE;
    
//	SaveKey(categoryTitle);

	char sParam[256];
    const CHAR* pKey = CMGlobal::TheOne().Encode(categoryID);
    snprintf(sParam,sizeof(sParam),"flag=%s&categoryid=%s", sFlag, pKey);
	SAFEDELETE(pKey);
    SetPaging(TRUE);

	Clear();
	return CMContenthandler::Request(SERVICE_SEARCH,sParam);
}

int CMSearch::GetRecentKeyCount()
{
	if(m_lstKey)
		return m_lstKey->size();
	else
		return 0;
}

const char* CMSearch::GetRecentKeyItem(int nIndex)
{
	if(!m_lstKey)
		return NULL;
	if(nIndex >= m_lstKey->size() || nIndex < 0)
		return NULL;

	return m_lstKey->at(nIndex);
}

BOOL CMSearch::LoadKey()
{
	if(m_lstKey)
		m_lstKey->clear();
	else
		m_lstKey = new CMList<char*>;
	
    BOOL bRet = FALSE;
	CMString sPath = CMGlobal::TheOne().GetUserDir() + L"recentkey.xml";
	TiXmlDocument *pDoc = new TiXmlDocument(sPath);
	if(!pDoc)
		return bRet;
	if(!CMFile::FileExist(sPath))
	{
		pDoc->Parse("<?xml version=\"1.0\" encoding=\"utf-8\" ?><recentkey/>",NULL,TIXML_ENCODING_UTF8);
		bRet = !pDoc->Error();
		if(bRet)
			pDoc->SaveFile();
	}
	else
	{
		pDoc->LoadFile(TIXML_ENCODING_UTF8);
		if(!pDoc->Error())
		{
			TiXmlElement *pRoot = pDoc->RootElement();
			if(pRoot)
			{
				TiXmlElement* pItem = pRoot->FirstChildElement("item");
				while(pItem)
				{
                    char* k = new char[strlen(pItem->Attribute("key"))+1];
                    utf8ncpy(k, pItem->Attribute("key"), strlen(pItem->Attribute("key")));
					m_lstKey->push_back(k);
					pItem = pItem->NextSiblingElement("item");
				}	
				bRet = TRUE;
			}
		}
	}

	SAFEDELETE(pDoc);
    return bRet;
}

void CMSearch::SaveKey(const char* skey)
{
	if(!m_lstKey) 
		m_lstKey = new CMList<char*>;

	//创建一个XML的文档对象。
	TiXmlDocument *pDoc = new TiXmlDocument(CMGlobal::TheOne().GetUserDir() + L"recentkey.xml");
	if(pDoc && pDoc->LoadFile(TIXML_ENCODING_UTF8))
	{
		//获得根元素。
		TiXmlElement *pRootElement = pDoc->RootElement();		
		
		if(pRootElement)
		{
			TiXmlElement* pFirstItem = pRootElement->FirstChildElement("item");
			TiXmlElement* pItem = pFirstItem;			
			while(pItem)
			{
				if(strcmp(pItem->Attribute("key"), skey) == 0)
				{
					if(pItem != pFirstItem)
					{
						pRootElement->InsertBeforeChild(pFirstItem, *pItem);
						pRootElement->RemoveChild(pItem);
						for(int i = 0;i < m_lstKey->size();i++)
						{
							if(strcmp(m_lstKey->at(i), skey) == 0)
							{
								m_lstKey->removeAt(i);
								break;
							}
						}
						char* k = new char[strlen(skey)+1];
                        utf8ncpy(k, skey, strlen(skey));
						m_lstKey->push_front(k);
						pDoc->SaveFile();
					}
					SAFEDELETE(pDoc);
					return;
				}
				pItem = pItem->NextSiblingElement("item");
			}

			TiXmlElement* pAddItem = new TiXmlElement("item");
			if(pAddItem)
			{
				pAddItem->SetAttribute("key", skey);

				pItem = pRootElement->FirstChildElement("item");
				if (pItem) {
					pRootElement->InsertBeforeChild(pItem, *pAddItem);
					SAFEDELETE(pAddItem);
				}
				else
					pRootElement->LinkEndChild(pAddItem);
				pDoc->SaveFile();
				if(pDoc->SaveFile())
				{
					char* k = new char[strlen(skey)+1];
                    utf8ncpy(k,skey,strlen(skey));
					m_lstKey->push_front(k);
				}
			}
		}
	}
	SAFEDELETE(pDoc);
}
