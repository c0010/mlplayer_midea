// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmvideoplay.h"
#include "mplayerinterface.h"
#include "cmfile.h"

//#import <NSThread.h>

@interface CMThreadObject:NSObject
{
	IMThread* m_pNotify;
	NSThread* myThread;
	BOOL      bExit;
	NSCondition*  cond;
	NSConditionLock* locker;
}
+ (id)initWithNotify:(IMThread*)pNotify;

- (void)Start;

- (void)Close;
@end

@implementation CMThreadObject

+ (void)AAA:(CMThreadObject*)it{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	[it->locker lock];
	while (!it->bExit) 
	{
		it->m_pNotify->RunL();
	}
	[it->locker unlockWithCondition:1];
	[pool release];
	[NSThread exit];
}

+ (id)initWithNotify:(IMThread*)pNotify;
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

	CMThreadObject* inst = [[CMThreadObject alloc]init];
	inst->m_pNotify = pNotify;
	inst->bExit = FALSE;
	inst->myThread = [[NSThread alloc]initWithTarget:[CMThreadObject class] selector:@selector(AAA:) object:inst];
	inst->locker = [[NSConditionLock alloc] initWithCondition:1];
//	[inst release];
    [pool drain];
	return inst;
}

- (void) dealloc {
	[locker release];
	[myThread release];
	
	[super dealloc];
}

- (void)Start {
	if (![myThread isExecuting])
		[myThread start];
}

//等0。5s
- (void)Close {
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

	bExit = TRUE;
	int nTry = 20;
	while (nTry-- > 0){
		if ([locker tryLockWhenCondition:1]){
			[locker unlockWithCondition:1];
			break;
		}
		else {
			if (nTry > 0)
				[NSThread sleepForTimeInterval:0.1];
			else {
				[myThread cancel];
				break;
			}

		}
	}
    [pool drain];
}

@end

CMVideoPlay::CMVideoPlay(IMVideoNotify& rVideoNotify, IMReferenceClock& rRefClock, CMStreamBuffer* pStreamBuffer)
: m_VideoNotify(rVideoNotify)
, m_RefClock(rRefClock)
, m_pStreamBuffer(pStreamBuffer)
, m_bPlaying(FALSE)
, m_pCodec(NULL)
, m_pVideoPacket(NULL)
, m_nCurPosInPacket(0)
, m_nTimeStamp(0)
, m_pOverlay(NULL)
, m_nWidth(320)
, m_nHeight(240)
, m_nBpp(16)
, m_nXpitch(2)
, m_nYpitch(480)
, m_nRenderWidth(320)
, m_nRenderHeight(240)
, m_nRotation(0)
//, m_cTimer(this)
, m_buffer(NULL)
{
	m_myThread = NULL;
	
}

CMVideoPlay::~CMVideoPlay()
{
	SAFEDELETE(m_pOverlay);
}

void CMVideoPlay::Play()
{
//    m_cTimer.Set(2000);
//    m_cTimer.Start();
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

	if (m_myThread == NULL)
	{
		m_myThread = [CMThreadObject initWithNotify:this];
	}
	
	CMThreadObject* pThread = (CMThreadObject*)m_myThread;
	[pThread Start];
	
    m_bPlaying = TRUE;
    
    [pool drain];
}

void CMVideoPlay::Pause()
{
    m_bPlaying = FALSE;
}

void CMVideoPlay::Stop()
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

    m_bPlaying = FALSE;
	CMThreadObject* pThread = (CMThreadObject*)m_myThread;
	[pThread Close];
	[pThread release];
	m_myThread = NULL;
//    m_cTimer.Stop();
    //Cancel();
    //数据位置归零
    m_pVideoPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
    
    [pool drain];
}

void CMVideoPlay::Close()
{
    
    //Todo: 关闭Codec
    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
        
    }
}

void CMVideoPlay::Restart(RDirectScreenAccess::TTerminationReasons aReason)
{
    
	if (m_buffer)
		SAFEDELETE(m_buffer);
	
	m_buffer = new UINT8[m_nRenderWidth * m_nRenderHeight * m_nXpitch];
	
    m_bPlaying = TRUE;
	m_mutex.UnLock();
}

void CMVideoPlay::AbortNow(RDirectScreenAccess::TTerminationReasons aReason)
{
	m_mutex.Lock();
    m_bPlaying = FALSE;
}


void CMVideoPlay::RunL()
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

   INT32 time = m_nTimeStamp - m_RefClock.GetRefTime();
	//   CM_LOGP(CM_LOGL_DEBUG, "CMVideoPlay::RunL time = %d, m_nTimeStamp = %d, m_bPlaying = %d", time, m_nTimeStamp, m_bPlaying);
    if(time > 50)
    {
        //太快了，需要等一等
        [NSThread sleepForTimeInterval:0.05];   
    }
    else 
	{
		if(this->GetNextFrame())
    {
        if(m_bPlaying && time > -200)
        {
            if(m_pOverlay && m_pOverlay->IsInitialized() && m_OutData.size[0] > 0){
				m_mutex.Lock();
				m_pOverlay->SetSrcPitch(m_OutData.size[0]);
				m_pOverlay->Convert(m_OutData.data, (UINT8*)m_buffer);
				m_VideoNotify.VideoDraw(m_buffer, m_nRenderWidth, m_nRenderHeight);
				m_mutex.UnLock();
            }
            
            memset(&m_OutData, 0, sizeof(MDecData));
        }
        //else如果太慢了，就少画一次
        }
	}
    [pool drain];
}

//void CMVideoPlay::OnTimer(CMTimer &cTimer)
//{
//    INT32 time = m_nTimeStamp - m_RefClock.GetRefTime();
// //   CM_LOGP(CM_LOGL_DEBUG, "CMVideoPlay::RunL time = %d, m_nTimeStamp = %d, m_bPlaying = %d", time, m_nTimeStamp, m_bPlaying);
//	NSLog(@"video 1 %d %d", time, m_bPlaying);
////    if(!m_bPlaying || time > 50)
////    {
////        //太快了，需要等一等
////        //[NSThread sleepForTimeInterval:50];
////    }
////    else 
//		if(m_bPlaying && this->GetNextFrame())
//    {
//		NSLog(@"video 2");
//        if(time > -200)
//        {
//			//有可能解码成功，但是没有输出，需要检查m_OutData的size
//            if(m_pOverlay && m_pOverlay->IsInitialized() && m_OutData.size[0] > 0){
//				m_pOverlay->SetSrcPitch(m_OutData.size[0]);
//				m_pOverlay->Convert(m_OutData.data, (UINT8*)m_buffer);
//				m_VideoNotify.VideoDraw(m_buffer, m_nWidth, m_nHeight);
//            }
//            
//            memset(&m_OutData, 0, sizeof(MDecData));
//        }
//        //else如果太慢了，就少画一次
//    }
//	else 
//		NSLog(@"video 3");
//    m_cTimer.Start();
//
//}

void CMVideoPlay::DoCancel()
{
    m_bPlaying = FALSE;
}

BOOL CMVideoPlay::InitDirectDraw()
{
	m_nBpp = 16;
	m_nXpitch = 2;
    m_nYpitch = m_nWidth * 2;
    m_nRenderWidth = m_nWidth;
    m_nRenderHeight = m_nHeight;
//	m_nYpitch = 640;
    return TRUE;
}
