// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmplayerutility.h
//  Description: The class offers a simple interface to open, play and obtain information from sampled data that be provided using files or URLs.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMPLAYERUTILITY_H_HEADER_INCLUDED_B5AED858
#define CMPLAYERUTILITY_H_HEADER_INCLUDED_B5AED858

#include "mplayerinterface.h"

#ifdef __cplusplus

class CMString;
class CMFile;

#if defined(PLAT_AND)
#include <jni.h>
struct filedsU {
	jfieldID  mContext;
	jmethodID VideoDrawFunc;
	jmethodID PostToFunc;
};
#endif


class CMPlayerUtility
{
  public:
    CMPlayerUtility(IMPlayerUtilityObserver* rPlayerObserver);

    virtual ~CMPlayerUtility();

    void SetUserData(void* UserData);



    // Description: Creates instance of buffer??Audio??Video.
    // Return: TRUE if successful; otherwise FALSE.
    BOOL Init();

    // Description: Creates instance of network datasource and open it.
    // param sUrl: Opening url.
    // param nMode: Mode of dest.
    // Return: none.
    void OpenUrl(const char* sUrl, const UINT32 nMode/* = EMode_3mv*/,const char* coursewareID = NULL);

    void OpenFile(const char* sFileName,const UINT32 nMode = EMode_3mv);

    // Description: Play audio and video.
    // Return: none.
    void Play();

    // Description: Pause audio and video.
    // Return: none.
    void Pause();

    // Description: Stop audio and video, reset buffer, set DataInter's pos to 0.
    // Return: none.
    void Stop();

    // 关闭并销毁网络数据源，关闭音频、视频，reset任何状态值
    // Description: Close DataInter, audio and video and reset all.
    // Return: none.
    void Close();

    INT32 Duration();

    INT32 GetPosition();

    void SetPosition(INT32 nPos);

    INT32 MaxVolume();

    INT32 GetVolume();

    void SetVolume(INT32 nVolume);

	//设置百分比类型的声音 50  50％
	void SetVolPer(UINT32 nPer);
	
	//声音增大，为max的10％
	void VolUp();
	
	INT32 GetOpenType();

	//声音减小，为max的10％
	void VolDown();
	
    INT32 GetRotation();

    void SetRotation(INT32 nRotation);

	void SetDrawSize(INT32 nWidth, INT32 nHeight);

	void SetDrawPoint(INT32 nLeft, INT32 nTop);

    void SetBufTime(UINT32 nBufTime) {m_nBufTime = nBufTime;};
    
	BOOL IsPlaying();

    BOOL IsDataCompleted(){return m_bDataCompleted;}

    void SetManuPause(BOOL pause);

    BOOL IsManuPause();

    void StatusChange(INT32 nStatus);
    void VideoDraw(void* data, int width, int height);

#if defined(__IPHONE_OS__)
    void InterruptStart();
    void InterruptEnd();
#endif
    
#if defined(PLAT_AND)
    static filedsU field;
#endif

  private:
    IMPlayerUtilityObserver* m_PlayerObserver;

    void* m_UserData;

    INT32 m_nState;

    INT32 nOpenType; //0 openfile 1openurl

    UINT32 m_nDuration;
    
    UINT32 m_nPosition;

    UINT32 m_nBufTime;

    BOOL   m_bOnlyAudio;

    BOOL m_bDataCompleted;

    BOOL m_bOpened;

    BOOL m_bManuPause;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

void status_change(void* p, int status);
void video_draw(void* p, void* data, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /* CMPLAYERUTILITY_H_HEADER_INCLUDED_B5AED858 */
