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
, m_pOutputStream(NULL)
, m_bOpened(FALSE)
, m_bPlaying(FALSE)
, m_nFrameSize(320)
, m_nPCMDataSize(0)
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
    for(int i=0; i<2; i++)
    {
        if (m_pPCMData[i] && nPCMDataSize != m_nPCMDataSize)
        {
            delete[]  m_pPCMData[i];
            m_pPCMData[i] = NULL;
        }
        
        if (!m_pPCMData[i])
            m_pPCMData[i] = new UINT8[nPCMDataSize];

        memset(m_pPCMData[i], 0, nPCMDataSize);
    }
    m_nPCMDataSize = nPCMDataSize;
    //打开输出流
    if(ret == TRUE && m_pOutputStream == NULL)
    {
        m_pOutputStream = CMdaAudioOutputStream::NewL(*this);
        if(m_pOutputStream)
        {
            switch (nChannels)
            {
                case 1:
                    m_StreamSettings.iChannels = TMdaAudioDataSettings::EChannelsMono;
                    break;
                case 2:
                    m_StreamSettings.iChannels = TMdaAudioDataSettings::EChannelsStereo;
                    break;
                default:
                    CM_ERRP("Wrong channels %d", nChannels);
                    return FALSE;
            }
            
            switch (nSamplesPerSec)
            {
                case 8000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate8000Hz;
                    break;
                case 11025:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate11025Hz;
                    break;
                case 12000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate12000Hz;
                    break;
                case 16000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate16000Hz;
                    break;
                case 22050:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate22050Hz;
                    break;
                case 24000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate24000Hz;
                    break;
                case 32000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate32000Hz;
                    break;
                case 44100:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate44100Hz;
                    break;
                case 48000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate48000Hz;
                    break;
                case 96000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate96000Hz;
                    break;
                case 64000:
                    m_StreamSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate64000Hz;
                    break;
                default:
                    CM_ERRP("Wrong samplerate %d", nSamplesPerSec);
                    return FALSE;
            }
            m_pOutputStream->Open(&m_StreamSettings);
        }
        else
            ret = FALSE;
    }
    return ret;
}

void CMAudioPlay::Play()
{
    m_bPlaying = TRUE;
    if(m_bOpened && m_pOutputStream)
    {        
        memset(m_pPCMData[0], 0, m_nFrameSize);
        memset(m_pPCMData[1], 0, m_nFrameSize);
        m_PCMDataPtr[0].Set(m_pPCMData[0], m_nFrameSize);
        m_PCMDataPtr[1].Set(m_pPCMData[1], m_nFrameSize);
        m_pOutputStream->WriteL(m_PCMDataPtr[0]);
        m_pOutputStream->WriteL(m_PCMDataPtr[1]);
    }
}

void CMAudioPlay::Pause()
{
    m_bPlaying = FALSE;
}

void CMAudioPlay::Stop()
{
    m_bPlaying = FALSE;
    if(m_pOutputStream)
        m_pOutputStream->Stop();
    //数据位置归零
    m_pAudioPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
    m_nNotifyPos = 0;
}

void CMAudioPlay::Close()
{
    m_bOpened = FALSE;
    SAFEDELETE(m_pOutputStream);
    //Todo: 关闭Codec
    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
    }
}

INT32 CMAudioPlay::MaxVolume()
{
    INT32 nVol = 10;
    if(m_pOutputStream)
        nVol = m_pOutputStream->MaxVolume();
    return nVol;
}

INT32 CMAudioPlay::GetVolume()
{
    if(m_pOutputStream)
        m_nVolume = m_pOutputStream->Volume();
    return m_nVolume;
}

void CMAudioPlay::SetVolume(INT32 nVolume)
{
    m_nVolume = nVolume;
    if(m_pOutputStream)
    {
        m_pOutputStream->SetVolume(nVolume);
    }
}

void CMAudioPlay::MaoscOpenComplete(TInt aError)
{
    CM_LOGP(CM_LOGL_DEBUG, "CMAudioPlay::MaoscOpenComplete aError = %d", aError);
    if(aError == KErrNone)
    {
        TRAPD(err,m_pOutputStream->SetAudioPropertiesL(m_StreamSettings.iSampleRate, 
                m_StreamSettings.iChannels));
        this->SetVolume(m_nVolume);
        
        if(m_bOpened == FALSE)
        {
            m_bOpened = TRUE;
            if(m_bPlaying)
            {
                CM_LOG(CM_LOGL_DEBUG, "CMAudioPlay::MaoscOpenComplete Play");
                this->Play();
            }                
        }
    }
}

void CMAudioPlay::MaoscBufferCopied(TInt aError, const TDesC8& aBuffer)
{
    if(aError == KErrNone && m_pOutputStream)
    {
        UINT32 nNo = 0;
        UINT32 nLen = m_nPCMDataSize;
        const UINT8* pBuffer = aBuffer.Ptr();
        if(pBuffer == m_pPCMData[0])
            nNo = 0;
        else if(pBuffer == m_pPCMData[1])
            nNo = 1;
        else
            return;

        if(m_bPlaying)
        {
            if(this->GetNextPCM(m_pPCMData[nNo], nLen))
            {
                m_PCMDataPtr[nNo].Set(m_pPCMData[nNo], nLen);
                m_pOutputStream->WriteL(m_PCMDataPtr[nNo]);
                //CM_LOG(CM_LOGL_DEBUG, "CMAudioPlay::MaoscBufferCopied           Play WriteL");
            }
            else
            {
                //m_pOutputStream->WillResumePlay();
                memset(m_pPCMData[nNo], 0, m_nFrameSize);
                m_PCMDataPtr[nNo].Set(m_pPCMData[nNo], m_nFrameSize);
                m_pOutputStream->WriteL(m_PCMDataPtr[nNo]);
                //CM_LOG(CM_LOGL_DEBUG, "CMAudioPlay::MaoscBufferCopied           Play Mute");
            }
        }
    }
}

void CMAudioPlay::MaoscPlayComplete(TInt aError)
{
    CM_LOGP(CM_LOGL_DEBUG, "CMAudioPlay::MaoscPlayComplete aError = %d", aError);
    if(aError == KErrUnderflow)
    {
        if(m_bPlaying)
            this->Play();
    }
    else if(aError != KErrCancel && aError != KErrNone)
        this->Stop();
}
