// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCOURSEINFO_H_HEADER_INCLUDED_B19B2B7C
#define CMCOURSEINFO_H_HEADER_INCLUDED_B19B2B7C

#include "stdafx.h"
#include "cmcommon.h"
#include "cmhandler.h"

template<typename T> class CMList;

class CMCourseInfo: public CMHandler<TCoursewareItem>
{
public:
	CMCourseInfo(const CMCourseInfo& other);

	CMCourseInfo();

	virtual ~CMCourseInfo();

	void SetListener(IMUpdateDataListener* pUpdateDataListener,IMRatingListener* pRatingListener);

	void RequestCourseware(const char* sid);

	//用内部TClassItem对象填充
	BOOL GetClassItem(TClassItem& item);

	BOOL Rating();

	//仅供cmcoursedownload使用，直接调用内部对象
	int CoursewareCount() const;
	//仅供cmcoursedownload使用，直接调用内部对象
	BOOL GetCourseware(int nIndex, TCoursewareItem& item) const;

	int GetCurrentCoursewareIndex();

	int GetCoursewareFlag(int nIndex);

	void SetCoursewareFlag(int nIndex, int nCheck);

	void SetUserData(void* UserData);

	CMCourseInfo& operator=(const CMCourseInfo& right);

	CMCourseInfo& operator=(const TBrowserItem& right);

	// CMCourseInfo& operator=(const TClassItem& right);

	BOOL operator==(const CMCourseInfo& right);

	int HaveCourseware(const TCoursewareItem& item);

	BOOL RequestCourseAndClass(const char* setid);

	BOOL RatingCourseinfo(const char* CoursewareID); //课件喜欢

protected:

	BOOL SaveCourseItem(sqlite3* db, const TCoursewareItem& item);
	CMCourseInfo& operator=(const TiXmlElement* right);

	TiXmlElement* CreateXmlElement();

	//当前下载状态，0：未下载； 1：部分下载;  2：已全部下载
	INT32 m_nStatus;

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode,TiXmlDocument* pDoc);

	void DoCoursewareItemList(const TiXmlElement* pItemList);

	friend class CMCourseDownload;

	//网络回来数据，要入缓存并刷新对象
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TCoursewareItem& item);
	//缓存回来数据，读取缓存到对象列表
	virtual BOOL DoGetCacheItems(sqlite3* db);
	virtual BOOL DoRefresh(TCoursewareItem& obj);
	virtual BOOL DoUpdate(const TCoursewareItem& obj);
	virtual BOOL DoCreate(sqlite3* db);
	virtual void DoClear();

	int requestModel;

	friend class CMDBHelper;

private:

	BOOL SaveClassInfo(TClassItem& item);
	BOOL GetClassInfo(TClassItem& item, const char* SID);

	char m_ClassTablename[64];

	IMRatingListener* m_pRatingListener;

	TClassItem* m_pClassItem;

	int m_nCurrentCourseware;

	BOOL m_bRatting;

	char operatingID[64];
};

#endif /* CMCOURSEINFO_H_HEADER_INCLUDED_B19B2B7C */
