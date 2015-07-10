// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器实现类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmtimer_sym.h"
#include "cmtimer.h"

CMTimer_Imp::CMTimer_Imp(CMTimer* pTimer):CTimer(EPriorityStandard)
{
    m_pTimer = pTimer;
    CActiveScheduler::Add(this);
    CTimer::ConstructL();
}

void CMTimer_Imp::SetTimer(UINT32 nInterval)
{
    if (IsActive())
    {
        Cancel();
    }
    
    //After参数微秒
    After(TTimeIntervalMicroSeconds32(1000 * nInterval));
}

void CMTimer_Imp::KillTimer()
{
    Cancel();
}

void CMTimer_Imp::RunL()
{
    ASSERT(m_pTimer != NULL && m_pTimer->m_pNotify != NULL);
    m_pTimer->m_pNotify->OnTimer(*m_pTimer);
}
