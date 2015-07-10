/*
 * cmpushmsg.cpp
 *
 *  Created on: 2015年5月25日
 *      Author: Administrator
 */

#include "stdafx.h"
#include "cmpushmsg.h"
#include "tinyxml.h"
#include "cmlist.h"

#define TABLE_TRAINAPPLY "pushmsgs"


CMPushMsg* CMPushMsg::m_pTHIS = NULL;

TPushItem::TPushItem()
{
	sID = "";
	sKey = "";
	sMsg = "";
	sType = "";
	sPubDate = "";
	bIsRead = FALSE;
}

TPushItem::~TPushItem()
{

}

void TPushItem::bindItem(sqlite3_stmt *stmt) const
{

	sqlite3_bind_text(stmt, 1, sID.c_str(), -1, NULL);

	sqlite3_bind_text(stmt, 2, sKey.c_str(), -1, NULL);

	sqlite3_bind_text(stmt, 3, sMsg.c_str(), -1, NULL);

	sqlite3_bind_text(stmt, 4, sType.c_str(), -1, NULL);

	sqlite3_bind_text(stmt, 5, sPubDate.c_str(), -1, NULL);

	sqlite3_bind_int(stmt, 6, bIsRead);

}

void TPushItem::fetchItem(sqlite3_stmt *stmt)
{

	sID = (const char*)sqlite3_column_text(stmt, 0);
	sKey = (const char*)sqlite3_column_text(stmt, 1);
	sMsg = (const char*)sqlite3_column_text(stmt, 2);
	sType = (const char*)sqlite3_column_text(stmt, 3);
	sPubDate = (const char*)sqlite3_column_text(stmt, 4);
	bIsRead = sqlite3_column_int(stmt,5);

}

CMPushMsg* CMPushMsg::GetInstance()
{
	if(m_pTHIS == NULL) {
		m_pTHIS = new CMPushMsg();
	}
	return m_pTHIS;
}

CMPushMsg::CMPushMsg() : CMHandler<TPushItem>()
{
	m_nRequestType = 1;
	SetPaging(FALSE);
	m_nCacheDuration = 0;
	snprintf(m_tablename, 64,"pushmsgs");

	sqlite3* db =CheckTable();

	if(db)
	{
		DoCreate(db);
	}
}

CMPushMsg::~CMPushMsg()
{

}

void CMPushMsg::SetListener(IMUpdateDataListener* pListener)
{
	m_pListener = pListener;
}

BOOL CMPushMsg::DoCreate(sqlite3* db)
{

	if(db == NULL) return FALSE;
	if (strcmp(m_tablename, "") == 0) return FALSE;

	char *errorMsg;
	char sql[1024];                              //数据库中添加sQcategorytitle  ，sQcategoryid 两个字段
	snprintf(sql,sizeof(sql),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,msg TEXT,type TEXT,key TEXT,pubdate TEXT,isread INTEGER);", m_tablename);

	int i = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);

	if (i==SQLITE_OK) {
		return TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}

}

BOOL CMPushMsg::DoRefresh(TPushItem& obj)
{
	BOOL ret = FALSE;

	m_mutex.Lock();
	for(int i=0;i<m_lstItem->size();i++)
	{
		TPushItem& item = m_lstItem->at(i);
		if(item.sID.c_str() == obj.sID.c_str())
		{
			obj = item;
			ret = TRUE;
		}
	}
	m_mutex.UnLock();

	if (strcmp(m_tablename, "") == 0) return FALSE;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db=CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;

	snprintf(sql,sizeof(sql),"SELECT id,key,msg,type,pubdate,isread FROM %s WHERE id=?",m_tablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, obj.sID.c_str());

		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			obj.fetchItem(stmt);
		}
        else
        {
        	CM_ERRP("sqlite3_prepare_v2 %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
		sqlite3_finalize(stmt);
	}
	else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return ret;
}


BOOL CMPushMsg::DoUpdate(const TPushItem& obj)
{
	BOOL ret = FALSE;

	m_mutex.Lock();
	for (int i = 0; i < m_lstItem->size(); i++) {
		TPushItem& item = m_lstItem->at(i);

		if (strcmp(item.sID.c_str(),obj.sID.c_str()) == 0) {
			item = obj;
			ret = TRUE;
			break;
		}
	}
	m_mutex.UnLock();

	if (strcmp(m_tablename, "") == 0)
		return FALSE;

    //保存入数据库
    sqlite3*db = CheckTable(m_tablename);
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"UPDATE %s SET id=?,key=?,msg=?, type=?, pubdate=?, isread=? WHERE id=? ", m_tablename);

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            obj.bindItem(stmt);
            BindParam(stmt,7,obj.sID.c_str());
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

