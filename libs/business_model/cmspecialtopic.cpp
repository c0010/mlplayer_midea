// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmspecialtopic.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "utf8ncpy.h"

CMSpecialTopic::CMSpecialTopic(IMUpdateDataListener* pListener)
:CMContenthandler()
{
    memset(m_sTitle, 0, 100);
    memset(m_sImage, 0, 300);
    memset(sParentSpecId, 0, 64);
    
    SetListener(pListener, NULL);
}


CMSpecialTopic::~CMSpecialTopic()
{
}

//SELECT specialtopic.*
//FROM specialtopic
//LEFT JOIN browserall_course
//ON specialtopic.parentspecid = browserall_course.specialtopic;

void CMSpecialTopic::GetSpecialTopic(const char* sID)
{
    
    if (IsRunning())
		return ;
	char sParam[200];
	snprintf(sParam,sizeof(sParam),"id=%s", sID);
    sprintf(m_tablename, "browser_specialtopic");

    strcpy(sParentSpecId, sID);
    
	this->Request(SERVICE_GETSPECIALTOPIC,sParam);
}

const char* CMSpecialTopic::GetTitle()
{
	return m_sTitle;
}

const char* CMSpecialTopic::GetImage()
{
	return m_sImage;
}

void CMSpecialTopic::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	if(nCode == MER_OK && nCmdID == SERVICE_GETSPECIALTOPIC)
	{
		TiXmlElement *pItem = pDoc->RootElement();
        
		INT32 nErr = -1;
		pItem->QueryIntAttribute("errno", &nErr);
		if(nErr == 0)
		{
			//title
			const char* pStr = pItem->Attribute("title");
			if(pStr)
				strcpy(m_sTitle, pStr);
			//image
			pStr = pItem->Attribute("image");
			if(pStr)
				strcpy(m_sImage, pStr);
		}
	}
	CMContenthandler::OnSessionCmd(nCmdID, nCode, pDoc);
}


void CMSpecialTopic::DoClear()
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

    
    sqlite3* db = CheckTable();
    
    if(db != NULL)
    {
        CHAR sql[1024];
        sql[0] = '\0';
        sqlite3_stmt *stmt;
        
        snprintf(sql, sizeof(sql),"DELETE FROM %s WHERE parentspecid = ? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
        {
            BindParam(stmt, 1, sParentSpecId);
            
            
            if (sqlite3_step(stmt) != SQLITE_DONE)
            {
                CM_ERRP("exec %s failed.", sql);
            }
        }
    }
}


BOOL CMSpecialTopic::DoCreate(sqlite3* db)
{
	char *errorMsg;
	char sql[2048];
    
    BOOL ret=FALSE;

    if(strlen(m_tablename)==0)
        return FALSE;
    
	snprintf(sql,sizeof(sql), "CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT,stitle TEXT,simage TEXT,parentspecid TEXT)", m_tablename);
    
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		ret = TRUE ;
	}
	else
	{
        CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		ret   = FALSE;
	}
    
    
    
    if(CMContenthandler::DoCreate(db)==FALSE)
        return FALSE;
    else
        return ret;
}


