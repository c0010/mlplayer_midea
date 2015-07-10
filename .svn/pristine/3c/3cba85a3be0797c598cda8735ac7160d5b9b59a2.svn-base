// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmaudioplay.h"

 void CMAudioPlay::AQBufferCallback(void *					inUserData,
								AudioQueueRef			inAQ,
								AudioQueueBufferRef		inCompleteAQBuffer) 
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];
    
	CMAudioPlay *THIS = (CMAudioPlay *)inUserData;

	UINT8* pBuffer = (UINT8*)inCompleteAQBuffer->mAudioData;
	UINT32 nLen = THIS->mBufferSize;
	if(THIS->GetNextPCM(pBuffer, nLen))
	{
		//NSLog(@"GetNextPCM TRUE");
		inCompleteAQBuffer->mAudioDataByteSize = nLen;		
	}
	else
	{
		//NSLog(@"GetNextPCM FALSE");
		memset(pBuffer, 0, 320);
		inCompleteAQBuffer->mAudioDataByteSize = 320;
	}
	OSStatus result = AudioQueueEnqueueBuffer(inAQ, inCompleteAQBuffer, 0, NULL);
    
    [pool drain];
	//NSLog(@"CMAudioPlay::AudioQueueEnqueueBuffer return %d", result);
}

void CMAudioPlay::isRunningProc (  void *              inUserData,
							  AudioQueueRef           inAQ,
							  AudioQueuePropertyID    inID)
{
    
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

	CMAudioPlay *THIS = (CMAudioPlay *)inUserData;
	UInt32 size = sizeof(THIS->mIsRunning);
	OSStatus result = AudioQueueGetProperty (inAQ, kAudioQueueProperty_IsRunning, &THIS->mIsRunning, &size);
	
	if ((result == noErr) && (!THIS->mIsRunning))
	{
		NSLog(@"playbackQueueStopped");
		//[[NSNotificationCenter defaultCenter] postNotificationName: @"playbackQueueStopped" object: nil];
	}
    
    [pool drain];
}

CMAudioPlay::CMAudioPlay(IMAudioNotify& rAudioNotify, CMStreamBuffer* pStreamBuffer)
: m_pAudioPacket(NULL)
, m_nCurPosInPacket(0)
, m_AudioNotify(rAudioNotify)
, m_pStreamBuffer(pStreamBuffer)
, m_nAState(EUnKnown)
, m_nTimeStamp(0)
, m_nNotifyPos(0)
, m_nVolume(0)
, m_pCodec(NULL)
, m_bPlaying(FALSE)
, mQueue(0)
, mIsRunning(false)
, mIsInitialized(false)
, mIsDone(false)
, mBufferSize(8000)
, m_nAudioType(CODECID_NONE)
, m_nSampleRate(8000)
, m_nDeltaTimeStamp(0)
{
}

CMAudioPlay::~CMAudioPlay()
{
}

