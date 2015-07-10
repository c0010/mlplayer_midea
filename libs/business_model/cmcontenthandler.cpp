// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmcontenthandler.h"
#include "cmglobal.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "utf8ncpy.h"
#include "sqlite3.h"
//#include "cmcourseinfo.h"

int CMContenthandler::GetHeadItemModel(int nIndex)
{
    
    if(m_lstHeadItem)
    {
        if(nIndex >= 0 && nIndex < m_lstHeadItem->size())
        {
            TBrowserItem * temp ;
            
            temp=m_lstHeadItem->at(nIndex);
            
            return temp->nModel;
        }
        else
            return -1;
    }
    else
        return -1;
}


int CMContenthandler::GetItemModel(int nIndex)
{
    
    if(m_lstItem)
    {
        if(nIndex >= 0 && nIndex < m_lstItem->size())
        {
            TBrowserItem * temp = m_lstItem->at(nIndex);
        
            return temp->nModel;
        }
        else
            return -1;
        
    }
    else
        return -1;
    
}

CMContenthandler::~CMContenthandler()
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
        
        SAFEDELETE(m_lstHeadItem);

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
        SAFEDELETE(m_lstItem);
    }
    m_mutex.UnLock();

    
    m_pListener=NULL;
    m_pRatingListener=NULL;
}

CMContenthandler::CMContenthandler()
:CMHandler<TBrowserItem*>()
,m_lstHeadItem(NULL)
{
    m_pRatingListener=NULL;
    m_lstHeadItem = new CMList<TBrowserItem*>;
}

void CMContenthandler::SetListener(IMUpdateDataListener* pListener, IMRatingListener* pRatingListener)
{
    m_pListener=pListener;
    m_pRatingListener= pRatingListener;
}

//CMContenthandler& CMContenthandler::operator=(const CMContenthandler& right)
//{
//
//    utf8ncpy(m_tablename, right.m_tablename,63);
//	m_tablename[63] = '\0';
//
//    m_bPaging=right.m_bPaging;
//
//    return *this;
//}

int CMContenthandler::GetHeadItemCount()
{
	int size;
	m_mutex.Lock();
    if(m_lstHeadItem)
        size = m_lstHeadItem->size();
    else
        size=0;
	m_mutex.UnLock();
	return size;
}

BOOL CMContenthandler::GetHeadItem(int nIndex, TBrowserItem*& item)
{
	BOOL ret = FALSE;

	m_mutex.Lock();
	if(nIndex < m_lstHeadItem->size() && nIndex >= 0)
	{
		*item = *m_lstHeadItem->at(nIndex);
		ret = TRUE;
	}
	m_mutex.UnLock();

	return ret;
}

BOOL CMContenthandler::Rating(const char* sID)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
	char str[64];
	snprintf(str,64,"&id=%s",sID);
    utf8ncpy(ratingID, sID, 63);
    
	m_bRatting = TRUE;
    m_nServiceNo=SERVICE_RATING;
    
	m_pSession->Command(SERVICE_RATING,str);
	return TRUE;
}

BOOL CMContenthandler::RatingCourseinfo(const char* CoursewareID)
{
    if(strlen(CoursewareID)==0)
        return FALSE;
    
	if(!m_pSession)
		m_pSession = new CMSession(this);
    
	if(m_pSession->IsRunning())
		return FALSE;
    
	char str[64];
	snprintf(str,64,"&id=%s",CoursewareID);
    utf8ncpy(ratingID, CoursewareID, 63);
    
	m_bRatting = TRUE;
    
    m_nServiceNo=SERVICE_RATINGCOURSEWARE;
    
	m_pSession->Command(SERVICE_RATINGCOURSEWARE,str);
	return TRUE;
}

BOOL CMContenthandler::DoCreate(sqlite3* db)
{
	char *errorMsg;
	char sql[1024];
    
    BOOL ret = FALSE;
    
    if(strlen(m_tablename)!=0)
    {
        snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE)", m_tablename);
        
        if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
            ret = TRUE;
        }
        else
        {
            CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
            ret = FALSE;
        }
    }
    
    memset(sql, 0, sizeof(sql));
    
    if(ret == FALSE)
        return FALSE;
    
    if(strlen(kCourseTable)==0)
        return FALSE;
    
	snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,flag TEXT,title TEXT,brief TEXT,largeimage TEXT,image TEXT,thumb TEXT,type TEXT,coursewarecount INTEGER,url TEXT,pubdate TEXT,vc INTEGER,pv INTEGER,commentcount INTEGER,enablecomment INTEGER,enabledownload INTEGER,enablerating INTEGER,enableshare INTEGER,description TEXT,tag TEXT,specialtopic TEXT,credit TEXT,studyduration INTEGER,studyprogress INTEGER,laststudydate TEXT,favoritedate TEXT,mycompany INTEGER,israted INTEGER,markid TEXT,marktitle TEXT,model INTEGER,setid TEXT,islearned INTEGER,downloadurl TEXT,markpicurl TEXT,orientation TEXT,commonstar TEXT,mystar INTEGER, author TEXT, language TEXT, coursetype TEXT, courselevel TEXT, developtime TEXT, courseversion TEXT,starcount INTEGER)", kCourseTable);
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		return TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
    
}


void CMContenthandler::DoClear()
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
    
    if(strlen(m_tablename)==0)
        return;
    
    sqlite3* db = CheckTable(m_tablename);
    
    
    if(db != NULL)
    {
        
        CHAR sql[1024];
        sql[0] = '\0';
        char* errorMsg;
        
        snprintf(sql,1024,"DELETE FROM %s", m_tablename);
        
        if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
        }
        
    }
    
}
/**
 *	根据nModel判别课件，课程，并在堆上开辟空间，防止item提前释放
 *
 *	@param	pItem	传回的xml
 *	@param	db	可操作的数据库指针
 *	@param	item	要接受处理的item,处理后数据存入其中
 *
 *	@return
 */
