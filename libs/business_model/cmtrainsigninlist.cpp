/*
 * cmtrainapplylist.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: Administrator
 */

#include "stdafx.h"
#include "cmtrainsigninlist.h"

#define TABLE_TRAINSIGNIN "train_signin"

TTrainSignInItem::TTrainSignInItem()
{
	nMode = 0;
	nSignInNum = 0;
	m_pSession = NULL;
	m_pListener = NULL;
	m_sListener = NULL;
}

TTrainSignInItem::~TTrainSignInItem()
{
	if(m_pSession)
		m_pSession->Cancel();
}


void TTrainSignInItem::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

void TTrainSignInItem::SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener)
{
	m_pListener = pUpdateDataListener;
	m_sListener = pSimpleResultListener;
}

void TTrainSignInItem::SetUserData(void* userdata)
{
	m_UserData = userdata;
}

TTrainSignInItem& TTrainSignInItem::operator=(const TiXmlElement* right)
{
	const char* pStr = NULL;
	pStr = right->Attribute("id");
	if(pStr)
	{
		sID = pStr;
	}

	pStr = right->Attribute("title");
	if(pStr)
	{
		sTitle = pStr;
	}

	pStr = right->Attribute("trainid");
	if(pStr)
	{
		sTrainID = pStr;
	}

	pStr = right->Attribute("image");
	if(pStr)
	{
		sImageURL = pStr;
	}

	pStr = right->Attribute("time");
	if(pStr)
	{
		sTime = pStr;
	}

	pStr = right->Attribute("address");
	if(pStr)
	{
		sAddress = pStr;
	}

	pStr = right->Attribute("signintime");
	if(pStr)
	{
		sSignInTime = pStr;
	}

	pStr = right->Attribute("flag");
	if(pStr)
	{
		sFlag = pStr;
	}
	right->QueryIntAttribute("mode",&nMode);
	right->QueryIntAttribute("signinnum",&nSignInNum);
}

int TTrainSignInItem::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TTrainSignInItem::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{

    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);

    return sqlite3_bind_null(stmt, col);

}
int TTrainSignInItem::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TTrainSignInItem::bindItem(sqlite3_stmt *stmt) const
{
	sqlite3_bind_text(stmt, 1, sID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 2, sTitle.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 3, sTrainID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 4, sImageURL.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 5, sTime.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 6, sAddress.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 7, sSignInTime.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 8, sFlag.c_str(), -1,NULL);
	sqlite3_bind_int(stmt, 9, nMode);
	sqlite3_bind_int(stmt, 10, nSignInNum);
}

void TTrainSignInItem::fetchItem(sqlite3_stmt *stmt)
{
	sID = (const char*)sqlite3_column_text(stmt, 1);
	sTitle = (const char*)sqlite3_column_text(stmt, 2);
	sTrainID = (const char*)sqlite3_column_text(stmt, 3);
	sImageURL = (const char*)sqlite3_column_text(stmt, 4);
	sTime = (const char*)sqlite3_column_text(stmt, 5);
	sAddress = (const char*)sqlite3_column_text(stmt, 6);
	sSignInTime = (const char*)sqlite3_column_text(stmt, 7);
	sFlag = (const char*)sqlite3_column_text(stmt, 8);
	nMode = sqlite3_column_int(stmt, 9);
	nSignInNum = sqlite3_column_int(stmt, 10);
}

BOOL TTrainSignInItem::RequestInfo()
{
	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	m_bUpdateData = TRUE;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "id=%s",this->sID.c_str());

	m_pSession->Command(SERVICE_TRAINSIGNININFO,sParam);

	return TRUE;
}

BOOL TTrainSignInItem::SignInTrain()
{

	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	m_bUpdateData = FALSE;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "id=%s",this->sID.c_str());

	m_pSession->Command(SERVICE_TRAINSIGNIN,sParam);

}

BOOL TTrainSignInItem::Update()
{

	BOOL ret = FALSE;
	sqlite3*db=CMDBHelper::GetInstance(1)->GetConnection();
	if(db)
	{
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,512,"REPLACE INTO %s(id,title,trainid,image,time,address,signintime,flag,mode,signinnum) VALUES (?,?,?,?,?,?,?,?,?,?)", TABLE_TRAINSIGNIN);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			bindItem(stmt);
			if(sqlite3_step(stmt)==SQLITE_DONE)
			{
				ret = TRUE;
			}
			else {
				CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
			}
		}
		else {
			CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	}

	return ret;

}

BOOL TTrainSignInItem::Refresh()
{
	BOOL ret = FALSE;

	if(strlen(TABLE_TRAINSIGNIN) == 0)
		return FALSE;


	if(strlen(sID.c_str()) == 0)
		return FALSE;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db = CMDBHelper::GetInstance(1)->GetConnection();

	if (db == NULL)
		return FALSE;

	snprintf(sql,1024,"SELECT * FROM %s WHERE id = ?", TABLE_TRAINSIGNIN);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, sID.c_str());
		int i = sqlite3_step(stmt);
		if (i == SQLITE_ROW)
		{
			fetchItem(stmt);
			ret = TRUE;
		}
		else if (i == SQLITE_DONE)
		{
			ret = TRUE;
		}
		else
		{
			if (i != SQLITE_DONE) {
			CM_ERRP("sqlite3_prepare_refresh %s failed.error:%s sid:%s", sql, sqlite3_errmsg(db),sID.c_str());
			}
		}

		sqlite3_finalize(stmt);
	}
	else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}
	return ret;
}

