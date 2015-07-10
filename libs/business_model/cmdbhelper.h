// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMDBHELPER_H_HEADER_INCLUDED_B235FC36
#define CMDBHELPER_H_HEADER_INCLUDED_B235FC36
#include "stdafx.h"

#include "cmcommon.h"

#include "sqlite3.h"
#include "cmmutex.h"

#include "cmlist.h"

//课程课件表名称
#define kCourseTable  "courseAll"

//课程课件表的数据最后列的列数
#define kDbColumnIndex  45


class CMCourseInfo;

class CMDBHelper
{
public:
    
    static CMDBHelper* GetInstance(int type);

	sqlite3* GetConnection();
    
    ~CMDBHelper();

    bool ClearCacheTable();//删除“cacheInfo”表
protected:
    
    CMDBHelper();

    void CloseConnection();
    
    BOOL CreateCacheTable(sqlite3* db);

private:
    
    
    bool RefreshFavoriteTable(sqlite3* db, int oldVersion, CMList<TBrowserItem*>* favoriteList);

    bool RefreshDownloadTable(sqlite3* db, int oldVersion, CMList<CMCourseInfo*>* downloadList);
    
    bool UpgradeFavoriteTable(sqlite3* db, int newVersion, CMList<TBrowserItem*>* favoriteList);
    
    bool UpgradeDownloadTable(sqlite3* db, int newVersion, CMList<CMCourseInfo*>* downloadList);
    
    
    bool DeleteAllTables(sqlite3* db);
    
    int nType;//0.RootDir_DB   1.UserDir_DB
    
	const static int DB_VERSION = 15;
    
	static CMDBHelper* pTHIS;
    
    static CMDBHelper* pRootTHIS;
        
    sqlite3* db;
    
	//建表
	bool OnCreate(sqlite3* db);

	//升级表
	bool OnUpgrade(sqlite3* db, int oldVersion, int newVersion);

	int GetVersion(sqlite3* db);

	void SetVersion(sqlite3* db, int version);
    
//      CMMutex  m_mutex;


    
    friend class CMLogin;
    
    friend class CMGlobal;

};


#endif



