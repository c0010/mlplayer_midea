// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmfavorites.h"
#include "tinyxml.h"
#include "cmlist.h"
#include "cmglobal.h"
#include "cmdatetime.h"
#include "cmfile.h"

CMFavorites* CMFavorites::m_pTHIS = NULL;

CMFavorites* CMFavorites::GetInstance()
{
//    CMBrowser *item = new CMBrowser(NULL);
	if(m_pTHIS == NULL) {
		m_pTHIS = new CMFavorites();
        
        snprintf(m_pTHIS->m_tablename, 64,"favorites");

	}
	
	return m_pTHIS;
}

CMFavorites::~CMFavorites()
{
	m_pTHIS = NULL; //收藏有删除的需求
}

CMFavorites::CMFavorites()
{
}

void CMFavorites::SetListener(IMUpdateDataListener* pListener)
{
	m_pListener=pListener;
}

void CMFavorites::DoClear()
{
    
    m_mutex.Lock();
    if(m_lstHeadItem)
    {
        
        for(int i = 0; i < m_lstHeadItem->size(); i++)
        {
            TBrowserItem* ptr = m_lstHeadItem->at(i);
            SAFEDELETE(ptr);
        }
        
        m_lstHeadItem->clear();
    }
	m_mutex.UnLock();
    
	m_mutex.Lock();
    if(m_lstItem)
    {
        for(int i = 0; i < m_lstItem->size(); i++)
        {
            TBrowserItem* ptr = m_lstItem->at(i);
            SAFEDELETE(ptr);
        }
        
        m_lstItem->clear();
    }
    m_mutex.UnLock();

    
}



BOOL CMFavorites::LoadFromDB()
{
	if(m_lstItem)
		DoClear();
	else
		m_lstItem = new CMList<TBrowserItem*>;
	
    snprintf(m_tablename, 64,"favorites");
    
    SetPaging(FALSE);
    
    sqlite3* db = CheckTable(m_tablename);
    
    if (!db)
        return FALSE;
    if (DoGetCacheItems(db))
    {
        if (m_pListener)
        	m_pListener->OnUpdateDataFinish(m_UserData, MER_OK);
        return TRUE;
    }
    else
    {
        if (m_pListener)
        	m_pListener->OnUpdateDataFinish(m_UserData, MER_NOFOUND);
    	return FALSE;
    }
}



BOOL CMFavorites::RemoveItem(int nIndex)
{
    TBrowserItem* item = NULL;
    
    if(GetItemModel(nIndex)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }
    
	if(!GetItem(nIndex, item))
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
        BindParam(stmt, 1, item->sID);
        
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
       // m_lstItem->removeOne(item);
	m_mutex.UnLock();
    
    SAFEDELETE(item);

    if (m_pListener)
    	m_pListener->OnUpdateDataFinish(m_UserData, MER_OK);
    return ret;
}

// 返回值：0失败，1无收藏，2已收藏
int CMFavorites::IsInDB(const TBrowserItem& item)
{
    int ret = 0;
    
    if (strlen(m_tablename)==0) {
        return ret;
    }
    
    CHAR sql[2048];
    sql[0]='\0';
    sqlite3_stmt *stmt;
    
    sqlite3 * db =CheckTable(m_tablename);
    
    snprintf(sql,2048,"SELECT * FROM %s WHERE id = ?",m_tablename);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        BindParam(stmt, 1, item.sID);
        
        if(sqlite3_step(stmt)==SQLITE_ROW)
            ret=2;
        else
            ret=1;
    }
    
    sqlite3_finalize(stmt);
    
    
    return ret;
}


// 加一项收藏到收藏列表顶部，返回值：0失败，1成功，2已收藏
int CMFavorites::AddFavorite(const TBrowserItem& bitem)
{
	int ret = 0;
    

    TBrowserItem *item = NULL;
    
    if(bitem.nModel==0)
    {
       item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();

    }
    
    *item = bitem;
   
    if (strlen(m_tablename)==0) {
        SAFEDELETE(item);
        return ret;
    }
    
    if(strlen(item->sID) == 0)
    {
        SAFEDELETE(item);
        return 0;
    }
    //检查是否已收藏，已收藏直接返回
    m_mutex.Lock();

    for (int i = 0; i < m_lstItem->size(); i++)
    {
    	TBrowserItem* citem = m_lstItem->at(i);
		if (strcmp(item->sFlag, citem->sFlag) == 0 && strcmp(item->sID, citem->sID) == 0)
		{
			m_mutex.UnLock();
			return 2;
		}
    }

    m_mutex.UnLock();

    //无收藏添加数据库
    sqlite3 * db =CheckTable();

    m_bRefresh = FALSE;

    //需要push_back,item不能释放
    if(CMContenthandler::DoPutItem(NULL, db, item))
    {
        if (m_pListener)
        	m_pListener->OnUpdateDataFinish(m_UserData, MER_OK);
        return TRUE;
    }
    else
        return FALSE;
}


// 是否已收藏
int CMFavorites::IsAdded(const char* sFlag, const char* sid)
{
	int ret = -1;
	for (int i = 0; i < GetItemCount(); i++)
	{
		TBrowserItem* citem= new TBrowserItem();
		if (GetItem(i, citem))
		{

            
			if (strcmp(sFlag, citem->sFlag) == 0 && strcmp(sid, citem->sID) == 0)
			{
				ret = i;
                SAFEDELETE(citem);
				break;
			}
		}
        SAFEDELETE(citem);
	}

    return ret;
}



