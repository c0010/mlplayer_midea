// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmexercise.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "cmlist.h"
#include <time.h>
#include <iostream>
#include <ctime>

CMExercise::CMExercise()
	: CMWrongQuestion()
{
    memset(m_tablename, 0, 64);
    
    snprintf(m_tablename,64,"exercisequestion");
    
    memset(m_SubTablename, 0, 64);
    
    snprintf(m_SubTablename,64,"exerciseoption");
    
    m_nCompleteNumber = 0;
    
}


CMExercise::~CMExercise()
{
}

void CMExercise::SetListener(IMUpdateDataListener *pListener, IMSimpleResultListener *pSimpleResultListener)
{
    m_pListener = pListener;
    m_pSimpleResultListener = pSimpleResultListener;
}

void CMExercise::GetExerciseQuestion(const char* sID)
{
    Clear();

    mID = sID;
    
    if(CMGlobal::TheOne().IsOffline())
    {
        if(LoadFromDB())
        {
            if (m_pListener)
                m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
        }
        else
        {
            if (m_pListener)
                m_pListener->OnUpdateDataFinish(m_UserData, TResult::ENetDisconnect);
        }
    }
    else
    {


        //本地是否存在
        if (CheckExerciseIsExit(sID) == GetExerciseCount(sID))
        {
        	LoadFromDB();
            if (m_pListener)
                m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
        }
        else
        {
        	CMQuestionhandler::GetQuestion(SERVICE_GETEXERCISEQUESTION, sID, FALSE);
        }
    }
}

int CMExercise::CheckExerciseIsExit(const char* sID)
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
    
    snprintf(sql, 1024,"SELECT COUNT(*) FROM %s WHERE mid=?", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, sID);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            nCount = sqlite3_column_int(stmt, 0);
        }
        
        sqlite3_finalize(stmt);
    }
    else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}
    
    return nCount;
}

BOOL CMExercise::SetAnswerItem(TQuestion* itemoption,TiXmlElement* pItem)
{
	int flag = 0;
	if(itemoption->item.nType != TQuestionType::EText)
	{
		BOOL bModified = FALSE;
		for (CMList<TOption>::iterator it1 = itemoption->m_lisOption->begin(); it1 != itemoption->m_lisOption->end(); it1++)
		{
			TOption& option = (TOption&)*it1;
			if(&option && option.bMyAnswer != option.bCheck)
				bModified = TRUE;
			if(&option && option.bCheck)
				flag = 1;
		}
		if(bModified == FALSE)
			flag = 2;//未改动，不标记
	}
	else
	{
        
		//练习的问答题始终有答案
        if (strcmp(itemoption->item.sMyAnswer.c_str(), itemoption->item.sAnswer.c_str()) == 0)
            flag=2;
        else
            flag = 1;
        

	}
	
	return TRUE;
}

