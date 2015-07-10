// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmcategory.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "cmfile.h"
#include "utf8ncpy.h"
#include "cmundone.h"

CMCategory* CMCategory::m_pTHIS = NULL;

CMCategory* CMCategory::GetInstance() {
	if (m_pTHIS == NULL)
		m_pTHIS = new CMCategory();
	return m_pTHIS;
}

CMCategory::CMCategory() :
		CMHandler<CMCategoryItem*>() {

}

CMCategory::~CMCategory() {
}

void CMCategory::SetListener(IMUpdateDataListener* pListener) {
	m_pListener = pListener;
}

void CMCategory::ClearTree(CMList<CMCategoryItem*>* plist) {
	for (CMList<CMCategoryItem*>::iterator i = plist->begin(); i < plist->end();
			i++) {
		CMCategoryItem *p = (CMCategoryItem*) *i;
		if (p->m_lstItem) {
			if (p->m_lstItem->size() > 0)
				ClearTree(p->m_lstItem);
			else {
				delete p;
				p = NULL;
			}
		}
	}
	plist->clear();
}

BOOL CMCategory::UpdateData() {

	if (IsRunning())
		return FALSE;
	SetPaging(FALSE);
	char param[64];
	param[0] = '\0';
	snprintf(m_tablename, 64, "category");
	SetRequestType(1);

	return Request(SERVICE_GETCATEGORYLIST, param);
}

BOOL CMCategory::UpdateCategoryList() {

	if (IsRunning())
		return FALSE;
	SetPaging(FALSE);
	char param[64];
	param[0] = '\0';
	snprintf(m_tablename, 64, "category");
	SetRequestType(0);

	return Request(SERVICE_UPDATECATEGORYLIST, param);
}

BOOL CMCategory::GetCacheData() {
	snprintf(m_tablename, 64, "category");
	sqlite3* db = CheckTable();
	if (db != NULL) {
		return DoGetCacheItems(db);
	}
	return TRUE;
}

int CMCategory::TopItemCount() {
	if (!m_lstItem)
		return 0;
	return m_lstItem->size();
}

CMCategoryItem* CMCategory::GetTopItem(int nIndex) {
	if (!m_lstItem)
		return NULL;
	if (nIndex >= 0 && nIndex < m_lstItem->size())
		return m_lstItem->at(nIndex);
	else
		return NULL;
}

void CMCategory::OnSessionCmd(unsigned int nCmdID, unsigned int nCode,
		TiXmlDocument* pDoc) {
	INT32 result = TResult::EUnknownError;
	if (nCode == MER_OK) {
		TiXmlElement *pItem = pDoc->RootElement();

		INT32 nErr = -1;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no", &nCmdID);

		if (m_bPaging) {
			pItem->QueryIntAttribute("totalcount", &m_nTotalCount);
			pItem->QueryIntAttribute("pageno", &m_nPageNo);

			int count = m_nTotalCount / m_nPageSize;
			if (m_nTotalCount % m_nPageSize > 0)
				count++;
			m_bEnd = (m_nPageNo >= count);
		}
		pItem->QueryIntAttribute("errno", &nErr);
		if (nErr == 0) {

			if (!pItem->NoChildren()) {
				sqlite3* db = CheckTable(m_tablename);

				CHAR sql[1024];
				sql[0] = '\0';
				char* errorMsg;

				if (!m_bPaging || m_nPageNo == 1) {
					m_mutex.Lock();
					ClearTree(m_lstItem);
					m_mutex.UnLock();
				}

				if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0, 0,
						&errorMsg) != SQLITE_OK) {
					CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
				}

				pItem = pItem->FirstChildElement("outline");
				m_mutex.Lock();
				sqlNotin ="(";
				while (pItem) {
					CMCategoryItem* item = new CMCategoryItem();

					if (DoPutItem(pItem, db, item)) {
						m_lstItem->push_back(item);
					} else {
						SAFEDELETE(item);
					}
					pItem = pItem->NextSiblingElement("outline");
				}
				m_mutex.UnLock();

				if (sqlite3_exec(db, "COMMIT TRANSACTION;", 0, 0,
						&errorMsg) != SQLITE_OK) {
					CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
				}
				sqlNotin.erase(sqlNotin.end()-1);
				sqlNotin.append(")");
				UpdateCache();

				//以后再做本地化
				InitSubscription();

				if (GetItemCount() > 0)
					result = TResult::ESuccess;
				else
					result = TResult::ENothing;

			}

		} else
			result = TResult::EUnknownError;
	}
    else {
        
        result = ResultHandle(nCode);

    }
    


	if (m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData, result);
}

