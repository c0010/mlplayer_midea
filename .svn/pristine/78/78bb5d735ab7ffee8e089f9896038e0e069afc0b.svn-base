// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMFEEDBACK_H_HEADER_INCLUDED_B20CB0EA
#define CMFEEDBACK_H_HEADER_INCLUDED_B20CB0EA

#include "stdafx.h"
#include "cmcommon.h"

class CMFeedback : IMNotifySession
{
  public:
    CMFeedback(IMSimpleResultListener* pListener);

    virtual ~CMFeedback();

    void SetUserData(void* UserData);

    void CommitFeedback(const char* sSuggestion, const char* sModel);

  private:
    //interface from IMNotifySession
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

    IMSimpleResultListener* m_pListener;

    void* m_UserData;

	CMSession *m_pSession;

};



#endif /* CMFEEDBACK_H_HEADER_INCLUDED_B20CB0EA */
