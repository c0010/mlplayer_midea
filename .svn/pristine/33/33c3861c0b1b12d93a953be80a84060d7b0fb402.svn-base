// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
#include "cmdbhelper.h"
#include "cmglobal.h"
#include "cmpath.h"
#include "cmsettings.h"
#include "cmhandler.h"
#include "cmfavorites.h"
#include "cmcoursedownload.h"
#include "cmmutex.h"

/*
 ////////////
 root:
 enterpriseInfo
 
 ////////////////
 cmbrowser :    browserall_position browserall_course(sub_browserall_course)    browser all_news(sub_browserall_news)

 cmcategory:  category

 courseinfo:  coursewareall

 favorites: favorites

 cmmyinfo: myinfo

 cmqalist:  qalist

 cmquestiondetail:  AnswerList

 cmspecialtopic:  browser_specialtopic(sub_browser_specialtopic)
 
  dbversion:
 
 4: ver 2.0
 删除之前的所有表
 
 加入根目录db和用户文件夹下db区分
 
 5:  ver 2.1
 所有课程课件放入一个大表,下载和收藏数据升级
 */

static CMMutex g_mutex;

CMDBHelper* CMDBHelper::pTHIS = NULL;

CMDBHelper* CMDBHelper::pRootTHIS = NULL;

CMDBHelper::CMDBHelper() {
	db = NULL;
}

/**
 *	Get DB Instance
 *
 *	@param	type	0.RootDir  1.UserDir
 *
 *	@return
 */
CMDBHelper* CMDBHelper::GetInstance(int type) {

	if (type != 0 && type != 1)
		return NULL;

	if (type == 1) {

		if (pTHIS == NULL) {

			g_mutex.Lock();
            
			if (pTHIS != NULL) {
				g_mutex.UnLock();
				return pTHIS;
			}

            
			pTHIS = new CMDBHelper();

			pTHIS->nType = type;
            
            
            //创建缓存表
            sqlite3* db = pTHIS->GetConnection();
            
            pTHIS->CreateCacheTable(db);
            
            g_mutex.UnLock();

		}
		pTHIS->nType = type;

		return pTHIS;
        
	} else {
        
		if (pRootTHIS == NULL) {

			g_mutex.Lock();

			if (pRootTHIS != NULL) {
				g_mutex.UnLock();

				return pRootTHIS;
			}

			pRootTHIS = new CMDBHelper();

			pRootTHIS->nType = type;
		
			g_mutex.UnLock();

		}
        
		pRootTHIS->nType = type;

		return pRootTHIS;
	}

}
void CMDBHelper::CloseConnection() {
	if (db == NULL)
		return;

	sqlite3_close(db);

	db = NULL;

}

sqlite3* CMDBHelper::GetConnection() {

	if (db != NULL)
		return db;

	char DB_NAME[256];

	CMString sDir;

	// 0.RootDir  1.UserDir
	switch (nType) {

	case 0: {
		sDir = CMGlobal::TheOne().GetRootDir();

		break;
	}
	case 1: {
		sDir = CMGlobal::TheOne().GetUserDir();
		break;
	}
	default: {

		return NULL;
		break;
	}
	}

	snprintf(DB_NAME, 256, "%s%s", (const char*) sDir, "local.db");


    //连接数据库
	CM_LOGP(CM_LOGL_INFO, " db path :%s   type:%d", DB_NAME, nType);
    
    //使用串行方式
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);

	int ret = sqlite3_open_v2(DB_NAME, &db,
			SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
			NULL);
	if (ret != SQLITE_OK) {
		CM_ERRP("CMDBHelper::GetConnection %s failed:%d", DB_NAME, ret);
	}
    
    if(db == NULL)
        return NULL;
    
    //判断版本，建表或者升级表
    int version = GetVersion(db);

    
    if (version != DB_VERSION) {
     
        if (version == 0) {
            OnCreate(db);
        } else {
            
            //表升级
            for(int nowVersion = version; nowVersion < DB_VERSION; nowVersion++)
            {
                OnUpgrade(db, nowVersion, nowVersion + 1);
            }
            
        }
        
    }
    
	return db;
}

