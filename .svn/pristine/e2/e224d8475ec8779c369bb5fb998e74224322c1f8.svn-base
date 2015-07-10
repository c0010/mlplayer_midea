// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmaudioplay.h
//  Description: The class offers a simple interface to open, play and obtain information from sampled audio data.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMAUDIOPLAY_H_HEADER_INCLUDED_B5AE8DF6
#define CMAUDIOPLAY_H_HEADER_INCLUDED_B5AE8DF6
#include "mplayerinterface.h"
#include "cmcodec.h"

#if defined(PLAT_SYMBIAN)
#include <MdaAudioOutputStream.h>
#include <mda\common\audio.h>
#elif defined(PLAT_WINCE)
#include "cmscreen.h"
#elif defined(PLAT_IOS)

#import <AudioToolbox/AudioToolbox.h>


//#include "CAStreamBasicDescription.h"
//#include "CAXException.h"

#define kNumberBuffers 2
#elif defined(PLAT_AND)
#include <jni.h>
struct filedsA {
	jclass    audioClass;
	jmethodID construction_id;
	jmethodID getState_method;
	jmethodID play_method;
	jmethodID pause_method;
	jmethodID stop_method;
	jmethodID release_method;
	jmethodID setStereoVolume_method;
	jmethodID write_method;
	jmethodID getMinBufferSize_method;
	jmethodID getMaxVolume_method;
	jmethodID getMinVolume_method;
	jmethodID getPlayState_method;
};
#endif

#ifdef WINCE_OTHER
	#define PCM_BUFFER_LEN 8000
#else
	#define PCM_BUFFER_LEN 1600
#endif

class CMAudioPlay : public IMReferenceClock
#if defined(PLAT_SYMBIAN)
, MMdaAudioOutputStreamCallback
#endif
{
  public:
    CMAudioPlay(IMAudioNotify& rAudioNotify, CMStreamBuffer* pStreamBuffer);

    virtual ~CMAudioPlay();

    // Description: Init codec and open audio device.
    // param nCodec: Codec type.
    // param nChannels: channels of audio.
    // param nSamplesPerSec: Sample rate of audio.
    // param nBitsPerSample: Bits of audio.
    // Return: TRUE if successful; otherwise FALSE.
    BOOL Open(INT32 nCodec, INT32 nChannels = 1, INT32 nSamplesPerSec = 8000, INT32 nBitsPerSample = 16);

    void Play();

    void Pause();

    void Stop();

    void Close();

    INT32 MaxVolume();

    INT32 GetVolume();

    void SetVolume(INT32 nVolume);

    //from IMReferenceClock
    virtual INT32 GetRefTime(){return m_nTimeStamp-300;};
	
	void PacketClear(){ m_pAudioPacket = NULL;};

  private:
    // Description: Get playing PCM data.
    // param pBuffer: [out]Pointer to the buffer to receive the copied data.
    // param nLen: The size in bytes of the buffer pointed to by the pBuffer parameter.
    // Return: TRUE if has data; otherwise FALSE.
    BOOL GetNextPCM(UINT8* pBuffer, UINT32& nLen);

    Med_Packet* m_pAudioPacket;

    UINT32 m_nCurPosInPacket;

    UINT8* m_pPCMData[2];

    UINT32 m_nPCMDataSize;

	UINT32 m_nFrameSize;

    IMAudioNotify& m_AudioNotify;

    CMStreamBuffer* m_pStreamBuffer;

    INT32   m_nAState;

    INT32   m_nTimeStamp;

    INT32   m_nNotifyPos;
    
    UINT32  m_nVolume;

    IMCodec* m_pCodec;

    MDecData m_OutData;

    BOOL m_bPlaying;

	UINT32 m_nAudioType;

	UINT32 m_nSampleRate;

	UINT32 m_nDeltaTimeStamp;
#if defined(PLAT_SYMBIAN)
    CMdaAudioOutputStream* m_pOutputStream;
    TMdaAudioDataSettings  m_StreamSettings;
    BOOL m_bOpened;
    TPtrC8 m_PCMDataPtr[2];
    //The following function inherit from MMdaAudioOutputStreamCallback, see also MMdaAudioOutputStreamCallback
    virtual void MaoscOpenComplete(TInt aError);
    virtual void MaoscBufferCopied(TInt aError, const TDesC8& aBuffer);
    virtual void MaoscPlayComplete(TInt aError);
#elif defined(PLAT_WINCE)
    HWAVEOUT        m_hWaveOut;
    WAVEFORMATEX    m_WaveFormatEx;
	WAVEHDR         m_WaveOutHdr[2];

    static void CALLBACK WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD wParam, DWORD lParam);
public:
    // Description: This function is called when a audio message occurs..
    // param message: Specifies the Windows message to be processed.
    // param wParam: Provides additional information used in processing the message. The parameter value depends on the message.
    // param lParam: Provides additional information used in processing the message. The parameter value depends on the message.
    // Return: none.
    void OnAudioMessage(UINT message, WPARAM wParam, LPARAM lParam);
#elif defined(PLAT_IOS)
	AudioQueueRef					mQueue;
	AudioQueueBufferRef				mBuffers[kNumberBuffers];
	//CAStreamBasicDescription		mDataFormat;
	Boolean							mIsInitialized;
	UInt32							mIsRunning;
	Boolean							mIsDone;
	UInt32							mBufferSize;
	
	static void isRunningProc(		void *              inUserData,
							  AudioQueueRef           inAQ,
							  AudioQueuePropertyID    inID);
	
	static void AQBufferCallback(	void *					inUserData,
								 AudioQueueRef			inAQ,
								 AudioQueueBufferRef		inCompleteAQBuffer);
#elif defined(PLAT_AND)
public:
	static filedsA   field;

private:
	float AudioMaxVol();
	float AudioMinVol();
	BOOL  RunL(JNIEnv*env);

	jobject     mAudioTrack;
	jobject	    mjarray;
    JNIEnv*     m_AudioEnv;
	CMMutex     m_mutex;
	BOOL        m_bExitThread;
	BOOL        m_bRunning;
	static VOID* PlayThreadProc(VOID* pData);
#endif
};



#endif /* CMAUDIOPLAY_H_HEADER_INCLUDED_B5AE8DF6 */