TTrainSignInItem& TTrainSignInItem::operator=(const TTrainSignInItem& right)
{
	sID = right.sID;
	sTitle = right.sTitle;
	sTrainID = right.sTrainID;
	sImageURL = right.sImageURL;
	sTime = right.sTime;
	sAddress = right.sAddress;
	sSignInTime = right.sSignInTime;
	sFlag = right.sFlag;
	nMode = right.nMode;
	nSignInNum = right.nSignInNum;
}

void TTrainSignInItem::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;

	if(nCode == MER_OK)
	{
		ASSERT(pDoc);
		TiXmlElement* pItem = pDoc->RootElement();

		INT32 nErr = 0;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no",&nCmdID);

		if(pItem->QueryIntAttribute("errno",&nErr) == TIXML_SUCCESS)
		{

			if(nErr == 0)
			{

				result = TResult::ESuccess;
				if(nCmdID == SERVICE_TRAINSIGNININFO)
				{
					if(pItem->FirstChildElement("item"))
					{
						*this = pItem->FirstChildElement("item");
						Update();
					}else{
						result = TResult::ENothing;
					}
				}
			}
			else if(nErr == -14)
			{
				result = TResult::EDuplicaterating;
			}
			else if(nErr == -30)
			{
				result = TResult::ETimeNotStart;
			}
			else if(nErr == -31)
			{
				result = TResult::ETimeEnd;
			}
			else if(nErr == -32)
			{
				result = TResult::EBeCancel;
			}
			else if(nErr == -33)
			{
				result = TResult::ENotBelong;
			}
			else if(nErr == -26)
			{
				result = TResult::EGroupInexistence;
			}
			else
				result = TResult::EUnknownError;

		}
		else
			result = TResult::EProtocolFormatError;
	}
	else if(nCode ==MERN_INITIALIZE)
	{
		result = TResult::ENetDisconnect;
	}
	else if(nCode==MERN_OFFLINE)
	{
		result=TResult::ENotSupportOffline;
	}
	else
		result = TResult::ENetTimeout;

	if(m_bUpdateData)
	{
		if(m_pListener)
			m_pListener->OnUpdateDataFinish( m_UserData, result);
	}else
	{
		if(m_sListener)
			m_sListener->OnRequestFinish( m_UserData,result);
	}

}


CMTrainSignInList::CMTrainSignInList():CMHandler<TTrainSignInItem>()
{
	SetPaging(TRUE);
}

CMTrainSignInList::~CMTrainSignInList()
{

}

BOOL CMTrainSignInList::RemoveSuccessItem(int nIndex)
{
	BOOL ret = FALSE;

	if (!m_lstItem || nIndex < 0 || nIndex >= m_lstItem->size()) {
		return ret;
	}

	m_lstItem->removeAt(nIndex);
	ret = TRUE;
	m_bRefresh=TRUE;
	if(m_pListener)
		m_pListener->OnUpdateDataFinish( m_UserData, TResult::ESuccess);

	return ret;
}

void CMTrainSignInList::SetListener(IMUpdateDataListener* pUpdateDataListener)
{
	m_pListener = pUpdateDataListener;
}

BOOL CMTrainSignInList::RequestTrainApplyList(const char* mFlag)
{

	if(IsRunning())
		return false;

	if(strlen(mFlag) == 0)
		return false;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "flag=%s",mFlag);

	sprintf(m_tablename,TABLE_TRAINSIGNIN);
	return CMHandler<TTrainSignInItem>::Request(SERVICE_TRAINSIGNINLIST,sParam);

}

BOOL CMTrainSignInList::DoCreate(sqlite3* db)
{

	if (db == NULL)
			return FALSE;

		if (strcmp(m_tablename, "") == 0)
			return FALSE;

		char *errorMsg;
		char sql[1024];
		snprintf(sql, sizeof(sql),
				"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,title TEXT DEFAULT '',trainid TEXT DEFAULT '',image TEXT DEFAULT '',time TEXT DEFAULT '',address TEXT DEFAULT '',signintime TEXT DEFAULT '',flag TEXT DEFAULT '',mode INTEGER,signinnum INTEGER);",
				m_tablename);

		int i = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);

		if (i == SQLITE_OK)
		{
			return TRUE;
		}
		else
		{
			CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
			return FALSE;
		}

}


BOOL CMTrainSignInList::DoPutItem(TiXmlElement* pItem, sqlite3* db, TTrainSignInItem& item)
{
    item = pItem;

    if (strcmp(m_tablename, "") == 0)
	{
		//表名为空，不入库，返回成功
		return TRUE;
	}

    CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql,512,"REPLACE INTO %s(id,title,trainid,image,time,address,signintime,flag,mode,signinnum) VALUES (?,?,?,?,?,?,?,?,?,?)", TABLE_TRAINSIGNIN);
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		item.bindItem(stmt);
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

	return  TRUE;
}

void CMTrainSignInList::DoClear()
{
	//目前列表没有清除，可能有多余数据，因此不应该使用SetRequestType(1)
	m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->clear();
	m_mutex.UnLock();
}
