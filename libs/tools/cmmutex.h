// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmmutex.h
//  Description: Provides the functionality of a mutex.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMMUTEX_H_HEADER_INCLUDED_B5C11131
#define CMMUTEX_H_HEADER_INCLUDED_B5C11131

#if defined(PLAT_IOS)
#include <dispatch/dispatch.h>
#elif defined(PLAT_AND)
#include <pthread.h>
#endif

// 封装互斥量
class CMMutex
{
  public:
    CMMutex();

    ~CMMutex();

    void Lock();

    void UnLock();
private:
#if defined(PLAT_SYMBIAN)
    RMutex m_Mutex;
#elif defined(PLAT_WINCE)
    CRITICAL_SECTION m_CritSec;
#elif defined(PLAT_IOS)
	void* accessLock;
#elif defined(PLAT_AND)
	pthread_mutex_t mtx;
#endif
};



#endif /* CMMUTEX_H_HEADER_INCLUDED_B5C11131 */