BOOL CMContenthandler::DoPutItem(TiXmlElement* pItem, sqlite3* db, TBrowserItem*& item)
{

    if(!db)
        return FALSE;
    
    if(pItem != NULL)
        *item=pItem;
    
    if (item->bIsHeadItem)
    {
        if(m_lstHeadItem)
            m_lstHeadItem->push_back(item);
    }
    else
    {
        if(m_lstItem)
            m_lstItem->push_back(item);
    }
    
    if(strlen(m_tablename)==0)
        return FALSE;
    
    CHAR sql[1024];
    
    BOOL ret = FALSE;
    
	sqlite3_stmt *stmt;
    
    snprintf(sql,1024,"REPLACE INTO %s(id) VALUES (?)", m_tablename);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        
        BindParam(stmt, 1, item->sID);
        
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
    
    if(ret == TRUE)
    {
        if(DoSaveTBrowseitem(db, *item))
        {
            return ret;
        }
        else
            return FALSE;
    }
    
    return  ret;
}

BOOL CMContenthandler::DoGetItem(int nIndex, TBrowserItem*& item)
{
	BOOL ret = FALSE;

	//暂不支持空指针
	if (item == NULL) return ret;

	m_mutex.Lock();
	if(nIndex < m_lstItem->size() && nIndex >= 0)
	{
		*item = *m_lstItem->at(nIndex);
		ret = TRUE;
	}
	m_mutex.UnLock();

	return ret;
}

BOOL CMContenthandler::DoRefresh(TBrowserItem*& obj)
{
    
    BOOL ret = FALSE;
    
    m_mutex.Lock();
    
    for (int i = 0; i < m_lstItem->size(); i++) {
        TBrowserItem* item = m_lstItem->at(i);
        if (strcmp(item->sID, obj->sID) == 0) {
            *obj =  *item;
            ret = TRUE;
            CM_ERRP("DoRefresh %s success ", item->sID);
            break;
        }
    }
    m_mutex.UnLock();
    
    if(strlen(kCourseTable)==0)
        return FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	sqlite3*db=CheckTable(kCourseTable);
    
	if (db == NULL)
		return FALSE;
    
	snprintf(sql,1024,"SELECT * FROM %s WHERE id = ?", kCourseTable);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, obj->sID);
        
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            
            obj->fetchItem(stmt);
            ret = TRUE;
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


BOOL CMContenthandler::DoUpdate(TBrowserItem* const & obj)
{
    
    m_mutex.Lock();
    
    for (int i = 0; i < m_lstItem->size(); i++) {
        TBrowserItem* item = m_lstItem->at(i);
        
        if (strcmp(item->sID, obj->sID) == 0) {
            *item = *obj;
            CM_ERRP("DoRefresh %s success. title: %s  \n", item->sID,item->sTitle);
            break;
        }
    }
    
    for (int i = 0; i < m_lstHeadItem->size(); i++) {
        TBrowserItem* item = m_lstHeadItem->at(i);
        
        if (strcmp(item->sID, obj->sID) == 0) {
            *item = *obj;
            
            
            break;
        }
    }
    m_mutex.UnLock();
    
    if(strlen(kCourseTable)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    sqlite3*db=CheckTable(kCourseTable);
    
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[1024];
		snprintf(sql,1024,"UPDATE %s SET id=?, flag=?, title=?, brief=?, largeimage=?, image=?, thumb=?, type=?, coursewarecount=?, url=?, pubdate=?, vc=?, pv=?, commentcount=?, enablecomment=?, enabledownload=?, enablerating=?,enableshare=?, description=?, tag=?, specialtopic=?, credit=?, studyduration=?, studyprogress=?, laststudydate=?, favoritedate=?, mycompany=?, israted=?, markid=?, marktitle=?, model=?, setid=?, islearned=?, downloadurl=?, markpicurl=?, orientation=?,commonstar=?,mystar=?,author=?,language=?,coursetype=?,courselevel=?,developtime=?,courseversion=?,starcount=? WHERE id=? ", kCourseTable);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
        	obj->bindItem(stmt);
            
            BindParam(stmt, kDbColumnIndex+1, obj->sID);
            
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


BOOL CMContenthandler::DoGetCacheItems(sqlite3* db)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    snprintf(sql,1024,"SELECT main.*   FROM %s AS sub  LEFT JOIN %s AS main ON sub.id = main.id  ",m_tablename,kCourseTable );
    if (m_bPaging)
    {
        snprintf(sql,1024,"%s LIMIT %d OFFSET %d", sql, m_nPageSize, (m_nPageNo - 1)*m_nPageSize);
    }
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        
        if(!m_bPaging || m_nPageNo==1)
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
        
        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
            if (sqlite3_column_int(stmt, 30)==0)//根据model判断课程还是课件
            {
                TClassItem* item=new TClassItem();
                item->fetchItem(stmt);
                
                m_mutex.Lock();
                
                if (item->bIsHeadItem)
                {
                    if(m_lstHeadItem)
                        m_lstHeadItem->push_back(item);
                }
                else
                    if(m_lstItem)
                        m_lstItem->push_back(item);
                m_mutex.UnLock();
                
            }else
            {
                TCoursewareItem* item=new TCoursewareItem();
                item->fetchItem(stmt);
                
                m_mutex.Lock();
                
                if (item->bIsHeadItem)
                {
                    if(m_lstHeadItem)
                        m_lstHeadItem->push_back(item);
                }
                else
                    if(m_lstItem)
                        m_lstItem->push_back(item);
                m_mutex.UnLock();
                
            }
        }
        sqlite3_finalize(stmt);

        if (ret)
        {
            m_nTotalCount = 0;
            snprintf(sql,1024,"SELECT main.*   FROM %s AS sub  LEFT JOIN %s AS main ON sub.id = main.id",m_tablename,kCourseTable);
            
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
            {
                if (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    m_nTotalCount = sqlite3_column_int(stmt, 0);
                }
                
            }
            else{
                CM_ERRP("db fail; %s",sqlite3_errmsg(db));
            }
            
            sqlite3_finalize(stmt);

            
        }
        
        
       // sqlite3_finalize(stmt);
        
        ret = TRUE;
	}
    else
        CM_ERRP("db fail; %s",sqlite3_errmsg(db));

	if(m_nTotalCount==0){
		ret=FALSE;
	}

	return ret;
}

/**
 *	http回调方法
 *
 *	@param	nCmdID	请求接口号
 *	@param	nCode	返回参数
 *	@param	pDoc	返回的xml
 */
