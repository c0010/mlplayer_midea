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
    m_Mutex.CreateLocal();
}

CMMutex::~CMMutex()
{
    m_Mutex.Close();
}

void CMMutex::Lock()
{
    m_Mutex.Wait();
}

void CMMutex::UnLock()
{
    m_Mutex.Signal();
}

