// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器实现类
//  Author:Tim 
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99
#define CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99
#include "cmlist.h"
#include <cmmutex.h>


class IMNotifyTimer;
class CMTimer;
/*struct _Andtimer
{
	CMTimer* pTimer;
	int cyctimes;
	int curtimes;
};*/
class CMTimer_Imp
{
public:
    CMTimer_Imp(CMTimer* pTimer);
    ~CMTimer_Imp();

    void SetTimer(UINT32 nInterval);

    void KillTimer();
    
private:
	
    CMTimer* m_pTimer;
	BOOL     m_bRuning;
	BOOL     m_bExitThread;
	int      m_nWaitingInterval;
	pthread_t m_Pthread_t;
	static VOID* TimeProc(VOID* pData);
};
#endif /* CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99 */
