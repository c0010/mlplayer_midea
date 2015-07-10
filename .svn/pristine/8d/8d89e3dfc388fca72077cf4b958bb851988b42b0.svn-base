// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmexerciselist.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"
#include "cmfile.h"

TExerciseListItem::TExerciseListItem()
{
    nQuestioncount = 0;
    nCompleteCount = 0;
    nUsercompletecount = 0;
    nCurIndex = 0;
    nRightCount = 0;
    nWrongCount = 0;
    sTrainID = "";
}

int TExerciseListItem::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TExerciseListItem::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{
    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);
    
    return sqlite3_bind_null(stmt, col);
    
}
int TExerciseListItem::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TExerciseListItem::bindItem(sqlite3_stmt* stmt) const
{
    BindParam(stmt, 1, sID.c_str());
    BindParam(stmt, 2, sTitle.c_str());
    BindParam(stmt, 3, nQuestioncount);
    BindParam(stmt, 4, nCompleteCount);
    BindParam(stmt, 5, sDesc.c_str());
    BindParam(stmt, 6, sCategory.c_str());
    BindParam(stmt, 7, nUsercompletecount);
    BindParam(stmt, 8, sPubdate.c_str());
    BindParam(stmt, 9, nCurIndex);
    BindParam(stmt, 10, nWrongCount);
    BindParam(stmt, 11, nRightCount);
    BindParam(stmt,12,sTrainID.c_str());
}

TExerciseListItem::~TExerciseListItem()
{
   
}

const char* TExerciseListItem::GetExerciseListItemID() const
{
    return sID.c_str();
}

const char* TExerciseListItem::GetExerciseListItemTitle() const
{
    return sTitle.c_str();
}

const char* TExerciseListItem::GetExerciseListItemDesc() const
{
    return sDesc.c_str();
}

const char* TExerciseListItem::GetExerciseListItemCategory() const
{
    return sCategory.c_str();
}

const char* TExerciseListItem::GetExerciseListItemPubdate() const
{
    return sPubdate.c_str();
}

CMExerciseList::CMExerciseList()
{
	sprintf(m_tablename,"exerciselist");
}


CMExerciseList::~CMExerciseList()
{

}

void CMExerciseList::SetListener(IMUpdateDataListener* pListener)
{
	m_pListener = pListener;
}

BOOL CMExerciseList::GetList()
{
    if (IsRunning())
        return FALSE;
    
    n_sTrainID = "";

    if(CMGlobal::TheOne().IsOffline())
    {
        LoadFromDB();
        if (m_pListener)
            m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
        return TRUE;
        
    }
    else
    {
       	return Request(SERVICE_GETEXERCISELIST, "");
    }
}

BOOL CMExerciseList::GetTrainList(const char* sTrainId)
{
	if(IsRunning())
		return FALSE;
	n_sTrainID = sTrainId;

	if(CMGlobal::TheOne().IsOffline())
	{
		LoadFromDB();
		if (m_pListener)
			m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
		return TRUE;

	}
	else
	{
		char sParam[200];
		memset(sParam, 0, 200);

		snprintf(sParam, 200, "id=%s",sTrainId);

		return Request(SERVICE_GETMYTRAINEXERCISELIST,sParam);
	}

}

BOOL CMExerciseList::GetExerciseById(const char* exerciseId)
{
    if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
        return FALSE;
    
    
    if (strlen(exerciseId) == 0) {
        return FALSE;
    }
    
    char sParam[200];
    snprintf(sParam,200,"id=%s",exerciseId);
    
    SetPaging(FALSE);
    
    return Request(SERVICE_GETEXERCISEBYID,sParam);

    
    
}

BOOL CMExerciseList::CheckExerciseListIsExit(const char *sID)
{
    BOOL ret = FALSE;
    if(strlen(m_tablename)==0)
        return ret;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    sqlite3*db=CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;
    
    int nCount = 0;
    
    snprintf(sql, 1024,"SELECT COUNT(*) FROM %s WHERE id=?", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, sID);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            nCount = sqlite3_column_int(stmt, 0);
            if (nCount > 0)
                ret = TRUE;
        }
        
        sqlite3_finalize(stmt);
    }
    else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}
    return ret;
}

