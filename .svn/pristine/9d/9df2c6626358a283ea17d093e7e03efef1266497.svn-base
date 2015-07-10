// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <unistd.h>
#include <jni.h>
#include "cmvideoplay.h"
#include "mplayerinterface.h"
#include "cmmutex.h"
#include "android/env.h"


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
, m_nYpitch(640)
, m_nRenderLeft(0)
, m_nRenderTop(0)
, m_nRenderWidth(320)
, m_nRenderHeight(240)
, m_nRotation(0)
, m_bExitThread(TRUE)
, m_bRunning(FALSE)
, m_buffer(NULL)
{
	
}

CMVideoPlay::~CMVideoPlay()
{
	SAFEDELETE(m_pOverlay);

	if (m_buffer)
	{
		JNIEnv*  env ;
		if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
			return ;

		env->DeleteGlobalRef((jobject)m_buffer);
		m_buffer = NULL;
	}
}

void CMVideoPlay::Play()
{
    if(m_bExitThread)
    {
		pthread_t pid;
		if(	pthread_create(&pid, NULL, PlayThreadProc, this) != 0)
			return;
		m_bExitThread = FALSE;
    }

    m_bPlaying = TRUE;
}

void CMVideoPlay::Pause()
{
    m_bPlaying = FALSE;
}

void CMVideoPlay::Stop()
{
	m_bExitThread = TRUE;

	//waiting for 1 sec
	int times = 0;
	while(m_bRunning && times++ < 10)
	{
		struct timeval delay;
		delay.tv_sec = 0;
		delay.tv_usec = 100 * 1000;
		select(0, NULL, NULL, NULL, &delay);
	}

    m_bPlaying = FALSE;
    m_pVideoPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
}

void CMVideoPlay::Close()
{
    //Todo: ???Codec
    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
        
    }
}
VOID * CMVideoPlay::PlayThreadProc(VOID* pData)
{
    CMVideoPlay* pVideoPlay = (CMVideoPlay*)pData;
	pVideoPlay->m_bExitThread = FALSE;
	pVideoPlay->m_bRunning = TRUE;
	JNIEnv*env;
	int i = GetJavaVM()->AttachCurrentThread((JNIEnv**)&env, NULL);
    if(pVideoPlay)
    {
        while(TRUE)
        {
            if(pVideoPlay->m_bExitThread)
                break;
            pVideoPlay->RunL(env);
        }
    }
    GetJavaVM()->DetachCurrentThread();
    pVideoPlay->m_bRunning = FALSE;
    return ((VOID *)0);
}
void CMVideoPlay::Restart(RDirectScreenAccess::TTerminationReasons aReason)
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("CMVideoPlay::Restart GetEnv failed");
		m_mutex.UnLock();
		return ;
	}
	CM_LOGP(CM_LOGL_INFO, "CMVideoPlay::Restart %0x, want x %d y %d", m_buffer, m_nRenderWidth, m_nRenderHeight);
	if (m_buffer != NULL)
	{
		env->DeleteGlobalRef((jobject)m_buffer);
		m_buffer = NULL;
	}
	jintArray intarray = env->NewIntArray(m_nRenderWidth * m_nRenderHeight);
	if (intarray)
	{
		m_buffer = env->NewGlobalRef(intarray);
		env->DeleteLocalRef(intarray);
		m_bPlaying = TRUE;
	}
	else
		CM_ERR("CMVideoPlay::Restart New buffer return null");
    m_mutex.UnLock();
}

void CMVideoPlay::AbortNow(RDirectScreenAccess::TTerminationReasons aReason)
{
	m_mutex.Lock();
    m_bPlaying = FALSE;
}
void CMVideoPlay::RunL(void* para)
{
	JNIEnv*env = (JNIEnv*)para;

    INT32 time = m_nTimeStamp - m_RefClock.GetRefTime();
//	CM_LOGP(CM_LOGL_DEBUG, "CMVideoPlay::RunL time = %d, m_nTimeStamp = %d, m_bPlaying = %d", time, m_nTimeStamp, m_bPlaying);
    if(time > 50)
    {
        //sleep(50); 
        struct timeval delay;
		delay.tv_sec = 0;
		delay.tv_usec = 100* 1000; // 50 ms
		select(0, NULL, NULL, NULL, &delay);
    }
    else 
	{
		if(this->GetNextFrame())
    {
       if(m_bPlaying && time > -200)//
        {
            if(m_pOverlay && m_pOverlay->IsInitialized() && m_OutData.size[0] > 0){
				m_mutex.Lock();
				m_pOverlay->SetSrcPitch(m_OutData.size[0]);
				int* data = env->GetIntArrayElements((jintArray)m_buffer, NULL);
				m_pOverlay->Convert(m_OutData.data, (UINT8*)data);
				env->ReleaseIntArrayElements((jintArray)m_buffer, data, 0);
				m_VideoNotify.VideoDraw((UINT8*)m_buffer, m_nRenderWidth, m_nRenderHeight);
				m_mutex.UnLock();
            }
            
            memset(&m_OutData, 0, sizeof(MDecData));
        }
    }
	}
}

BOOL CMVideoPlay::InitDirectDraw()
{
    AbortNow(RDirectScreenAccess::ETerminateRotation);
	m_nBpp = 32;
	m_nXpitch = 4;
	m_nYpitch = m_nWidth*4;
	m_nRenderWidth = m_nWidth;
	m_nRenderHeight = m_nHeight;
	Restart(RDirectScreenAccess::ETerminateRotation);
    return TRUE;
}
