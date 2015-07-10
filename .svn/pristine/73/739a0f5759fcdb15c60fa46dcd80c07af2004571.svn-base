/*

 * cmtrainapplylist.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: Administrator
 */

#include "stdafx.h"
#include "cmtrainapplylist.h"

#define TABLE_TRAINAPPLY "train_apply"

TTrainApplyItem::TTrainApplyItem()
{
	nIsPass = 2;
	nEnableCancelApply = 0;
	nAppliedNum = 0;
	m_pSession = NULL;
	m_pListener = NULL;
	m_sListener = NULL;
	nEnableApply = 0;
}

TTrainApplyItem::~TTrainApplyItem()
{
	if(m_pSession)
		m_pSession->Cancel();
}


void TTrainApplyItem::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

void TTrainApplyItem::SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener)
{
	m_pListener = pUpdateDataListener;
	m_sListener = pSimpleResultListener;
}

void TTrainApplyItem::SetUserData(void* userdata)
{
	m_UserData = userdata;
}

TTrainApplyItem& TTrainApplyItem::operator=(const TiXmlElement* right)
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

	pStr = right->Attribute("traintime");
	if(pStr)
	{
		sTrainTime = pStr;
	}

	pStr = right->Attribute("applytime");
	if(pStr)
	{
		sApplyTime = pStr;
	}

	pStr = right->Attribute("address");
	if(pStr)
	{
		sAddress = pStr;
	}

	pStr = right->Attribute("flag");
	if(pStr)
	{
		sFlag = pStr;
	}

	pStr = right->Attribute("description");
	if(pStr)
	{
		sDesc = pStr;
	}

	pStr = right->Attribute("appliedtime");
	if(pStr)
	{
		sAppliedTime = pStr;
	}
    
    pStr = right->Attribute("planperson");
    if(pStr)
    {
        sPlanPerson = pStr;
    }

	right->QueryIntAttribute("ispass",&nIsPass);
	right->QueryIntAttribute("enablecancelapply",&nEnableCancelApply);
	right->QueryIntAttribute("appliednum",&nAppliedNum);
	right->QueryIntAttribute("enableapply",&nEnableApply);
}

int TTrainApplyItem::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TTrainApplyItem::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{

    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);

    return sqlite3_bind_null(stmt, col);

}
int TTrainApplyItem::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TTrainApplyItem::bindItem(sqlite3_stmt *stmt) const
{
	sqlite3_bind_text(stmt, 1, sID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 2, sTitle.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 3, sTrainID.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 4, sImageURL.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 5, sTrainTime.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 6, sApplyTime.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 7, sAddress.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 8, sFlag.c_str(), -1,NULL);
	sqlite3_bind_text(stmt, 9, sDesc.c_str(), -1,NULL);
	sqlite3_bind_int(stmt, 10, nIsPass);
	sqlite3_bind_text(stmt, 11, sAppliedTime.c_str(), -1,NULL);
	sqlite3_bind_int(stmt, 12, nEnableCancelApply);
	sqlite3_bind_int(stmt, 13, nAppliedNum);
	sqlite3_bind_int(stmt,14,nEnableApply);
    sqlite3_bind_text(stmt, 15, sPlanPerson.c_str(), -1,NULL);
}

void TTrainApplyItem::fetchItem(sqlite3_stmt *stmt)
{
	sID = (const char*)sqlite3_column_text(stmt, 1);
	sTitle = (const char*)sqlite3_column_text(stmt, 2);
	sTrainID = (const char*)sqlite3_column_text(stmt, 3);
	sImageURL = (const char*)sqlite3_column_text(stmt, 4);
	sTrainTime = (const char*)sqlite3_column_text(stmt, 5);
	sApplyTime = (const char*)sqlite3_column_text(stmt, 6);
	sAddress = (const char*)sqlite3_column_text(stmt, 7);
	sFlag = (const char*)sqlite3_column_text(stmt, 8);
	sDesc = (const char*)sqlite3_column_text(stmt, 9);
	nIsPass = sqlite3_column_int(stmt, 10);
	sAppliedTime = (const char*)sqlite3_column_text(stmt, 11);
	nEnableCancelApply = sqlite3_column_int(stmt, 12);
	nAppliedNum = sqlite3_column_int(stmt, 13);
	nEnableApply = sqlite3_column_int(stmt,14);
    sPlanPerson = (const char*)sqlite3_column_text(stmt, 15);
}

BOOL TTrainApplyItem::RequestInfo()
{
	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	m_bUpdateData = TRUE;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "id=%s",this->sID.c_str());

	m_pSession->Command(SERVICE_GETTRAINAPPLYINFO,sParam);

	return TRUE;
}

