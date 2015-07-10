// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMRESETPASSWORD_H_HEADER_INCLUDED_B20C974C
#define CMRESETPASSWORD_H_HEADER_INCLUDED_B20C974C

#include "cmcommon.h"

class CMResetPassword : IMNotifySession
{
  public:
    CMResetPassword(IMSimpleResultListener* pListener);

    virtual ~CMResetPassword();

    void SetUserData(void* UserData);

    void Commit(const char* sOld, const char* sNew);

    //interface from IMNotifySession
  private:
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

    IMSimpleResultListener* m_pListener;

    void* m_UserData;
	
	char m_sNewPass[100];

	CMSession* m_pSession;	
};



#endif /* CMRESETPASSWORD_H_HEADER_INCLUDED_B20C974C */