BOOL CMExercise::LoadFromDB()
{
    BOOL ret = FALSE;
    
    if(m_lstItem)
		m_lstItem->clear();
	else
		m_lstItem = new CMList<TQuestion>;
	
    
    sqlite3* db = CheckTable();
    
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

void CMExercise::SetCompleteNumber(int nNum)
{
    m_nCompleteNumber = nNum;
}



BOOL CMExercise::DoClearAnswer(TQuestion &obj)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    
    UpDateList();

    //更新对象
//    m_mutex.Lock();
//    for (int i = 0; i < m_lstItem->size(); i++) {
//        TQuestion& item = m_lstItem->at(i);
//        
//        if (strcmp(item.item.sID.c_str(), obj.item.sID.c_str()) == 0) {
//            //item = obj;
//            item.item = obj.item;
//            if (item.m_lisOption)
//            {
//                item.m_lisOption->clear();
//            }
//            else
//                item.m_lisOption = new CMList<TOption>;
//            item.m_lisOption->append(*obj.m_lisOption);
//            
//            ret = TRUE;
//            //   CM_ERRP("DoUpdate %s success", item.item.sID);
//            break;
//        }
//    }
//    m_mutex.UnLock();
    
    sqlite3* db = CheckTable();
    
    if(db)
    {
        sqlite3_stmt *stmt;
        
        CHAR sql[512];
        
        snprintf(sql, 512,"UPDATE %s SET iswrong=?, myanswer=?, answer=?, right=?, checked=?,lastupdate=? WHERE  id=? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            BindParam(stmt, 1, obj.item.isWrong);
            
            BindParam(stmt, 2, obj.item.sMyAnswer.c_str());
            
            BindParam(stmt, 3, obj.item.sAnswer.c_str());
            
            BindParam(stmt, 4, obj.item.isRight);
            
            BindParam(stmt, 5, obj.item.isChecked);
            
            BindParam(stmt, 6, sLastUpdate);
            
            BindParam(stmt, 7, obj.item.sID.c_str());
            
            if(sqlite3_step(stmt)==SQLITE_DONE)
            {
                for (int i = 0; i < obj.m_lisOption->size(); i++) {
                    TOption& optionitem = obj.m_lisOption->at(i);
                    optionitem.bCheck = FALSE;
                    optionitem.bMyAnswer = FALSE;
                    DoClearOptionAnswer(db, optionitem);
                }
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

BOOL CMExercise::DoClearOptionAnswer(sqlite3 *db, TOption &obj)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    
    
    sqlite3_stmt *stmt;
    
    CHAR sql[512];
    
    snprintf(sql, 512,"UPDATE %s SET bcheck=?, myanswer=? WHERE  sumid=? ", m_SubTablename);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK){
        
        BindParam(stmt, 1, obj.bCheck);
        
        BindParam(stmt, 2, obj.bMyAnswer);
        
        char sumid[128];
        sprintf(sumid, "%s%s",obj.sSID.c_str(),obj.nID.c_str());
        
        BindParam(stmt, 3, sumid);
        
        if(sqlite3_step(stmt)==SQLITE_DONE)
        {
            ret=TRUE;
        }
        else {
            CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
    }
    else {
        CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    
    return ret;

}


BOOL CMExercise::DoLastUpdate(int lasttime)
{
    BOOL ret = FALSE;
    
    if(strlen(m_tablename)==0)
        return FALSE;
    
    //更新对象
    m_mutex.Lock();
    TQuestion& obj = m_lstItem->at(GetCurIndex());
    sLastUpdate = lasttime;
    m_mutex.UnLock();
    
    sqlite3* db = CheckTable();
    
    if(db)
    {
        sqlite3_stmt *stmt;
        
        CHAR sql[512];
        
        snprintf(sql, 512,"UPDATE %s SET lastupdate=? WHERE  id=? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            BindParam(stmt, 1, sLastUpdate);
            
            BindParam(stmt, 2, obj.item.sID.c_str());
            
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

BOOL CMExercise::UpDateList()
{
    BOOL ret = FALSE;
    //保存入数据库
    sqlite3*db=CheckTable();
    
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"UPDATE %s SET uncompletecount=?,nwrongcount=?,usercompletecount=?, curindex=?,rightcount=? WHERE id=? ", "exerciselist");
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            int nCompletecount = GetDoneCount();
            BindParam(stmt, 1, nCompletecount);
            BindParam(stmt, 2, GetWrongCountExcise(mID.c_str()));
            BindParam(stmt, 3, m_nCompleteNumber);
            BindParam(stmt, 4, GetCurIndex());
            BindParam(stmt, 5, GetRightCountExcise(mID.c_str()));
            BindParam(stmt, 6, mID.c_str());
           
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

int CMExercise::GetExerciseCount(const char* sID)
{
	BOOL ret = FALSE;
	//保存入数据库
	sqlite3*db=CheckTable();

	int count = 0;

	if(db)
	{
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"SELECT questioncount FROM %s WHERE id=? ", "exerciselist");

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
        {
            BindParam(stmt, 1, sID);
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                count = sqlite3_column_int(stmt, 0);
            }
        }
		else
		{
			CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	}

	return count;
}


BOOL CMExercise::UpDateExerciseListWrongCount()
{
    BOOL ret = FALSE;
    //保存入数据库
    sqlite3*db=CheckTable();
    
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"UPDATE %s SET nwrongcount=? WHERE id=? ", "exerciselist");
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            
            int nCount = 0;
            
            for(CMList<TQuestion>::iterator it = m_lstItem->begin(); it != m_lstItem->end(); it++)
            {
                TQuestion question = (TQuestion)*it;
                
                TQuestionItem item = question.item;
                
                if (item.isWrong) {
                    nCount++;
                }
            }
            
            BindParam(stmt, 1, nCount/*GetWrongCountExcise(mID.c_str())*/);
            BindParam(stmt, 2, mID.c_str());
            
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


BOOL CMExercise::DoSaveExerciseStatus()
{
    BOOL ret = FALSE;
    sqlite3* db = CheckTable();
    char* errorMsg;

    if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
    }
    
    for (int i = 0; i < GetItemCount(); i++) {
        TQuestion qitem;
        GetItem(i, qitem);
        DoUpdate(qitem);
        ret = TRUE;
    }
    
    UpDateList();

    
    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
    }
    
    return ret;
}

BOOL CMExercise::DoSaveWrongStatus()
{
    BOOL ret = FALSE;
    sqlite3* db = CheckTable();
    char* errorMsg;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
    }
    
    for (int i = 0; i < GetItemCount(); i++) {
        TQuestion qitem;
        GetItem(i, qitem);
        DoUpdateWrongs(qitem);
        ret = TRUE;
    }
    
    UpDateExerciseListWrongCount();
    
    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
    }
    
    return ret;

}

BOOL CMExercise::LoadStatus()
{
    BOOL ret = FALSE;
    
    if (CMQuestionhandler::LoadStatus()) {
        CMQuestionhandler::ClearStatus();
        DoSaveExerciseStatus();
    }
    
    return ret;
}

int CMExercise::GetRightCountExcise(const char *questionID)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    sqlite3*db=CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;

    snprintf(sql, 1024,"SELECT COUNT(*) FROM %s WHERE right=? and mid=?", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, 1);
        BindParam(stmt, 2, questionID);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            nRightCount = sqlite3_column_int(stmt, 0);
        }
        
        sqlite3_finalize(stmt);
    }
    return nRightCount;
}

