// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <time.h>
#include "tinyxml.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "utf8ncpy.h"

template <typename T>
CMHandler<T>::CMHandler()
:m_UserData(NULL)
,m_pSession(NULL)
,m_pListener(NULL)
,m_bPaging(FALSE)
, m_nPageNo(1)
, m_nPageSize(30)
, m_nTotalCount(0)
, m_bEnd(TRUE)
, m_nServiceNo(0)
, m_nRequestType(0)
, m_nDefRequestType(0)
, m_nLastRequestType(0)
, m_nCacheDuration(10800) //默认缓存时间
,m_bRefresh(TRUE)
{
	m_pListener = NULL;
	m_lstItem = new CMList<T>();
    memset(&m_tablename, 0, 64);
}


template <typename T>
CMHandler<T>::~CMHandler()
{
	m_pListener = NULL;
    
	if(m_lstItem)
	{
		m_mutex.Lock();
		m_lstItem->clear();
		SAFEDELETE(m_lstItem);
		m_mutex.UnLock();
	}
	SAFEDELETE(m_pSession);
}

template <typename T>
void CMHandler<T>::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

template <typename T>
void CMHandler<T>::SetPaging(BOOL bPaging)
{
	m_bPaging = bPaging;
}

template <typename T>
BOOL CMHandler<T>::RequestMore()
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;

	m_bRefresh=FALSE;

    if(strlen(m_tablename)>0)
    {
        sqlite3* db = NULL;
        db = CheckTable();
        if(db)
        {
            DoCreate(db);
        }
    }
    
	if(m_bPaging)
	{
		if(m_nTotalCount <= m_nPageSize)
			return FALSE;
		int count = m_nTotalCount/m_nPageSize;
		if(m_nTotalCount%m_nPageSize > 0)
			count++;
		if(m_nPageNo < count)
		{
			m_nPageNo += 1;
			//请求更多时，请求类型和上次的保持一致
			if (m_nLastRequestType != m_nRequestType)
			{
				m_nRequestType = m_nLastRequestType;
			}
			return CurrentRequest(m_sParam,m_nPageNo,m_nPageSize);
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

template <typename T>
BOOL CMHandler<T>::CurrentRequest(const char* param,int pageno,int pagesize)
{
    if(strlen(m_tablename)>0)
    {
        sqlite3* db = NULL;
        db = CheckTable();
        if(db)
        {
            DoCreate(db);
        }
    }
    
	if (CMGlobal::TheOne().IsOffline())
	{
		//只做读取缓存，照常进行网络请求
		DoOffline();
	}

	char sParam[640];
	snprintf(sParam,640,"%s&pageno=%d&pagesize=%d",m_sParam,pageno,pagesize);
	    return CommonRequest(m_nServiceNo, sParam);

	return FALSE;
}

template <typename T>
void CMHandler<T>::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

template <typename T>
int CMHandler<T>::GetItemCount()
{
	int size;
	m_mutex.Lock();
    if(m_lstItem)
        size = m_lstItem->size();
    else
        size=0;
	m_mutex.UnLock();
	return size;
}

template <typename T>
BOOL CMHandler<T>::GetItem(int nIndex, T& item)
{
	return DoGetItem(nIndex, item);
}

template <typename T>
BOOL CMHandler<T>::DoGetItem(int nIndex, T& item)
{
	BOOL ret = FALSE;
    
	m_mutex.Lock();
	if(nIndex < m_lstItem->size() && nIndex >= 0)
	{
		item = m_lstItem->at(nIndex);
		ret = TRUE;
	}
	m_mutex.UnLock();
    
	return ret;
}

template <typename T>
void CMHandler<T>::Clear()
{
    DoClear();
}

template <typename T>
BOOL CMHandler<T>::GetCacheItems(sqlite3* db)
{
	if (DoGetCacheItems(db)) {
		int count = m_nTotalCount/m_nPageSize;
		if(m_nTotalCount%m_nPageSize > 0)
			count++;
		m_bEnd = (m_nPageNo >= count);
		return TRUE;
	}
	return FALSE;
}

template <typename T>
BOOL CMHandler<T>::Request(int nServiceNo, const char* sParam)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
    m_bRefresh=TRUE;
    
    if(strlen(m_tablename)>0)
    {
        sqlite3* db = NULL;
        db = CheckTable();
        if(db)
        {
            DoCreate(db);
        }
    }
    
	m_nServiceNo = nServiceNo;
	m_nPageNo = 1;
	m_nTotalCount = 0;
	strcpy(m_sParam,sParam);

    //拷贝url参数段作为cache内容(不添加分页信息),用cache内容和表名查缓存时间
    m_sCache = sParam;

	if(m_bPaging)
	{
		return CurrentRequest(m_sParam, 1, m_nPageSize);
	}
	else if (CMGlobal::TheOne().IsOffline() && strlen(m_tablename) > 0)  //只对有表的走DoOffline流程
	{
		DoOffline();
	}

	return CommonRequest(nServiceNo, sParam);
}

template <typename T>
BOOL CMHandler<T>::CommonRequest(int nServiceNo, const char* sParam)
{

    if(!m_pSession)
        m_pSession = new CMSession(this);
    if(m_pSession->IsRunning())
        return FALSE;

    //优先读缓存需要表名
    if (m_nRequestType == 1 && strlen(m_tablename) > 0)
    {

        time_t nExistTime = GetCacheTime();

        if (nExistTime != 0)
        {
        	time_t nCurrTime = GetCurrentTime();
			
			
            if (nCurrTime - nExistTime > m_nCacheDuration)
            {
                //当RequestType为1且超过了缓存时间时，先拿一遍缓存数据
                sqlite3* db = CheckTable();

                //若list为空才取
                if(GetItemCount() <= 0){
                	GetCacheItems(db);
                	#if defined(PLAT_AND)
	                	if(m_pListener)
	                    {
	                        m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccessCache);
	                    }
	                #endif
                }
				

                m_pSession->Command(nServiceNo, sParam);
            }
            else
            {
                sqlite3* db = CheckTable();
                
            	m_nLastRequestType = m_nRequestType;
            	if (m_nRequestType != m_nDefRequestType)
            	{
            		//重置请求类型到默认请求类型，
            		m_nRequestType = m_nDefRequestType;
            	}
                if (GetCacheItems(db))
                {
                    if(m_pListener)
                    {
                        m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
                    }
                }
                else
                {
                    m_pSession->Command(nServiceNo, sParam);
 
                }
            }
        }
        else
        {
            m_pSession->Command(nServiceNo, sParam);
        }
    }
    else
    {
        m_pSession->Command(nServiceNo, sParam);
    }
    
    return TRUE;
}

