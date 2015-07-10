// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmvideoplay.h
//  Description: The class offers a simple interface to open, play and obtain information from sampled video data.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMVIDEOPLAY_H_HEADER_INCLUDED_B5AEFDC6
#define CMVIDEOPLAY_H_HEADER_INCLUDED_B5AEFDC6

#include "mplayerinterface.h"
#include "cmcodec.h"
//#include "cmrect.h"

#include "cczoomrotationbase.h"

#if defined(PLAT_SYMBIAN)
#include <w32std.h>
#include "cmtimer.h"
#else
class RDirectScreenAccess
{
public:
    enum TTerminationReasons
    {
	    /** The application has finished direct screen access. */
	    ETerminateCancel,
	    /** A window is about to come in front of a part of the area that is being used 
		 for direct screen access. */
	    ETerminateRegion,
	    /** The screen's color depth (as enumerated by TDisplayMode) is about to change. */
	    ETerminateScreenMode,
	    /** The current screen mode (the combination of screen rotation and screen size) 
		 is about to change. */
	    ETerminateRotation,
    };
};
class MDirectScreenAccess
{
public:
	virtual void Restart(RDirectScreenAccess::TTerminationReasons aReason) = 0;
	virtual void AbortNow(RDirectScreenAccess::TTerminationReasons aReason) = 0;
};
#if defined(PLAT_WINCE)
const UINT32 DIRECTDRAWMODE_NONE = 0;
const UINT32 DIRECTDRAWMODE_GAPI = 1;
const UINT32 DIRECTDRAWMODE_DDRAW = 2;

#include <ddraw.h>
typedef LONG (*DIRECTDRAWCREATE)(LPGUID, LPUNKNOWN *, LPUNKNOWN *);

#include <gx.h>
#pragma comment(lib,  "gx.lib")


#elif defined(PLAT_IOS)
//#include "cmtimer.h"
class IMThread {
public:
	virtual void RunL() = 0;
	virtual void DoCancel() = 0;
};
#elif defined(PLAT_AND)
#include <pthread.h>
#endif
#endif

class CMVideoPlay : public MDirectScreenAccess
#if defined(PLAT_SYMBIAN) 
, public IMNotifyTimer
, public CActive
#elif defined(PLAT_IOS)
, public IMThread
#endif
{
  public:
    CMVideoPlay(IMVideoNotify& rVideoNotify, IMReferenceClock& rRefClock, CMStreamBuffer* pStreamBuffer);

    virtual ~CMVideoPlay();

    // Description: Init codec and open video device.
    // param nCodec: Codec type.
    // param nWidth: width of video.
    // param nHeight: height of video.
    // Return: TRUE if successful; otherwise FALSE.
    BOOL Open(INT32 nCodec, INT32 nWidth, INT32 nHeight);

    void Play();

    void Pause();

    void Stop();

    void Close();

    INT32 GetRotation();

    void SetRotation(INT32 nRotation);

   // void GetDrawRect(CMRect& rcDraw);

	void SetDrawSize(INT32 nWidth, INT32 nHeight);

	void SetDrawPoint(INT32 nLeft, INT32 nTop);
	
  private:
    IMVideoNotify& m_VideoNotify;

    IMReferenceClock& m_RefClock;

    CMStreamBuffer* m_pStreamBuffer;

    INT32 m_nVState;

    //INT32 m_nRotation;

    //CMRect m_rcRender;

    BOOL m_bPlaying;

    IMCodec* m_pCodec;

    MDecData m_OutData;

    //UINT32 m_nWidth;

    //UINT32 m_nHeight;

    Med_Packet* m_pVideoPacket;

    UINT32 m_nCurPosInPacket;

    INT32 m_nTimeStamp;
    
    //CMOverlay m_Overlay;

	ColorConvertBase* m_pOverlay;

    BOOL InitDirectDraw();
	void UpdateOverlay();
    BOOL GetNextFrame();

    // Functions from base class MDirectScreenAccess
	void Restart(RDirectScreenAccess::TTerminationReasons aReason);
	void AbortNow(RDirectScreenAccess::TTerminationReasons aReason);
    // Functions from base class CActive
	void RunL();
	void DoCancel();

    UINT32  m_nBpp;//目前的手机都是16位色，所以目前只支持16
	UINT32  m_nXpitch;//目前的设备都是2，所以处理中默认按2处理，此变量没有启用
	UINT32  m_nYpitch;
	UINT32 m_framebufwidth;
	UINT32 m_framebufheight;

	INT32   m_nWidth;//原始图像宽
    INT32   m_nHeight;//原始图像高
    UINT32  m_nRotation;//旋转
	INT32   m_nRenderWidth;
	INT32   m_nRenderHeight;
	INT32   m_nRenderLeft;
	INT32   m_nRenderTop;
	
#if defined(PLAT_SYMBIAN)
    CDirectScreenAccess* m_pDSA;
    CFbsBitGc* m_pGc;
    CFbsBitmap* m_pVirtualScreen;
    
    CMTimer m_cTimer;
	void OnTimer(CMTimer &cTimer);
#elif defined(PLAT_WINCE)
	UINT32				m_nDirectDrawMode;
    DIRECTDRAWCREATE    m_DirectDrawCreate;
    HINSTANCE           m_hDdraw;
    IDirectDraw*        m_pdd;
    DDSURFACEDESC       m_ddsd;
    IDirectDrawSurface* m_psurf;

    HANDLE m_hThread;
    HANDLE m_hExitEvent;
    static DWORD PlayThreadProc(LPVOID pData);

	void* BeginDraw();
	void EndDraw();
#elif defined(PLAT_IOS)
	UINT8*  m_buffer;
	void*   m_myThread;
	CMMutex m_mutex;
//	CMTimer m_cTimer;
//	void OnTimer(CMTimer &cTimer);
#elif defined(PLAT_AND)
	void*  m_buffer;
	CMMutex m_mutex;
	BOOL  m_bExitThread;
	BOOL  m_bRunning;
	static VOID* PlayThreadProc(VOID* pData);
	void RunL(void* para);
#endif
};



#endif /* CMVIDEOPLAY_H_HEADER_INCLUDED_B5AEFDC6 */
