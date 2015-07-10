// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description: 播放控制回调声明
//  Author:Tim Wxp
// //////////////////////////////////////////////////////////////////////////////
#ifndef __MPLAYERINTERFACE_INCLUDE__
#define __MPLAYERINTERFACE_INCLUDE__
#ifdef __cplusplus
#include"cmstreambuffer.h"
#include "cmstring.h"

const INT32 EMode_swf = 1; //swf格式http点播
const INT32 EMode_3mv = 2; //3mv格式http点播
const INT32 EMode_rtspvod = 3; //rtsp点播
const INT32 EMode_rtspliv = 4; //rtsp直播
const INT32 EMode_3ma = 5; //3ma格式http点播
const INT32 EMode_3mt = 6; //图文格式点播
const INT32 EMode_wml = 7; //WML格式
const INT32 EMode_html = 8; //HTML格式
const INT32 EMode_3gp = 9; //3gp点播
const INT32 EMode_scorm = 10; //scorm课件
const INT32 EMode_xml   = 11; //xml
const INT32 EMode_aac   = 12; //aac

#endif

//state
#define EUnKnown 0
#define EReady   1
#define EOpening 2
#define EPlaying 3
#define ESeeking 4   //只有EPlaying过程中才能seek。
#define EPausing 5   //只有EPlaying/EPaused状态才能进行操作。中间态，不上报
#define EPaused  6
#define EStopped 7
#define ESeeking2 8  //内部使用，不上报

#ifdef __cplusplus
enum EMediaType
{
	NET_VOD=0, //网络点播
	NET_LIVE,   //网络直播
	LOCAL_FILE   //本地播放
};
//网络数据通知类
class IMDataNotify
{
  public:
    virtual void OnHeadCompleted(Med_Info& HeadInfo) = 0;//头完成
    virtual void OnProgressChanged() = 0;//进度改变
	virtual void OnAllCompleted() = 0;
	virtual void OnSeekTime(UINT32 msec) = 0; //快进、快退时间通知
    virtual void OnError(UINT32 err=0) = 0;

};
//数据接口类
 class IMDataInter
{
  public:
    virtual BOOL Init(IMDataNotify* pNetworkNotify, CMStreamBuffer* pStreamBuffer) = 0;//初始化
    virtual BOOL Open(const CMString& sUrl, int mtype) = 0;//打开sUrl
	virtual BOOL IsRunning() = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
    virtual void Seek(UINT32 sec) = 0;
	virtual void GetHeadInfo(Med_Info& HeadInfo) = 0;
	virtual ~IMDataInter(){};
};
class IMAudioNotify
{
  public:
    virtual void ProgressChange(INT32 nBufPer, INT32 nPlayPos) = 0;
    virtual void NeedMoreData() = 0;
};
class IMVideoNotify
{
  public:
	virtual void VideoDraw(UINT8* data, INT32 width, INT32 height) = 0;
    virtual void ProgressChange(INT32 nBufPer, INT32 nPlayPos) = 0;
    virtual void NeedMoreData() = 0;

};
class IMPlayerUtilityObserver
{
  public:
    virtual void StateChange(void* UserData, INT32 nNew, INT32 nOld) = 0;

    virtual void ProgressChange(void* UserData, INT32 nBufPer, INT32 nPlayPos) = 0;

    virtual void OnAllCompleted(void* UserData) = 0;

    virtual void OnError(void* UserData, INT32 nErrorCode) = 0;
	
	virtual void VideoDraw(UINT8* data, INT32 width, INT32 height) = 0;

	virtual void NotifyStop() = 0; //android专用

};
class IMReferenceClock
{
  public:
    virtual INT32 GetRefTime() = 0;

};
#endif

#endif
