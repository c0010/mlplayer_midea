// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcoursedownload.h"
#include "cmcourseinfo.h"
#include "cmlist.h"
#include "cmdownloader.h"
#include "cmfile.h"
#include "cmpath.h"
#include "cmglobal.h"
#include "cmgeneral.h"
#include "cmcontenthandler.h"
static CMMutex g_mutex;

bool CMCourseDownload::ISRUNNING = true;

CMCourseDownload *CMCourseDownload::m_pTHIS = NULL;

CMCourseDownload* CMCourseDownload::GetInstance() {
	if (m_pTHIS == NULL) {
		g_mutex.Lock();

		if (m_pTHIS != NULL) {
			g_mutex.UnLock();
			return m_pTHIS;
		}

		m_pTHIS = new CMCourseDownload();

		g_mutex.UnLock();

	}
	return m_pTHIS;
}

CMCourseDownload::CMCourseDownload() {
	CMCourseDownload::ISRUNNING = true;
	isDoingUnzip = false;
	m_lstItem = NULL;
	m_pDownloader = new CMDownloader(this);
	m_pDownloader->SetProgress(TRUE);

	m_nCourseIndex = -1;
	m_nCoursewareIndex = -1;
	m_pUpdateListener = NULL;

	memset(m_tablename, 0, 64);

	snprintf(m_tablename, 64, "download_class");

	memset(m_SubTablename, 0, 64);

	snprintf(m_SubTablename, 64, "download_courseware");
	m_pt = 0;

}

CMCourseDownload::~CMCourseDownload() {

	CMCourseDownload::ISRUNNING = false;

	m_pUpdateListener = NULL;

#if defined(PLAT_IOS)
	SAFEDELETE(m_pDownloadIos);
#endif

	SAFEDELETE(m_pDownloader);
	SAFEDELETE(m_lstItem);

}

void CMCourseDownload::SetUserData(void* userdata) {
	m_UserData = userdata;
}

void CMCourseDownload::SetListener(IMUpdateDataListener* pListener) {
	m_pUpdateListener = pListener;
}

void CMCourseDownload::Release() {
	SAFEDELETE(m_pTHIS);
}

int CMCourseDownload::Append(const CMCourseInfo& course) {
	INT32 nIndex = -1;

	if (!m_lstItem)
		m_lstItem = new CMList<CMCourseInfo>;

	if (m_lstItem) {
		nIndex = m_lstItem->indexOf(course);

		if (nIndex == -1) {
			//下载列表没有此课程
			m_lstItem->push_back(course);

			sqlite3* db = CheckTable();
			DoPutItem(NULL, db, (CMCourseInfo&) course);

			nIndex = m_lstItem->size() - 1;
			Start(nIndex);
		} else {

			BOOL ret = FALSE;

			//得到旧数据
			CMCourseInfo temp = m_lstItem->at(nIndex);

			//若课程已经下载，检查课程的课件是否有修改
			for (int i = 0; i < course.CoursewareCount(); i++) {
				TCoursewareItem item;

				course.GetCourseware(i, item);

				//检查有无此课件
				int subIndex = -1;
				subIndex = temp.m_lstItem->indexOf(item);

				//若没有此课件
				if (subIndex == -1) {
					ret = TRUE;
					break;
				}

			}
			//已经下载的课件列表和要加入下载的课程的课件列表不同(若课程删除了课件，则不管，只添加新添加的课件)
			if (ret) {
				//删除整个课程重新下载
				Delete(nIndex);

				//重新加入下载
				Append(course);

			}

		}
	}

	return nIndex;
}

void CMCourseDownload::Delete(int nCourseIndex) {
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		TClassItem item;
		m_lstItem->at(nCourseIndex).GetClassItem(item);

		if (m_nCourseIndex != -1) {
			if (nCourseIndex == m_nCourseIndex) {
				Stop();
				DoDelete(item);
                m_pDownloader->SetStatusCompleded();
				m_lstItem->removeAt(nCourseIndex);
				Start(nCourseIndex);
			} else if (nCourseIndex < m_nCourseIndex) {

				DoDelete(item);
				m_lstItem->removeAt(nCourseIndex);
				m_nCourseIndex--;
			} else {
				DoDelete(item);
				m_lstItem->removeAt(nCourseIndex);
			}
		} else {
			DoDelete(item);

			m_lstItem->removeAt(nCourseIndex);
		}
		//		SaveToFile();
	}
}

