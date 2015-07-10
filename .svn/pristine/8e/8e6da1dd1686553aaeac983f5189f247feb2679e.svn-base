// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef __CMRETRIEVEPASS_H__
#define __CMRETRIEVEPASS_H__

#include "cmcommon.h"


class CMRetrievePass : public IMNotifySession
{
  public:
	CMRetrievePass(IMSimpleResultListener* pListener);

	virtual ~CMRetrievePass();

	void Commit(const char* emialorphone);

	void SetUserData(void* UserData);

	char* getPMsg();

  protected:
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

  private:
	IMSimpleResultListener* m_pListener;

    void* m_UserData;

	CMSession* m_pSession;

	char m_Msg[300];

};

#endif /* CMBROWSER_H_HEADER_INCLUDED_B19B17D3 */