BOOL TTrainApplyItem::Apply()
{
	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	m_bUpdateData = FALSE;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "id=%s",this->sID.c_str());

	m_pSession->Command(SERVICE_TRAINAPPLY,sParam);

	return TRUE;
}

BOOL TTrainApplyItem::CancelApply()
{
	if(m_pSession == NULL)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	m_bUpdateData = FALSE;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "id=%s",this->sID.c_str());

	m_pSession->Command(SERVICE_TRAINCANCELAPPLY,sParam);

	return TRUE;
}

BOOL TTrainApplyItem::Update()
{

	BOOL ret = FALSE;

	sqlite3*db=CMDBHelper::GetInstance(1)->GetConnection();
	if(db)
	{
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,512,"REPLACE INTO %s(id,title,trainid,image,traintime,applytime,address,flag,description,ispass,appliedtime,enablecancelapply,appliednum,enableapply,planperson) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)", TABLE_TRAINAPPLY);

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

BOOL TTrainApplyItem::Refresh()
{
	BOOL ret = FALSE;

	if(strlen(TABLE_TRAINAPPLY) == 0)
		return FALSE;


	if(strlen(sID.c_str()) == 0)
		return FALSE;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db = CMDBHelper::GetInstance(1)->GetConnection();

	if (db == NULL)
		return FALSE;

	snprintf(sql,1024,"SELECT * FROM %s WHERE id = ?", TABLE_TRAINAPPLY);

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

TTrainApplyItem& TTrainApplyItem::operator=(const TTrainApplyItem& right)
{
	sID = right.sID;
	sTitle = right.sTitle;
	sTrainID = right.sTrainID;
	sImageURL = right.sImageURL;
	sTrainTime = right.sTrainTime;
	sApplyTime = right.sApplyTime;
	sAddress = right.sAddress;
	sFlag = right.sFlag;
	sDesc = right.sDesc;
	sAppliedTime = right.sAppliedTime;
    sPlanPerson = right.sPlanPerson;
	nIsPass = right.nIsPass;
	nEnableCancelApply = right.nEnableCancelApply;
	nAppliedNum = right.nAppliedNum;
	nEnableApply = right.nEnableApply;
    
}

void TTrainApplyItem::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
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
				if(nCmdID == SERVICE_GETTRAINAPPLYINFO)
				{
					if(pItem->FirstChildElement("item"))
					{
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
			else if(nErr == -34)
			{
				result = TResult::EOutNum;
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


CMTrainApplyList::CMTrainApplyList():CMHandler<TTrainApplyItem>()
{
	SetPaging(TRUE);
}

CMTrainApplyList::~CMTrainApplyList()
{

}

void CMTrainApplyList::SetListener(IMUpdateDataListener* pUpdateDataListener)
{
	m_pListener = pUpdateDataListener;
}

BOOL CMTrainApplyList::RequestTrainApplyList(const char* mFlag)
{
	if(IsRunning())
		return false;

	if(strlen(mFlag) == 0)
		return false;

	char sParam[200];
	memset(sParam, 0, 200);

	snprintf(sParam, 200, "flag=%s",mFlag);

	sprintf(m_tablename,TABLE_TRAINAPPLY);
	return CMHandler<TTrainApplyItem>::Request(SERVICE_GETTRAINAPPLYLIST,sParam);
}

BOOL CMTrainApplyList::RemoveSuccessItem(int nIndex)
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

BOOL CMTrainApplyList::DoCreate(sqlite3* db)
{

	if (db == NULL)
			return FALSE;

		if (strcmp(m_tablename, "") == 0)
			return FALSE;

		char *errorMsg;
		char sql[1024];
		snprintf(sql, sizeof(sql),
				"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,title TEXT DEFAULT '',trainid TEXT DEFAULT '',image TEXT DEFAULT '',traintime TEXT DEFAULT '',applytime TEXT DEFAULT '',address TEXT DEFAULT '',flag TEXT DEFAULT '',description TEXT DEFAULT '',ispass INTEGER,appliedtime TEXT DEFAULT '',enablecancelapply INTEGER,appliednum INTEGER,enableapply INTEGER,planperson TEXT DEFAULT '');",
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


BOOL CMTrainApplyList::DoPutItem(TiXmlElement* pItem, sqlite3* db, TTrainApplyItem& item)
{
    item = pItem;

    if (strcmp(m_tablename, "") == 0)
	{
		//表名为空，不入库，返回成功
		return TRUE;
	}

    CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql,512,"REPLACE INTO %s(id,title,trainid,image,traintime,applytime,address,flag,description,ispass,appliedtime,enablecancelapply,appliednum,enableapply,planperson) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)", TABLE_TRAINAPPLY);
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

void CMTrainApplyList::DoClear()
{
	//目前列表没有清除，可能有多余数据，因此不应该使用SetRequestType(1)
	m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->clear();
	m_mutex.UnLock();
}
