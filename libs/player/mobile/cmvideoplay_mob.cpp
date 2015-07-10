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

extern HWND GetSafeHwnd();

CMVideoPlay::CMVideoPlay(IMVideoNotify& rVideoNotify, IMReferenceClock& rRefClock, CMStreamBuffer* pStreamBuffer)
//: CActive(CActive::EPriorityStandard)
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
, m_nRotation(0)
, m_nDirectDrawMode(DIRECTDRAWMODE_GAPI)
, m_DirectDrawCreate(NULL)
, m_hDdraw(NULL)
, m_pdd(NULL)
, m_psurf(NULL)
, m_hThread(NULL)
, m_hExitEvent(NULL)
, m_nRenderLeft(0)
, m_nRenderTop(0)
, m_nRenderWidth(0)
, m_nRenderHeight(0)
{

}

CMVideoPlay::~CMVideoPlay()
{
}

void CMVideoPlay::Play()
{
    if(m_hExitEvent == NULL)
    {
        m_hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    if(m_hThread == NULL)
    {
        DWORD dwDummy;
        m_hThread = CreateThread(NULL, 0, PlayThreadProc, (LPVOID)this, 0, &dwDummy);
    }
    m_bPlaying = TRUE;
}

void CMVideoPlay::Pause()
{
    m_bPlaying = FALSE;
}

void CMVideoPlay::Stop()
{
    m_bPlaying = FALSE;
    if(m_hThread)
    {
        SetEvent(m_hExitEvent);
	    if(WaitForSingleObject(m_hThread, 2000) != WAIT_OBJECT_0)
		    ::TerminateThread(m_hThread, 1);
	    ::CloseHandle(m_hExitEvent);
	    m_hThread = NULL;
	    m_hExitEvent = NULL;
    }
    //数据位置归零
    m_pVideoPacket = NULL;
    m_nCurPosInPacket = 0;
    m_nTimeStamp = 0;
}

void CMVideoPlay::Close()
{
	if(m_nDirectDrawMode == DIRECTDRAWMODE_GAPI)
		::GXCloseDisplay();
	else if(m_nDirectDrawMode == DIRECTDRAWMODE_DDRAW)
	{
		if(m_psurf)
		{
			m_psurf->Release();
			m_psurf = NULL;
		}
		if(m_pdd)
		{
			m_pdd->Release();
			m_pdd = NULL;
		}
		m_DirectDrawCreate = NULL;
		if(m_hDdraw)
		{
			FreeLibrary(m_hDdraw);
			m_hDdraw = NULL;
		}
	}    
	m_nDirectDrawMode = DIRECTDRAWMODE_NONE;
    if(m_pCodec)
    {
        m_pCodec->Close();
        delete m_pCodec;
        m_pCodec = NULL;
    }
}

void CMVideoPlay::Restart(RDirectScreenAccess::TTerminationReasons aReason)
{
    m_bPlaying = TRUE;
    //if(m_psurf)
    //    m_psurf->Unlock(0);
}

void CMVideoPlay::AbortNow(RDirectScreenAccess::TTerminationReasons aReason)
{
    //if(m_psurf)
    //    m_psurf->Lock(0, &m_ddsd, DDLOCK_WAITNOTBUSY, 0);
    m_bPlaying = FALSE;
}

void CMVideoPlay::RunL()
{
    INT32 time = m_nTimeStamp - m_RefClock.GetRefTime();
    if(time > 50)
    {
        //太快了，需要等一等
        Sleep(50);
    }
    else if(this->GetNextFrame())
    {
        if(m_bPlaying && time > -200)
        {         
            //CMRect rc(0,0,0,0);
            //m_Overlay.GetDrawRect(rc);
            UINT8* pFrameBuf = (UINT8*)BeginDraw();
			if(pFrameBuf && m_pOverlay && m_pOverlay->IsInitialized()){
				m_pOverlay->SetSrcPitch(m_OutData.size[0]);
				m_pOverlay->Convert(m_OutData.data, pFrameBuf + m_nRenderTop * m_nYpitch + m_nRenderLeft * m_nXpitch);
				//m_Overlay.Process(m_OutData, pFrameBuf + rc.top*m_Overlay.m_nYpitch + rc.left*m_Overlay.m_nXpitch);
			}
            EndDraw();
            memset(&m_OutData, 0, sizeof(MDecData));
        }
        //else如果太慢了，就少画一次
    }
    //if(this->GetNextFrame())
    //{
    //    INT32 time = 0;
    //    while((time = m_nTimeStamp - m_RefClock.GetRefTime()) > 200)
    //    {
    //        Sleep(50);
    //        if(::WaitForSingleObject(m_hExitEvent,0) == WAIT_OBJECT_0)
    //            break;
    //    }

    //    if(time > -200)
    //    {
    //        m_ddsd.dwSize = sizeof(m_ddsd);
	   //     if(DD_OK != m_psurf->Lock(0, &m_ddsd, DDLOCK_WAITNOTBUSY, 0))
		  //      return;
    //        m_Overlay.Process(m_OutData, m_ddsd.lpSurface);
    //        m_psurf->Unlock(0);
    //        memset(&m_OutData, 0, sizeof(MDecData));
    //    }
    //}
}

DWORD CMVideoPlay::PlayThreadProc(LPVOID pData)
{
    CMVideoPlay* pVideoPlay = (CMVideoPlay*)pData;
    if(pVideoPlay)
    {
        while(TRUE)
        {
            if(::WaitForSingleObject(pVideoPlay->m_hExitEvent,0) == WAIT_OBJECT_0)
                break;
            if(pVideoPlay)
                pVideoPlay->RunL();
        }
    }
    return 0;
}

BOOL CMVideoPlay::InitDirectDraw()
{
	if(::GXOpenDisplay(GetSafeHwnd(), GX_FULLSCREEN) == 0)
    {
        return FALSE;   // 创建失败
    }
    // 获取显示属性
    GXDisplayProperties gxdp = ::GXGetDisplayProperties();
    if(!(gxdp.ffFormat & kfDirect565 || gxdp.ffFormat & kfDirect888))
        return FALSE;
	m_nBpp = gxdp.cBPP;
    m_nXpitch = gxdp.cbxPitch;
    m_nYpitch = gxdp.cbyPitch;
    m_framebufwidth = gxdp.cxWidth;
    m_framebufheight = gxdp.cyHeight;
	if(::GXIsDisplayDRAMBuffer())
	{
		::GXCloseDisplay();
	}
	else
	{
		m_nDirectDrawMode = DIRECTDRAWMODE_GAPI;
		return TRUE;
	}
////////////////////////////////////////////
    if(m_hDdraw == NULL)
    {
        m_hDdraw = LoadLibrary(L"ddraw.dll");
        if(m_hDdraw == NULL)
            return FALSE;
    }
    if(m_DirectDrawCreate == NULL)
    {
        m_DirectDrawCreate = (DIRECTDRAWCREATE)GetProcAddress(m_hDdraw, L"DirectDrawCreate");
        if(m_DirectDrawCreate == NULL)
            return FALSE;
    }
    if(m_pdd == NULL)
    {
        LONG hr;

	    hr = m_DirectDrawCreate(0, (IUnknown **)&m_pdd, 0);
	    if(hr != DD_OK)
	    {
		    return FALSE;
	    }

	    hr = m_pdd->SetCooperativeLevel(GetSafeHwnd(), DDSCL_NORMAL);
	    if(hr != DD_OK)
	    {
		    m_pdd->Release();
		    m_pdd = NULL;
		    return FALSE;
	    }

	    memset((void *)&m_ddsd, 0, sizeof(m_ddsd));
	    m_ddsd.dwSize = sizeof(m_ddsd);
	    m_ddsd.dwFlags = DDSD_CAPS;
	    m_ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;	//no back buffering, only use the visible display area

	    //create surface (entire screen)
	    hr = m_pdd->CreateSurface(&m_ddsd, &m_psurf, NULL);
	    if(hr != DD_OK )
	    {
		    m_pdd->Release();
		    m_pdd = NULL;
		    return FALSE;
	    }

	    //get parameters with locking
	    memset((void *)&m_ddsd, 0, sizeof(m_ddsd));
	    m_ddsd.dwSize = sizeof(m_ddsd);
	    hr = m_psurf->Lock(0, &m_ddsd, DDLOCK_WAITNOTBUSY, 0);
	    if(hr != DD_OK)
	    {
		    m_psurf->Release();
		    m_psurf = NULL;
		    m_pdd->Release();
		    m_pdd = NULL;
		    return FALSE;
	    }

	    m_nBpp = m_ddsd.ddpfPixelFormat.dwRGBBitCount;
	    m_nXpitch = m_ddsd.lXPitch;
	    m_nYpitch = m_ddsd.lPitch;
	    m_framebufwidth = m_ddsd.dwWidth;
	    m_framebufheight = m_ddsd.dwHeight;

        //m_rcRender.left=(m_framebufwidth-m_Overlay.m_nWidth)/2;
        //m_rcRender.top=(m_framebufheight-m_Overlay.m_nHeight)/2;
        //m_rcRender.right=m_rcRender.left+m_Overlay.m_nWidth;
        //m_rcRender.bottom=m_rcRender.top+m_Overlay.m_nHeight;

	    //finally unlock surface
	    m_psurf->Unlock(0);
    }
	m_nDirectDrawMode = DIRECTDRAWMODE_DDRAW;
	return TRUE;
}

void* CMVideoPlay::BeginDraw()
{
	if(m_nDirectDrawMode == DIRECTDRAWMODE_GAPI)
		return ::GXBeginDraw();
	else if(m_nDirectDrawMode == DIRECTDRAWMODE_DDRAW)
	{
		m_ddsd.dwSize = sizeof(m_ddsd);
		if(DD_OK != m_psurf->Lock(0, &m_ddsd, DDLOCK_WRITEONLY | DDLOCK_DISCARD | DDLOCK_WAITNOTBUSY, 0))
			return NULL;
		else
			return m_ddsd.lpSurface;
	}
	else
		return NULL;
}

void CMVideoPlay::EndDraw()
{
	if(m_nDirectDrawMode == DIRECTDRAWMODE_GAPI)
		::GXEndDraw();
	else if(m_nDirectDrawMode == DIRECTDRAWMODE_DDRAW)
		m_psurf->Unlock(0);
}

//void CMVideoPlay::UpdateRect()
//{
//	if(m_pCodec && ::GXIsDisplayDRAMBuffer())
//    {
//		//CMRect rc = CMGlobal::TheOne().GetDefaultScreen()->GetScreenRect();        
//		CMRect rcDraw(0,0,0,0);
//		m_Overlay.GetDrawRect(rcDraw);
//
//		::GXSetViewport(rcDraw.top, m_framebufheight - rcDraw.top, 0, 0);
//		if(m_framebufwidth <= rcDraw.Width())
//		{			
//			rcDraw.left = 0;
//			rcDraw.right = m_framebufwidth;
//		}		
//		rcDraw.bottom = m_framebufheight < rcDraw.Height() ? m_framebufheight : rcDraw.Height();
//		rcDraw.top = 0;
//
//		m_Overlay.SetDrawRect(rcDraw);
//	}    
//}