BOOL CMCourseDownload::Start(int nCourseIndex) {
	CMCourseInfo& info = m_lstItem->at(nCourseIndex);

	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		CMDownloader::STATUS status = m_pDownloader->GetStatus();

		if (status == CMDownloader::RUNNING || isDoingUnzip == true) {
			return TRUE;
		}

		//找到需要开始下载||继续下载||继续解压的课件
		m_nCoursewareIndex = -1;
		INT32 nCount = info.CoursewareCount();
		if (nCount == 0)
			return FALSE;
		for (int i = 0; i < nCount; i++) {
			INT32 nCheck = info.GetCoursewareFlag(i);
			bool bDecompressed = (info.m_lstItem->at(i)).bDecompressed;

			//找到还未下载完和下载完还未解压完的第一个课件
			if (nCheck == 1 || (nCheck == 2 && bDecompressed == false)) {
				m_nCoursewareIndex = i;
				break;
			}
		}
		if (m_nCoursewareIndex == -1) {
			return FALSE;
		}

		TCoursewareItem item;
		info.GetCourseware(m_nCoursewareIndex, item);

		if (status == CMDownloader::PAUSED || status == CMDownloader::STOPED) {
			if (m_nCourseIndex >= 0 && nCourseIndex == m_nCourseIndex) {
				if (item.nCheckStatus == 1) {
					//未下载完则继续下载
					m_pDownloader->Resume();
					return TRUE;
				}

			}
		}

		m_nCourseIndex = nCourseIndex;

		if (item.nCheckStatus == 1) {
			//未下载完则继续下载
			CMGeneral * pGeneral = new CMGeneral();

			m_pDownloader->Download(
					pGeneral->FormatUrlBySID(item.sDownloadUrl));

			delete pGeneral;
			return TRUE;
		}

		if (item.nCheckStatus == 2 && item.bDecompressed == false) {
			//已下载完但还未压缩
			UnzipCourseware(m_nCourseIndex, m_nCoursewareIndex);
			return TRUE;
		}

		return FALSE;

	}

	return FALSE;
}

void CMCourseDownload::Stop() {
	if (m_nCourseIndex != -1) {
		if (m_pDownloader != NULL) {
			m_pDownloader->Cancel();
		}
	}
}

void CMCourseDownload::CheckCourseware(int nCourseIndex, int nCoursewareIndex) {
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		CMCourseInfo& info = m_lstItem->at(nCourseIndex);
		if (info.GetCoursewareFlag(nCoursewareIndex) == 0) {
			info.SetCoursewareFlag(nCoursewareIndex, 1);
			if (m_lstItem && nCoursewareIndex >= 0
					&& nCoursewareIndex < m_lstItem->size())
				DoUpdate(info.m_lstItem->at(nCoursewareIndex));
			//            SaveToFile();
		}
	}
}

void CMCourseDownload::UnCheckCourseware(int nCourseIndex,
		int nCoursewareIndex) {
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		CMCourseInfo& info = m_lstItem->at(nCourseIndex);
		if (info.GetCoursewareFlag(nCoursewareIndex) == 1) {
			info.SetCoursewareFlag(nCoursewareIndex, 0);
			if (m_lstItem && nCoursewareIndex >= 0
					&& nCoursewareIndex < m_lstItem->size())
				DoUpdate(info.m_lstItem->at(nCoursewareIndex));

			//            SaveToFile();

		}
	}
}

int CMCourseDownload::Status(int nCourseIndex) {
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		const CMCourseInfo& info = m_lstItem->at(nCourseIndex);

		if (info.m_nStatus == 2) {

			return EStatusComplete;
		}

		if (m_nCourseIndex == nCourseIndex) {

			if (m_pDownloader != NULL) {
				CMDownloader::STATUS status = m_pDownloader->GetStatus();

				if (status == CMDownloader::RUNNING || isDoingUnzip == TRUE) {
					return EStatusDownloading;
				} else {
					return EStatusPauseDownload;
				}
			} else
				return EStatusPauseDownload;
		} else {
			//in list
			return EStatusInDownloadList;
		}
	}
	return EStatusError;
}

int CMCourseDownload::GetCurrent() {
	return m_nCourseIndex;
}

