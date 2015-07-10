// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015,
//  All rights reserved.
//
//  FileName:
//  Description:网络Http层接口序列类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmsessionsequence.h"
#include <stdio.h>

#include "cmsession.h"

CMSessionSequence* CMSessionSequence::m_pTHIS = NULL;

CMSessionSequence* CMSessionSequence::GetInstance()
{
    if (m_pTHIS == NULL)
        m_pTHIS = new CMSessionSequence();
    return m_pTHIS;
}

BOOL CMSessionSequence::Append(CMSession* pSession)
{
//    if (!pSession || pSession->m_sSequence.length() == 0) return FALSE;
    m_mutex.Lock();
    m_map[pSession->m_sSequence].push_back(pSession);
    if (m_map[pSession->m_sSequence].front() == pSession)
    {
        pSession->Command();
    }
    m_mutex.UnLock();
    return TRUE;
}

BOOL CMSessionSequence::Remove(CMSession* pSession)
{
//    if (!pSession || pSession->m_sSequence.length() == 0) return FALSE;
    
    map<string, list<CMSession*> >::iterator iter = m_map.find(pSession->m_sSequence);
    if (iter != m_map.end())
    {
        m_mutex.Lock();
        list<CMSession*>& lst = (*iter).second;
        bool found = false;
        for (list<CMSession*>::iterator it = lst.begin(); it != lst.end(); it++)
        {
            if (*it == pSession)
            {
                found = true;
                
                it = lst.erase(it);
                if (it !=lst.end() && it == lst.begin())
                {
                    pSession->Command();
                }
                    
                break;
            }
        }
        m_mutex.UnLock();
        if (found)
        {
            return TRUE;
        }
    } else {
        // do anythig if the key was not founded
    }
    
    return FALSE;
}

//void CMSessionSequence::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
//{
//
//}

