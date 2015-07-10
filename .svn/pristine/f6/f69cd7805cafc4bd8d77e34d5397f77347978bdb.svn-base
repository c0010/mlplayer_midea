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
#include "cmcoursedownload.h"
#include <string>

using namespace std;

class CMVideoPlay;
class CMStreamBuffer;
class CMAudioPlay;

#if defined(PLAT_AND)
#include <jni.h>
struct filedsU {
	jfieldID  mContext;
	jmethodID VideoDrawFunc;
	jmethodID PostToFunc;
};
#endif

class CMPlayerUtility : public IMAudioNotify, public IMVideoNotify, public IMDataNotify
{
  public:
    CMPlayerUtility(IMPlayerUtilityObserver& rPlayerObserver);

    virtual ~CMPlayerUtility();

    void SetUserData(void* UserData);

    // Description: Creates instance of buffer??Audio??Video.
    // Return: TRUE if successful; otherwise FALSE.
    BOOL Init();

    // Description: Creates instance of network datasource and open it.
    // param sUrl: Opening url.
    // param nMode: Mode of dest.
    // Return: none.
    void OpenUrl(CMString sUrl, const UINT32 nMode/* = EMode_3mv*/,const char* coursewareID = NULL);//有sLocalFilePath就先读本地文件，没有则读surl.sLocalFilePath可为空字符串

    void OpenFile(CMString sFileName,const UINT32 nMode = EMode_3mv);

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
	
	//声音减小，为max的10％
	void VolDown();
	
    INT32 GetRotation();

    void SetRotation(INT32 nRotation);

	void SetDrawSize(INT32 nWidth, INT32 nHeight);

	void SetDrawPoint(INT32 nLeft, INT32 nTop);
//    void GetDrawRect(CMRect& rcDraw);
//
//    void SetDrawRect(CMRect& rcDraw);//为了运算效率，要求宽、高可以被16整除

    void SetBufTime(UINT32 nBufTime) {m_nBufTime = nBufTime;};
    
	BOOL IsPlaying(){return (m_nState == EPlaying);}

    BOOL IsDataCompleted(){return m_bDataCompleted;}

    void SetManuPause(BOOL pause);

    BOOL IsManuPause();

    //The following function inherit from IMDataNotify, see also IMDataNotify
    virtual void OnHeadCompleted(Med_Info& HeadInfo);//头完成
    virtual void OnProgressChanged();//进度改变
	virtual void OnAllCompleted();
    virtual void OnSeekTime(UINT32 msec); //快进、快退时间通知
    virtual void OnError(UINT32 err=0);

    //The following function inherit from IMAudioNotify & IMVideoNotify, see also IMAudioNotify & IMVideoNotify
	virtual void VideoDraw(UINT8* data, INT32 width, INT32 height);
    virtual void ProgressChange(INT32 nBufPer, INT32 nPlayPos);
    virtual void NeedMoreData();

#if defined(PLAT_AND)
    static filedsU field;
#endif

  private:
    IMPlayerUtilityObserver& m_PlayerObserver;

    void* m_UserData;

    CMStreamBuffer* m_pStreamBuffer;

    IMDataInter* m_pMediaData;

    CMAudioPlay* m_pAudioPlay;

    CMVideoPlay* m_pVideoPlay;

    INT32 m_nState;

    UINT32 m_nDuration;
    
    UINT32 m_nPosition;

    UINT32 m_nBufTime;

    BOOL   m_bOnlyAudio;

    BOOL m_bDataCompleted;

    BOOL m_bOpened;

    BOOL m_bManuPause;
};



#endif /* CMPLAYERUTILITY_H_HEADER_INCLUDED_B5AED858 */
