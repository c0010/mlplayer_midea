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

class CMTimer_Imp : public CTimer
{
public:
    CMTimer_Imp(CMTimer* pTimer);

    void SetTimer(UINT32 nInterval);

    void KillTimer();

private:
    virtual void RunL();

    CMTimer* m_pTimer;
};



#endif /* CMTIMER_IMP_H_HEADER_INCLUDED_B5BC9E99 */