int CMExercise::GetWrongCountExcise(const char *questionID)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    sqlite3*db=CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;
    
    snprintf(sql, 1024,"SELECT COUNT(*) FROM %s WHERE iswrong=? and mid=?", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, 1);
        BindParam(stmt, 2, questionID);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            m_nWrongs = sqlite3_column_int(stmt, 0);
        }
        
        sqlite3_finalize(stmt);
    }
    return CMWrongQuestion::GetWrongCount(questionID);
}

void CMExercise::DoGetWrongQuestion(const char *sID)
{
    if(m_lstItem)
		m_lstItem->clear();
	else
		m_lstItem = new CMList<TQuestion>;
    
    mID = sID;
    
    sqlite3* db = CheckTable();
    char* errorMsg;

    if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
    }
    
    DoGetWrongItems(db);
    
    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
    }

    if (m_pListener)
        	m_pListener->OnUpdateDataFinish(m_UserData, MER_OK);

}

int CMExercise::DoGetRightCount(const char* questionID)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    sqlite3*db=CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;
    
    snprintf(sql, 1024,"SELECT COUNT(*) FROM %s WHERE right=? and mid=?", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        BindParam(stmt, 1, 1);
        BindParam(stmt, 2, questionID);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            nRightCount = sqlite3_column_int(stmt, 0);
        }
        
        sqlite3_finalize(stmt);
    }
    return nRightCount;
}

BOOL CMExercise::DoCreate(sqlite3* db)
{
    BOOL ret = FALSE;
    
    char *errorMsg = NULL;
    char sql[1024];
    
    if (strlen(m_tablename) == 0) {
        return  ret;
    }
    
    snprintf(sql, 1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,type INTEGER,question TEXT,description TEXT,value INTEGER,iswrong INTEGER,rightanswer TEXT,myanswer TEXT,answer TEXT,iswrongorig INTEGER,right INTEGER,mid TEXT,checked INTEGER,lastupdate INTEGER)", m_tablename);
    
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		ret = TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
    
    memset(sql, 0, 1024);
    
    if(strlen(m_SubTablename)==0)
        return FALSE;
    
	snprintf(sql, 1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,sumid TEXT UNIQUE, qid TEXT, id TEXT, bcheck INTEGER, description TEXT, rightanswer INTEGER,myanswer INTEGER)", m_SubTablename);
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		return ret ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
}

