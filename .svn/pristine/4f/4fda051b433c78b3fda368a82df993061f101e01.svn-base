// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmcustomerlist.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "cmsettings.h"
#include "utf8ncpy.h"

CMCustomerList::CMCustomerList(IMUpdateDataListener* pListener)
{
	m_pListener = pListener;
	m_UserData = NULL;
	m_pSession = NULL;
	m_lstCustomerListItem = new CMList<TCustomerListItem>();
}

CMCustomerList::~CMCustomerList()
{
	m_lstCustomerListItem->clear();
	if (m_pSession) {
		m_pSession->Cancel();
	}
	SAFEDELETE(m_lstCustomerListItem);
	SAFEDELETE(m_pSession);
}

void CMCustomerList::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

void CMCustomerList::GetList()
{
	m_lstCustomerListItem->clear();
	CMString sParam;
    if(!m_pSession)
		m_pSession = new CMSession(this);
    m_pSession->Command(SERVICE_GETCUSTOMERLIST, sParam); 
}

int CMCustomerList::GetItemCount()
{
	return m_lstCustomerListItem->size();
}

BOOL CMCustomerList::GetItem(int nIndex, TCustomerListItem& item)
{
	if(nIndex < 0 || nIndex >= m_lstCustomerListItem->size())
		return FALSE;
	item = m_lstCustomerListItem->at(nIndex);
	return TRUE;
}
void CMCustomerList::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
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
                if (nErr == 0)
                {
                    if (nCmdID  ==  SERVICE_GETCUSTOMERLIST)
                    {
                        //添加item到显示list
                        pItem = pItem->FirstChildElement();
						
                        //更新对象，
                        while (pItem)
                        {					
							TCustomerListItem listItem;
							memset(&listItem,0,sizeof(TCustomerListItem));
							const char* pstr = pItem->Attribute("id");
							if(pstr)
                                utf8ncpy(listItem.sID, pstr, 99);
							pstr = pItem->Attribute("name");
							if(pstr)
                                utf8ncpy(listItem.sName, pstr, 99);

							pstr = pItem->Attribute("server");
							if(pstr)
                                utf8ncpy(listItem.sServer, pstr, 99);
					
							if (SETTING.GetCustomer() == (CMString)listItem.sName) {
								listItem.bcheck = TRUE;
							}else{
								listItem.bcheck = FALSE;
							}
							
							m_lstCustomerListItem->push_back(listItem);
                            pItem = pItem->NextSiblingElement("item");
                        }
						if(m_lstCustomerListItem->size() > 0)
						{
							m_pListener->OnUpdateDataFinish(m_UserData,TResult::ESuccess);
						}
						else
						{
							m_pListener->OnUpdateDataFinish(m_UserData,TResult::ENothing);
							return ;
						}
						
                    }
                }
                else if (nErr == MERS_NOTRETURN)
                {
					m_pListener->OnUpdateDataFinish(m_UserData,TResult::ENothing);
                    CM_ERR("MERS_NOTRETURN");
                }
                else
					m_pListener->OnUpdateDataFinish(m_UserData,TResult::ENothing);
            }
        }
    }
    else
    {
		m_pListener->OnUpdateDataFinish(m_UserData,TResult::ENothing);
        CM_ERR("CMCustomerListUI OnSessionCmd not ok");
    }	
}

void CMCustomerList::SetServerUrl(char* sName, char* sUrl)
{
	if(sName != NULL)
		SETTING.SetCustomer(sName);
	if(sUrl != NULL)
	{
		SETTING.SetSelServer(FALSE);
		SETTING.SetServerUrl(sUrl);
		SETTING.Save();
		SETTING.SetSelServer(TRUE);
	}	
}

BOOL CMCustomerList::GetCustomerName(char* sName, int nBufLen)
{
	if(SETTING.GetCustomer() == NULL || SETTING.GetServerUrl()== NULL)
		return FALSE;
	else
	{
		//if(strlen(SETTING.GetCustomer()) >= nBufLen)
//			SETTING.m_sCustomer = SETTING.m_sCustomer.Left(nBufLen);
        
        utf8ncpy(sName, SETTING.GetCustomer(), 99);
		return TRUE;
	}
}