BOOL CMCourseDownload::DoRefresh(CMCourseInfo& obj) {
	if (strlen(m_tablename) == 0)
		return FALSE;

	if (strlen(obj.m_pClassItem->sID))
		return FALSE;

	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db = CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;

	snprintf(sql, 1024, "SELECT * FROM %s WHERE id = ?", m_tablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, obj.m_pClassItem->sID);

		if (sqlite3_step(stmt) == SQLITE_ROW) {
			obj.m_pClassItem->fetchItem(stmt);
		} else {
			CM_ERRP("sqlite3_prepare_v2 %s failed.error:%s", sql,
					sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	m_mutex.Lock();

	for (int i = 0; i < m_lstItem->size(); i++) {
		CMCourseInfo courseitem = m_lstItem->at(i);

		TClassItem item;
		courseitem.GetClassItem(item);
		if (strcmp(item.sID, obj.m_pClassItem->sID) == 0) {
			item = *obj.m_pClassItem;
			ret = TRUE;
			CM_ERRP("DoRefresh %s success ", item.sID);
			break;
		}
	}
	m_mutex.UnLock();
	return ret;
}

BOOL CMCourseDownload::DoGetCacheItems(sqlite3* db) {

	if (strlen(m_tablename) == 0)
		return FALSE;

	m_mutex.Lock();
	if (m_lstItem)
		m_lstItem->clear();
	m_mutex.UnLock();

	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	CMCourseInfo item;
	memset(sql, 0, 1024);

	snprintf(sql, 1024,
			"SELECT main.*,  sub.status FROM %s AS sub  LEFT JOIN %s AS main ON sub.id = main.id  ",
			m_tablename, kCourseTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		while (sqlite3_step(stmt) == SQLITE_ROW) {

			ret = TRUE;

			((CMCourseInfo&) item).m_pClassItem->fetchItem(stmt);

			item.m_nStatus = sqlite3_column_int(stmt, kDbColumnIndex + 1);

			//sqlite3_stmt *newstmt

			DoGetCacheCourseware(db, item);

			m_mutex.Lock();

			if (!m_lstItem)
				m_lstItem = new CMList<CMCourseInfo>;

			m_lstItem->push_back(item);
			m_mutex.UnLock();

		}

		sqlite3_finalize(stmt);

		if (ret) {
			m_nTotalCount = 0;
			snprintf(sql, 1024, "SELECT COUNT(*) FROM %s ", m_tablename);
			if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
				if (sqlite3_step(stmt) == SQLITE_ROW) {
					m_nTotalCount = sqlite3_column_int(stmt, 0);
				}

			}
            sqlite3_finalize(stmt);
		}

		//sqlite3_finalize(stmt);

		ret = TRUE;
	}
	return ret;
}
BOOL CMCourseDownload::DoGetCacheCourseware(sqlite3* db, CMCourseInfo& item) {
	if (strlen(m_SubTablename) == 0)
		return FALSE;

	m_mutex.Lock();
	item.m_lstItem->clear();
	m_mutex.UnLock();

	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	snprintf(sql, 1024,
			"SELECT main.*,  sub.checkstatus, sub.decompressed, sub.entryfilepath, sub.localfilepath FROM %s AS sub  LEFT JOIN %s AS main ON sub.id = main.id WHERE main.setid = ?  ",
			m_SubTablename, kCourseTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		BindParam(stmt, 1, item.m_pClassItem->sID);

		while (sqlite3_step(stmt) == SQLITE_ROW) {

			TCoursewareItem courseware;

			((TCoursewareItem&) courseware).fetchItem(stmt);

			((TCoursewareItem&) courseware).nCheckStatus = sqlite3_column_int(
					stmt, kDbColumnIndex + 1);

			((TCoursewareItem&) courseware).bDecompressed = sqlite3_column_int(
					stmt, kDbColumnIndex + 2);

			utf8ncpy(((TCoursewareItem&) courseware).sEntryFilePath,
					(const char*) sqlite3_column_text(stmt, kDbColumnIndex + 3),
					299);

			utf8ncpy(((TCoursewareItem&) courseware).sLocalFilePath,
					(const char*) sqlite3_column_text(stmt, kDbColumnIndex + 4),
					299);

			m_mutex.Lock();

			if (!item.m_lstItem)
				item.m_lstItem = new CMList<TCoursewareItem>;

			item.m_lstItem->push_back(courseware);
			m_mutex.UnLock();

		}

		if (ret) {
			item.m_nTotalCount = 0;
			snprintf(sql, 1024, "SELECT COUNT(*) FROM %s ", m_SubTablename);
			if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
				if (sqlite3_step(stmt) == SQLITE_ROW) {
					item.m_nTotalCount = sqlite3_column_int(stmt, 0);
				}

				sqlite3_finalize(stmt);
			}
		}

		sqlite3_finalize(stmt);

		ret = TRUE;
	}
	return ret;
}

BOOL CMCourseDownload::DoCreate(sqlite3* db) {
	BOOL ret = FALSE;

	char *errorMsg = NULL;
	char sql[1024];

	if (strlen(m_tablename) == 0)
		return FALSE;

	snprintf(sql, 1024,
			"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,status INTEGER)",
			m_tablename);

	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK) {
		ret = TRUE;
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}

	memset(sql, 0, 1024);

	if (strlen(m_SubTablename) == 0)
		return FALSE;

	snprintf(sql, 1024,
			"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT, id TEXT UNIQUE, checkstatus INTEGER, setid TEXT ,decompressed INTEGER, entryfilepath TEXT, localfilepath TEXT)",
			m_SubTablename);

	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK) {
		return ret;
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
}