BOOL CMPushMsg::DoGetCacheItems(sqlite3* db)
{
	if (strcmp(m_tablename, "") == 0) return FALSE;

	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	snprintf(sql,sizeof(sql),"SELECT id,key,msg,type,pubdate,isread FROM %s ORDER BY pubdate DESC", m_tablename);

	if (m_bPaging)
	{
		//添加page字串
		snprintf(sql,sizeof(sql),"%s LIMIT %d OFFSET %d", sql, m_nPageSize, (m_nPageNo - 1)*m_nPageSize);
	}

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{

        if (!m_bPaging || m_nPageNo == 1)
        {
        	//如果是第一页，清空表
        	m_mutex.Lock();
        	m_lstItem->clear();
        	m_mutex.UnLock();
        }

        m_mutex.Lock();
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
        	TPushItem item;

            item.fetchItem(stmt);

        	m_lstItem->push_back(item);           //从服务器读到的数据，写入数据库，然后把数据库中的数据读到相关结构体中
        }
        m_mutex.UnLock();

        sqlite3_finalize(stmt);

        ret = TRUE;
	}

	if (ret)
	{
		//计算总数
		m_nTotalCount = 0;
		snprintf(sql,sizeof(sql),"SELECT COUNT(*) FROM %s", m_tablename);
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
		{
	        if (sqlite3_step(stmt) == SQLITE_ROW)
	        {
	        	m_nTotalCount = sqlite3_column_int(stmt, 0);
	        }

	        sqlite3_finalize(stmt);
		}
	}

	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData,TResult::ESuccess);

	return ret;
}

void CMPushMsg::DoClear()
{
    m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->clear();
	m_mutex.UnLock();

	CHAR sql[1024];
	sql[0] = '\0';
	char* errorMsg;
	sqlite3_stmt *stmt;

    sqlite3* db = CheckTable(m_tablename);

	snprintf(sql,sizeof(sql),"DELETE FROM %s", m_tablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{

		if (sqlite3_step(stmt) != SQLITE_DONE)
		{
			CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		}

		sqlite3_finalize(stmt);
	}

	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData,TResult::ESuccess);

}

BOOL CMPushMsg::AddPushMsg(const TPushItem& item)
{
	BOOL ret = FALSE;

    if (strlen(m_tablename)==0) {
        return TRUE;
    }

    sqlite3* db =CheckTable();

	CHAR sql[1024];
	sqlite3_stmt *stmt;
    snprintf(sql,sizeof(sql),"REPLACE INTO %s(id,key,msg,type,pubdate,isread) VALUES (?,?,?,?,?,?)", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        item.bindItem(stmt);
        if(sqlite3_step(stmt) == SQLITE_DONE)
        {
        	ret = TRUE;
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

    if(m_pListener)
    	m_lstItem->push_front(item);
    if(m_pListener)
    	m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);

    return  TRUE;

}

BOOL CMPushMsg::LoadFromDB()
{
	m_bRefresh = TRUE;
	m_nPageNo = 1;
	sqlite3* db =CheckTable();
	return DoGetCacheItems(db);
}

BOOL CMPushMsg::Clear()
{
	m_mutex.Lock();
	if(m_lstItem)
		m_lstItem->clear();
	m_mutex.UnLock();
	return TRUE;
}

BOOL CMPushMsg::ClearCache()
{
	DoClear();
	return TRUE;
}

BOOL CMPushMsg::RemoveItem(int nIndex)
{
    TPushItem* item = new TPushItem();



	if( !GetItem(nIndex, *item) )
	{
        SAFEDELETE(item);
		return FALSE;
	}

    //从数据库中删除
    if(strlen(m_tablename)==0)
    {
        SAFEDELETE(item);
        return FALSE;
    }

    sqlite3 * db = CheckTable(m_tablename);

    BOOL ret= FALSE;

    char sql[1024];
    sql[0]='\0';

    sqlite3_stmt *stmt;

    snprintf(sql, 1024,"DELETE FROM %s WHERE id = ? ",m_tablename);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, item->sID.c_str());

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            CM_ERRP("exec %s failed.", sql);
            SAFEDELETE(item);
            return ret;
        }

        ret=TRUE;
    }

    sqlite3_finalize(stmt);


    m_bRefresh = TRUE;

    //从链表中删除
    m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->removeAt(nIndex);
	m_mutex.UnLock();

    SAFEDELETE(item);
    if (m_pListener)
    	m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
    return ret;
}

int CMPushMsg::GetUnReadCount()
{
	if(m_lstItem->size()==0)
		LoadFromDB();

	int count = 0;

	for(int i=0;i<m_lstItem->size();i++)
	{
		TPushItem& item = m_lstItem->at(i);
		if(!item.bIsRead)
		{
			count++;
		}
	}

	return count;

}

