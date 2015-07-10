// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <eikdef.h>
#include <coemain.h>
#include "cmvideoplay.h"
#include "mplayerinterface.h"
#include "cmfile.h"
#include "cmscreen.h"

CMVideoPlay::CMVideoPlay(IMVideoNotify& rVideoNotify, IMReferenceClock& rRefClock, CMStreamBuffer* pStreamBuffer)
: CActive(CActive::EPriorityStandard)
, m_VideoNotify(rVideoNotify)
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
, m_nRotation(0)
, m_pDSA(NULL)
, m_pGc(NULL)
, m_pVirtualScreen(NULL)
, m_cTimer(this)
, m_nRenderLeft(0)
, m_nRenderTop(0)
, m_nRenderWidth(0)
, m_nRenderHeight(0)
{
    CActiveScheduler::Add( this );
}

CMVideoPlay::~CMVideoPlay()
{
}

void CMVideoPlay::Play()
{
    m_cTimer.Set(20);
    m_cTimer.Start();
//    if(!IsActive())
//    {
//        SetActive();
//        TRequestStatus* status;
//        status = &iStatus;
//        User::RequestComplete( status, KErrNone );
//    }
    m_bPlaying = TRUE;
}

void CMVideoPlay::Pause()
{
    m_bPlaying = FALSE;
}

void CMVideoPlay::Stop()
{
    m_bPlaying = FALSE;
    m_cTimer.Stop();
    //Cancel();
    //数据位置归零
    m_pVideoPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
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
    if(m_pVirtualScreen)
    {
        m_pVirtualScreen->Reset();
        delete m_pVirtualScreen;
        m_pVirtualScreen = NULL;
    }
    if(m_pDSA)
    {
        m_pDSA->Cancel();
        delete m_pDSA;
        m_pDSA = NULL;
        m_pGc = NULL;
    }
}

void CMVideoPlay::Restart(RDirectScreenAccess::TTerminationReasons aReason)
{
    if(m_pDSA && m_pVirtualScreen)
    {
        TRAPD( err, m_pDSA->StartL() ); // You may panic here, if you want
        if( KErrNone == err )
        {
            m_pVirtualScreen->Resize(TSize(m_nRenderWidth, m_nRenderHeight));
            m_nYpitch = m_nRenderWidth*2;
            m_pVirtualScreen->LockHeap( ETrue );
            memset(m_pVirtualScreen->DataAddress(), 0, m_nRenderWidth*m_nRenderHeight*2);
            m_pVirtualScreen->UnlockHeap( ETrue );
            m_pGc = m_pDSA->Gc();
            RRegion* region = m_pDSA->DrawingRegion();
            m_pGc->SetClippingRegion( region );
            
            m_bPlaying = TRUE;
        }
    }
}

void CMVideoPlay::AbortNow(RDirectScreenAccess::TTerminationReasons aReason)
{
    if(m_pDSA)
        m_pDSA->Cancel();
    m_bPlaying = FALSE;
}


void CMVideoPlay::RunL()
{
}

void CMVideoPlay::OnTimer(CMTimer &cTimer)
{
    User::ResetInactivityTime();
    INT32 time = m_nTimeStamp - m_RefClock.GetRefTime();
 //   CM_LOGP(CM_LOGL_DEBUG, "CMVideoPlay::RunL time = %d, m_nTimeStamp = %d, m_bPlaying = %d", time, m_nTimeStamp, m_bPlaying);
    if(time > 50)
    {
        //太快了，需要等一等
        //User::After(50000);目前播放在主线程执行，是不能等的        
    }
    else if(this->GetNextFrame())
    {
        if(m_bPlaying && time > -200)
        {
            m_pVirtualScreen->LockHeap( ETrue );            
            if(m_pOverlay && m_pOverlay->IsInitialized()){
				m_pOverlay->SetSrcPitch(m_OutData.size[0]);
				m_pOverlay->Convert(m_OutData.data, (UINT8*)m_pVirtualScreen->DataAddress());
				//m_Overlay.Process(m_OutData, (UINT8*)m_pVirtualScreen->DataAddress());
            }
            m_pVirtualScreen->UnlockHeap( ETrue );
            m_pGc->BitBlt( TPoint(m_nRenderLeft, m_nRenderTop), m_pVirtualScreen );
            m_pDSA->ScreenDevice()->Update();
            memset(&m_OutData, 0, sizeof(MDecData));
        }
        //else如果太慢了，就少画一次
    }
    m_cTimer.Start();
//    if(!IsActive())
//    {
//        SetActive();
//        TRequestStatus* status;
//        status = &iStatus;
//        User::RequestComplete( status, KErrNone );
//    }
}

void CMVideoPlay::DoCancel()
{
    m_bPlaying = FALSE;
}

BOOL CMVideoPlay::InitDirectDraw()
{
    if(m_pVirtualScreen == NULL)
    {
        m_pVirtualScreen = new (ELeave) CFbsBitmap;
        if(m_pVirtualScreen)
        {
            User::LeaveIfError( m_pVirtualScreen->Create( TSize(m_nRenderWidth, m_nRenderHeight), EColor64K ) );
            m_pVirtualScreen->LockHeap( ETrue );
            memset(m_pVirtualScreen->DataAddress(), 0, m_nRenderWidth*m_nRenderHeight*2);
            m_pVirtualScreen->UnlockHeap( ETrue );
        }
        else
            return FALSE;
    }

    if(m_pDSA == NULL)
    {
        m_pDSA = CDirectScreenAccess::NewL(CCoeEnv::Static()->WsSession(), *CCoeEnv::Static()->ScreenDevice(), 
        		CMScreen::GetDefaultScreen()->GetWindow(), *this);
    }
    if(m_pDSA)
    {
        m_pDSA->StartL();
        m_pGc = m_pDSA->Gc();
        RRegion* region = m_pDSA->DrawingRegion();
        m_pGc->SetClippingRegion(region);
        
        m_nBpp = 16;
        m_nXpitch = 2;
        m_nYpitch = m_nRenderWidth*2;
        TSize size = CCoeEnv::Static()->ScreenDevice()->SizeInPixels();
        m_framebufwidth = size.iWidth;
        m_framebufheight = size.iHeight;
    }
    else
        return FALSE;

    return TRUE;
}