bool CMDBHelper::OnCreate(sqlite3* db) {

	if (nType == 1) {
		pTHIS->OnUpgrade(db, 0, 3);
		pTHIS->OnUpgrade(db, 3, DB_VERSION);

		//建表
	    CreateCacheTable(db);
		return true;

	}

	if (nType == 0) {

		pRootTHIS->OnUpgrade(db, 0, DB_VERSION);
		return true;
	}

	return true;
}

bool CMDBHelper::OnUpgrade(sqlite3* db, int oldVersion, int newVersion) {
	if (newVersion > oldVersion) {
		if (newVersion == 2 || newVersion == 3) {
			if (nType == 1) {
				char query[128];
				snprintf(query, 128,
						"DROP TABLE IF EXISTS qalist; DROP TABLE IF EXISTS AnswerList;");
				char *errorMsg;
				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK) {
					CM_ERRP("Table update failed, err: ", errorMsg);
                    }
			}
		}

		if (newVersion == 4) {
			if (nType == 1) {
				DeleteAllTables(db);
			}
		}

		if (newVersion == 5 && (oldVersion == 4 || oldVersion == 3)) {
			if (nType == 1) {

				CMList<TBrowserItem*>* favoriteList = new CMList<TBrowserItem*>();

				CMList<CMCourseInfo*>* downloadList = new CMList<CMCourseInfo*>();

				RefreshFavoriteTable(db, oldVersion, favoriteList);

				RefreshDownloadTable(db, oldVersion, downloadList);

				char* errorMsg = NULL;

				//删除所有表
				DeleteAllTables(db);

				//建立课程课件大表
				char sql[1024];
				BOOL ret = FALSE;
				snprintf(sql, 1024,
						"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,flag TEXT,title TEXT,brief TEXT,largeimage TEXT,image TEXT,thumb TEXT,type TEXT,coursewarecount INTEGER,url TEXT,pubdate TEXT,vc INTEGER,pv INTEGER,commentcount INTEGER,enablecomment INTEGER,enabledownload INTEGER,enablerating INTEGER,description TEXT,tag TEXT,specialtopic TEXT,credit TEXT,studyduration INTEGER,studyprogress INTEGER,laststudydate TEXT,favoritedate TEXT,mycompany INTEGER,israted INTEGER,markid TEXT,marktitle TEXT,model INTEGER,setid TEXT,islearned INTEGER)",
						kCourseTable);

				if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK) {
					ret = TRUE;
				} else {
					CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
					ret = FALSE;
				}

				//存入下载数据
				UpgradeDownloadTable(db, newVersion, downloadList);

				//存入收藏数据
				UpgradeFavoriteTable(db, newVersion, favoriteList);
                
                for(int i =0; i< favoriteList->size();i++)
                {
                    SAFEDELETE(favoriteList->at(i));
                }
                
                for(int i =0; i< downloadList->size();i++)
                {
                    SAFEDELETE(downloadList->at(i));
                }
                
				SAFEDELETE(favoriteList);
				SAFEDELETE(downloadList);
			}
		}
        
        if (newVersion == 6 && oldVersion == 5 )
        {
            
            if(nType == 1)
            {
                //删除myinfo表
                char query[128];
                snprintf(query, 128,
                         "DROP TABLE IF EXISTS myinfo;");
                char *errorMsg;
                if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK) {
                    CM_ERRP("Table update failed, err: ", errorMsg);
                }
                
                //拿下载数据
                CMList<TCoursewareItem>* coursewareList = new CMList<TCoursewareItem>();
                sqlite3_stmt *stmt = NULL;
                CHAR sql[1024];
                sql[0] = '\0';
                memset(sql, 0, 1024);
                
                snprintf(sql, 1024, "SELECT * FROM %s ORDER BY _id ASC", "download_courseware");
                
                if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
                    
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        
                        TCoursewareItem citem;
                        
                        utf8ncpy(citem.sID, (const char*)sqlite3_column_text(stmt, 1), 63);
                        
                        citem.nCheckStatus= sqlite3_column_int(stmt, 2);
                        
                        utf8ncpy(citem.sSetID, (const char*)sqlite3_column_text(stmt, 3), 63);

                        coursewareList->push_back(citem);
                        
                    }
                } else {
                    CM_ERRP("db fail! %s", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                }
                
                //删除下载表
                memset(sql, 0, 1024);
                
                snprintf(sql,1024 , "DROP TABLE IF EXISTS  %s ;", "download_courseware");
                //
                if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK) {
                    
                    CM_ERRP("Table update failed, err:%s ", errorMsg);
                    
                } else {
                    
                }
                
                //建表
                memset(sql, 0, 1024);
                snprintf(sql, 1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT, id TEXT UNIQUE, checkstatus INTEGER, setid TEXT)", "download_courseware");
                
                if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {

                }
                else
                {
                    CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
                }
                
                //存储数据
                for (int i = 0; i<coursewareList->size(); i++) {
                    
                    TCoursewareItem* item = &coursewareList->at(i);
                    
                    memset(sql, 0, 1024);

                    snprintf(sql, 1024,"REPLACE INTO %s(id,checkstatus,setid) VALUES (?,?,?) ;", "download_courseware");
                    
                    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
                    {
                        
                         sqlite3_bind_text(stmt,1,item->sID,-1,NULL);
                        
                        sqlite3_bind_int(stmt, 2, item->nCheckStatus);
                        
                        sqlite3_bind_text(stmt,3,item->sSetID,-1,NULL);
                        
                        if(sqlite3_step(stmt) == SQLITE_DONE)
                        {
                            
                        }
                        else
                        {
                            CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
                        }
                        
                        sqlite3_finalize(stmt);
                    }
                    else {
                        CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
                    }
                }
                
                SAFEDELETE(coursewareList);

            }
           
        }
        if(newVersion == 7 && oldVersion == 6)
        {
            if(nType == 1)
            {
                //coursewareAll表增加downloadurl
                char query[128];
				snprintf(query, 128,
                         "ALTER TABLE courseAll ADD COLUMN downloadurl TEXT;");
				char *errorMsg;
				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);
                
                
                //download_courseware表增加decompressed,entryfilepath
                
                memset(query, 0, 128);

                snprintf(query, 128,
                         "ALTER TABLE download_courseware ADD COLUMN decompressed INTEGER;");
                if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
                    CM_ERRP("Table update failed, err: ", errorMsg);
                
                
                //download_courseware表增加entryfilepath
                
                memset(query, 0, 128);

                snprintf(query, 128,
                         "ALTER TABLE download_courseware ADD COLUMN entryfilepath TEXT;");
                if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
                    CM_ERRP("Table update failed, err: ", errorMsg);
                
                
                //download_courseware表增加localfilepath
                
                memset(query, 0, 128);

                snprintf(query, 128,
                         "ALTER TABLE download_courseware ADD COLUMN localfilepath TEXT;");
                if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
                    CM_ERRP("Table update failed, err: ", errorMsg);
                
                ///download_class中status改为0

                memset(query, 0, 128);

                sqlite3_stmt *stmt;
                snprintf(query, 128,
                         "UPDATE download_class SET status=?;");
                if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, 0);
                    
                }
                
                if(sqlite3_step(stmt)==SQLITE_DONE)
                {
                    
                }
                else {
                    CM_ERRP("sqlite3_step %s failed.error:%s", query, sqlite3_errmsg(db));
                }

          
                //download_courseware中checkstatus都改为1
                
                memset(query, 0, 128);
                
                snprintf(query, 128,
                         "UPDATE download_courseware SET checkstatus=?;");
                if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, 1);
                    
                }
                
                if(sqlite3_step(stmt)==SQLITE_DONE)
                {
                    
                }
                else {
                    CM_ERRP("sqlite3_step %s failed.error:%s", query, sqlite3_errmsg(db));
                }
                
                //download_courseware中decompressed都改为1
                memset(query, 0, 128);
                
                snprintf(query, 128,
                         "UPDATE download_courseware SET decompressed=?;");
                if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
                {
                    sqlite3_bind_int(stmt, 1, 1);
                    
                }
                
                if(sqlite3_step(stmt)==SQLITE_DONE)
                {
                    
                }
                else {
                    CM_ERRP("sqlite3_step %s failed.error:%s", query, sqlite3_errmsg(db));
                }

                //处理得到url
                char tempurl[100];
                memset(tempurl, 0, 100);
                utf8ncpy(tempurl, SETTING.GetServerUrl(), 99);
                
                for(int i=strlen(tempurl)-1;i>0;i--)
                {
                    if(tempurl[i]=='/')
                    {
                        tempurl[i+1] = 0;
                        break;
                    }
                    
                }
                
                
                //得到所有的课件
                CMList<TCoursewareItem>* coursewareList = new CMList<TCoursewareItem>();
                CHAR sql[1024];
                sql[0] = '\0';
                memset(sql, 0, 1024);
                
                snprintf(sql, 1024, "SELECT * FROM courseAll WHERE model = ? ");
                
                if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
                    
                    sqlite3_bind_int(stmt, 1, 1);
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        
                        TCoursewareItem citem;
                        citem.fetchItem(stmt);
                        //拼接下载地址
                        string downloadurl = string(tempurl);
                        downloadurl.append("ContentHandler/GetCoursePackage?id=");
                        downloadurl.append(citem.sID);
                        
                        utf8ncpy(citem.sDownloadUrl, downloadurl.c_str(), 299);
                        
                        coursewareList->push_back(citem);
                        
                    }
                } else {
                    CM_ERRP("db fail! %s", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                }
                
                //download_courseware中text/html的decompressed为0
                
                for (int i =  0 ; i<coursewareList->size() ; i++) {
                    
                    TCoursewareItem item;
                    item = coursewareList->at(i);
                    item.Update();
                    
                    //download_courseware中checkstatus改为1,若视频的话decompressed为1，其他为0
                    memset(query, 0, 128);
                    
                    snprintf(query, 128,
                             "UPDATE download_courseware SET decompressed=? WHERE id=?; ");
                    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
                    {
                        
                        if (strcmp(item.sType, "text/html")==0)
                        {
                            sqlite3_bind_int(stmt, 1, 0);
                        }else
                        {
                            sqlite3_bind_int(stmt, 1, 1);
                        }
                        
                        sqlite3_bind_text(stmt, 2, item.sID,-1,NULL);

                        
                    }
                    
                    if(sqlite3_step(stmt)==SQLITE_DONE)
                    {
                        
                    }
                    else {
                        CM_ERRP("sqlite3_step %s failed.error:%s", query, sqlite3_errmsg(db));
                    }

                    sqlite3_finalize(stmt);
                    
                }
           
                SAFEDELETE(coursewareList);
            }
        }
        
        if(newVersion ==8 && oldVersion == 7)
        {
            if(nType == 1)
            {
                
                //coursewareAll表增加markpicurl(标签图片地址)
                char query[256];
				snprintf(query, 256,
                         "ALTER TABLE courseAll ADD COLUMN markpicurl TEXT;");
				char *errorMsg = NULL;
				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);
                
                //地址改为相对地址
                //先拿出所有数据
                CMList<TCoursewareItem>* coursewareList = new CMList<TCoursewareItem>();
                CHAR sql[1024];
                sql[0] = '\0';
                memset(sql, 0, 1024);
                
                snprintf(sql, 1024, "SELECT * FROM download_courseware ");
                
                sqlite3_stmt *stmt;

                if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
                    
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        
                        TCoursewareItem citem;
                        utf8ncpy(citem.sID, (const char*)sqlite3_column_text(stmt, 1), 63);
                        utf8ncpy(citem.sLocalFilePath, (const char*)sqlite3_column_text(stmt, 6), 299);
                        
                        
                        //处理地址
                        char* path = NULL;
                        char* pointer = NULL;
                        
                        pointer = &citem.sLocalFilePath[0];
                        
                        while (*pointer != 0)
                        {
                            if ((*pointer == '/') || (*pointer == '\\'))
                                path = pointer+1;
                            
                            pointer++;
                        }
                        
                        utf8ncpy(citem.sLocalFilePath, path, 299);
                        
                        coursewareList->push_back(citem);
                        
                    }
                }
                else
                {
                    CM_ERRP("db fail! %s", sqlite3_errmsg(db));
                    sqlite3_finalize(stmt);
                }
                
                
                //更新数据
                for (int i =  0 ; i<coursewareList->size() ; i++) {
                    
                    TCoursewareItem item;
                    item = coursewareList->at(i);
                    
                    //download_courseware中checkstatus改为1,若视频的话decompressed为1，其他为0
                    memset(query, 0, 256);
                    
                    snprintf(query, 256,
                             "UPDATE download_courseware SET localfilepath=? WHERE id=?; ");
                    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
                    {
                        sqlite3_bind_text(stmt, 1, item.sLocalFilePath, -1,NULL);
                        
                        
                        sqlite3_bind_text(stmt, 2, item.sID, -1,NULL);

                    }
                    
                    if(sqlite3_step(stmt)==SQLITE_DONE)
                    {
                        
                    }
                    else
                    {
                        CM_ERRP("sqlite3_step %s failed.error:%s", query, sqlite3_errmsg(db));
                    }
                }
                SAFEDELETE(coursewareList);
            }
                
        }
        
        if(newVersion ==10 && oldVersion ==9)
        {
            if(nType == 1)
            {
                //qalist表增加categorytitle(问题类别名)
                char query[256];
				snprintf(query, 256,
                         "ALTER TABLE qalist ADD COLUMN categorytitle TEXT;");
				char *errorMsg = NULL;
                
				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);
                
                //qalist表增加categoryid(问题类别名)
                memset(query, 0, 256);
				snprintf(query, 256,
                         "ALTER TABLE qalist ADD COLUMN categoryid TEXT;");
				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);
                

            }
        }
        
        if (newVersion == 11 && oldVersion == 10) {
            if(nType == 1)
            {
                //courseAll 增加播放方向 orientation
                char query[1024];
				snprintf(query, 1024,
                         "ALTER TABLE courseAll ADD COLUMN orientation TEXT;");
				char *errorMsg = NULL;

				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);

            }
        }

        if (newVersion == 13 && oldVersion == 12) {
            if(nType == 1)
            {
                //互动通讯录增加jid，删除原有通讯记录
                char query[1024];
				snprintf(query, 1024,
                         "DROP TABLE contacts_recent;");
				char *errorMsg = NULL;
                
				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);
            }
        }

        if(newVersion == 14 && oldVersion == 13)
        {
        	if(nType == 1)
        	{
        		char query[1024];
        		snprintf(query,1024,"ALTER TABLE exerciselist ADD COLUMN trainid TEXT DEFAULT ''");
        		char *errorMsg = NULL;

				if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
					CM_ERRP("Table update failed, err: ", errorMsg);
                
                memset(query, 0, 1024);
                snprintf(query,1024,"ALTER TABLE myinfo ADD COLUMN sex TEXT DEFAULT ''");
                
                if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
                    CM_ERRP("Table update failed, err: ", errorMsg);

        	}
        }
        
        if (newVersion == 15) {
            if(nType == 1)
            {
                //courseAll 增加播放方向 orientation
                char query[1024];
                snprintf(query, 1024,
                         "ALTER TABLE qalist ADD COLUMN isanonymity INTEGER;");
                char *errorMsg = NULL;
                
                if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK)
                    CM_ERRP("Table update failed, err: ", errorMsg);
                
            }
        }


		SetVersion(db, newVersion);

	}
	return true;
}


