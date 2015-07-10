// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmtimer.h"
#if defined(PLAT_SYMBIAN)
	#include "cmtimer_sym.h"
#elif defined(PLAT_WINCE)
	#include "cmtimer_mob.h"
#elif defined(PLAT_IOS)
	#include "cmtimer_iph.h"
#elif defined(PLAT_AND)
	#include "cmtimer_and.h"
#else

#endif

CMTimer::CMTimer()
{
}

CMTimer::CMTimer(IMNotifyTimer* pNotify)
{
    m_nID = 0;
    m_nInterval = 0;
    m_pNotify = pNotify;

    ASSERT(m_pNotify != NULL);

    m_pImp = new CMTimer_Imp(this);
}

CMTimer::~CMTimer()
{
    if (m_pImp)
        delete m_pImp;
}

void CMTimer::Set(UINT32  nInterval)
{
    m_nInterval = nInterval;
}

void CMTimer::Start()
{
    m_pImp->SetTimer(m_nInterval);
}

void CMTimer::Stop()
{
    m_pImp->KillTimer();
}

void CMTimer::SetTimerID(UINT32 nID)
{
    m_nID = nID;
}

UINT32 CMTimer::GetTimerID()
{
    return m_nID;
}

