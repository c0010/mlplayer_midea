/*
 * cmversionverify.h
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#ifndef CMVERSIONVERIFY_H_
#define CMVERSIONVERIFY_H_


#include "stdafx.h"
#include "cmcommon.h"
#include <string>

#endif /* CMVERSIONVERIFY_H_ */

class CMVersionVerify : public IMNotifySession
{

public:
	CMVersionVerify(IMUpdateDataListener* pListener);
	virtual ~CMVersionVerify();

	void GetVersionMsg();

	void SetUserData(void* UserData);

	string sVerCode;//版本号

	string sVerNode;//版本简介

	string sDownUrl;//下载地址

	BOOL bForceUpdate;//是否强制更新

	void Cancel();

private:

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode,
			TiXmlDocument* pDoc);

    IMUpdateDataListener* m_pUpdateDataListener;

	void* m_UserData;

	CMSession* m_pSession;

};