bool CMDBHelper::RefreshFavoriteTable(sqlite3* db, int oldVersion, CMList<TBrowserItem*>* favoriteList) {
	//查询所有收藏
	BOOL ret = FALSE;
	sqlite3_stmt *stmt = NULL;
	CHAR sql[1024];
	sql[0] = '\0';

	snprintf(sql, 1024, "SELECT * FROM %s ORDER BY _id ASC", "favorites");

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

        TBrowserItem *item;
        
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			if (sqlite3_column_int(stmt, 30) == 0) {
                item =new TClassItem();

			} else {
			    item =new TCoursewareItem();
			}
            
            item->fetchItem(stmt);

            favoriteList->push_back(item);

		}
		sqlite3_finalize(stmt);

		ret = TRUE;
	} else {
		CM_ERRP("db fail! %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);

		return FALSE;
	}

	return ret;

}

bool CMDBHelper::RefreshDownloadTable(sqlite3* db, int oldVersion,
		CMList<CMCourseInfo*>* downloadList) {
    //之前版本的代码
	//查询所有下载
    BOOL ret = FALSE;

    if(oldVersion <5)
    {
        sqlite3_stmt *stmt = NULL;
        CHAR sql[1024];
        sql[0] = '\0';
        memset(sql, 0, 1024);

        snprintf(sql, 1024, "SELECT * FROM %s ORDER BY _id ASC", "download_class");

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

            while (sqlite3_step(stmt) == SQLITE_ROW) {

                CMCourseInfo *item= new CMCourseInfo();
                TClassItem citem;
                citem.fetchItem(stmt);

                item->m_nStatus = sqlite3_column_int(stmt, 33);
                
                //从TClassItem拷贝内容到CMCourseInfo对象
                *item = citem;

                downloadList->push_back(item);

                ret = TRUE;
            }
        } else {
            CM_ERRP("db fail! %s", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return FALSE;
        }

        for (int i = 0; i < downloadList->size(); i++) {
            CMCourseInfo* item = downloadList->at(i);
            TClassItem citem;
            item->GetClassItem(citem);

            memset(sql, 0, 1024);

            snprintf(sql, 1024, "SELECT * FROM %s WHERE setid = ? ORDER BY _id ASC",
                    "download_courseware");

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

                sqlite3_bind_text(stmt, 1, citem.sID, -1, NULL);

                while (sqlite3_step(stmt) == SQLITE_ROW) {

                    TCoursewareItem courseware;

                    ((TCoursewareItem&) courseware).fetchItem(stmt);

                    ((TCoursewareItem&) courseware).nCheckStatus =
                            sqlite3_column_int(stmt, 33);

                    if (!(item->m_lstItem))
                        item->m_lstItem = new CMList<TCoursewareItem>;

                    item->m_lstItem->push_back(courseware);
                }
            }
        }
        
        sqlite3_finalize(stmt);
    }
    
    if(oldVersion == 5)
    {
                sqlite3_stmt *stmt = NULL;
        CHAR sql[1024];
        sql[0] = '\0';
        memset(sql, 0, 1024);
        
        
        snprintf(sql, 1024, "SELECT * FROM %s ORDER BY _id ASC", "download_courseware");
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                
                CMCourseInfo *item= new CMCourseInfo();
                TClassItem citem;
                citem.fetchItem(stmt);
                
                item->m_nStatus = sqlite3_column_int(stmt, 33);
                
                //从TClassItem拷贝内容到CMCourseInfo对象
                *item = citem;
                downloadList->push_back(item);
                
                ret = TRUE;
            }
        } else {
            CM_ERRP("db fail! %s", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return FALSE;
        }
        
    }

	return ret;
}


