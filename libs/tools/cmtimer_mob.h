// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:定时器实现类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99
#define CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99

class IMNotifyTimer;
class CMTimer;

class CMTimer_Imp
{
public:
    CMTimer_Imp(CMTimer* pTimer);
    ~CMTimer_Imp();

    void SetTimer(UINT32 nInterval);

    void KillTimer();

    static void CALLBACK TIMECALL(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2); 

private:
    CMTimer* m_pTimer;
    UINT32 m_nID;
};



#endif /* CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99 */
