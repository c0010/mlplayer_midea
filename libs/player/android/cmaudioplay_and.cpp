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
#include <stddef.h>
#include <pthread.h>
#include <sys/select.h>
#include "android/env.h"




// ÔÝĘąĐ´ËŔ
#define AudioFormat_CHANNEL_CONFIGURATION_MONO  	2  
#define AudioFormat_CHANNEL_CONFIGURATION_STEREO    3
#define AudioFormat_ENCODING_PCM_16BIT              2
#define AudioFormat_ENCODING_PCM_8BIT				3
#define AudioManager_STREAM_MUSIC                   3
#define AudioTrack_MODE_STREAM						1
#define AudioTrack_STATE_INITIALIZED				1
#define AudioTrack_ERROR_INVALID_OPERATION			-3
#define AudioTrack_ERROR_BAD_VALUE					-2
#define PLAYSTATE_PAUSED                            2
#define PLAYSTATE_PLAYING                           3
#define PLAYSTATE_STOPPED                           1


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
, m_nPCMDataSize(0)
, m_nFrameSize(320)
, m_nAudioType(CODECID_NONE)
, m_nSampleRate(8000)
, m_nDeltaTimeStamp(0)
, m_bExitThread(TRUE)
, mAudioTrack(NULL)
, mjarray(NULL)
{
	m_pPCMData[0] = NULL;
	m_pPCMData[1] = NULL;
}

CMAudioPlay::~CMAudioPlay()
{
    if (m_pPCMData[0])
    {
        delete[]  m_pPCMData[0];
        m_pPCMData[0] = NULL;
    }

    if (m_pPCMData[1])
    {
        delete[]  m_pPCMData[1];
        m_pPCMData[1] = NULL;
    }
}

BOOL CMAudioPlay::Open(INT32 nCodec, INT32 nChannels/* = 1*/, INT32 nSamplesPerSec/* = 8000*/, INT32 nBitsPerSample/* = 16*/)
{
	//CM_ERRP("CMAudioPlay::Open......nCodec:%d nChannels:%d nSamplesPerSec:%d nBitsPerSample:%d", nCodec,nChannels, nSamplesPerSec, nBitsPerSample);
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return FALSE;
	}

	m_nSampleRate = nSamplesPerSec;
	INT32 nPCMDataSize = 0;
	if(nCodec == 0x02)
	{
		m_nAudioType = CODECID_AMRNB;
		m_nFrameSize = 320;
		nPCMDataSize = PCM_BUFFER_LEN;
	}
	else if(nCodec == 0x03)
	{
		m_nAudioType = CODECID_AAC;
		m_nFrameSize = 1024*nBitsPerSample/8*nChannels;
		nPCMDataSize = 4*1024*nBitsPerSample/8*nChannels;
	}
	else
		return  FALSE;
	
	int channelconfig;
	int audioformat;
	
	if(nChannels == 1)
		channelconfig = AudioFormat_CHANNEL_CONFIGURATION_MONO;
	else if(nChannels == 2)
		channelconfig = AudioFormat_CHANNEL_CONFIGURATION_STEREO;
	else
		return FALSE;
	
	if(nBitsPerSample == 16)
		audioformat = AudioFormat_ENCODING_PCM_16BIT;
	else if(nBitsPerSample == 8)
		audioformat = AudioFormat_ENCODING_PCM_8BIT;
	else
		return FALSE;
	
	Close();

	int nAudioBufferSize = env->CallStaticIntMethod(CMAudioPlay::field.audioClass,CMAudioPlay::field.getMinBufferSize_method,nSamplesPerSec, channelconfig, audioformat);


	if(nAudioBufferSize > 0)
		nAudioBufferSize = nAudioBufferSize > nPCMDataSize ?  nAudioBufferSize : nPCMDataSize;
	else
		return FALSE;

	CM_LOGP(CM_LOGL_DEBUG, "CMAudioPlay buffer size %d", nAudioBufferSize);

	jobject aobj = env->NewObject(CMAudioPlay::field.audioClass, CMAudioPlay::field.construction_id,AudioManager_STREAM_MUSIC, nSamplesPerSec, channelconfig, audioformat, nAudioBufferSize, AudioTrack_MODE_STREAM);

	if(aobj)
	{
    		mAudioTrack = env->NewGlobalRef(aobj);
    		env->DeleteLocalRef(aobj);
	}
	else
	{
		CM_ERR("new AudioTrack failed");
		return FALSE;
	}
	int ngetState = env->CallIntMethod(mAudioTrack,CMAudioPlay::field.getState_method);

	if(ngetState != AudioTrack_STATE_INITIALIZED)
			return FALSE;
	SetVolume(MaxVolume()); 		

	if(m_pCodec == NULL)
	{
		memset(&m_OutData, 0, sizeof(MDecData));
			m_pCodec = CMCodecFactory::GetInstance()->Create(nCodec);
		if(m_pCodec)
		    m_pCodec->Start();
		else
			return FALSE;
	}
	/*if(nPCMDataSize != m_nPCMDataSize)
    {
        delete[]  m_pPCMData[0];
        m_pPCMData[0] = NULL;
    }
	if(!m_pPCMData[0])
		m_pPCMData[0] = new UINT8[nPCMDataSize];*/
	m_nPCMDataSize = nPCMDataSize;
	
	if(mjarray == NULL)
	{
		jbyteArray jarray = env->NewByteArray(m_nPCMDataSize);
		if(jarray)
		{
	    	mjarray = env->NewGlobalRef(jarray);
	    	env->DeleteLocalRef(jarray);
	    }
	    else
	    {
			CM_ERR("new mjarray failed");
			return FALSE;
		}
	}
	return TRUE;
}