//bool RefreshQuestionTable(sqlite3* db, int oldVersion, CMList<CMCourseInfo*>* downloadList)
//{
//    return TRUE;
//}



bool CMDBHelper::UpgradeFavoriteTable(sqlite3* db, int newVersion,
		CMList<TBrowserItem*>* favoriteList) {
	BOOL ret = FALSE;

    if(favoriteList == NULL || favoriteList->size() == 0)
        return FALSE;

    char* errorMsg;

    
    if (sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", NULL, NULL,
                     &errorMsg) != SQLITE_OK) {
        CM_ERRP("Failed to begin transaction: %s", errorMsg);
    }
		//建立收藏表
		ret = CMFavorites::GetInstance()->DoCreate(db);

		//存入收藏数据
		for (int i = 0; i < favoriteList->size(); i++) {

			TBrowserItem* temp = favoriteList->at(i);

			TBrowserItem* item;

			if (temp->nModel == 0) {
				item = new TClassItem();

			} else {
				item = new TCoursewareItem();
			}
            
            
            *item = *(favoriteList->at(i));
            
     
            CMFavorites::GetInstance()->CMContenthandler::DoPutItem(NULL,
                                                                    db, item);
  
            
            CMFavorites::GetInstance()->DoClear(); //只清空链表


            
		}
    
    if (sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL,
                     &errorMsg) != SQLITE_OK) {
        CM_ERRP("Failed to commit transaction: %s", errorMsg);
    }
    
	
	return ret;

}

