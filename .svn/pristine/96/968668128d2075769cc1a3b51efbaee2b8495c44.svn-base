/*
 * cmtrainapplylist.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: Administrator
 */

#include "stdafx.h"
#include "cmmytrainlist.h"

#define TABLE_MYTRAIN "traininfo"

TMyTrainItem::TMyTrainItem()
{
	nUserCount = 0;
	m_pSession = NULL;
	m_pListener = NULL;
	m_sListener = NULL;
}

TMyTrainItem::~TMyTrainItem()
{
	if(m_pSession)
		m_pSession->Cancel();
}


void TMyTrainItem::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

void TMyTrainItem::SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener)
{
	m_pListener = pUpdateDataListener;
	m_sListener = pSimpleResultListener;
}

void TMyTrainItem::SetUserData(void* userdata)
{
	m_UserData = userdata;
}

TMyTrainItem& TMyTrainItem::operator=(const TiXmlElement* right)
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

	pStr = right->Attribute("icon");
	if(pStr)
	{
		sIcon = pStr;
	}

	pStr = right->Attribute("trainnumber");
	if(pStr)
	{
		sTrainNumber = pStr;
	}

	pStr = right->Attribute("mode");
	if(pStr)
	{
		sMode = pStr;
	}

	pStr = right->Attribute("traintime");
	if(pStr)
	{
		sTrainTime = pStr;
	}

	right->QueryIntAttribute("usercount",&nUserCount);

	pStr = right->Attribute("description");
	if(pStr)
	{
		sDesc = pStr;
	}

	pStr = right->Attribute("remark");
	if(pStr)
	{
		sRemark = pStr;
	}

	pStr = right->Attribute("roomid");
	if(pStr)
	{
		sRoomID = pStr;
	}

	pStr = right->Attribute("roomjid");
	if(pStr)
	{
		sRoomJID = pStr;
	}

	pStr = right->Attribute("roompwd");
	if(pStr)
	{
		sRoomPwd = pStr;
	}

	pStr = right->Attribute("tablist");
	if(pStr)
	{
		sTabList = pStr;
	}

	pStr = right->Attribute("address");
	if(pStr)
	{
		sAddress = pStr;
	}
}

int TMyTrainItem::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TMyTrainItem::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{

    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);

    return sqlite3_bind_null(stmt, col);

}
int TMyTrainItem::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TMyTrainItem::bindItem(sqlite3_stmt *stmt) const
{
	sqlite3_bind_text(stmt, 1, sID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 2, sTitle.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 3, sIcon.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 4, sTrainNumber.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 5, sMode.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 6, sTrainTime.c_str(), -1,NULL);
	sqlite3_bind_int(stmt, 7, nUserCount);
	sqlite3_bind_text(stmt, 8, sDesc.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 9, sRemark.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 10, sRoomID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 11, sRoomJID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 12, sRoomPwd.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 13, sTabList.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 14, sAddress.c_str(), -1,NULL);
}

void TMyTrainItem::fetchItem(sqlite3_stmt *stmt)
{
	sID = (const char*)sqlite3_column_text(stmt, 1);
	sTitle = (const char*)sqlite3_column_text(stmt, 2);
	sIcon = (const char*)sqlite3_column_text(stmt, 3);
	sTrainNumber = (const char*)sqlite3_column_text(stmt, 4);
	sMode = (const char*)sqlite3_column_text(stmt, 5);
	sTrainTime = (const char*)sqlite3_column_text(stmt, 6);
	nUserCount = sqlite3_column_int(stmt, 7);
	sDesc = (const char*)sqlite3_column_text(stmt, 8);
	sRemark = (const char*)sqlite3_column_text(stmt, 9);
	sRoomID = (const char*)sqlite3_column_text(stmt, 10);
	sRoomJID = (const char*)sqlite3_column_text(stmt, 11);
	sRoomPwd = (const char*)sqlite3_column_text(stmt, 12);
	sTabList = (const char*)sqlite3_column_text(stmt, 13);
	sAddress = (const char*)sqlite3_column_text(stmt, 14);
}

BOOL TMyTrainItem::RequestInfo()
{
	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "id=%s",this->sID.c_str());

	m_pSession->Command(SERVICE_GETMYTRAININFO,sParam);

	return TRUE;
}

