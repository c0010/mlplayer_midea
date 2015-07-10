//
//  cmshake.cpp
//  MLPlayer
//
//  Created by wmgwd on 13-6-20.
//  Copyright (c) 2013定 w. All rights reserved.
//

#include "stdafx.h"
#include "cmshake.h"
#include "cmsession.h"
#include "utf8ncpy.h"
#include "cmcommon.h"

CMShake::CMShake(IMUpdateDataListener* pListener)
:CMContenthandler()
{
    memset(&sCategoryID, 0, 64);
    SetListener(pListener, NULL);
}

CMShake::~CMShake()
{
    
}

BOOL CMShake::Request()
{
    if (IsRunning())
    {
        return FALSE;
    }
    sprintf(m_tablename,"");
    SetPaging(FALSE);
    
    char sParam[200];
    sParam[0] = '\0';
    return CMContenthandler::Request(SERVICE_GETSHAKECOURSE,sParam);
}

void CMShake::DoClear()
{
    m_mutex.Lock();
    if(m_lstHeadItem)
    {
        
        for(int i = 0; i < m_lstHeadItem->size(); i++)
        {
            TBrowserItem* ptr = m_lstHeadItem->at(i);
            SAFEDELETE(ptr);
        }
        
        m_lstHeadItem->clear();
    }
	m_mutex.UnLock();
    
	m_mutex.Lock();
    if(m_lstItem)
    {
        for(int i = 0; i < m_lstItem->size(); i++)
        {
            TBrowserItem* ptr = m_lstItem->at(i);
            SAFEDELETE(ptr);
        }
        
        m_lstItem->clear();
    }
    m_mutex.UnLock();

}


BOOL CMShake::DoCreate(sqlite3 *db)
{
    return TRUE;
}



BOOL CMShake::DoGetCacheItems(sqlite3 *db)
{
    return TRUE;
}


void CMShake::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
//    if(nCmdID == SERVICE_GETSHAKECOURSE)
//    {
        CMContenthandler::OnSessionCmd(nCmdID, nCode, pDoc);
//    }
}