BOOL CMSpecialTopic::DoPutItem(TiXmlElement* pItem, sqlite3* db, TBrowserItem*& item)
{
    const CHAR* pid = NULL;
    
	pid = pItem->Attribute("id");

    
    //存入数据库
    if(!db)
        return FALSE;
    
    if(strlen(m_tablename)==0)
        return FALSE;
    
    CHAR sql[1024];
    
    BOOL ret = FALSE;
    
	sqlite3_stmt *stmt;
    
    snprintf(sql,sizeof(sql), "INSERT INTO %s(id,stitle,simage,parentspecid) VALUES (?,?,?,?)", m_tablename);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        BindParam(stmt, 1, pid);
        
        BindParam(stmt,2, m_sTitle);
        BindParam(stmt, 3, m_sImage);
        BindParam(stmt, 4, sParentSpecId);
        
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
    
    if( CMContenthandler::DoPutItem(pItem, db, item)==FALSE)
        ret= FALSE;
    
    char* errorMsg;
    
    //发生错误则回滚
    if (ret == FALSE) {
        
        if (db != NULL && sqlite3_exec(db, "ROLLBACK TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("ROLLBACK TRANSACTION failed.error:%s", errorMsg);
        }
        
    }
    
    return ret;
}

BOOL CMSpecialTopic::DoGetCacheItems(sqlite3* db)
{
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    snprintf(sql,sizeof(sql),"SELECT main.*, sub.stitle , sub.simage , sub.parentspecid FROM %s AS sub  LEFT JOIN %s AS main ON sub.id = main.id WHERE sub.parentspecid = ? ",m_tablename,m_tablename );
    
    if (m_bPaging)
    {
        snprintf(sql,sizeof(sql),"%s LIMIT %d OFFSET %d", sql, m_nPageSize, (m_nPageNo - 1)*m_nPageSize);
    }
    
    // printf("error:%d \n",sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) );
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        BindParam(stmt, 1, sParentSpecId);
        if ( m_nPageNo == 1)
        {
            m_mutex.Lock();
            m_lstItem->clear();
            m_mutex.UnLock();
            
            m_mutex.Lock();
            m_lstHeadItem->clear();
            m_mutex.UnLock();
            
        }
        
        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
        	TClassItem* item= new TClassItem();
            
            item->fetchItem(stmt);
            
//            utf8ncpy(item.sID, (const char*)sqlite3_column_text(stmt, 1), 63);
//            
//            utf8ncpy(item.sFlag, (const char*)sqlite3_column_text(stmt, 2), 15);
//            
//            utf8ncpy(item.sTitle, (const char*)sqlite3_column_text(stmt, 3), 99);
//            
//            utf8ncpy(item.sBrief, (const char*)sqlite3_column_text(stmt, 4), 99);
//
//            
//            utf8ncpy(item.sLargeimage, (const char*)sqlite3_column_text(stmt, 5) ,299);
//            
//            utf8ncpy(item.sImage, (const char*)sqlite3_column_text(stmt, 6) ,299);
//            
//            utf8ncpy(item.sThumbs, (const char*)sqlite3_column_text(stmt, 7) ,299);
//            
//            utf8ncpy(item.sType , (const char*)sqlite3_column_text(stmt, 8) ,63);
//            
//            item.nCoursewarecount = sqlite3_column_int(stmt, 9);
//            
//            utf8ncpy(item.sUrl, (const char*)sqlite3_column_text(stmt, 10) ,299);
//            
//            utf8ncpy(item.sPubdate, (const char*)sqlite3_column_text(stmt, 11) ,19);
//            
//            item.nVC = sqlite3_column_int(stmt, 12);
//            
//            item.nPV = sqlite3_column_int(stmt, 13);
//            
//            item.nCommentcount = sqlite3_column_int(stmt, 14);
//            
//            item.bEnablecomment = sqlite3_column_int(stmt, 15);
//            
//            item.bEnabledownload = sqlite3_column_int(stmt, 16);
//            
//            item.bEnablerating = sqlite3_column_int(stmt, 17);
//            
//            utf8ncpy(item.sDescription,  (const char*)sqlite3_column_text(stmt, 18) , 449);
//            
//            
//            utf8ncpy(item.sTag,  (const char*)sqlite3_column_text(stmt, 19) , 63);
//            
//            utf8ncpy(item.sSpecialtopic,  (const char*)sqlite3_column_text(stmt, 20) , 63);
//            
//            utf8ncpy(item.sCredit,  (const char*)sqlite3_column_text(stmt, 21) , 31);
//            
//            item.nStudyduration = sqlite3_column_int(stmt, 22);
//            
//            item.nStudyprogress = sqlite3_column_int(stmt, 23);
//            
//            utf8ncpy(item.sLaststudydate,  (const char*)sqlite3_column_text(stmt, 24) , 31);
//            
//            
//            utf8ncpy(item.sFavoritedate,  (const char*)sqlite3_column_text(stmt, 25) , 19);
//            
//            item.bMyCompany = sqlite3_column_int(stmt, 26);
//            
//            item.bIsRated = sqlite3_column_int(stmt, 27);


            utf8ncpy(m_sTitle,  (const char*)sqlite3_column_text(stmt, 28) , 99);
            
            utf8ncpy(m_sImage,  (const char*)sqlite3_column_text(stmt, 29) , 299);
            utf8ncpy(sParentSpecId,  (const char*)sqlite3_column_text(stmt, 30) , 63);
            
            
            m_mutex.Lock();
            
            if(m_lstItem)
                m_lstItem->push_back(item);
            m_mutex.UnLock();
            
            
        }
        ret=TRUE;
        
        if (ret)
        {
            //计算总数
            m_nTotalCount = 0;
            snprintf(sql,sizeof(sql),"SELECT COUNT(*) FROM %s WHERE parentspecid = ? ", m_tablename);
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
            {
                BindParam(stmt, 1, sParentSpecId);

                
                if (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    
                    m_nTotalCount = sqlite3_column_int(stmt, 0);
                }
                
                sqlite3_finalize(stmt);
            }
        }
        
        
        sqlite3_finalize(stmt);
        
        ret = TRUE;
	}
    
	return ret;
}