BOOL CMExerciseList::LoadFromDB()
{
    BOOL ret = FALSE;
    
    if(m_lstItem)
		m_lstItem->clear();
	else
		m_lstItem = new CMList<TExerciseListItem>;
	
    
    sqlite3* db = CheckTable(m_tablename);
    
    if (!db)
        return ret;
    
    char* errorMsg;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
    }
    
    ret = DoGetCacheItems(db);
    
    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
    }
    
    
    return   ret;
}


BOOL CMExerciseList::DoCreate(sqlite3 *db)
{
    if (db == NULL)  return FALSE;
	if (strcmp(m_tablename, "") == 0) return FALSE;
    
	char *errorMsg;
	char sql[1024];
	snprintf(sql,sizeof(sql),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,title TEXT,questioncount INTEGER,uncompletecount INTEGER,desc TEXT,category TEXT,usercompletecount INTEGER,pubdate TEXT,curindex INTEGER,nwrongcount INTEGER, rightcount INTEGER,trainid TEXT DEFAULT '')", m_tablename);
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK)
    {
		return TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
}

BOOL CMExerciseList::DoRefresh(TExerciseListItem& obj)
{
	BOOL ret = FALSE;

    
	if (strcmp(m_tablename, "") == 0)
        return FALSE;

	//根据obj的sID属性更新
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	sqlite3*db=CheckTable(m_tablename);

	if (db == NULL)
		return FALSE;


	snprintf(sql,sizeof(sql),"SELECT id,title,questioncount,uncompletecount,desc,category,usercompletecount,pubdate,curindex,nwrongcount,rightcount,trainid FROM %s WHERE id = ?", m_tablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, obj.sID.c_str());
        
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            
            obj.sID = (const char*)sqlite3_column_text(stmt, 0);
            
//            obj.sTitle = (const char*)sqlite3_column_text(stmt, 1);
            
//            obj.nQuestioncount = sqlite3_column_int(stmt, 2);
            
            obj.nCompleteCount = sqlite3_column_int(stmt, 3);
            
//            obj.sDesc = (const char*)sqlite3_column_text(stmt, 4);
            
//            obj.sCategory = (const char*)sqlite3_column_text(stmt, 5);
            
            obj.nUsercompletecount = sqlite3_column_int(stmt, 6);
            
//            obj.sPubdate = (const char*)sqlite3_column_text(stmt, 7);
            
            obj.nCurIndex = sqlite3_column_int(stmt, 8);
            
            obj.nWrongCount = sqlite3_column_int(stmt, 9);
            
            obj.nRightCount = sqlite3_column_int(stmt, 10);
            
//            obj.sTrainID = (const char*)sqlite3_column_text(stmt,11);

            m_mutex.Lock();
            
            for (int i = 0; i < m_lstItem->size(); i++) {
                TExerciseListItem& item = m_lstItem->at(i);
                
                if (strcmp(item.sID.c_str(), obj.sID.c_str()) == 0) {
                    item = obj;
                    ret = TRUE;
                    break;
                }
            }
            m_mutex.UnLock();

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

BOOL CMExerciseList::DoUpdate(const TExerciseListItem& obj)
{
    BOOL ret = FALSE;
    
    //更新对象
    m_mutex.Lock();
    
    for (int i = 0; i < m_lstItem->size(); i++)
    {
        TExerciseListItem& item = m_lstItem->at(i);
        
        if (strcmp(item.sID.c_str(), obj.sID.c_str()) == 0) {
            item = obj;
            ret = TRUE;
            break;
        }
    }
    m_mutex.UnLock();
    
	if (strcmp(m_tablename, "") == 0)
        return FALSE;
    
    //保存入数据库
    sqlite3*db=CheckTable(m_tablename);
    
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"UPDATE %s SET id=?, title=?, questioncount=?, uncompletecount=?, desc=?, category=?, usercompletecount=?, pubdate=?,curindex=?,nwrongcount=?,rightcount=?,trainid=? WHERE id=? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            BindParam(stmt, 1, obj.sID.c_str());
            BindParam(stmt, 2, obj.sTitle.c_str());
            BindParam(stmt, 3, obj.nQuestioncount);
            BindParam(stmt, 4, obj.nCompleteCount);
            BindParam(stmt, 5, obj.sDesc.c_str());
            BindParam(stmt, 6, obj.sCategory.c_str());
            BindParam(stmt, 7, obj.nUsercompletecount);
            BindParam(stmt, 8, obj.sPubdate.c_str());
            BindParam(stmt, 9, obj.nCurIndex);
            BindParam(stmt, 10, obj.nWrongCount);
            BindParam(stmt, 11, obj.nRightCount);
            BindParam(stmt, 12, obj.sTrainID.c_str());
            if(sqlite3_step(stmt)==SQLITE_DONE)
            {
                ret = TRUE;
            }
            else
            {
            	CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
            }
        }
        else
        {
        	CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
    }
    
    return ret;
}

