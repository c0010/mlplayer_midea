/*
 * cmwetools.h
 *
 *  Created on: 2013-10-10
 *      Author: mazhen
 */

#ifndef CMWETOOLS_H_
#define CMWETOOLS_H_

#include "stdafx.h"
#include "cmcommon.h"

//class WECoursetools {
//public:
//
//	char sWesize[16];
//
//	char sWeversion[16]; //版本号
//
//	char sWeurl[600]; //下载地址
//
//};

class CMWetools: public IMNotifySession {
public:

	CMWetools();
	virtual ~CMWetools();

	CMWetools(IMUpdateDataListener* pUpdateDataListener);
	void GetWetool();

	void SetUserData(void* UserData);

	const char* GetWesize() const;

	const char* GetWeversion() const;

	const char* GetWeUrl() const;

//protected:
//
//struct WEtoolsItem
//	{
//	    WECoursetools		tWeItem;
//	};

private:

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode,
			TiXmlDocument* pDoc);

    IMUpdateDataListener* m_pUpdateDataListener;

	void* m_UserData;

	CMSession* m_pSession;

	INT32	m_nCount;

	char sWesize[16];

	char sWeversion[16]; //版本号

	char sWeurl[600]; //下载地址

};

#endif /* CMWETOOLS_H_ */
