// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器实现类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmtimer_mob.h"
#include "cmtimer.h"

CMTimer_Imp::CMTimer_Imp(CMTimer* pTimer) :
    m_pTimer(pTimer),
    m_nID(0)
{
    m_pTimer = pTimer;
}

CMTimer_Imp::~CMTimer_Imp()
{
    KillTimer();
    m_pTimer = NULL;
}

void CMTimer_Imp::SetTimer(UINT32 nInterval)
{
    KillTimer();
    m_nID = ::timeSetEvent(nInterval, 0, TIMECALL, (DWORD)this, TIME_ONESHOT);
}

void CMTimer_Imp::KillTimer()
{
    if (m_nID != 0)
    {
        ::timeKillEvent(m_nID);
        m_nID = 0;
    }
}

void CMTimer_Imp::TIMECALL(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    CMTimer_Imp* pImp = (CMTimer_Imp*)dwUser;
    ASSERT(pImp != NULL && pImp->m_pTimer != NULL && pImp->m_pTimer->m_pNotify != NULL);
    pImp->m_pTimer->m_pNotify->OnTimer(*pImp->m_pTimer);
}