template <typename T>
void CMHandler<T>::SetRequestType(int nType)
{
    m_nRequestType = nType;
}

template <typename T>
void CMHandler<T>::SetCacheDuration(unsigned int nTime)
{
    m_nCacheDuration = nTime;
}

template <typename T>
BOOL CMHandler<T>::UpdateCacheTime(time_t time)
{
    BOOL ret = FALSE;
    if(strlen(m_tablename) == 0)
    {
    	return ret;
    }
    
    CHAR sql[512];
    sqlite3_stmt* stmt;
    sqlite3* db = CMDBHelper::GetInstance(1)->GetConnection();

    snprintf(sql, 512,"INSERT OR REPLACE INTO %s(tablename,cache,time) VALUES(?,?,?)","cacheinfo");
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
    	CMHandler<T>::BindParam(stmt, 1, m_tablename);
    	CMHandler<T>::BindParam(stmt, 2, m_sCache.c_str());
    	char s[64];
    	snprintf(s, 64,"%ld", time);
    	CMHandler<T>::BindParam(stmt, 3, s);
        
        if (sqlite3_step(stmt) == SQLITE_DONE)
        {
            ret = TRUE;
        }
        else
        {
        	CM_ERRP("exec %s failed error = %s", sql, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
    }
    else {
    	CM_ERRP("exec %s failed error = %s", sql, sqlite3_errmsg(db));
    }
    return ret;
}

template <typename T>
BOOL CMHandler<T>::UpdateCacheTime()
{
	return UpdateCacheTime(GetCurrentTime());
}

template <typename T>
time_t CMHandler<T>::GetCacheTime()
{
	//需要有表名
    if(strlen(m_tablename) == 0)
    {
    	return 0;
    }

    time_t ret = 0;
    sqlite3_stmt* stmt;
    CHAR sql[512];
    sql[0] = '\0';
    
    sqlite3* db = CMDBHelper::GetInstance(1)->GetConnection();
    
    snprintf(sql, 512,"SELECT time FROM %s WHERE tablename = ? AND cache = ?","cacheinfo");
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, m_tablename);
        BindParam(stmt, 2, m_sCache.c_str());
        
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            ret = atol((const char *)sqlite3_column_text(stmt, 0));
        }
        sqlite3_finalize(stmt);
    }
    
    return ret;
}

template <typename T>
time_t CMHandler<T>::GetCurrentTime()
{
    time_t currtTime;

    time(&currtTime);

    return mktime(localtime(&currtTime));
}

template<typename T>
inline BOOL CMHandler<T>::DoCreate(sqlite3* db)
{
	return FALSE;
}

template<typename T>
inline BOOL CMHandler<T>::DoPutItem(TiXmlElement* pItem, sqlite3* db, T& item)
{
	//默认实现不支持拷贝
	return FALSE;
}

template<typename T>
inline BOOL CMHandler<T>::DoGetCacheItems(sqlite3* db)
{
	return FALSE;
}

template<typename T>
inline BOOL CMHandler<T>::DoRefresh(T& obj)
{
	return FALSE;
}

template<typename T>
inline BOOL CMHandler<T>::DoUpdate(const T& obj)
{
	return FALSE;
}

template <typename T>
void CMHandler<T>::DoClear()
{
	m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->clear();
	m_mutex.UnLock();
    
    if(strlen(m_tablename) == 0)
        return;
    
    sqlite3* db = CheckTable(m_tablename);
    
    
    if(db != NULL)
    {
        
        CHAR sql[1024];
        sql[0] = '\0';
        char* errorMsg;
        
        snprintf(sql, 1024,"DELETE FROM %s", m_tablename);
        
        if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
        }        
    }
    
}

