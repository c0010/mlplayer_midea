// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器实现类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmtimer_iph.h"
#include "cmtimer.h"


@interface CMTimerObject:NSObject
{
	CMTimer* m_pTimer;
	IMNotifyTimer* m_pNotify;
    @public
	NSTimer* myTimer;
}


+ (id)InitWithCTimer:(CMTimer*)pTimer notify:(IMNotifyTimer*)pNotify;

- (void)myMethod:(NSTimer*)timer;

@end

@implementation CMTimerObject

+ (id)InitWithCTimer:(CMTimer*)pTimer notify:(IMNotifyTimer*)pNotify;
{
	CMTimerObject* inst = [[CMTimerObject alloc]init];
	inst->m_pTimer = pTimer;
	inst->m_pNotify = pNotify;
	inst->myTimer = nil;

	return inst;
}
-(void)myMethod:(NSTimer*)timer {
    
	if(m_pNotify)
		m_pNotify->OnTimer(*m_pTimer);
}

-(void)dealloc
{
    [myTimer invalidate];
    [self->myTimer release];
    self->myTimer=nil;
    [super dealloc];
}

@end

CMTimer_Imp::CMTimer_Imp(CMTimer* pTimer) :
    m_pTimer(pTimer)
{
    m_pTimer = pTimer;
	m_myTimer = [CMTimerObject InitWithCTimer:m_pTimer notify:m_pTimer->m_pNotify];
}

CMTimer_Imp::~CMTimer_Imp()
{
    KillTimer();
    m_pTimer = NULL;
	CMTimerObject* myTimerObject = (CMTimerObject*)m_myTimer;
	[myTimerObject release];
}

void CMTimer_Imp::SetTimer(UINT32 nInterval)
{
    KillTimer();
	CMTimerObject* myTimerObject = (CMTimerObject*)m_myTimer;
	myTimerObject->myTimer =[[NSTimer scheduledTimerWithTimeInterval:nInterval/1000.0
					target:myTimerObject 
					selector:@selector(myMethod:)
					userInfo:nil
                    repeats:NO] retain];
    
}

void CMTimer_Imp::KillTimer()
{
	CMTimerObject* myTimerObject = (CMTimerObject*)m_myTimer;
    if (myTimerObject->myTimer != NULL)
    {		
		[myTimerObject->myTimer invalidate];
        [myTimerObject->myTimer release];
        myTimerObject->myTimer = NULL;
    }
}
