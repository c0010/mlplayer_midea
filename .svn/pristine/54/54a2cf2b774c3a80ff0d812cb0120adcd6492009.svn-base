// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmmutex.h"

CMMutex::CMMutex()
{
    InitializeCriticalSection(&m_CritSec);
}

CMMutex::~CMMutex()
{
    DeleteCriticalSection(&m_CritSec);
}

void CMMutex::Lock()
{
    EnterCriticalSection(&m_CritSec);
}

void CMMutex::UnLock()
{
    LeaveCriticalSection(&m_CritSec);
}

