/*
 *  cmdevicetoken.h
 *  MLPlayer
 *
 *  Created by sunjj on 12-6-6.
 *  Copyright 2012 w. All rights reserved.
 *
 */

#ifndef CMDEVICETOKEN_H_HEADER_INCLUDED_B19B17D3
#define CMDEVICETOKEN_H_HEADER_INCLUDED_B19B17D3

#include "cmcommon.h"


class CMDeviceToKen : public IMNotifySession
{
public:   
	
	CMDeviceToKen(IMSimpleResultListener* pListener);
	
	 virtual ~CMDeviceToKen();
	
	void SetUserData(void* UserData);	
	
	//回传设备令牌	该条协议支持匿名访问（iOS专用）
	void SendDeviceToKen(const char* sDeviceToKen);
	
private:
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
	
    IMSimpleResultListener* m_pListener;
	
    void* m_UserData;

	CMSession* m_pSession;
};

#endif /*CMDEVICETOKEN_H_HEADER_INCLUDED_B19B17D3*/