CMCategoryItem* CMCategory::GetCategoryItem(const char* sTopID,
		const char* sID) {
	if (sTopID == NULL || sID == NULL)
		return NULL;
	for (int i = 0; i < TopItemCount(); i++) {
		CMCategoryItem* pTopItem = GetTopItem(i);
		if (strcmp(pTopItem->sID, sTopID) == 0) {
			CMCategoryItem* pCategoryItem = pTopItem->GetCategoryItem(sID);
			if (pCategoryItem)
				return pCategoryItem;
		}
	}
	return NULL;
}

void CMCategory::InitSubscription() {
	CMString sPath = CMGlobal::TheOne().GetUserDir() + L"subscription.xml";
	TiXmlDocument *pDoc = new TiXmlDocument(sPath);
	if (!pDoc)
		return;
	if (!CMFile::FileExist(sPath)) {
		pDoc->Parse(
				"<?xml version=\"1.0\" encoding=\"utf-8\" ?><subscription/>",
				NULL, TIXML_ENCODING_UTF8);
		if (!pDoc->Error())
			pDoc->SaveFile();
	} else {
		pDoc->LoadFile(TIXML_ENCODING_UTF8);
		if (!pDoc->Error()) {
			TiXmlElement *pRootElement = pDoc->RootElement();
			if (pRootElement) {
				TiXmlElement* pItem = pRootElement->FirstChildElement(
						"outline");
				while (pItem) {
					CMCategoryItem* pCategoryItem = GetCategoryItem(
							pItem->Attribute("topid"), pItem->Attribute("id"));
					if (pCategoryItem && pCategoryItem->bEnablesubscription) {
						int subscription = 0;
						pItem->QueryIntAttribute("subscription", &subscription);
						pCategoryItem->m_bSubscription = subscription;
					}
					pItem = pItem->NextSiblingElement("outline");
				}
			}
		}
	}
	SAFEDELETE(pDoc);
}

BOOL CMCategory::DoPutItem(TiXmlElement* pItem, sqlite3* db,
		CMCategoryItem*& item) {

	const CHAR *pStr = NULL;

	//id
	pStr = pItem->Attribute("id");
	if (pStr)
		utf8ncpy(item->sID, pStr, 63);
	//type
	pStr = pItem->Attribute("type");
	if (pStr)
		utf8ncpy(item->sType, pStr, 15);
	//title
	pStr = pItem->Attribute("title");
	if (pStr)
		utf8ncpy(item->sTitle, pStr, 99);
	//image
	pStr = pItem->Attribute("image");
	if (pStr)
		utf8ncpy(item->sImage, pStr, 299);

	int enablesubscription = 0;
	pItem->QueryIntAttribute("enablesubscription", &enablesubscription);
	item->bEnablesubscription = enablesubscription;

	pItem->QueryIntAttribute("itemcount", &item->nItemcount);
	if (item->bEnablesubscription && item->nItemcount == 0)
		item->nItemcount = 30; //为RRS订阅；栏目不能即使取得项数而特殊处理


	sqlNotin.append("'");
	sqlNotin.append(item->sID);
	sqlNotin.append("'");
	sqlNotin.append(",");
	DoRefresh(item);

	//如果已经通过 2000 获取到测验，调研内容，更新进数据库
	CMUnDone *pUnDone = CMUnDone::GetInstance();
	if (pUnDone != NULL
			&& (strcasecmp(item->sType, "survey") == 0
					|| strcasecmp(item->sType, "exam") == 0)) {

		int count = pUnDone->GetItemCount();

		for (int i = 0; i < count; i++) {
			TUnDoneItem undoneitem;
			pUnDone->GetItem(i, undoneitem);

			if (strcasecmp(item->sType, undoneitem.sType.c_str()) == 0
					&& undoneitem.nItemCount > 0) {
				item->nItemcount = undoneitem.nItemCount;
			}

		}

	}

	CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql, 1024,
			"Replace INTO %s(id,topid,type,title,image,enablesubscription,itemcount,isselected) VALUES (?,?,?,?,?,?,?,?)",
			m_tablename);
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, item->sID);
		BindParam(stmt, 2, item->m_sTopID);
		BindParam(stmt, 3, item->sType);
		BindParam(stmt, 4, item->sTitle);
		BindParam(stmt, 5, item->sImage);
		BindParam(stmt, 6, item->bEnablesubscription);
		BindParam(stmt, 7, item->nItemcount);
		BindParam(stmt, 8, item->bIsSelected);
		if (sqlite3_step(stmt) == SQLITE_DONE) {
//        	ret = TRUE;
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	pItem = pItem->FirstChildElement("outline");
	while (pItem) {
		CMCategoryItem * pchild = new CMCategoryItem();
		utf8ncpy(pchild->m_sTopID, item->sID, 63);

		if (DoPutItem(pItem, db, pchild)) {
			item->m_lstItem->push_back(pchild);
		}

		pItem = pItem->NextSiblingElement("outline");
	}

	return TRUE;
}