void CMAudioPlay::Play()
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return ;
	}

	env->CallVoidMethod(mAudioTrack,CMAudioPlay::field.play_method);
	m_bPlaying = TRUE;
    if(m_bExitThread)
    {
		pthread_t pid;
		if(	pthread_create(&pid, NULL, PlayThreadProc, this) != 0)
			return;
    }
}

void CMAudioPlay::Pause()
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return ;
	}

    m_bPlaying = FALSE;
	env->CallVoidMethod(mAudioTrack,CMAudioPlay::field.pause_method);
}

void CMAudioPlay::Stop()
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return ;
	}

    m_bPlaying = false;
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

	env->CallVoidMethod(mAudioTrack,CMAudioPlay::field.stop_method);
	
	m_pAudioPacket = NULL;
	m_nCurPosInPacket = 0;
	m_nTimeStamp = 0;
	m_nNotifyPos = 0;

}

void CMAudioPlay::Close()
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return ;
	}

	m_mutex.Lock();
	if(mAudioTrack)
	{
		env->CallVoidMethod(mAudioTrack,CMAudioPlay::field.release_method);
		env->DeleteGlobalRef(mAudioTrack);
		mAudioTrack = NULL;
	}
	if(mjarray)
	{
		env->DeleteGlobalRef(mjarray);
		mjarray = NULL;	
	}

    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
    }
	m_mutex.UnLock();

}
float CMAudioPlay::AudioMaxVol()
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return 0.0;
	}

	return env->CallStaticFloatMethod(CMAudioPlay::field.audioClass,CMAudioPlay::field.getMaxVolume_method);

}
float CMAudioPlay::AudioMinVol()
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return 0.0;
	}

	return env->CallStaticFloatMethod(CMAudioPlay::field.audioClass,CMAudioPlay::field.getMinVolume_method);
}
INT32 CMAudioPlay::MaxVolume()
{
	return (int) ((AudioMaxVol() - AudioMinVol()) * 10);
}

INT32 CMAudioPlay::GetVolume()
{
	return m_nVolume;
}

void CMAudioPlay::SetVolume(INT32 nVolume)
{
	JNIEnv*  env = NULL;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("get env failed");
		return ;
	}

	m_nVolume = nVolume;

	env->CallIntMethod (mAudioTrack,CMAudioPlay::field.setStereoVolume_method,AudioMaxVol() + m_nVolume/10, AudioMinVol() + m_nVolume/10);

}
BOOL CMAudioPlay::RunL(JNIEnv*env)
{
	if (m_bPlaying) {
		int size = 0;
		jbyte* pcmdata = env->GetByteArrayElements((jbyteArray)mjarray, NULL);
		UINT32 nLen = m_nPCMDataSize;
		BOOL ret = GetNextPCM((UINT8*)pcmdata, nLen);
		env->ReleaseByteArrayElements((jbyteArray)mjarray, pcmdata, 0);
		if (ret) {
			if(mAudioTrack)
			   size = env->CallIntMethod(mAudioTrack, CMAudioPlay::field.write_method, mjarray, 0, nLen);
			if(size == AudioTrack_ERROR_INVALID_OPERATION || size == AudioTrack_ERROR_BAD_VALUE)
			{
				CM_ERR("CMAudioPlay::RunL()...................Fail!!!");
				return FALSE;
			}
			return TRUE;
		}
	}

	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = 50 * 1000; // 5 ms
	select(0, NULL, NULL, NULL, &delay);

	return TRUE;
}

VOID * CMAudioPlay::PlayThreadProc(VOID* pData)
{
 	CMAudioPlay* pAudioPlay = (CMAudioPlay*)pData;
	pAudioPlay->m_bExitThread = FALSE;
	pAudioPlay->m_bRunning = TRUE;
	JNIEnv*env;
	GetJavaVM()->AttachCurrentThread((JNIEnv**)&env, NULL);
    if(pAudioPlay)
    {
        pAudioPlay->m_mutex.Lock();
        while(TRUE)
        {
            if(pAudioPlay->m_bExitThread)
                break;
            if(!pAudioPlay->RunL(env))
				break;
        }
		pAudioPlay->m_mutex.UnLock();
    }
    GetJavaVM()->DetachCurrentThread();
	pAudioPlay->m_bRunning = FALSE;
    return ((VOID *)0);
}


