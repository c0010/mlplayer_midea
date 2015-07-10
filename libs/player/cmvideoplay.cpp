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
//#include "cmrect.h"
#include "mplayerinterface.h"
//#include "cmglobal.h"
//#include "cmscreen.h"
#include "cmfile.h"
#include "cczoomrotation16.h"
#include "cczoomrotation24.h"
#include "cczoomrotation32.h"

INT32 CMVideoPlay::GetRotation()
{
    return m_nRotation;;
}

void CMVideoPlay::SetRotation(INT32 nRotation)
{
    AbortNow(RDirectScreenAccess::ETerminateRotation);
    m_nRotation = nRotation;
	UpdateOverlay();
    Restart(RDirectScreenAccess::ETerminateRotation);
}

void CMVideoPlay::SetDrawSize(INT32 nWidth, INT32 nHeight)
{
    AbortNow(RDirectScreenAccess::ETerminateRotation);
#if !(defined(PLAT_AND) || defined(PLAT_IOS)) //android ios 不缩放
    m_nRenderWidth = nWidth;
	m_nRenderHeight = nHeight;
#endif
#if !(defined(PLAT_WINCE) || defined(PLAT_AND) || defined(PLAT_IOS))
	m_nYpitch = nWidth*2;
#endif
	UpdateOverlay();
    Restart(RDirectScreenAccess::ETerminateRotation);
}

void CMVideoPlay::SetDrawPoint(INT32 nLeft, INT32 nTop)
{
	m_nRenderLeft = nLeft;
	m_nRenderTop = nTop;
}
BOOL CMVideoPlay::Open(INT32 nCodec, INT32 nWidth, INT32 nHeight)
{
    BOOL ret = FALSE;

    CM_LOGP(CM_LOGL_DEBUG, "CMVideoPlay::Open nWidth = %d, nHeight = %d", nWidth, nHeight);
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

    if(ret)
	{
		m_nWidth = nWidth;
		m_nHeight = nHeight;
        ret = InitDirectDraw();
        //触发重新缓存加载
        SetRotation(0);
	}
	
    if(ret)
	{
		SAFEDELETE(m_pOverlay);
		switch(m_nBpp)
		{
		case 16:
			m_pOverlay = ColorConvert16::NewL();
			break;
		case 24:
			m_pOverlay = ColorConvert24::NewL();
			break;
		case 32:
			m_pOverlay = ColorConvert32::NewL();
			break;
		default:
			break;
		}
		ret = !!m_pOverlay;
	}
	if(ret)
	{
		UpdateOverlay();
	}

    return ret;
}

void CMVideoPlay::UpdateOverlay()
{
	if(m_pOverlay)
	{
		INT32 n = (m_nRotation == 90 ? CCROTATE_CNTRCLKWISE : (m_nRotation == 270 ? CCROTATE_CLKWISE : m_nRotation));
		if(m_pOverlay->Init(m_nWidth, m_nHeight, m_nWidth, 
			m_nRenderWidth, m_nRenderHeight, m_nYpitch/(m_nBpp>>3), n))
		{
			m_pOverlay->SetMemHeight(m_nHeight);
			m_pOverlay->SetMode(1);
		}
	}
}
BOOL CMVideoPlay::GetNextFrame()
{
    BOOL ret = FALSE;
    if(m_pVideoPacket == NULL)
	{
        m_pVideoPacket = m_pStreamBuffer->GetNextPacket(MEDIATYPE_VIDEO);

		if(m_pVideoPacket)
		{
			m_nTimeStamp += m_pVideoPacket->timestamp;
		}
	}
    if(m_pVideoPacket)
    {
        INT32 nConsumed = m_pCodec->Decode((INT8*)m_pVideoPacket->data + m_nCurPosInPacket, 
                                      m_pVideoPacket->len - m_nCurPosInPacket, m_OutData);
        if(nConsumed > 0)
        {
            m_nCurPosInPacket += nConsumed;
//            if(f ==NULL)
//            {
//                f = new CMFile;
//                f->Open("/sdcard/ld.yuv", CMFile::OPEN_RW_ALWAYS);
//            }
//            UINT32 i;
//            for(i=0; i<m_nHeight; i++)
//                f->Write((CHAR*)m_OutData.data[0] + i * m_OutData.size[0], m_nWidth);
//            for(i=0; i<m_nHeight/2; i++)
//                f->Write((CHAR*)m_OutData.data[1] + i * m_OutData.size[1], m_nWidth/2);
//            for(i=0; i<m_nHeight/2; i++)
//                f->Write((CHAR*)m_OutData.data[2] + i * m_OutData.size[2], m_nWidth/2);

            ret = TRUE;
        }
        else if(nConsumed == 0)
        {
            m_nCurPosInPacket += m_pVideoPacket->len - m_nCurPosInPacket;
        }

        if(m_nCurPosInPacket >= m_pVideoPacket->len)
        {
            m_pVideoPacket = NULL;
            m_nCurPosInPacket = 0;
        }
        //m_VideoNotify.ProgressChange(m_pStreamBuffer->GetPercent(), m_nTimeStamp);        
    }
    else
    {
        //m_VideoNotify.NeedMoreData();
    }
    return ret;
}