BOOL CMExercise::DoRefresh(TQuestion& obj)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    if(strlen(obj.item.sID.c_str()) == 0)
        return FALSE;
    
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	sqlite3*db=CheckTable();
	if (db == NULL)
		return FALSE;
    
    
	snprintf(sql,1024,"SELECT iswrong, myanswer, answer, right, checked,lastupdate FROM %s WHERE id = ?", m_tablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{

        BindParam(stmt, 1, obj.item.sID.c_str());
        
        int step = sqlite3_step(stmt);
        
        if (step == SQLITE_ROW)
        {
            
            obj.item.isWrong=sqlite3_column_int(stmt, 0);
            
            obj.item.sMyAnswer = (const char*)sqlite3_column_text(stmt, 1);
            
            obj.item.sAnswer = (const char*)sqlite3_column_text(stmt, 2);
            
            obj.item.isRight=sqlite3_column_int(stmt, 3);
            
            obj.item.isChecked=sqlite3_column_int(stmt, 4);
            
            sLastUpdate = sqlite3_column_int(stmt, 5);

            m_mutex.Lock();
            for (int i = 0; i < obj.m_lisOption->size(); i++) {
                TOption& optionitem = obj.m_lisOption->at(i);
                DoRefreshOption(db, optionitem);
            }
            
            for (int i = 0; i < m_lstItem->size(); i++) {
                TQuestion& item = m_lstItem->at(i);
                
                if (strcmp(item.item.sID.c_str(), obj.item.sID.c_str()) == 0) {
                    item.item=obj.item;
                    item.m_lisOption = item.m_lisOption;
                    break;
                }
            }
            m_mutex.UnLock();
            
        }
        else if (step == SQLITE_DONE)
        {
            ;
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

BOOL CMExercise::DoRefreshOption(sqlite3 *db, TOption& obj)
{
    if(strlen(m_SubTablename)==0)
        return FALSE;
    
    if(strlen(obj.sSID.c_str()) == 0)
        return FALSE;
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	if (db == NULL)
		return FALSE;
    
    
	snprintf(sql,1024,"SELECT bcheck, myanswer FROM %s WHERE qid = ? and id = ?", m_SubTablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        BindParam(stmt, 1, obj.sSID.c_str());
        BindParam(stmt, 2, obj.nID.c_str());
        
        int step = sqlite3_step(stmt);
        
        if (step == SQLITE_ROW)
        {
            obj.bCheck=sqlite3_column_int(stmt, 0);
            
            obj.bMyAnswer=sqlite3_column_int(stmt, 1);
            
        }
        else if (step == SQLITE_DONE)
        {
            ;
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

BOOL CMExercise::DoUpdate(const TQuestion& obj)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    
    //更新对象
    m_mutex.Lock();
    for (int i = 0; i < m_lstItem->size(); i++) {
        TQuestion& item = m_lstItem->at(i);
        
        if (strcmp(item.item.sID.c_str(), obj.item.sID.c_str()) == 0) {
            item = obj;
            ret = TRUE;
            break;
        }
    }
    m_mutex.UnLock();
    
    sqlite3* db = CheckTable();
 
    if(db)
    {
        sqlite3_stmt *stmt;
        
        CHAR sql[512];
        
        snprintf(sql, 512,"UPDATE %s SET iswrong=?, myanswer=?, answer=?, right=?, checked=?,lastupdate=? WHERE  id=? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            BindParam(stmt, 1, obj.item.isWrong);

            BindParam(stmt, 2, obj.item.sMyAnswer.c_str());
            
            BindParam(stmt, 3, obj.item.sAnswer.c_str());
            
            BindParam(stmt, 4, obj.item.isRight);
            
            BindParam(stmt, 5, obj.item.isChecked);
            
            BindParam(stmt, 6, sLastUpdate);
            
            BindParam(stmt, 7, obj.item.sID.c_str());
            
            if(sqlite3_step(stmt)==SQLITE_DONE)
            {
                for (int i = 0; i < obj.m_lisOption->size(); i++) {
                    TOption optionitem = obj.m_lisOption->at(i);
                    DoUpdateOption(db, optionitem);
                }
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

BOOL CMExercise::DoUpdateOption(sqlite3* db, const TOption& obj)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    
    
    sqlite3_stmt *stmt;
    
    CHAR sql[512];
    
    snprintf(sql, 512,"UPDATE %s SET bcheck=?, myanswer=? WHERE  sumid=? ", m_SubTablename);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK){
        
        BindParam(stmt, 1, obj.bCheck);
        
        BindParam(stmt, 2, obj.bMyAnswer);
        
        char sumid[128];
        sprintf(sumid, "%s%s",obj.sSID.c_str(),obj.nID.c_str());
        
        BindParam(stmt, 3, sumid);
        
        if(sqlite3_step(stmt)==SQLITE_DONE)
        {
            ret=TRUE;
        }
        else {
            CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
    }
    else {
        CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    
    return ret;
}

BOOL CMExercise::DoPutItem(TiXmlElement* pItem, sqlite3* db, TQuestion& item)
{
    
    //添加item到显示list
    pItem = pItem->FirstChildElement();
    
    const char *pstr = NULL;
    
    
    while (pItem)
    {
        TQuestion* itemoption = new TQuestion();
		itemoption->m_lisOption = new CMList<TOption>;
        
		pstr = pItem->Attribute("id");
		if (!pstr)
			continue;
        itemoption->item.sID = pstr;
        
        int count = m_lstItem->size();

		int temp = 0;
		pItem->Attribute("iscomplete", &temp);
        itemoption->item.isChecked = temp;
        
		pItem->Attribute("type", &itemoption->item.nType);
        
		pstr =  pItem->Attribute("question");
		if(pstr)
            itemoption->item.sQuestion = pstr;
        
		//在线调研题目属性
		//pstr = pItem->Attribute("category");
		//if(pstr)
		//	strcpy(itemoption->item.sCategory,pstr);
        
		pItem->Attribute("value", &itemoption->item.nValue);
        
		int val = 0;
		pItem->Attribute("iswrong", &val);
		itemoption->item.isWrongOrig = itemoption->item.isWrong = val;
        
		pstr =  pItem->Attribute("description");
		if(pstr)
            itemoption->item.sDescription = pstr;
        
		pstr =  pItem->Attribute("rightanswer");
		if(pstr)
            itemoption->item.sRightAnswer = pstr;
        
		pstr =  pItem->Attribute("myanswer");
		if(pstr)
            itemoption->item.sMyAnswer = pstr;
        
        //获取从服务器返回的 以前做题答案状态
//        itemoption->item.sAnswer = pstr;
        
//        if (itemoption->item.sAnswer != NULL && strlen(itemoption->item.sAnswer.c_str()) > 0) {
//            itemoption->item.isChecked = TRUE;
//        }
        
        sLastUpdate = 0;
        
        if (itemoption->item.nType != TQuestionType::EText) //不是问答题
        {
            TiXmlElement* pOptionItem = pItem->FirstChildElement();
            while (pOptionItem)
            {
                TOption option;
                option.bCheck = FALSE;
                option.sSID = itemoption->item.sID;
                


                
                pstr = pOptionItem->Attribute("description");
				if(pstr)
                    option.sText = pstr;
                
				pstr = pOptionItem->Attribute("id");
				if(pstr)
					option.nID = pstr;

				int val = 0;
				pOptionItem->Attribute("rightanswer", &val);
				option.bRightAnswer = val;
                
				pOptionItem->Attribute("myanswer", &val);
				option.bMyAnswer = val;
                
                //获取从服务器返回的 以前做题答案状态
                option.bCheck = val;
                
                if (option.bCheck) {
                    itemoption->item.isChecked = val;
                }              
                
                DoRefreshOption(db, option);

                itemoption->m_lisOption->push_back(option);

                SaveOption(db, option);
                
                pOptionItem = pOptionItem->NextSiblingElement("option");
            }
            
        }
        
        if(!m_lstItem)
            m_lstItem=new CMList<TQuestion>;
        
        //判断 从网络读取的以前做题对错
        if (!itemoption->item.isWrong && itemoption->item.isChecked && itemoption->item.nType != TQuestionType::EText) {
            itemoption->item.isRight = TRUE;
        }
        
        DoRefresh(*itemoption);

        m_lstItem->push_back(*itemoption);

        SaveQuestion(db, itemoption->item);
        
        pItem = pItem->NextSiblingElement("item");
    }
    
    return TRUE;
}

BOOL CMExercise::SaveQuestion(sqlite3* db,TQuestionItem &questionitem)
{
    BOOL ret = FALSE;

    if (strcmp(m_tablename, "") == 0) {
		return TRUE;
	}
    
    CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql,1024,
             "REPLACE INTO %s(id,type,question,description,value,iswrong,rightanswer,myanswer,answer,iswrongorig,right,mid,checked,lastupdate) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
             m_tablename);
    
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        
		BindParam(stmt, 1, questionitem.sID.c_str());
		BindParam(stmt, 2, questionitem.nType);
		BindParam(stmt, 3, questionitem.sQuestion.c_str());
		BindParam(stmt, 4, questionitem.sDescription.c_str());
		BindParam(stmt, 5, questionitem.nValue);
		BindParam(stmt, 6, questionitem.isWrong);
		BindParam(stmt, 7, questionitem.sRightAnswer.c_str());
        
		BindParam(stmt, 8,  questionitem.sMyAnswer.c_str());
		BindParam(stmt, 9, questionitem.sAnswer.c_str());
		BindParam(stmt, 10, questionitem.isWrongOrig);
		BindParam(stmt, 11, questionitem.isRight);
        BindParam(stmt, 12, mID.c_str());
        BindParam(stmt, 13, questionitem.isChecked);
        BindParam(stmt, 14, sLastUpdate);
        
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

BOOL CMExercise::SaveOption(sqlite3* db,TOption &option)
{
    BOOL ret = FALSE;
    
    if (strcmp(m_SubTablename, "") == 0) {
		return TRUE;
	}
    
    CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql,1024,
             "REPLACE INTO  %s(sumid,qid,id,bcheck,description,rightanswer,myanswer) values (?,?,?,?,?,?,?)",
             m_SubTablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        char sumid[128];
        sprintf(sumid, "%s%s",option.sSID.c_str(),option.nID.c_str());

        BindParam(stmt, 1, sumid);
        BindParam(stmt, 2, option.sSID.c_str());
		BindParam(stmt, 3, option.nID.c_str());
		BindParam(stmt, 4, option.bCheck);
		BindParam(stmt, 5, option.sText.c_str());
        BindParam(stmt, 6, option.bRightAnswer);
		BindParam(stmt, 7, option.bMyAnswer);
        
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

BOOL CMExercise::DoUpdateWrongs(const TQuestion& obj)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
    BOOL ret = FALSE;
    
    sqlite3* db = CheckTable();
    
    if(db)
    {
        sqlite3_stmt *stmt;
        
        CHAR sql[512];
        
        snprintf(sql, 512,"UPDATE %s SET iswrong=? WHERE  id=? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            BindParam(stmt, 1, obj.item.isWrong);
            
            BindParam(stmt, 2, obj.item.sID.c_str());
            
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

BOOL CMExercise::DoGetWrongItems(sqlite3 *db)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    memset(sql, 0, 1024);
    
    snprintf(sql,1024,"SELECT * from %s WHERE mid = ? and iswrong = ? order by lastupdate ASC ",m_tablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        m_mutex.Lock();
        if(m_lstItem)
        {
            m_lstItem->clear();
        }
        m_mutex.UnLock();
        
        BindParam(stmt, 1, mID.c_str());
        BindParam(stmt, 2, 1);
        
        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
            TQuestion* Qitem = new TQuestion;
            Qitem->m_lisOption = new CMList<TOption>;
            ret = TRUE;
          
            Qitem->item.sID = (const char*) sqlite3_column_text(stmt, 1);
            
            Qitem->item.nType=sqlite3_column_int(stmt, 2);
         
            Qitem->item.sQuestion = (const char*) sqlite3_column_text(stmt, 3);
            
            Qitem->item.sDescription = (const char*) sqlite3_column_text(stmt, 4);
            
            Qitem->item.nValue=sqlite3_column_int(stmt, 5);
            
            Qitem->item.isWrong=sqlite3_column_int(stmt, 6);
            
            Qitem->item.sRightAnswer = (const char*) sqlite3_column_text(stmt,7);
            
            Qitem->item.sMyAnswer = (const char*) sqlite3_column_text(stmt, 8);
            
            Qitem->item.sAnswer = (const char*) sqlite3_column_text(stmt, 9);
            
            Qitem->item.isWrongOrig=sqlite3_column_int(stmt, 10);
            
            Qitem->item.isRight=sqlite3_column_int(stmt, 11);
            
            mID = (const char*) sqlite3_column_text(stmt, 12);
            
            Qitem->item.isChecked=0;//sqlite3_column_int(stmt, 13);
            
            sLastUpdate = sqlite3_column_int(stmt, 14);
            
            DoGetWrongOptionItems(db,*Qitem);
            
            m_mutex.Lock();
            
            if(!m_lstItem)
                m_lstItem=new CMList<TQuestion>;
            
            m_lstItem->push_back(*Qitem);
            m_mutex.UnLock();
            
        }
        
        
        sqlite3_finalize(stmt);
        
        ret = TRUE;
	}
    return ret;
}

BOOL CMExercise::DoGetWrongOptionItems(sqlite3 *db, TQuestion &item)
{
    if(strlen(m_SubTablename)==0)
        return FALSE;
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    snprintf(sql,1024,"SELECT * from %s WHERE qid = ?  order by _id ASC ",m_SubTablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        
        BindParam(stmt, 1, item.item.sID.c_str());
        
        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
            TOption option;
            
            option.sSID = (const char*) sqlite3_column_text(stmt, 2);
            
            option.nID = (const char*) sqlite3_column_text(stmt, 3);
            
            option.bCheck = 0;//sqlite3_column_int(stmt, 4);
            
            option.sText = (const char*) sqlite3_column_text(stmt, 5);
            
            option.bRightAnswer = sqlite3_column_int(stmt, 6);
            
            option.bMyAnswer = sqlite3_column_int(stmt, 7);
            
            m_mutex.Lock();
            
            item.m_lisOption->push_back(option);
            m_mutex.UnLock();
            
        }
        
        sqlite3_finalize(stmt);
        
        ret = TRUE;
	}
    return ret;
}

BOOL CMExercise::DoGetCacheItems(sqlite3* db)
{
    if(strlen(m_tablename)==0)
        return FALSE;
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    memset(sql, 0, 1024);
    
    snprintf(sql,1024,"SELECT * from %s WHERE mid = ? order by _id ASC ",m_tablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        m_mutex.Lock();
        if(m_lstItem)
        {
            m_lstItem->clear();
        }
        m_mutex.UnLock();
        
        BindParam(stmt, 1, mID.c_str());
        
        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
            TQuestion* Qitem = new TQuestion;
            Qitem->m_lisOption = new CMList<TOption>;
            ret = TRUE;
            
            Qitem->item.sID = (const char*) sqlite3_column_text(stmt, 1);

            Qitem->item.nType=sqlite3_column_int(stmt, 2);

            Qitem->item.sQuestion = (const char*) sqlite3_column_text(stmt, 3);
       
            Qitem->item.sDescription = (const char*) sqlite3_column_text(stmt, 4);
            
            Qitem->item.nValue=sqlite3_column_int(stmt, 5);

            Qitem->item.isWrong=sqlite3_column_int(stmt, 6);

            Qitem->item.sRightAnswer = (const char*) sqlite3_column_text(stmt,7);
            
            Qitem->item.sMyAnswer =(const char*) sqlite3_column_text(stmt, 8);
            
            Qitem->item.sAnswer = (const char*) sqlite3_column_text(stmt, 9);
            
            Qitem->item.isWrongOrig=sqlite3_column_int(stmt, 10);

            Qitem->item.isRight=sqlite3_column_int(stmt, 11);
            
            mID = (const char*) sqlite3_column_text(stmt, 12);
            
            Qitem->item.isChecked=sqlite3_column_int(stmt, 13);
            
            sLastUpdate = sqlite3_column_int(stmt, 14);

            DoGetOptionCacheItems(db,*Qitem);
            
            m_mutex.Lock();
            
            if(!m_lstItem)
                m_lstItem=new CMList<TQuestion>;
            
            m_lstItem->push_back(*Qitem);
            m_mutex.UnLock();
            
            ret = TRUE;

            
        }
        
        
        sqlite3_finalize(stmt);
        
	}
    return ret;
}

BOOL CMExercise::DoGetOptionCacheItems(sqlite3* db, TQuestion& item)
{
    
    if(strlen(m_SubTablename)==0)
        return FALSE;
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
    snprintf(sql,1024,"SELECT * from %s WHERE qid = ?  order by _id ASC ",m_SubTablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        
        BindParam(stmt, 1, item.item.sID.c_str());
        
        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
            TOption option;
            
            option.sSID = (const char*) sqlite3_column_text(stmt, 2);
            
            option.nID = (const char*)sqlite3_column_text(stmt, 3);
            
            option.bCheck = sqlite3_column_int(stmt, 4);
            
            option.sText = (const char*) sqlite3_column_text(stmt, 5);
            
            option.bRightAnswer = sqlite3_column_int(stmt, 6);
            
            option.bMyAnswer = sqlite3_column_int(stmt, 7);
            
            m_mutex.Lock();
          
            item.m_lisOption->push_back(option);
            m_mutex.UnLock();
            
        }
        
        sqlite3_finalize(stmt);
        
        ret = TRUE;
	}
    return ret;

}

void CMExercise::DoClear()
{
    m_mutex.Lock();
    Clear();
	m_mutex.UnLock();
    
    if(strlen(m_tablename) == 0)
        return;
    
    sqlite3* db = CheckTable();
    
    char* errorMsg;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
    }
    
    CHAR sql[1024];

    if(db != NULL)
    {
        
        sql[0] = '\0';
        
        snprintf(sql, 1024,"DELETE FROM %s", m_tablename);
        
        if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
        }
        else
        {
        }
        
    }
    memset(sql , 0, 1024);

    if(db != NULL)
    {
        
        sql[0] = '\0';
        
        snprintf(sql, 1024,"DELETE FROM %s", m_SubTablename);
        
        if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
        }
        else
        {
        }
        
    }
    
    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
    }

}

void CMExercise::DoCommit()
{
    isExCommit = 1;
    m_nCompleteNumber++;
    DoSaveExerciseStatus();
}

void CMExercise::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument *pDoc)
{
    INT32 result = TResult::EUnknownError;

    if(nCode == MER_OK)
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
                    if (nCmdID  ==  SERVICE_GETEXERCISEQUESTION)
                    {

                        sqlite3* db = CheckTable();
                        if(db)
                        {
                            DoCreate(db);
                        }
                        char* errorMsg;
                        
                        if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                        {
                            CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
                        }
                        
                        TQuestion a;

                        DoPutItem(pItem, db, a);
                        
                        if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                        {
                            CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
                        }

                        LoadStatus();
                        
                        m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);

                    }
                    else
                        result = TResult::EProtocolFormatError;
                  
                }
                else
                {
                    if(LoadFromDB())
                        result = TResult::ENothing;

                    m_pListener->OnUpdateDataFinish(m_UserData, result);
                }
            }
        }
    }
    else
    {
       if(LoadFromDB())
           result = TResult::ENothing;

        m_pListener->OnUpdateDataFinish(m_UserData, result);
    }
	
}