void CMContenthandler::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;

	if (nCmdID == SERVICE_RATING || nCmdID == SERVICE_RATINGCOURSEWARE )
	{
		if (nCode == MER_OK)
		{
			TiXmlElement *pItem = pDoc->RootElement();

			INT32 nErr = TResult::EUnknownError;
	        m_nTotalCount = 0;
	        m_nPageNo = 1;
			pItem->QueryIntAttribute("errno", &nErr);
			if (nErr == TResult::ESuccess && nCmdID == m_nServiceNo)
			{
                INT32 nRatting = 0;
                pItem->QueryIntAttribute("rating", &nRatting);

                TBrowserItem* item;
                if(nCmdID == SERVICE_RATING)
                    item = new TClassItem();
                else
                    item = new TCoursewareItem();

                utf8ncpy(item->sID, ratingID, 63);

                Refresh(item);

                if(!item->bIsRated)
                {
                    item->bIsRated=TRUE;
                    item->nPV +=1;
                    Update(item);
                }

                SAFEDELETE(item);

                result = TResult::ESuccess;
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

        if(m_pRatingListener)
            m_pRatingListener->OnRating(m_UserData,0,result);
	}
	else {
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
	        m_nTotalCount = 0;
	        m_nPageNo = 1;
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
                    sqlite3* db = CheckTable();

                    char* errorMsg;

                    if (db != NULL && sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                    {
                        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
                    }

                    m_mutex.Lock();
                    TiXmlElement* pHeadItemList = pItem->FirstChildElement("largeimage");

                    if(pHeadItemList)
                    {
                        TiXmlElement* pHeadItem = pHeadItemList->FirstChildElement("item");

                        while(pHeadItem)
                        {

                            //先监测model

                            const char* flag=NULL;
                            int model=0;

                            flag=pItem->Attribute("flag");

                            pItem->QueryIntAttribute("model",&model);

                            if(model==0)
                            {
                                TBrowserItem* bItem = new TClassItem();
                                bItem->bIsHeadItem=TRUE;
                                bItem->nModel=0;
                                DoPutItem(pHeadItem, db, bItem);

                            }else
                            {

                                TBrowserItem *bItem= new TCoursewareItem();
                                bItem->bIsHeadItem=TRUE;
                                bItem->nModel=1;

                                DoPutItem(pHeadItem, db, bItem);

                            }

                            pHeadItem = pHeadItem->NextSiblingElement("item");

                        }
                    }

                    TiXmlElement* plistItem = pItem->FirstChildElement("item");
                    while(plistItem)
                    {

                        int model=0;

                        plistItem->QueryIntAttribute("model",&model);

                        if(model==0)
                        {
                            TBrowserItem* bItem= new TClassItem();
                            bItem->bIsHeadItem=FALSE;
                            bItem->nModel=0;
                            DoPutItem(plistItem, db, bItem);
                        }
                        else
                        {
                            TBrowserItem* bItem= new TCoursewareItem();
                            bItem->bIsHeadItem=FALSE;
                            bItem->nModel=1;

                            DoPutItem(plistItem, db, bItem);

                        }
                        plistItem = plistItem->NextSiblingElement("item");
                    }
                    m_mutex.UnLock();

                    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                    {
                        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
                    }

				}
				if(m_lstItem && m_lstItem->size() > 0)
					result = TResult::ESuccess;
				else
					result = TResult::ENothing;
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
}

BOOL CMContenthandler::DoSaveTBrowseitem(sqlite3* db, TBrowserItem&item) {
	if (&item == NULL) {
		return FALSE;
	}

	if (strlen(kCourseTable) == 0) {
		return FALSE;
	}

	CHAR sql[1024];

	BOOL ret = FALSE;

	sqlite3_stmt *stmt;

	snprintf(sql, 1024,
			"REPLACE INTO %s(id,flag,title,brief,largeimage,image,thumb,type,coursewarecount,url,pubdate,vc,pv,commentcount,enablecomment,enabledownload,enablerating,enableshare,description,tag,specialtopic,credit,studyduration,studyprogress,laststudydate,favoritedate,mycompany,israted,markid,marktitle,model,setid,islearned,downloadurl,markpicurl,orientation,commonstar,mystar,author,language,coursetype,courselevel,developtime,courseversion,starcount) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
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

BOOL CMContenthandler::DoGetTBrowseitem(sqlite3* db, const char* id,
		TBrowserItem&item) {
	if (&item == NULL) {
		return FALSE;
	}

	if (strlen(kCourseTable) == 0) {
		return FALSE;
	}

	CHAR sql[1024];

	BOOL ret = FALSE;

	sqlite3_stmt *stmt;

	snprintf(sql, 1024, "SELECT * FROM %s WHERE id = ?", kCourseTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		sqlite3_bind_text(stmt, 1, id, -1, NULL);

		if (sqlite3_step(stmt) == SQLITE_ROW) {
			item.fetchItem(stmt);
			ret = TRUE;
		} else {
			CM_ERRP("sqlite3_prepare_v2 %s failed.error:%s",
					sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return ret;

}

//TClassItem//////////////////////////////


TClassItem::TClassItem()
:TBrowserItem()
{
    memset(sSpecialtopic,0,64);
    
	memset(sCredit,0,32);
    
	nStudyduration = 0;
    
	nStudyprogress = 0;
    
	memset(sLaststudydate,0,32);
    
	fCommonStar="0";

	nMyStar = 0;

	sAuthor="";//课程作者

	sLanguage="";//课程语言种类

	sCourseType="";//课程类别

	sCourseLevel="";//课程级别

	sDevelopTime="";//课程开发时间

	sCourseVersion="";//课程版本号

	nStarCount = 0;

}

TClassItem::~TClassItem()
{
    
}



void TClassItem::fetchItem(sqlite3_stmt* stmt)
{
    
    utf8ncpy(sID, (const char*)sqlite3_column_text(stmt, 1), 63);
    
    utf8ncpy(sFlag, (const char*)sqlite3_column_text(stmt, 2), 15);
    
    utf8ncpy(sTitle, (const char*)sqlite3_column_text(stmt, 3), 99);
    
    utf8ncpy(sBrief, (const char*)sqlite3_column_text(stmt, 4), 119);
    
    utf8ncpy(sLargeimage, (const char*)sqlite3_column_text(stmt, 5) ,299);
    
    utf8ncpy(sImage, (const char*)sqlite3_column_text(stmt, 6) ,299);
    
    utf8ncpy(sThumbs, (const char*)sqlite3_column_text(stmt, 7) ,299);
    
    utf8ncpy(sType , (const char*)sqlite3_column_text(stmt, 8) ,63);
    
    nCoursewarecount = sqlite3_column_int(stmt, 9);
    
    utf8ncpy(sUrl, (const char*)sqlite3_column_text(stmt, 10) ,299);
    
    utf8ncpy(sPubdate, (const char*)sqlite3_column_text(stmt, 11) ,99);
    
    nVC = sqlite3_column_int(stmt, 12);
    
    nPV = sqlite3_column_int(stmt, 13);
    
    nCommentcount = sqlite3_column_int(stmt, 14);
    
    bEnablecomment = sqlite3_column_int(stmt, 15);
    
    bEnabledownload = sqlite3_column_int(stmt, 16);
    
    bEnablerating = sqlite3_column_int(stmt, 17);
    
    bEnableShare = sqlite3_column_int(stmt, 18);

    utf8ncpy(sDescription,  (const char*)sqlite3_column_text(stmt, 19) , 449);
    
    
    utf8ncpy(sTag,  (const char*)sqlite3_column_text(stmt, 20) , 63);
    
    utf8ncpy(sSpecialtopic,  (const char*)sqlite3_column_text(stmt, 21) , 63);
    
    utf8ncpy(sCredit,  (const char*)sqlite3_column_text(stmt, 22) , 31);
    
    nStudyduration = sqlite3_column_int(stmt, 23);
    
    nStudyprogress = sqlite3_column_int(stmt, 24);
    
    utf8ncpy(sLaststudydate,  (const char*)sqlite3_column_text(stmt, 25) , 31);
    
    utf8ncpy(sFavoritedate,  (const char*)sqlite3_column_text(stmt, 26) , 19);
    
    bMyCompany = sqlite3_column_int(stmt, 27);
    
    bIsRated=sqlite3_column_int(stmt, 28);
    
    utf8ncpy(sMarkID,  (const char*)sqlite3_column_text(stmt, 29) , 63);
    
    utf8ncpy(sMarkTitle,  (const char*)sqlite3_column_text(stmt, 30) , 19);
    
    nModel=sqlite3_column_int(stmt, 31);
    
    utf8ncpy(sMarkPicUrl,  (const char*)sqlite3_column_text(stmt, 35) , 299);

    fCommonStar = (const char*)sqlite3_column_text(stmt, 37);
    nMyStar = sqlite3_column_int(stmt, 38);
    sAuthor = (const char*)sqlite3_column_text(stmt, 39);
    sLanguage = (const char*)sqlite3_column_text(stmt, 40);
    sCourseType = (const char*)sqlite3_column_text(stmt, 41);
    sCourseLevel = (const char*)sqlite3_column_text(stmt, 42);
    sDevelopTime = (const char*)sqlite3_column_text(stmt, 43);
    sCourseVersion = (const char*)sqlite3_column_text(stmt, 44);
    nStarCount = sqlite3_column_int(stmt, 45);
}


void TClassItem::bindItem(sqlite3_stmt* stmt) const
{
    
    BindParam(stmt, 1, sID);
    BindParam(stmt, 2, sFlag);
    BindParam(stmt, 3, sTitle);
    BindParam(stmt, 4, sBrief);
    BindParam(stmt, 5, sLargeimage);
    BindParam(stmt, 6, sImage);
    BindParam(stmt, 7, sThumbs);
    BindParam(stmt, 8, sType);
    BindParam(stmt, 9, nCoursewarecount);
    BindParam(stmt, 10, sUrl);
    BindParam(stmt, 11, sPubdate);
    BindParam(stmt, 12, nVC);
    BindParam(stmt, 13, nPV);
    BindParam(stmt, 14, nCommentcount);
    BindParam(stmt, 15, bEnablecomment);
    BindParam(stmt, 16, bEnabledownload);
    BindParam(stmt, 17, bEnablerating);
    BindParam(stmt, 18, bEnableShare);
    BindParam(stmt, 19, sDescription);
    BindParam(stmt, 20, sTag);
    BindParam(stmt, 21, sSpecialtopic);
    BindParam(stmt, 22, sCredit);
    BindParam(stmt, 23, nStudyduration);
    BindParam(stmt, 24, nStudyprogress);
    BindParam(stmt, 25, sLaststudydate);
    BindParam(stmt, 26, sFavoritedate);
    BindParam(stmt, 27, bMyCompany);
    BindParam(stmt, 28, bIsRated);
    BindParam(stmt, 29, sMarkID);
    BindParam(stmt, 30, sMarkTitle);
    BindParam(stmt, 31, nModel);
    
    BindParam(stmt, 35, sMarkPicUrl);

    BindParam(stmt,37,fCommonStar.c_str());
    BindParam(stmt,38,nMyStar);
    BindParam(stmt,39,sAuthor.c_str());
    BindParam(stmt,40,sLanguage.c_str());
    BindParam(stmt,41,sCourseType.c_str());
    BindParam(stmt,42,sCourseLevel.c_str());
    BindParam(stmt,43,sDevelopTime.c_str());
    BindParam(stmt,44,sCourseVersion.c_str());
    BindParam(stmt,45,nStarCount);

}


TClassItem& TClassItem::operator=(const TBrowserItem& right)
{
    TBrowserItem::operator=(right);
    
	utf8ncpy(sSpecialtopic, ((TClassItem&)right).sSpecialtopic,63);
    sSpecialtopic[63] = '\0';
    
	utf8ncpy(sCredit, ((TClassItem&)right).sCredit,31);
    sCredit[31] = '\0';
    
	nStudyduration = ((TClassItem&)right).nStudyduration;
    
	nStudyprogress = ((TClassItem&)right).nStudyprogress;
    
	utf8ncpy(sLaststudydate, ((TClassItem&)right).sLaststudydate,31);
    sLaststudydate[31] = '\0';
    
    fCommonStar = ((TClassItem&)right).fCommonStar;
    nMyStar = ((TClassItem&)right).nMyStar;
    sAuthor = ((TClassItem&)right).sAuthor;
    sLanguage = ((TClassItem&)right).sLanguage;
    sCourseType = ((TClassItem&)right).sCourseType;
    sCourseLevel = ((TClassItem&)right).sCourseLevel;
    sDevelopTime = ((TClassItem&)right).sDevelopTime;
    sCourseVersion = ((TClassItem&)right).sCourseVersion;

	return *this;
}



TClassItem& TClassItem::operator=(const TiXmlElement* right)
{
    TBrowserItem::operator=(right);
    
    const CHAR* pStr = NULL;
    
    
    pStr = right->Attribute("specialtopic");
	if(pStr)
	{
		utf8ncpy(sSpecialtopic,pStr,63);
		sSpecialtopic[63] = '\0';
	}
	else
		sSpecialtopic[0] = '\0';
    
	pStr = right->Attribute("credit");
	if(pStr)
	{
		utf8ncpy(sCredit,pStr,31);
		sCredit[31] = '\0';
	}
	else
		sCredit[0] = '\0';
    
	right->QueryIntAttribute("studyduration",&nStudyduration);
    
	double fStudyprogress = 0.0;
	right->QueryDoubleAttribute("studyprogress",&fStudyprogress);
	nStudyprogress = (int)(100*fStudyprogress);
    
	pStr = right->Attribute("laststudydate");
	if(pStr)
	{
		utf8ncpy(sLaststudydate,pStr,31);
		sLaststudydate[31] = '\0';
	}
	else
		sLaststudydate[0] = '\0';
    
	pStr = right->Attribute("commonstar");
	if(pStr)
		fCommonStar = pStr;

	right->QueryIntAttribute("mystar",&nMyStar);

	right->QueryIntAttribute("starcount", &nStarCount);

	pStr = right->Attribute("author");
	if(pStr)
		sAuthor = pStr;

	pStr = right->Attribute("language");
	if(pStr)
		sLanguage = pStr;

	pStr = right->Attribute("coursetype");
	if(pStr)
		sCourseType = pStr;

	pStr = right->Attribute("courselevel");
	if(pStr)
		sCourseLevel = pStr;

	pStr = right->Attribute("developtime");
	if(pStr)
		sDevelopTime = pStr;

	pStr = right->Attribute("courseversion");
	if(pStr)
		sCourseVersion = pStr;
    
    right->QueryIntAttribute("starcount", &nStarCount);

    return *this;
    
}

void TClassItem::SetListener(IMUpdateDataListener* pUpdateDataListener, IMRatingListener* pRatingListener,IMSimpleResultListener* pSimpleListener)
{
	if(pUpdateDataListener)
		m_pListener = pUpdateDataListener;
	if(pRatingListener)
		m_pRatingListener = pRatingListener;
	if(pSimpleListener)
		m_pSimpleListener = pSimpleListener;
}

BOOL TClassItem::DoComment(const char* sContent, BOOL bsyncqa)
{
    if(!sContent || !sID ||!sFlag)
    {
        CM_ERR("send comment fail!");
		return FALSE;
    }
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    char sComment[1600];
    
    snprintf(sComment,1600,"flag=%s&id=%s&enablesyncqa=%d",sFlag,sID,bsyncqa);

    CMString sParam = sComment;
//	m_nCmdId = SERVICE_MAKECOMMENT;
    
    CMList<FormData>* list= new CMList<FormData>;
    FormData data;
    data.key="content";
    data.value=sContent;
    data.dataType=1;
    list->push_back(data);
    
    m_pSession->CommandPost(SERVICE_MAKECOMMENT, sParam, *list);
    SAFEDELETE(list);
	return TRUE;
    
}



//TBrowserItem///////////////////////

void TBrowserItem::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    INT32 result = TResult::EUnknownError;
	if (nCode == MER_OK)
	{
		ASSERT(pDoc);
		TiXmlElement *pItem = pDoc->RootElement();
        
		INT32 nErr = 0;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no", &nCmdID);
		if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
		{
			if (nErr == 0)
			{
                if(nCmdID == SERVICE_MAKECOMMENT)
                {
                    Refresh();
                    nCommentcount ++;
                    Update();

                    if(m_pListener)
                        m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
                    
                    return;
                }
                
                if(nCmdID == SERVICE_RATING || nCmdID == SERVICE_RATINGCOURSEWARE )
				{
                    INT32 nRatting = 0;
                    pItem->QueryIntAttribute("rating", &nRatting);
                    
                    //要修改

                    Refresh();
                    
                    if(!bIsRated)
                    {
                        bIsRated=TRUE;
                        nPV +=1;
                        Update();
                    }
                    
                    if(m_pRatingListener)
                        m_pRatingListener->OnRating(m_UserData,nRatting,TResult::ESuccess);
                    
                    return;
                    
				}
                else
					result = TResult::EProtocolFormatError;
			}
			else if(nErr == -14 && nCmdID == SERVICE_RATING)
            {
				result = TResult::EDuplicaterating;
            }
			else
				result = TResult::EUnknownError;
		}
		else
			result = TResult::EProtocolFormatError;
	}
	else if(nCode == MERN_INITIALIZE)
	{
		result = TResult::ENetDisconnect;
	}
	else if(nCode==MERN_OFFLINE)
    {
        result=TResult::ENotSupportOffline;
    }
    else
		result = TResult::ENetTimeout;
    
	if(m_bRatting)
	{
		if(m_pRatingListener)
			m_pRatingListener->OnRating(m_UserData,0,result);
		m_bRatting = FALSE;
	}
	else
	{
		if(m_pListener)
			m_pListener->OnUpdateDataFinish(m_UserData, result);
	}
}

void TClassItem::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	if(nCmdID==SERVICE_STARTLEVEL)
	{
        INT32 result = TResult::EUnknownError;
        if (nCode == MER_OK)
        {
        	ASSERT(pDoc);
    		TiXmlElement *pItem = pDoc->RootElement();

    		INT32 nErr = 0;
    		INT32 nCmdID = 0;
    		pItem->QueryIntAttribute("no", &nCmdID);
    		if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
    		{
    			if (nErr == 0)
    			{
    				const char* pStr = NULL;
    				pStr = pItem->Attribute("commonstar");
    				if(pStr)
    					fCommonStar = pStr;
    				nStarCount += 1;
    				Update();

    				if(m_pSimpleListener)
    					m_pSimpleListener->OnRequestFinish(m_UserData,TResult::ESuccess);

    				return;

    			}
    			else if(nErr == -14)
				{
					result = TResult::EDuplicaterating;
				}
				else
					result = TResult::EUnknownError;
    		}
    		else
    			result = TResult::EProtocolFormatError;
        }
    	else if(nCode == MERN_INITIALIZE)
    	{
    		result = TResult::ENetDisconnect;
    	}
    	else if(nCode==MERN_OFFLINE)
        {
            result=TResult::ENotSupportOffline;
        }
        else
    		result = TResult::ENetTimeout;

        Refresh();

        if(m_pSimpleListener)
        	m_pSimpleListener->OnRequestFinish(m_UserData,result);

	}
	else
		TBrowserItem::OnSessionCmd(nCmdID, nCode, pDoc);
}


void TBrowserItem::SetListener(IMUpdateDataListener* pUpdateDataListener,IMRatingListener* pRatingListener,IMSimpleResultListener* pSimpleListener)
{
	m_pListener = pUpdateDataListener;
	m_pRatingListener = pRatingListener;

	if(pSimpleListener)
		m_pSimpleListener = pSimpleListener;
}

void TBrowserItem::SetUserData(void* UserData)
{
	m_UserData = UserData;
}


BOOL TBrowserItem::Rating()
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
	char str[64];
	snprintf(str,64,"&id=%s",sID);
	m_bRatting = TRUE;
    
	m_pSession->Command(SERVICE_RATING,str);
	return TRUE;
}

BOOL TClassItem::CommitStar(int myStar)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	char str[64];
	snprintf(str,sizeof(str),"&id=%s&mystar=%d",sID,myStar);

	nMyStar = myStar;

	m_pSession->Command(SERVICE_STARTLEVEL, str);

	return TRUE;
}

BOOL TBrowserItem::RatingCourseinfo()
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
	char str[64];
	snprintf(str,sizeof(str),"&id=%s",sID);
	m_bRatting = TRUE;
    
	m_pSession->Command(SERVICE_RATINGCOURSEWARE,str);
	return TRUE;
}
sqlite3* TBrowserItem::CheckTable(const char * tablename)
{
    sqlite3 * db=  CMDBHelper::GetInstance(1)->GetConnection();
    
    if (DoCreate(db))
    	return db;
    else
    {
        return NULL;
    }
}

BOOL TBrowserItem::DoCreate(sqlite3* db)
{
	char *errorMsg;
	char sql[1024];
    
	snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,flag TEXT,title TEXT,brief TEXT,largeimage TEXT,image TEXT,thumb TEXT,type TEXT,coursewarecount INTEGER,url TEXT,pubdate TEXT,vc INTEGER,pv INTEGER,commentcount INTEGER,enablecomment INTEGER,enabledownload INTEGER,enablerating INTEGER,enableshare INTEGER,description TEXT,tag TEXT,specialtopic TEXT,credit TEXT,studyduration INTEGER,studyprogress INTEGER,laststudydate TEXT,favoritedate TEXT,mycompany INTEGER,israted INTEGER,markid TEXT,marktitle TEXT,model INTEGER,setid TEXT,islearned INTEGER,downloadurl TEXT,markpicurl TEXT,orientation TEXT,commonstar TEXT,mystar INTEGER, author TEXT, language TEXT, coursetype TEXT, courselevel TEXT, developtime TEXT, courseversion TEXT,starcount INTEGER)", kCourseTable);
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		return TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
    
}


BOOL TBrowserItem::Refresh()
{
    BOOL ret = FALSE;
    
    if(strlen(kCourseTable)==0)
        return FALSE;
    
    
    if(strlen(sID)==0)
        return FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	sqlite3*db=CheckTable(kCourseTable);
    
	if (db == NULL)
		return FALSE;
    
	snprintf(sql,1024,"SELECT * FROM %s WHERE id = ?", kCourseTable);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, sID);
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
        	CM_ERRP("sqlite3_prepare_refresh %s failed.error:%s sid:%s", sql, sqlite3_errmsg(db),sID);
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

BOOL TBrowserItem::Update()
{
    
    if(strlen(kCourseTable)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    sqlite3*db=CheckTable(kCourseTable);
    if(db)
    {
        
		sqlite3_stmt *stmt;
		CHAR sql[1024];
		snprintf(sql,1024,"UPDATE %s SET id=?, flag=?, title=?, brief=?, largeimage=?, image=?, thumb=?, type=?, coursewarecount=?, url=?, pubdate=?, vc=?, pv=?, commentcount=?, enablecomment=?, enabledownload=?, enablerating=? ,enableshare=?, description=?, tag=?, specialtopic=?, credit=?, studyduration=?, studyprogress=?, laststudydate=?, favoritedate=?, mycompany=?, israted=?, markid=?, marktitle=?, model=?, setid=?, islearned=?, downloadurl=?, markpicurl=?, orientation=?, commonstar=?, mystar=?, author=?, language=?, coursetype=?, courselevel=?, developtime=?, courseversion=?, starcount=? WHERE id=?", kCourseTable);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
        	bindItem(stmt);
            
            BindParam(stmt, kDbColumnIndex+1, sID);
            
            
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
BOOL TBrowserItem::SendComment(const char* sContent, BOOL bsyncqa)
{
    return  DoComment( sContent,  bsyncqa);
}


BOOL TBrowserItem::DoComment(const char* sContent, BOOL bsyncqa)
{
    CM_ERR("wrong call!");
    return FALSE;
}


int TBrowserItem::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TBrowserItem::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{
    
    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);
    
    return sqlite3_bind_null(stmt, col);
    
}
int TBrowserItem::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TBrowserItem::bindItem(sqlite3_stmt* stmt) const
{
    
    if(strlen(sID) == 0)
        CM_ERR("item has no id.");
    
    //nothing
    BindParam(stmt, 1,  sID);
    BindParam(stmt, 2,  sFlag);
    BindParam(stmt, 3,  sTitle);
    BindParam(stmt, 4,  sBrief);
    BindParam(stmt, 5,  sLargeimage);
    BindParam(stmt, 6,  sImage);
    BindParam(stmt, 7,  sThumbs);
    BindParam(stmt, 8,  sType);
    BindParam(stmt, 9,  nCoursewarecount);
    BindParam(stmt, 10, sUrl);
    BindParam(stmt, 11, sPubdate);
    BindParam(stmt, 12, nVC);
    BindParam(stmt, 13, nPV);
    BindParam(stmt, 14, nCommentcount);
    BindParam(stmt, 15, bEnablecomment);
    BindParam(stmt, 16, bEnabledownload);
    BindParam(stmt, 17, bEnablerating);
    BindParam(stmt,18,bEnableShare);
    BindParam(stmt, 19, sDescription);
    BindParam(stmt, 20, sTag);
    BindParam(stmt, 26, sFavoritedate);
    BindParam(stmt, 27, bMyCompany);
    BindParam(stmt, 28, bIsRated);
    BindParam(stmt, 29, sMarkID);
    BindParam(stmt, 30, sMarkTitle);
    BindParam(stmt, 31, nModel);
    
    BindParam(stmt, 35, sMarkPicUrl);

}

void TBrowserItem::fetchItem(sqlite3_stmt* stmt)
{
    //nothing
    utf8ncpy(sID, (const char*)sqlite3_column_text(stmt, 1), 63);
    
    utf8ncpy(sFlag, (const char*)sqlite3_column_text(stmt, 2), 15);
    
    utf8ncpy(sTitle, (const char*)sqlite3_column_text(stmt, 3), 99);
    
    utf8ncpy(sBrief, (const char*)sqlite3_column_text(stmt, 4), 119);
    
    utf8ncpy(sLargeimage, (const char*)sqlite3_column_text(stmt, 5) ,299);
    
    utf8ncpy(sImage, (const char*)sqlite3_column_text(stmt, 6) ,299);
    
    utf8ncpy(sThumbs, (const char*)sqlite3_column_text(stmt, 7) ,299);
    
    utf8ncpy(sType , (const char*)sqlite3_column_text(stmt, 8) ,63);
    
    nCoursewarecount = sqlite3_column_int(stmt, 9);
    
    utf8ncpy(sUrl, (const char*)sqlite3_column_text(stmt, 10) ,299);
    
    utf8ncpy(sPubdate, (const char*)sqlite3_column_text(stmt, 11) ,99);
    
    nVC = sqlite3_column_int(stmt, 12);
    
    nPV = sqlite3_column_int(stmt, 13);
    
    nCommentcount = sqlite3_column_int(stmt, 14);
    
    bEnablecomment = sqlite3_column_int(stmt, 15);
    
    bEnabledownload = sqlite3_column_int(stmt, 16);
    
    bEnablerating = sqlite3_column_int(stmt, 17);
    
    bEnableShare = sqlite3_column_int(stmt, 18);

    utf8ncpy(sDescription,  (const char*)sqlite3_column_text(stmt, 19) , 449);
    
    
    utf8ncpy(sTag,  (const char*)sqlite3_column_text(stmt, 20) , 63);
    
    utf8ncpy(sFavoritedate,  (const char*)sqlite3_column_text(stmt, 26) , 19);
    
    bMyCompany = sqlite3_column_int(stmt, 27);
    
    bIsRated=sqlite3_column_int(stmt, 28);
    
    utf8ncpy(sMarkID,  (const char*)sqlite3_column_text(stmt, 29) , 63);
    
    utf8ncpy(sMarkTitle,  (const char*)sqlite3_column_text(stmt, 30) , 19);
    
    nModel=sqlite3_column_int(stmt, 31);
    
    utf8ncpy(sMarkPicUrl,  (const char*)sqlite3_column_text(stmt, 35) , 299);
    
}

TBrowserItem::TBrowserItem()
:m_UserData(NULL)
,m_pListener(NULL)
,m_pRatingListener(NULL)
,m_pSession(NULL)
{
	memset(sID,0,64);
    memset(sFlag,0,16);
    memset(sTitle,0,100);
    memset(sBrief,0,120);
    
    memset(sLargeimage,0,300);
    memset(sImage,0,300);
    memset(sThumbs,0,300);
    memset(sType,0,64);
    nCoursewarecount = 0;
    
    memset(sUrl,0,300);
    memset(sPubdate,0,100);
    
    nVC = 0;
    nPV = 0;
    nCommentcount = 0;
    
    bEnablecomment = FALSE;
    bEnabledownload = FALSE;
    bEnablerating = FALSE;
    bEnableShare = TRUE;
    memset(sDescription,0,450);
    
    memset(sTag,0,64);
    memset(sFavoritedate,0,20);

    bIsHeadItem=FALSE;
    
    bMyCompany = FALSE;
    
    nModel=0;
    bIsRated=FALSE;
    
    memset(sMarkID, 0,64);
    memset(sMarkTitle, 0, 20);
    memset(sMarkPicUrl, 0, 300);
    
}

void TBrowserItem::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

TBrowserItem::~TBrowserItem()
{
    if(m_pSession)
        m_pSession->Cancel();
    
    SAFEDELETE(m_pSession);
}

TBrowserItem::TBrowserItem(const TBrowserItem& right)
:m_UserData(NULL)
,m_pListener(NULL)
,m_pRatingListener(NULL)
,m_pSession(NULL)
{
	*this = right;
}

TBrowserItem& TBrowserItem::operator=(const TBrowserItem& right)
{
	utf8ncpy(sID, right.sID,63);
	sID[63] = '\0';
    
    utf8ncpy(sFlag, right.sFlag,15);
    sFlag[15] = '\0';
    
    utf8ncpy(sTitle, right.sTitle,99);
    sTitle[99] = '\0';

    utf8ncpy(sBrief, right.sBrief,119);
    sBrief[119] = '\0';
	
    utf8ncpy(sLargeimage, right.sLargeimage,299);
    sLargeimage[299] = '\0';
    
    utf8ncpy(sImage, right.sImage,299);
    sImage[299] = '\0';
    
    utf8ncpy(sThumbs, right.sThumbs,299);
    sThumbs[299] = '\0';
    
    utf8ncpy(sType, right.sType,63);
    sType[63] = '\0';
    
    nCoursewarecount = right.nCoursewarecount;
    
    utf8ncpy(sUrl, right.sUrl,299);
    sUrl[299] = '\0';
    
    utf8ncpy(sPubdate, right.sPubdate,99);
    sPubdate[99] = '\0';
    
    nVC = right.nVC;
    
    nPV = right.nPV;
    
    nCommentcount = right.nCommentcount;
    
    bEnablecomment = right.bEnablecomment;
    
    bEnabledownload = right.bEnabledownload;
    
    bEnablerating = right.bEnablerating;
    
    bEnableShare = right.bEnableShare;

    utf8ncpy(sDescription, right.sDescription,449);
    sDescription[449] = '\0';
    
    utf8ncpy(sTag, right.sTag,63);
    sTag[63] = '\0';
    
    
    utf8ncpy(sFavoritedate, right.sFavoritedate,19);
    sFavoritedate[19] = '\0';
    
    bMyCompany = right.bMyCompany;
    
    bIsRated=right.bIsRated;
    
    nModel=right.nModel;

    bIsHeadItem=right.bIsHeadItem;
    
    utf8ncpy(sMarkID, right.sMarkID,63);
    
    utf8ncpy(sMarkTitle, right.sMarkTitle,19);
    
    
    utf8ncpy(sMarkPicUrl, right.sMarkPicUrl,299);
    
	return *this;
}

TiXmlElement* TBrowserItem::CreateXmlElement() const
{
	TiXmlElement* pItem = new TiXmlElement("item");
	pItem->SetAttribute("id", sID);
	pItem->SetAttribute("flag", sFlag);
	pItem->SetAttribute("title", sTitle);
	pItem->SetAttribute("brief", sBrief);
	pItem->SetAttribute("largeimage", sLargeimage);
	pItem->SetAttribute("image", sImage);
	pItem->SetAttribute("thumbs", sThumbs);
	pItem->SetAttribute("type", sType);
	pItem->SetAttribute("coursewarecount", nCoursewarecount);
	pItem->SetAttribute("url", sUrl);
	pItem->SetAttribute("pubdate", sPubdate);
	pItem->SetAttribute("vc", nVC);
	pItem->SetAttribute("pv", nPV);
	pItem->SetAttribute("commentcount", nCommentcount);
	pItem->SetAttribute("enablecomment", bEnablecomment);
	pItem->SetAttribute("enabledownload", bEnabledownload);
	pItem->SetAttribute("enablerating", bEnablerating);
	pItem->SetAttribute("description", sDescription);
	pItem->SetAttribute("tag", sTag);

	pItem->SetAttribute("favoritedate", sFavoritedate);
	pItem->SetAttribute("mycompany", bMyCompany);
    pItem->SetAttribute("israted", bIsRated);
    
    

    
	return pItem;
}

TBrowserItem& TBrowserItem::operator=(const TiXmlElement* right)
{
	const CHAR* pStr = NULL;
    
	pStr = right->Attribute("id");
	if(pStr)
	{
		utf8ncpy(sID,pStr,63);
		sID[63] = '\0';
	}
	else
		sID[0] = '\0';
    
	pStr = right->Attribute("flag");
	if(pStr)
	{
		utf8ncpy(sFlag,pStr,15);
		sFlag[15] = '\0';
	}
	else
		sFlag[0] = '\0';
    
	pStr = right->Attribute("title");
	if(pStr)
	{
		utf8ncpy(sTitle,pStr,99);
		sTitle[99] = '\0';
	}
	else
		sTitle[0] = '\0';

		pStr = right->Attribute("brief");
	if(pStr)
	{
		utf8ncpy(sBrief,pStr,119);
		sBrief[119] = '\0';
	}
	else
		sBrief[0] = '\0';
    
	pStr = right->Attribute("largeimage");
	if(pStr)
	{
		utf8ncpy(sLargeimage,pStr,299);
		sLargeimage[299] = '\0';
	}
	else
		sLargeimage[0] = '\0';
    
	pStr = right->Attribute("image");
	if(pStr)
	{
		utf8ncpy(sImage,pStr,299);
		sImage[299] = '\0';
	}
	else
		sImage[0] = '\0';
    
	pStr = right->Attribute("thumbs");
	if(pStr)
	{
		utf8ncpy(sThumbs,pStr,299);
		sThumbs[299] = '\0';
	}
	else
		sThumbs[0] = '\0';
    
	pStr = right->Attribute("type");
	if(pStr)
	{
		utf8ncpy(sType,pStr,63);
		sType[63] = '\0';
	}
	else
		sType[0] = '\0';
    
	right->QueryIntAttribute("coursewarecount",&nCoursewarecount);
    
	pStr = right->Attribute("url");
	if(pStr)
	{
		utf8ncpy(sUrl,pStr,299);
		sUrl[299] = '\0';
	}
	else
		sUrl[0] = '\0';
    
	pStr = right->Attribute("pubdate");
	if(pStr)
	{
		utf8ncpy(sPubdate,pStr,99);
		sPubdate[99] = '\0';
	}
	else
		sPubdate[0] = '\0';
    
	right->QueryIntAttribute("vc",&nVC);
    
	right->QueryIntAttribute("pv",&nPV);
    
	right->QueryIntAttribute("commentcount",&nCommentcount);
    
	int tmp = 0;
	right->QueryIntAttribute("enablecomment",&tmp);
	bEnablecomment = tmp;
    
	tmp = 0;
	right->QueryIntAttribute("enabledownload",&tmp);
	bEnabledownload = tmp;
    
	tmp = 0;
	right->QueryIntAttribute("enablerating",&tmp);
	bEnablerating = tmp;
    
	tmp = 0;
	right->QueryIntAttribute("enableshare", &tmp);
	bEnableShare = tmp;

	pStr = right->Attribute("description");
	if(pStr)
	{
		utf8ncpy(sDescription,pStr,449);
		sDescription[449] = '\0';
	}
	else
		sDescription[0] = '\0';
    
	
    
	pStr = right->Attribute("tag");
	if(pStr)
	{
		utf8ncpy(sTag,pStr,63);
		sTag[63] = '\0';
	}
	else
		sTag[0] = '\0';
    
	pStr = right->Attribute("favoritedate");
	if(pStr)
	{
		utf8ncpy(sFavoritedate,pStr,19);
		sFavoritedate[19] = '\0';
	}
	else
		sFavoritedate[0] = '\0';
    
	tmp = 0;
	right->QueryIntAttribute("mycompany",&tmp);
	bMyCompany = tmp;
    
    
    tmp = 0;
	right->QueryIntAttribute("israted",&tmp);
	bIsRated = tmp;
    
    
    tmp = 0;
	right->QueryIntAttribute("model",&tmp);
	nModel = tmp;
    
    pStr = right->Attribute("markid");
	if(pStr)
	{
		utf8ncpy(sMarkID,pStr,63);
		sMarkID[63] = '\0';
	}
	else
		sMarkID[0] = '\0';
    
    
    pStr = right->Attribute("markcontent");
	if(pStr)
	{
		utf8ncpy(sMarkTitle,pStr,19);
		sMarkTitle[19] = '\0';
	}
	else
		sMarkTitle[0] = '\0';
    
    
    pStr = right->Attribute("markpicurl");
    
	if(pStr)
	{
		utf8ncpy(sMarkPicUrl,pStr,299);
        sMarkPicUrl[299] = '\0';

	}
	else
		sMarkPicUrl[0] = '\0';
    
    
	return *this;
}

