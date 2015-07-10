// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMTIMER_H_HEADER_INCLUDED_B5BE1A23
#define CMTIMER_H_HEADER_INCLUDED_B5BE1A23

class CMTimer;

class IMNotifyTimer
{
public:
    // 定时器时间到触发此接口，cTimer是触发的Timer
    virtual void OnTimer(CMTimer &cTimer) = 0;

};

class CMTimer_Imp;

class CMTimer
{
public:
    CMTimer(IMNotifyTimer* pNotify);
    ~CMTimer();

    // 精度毫秒
    void Set(UINT32  nInterval);

    // 开始计时
    void Start();

    void Stop();

    // 如果不设，此ID为为任意值
    void SetTimerID(UINT32 nID);

    UINT32 GetTimerID();

private:
    CMTimer();

    UINT32           m_nID;
    UINT32           m_nInterval;
    IMNotifyTimer*   m_pNotify;

    CMTimer_Imp*     m_pImp;

    friend  class CMTimer_Imp;
};


#endif /* CMTIMER_H_HEADER_INCLUDED_B5BE1A23 */