BOOL CMExerciseList::DoPutItem(TiXmlElement* pItem, sqlite3* db, TExerciseListItem& item)
{
	BOOL ret = FALSE;
	const CHAR* pStr = NULL;

	pStr = pItem->Attribute("id");
	if(pStr)
        item.sID = pStr;
    
	pStr = pItem->Attribute("title");
	if(pStr)
        item.sTitle = pStr;
    
    pItem->QueryIntAttribute("questioncount", &item.nQuestioncount);
    

//    pItem->QueryIntAttribute("uncompletecount", &item.nCompleteCount);
    
	pStr = pItem->Attribute("desc");
	if(pStr)
        item.sDesc = pStr;
    
	pStr = pItem->Attribute("category");
	if(pStr)
        item.sCategory = pStr;
    
    pItem->QueryIntAttribute("usercompletecount", &item.nUsercompletecount);
    
	pStr = pItem->Attribute("pubdate");
	if(pStr)
        item.sPubdate = pStr;
    
    int temp = 0;
    item.nCurIndex = temp;
    item.nWrongCount = 0;
    item.nRightCount = 0;

    item.sTrainID = n_sTrainID;

	if (strcmp(m_tablename, "") == 0)
	{
		//表名为空，不入库，返回成功
		return TRUE;
	}
    
    if (CheckExerciseListIsExit(item.sID.c_str())) {
        //该练习存在,无需更新表,直接从表里读数据
        Refresh(item);
//        return TRUE;
    }
    else
    {
        GetExerciseData(item.sID.c_str(), item);
    }
    
	CHAR sql[1024];
	sqlite3_stmt *stmt;
    snprintf(sql,sizeof(sql),"REPLACE INTO %s(id,title,questioncount,uncompletecount,desc,category,usercompletecount,pubdate,curindex,nwrongcount,rightcount,trainid) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        BindParam(stmt, 1, item.sID.c_str());
        BindParam(stmt, 2, item.sTitle.c_str());
        BindParam(stmt, 3, item.nQuestioncount);
        BindParam(stmt, 4, item.nCompleteCount);
        BindParam(stmt, 5, item.sDesc.c_str());
        BindParam(stmt, 6, item.sCategory.c_str());
        BindParam(stmt, 7, item.nUsercompletecount);
        BindParam(stmt, 8, item.sPubdate.c_str());
        BindParam(stmt, 9, item.nCurIndex);
        BindParam(stmt, 10, item.nWrongCount);
        BindParam(stmt, 11, item.nRightCount);
        BindParam(stmt, 12, item.sTrainID.c_str());
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
    else
    {
    	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
    }
    
    return  ret;
}


BOOL CMExerciseList::DoGetCacheItems(sqlite3* db)
{
	if (strcmp(m_tablename, "") == 0)
        return FALSE;
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	snprintf(sql,sizeof(sql),"SELECT id,title,questioncount,uncompletecount,desc,category,usercompletecount,pubdate,curindex,nwrongcount,rightcount,trainid FROM %s WHERE trainid=? ORDER BY _id ASC", m_tablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt,1,n_sTrainID.c_str());
        m_mutex.Lock();
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
        	TExerciseListItem item;
            
            item.sID = (const char*)sqlite3_column_text(stmt, 0);
            
            item.sTitle = (const char*)sqlite3_column_text(stmt, 1);
            
            item.nQuestioncount = sqlite3_column_int(stmt, 2);
            
            item.nCompleteCount = sqlite3_column_int(stmt, 3);
            
            item.sDesc = (const char*)sqlite3_column_text(stmt, 4);
            
            item.sCategory = (const char*)sqlite3_column_text(stmt, 5);
            
            item.nUsercompletecount = sqlite3_column_int(stmt, 6);
            
            item.sPubdate = (const char*)sqlite3_column_text(stmt, 7);
            
            item.nCurIndex = sqlite3_column_int(stmt, 8);
            
            item.nWrongCount = sqlite3_column_int(stmt, 9);
            
            item.nRightCount = sqlite3_column_int(stmt, 10);
            
            item.sTrainID = (const char*)sqlite3_column_text(stmt, 11);

        	m_lstItem->push_back(item);
            
            ret = TRUE;

        }
        m_mutex.UnLock();
        
        sqlite3_finalize(stmt);
        
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
    
	return ret;
}


