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
	pthread_mutexattr_t   mta;
	pthread_mutexattr_init(&mta);
	/* or PTHREAD_MUTEX_RECURSIVE_NP */
	pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mtx, &mta);
}

CMMutex::~CMMutex()
{
    pthread_mutex_destroy( &mtx );
}

void CMMutex::Lock()
{
    pthread_mutex_lock( &mtx );
}

void CMMutex::UnLock()
{
    pthread_mutex_unlock( &mtx );
}