BOOL TMyTrainItem::Update()
{

	BOOL ret = FALSE;
	sqlite3*db=CMDBHelper::GetInstance(1)->GetConnection();
	if(db)
	{
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,512,"REPLACE INTO %s(id,title,icon,trainnumber,mode,traintime,usercount,description,remark,roomid,roomjid,roompwd,tablist,address) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)", TABLE_MYTRAIN);

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

BOOL TMyTrainItem::Refresh()
{
	BOOL ret = FALSE;

	if(strlen(TABLE_MYTRAIN) == 0)
		return FALSE;


	if(strlen(sID.c_str()) == 0)
		return FALSE;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db = CMDBHelper::GetInstance(1)->GetConnection();

	if (db == NULL)
		return FALSE;

	snprintf(sql,1024,"SELECT * FROM %s WHERE id = ?", TABLE_MYTRAIN);

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

TMyTrainItem& TMyTrainItem::operator=(const TMyTrainItem& right)
{
	sID = right.sID;
	sTitle = right.sTitle;
	sIcon = right.sIcon;
	sTrainNumber = right.sTrainNumber;
	sMode = right.sMode;
	sTrainTime = right.sTrainTime;
	nUserCount = right.nUserCount;
	sDesc = right.sDesc;
	sRemark = right.sRemark;
	sRoomID = right.sRoomID;
	sRoomJID = right.sRoomJID;
	sRoomPwd = right.sRoomPwd;
	sTabList = right.sTabList;
	sAddress = right.sAddress;
}

void TMyTrainItem::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;


	if(nCode ==MER_OK)
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
				if(nCmdID == SERVICE_GETMYTRAININFO)
				{
					if(pItem->FirstChildElement("item")){
						*this = pItem->FirstChildElement("item");
						Update();

					}else
					{
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

	if(m_pListener)
		m_pListener->OnUpdateDataFinish( m_UserData, result);

}


CMMyTrainList::CMMyTrainList():CMHandler<TMyTrainItem>()
{
	SetPaging(TRUE);
}

CMMyTrainList::~CMMyTrainList()
{

}

void CMMyTrainList::SetListener(IMUpdateDataListener* pUpdateDataListener)
{
	m_pListener = pUpdateDataListener;
}

BOOL CMMyTrainList::RequestTrainApplyList()
{

	if(IsRunning())
		return false;

	char sParam[200];
	memset(sParam, 0, 200);

//	snprintf(sParam, 200, "flag=%s",mFlag);

	sprintf(m_tablename,TABLE_MYTRAIN);
	return CMHandler<TMyTrainItem>::Request(SERVICE_GETMYTRAINLIST,sParam);

}

BOOL CMMyTrainList::DoCreate(sqlite3* db)
{

	if (db == NULL)
			return FALSE;

		if (strcmp(m_tablename, "") == 0)
			return FALSE;

		char *errorMsg;
		char sql[1024];
		snprintf(sql, sizeof(sql),
				"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,title TEXT DEFAULT '',icon TEXT DEFAULT '',trainnumber TEXT DEFAULT '',mode TEXT DEFAULT '',traintime TEXT DEFAULT '',usercount INTEGER,description TEXT DEFAULT '',remark TEXT DEFAULT '',roomid TEXT DEFAULT '',roomjid TEXT DEFAULT '',roompwd TEXT DEFAULT '',tablist TEXT DEFAULT '',address TEXT DEFAULT '');",
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


BOOL CMMyTrainList::DoPutItem(TiXmlElement* pItem, sqlite3* db, TMyTrainItem& item)
{
    item = pItem;

    if (strcmp(m_tablename, "") == 0)
	{
		//表名为空，不入库，返回成功
		return TRUE;
	}

    CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql,512,"REPLACE INTO %s(id,title,icon,trainnumber,mode,traintime,usercount,description,remark,roomid,roomjid,roompwd,tablist,address) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)", TABLE_MYTRAIN);
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

void CMMyTrainList::DoClear()
{
	//目前列表没有清除，可能有多余数据，因此不应该使用SetRequestType(1)
	m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->clear();
	m_mutex.UnLock();
}
