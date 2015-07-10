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
BOOL CMAudioPlay::GetNextPCM(UINT8* pBuffer, UINT32& nLen)
{
    BOOL ret = FALSE;
    if(m_pAudioPacket == NULL)
	{
        m_pAudioPacket = m_pStreamBuffer->GetNextPacket(MEDIATYPE_AUDIO);

		//if(m_pAudioPacket)
		//{
		//	m_nTimeStamp = m_pAudioPacket->timestamp;
		//}
	}
    if(m_pAudioPacket)
    {
        INT32 nConsumed = 0;
        UINT32 nOutLen = 0;
		INT32 nFrames = 0;
        for(;nOutLen < nLen && m_nCurPosInPacket < m_pAudioPacket->len;)
        {
            m_OutData.data[0] = pBuffer + nOutLen;
            m_OutData.size[0] = nLen - nOutLen;
            nConsumed = m_pCodec->Decode((INT8*)m_pAudioPacket->data + m_nCurPosInPacket, 
                                            m_pAudioPacket->len - m_nCurPosInPacket, m_OutData);
            //m_OutData.size[0] = 320;
            if(nConsumed > 0)
            {
                m_nCurPosInPacket += nConsumed;
                nOutLen += m_OutData.size[0];
				if(m_OutData.size[0] > 0)
					nFrames++;
            }
            else
                break;
        }
		INT32 nConsumedTime = (m_nAudioType == CODECID_AMRNB ? 20 : (1024000/m_nSampleRate))*nFrames;
        m_nNotifyPos += nConsumedTime;
        m_nTimeStamp += nConsumedTime;
		m_nDeltaTimeStamp += 1024000%m_nSampleRate;
        nLen = nOutLen;
        if(m_nCurPosInPacket >= m_pAudioPacket->len)
        {
            m_pAudioPacket = NULL;
            m_nCurPosInPacket = 0;
			if(m_nAudioType == CODECID_AAC)
			{
				m_nTimeStamp += m_nDeltaTimeStamp/m_nSampleRate;
				m_nDeltaTimeStamp = 0;
			}
        }
        if(m_nNotifyPos >= 1000)
        {
            m_AudioNotify.ProgressChange(m_pStreamBuffer->GetPercent(), m_nNotifyPos);
            m_nNotifyPos = 0;
        }
		if(nLen > 0)
			ret = TRUE;
    }
    else
    {
#if defined(PLAT_WINCE)
        ::PostMessage(CMScreen::GetDefaultScreen()->GetSafeHwnd(), WM_USER+200, 0, (LPARAM)this);//TODO:
#else
     m_AudioNotify.NeedMoreData();
#endif
    }
    return ret;
}