//缓存回来数据，读取缓存到对象列表
BOOL CMCategory::DoGetCacheItems(sqlite3* db) {
	ClearTree(m_lstItem);
	return DoGetCacheTreeItems(db, m_lstItem, "");
}

BOOL CMCategory::DoGetCacheTreeItems(sqlite3* db,
		CMList<CMCategoryItem*>* plist, const char* topid) {
	//保存全部数据
	CMList<CMCategoryItem*> * tempList = new CMList<CMCategoryItem*>;

	BOOL ret = FALSE;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	snprintf(sql, 1024,
			"SELECT id,topid,type,title,image,enablesubscription,itemcount,isselected FROM %s  ORDER BY _id ASC",
			m_tablename);

	//拿出全部数据
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, topid);

		m_mutex.Lock();
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			CMCategoryItem* item = new CMCategoryItem();

			utf8ncpy(item->sID, (const char*) sqlite3_column_text(stmt, 0), 63);

			utf8ncpy(item->m_sTopID, (const char*) sqlite3_column_text(stmt, 1),
					63);

			utf8ncpy(item->sType, (const char*) sqlite3_column_text(stmt, 2),
					15);

			utf8ncpy(item->sTitle, (const char*) sqlite3_column_text(stmt, 3),
					99);

			utf8ncpy(item->sImage, (const char*) sqlite3_column_text(stmt, 4),
					299);

			item->bEnablesubscription = sqlite3_column_int(stmt, 5);

			item->nItemcount = sqlite3_column_int(stmt, 6);

			item->bIsSelected = sqlite3_column_int(stmt, 7);

			tempList->push_back(item);
		}

		m_mutex.UnLock();

		sqlite3_finalize(stmt);
		//若无数据则认为是错误
		if (tempList->size() != 0)
			ret = TRUE;

	}

	for (int i = 0; i < tempList->size(); i++) {
		CMCategoryItem* item = tempList->at(i);
		const char* topid = item->sID;

		//若为根节点，放入list
		if (strcmp(item->m_sTopID, "") == 0) {
			plist->push_back(item);
		}

		//寻找子节点
		for (int j = 0; j < tempList->size(); j++) {
			CMCategoryItem* tempItem = tempList->at(j);

			if (strcmp(topid, tempItem->m_sTopID) == 0)
				item->m_lstItem->push_back(tempItem);
		}
	}

	SAFEDELETE(tempList);

	return ret;

}

BOOL CMCategory::UpdateCache()
{
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	snprintf(sql, 1024,
			"DELETE FROM %s WHERE id NOT IN %s",
			m_tablename,sqlNotin.c_str());


	sqlite3* db = CheckTable();
	if (db == NULL) {

		return FALSE;
	}

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		if (sqlite3_step(stmt) == SQLITE_DONE) {
        	ret = TRUE;
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}
	}else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return ret;

}

