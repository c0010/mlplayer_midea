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
, m_hWaveOut(NULL)
, m_nPCMDataSize(0)
, m_nFrameSize(320)
, m_nAudioType(CODECID_NONE)
, m_nSampleRate(8000)
, m_nDeltaTimeStamp(0)
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
    BOOL ret = FALSE;

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
		ret = FALSE;
    //打开waveout
    if(ret == TRUE && m_hWaveOut == NULL)
    {
        memset(&m_WaveFormatEx,0x00,sizeof(m_WaveFormatEx));
	    m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	    m_WaveFormatEx.nChannels = nChannels;
	    m_WaveFormatEx.wBitsPerSample = nBitsPerSample;
	    m_WaveFormatEx.cbSize = 0;
	    m_WaveFormatEx.nSamplesPerSec = nSamplesPerSec;
	    m_WaveFormatEx.nBlockAlign = (unsigned short)((m_WaveFormatEx.wBitsPerSample/8)*m_WaveFormatEx.nChannels);
	    m_WaveFormatEx.nAvgBytesPerSec = m_WaveFormatEx.nSamplesPerSec*m_WaveFormatEx.nBlockAlign;

        for(int i=0; i<2; i++)
	    {
            if (m_pPCMData[i] && nPCMDataSize != m_nPCMDataSize)
            {
                delete[]  m_pPCMData[i];
                m_pPCMData[i] = NULL;
            }
            
            if (!m_pPCMData[i])
                m_pPCMData[i] = new UINT8[nPCMDataSize];

	        memset(&m_WaveOutHdr[i], 0, sizeof(WAVEHDR));
            memset(m_pPCMData[i], 0, nPCMDataSize);
	        m_WaveOutHdr[i].lpData = (LPSTR)m_pPCMData[i];
	        m_WaveOutHdr[i].dwBufferLength = nPCMDataSize;
	    }
        m_nPCMDataSize = nPCMDataSize;
        for (UINT id = 0; id < waveOutGetNumDevs(); id++)
		{
			if (::waveOutOpen(&m_hWaveOut, id, &m_WaveFormatEx, (DWORD)WaveOutProc, (DWORD)this, CALLBACK_FUNCTION) == MMSYSERR_NOERROR)
            {
                for(int i = 0; i < 2;i++)
			    {
				    if(waveOutPrepareHeader(m_hWaveOut, &m_WaveOutHdr[i], sizeof(WAVEHDR)) == MMSYSERR_NOERROR)
				    {		
					    waveOutWrite(m_hWaveOut, &m_WaveOutHdr[i], sizeof(WAVEHDR));
				    }
			    }
                this->SetVolume(m_nVolume);
                ::waveOutPause(m_hWaveOut);
                ret = TRUE;
                break;
            }
		}
    }
    return ret;
}

void CMAudioPlay::Play()
{
    m_bPlaying = TRUE;
    if(m_hWaveOut)
    {
        ::waveOutRestart(m_hWaveOut);
        for(int i = 0; i < 2;i++)
	    {
		    if(waveOutPrepareHeader(m_hWaveOut, &m_WaveOutHdr[i], sizeof(WAVEHDR)) == MMSYSERR_NOERROR)
		    {		
			    waveOutWrite(m_hWaveOut, &m_WaveOutHdr[i], sizeof(WAVEHDR));
		    }
	    }
    }
}

void CMAudioPlay::Pause()
{
    m_bPlaying = FALSE;
    if(m_hWaveOut)
        ::waveOutPause(m_hWaveOut);
}

void CMAudioPlay::Stop()
{
    m_bPlaying = FALSE;
    if(m_hWaveOut)
    {
        ::waveOutReset(m_hWaveOut);
        for(int i = 0; i < 2;i++)
		{
			waveOutUnprepareHeader(m_hWaveOut, &m_WaveOutHdr[i], sizeof(WAVEHDR));
			memset(&m_WaveOutHdr[i], 0, sizeof(WAVEHDR));
            memset(m_pPCMData[i], 0, m_nPCMDataSize);
			m_WaveOutHdr[i].lpData = (LPSTR)m_pPCMData[i];
			m_WaveOutHdr[i].dwBufferLength = 0;
		}
        //m_bStopping = FALSE;
    }
    //数据位置归零
    m_pAudioPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
    m_nNotifyPos = 0;
}

void CMAudioPlay::Close()
{
    if(m_hWaveOut)
    {
        ::waveOutClose(m_hWaveOut);
        m_hWaveOut = NULL;
    }
    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
    }
}

INT32 CMAudioPlay::MaxVolume()
{
    return 0x0000FFFF;
}

INT32 CMAudioPlay::GetVolume()
{
	DWORD nVol = 0;

	if(m_hWaveOut && ::waveOutGetVolume(m_hWaveOut, &nVol) == MMSYSERR_NOERROR)
		m_nVolume = nVol;

    return LOWORD(m_nVolume);
}

void CMAudioPlay::SetVolume(INT32 nVolume)
{
    m_nVolume = nVolume;
    if(m_hWaveOut)
        ::waveOutSetVolume(m_hWaveOut, MAKELONG(nVolume, nVolume));
}

void CALLBACK CMAudioPlay::WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD wParam, DWORD lParam)
{
    CMAudioPlay *pAudioPlay = (CMAudioPlay *)dwInstance;
    if(pAudioPlay && pAudioPlay->m_bPlaying)
    {
        //::PostMessage(CMGlobal::TheOne().GetDefaultScreen()->GetSafeHwnd(),
        //                WM_USER+uMsg, wParam, dwInstance);
        pAudioPlay->OnAudioMessage(WM_USER+uMsg, wParam, 0);
    }
}
void OnAudioMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	CMAudioPlay *pAudioPlay = (CMAudioPlay *)lParam;
	if(pAudioPlay)
		pAudioPlay->OnAudioMessage(message, wParam, 0);
}
void CMAudioPlay::OnAudioMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch(message) 
    {
	case WM_USER+WOM_DONE:
		{
			LPWAVEHDR lpHdr = (LPWAVEHDR) wParam;
			if(lpHdr)
			{				
                waveOutUnprepareHeader(m_hWaveOut, lpHdr, sizeof(WAVEHDR));
                UINT8* pBuffer = (UINT8*)lpHdr->lpData;
                UINT32 nLen = m_nPCMDataSize;
                memset(lpHdr, 0, sizeof(WAVEHDR));
				if(GetNextPCM(pBuffer, nLen))
				{
					lpHdr->lpData = (LPSTR)pBuffer;
					lpHdr->dwBufferLength = nLen;
				}
				else
				{
                    memset(pBuffer, 0, m_nFrameSize);
					lpHdr->lpData = (LPSTR)pBuffer;
					lpHdr->dwBufferLength = m_nFrameSize;
				}
				waveOutPrepareHeader(m_hWaveOut, lpHdr, sizeof(WAVEHDR));
				waveOutWrite(m_hWaveOut, lpHdr, sizeof(WAVEHDR));
			}
		}
		break;
    case WM_USER+200:
        m_AudioNotify.NeedMoreData();
        break;
	default:
		break;
	}
}