void CMExerciseList::DoClear()
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
}


BOOL CMExerciseList::GetExerciseData(const char *eid, TExerciseListItem &item)
{
    BOOL ret = FALSE;
    CMString sPath = CMGlobal::TheOne().GetUserDir() + L"examexercise.xml";
    TiXmlDocument *pDoc = new TiXmlDocument(sPath);
    if(!pDoc)
		return ret;
	if(CMFile::FileExist(sPath))
	{
		pDoc->LoadFile(TIXML_ENCODING_UTF8);
        
		if(!pDoc->Error())
		{
			TiXmlElement *pRoot = pDoc->RootElement();
			if(pRoot)
			{
				TiXmlElement* pQuestion = pRoot->FirstChildElement("question");
				while(pQuestion)
				{
					const char* sid = pQuestion->Attribute("id");
                    
					if (strcmp(sid, eid) == 0)
					{
                        int curindex = 0;
                        pQuestion->QueryIntAttribute("index", &curindex);
                        item.nCurIndex = curindex;
                        
                        int rightcount = 0;
                        pQuestion->QueryIntAttribute("rightcount", &rightcount);
                        item.nRightCount = rightcount;
                        
                        TiXmlElement* pItem = pQuestion->FirstChildElement("item");
                        
                        int wrongcount = 0;
                        while (pItem)
                        {
                            int nWrong = 0;
                            pItem->Attribute("iswrong", &nWrong);
                            if (nWrong == 1) {
                                wrongcount++;
                            }
                            pItem = pItem->NextSiblingElement("item");
                        }
                        item.nWrongCount = wrongcount;
                    }
                    pQuestion = pQuestion->NextSiblingElement("question");
                }
            }
        }
    }
    
	SAFEDELETE(pDoc);
    
    return ret;
}


void CMExerciseList::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    INT32 result = TResult::EUnknownError;

    if (nCode == MER_OK)
    {
    //获得根元素res。
    TiXmlElement *pItem = pDoc->RootElement();
    if(pItem)
    {
        INT32 nCmdID = 0;
        pItem->QueryIntAttribute("no", &nCmdID);
        
        INT32 nErr = 0;
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
        {
            if (nErr == 0)
            {
                
                if (nCmdID  ==  SERVICE_GETEXERCISELIST || nCmdID == SERVICE_GETEXERCISEBYID||nCmdID == SERVICE_GETMYTRAINEXERCISELIST)
                {
                    sqlite3* db = CheckTable();
                    if(db)
                    {
                        DoCreate(db);
                    }
                    pItem = pItem->FirstChildElement("item");

                    char* errorMsg;
                    
                    if (m_lstItem) {
                        m_lstItem->clear();
                    }
                    
		            if (db != NULL && sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
		            {
		            	CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
		            }

					while(pItem)
					{
                        TExerciseListItem a;
						if (DoPutItem(pItem, db, a))
						{
							m_lstItem->push_back(a);
						}

                        pItem = pItem->NextSiblingElement("item");
					}
                    
                    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
		            {
		            	CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
		            }

                    if(GetItemCount() > 0)
						result = TResult::ESuccess;
					else
						result = TResult::ENothing;

                }
                
            }
            else
            {
                result = TResult::ENetDisconnect;
                LoadFromDB();
            }
        }
     }
    }
    else
    {
        LoadFromDB();
        result = TResult::ENetDisconnect;
    }
    if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData, result);

}