BOOL CMCategory::DoRefresh(CMCategoryItem*& obj) {

	BOOL ret = FALSE;

	if(strcmp(m_tablename,"") == 0)
		return FALSE;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3 *db = CheckTable(m_tablename);

	if(db == NULL)
		return FALSE;
	snprintf(sql, 1024,
				"SELECT id,topid,type,title,image,enablesubscription,itemcount,isselected FROM %s  WHERE id = ?",
				m_tablename);

	if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, obj->sID);

		if(sqlite3_step(stmt) == SQLITE_ROW)
		{
			obj->bIsSelected = sqlite3_column_int(stmt, 7);
		}
		sqlite3_finalize(stmt);
		ret = TRUE;
	}else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return ret;
}

void CMCategory::SetExamSurveyCount(int count, const char* type) {



	int p = m_pTHIS->GetItemCount();
	CMCategoryItem* pItem = m_pTHIS->GetTopItem(p - 1);
	for (int i = 0; i < pItem->ChildItemCount(); i++) {
		CMCategoryItem* pChildItem = pItem->GetChildItem(i);
		if (pChildItem != NULL)
			if (strcasecmp(pChildItem->sID, type) == 0) {
				pChildItem->nItemcount = count;
				DoUpdate(pChildItem);
			}
	}
}

BOOL CMCategory::DoUpdate(CMCategoryItem* const &obj) {
	BOOL ret = FALSE;

	sqlite3* db = CheckTable(m_tablename);

	if (db) {
		m_mutex.Lock();

		CHAR sql[1024];
		sqlite3_stmt *stmt;
		snprintf(sql, 1024, "UPDATE %s SET itemcount=?,isselected=?,topid=? WHERE  id=? ",
				m_tablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			BindParam(stmt, 1, obj->nItemcount);
			BindParam(stmt,2,obj->bIsSelected);
			BindParam(stmt, 3,obj->m_sTopID);
			BindParam(stmt, 4, obj->sID);
			if (sqlite3_step(stmt) == SQLITE_DONE) {
				ret = TRUE;
			} else {
				CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
			}
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		m_mutex.UnLock();

		sqlite3_finalize(stmt);
	}
	return ret;
}

BOOL CMCategory::DoCreate(sqlite3* db) {
	char *errorMsg;
	char sql[512];
	snprintf(sql, 1024,
			"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,topid TEXT,type TEXT,title TEXT,image TEXT,enablesubscription INTEGER,itemcount INTEGER,isselected INTEGER)",
			m_tablename);

	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK) {
		return TRUE;
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
}

void CMCategory::DoClear() {
	m_mutex.Lock();
	ClearTree(m_lstItem);
	m_mutex.UnLock();

	sqlite3* db = CheckTable(m_tablename);

	if (db != NULL) {

		CHAR sql[1024];
		sql[0] = '\0';
		char* errorMsg;

		snprintf(sql, 1024, "DELETE FROM %s", m_tablename);

		if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK) {
			CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		}

	}
}

//CMCategoryItem///////////////////////////////////////////////////////
CMCategoryItem::CMCategoryItem() :
		m_lstItem(NULL) {
	memset(sID, 0, 64);

	memset(sType, 0, 16);

	memset(sTitle, 0, 100);

	memset(sImage, 0, 300);

	bEnablesubscription = FALSE;

	nItemcount = 0;

	m_bSubscription = TRUE;

	bIsSelected = TRUE;

	memset(m_sTopID, 0, 64);

	m_lstItem = new CMList<CMCategoryItem*>;
}

CMCategoryItem::~CMCategoryItem() {
}
int CMCategoryItem::FrontChildItemCount() {
	if (m_lstItem == NULL) {
		return 0;
	}

	for (int i = 0; i < m_lstItem->size(); i++) {
		CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
		if (p) {
			if (strcmp(p->sType, "div") == 0)
				return i + 1;
		}
	}

	return m_lstItem->size();
}

int CMCategoryItem::ChildItemCount() {
	if (m_lstItem == NULL) {
		return 0;
	}
	int count = 0;
	for (int i = 0; i < m_lstItem->size(); i++) {
		CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
		if (p && p->GetSubscription())
			count++;
	}
	return count;
}

CMCategoryItem* CMCategoryItem::GetChildItem(int nIndex) {
	if (nIndex >= 0 && nIndex < ChildItemCount()) {
		for (int i = 0; i < m_lstItem->size(); i++) {
			CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
			if (p && p->GetSubscription() && nIndex-- == 0)
				return p;
		}
	}
	return NULL;
}