BOOL CMAudioPlay::Open(INT32 nCodec, INT32 nChannels/* = 1*/, INT32 nSamplesPerSec/* = 8000*/, INT32 nBitsPerSample/* = 16*/)
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

    
    BOOL ret = FALSE;

    //Todo: 打开Codec
    if(m_pCodec == NULL)
    {
        memset(&m_OutData, 0, sizeof(MDecData));
        m_pCodec = CMCodecFactory::GetInstance()->Create(nCodec);
        if(m_pCodec)
        {
            m_pCodec->Start();
            ret = TRUE;
        }
    }
    m_nSampleRate = nSamplesPerSec;
    if(nCodec == 0x02)
	{
		m_nAudioType = CODECID_AMRNB;
	}
	else if(nCodec == 0x03)
	{
		m_nAudioType = CODECID_AAC;
	}
	else
		return  FALSE;
    //打开AudioQueue
	if(mQueue == NULL)
	{
		AudioStreamBasicDescription format; // 声音格式设置，这些设置要和采集时的配置一致
		memset(&format, 0, sizeof(format));

		format.mSampleRate = nSamplesPerSec; // 采样率 (立体声 = 8000)
		format.mFormatID = kAudioFormatLinearPCM; // PCM 格式
		format.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
		format.mChannelsPerFrame = nChannels;  // 1:单声道；2:立体声
		format.mBitsPerChannel = nBitsPerSample; // 语音每采样点占用位数
		format.mBytesPerFrame = (format.mBitsPerChannel / 8) * format.mChannelsPerFrame;
		format.mFramesPerPacket = 1;
		format.mBytesPerPacket = format.mBytesPerFrame * format.mFramesPerPacket;

		OSStatus result = AudioQueueNewOutput(&format,
							 CMAudioPlay::AQBufferCallback,
							 this,  // opaque reference to whatever you like
							 CFRunLoopGetMain(),
							 kCFRunLoopCommonModes,
							 0,
							 &mQueue);
  

        
		if(!result)
			result = AudioQueueAddPropertyListener(mQueue, kAudioQueueProperty_IsRunning, isRunningProc, this);

		mBufferSize = nChannels*nSamplesPerSec*nBitsPerSample / 8 / 10;  // around 1/2 sec of 8kHz 16 bit mono PCM
		for (int i = 0; i < kNumberBuffers && !result; ++i)
		{
			result = AudioQueueAllocateBufferWithPacketDescriptions(mQueue, mBufferSize, 0, &mBuffers[i]);
			memset(mBuffers[i]->mAudioData, 0, 320);
			mBuffers[i]->mAudioDataByteSize = 320;
			AudioQueueEnqueueBuffer(mQueue, mBuffers[i], 0, NULL);
		}

		if(!result)
		{
			SetVolume(m_nVolume);
			ret = TRUE;
			mIsInitialized = true;
		}
		else 
			ret = FALSE;
	}
	NSLog(@"CMAudioPlay::Open return %d", ret);
    [pool drain];
    return ret;
}

void CMAudioPlay::Play()
{
    m_bPlaying = TRUE;
    if(mQueue)
    {
		OSStatus result = AudioQueueStart(mQueue, NULL);
        
		NSLog(@"CMAudioPlay::AudioQueueStart return %d", result);
    }
}

void CMAudioPlay::Pause()
{
	NSLog(@"CMAudioPlay::Pause");
    m_bPlaying = FALSE;
    if(mQueue)
	{
        OSStatus result = AudioQueuePause(mQueue);
		NSLog(@"CMAudioPlay::AudioQueuePause return %d", result);
	}
}

void CMAudioPlay::Stop()
{
	NSLog(@"CMAudioPlay::Stop");
    m_bPlaying = FALSE;
    if(mQueue)
    {
        OSStatus result = AudioQueueStop(mQueue, false);
		NSLog(@"CMAudioPlay::AudioQueueStop return %d", result);
    }
    //数据位置归零
    m_pAudioPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
    m_nNotifyPos = 0;
}

void CMAudioPlay::Close()
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

	NSLog(@"CMAudioPlay::Close");
    if(mQueue)
    {
		if (mQueue)
		{
			OSStatus result = AudioQueueDispose(mQueue, false);
			NSLog(@"CMAudioPlay::AudioQueueDispose return %d", result);
			mQueue = NULL;
		}
		mIsInitialized = false;
    }
    //Todo: 关闭Codec
    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
    }
    
    [pool drain];
}

INT32 CMAudioPlay::MaxVolume()
{
    return 1000;
}

INT32 CMAudioPlay::GetVolume()
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];

	AudioQueueParameterValue nVol = 1.0;

	if(mQueue && !AudioQueueGetParameter(mQueue, kAudioQueueParam_Volume, &nVol))
	{
		m_nVolume = (UINT32)(nVol * 1000);
		NSLog(@"CMAudioPlay::GetVolume return %f(%d)", nVol, m_nVolume);
	}
    [pool drain];
    return m_nVolume;
}

void CMAudioPlay::SetVolume(INT32 nVolume)
{
    NSAutoreleasePool *pool=[[NSAutoreleasePool alloc]init];
    
    m_nVolume = nVolume;
	AudioQueueParameterValue nVol = nVolume/1000.0;
    if(mQueue)
	{
        OSStatus result = AudioQueueSetParameter(mQueue, kAudioQueueParam_Volume, nVol);
		NSLog(@"CMAudioPlay::SetVolume(%f) return %d", nVol, result);
	}
    
    [pool drain];
}