bool CMDBHelper::UpgradeDownloadTable(sqlite3* db, int newVersion,
		CMList<CMCourseInfo*>* downloadList) {
	BOOL ret = FALSE;

	if (newVersion == 5) {
		//建立下载表
		CMCourseDownload::GetInstance()->DoCreate(db);

		//存入下载数据
		for (int i = 0; i < downloadList->size(); i++) {
			CMCourseInfo *item = downloadList->at(i);
			CMCourseDownload::GetInstance()->DoPutItem(NULL, db, *item);
		}
	}

	return ret;

}
/**
 *	删除此db的所有表
 *
 *	@param	db	db指针
 *
 *	@return
 */
bool CMDBHelper::DeleteAllTables(sqlite3* db) {
	BOOL ret = FALSE;
	char query[512];

	sqlite3_stmt *stmt;

	//查询所有表
	snprintf(query, 512,
			"SELECT  name FROM sqlite_master WHERE type='table' AND name <> 'sqlite_sequence' ORDER BY name;");

	CMList<char*>* deleteTables = new CMList<char*>();

	if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			char* tablename = new char[64];
			memset(tablename, 0, 64);
			utf8ncpy(tablename, (const char*) sqlite3_column_text(stmt, 0), 63);

			deleteTables->push_back(tablename);
		}
	}
	sqlite3_finalize(stmt);

	char *errorMsg;


