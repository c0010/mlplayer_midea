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
	accessLock = [[NSRecursiveLock alloc] init];
	//m_Semaphore = dispatch_semaphore_create(0);
}

CMMutex::~CMMutex()
{
	NSRecursiveLock*lock = (NSRecursiveLock*)accessLock;
	[lock release];
	//dispatch_release(m_Semaphore);
}

void CMMutex::Lock()
{
	NSRecursiveLock*lock = (NSRecursiveLock*)accessLock;
	[lock lock];
	//dispatch_semaphore_wait(m_Semaphore, DISPATCH_TIME_FOREVER);
}

void CMMutex::UnLock()
{
	NSRecursiveLock*lock = (NSRecursiveLock*)accessLock;
	[lock unlock];
	//dispatch_semaphore_signal(m_Semaphore);
}