template <typename T>
BOOL CMHandler<T>::Refresh(T& obj)
{
	return DoRefresh(obj);
}

template <typename T>
BOOL CMHandler<T>::Update(const T& obj)
{
	return DoUpdate(obj);
}

template <typename T>
void CMHandler<T>::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;

	//请求类型的处理
	m_nLastRequestType = m_nRequestType;
	if (m_nRequestType != m_nDefRequestType)
	{
		//重置请求类型到默认请求类型，
		m_nRequestType = m_nDefRequestType;
	}

	if (nCode == MER_OK)
	{
		TiXmlElement *pItem = pDoc->RootElement();
        
		INT32 nErr = TResult::EUnknownError;

		pItem->QueryIntAttribute("errno", &nErr);
		if (nErr == TResult::ESuccess && nCmdID == m_nServiceNo)
		{
			//更新page信息
			if(m_bPaging)
			{
				pItem->QueryIntAttribute("totalcount", &m_nTotalCount);
				pItem->QueryIntAttribute("pageno", &m_nPageNo);
				int count = m_nTotalCount/m_nPageSize;
				if(m_nTotalCount%m_nPageSize > 0)
					count++;
				m_bEnd = (m_nPageNo >= count);
			}

			//清除以前缓存数据
            if (!m_bPaging || m_nPageNo == 1)
            {
                Clear();
            }

			//更新缓存时间
			UpdateCacheTime();

			if(!pItem->NoChildren())
			{
				sqlite3* db = CheckTable(m_tablename);

				char* errorMsg;

				if (db != NULL && sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
				{
					CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
				}

				pItem = pItem->FirstChildElement("item");

				m_mutex.Lock();
				while(pItem)
				{
					T t;

					if (DoPutItem(pItem, db, t))
					{
						m_lstItem->push_back(t);
					}

					pItem = pItem->NextSiblingElement("item");
				}
				m_mutex.UnLock();

				if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
				{
					CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
				}


				if(GetItemCount() > 0)
					result = TResult::ESuccess;
				else
					result = TResult::ENothing;
			}
            else
            {
                result = TResult::ENothing;
            }
            
		}
		else if(nErr == -17)
		{
			result = TResult::ENoPowerCourse;
		}
		else
		{
			if (nCmdID != m_nServiceNo)
				result = TResult::EProtocolFormatError;
			else
				result = TResult::EUnknownError;
		}
	}
	else
		result = ResultHandle(nCode);
	
	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData, result);
}


template <typename T>
int CMHandler<T>::ResultHandle(unsigned int nResult)
{
    if (nResult == MER_OK)
    {
        return TResult::ESuccess;
    }
    else if (nResult == MERN_INITIALIZE)
    {
        return TResult::ENetDisconnect;
    }
    else if (nResult == MERN_TIMEOUT)
    {
        return TResult::ENetTimeout;
    }
    else if (nResult == MERN_OFFLINE)
    {
    	return TResult::ENotSupportOffline;
    }
    else
    {
        return TResult::EUnknownError;
    }
}

template <typename T>
BOOL CMHandler<T>::IsEnd()
{
	return m_bEnd;
}

template <typename T>
BOOL CMHandler<T>::IsRefresh()
{
	return m_bRefresh;
}

template <typename T>
BOOL CMHandler<T>::IsRunning()
{
	if(m_pSession)
		return m_pSession->IsRunning();
	else
		return FALSE;
}

template <typename T>
int CMHandler<T>::BindParam(sqlite3_stmt* stmt,int col,int value)
{
    return  sqlite3_bind_int(stmt, col, value);
}

template <typename T>
int CMHandler<T>::BindParam(sqlite3_stmt* stmt,int col,const char* value)
{
    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);
    
    return sqlite3_bind_null(stmt, col);
    
}
template <typename T>
int CMHandler<T>::BindParam(sqlite3_stmt* stmt,int col,float value)
{
    return  sqlite3_bind_double(stmt, col, value);
}

template <typename T>
sqlite3* CMHandler<T>::CheckTable(const char * tablename)
{
    sqlite3 * db=  CMDBHelper::GetInstance(1)->GetConnection();
    
    if (DoCreate(db))
    	return db;
    else
    {
    	if (db != NULL)
    		return  db;
    	return NULL;
    }
}

template <typename T>
sqlite3* CMHandler<T>::CheckTable()
{
    sqlite3 * db=  CMDBHelper::GetInstance(1)->GetConnection();
    
    if(db)
        return db;
    else
        return NULL;
 
}

template <typename T>
sqlite3* CMHandler<T>::CheckRootTable()
{
    sqlite3 * db=  CMDBHelper::GetInstance(0)->GetConnection();
    
    if(db)
        return db;
    else
        return NULL;
    
}

template <typename T>
BOOL CMHandler<T>::DoOffline()
{
	sqlite3* db = CheckTable();
	if (db != NULL)
	{
		GetCacheItems(db);
	}
    
	return TRUE;
}



