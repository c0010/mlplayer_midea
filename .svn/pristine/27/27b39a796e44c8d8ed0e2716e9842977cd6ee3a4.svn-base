// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMMYINFO_H_HEADER_INCLUDED_B19A05E7
#define CMMYINFO_H_HEADER_INCLUDED_B19A05E7

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>
using namespace std;

class CMMyInfo: public CMHandler<TDummyItem>
{
public:
	static CMMyInfo* GetInstance();

	static void ClearAll();

	virtual ~CMMyInfo();

	void SetListener(IMUpdateDataListener* pListener, IMSimpleResultListener* pListener2);
    
    BOOL UpheadPhoto(const char* filename);
    
    BOOL UpdatePushInfo(const char* tags, const char* uid);    //只更新推送信息，在登录中使用

	BOOL UpdateData();
    
    BOOL CompareTags();
    
    BOOL CompareAlias();

    BOOL ClearTagsAlias();

	BOOL isFetched();

	const char* GetJobnumber() const;

	const char* GetHeadimage() const;

	const char* GetFullName() const;

	const char* GetOrg() const;

	const char* GetDep() const;

	const char* GetPosition() const;

	const char* GetTitle() const;

	const char* GetRankUrl() const;
    
	const char* GetDetailUrl() const;
    
    const char* GetUid() const;
    
	const char* GetTags() const;

	int GetLevel() const;

	int GetValue() const;

	int GetCredit() const;

	int GetStudyrecord() const;


	int GetPositionCourseCount() const;

	int GetCurrentminvalue() const;

	int GetNextvalue() const;
    
    int GetUndoExam() const;
    
    int GetWrongQa() const;
    
    BOOL SetWrongQa(int count);
    
    void SetPositionCourseCount(int count);

    void SetStudyrecord(int count);
    
    int GetSex() const;

    int nContributeValue;//贡献分

protected:
	CMMyInfo();
	virtual BOOL DoCreate(sqlite3* db);
	virtual BOOL DoGetCacheItems(sqlite3* db);
	virtual BOOL DoRefresh(TDummyItem& obj);
	virtual BOOL DoUpdate(const TDummyItem& obj);
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TDummyItem& item);

    BOOL GetPushInfo(const char* tags, const char* alias, sqlite3* db);


    BOOL GetPreviousTagsAndAlias(sqlite3* db);

    BOOL CreateTagsAlias(sqlite3* db);

    BOOL GetTagsAliasItem(TiXmlElement* pItem, sqlite3* db, TDummyItem& item);

    BOOL GetTagsAliasCacheItems(sqlite3* db);

private:

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	string sTitle;

	string sWorkname;

	string sDevelopment;

	string sJobnumber;

	string sHeadimage;

	string sPosition;

	string sOrg;

	string sRankurl;

	string sDetailurl;

    int nSex;

	int nLevel;

	int nValue;

	int nCredit;

	int nStudycount;

	int nPositionCourseCount;

	int nCurrentminvalue;

	int nNextvalue;

	BOOL m_isFetched;

    int nUndoExam;//用户测验数

    int nWrongQa;//用户错题数

    string sPreviousUid;  //上次登录alias

    string sPreviousTags;  //上次登录tags

    string sUid;  //最新登录alias

    string sTags;   //最新登录tags

    char  m_tagsandaliastablename[64];   //存储tags，alias数据表

	static CMMyInfo* m_pTHIS;
    
    IMSimpleResultListener* m_pListener2;
};

#endif /* CMMYINFO_H_HEADER_INCLUDED_B19A05E7 */