int CMCategoryItem::SelectedChildItemCount(){
    if (m_lstItem == NULL) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < m_lstItem->size(); i++) {
        CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
        if (p && p->bIsSelected)
            count++;
    }
    return count;
}

CMCategoryItem* CMCategoryItem::GetSelectedChildItem(int nIndex) {
    if (nIndex >= 0 && nIndex < SelectedChildItemCount()) {
        for (int i = 0; i < m_lstItem->size(); i++) {
            CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
            if (p && p->bIsSelected && nIndex-- == 0)
                return p;
        }
    }
    return NULL;
}




int CMCategoryItem::GetPositionCourseItem() {
	for (int i = 0; i < m_lstItem->size(); i++) {
		CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
		if (p && strcmp(p->sID, "9") == 0)
			return i;
	}
	return 0;
}

void CMCategoryItem::RemoveChildItem(int nIndex) {
	if (m_lstItem && nIndex >= 0 && nIndex < ChildItemCount()) {
		m_lstItem->removeAt(nIndex);
	}
}

int CMCategoryItem::EnablesubscriptionChildItemCount() {
	if (m_lstItem == NULL) {
		return 0;
	}
	int count = 0;
	for (int i = 0; i < m_lstItem->size(); i++) {
		CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
		if (p && p->bEnablesubscription)
			count++;
	}
	return count;
}

CMCategoryItem* CMCategoryItem::GetEnablesubscriptionChildItem(int nIndex) {
	if (nIndex >= 0 && nIndex < EnablesubscriptionChildItemCount()) {
		for (int i = 0; i < m_lstItem->size(); i++) {
			CMCategoryItem *p = (CMCategoryItem*) m_lstItem->at(i);
			if (p && p->bEnablesubscription && nIndex-- == 0)
				return p;
		}
	}
	return NULL;
}

BOOL CMCategoryItem::GetSubscription() {
	return m_bSubscription;
}

void CMCategoryItem::SetSubscription(BOOL bFlag) {
	BOOL ret = FALSE;
	if (bEnablesubscription) {
		//创建一个XML的文档对象。
		TiXmlDocument *pFavoritesDoc = new TiXmlDocument(
				CMGlobal::TheOne().GetUserDir() + L"subscription.xml");
		if (pFavoritesDoc)
			ret = pFavoritesDoc->LoadFile(TIXML_ENCODING_UTF8);
		if (ret) {
			TiXmlElement *pRootElement = pFavoritesDoc->RootElement();

			if (pRootElement) {
				BOOL bExist = FALSE;
				TiXmlElement* pItem = pRootElement->FirstChildElement(
						"outline");
				while (pItem) {
					const char* topid = pItem->Attribute("topid");
					const char* id = pItem->Attribute("id");
					if (topid && id && strcmp(topid, m_sTopID) == 0
							&& strcmp(id, sID) == 0) {
						bExist = TRUE;
						pItem->SetAttribute("subscription", (int) bFlag);
						break;
					}
					pItem = pItem->NextSiblingElement("outline");
				}

				if (!bExist) {
					TiXmlElement* pItem = new TiXmlElement("outline");
					pItem->SetAttribute("topid", m_sTopID);
					pItem->SetAttribute("id", sID);
					pItem->SetAttribute("subscription", (int) bFlag);
					pRootElement->LinkEndChild(pItem);
				}
				ret = pFavoritesDoc->SaveFile();
			}
		}
		SAFEDELETE(pFavoritesDoc);
	}
	if (ret)
		m_bSubscription = bFlag;
}

CMCategoryItem* CMCategoryItem::GetCategoryItem(const char* sID) {
	if (m_lstItem == NULL)
		return NULL;

	for (int i = 0; i < m_lstItem->size(); i++) {
		CMCategoryItem* pCategoryItem = m_lstItem->at(i);
		if (pCategoryItem) {
			if (strcmp(pCategoryItem->sID, sID) == 0)
				return pCategoryItem;
			else
				pCategoryItem = pCategoryItem->GetCategoryItem(sID);
			if (pCategoryItem)
				return pCategoryItem;
		}
	}
	return NULL;
}