//	sqlite3_close(db);
//
//	db = NULL;
//
//	db = pTHIS->GetConnection();

	memset(query, 0, 512);

    if (sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", NULL, NULL,
                     &errorMsg) != SQLITE_OK) {
		CM_ERRP("Failed to begin transaction: %s", errorMsg);
	}

    
	//删除所有表
	for (int i = 0; i < deleteTables->size(); i++) {
		memset(query, 0, 512);

		snprintf(query, 512, "DROP TABLE %s;", deleteTables->at(i));
		CM_ERRP("sql %s ", query);
		//
		if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK) {

			CM_ERRP("Table update failed, err:%s ", errorMsg);
			CM_ERRP("Table  %s ", deleteTables->at(i));

		} else {
			CM_ERR("ok!");

			ret = TRUE;
		}

	}
    
    if (sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL,
                     &errorMsg) != SQLITE_OK) {
		CM_ERRP("Failed to commit transaction: %s", errorMsg);
	}
    
	for (int i = 0; i < deleteTables->size(); i++) {

		SAFEDELETE(deleteTables->at(i));
	}

	SAFEDELETE(deleteTables);
	return ret;
}

int CMDBHelper::GetVersion(sqlite3* db) {

	static const char *query = "PRAGMA user_version;";
	sqlite3_stmt *stmt;
	int ret = 0;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
		int returnCode = sqlite3_step(stmt);
		if (returnCode == SQLITE_ROW || returnCode == SQLITE_DONE) {
			ret = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("Failed to prepare statement: %s", sqlite3_errmsg(db));
	}
	return ret;
}

