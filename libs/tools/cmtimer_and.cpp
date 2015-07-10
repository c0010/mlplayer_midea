// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器实现类
//  Author:Tim
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmtimer_and.h"
#include "cmtimer.h"
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <jni.h>
#include "android/env.h"



CMTimer_Imp::CMTimer_Imp(CMTimer* pTimer)
{
    m_pTimer = pTimer;
	m_bRuning = FALSE;
	m_bExitThread = TRUE;
	m_Pthread_t = 0;
}

CMTimer_Imp::~CMTimer_Imp()
{
    KillTimer();
    m_pTimer = NULL;
}

void CMTimer_Imp::SetTimer(UINT32 nInterval)
{
	m_nWaitingInterval = nInterval;
	m_bRuning = TRUE;
	if(m_bExitThread)
	{
		pthread_t pid;
		if(	pthread_create(&pid, NULL, TimeProc, this) != 0)
			return;		
	}
}
VOID * CMTimer_Imp::TimeProc(VOID* pData)
{
	  CMTimer_Imp *pTimer = (CMTimer_Imp*)pData;

	  struct timeval delay;
	  delay.tv_sec = 0;
	  delay.tv_usec = pTimer->m_nWaitingInterval * 1000;
	  select(0, NULL, NULL, NULL, &delay);	
	  
	  pTimer->m_bExitThread = FALSE;
	  pTimer->m_Pthread_t = pthread_self();
	  JNIEnv*env;
	  GetJavaVM()->AttachCurrentThread((JNIEnv**)&env, NULL);
	  if(pTimer)
	  {
		  	while(!pTimer->m_bExitThread)	 
	  		{
	  			if(pTimer->m_bRuning && pTimer->m_pTimer)
	  			{
	  				pTimer->m_bRuning = FALSE;
	  				pTimer->m_pTimer->m_pNotify->OnTimer(*pTimer->m_pTimer);
				}
				else
				{
					struct timeval delay;
					delay.tv_sec = 0;
					delay.tv_usec = pTimer->m_nWaitingInterval * 1000;
					select(0, NULL, NULL, NULL, &delay);				
				}
	  		}
	  }
	GetJavaVM()->DetachCurrentThread();
	pTimer->m_Pthread_t = 0;
}
void CMTimer_Imp::KillTimer()
{
	m_bExitThread = TRUE;
	if(m_Pthread_t != pthread_self())
	{
		int i = 0;
		while(m_Pthread_t != 0 && i++ < 20)
		{
			m_bExitThread = TRUE;
			struct timeval delay;
			delay.tv_sec = 0;
			delay.tv_usec = 50 * 1000;
			select(0, NULL, NULL, NULL, &delay);
		}
	}
}