BOOL CMCourseDownload::DoPutItem(TiXmlElement* pItem, sqlite3* db,
		CMCourseInfo& item) {
	if (!db)
		return FALSE;

	if (!m_tablename)
		return FALSE;

	char* errorMsg;

	if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0, 0, &errorMsg) != SQLITE_OK) {
		CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
	}

	CHAR sql[1024];

	BOOL ret = FALSE;

	sqlite3_stmt *stmt;

	snprintf(sql, 1024, "REPLACE INTO %s(id,status) VALUES (?,?)", m_tablename);
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, item.m_pClassItem->sID);

		BindParam(stmt, 2, item.m_nStatus);

		if (sqlite3_step(stmt) == SQLITE_DONE) {
			ret = TRUE;
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	memset(sql, 0, 1024);

	snprintf(sql, 1024,
			"REPLACE INTO %s(id,flag,title,brief,largeimage,image,thumb,type,coursewarecount,url,pubdate,vc,pv,commentcount,enablecomment,enabledownload,enablerating,enableshare,description,tag,specialtopic,credit,studyduration,studyprogress,laststudydate,favoritedate,mycompany,israted,markid,marktitle,model,setid,islearned,downloadurl,markpicurl,orientation,commonstar,mystar,author,language,coursetype,courselevel,developtime,courseversion,starcount) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
			kCourseTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		item.m_pClassItem->bindItem(stmt);

		if (sqlite3_step(stmt) == SQLITE_DONE) {
			for (int i = 0; i < item.GetItemCount(); i++) {

				TCoursewareItem courseware;

				item.GetCourseware(i, courseware);

				utf8ncpy(courseware.sSetID, item.m_pClassItem->sID, 63);

				DoGetCourseware(db, courseware);

			}

			ret = TRUE;
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	if (db != NULL
			&& sqlite3_exec(db, "COMMIT TRANSACTION;", 0, 0, &errorMsg)
					!= SQLITE_OK) {
		CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
	}

	return ret;
}

BOOL CMCourseDownload::DoGetCourseware(sqlite3* db, TCoursewareItem& item) {
	if (!db)
		return FALSE;

	if (!m_SubTablename)
		return FALSE;

	CHAR sql[1024];

	BOOL ret = FALSE;

	sqlite3_stmt *stmt;

	snprintf(sql, 1024,
			"REPLACE INTO %s(id,checkstatus,setid,decompressed,entryfilepath,localfilepath) VALUES (?,?,?,?,?,?) ;",
			m_SubTablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, item.sID);

		BindParam(stmt, 2, item.nCheckStatus);

		BindParam(stmt, 3, item.sSetID);

		BindParam(stmt, 4, item.bDecompressed);

		BindParam(stmt, 5, item.sEntryFilePath);

		BindParam(stmt, 6, item.sLocalFilePath);

		if (sqlite3_step(stmt) == SQLITE_DONE) {
			ret = TRUE;
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	memset(sql, 0, 1024);

	snprintf(sql, 1024,
			"REPLACE INTO %s(id,flag,title,brief,largeimage,image,thumb,type,coursewarecount,url,pubdate,vc,pv,commentcount,enablecomment,enabledownload,enablerating,enableshare,description,tag,specialtopic,credit,studyduration,studyprogress,laststudydate,favoritedate,mycompany,israted,markid,marktitle,model,setid,islearned,downloadurl,markpicurl,orientation) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
			kCourseTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		item.bindItem(stmt);

		if (sqlite3_step(stmt) == SQLITE_DONE) {
			ret = TRUE;

		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return ret;

}

BOOL CMCourseDownload::DoUpdate(const TCoursewareItem& obj) {
	if (strlen(m_SubTablename) == 0)
		return FALSE;

	BOOL ret = FALSE;
	sqlite3*db = CheckTable(m_SubTablename);
	if (db) {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql, 512,
				"UPDATE %s SET checkstatus=?, decompressed=?, entryfilepath=?, localfilepath=? WHERE id=? ",
				m_SubTablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

			BindParam(stmt, 1, ((TCoursewareItem&) obj).nCheckStatus);

			BindParam(stmt, 2, ((TCoursewareItem&) obj).bDecompressed);

			BindParam(stmt, 3, ((TCoursewareItem&) obj).sEntryFilePath);

			BindParam(stmt, 4, ((TCoursewareItem&) obj).sLocalFilePath);

			BindParam(stmt, 5, obj.sID);

			if (sqlite3_step(stmt) == SQLITE_DONE) {
				ret = TRUE;
			} else {
				CM_ERRP("sqlite3_step %s failed.error:%s", sql,
						sqlite3_errmsg(db));
			}
		} else {
			CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	}

	return ret;

}

BOOL CMCourseDownload::DoUpdate(const CMCourseInfo& obj) {
	if (strlen(m_tablename) == 0)
		return FALSE;

	BOOL ret = FALSE;
	sqlite3*db = CheckTable(m_tablename);
	if (db) {
		sqlite3_stmt *stmt;

		CHAR sql[512];

		snprintf(sql, 512, "UPDATE %s SET status=?  WHERE id=? ", m_tablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

			BindParam(stmt, 1, obj.m_nStatus);

			BindParam(stmt, 2, obj.m_pClassItem->sID);

			if (sqlite3_step(stmt) == SQLITE_DONE) {

			} else {
				CM_ERRP("sqlite3_step %s failed.error:%s", sql,
						sqlite3_errmsg(db));
			}
		} else {
			CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	}

	return ret;
}

string CMCourseDownload::GetLocalFilePath(const char* CoursewareID) //得到课件的下载文件的本地路径
		{

	if (CoursewareID == NULL || strlen(CoursewareID) == 0)
		return string("");

	if (strlen(m_tablename) == 0)
		return string("");

	string ret = "";

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db = CheckTable(m_SubTablename);

	if (db == NULL)
		return string("");

	snprintf(sql, 1024, "SELECT localfilepath FROM %s WHERE id = ?",
			m_SubTablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, CoursewareID);

		while (sqlite3_step(stmt) == SQLITE_ROW
				|| sqlite3_step(stmt) == SQLITE_DONE) {

			CMPath downloadPath(CMPath::DOWNLOAD_PATH);

			string tempPath((const char*) (CMString) downloadPath.String());

			tempPath.append((const char*) sqlite3_column_text(stmt, 0));

			ret = tempPath;

		}

	}
	return ret;
}

void* CMCourseDownload::DoExtractPackage(void* param1) {

	CMCourseDownload * obj = (CMCourseDownload*) param1;
	CMUnzipInfo * info = &(obj->m_pUnipInfo);

	unzFile uf = NULL;
	unz_global_info gi;
	int result;
	int opt_overwrite = 1; //是否覆盖

	uf = unzOpen64(info->src.c_str());

	result = unzGetGlobalInfo(uf, &gi);
	if (result != UNZ_OK || uf == NULL) {
		switch (result) {
		case UNZ_BADZIPFILE:
			CM_ERR("zip file corrupted.");
			break;

		case UNZ_PARAMERROR:
			CM_ERR("wrong path or not a zip file.");
			break;

		default:
			CM_ERR("open zipfile failed!");
			break;
		}
		//若为视频文件，直接返回

#if defined(PLAT_IOS)
		//iphone回调到主线程
		obj->m_pDownloadIos = new CMCourseDownload_Iph(obj);

		obj->m_pDownloadIos->GoOnDownload_iph();
#else
		obj->GoOnDownload();
#endif
		return NULL;
	}

	int err = unzGoToFirstFile(uf);
	if (err != UNZ_OK) {
		CM_ERRP("error %d with zipfile in unzGoToFirstFile\n", err);
		return NULL;
	}

	do {
		//检查是否析构
		if (!CMCourseDownload::ISRUNNING)
			return NULL;

		//建立课件文件夹
		CMPath m_pPath("");
		m_pPath.AddDir(info->dst.c_str());

		err = DoExtractFile(uf, 0, &opt_overwrite, NULL, info->dst.c_str());
		if (err != UNZ_OK)
			break;
		err = unzGoToNextFile(uf);
	} while (err == UNZ_OK);

	if (err != UNZ_END_OF_LIST_OF_FILE) {
		CM_ERRP("error %d with zipfile in unzGoToNextFile\n", err);

		return NULL;
	}
	int ret;

	//检查是否析构
	if (!CMCourseDownload::ISRUNNING)
		return NULL;

	//分析入口html文件地址
	ret = obj->GetEntryFilePathFromZip(obj->m_nCourseIndex,
			obj->m_nCoursewareIndex, info->dst.c_str());

	//解压缩完毕，继续下载
#if defined(PLAT_IOS)
	//iphone回调到主线程
	obj->m_pDownloadIos = new CMCourseDownload_Iph(obj);
	obj->m_pDownloadIos->GoOnDownload_iph();

#else
	obj->GoOnDownload();
#endif

	return NULL;

}

BOOL CMCourseDownload::GetEntryFilePathFromZip(int classIndex,
		int coursewareIndex, const char * dirPath) {
	//解析xml数据，拿到xml中的入口html文件地址

	string path = dirPath;
	path.append("scorm.xml");

	if (!CMFile::FileExist(CMString(path.c_str())))
		return false;

	TiXmlDocument *pNode = new TiXmlDocument(path.c_str());

	if (!pNode)
		return false;

	pNode->LoadFile(TIXML_ENCODING_UTF8);

	TiXmlElement *pRootElement = pNode->RootElement();

	TiXmlElement* pItem = pRootElement->FirstChildElement("item");

	if (pItem) {
		const char *pstr = NULL;

		pstr = pItem->Attribute("href");

		CMCourseInfo& info = m_lstItem->at(m_nCourseIndex);

		TCoursewareItem item;

		if (info.GetCourseware(m_nCoursewareIndex, item)) {
			TCoursewareItem &temp = info.m_lstItem->at(m_nCoursewareIndex);
			utf8ncpy(temp.sEntryFilePath, pstr, 299);

			temp.bDecompressed = TRUE;
		}

	} else {
		SAFEDELETE(pNode);
		return false;
	}

	SAFEDELETE(pNode);

	return true;

}

#define WRITEBUFFERSIZE (8192)

int CMCourseDownload::DoExtractFile(unzFile uf, int opt_extract_without_path,
		int* popt_overwrite, const char *password, const char* dstPath) {
	CMPath m_pPath("");

	unz_file_info64 file_info = { 0 };
	FILE* fout = NULL;
	void* buf = NULL;
	uInt size_buf = WRITEBUFFERSIZE;
	int err = UNZ_OK;
	int errclose = UNZ_OK;
	int skip = 0; //无用

	char filename_inzip[300];
//        char filename_inzip[256] = {0};
	char* filename_withoutpath = NULL;
	const char* write_filename = NULL;
	char* p = NULL;

	err = unzGetCurrentFileInfo64(uf, &file_info, filename_inzip,
			sizeof(filename_inzip), NULL, 0, NULL, 0);

	//拼接路径
	string dstFilename = dstPath;
	dstFilename.append(filename_inzip);

	if (err != UNZ_OK) {
		CM_ERRP("error %d with zipfile in unzGetCurrentFileInfo\n", err);
		return err;
	}

	p = filename_withoutpath = filename_inzip;

	//p往前走，遇到'/'或'\\'则把filename_withoutpath指向后面的内容
	while (*p != 0) {
		if ((*p == '/') || (*p == '\\'))
			filename_withoutpath = p + 1;
		p++;
	}

	/* If zip entry is a directory then create it on disk */
	if (*filename_withoutpath == 0) {
		if (opt_extract_without_path == 0) {
			m_pPath.AddDir(dstFilename.c_str());
		}
		return err;
	}

	buf = (void*) malloc(size_buf);
	if (buf == NULL) {
		CM_ERR("Error allocating memory\n");
		return UNZ_INTERNALERROR;
	}

	err = unzOpenCurrentFilePassword(uf, password);
	if (err != UNZ_OK)
		CM_ERRP("error %d with zipfile in unzOpenCurrentFilePassword\n", err);

	if (opt_extract_without_path)
		write_filename = filename_withoutpath;
	else
		write_filename = dstFilename.c_str();

	/* Create the file on disk so we can unzip to it */
	if ((skip == 0) && (err == UNZ_OK)) {

		fout = fopen(write_filename, "wb");
		/* Some zips don't contain directory alone before file */
		if ((fout == NULL) && (opt_extract_without_path == 0)
				&& (filename_withoutpath != (char*) filename_inzip)) {
			char c = *(filename_withoutpath - 1);
			*(filename_withoutpath - 1) = 0;

			string temp = write_filename;

			size_t index = temp.rfind("/");

			if(index != string::npos){
				temp = temp.substr(0,index);
			}
			m_pPath.AddDir(temp.c_str());
			*(filename_withoutpath - 1) = c;
			fout = fopen(write_filename, "wb");
		}
		if (fout == NULL)
			CM_ERRP("error opening %s;the errno:%d \n", write_filename,errno);
	}

	/* Read from the zip, unzip to buffer, and write to disk */
	if (fout != NULL) {
		do {
			err = unzReadCurrentFile(uf, buf, size_buf);
			if (err < 0) {
				CM_ERRP("error %d with zipfile in unzReadCurrentFile\n", err);
				break;
			}
			if (err == 0)
				break;
			if (fwrite(buf, err, 1, fout) != 1) {
				CM_ERRP("error %d in writing extracted file\n", errno);
				err = UNZ_ERRNO;
				break;
			}
		} while (err > 0);

		if (fout)
			fclose(fout);

		/* Set the time of the file that has been unzipped */
//            if (err == 0)
//                change_file_date(write_filename,file_info.dosDate, file_info.tmu_date);
	}

	errclose = unzCloseCurrentFile(uf);
	if (errclose != UNZ_OK)
		CM_ERRP("error %d with zipfile in unzCloseCurrentFile\n", errclose);

	free(buf);
	return err;
}

BOOL CMCourseDownload::isComplete(int nCourseIndex, int nCoursewareIndex) {
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		CMCourseInfo& info = m_lstItem->at(nCourseIndex);
		if (nCoursewareIndex >= info.CoursewareCount() || nCoursewareIndex < 0)
			return FALSE;
		TCoursewareItem item;
		if (info.GetCourseware(nCoursewareIndex, item)) {

			if (item.nCheckStatus == 2 && item.bDecompressed == true) {
				return true;
			} else
				return false;

		}
	}

	return FALSE;
}

const char* CMCourseDownload::GetStatusText(int nCourseIndex) {
	m_sStatusText[0] = '\0';
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		CMCourseInfo& info = m_lstItem->at(nCourseIndex);
		if (info.m_nStatus == 2) {
			CMFile f;
			int len = 0;
			for (int i = 0; i < info.CoursewareCount(); i++) {
				TCoursewareItem item;
				info.GetCourseware(i, item);

				//拼接地址
				CMPath downloadPath(CMPath::DOWNLOAD_PATH);

				CMString path = downloadPath.String()
						+ CMString(item.sLocalFilePath);

				f.Open(path);

				len += f.GetLength();
				f.Close();
			}
			snprintf(m_sStatusText, 128, "%dKB", len / 1024);
		} else if (m_nCourseIndex == nCourseIndex) {
			CMDownloader::STATUS status = m_pDownloader->GetStatus();
			const TDownloadInfo& downInfo = m_pDownloader->GetCurrentInfo();
			if (status == CMDownloader::RUNNING) {
				snprintf(m_sStatusText, 128, "%dKB/%dKB %.2fKB/s",
						downInfo.nDowned / 1024, downInfo.nSize / 1024,
						downInfo.nCurSpd / 1024.0);
			} else if (status == CMDownloader::PAUSED
					|| status == CMDownloader::STOPED) {
				snprintf(m_sStatusText, 128, "%dKB/%dKB",
						downInfo.nDowned / 1024, downInfo.nSize / 1024);
			}
		} else {
			utf8ncpy(m_sStatusText, " ", 127);
		}
	}
	return m_sStatusText;
}

const char* CMCourseDownload::GetStatusText(int nCourseIndex,
		int nCoursewareIndex) {
	m_sStatusText[0] = '\0';
	if (m_lstItem && nCourseIndex >= 0 && nCourseIndex < m_lstItem->size()) {
		CMCourseInfo& info = m_lstItem->at(nCourseIndex);

		if (info.GetCoursewareFlag(nCoursewareIndex) == 2) {
			CMFile f;
			TCoursewareItem item;

			if (info.GetCourseware(nCoursewareIndex, item)) {

				//拼接地址
				CMPath downloadPath(CMPath::DOWNLOAD_PATH);

				CMString path = downloadPath.String()
						+ CMString(item.sLocalFilePath);

				f.Open(path);

			}

			snprintf(m_sStatusText, 128, "%dKB", f.GetLength() / 1024);
			f.Close();
		} else if (m_nCourseIndex == nCourseIndex
				&& m_nCoursewareIndex == nCoursewareIndex) {
			CMDownloader::STATUS status = m_pDownloader->GetStatus();
			const TDownloadInfo& downInfo = m_pDownloader->GetCurrentInfo();
			if (status == CMDownloader::RUNNING) {
				snprintf(m_sStatusText, 128, "%dKB/%dKB %.2fkb/s",
						downInfo.nDowned / 1024, downInfo.nSize / 1024,
						downInfo.nCurSpd / 1024.0);
			} else if (status == CMDownloader::PAUSED
					|| status == CMDownloader::STOPED) {
				snprintf(m_sStatusText, 128, "%dKB/%dKB",
						downInfo.nDowned / 1024, downInfo.nSize / 1024);
			}
		} else {
			utf8ncpy(m_sStatusText, " ", 127);
		}
	}
	return m_sStatusText;
}

void CMCourseDownload::OnProgress(unsigned int nRate) {
	if (m_pUpdateListener)
		m_pUpdateListener->OnUpdateDataProgress(m_UserData, nRate);
}

BOOL CMCourseDownload::DoDelete(const TClassItem& obj) {
	BOOL ret = FALSE;

	if (strlen(m_tablename) == 0)
		return FALSE;
	if (strlen(m_SubTablename) == 0)
		return FALSE;

	sqlite3* db = CheckTable();

	if (db != NULL) {
		CHAR sql[1024];
		sql[0] = '\0';
		sqlite3_stmt *stmt;

		snprintf(sql, 1024, "DELETE FROM %s WHERE id = ? ; ", m_tablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

			BindParam(stmt, 1, obj.sID);

			if (sqlite3_step(stmt) == SQLITE_DONE) {
				ret = TRUE;
			} else {
				ret = FALSE;
			}

		} else
		CM_ERR("fail ");

		sqlite3_reset(stmt);

		memset(sql, 0, 1024);

		sqlite3_finalize(stmt);

		if (ret == FALSE)
			return FALSE;

		snprintf(sql, 1024, "DELETE FROM %s WHERE setid = ? ;", m_SubTablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

			BindParam(stmt, 1, obj.sID);

			if (sqlite3_step(stmt) == SQLITE_DONE) {
				ret = TRUE;
			} else {
				ret = FALSE;
			}
		} else
		CM_ERR("fail");

		sqlite3_finalize(stmt);
		return ret;

	}
	return ret;
}

void CMCourseDownload::GoOnDownload() {

	isDoingUnzip = FALSE;

	CMCourseInfo& info = m_lstItem->at(m_nCourseIndex);
	//课程状态变为下载中
	if (info.m_nStatus == 0)
		info.m_nStatus = 1;
	DoUpdate(info);

	if (info.m_lstItem && m_nCoursewareIndex >= 0
			&& m_nCoursewareIndex < info.m_lstItem->size()) {
		DoUpdate(info.m_lstItem->at(m_nCoursewareIndex));
	}

	//指向下一个课件
	m_nCoursewareIndex++;

	if (m_nCoursewareIndex < info.CoursewareCount()) {
		//若下载的课件不是最后一个，则继续下载下一个
		TCoursewareItem item;
		info.GetCourseware(m_nCoursewareIndex, item);
		CMGeneral * pGeneral = new CMGeneral();

		m_pDownloader->Download(pGeneral->FormatUrlBySID(item.sDownloadUrl));

		delete pGeneral;
	} else {
		//课程的全部课件下载完成
		info.m_nStatus = 2;
		DoUpdate(info);

		if (m_nCourseIndex < m_lstItem->size() - 1) {
			m_nCourseIndex++;
			Start(m_nCourseIndex);
		} else {
			m_nCourseIndex = -1;
			m_nCoursewareIndex = -1;
		}
	}

	if (m_pUpdateListener)
		m_pUpdateListener->OnUpdateDataFinish(m_UserData, 1);

}
void CMCourseDownload::UnzipCourseware(int classIndex, int coursewareIndex) {

	CMCourseInfo& info = m_lstItem->at(classIndex);

	//解压缩
	TCoursewareItem &item = info.m_lstItem->at(coursewareIndex);

	if (info.GetCourseware(coursewareIndex, item)) {

		CMString sUrl = CMString(item.sDownloadUrl);

		CMPath srcPath(CMPath::DOWNLOAD_PATH);
		CMPath dstPath(CMPath::UNZIP_PATH);

		CMString sOrgUrl;
		INT32 pos = sUrl.ReverseFind(L"?sid=");

		if (pos < 0)
			pos = sUrl.ReverseFind(L"&sid=");
		if (pos > 0)
			sOrgUrl = sUrl.Left(pos);
		else
			sOrgUrl = sUrl;

		//拼接压缩包地址
		string src = (const char*) (CMString&) srcPath.String();
		src.append(CMFile::GetTempFileName(sOrgUrl, ""));

		//写入文件地址
		utf8ncpy(item.sLocalFilePath, CMFile::GetTempFileName(sOrgUrl, ""),
				299);
		DoUpdate(item);

		//拼接解压缩地址
		string dst = (const char*) (CMString&) dstPath.String();
		dst.append(CMString(item.sID));
		dst.append("/");

		m_pUnipInfo.src = src;
		m_pUnipInfo.dst = dst;

		pthread_create(&m_pt, NULL, DoExtractPackage, this);

	}

}

void CMCourseDownload::OnDownload(unsigned int nCode,
		CMDownloader* pDownloader) {
	if (nCode == MER_OK)

	{
		CMCourseInfo& info = m_lstItem->at(m_nCourseIndex);
		//课程状态变为下载中
		if (info.m_nStatus == 0)
			info.m_nStatus = 1;
		DoUpdate(info);

		//标记课件下载完成
		info.SetCoursewareFlag(m_nCoursewareIndex, 2);

		int temp = m_nCoursewareIndex;

		if (info.m_lstItem && temp >= 0 && temp < info.m_lstItem->size()) {

			//下载完毕状态保存入数据库
			DoUpdate(info.m_lstItem->at(temp));
		}

		isDoingUnzip = true;
		//开始解压缩
		UnzipCourseware(m_nCourseIndex, m_nCoursewareIndex);

	}

	return;

}

void CMCourseDownload::SaveToFile() {
	if (m_lstItem) {
		TiXmlDocument *pDoc = new TiXmlDocument(
				CMGlobal::TheOne().GetUserDir() + L"coursedownload.xml");
		if (pDoc) {
			pDoc->LoadFile(TIXML_ENCODING_UTF8);
			if (!pDoc->Error()) {
				TiXmlElement *pRoot = pDoc->RootElement();
				if (pRoot) {
					pRoot->Clear();
					for (int i = 0; i < m_lstItem->size(); i++) {
						CMCourseInfo& bItem = m_lstItem->at(i);
						pRoot->LinkEndChild(bItem.CreateXmlElement());
					}
					pDoc->SaveFile();
				}
			}
			SAFEDELETE(pDoc);
		}
	}
}

void CMCourseDownload::LoadFromFile() {

	sqlite3* db = CheckTable();
	if (db != NULL) {
		DoCreate(db);

		if (DoGetCacheItems(db)) {

		}

	}

}

BOOL CMCourseDownload::IsDonwloaded(const TCoursewareItem& item) {
	for (int i = 0; i < GetItemCount(); i++) {
		CMCourseInfo citem;
		if (GetItem(i, citem)) {
			int pos = citem.HaveCourseware(item);
			TCoursewareItem tempCourseware;

			if (pos >= 0) {
				citem.GetCourseware(pos, tempCourseware);

				if (tempCourseware.nCheckStatus == 2)
					return TRUE;
				else
					return FALSE;

			}

		}
	}

	return FALSE;
}