void CMDBHelper::SetVersion(sqlite3* db, int version) {
    
    char* errorMsg;
    
    if (sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", NULL, NULL,
                     &errorMsg) != SQLITE_OK) {
        CM_ERRP("Failed to begin transaction: %s", errorMsg);
    }
	char query[64];
	snprintf(query, 64, "PRAGMA user_version = %d;", version);
	if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK) {
		CM_ERRP("PRAGMA user_version = %d failed: %s", version, errorMsg);
	}
    
    
    if (sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL,
                     &errorMsg) != SQLITE_OK) {
        CM_ERRP("Failed to commit transaction: %s", errorMsg);
    }
}

BOOL CMDBHelper::CreateCacheTable(sqlite3* db)
{
    char *errorMsg;
    char sql[512];
    sql[0] = '\0';

    snprintf(sql, 512,"CREATE TABLE IF NOT EXISTS %s(tablename TEXT, cache TEXT, time TEXT, PRIMARY KEY (tablename, cache) )","cacheinfo");

    if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK)
    {
        return TRUE;
    }
    else
    {
        CM_ERRP("exec %s failed error = %s",sql,errorMsg);
        return FALSE;
    }
}

bool CMDBHelper::ClearCacheTable()
{
    char query[128];
    snprintf(query, 128,
             "DELETE FROM cacheinfo;");
    char *errorMsg;
    if (sqlite3_exec(db, query, NULL, NULL, &errorMsg) != SQLITE_OK) {
        CM_ERRP("Table update failed, err: ", errorMsg);
        return false;
    }
    return true;
    
}

