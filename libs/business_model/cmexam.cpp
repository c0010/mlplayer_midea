// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmexam.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "utf8ncpy.h"
#include "cmfile.h"
#include "cmexamlist.h"

CMExam::CMExam()
	: CMWrongQuestion()
	, m_bView(FALSE)
	, m_nDuration(-1)
{
}


CMExam::~CMExam()
{
}

void CMExam::SetListener(IMUpdateDataListener *pListener, IMSimpleResultListener *pSimpleResultListener)
{
    m_pListener = pListener;
    m_pSimpleResultListener = pSimpleResultListener;
}

void CMExam::ViewExamQuestion(const char* sID)
{
    Clear();
    
	m_bView = TRUE;
    
    mID = sID;
    sprintf(m_tablename,"examquestion");

	CMQuestionhandler::GetQuestion(SERVICE_GETEXAMQUESTION, sID, TRUE);
}

void CMExam::StartExam(const char* sID)
{
    Clear();

	m_bView = FALSE;

    mID = sID;
    sprintf(m_tablename,"examquestion");
//    const char* sDst =
//
//    CM_ERRP("get the dts:%s",sDst);

	CMQuestionhandler::GetQuestionStart(SERVICE_GETEXAMQUESTION, sID, GetItemDstime(sID).c_str());
}

BOOL CMExam::SetAnswerItem(TQuestion* itemoption, TiXmlElement* pItem)
{
	if(m_bView)
		return CMWrongQuestion::SetAnswerItem(itemoption, pItem);
	else
		return CMQuestionhandler::SetAnswerItem(itemoption, pItem);
}


int CMExam::GetDuration()
{
	return m_nDuration;
}

void CMExam::SetDuration(int second)
{
	m_nDuration = second;
}

void CMExam::DoCommit()
{
	if(m_bView)
	{
		CMWrongQuestion::Commit();
	}
	else
	{
		char sParam[100] = {0};
		snprintf(sParam, 100,"examid=%s", mID.c_str());
		CMQuestionhandler::Commit(SERVICE_COMMITEXAM, sParam);
	}
}

TQuestion& TQuestion::operator=(const TiXmlElement* right)
{
    const CHAR* pStr = NULL;
    
    pStr = right->Attribute("id");
    if(pStr)
        item.sID = pStr;
    
    right->QueryIntAttribute("type", &item.nType);
    
    pStr = right->Attribute("question");
    if(pStr)
        item.sQuestion = pStr;
    
    right->QueryIntAttribute("value", &item.nValue);
    
    int tmp=0;
    right->QueryIntAttribute("iswrong", &tmp);
    item.isWrong = tmp;
    
    pStr = right->Attribute("description");
    if(pStr)
        item.sDescription = pStr;
    
    pStr = right->Attribute("rightanswer");
    if(pStr)
        item.sRightAnswer = pStr;
    
    pStr = right->Attribute("myanswer");
    if(pStr)
        item.sMyAnswer = pStr;
    
    if (item.nType != TQuestionType::EText)
    {
        if (!m_lisOption)
            m_lisOption = new CMList<TOption>;

        const TiXmlElement* pOptionItem = right->FirstChildElement("option");
        while (pOptionItem)
        {
            TOption option;
            
            option.bCheck = FALSE;

            pStr = pOptionItem->Attribute("id");
            if(pStr)
            	option.nID = pStr;
            
            pStr = pOptionItem->Attribute("description");
            if(pStr)
                option.sText = pStr;
            
            int val = 0;
            pOptionItem->Attribute("rightanswer", &val);
            option.bRightAnswer = val;
            
            pOptionItem->Attribute("myanswer", &val);
            option.bMyAnswer = val;
            
            m_lisOption->push_back(option);
            
            pOptionItem = pOptionItem->NextSiblingElement("option");
        }
        //m_lisOption = list;
    }

    return *this;
}

BOOL CMExam::DoCreate(sqlite3* db)
{
	if (db == NULL)
        return FALSE;
    
	char *errorMsg;
    
    BOOL retQuestion = FALSE;
    BOOL retOption = FALSE;
    BOOL retDts = FALSE;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMsg) == SQLITE_OK)
    {
        char sqlQuestion[1024];
        snprintf(sqlQuestion,sizeof(sqlQuestion),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,eid TEXT,id TEXT UNIQUE,type INTEGER,question TEXT,value INTEGER,iswrong INTEGER,description TEXT,rightanswer TEXT,oldanswer TEXT,newanswer TEXT)", "examquestion");
        
        if (sqlite3_exec(db, sqlQuestion, NULL, NULL, &errorMsg) == SQLITE_OK)
        {
            retQuestion = TRUE ;
        }
        else
        {
            CM_ERRP("exec %s failed.error:%s", sqlQuestion, errorMsg);
            retQuestion = FALSE;
        }
        
        char sqlOption[1024];
        snprintf(sqlOption,sizeof(sqlOption),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,sumid TEXT UNIQUE, qid TEXT,id TEXT,description TEXT,rightanswer INTEGER,oldanswer TEXT,checked INTEGER)", "examoption");
        
        if (sqlite3_exec(db, sqlOption, NULL, NULL, &errorMsg) == SQLITE_OK)
        {
            retOption = TRUE ;
        }
        else
        {
            CM_ERRP("exec %s failed.error:%s", sqlOption, errorMsg);
            retOption = FALSE;
        }

        char sqldts[1024];
        snprintf(sqldts,sizeof(sqldts),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,dts TEXT)", "examdts");

        if (sqlite3_exec(db, sqldts, NULL, NULL, &errorMsg) == SQLITE_OK)
        {
        	retDts = TRUE ;
        }
        else
        {
            CM_ERRP("exec %s failed.error:%s", sqldts, errorMsg);
            retDts = FALSE;
        }

    }
    else
    {
        CM_ERRP("Failed to begin transaction: %s", errorMsg);
    }
    
    if (retQuestion && retOption)
    {
        if (sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("Failed to commit transaction: %s", errorMsg);
            sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &errorMsg);
            CM_ERRP("Failed to ROLL transaction: %s", errorMsg);
            return FALSE;
        }
        
        return TRUE;
    }
    else
    {
        sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &errorMsg);
    }
    
    return FALSE;
}


BOOL CMExam::DoRefresh(TQuestion& obj)
{
    BOOL ret = FALSE;

    m_mutex.Lock();
    if(m_lstItem->size()>0){
        for (int i = 0; i < m_lstItem->size(); i++)
        {
            TQuestion& item = m_lstItem->at(i);

            if (strcmp(item.item.sID.c_str(), obj.item.sID.c_str()) == 0) {
                obj = item;
                ret = TRUE;
                break;
            }
        }
    }
    m_mutex.UnLock();

	//根据obj的sID属性更新
	sqlite3_stmt *stmt;
	CHAR sqlQuestion[1024];
	sqlQuestion[0] = '\0';

	sqlite3*db = CheckTable();

	if (db == NULL)
		return FALSE;

	snprintf(sqlQuestion,sizeof(sqlQuestion),"SELECT id, type, question, value, iswrong, description, rightanswer, oldanswer, newanswer FROM %s WHERE eid=? and id=?", "examquestion");

	if (sqlite3_prepare_v2(db, sqlQuestion, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, mID.c_str());
		BindParam(stmt, 2, obj.item.sID.c_str());

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            obj.item.sID = (const char*)sqlite3_column_text(stmt, 0);

            obj.item.nType = sqlite3_column_int(stmt, 1);

            obj.item.sQuestion = (const char*)sqlite3_column_text(stmt, 2);

            obj.item.nValue = sqlite3_column_int(stmt, 3);

//            obj.item.isWrong = sqlite3_column_int(stmt, 4);

            obj.item.sDescription =(const char*)sqlite3_column_text(stmt, 5);

            //obj.item.sRightAnswer =(const char*)sqlite3_column_text(stmt, 6);

            //obj.item.sMyAnswer = (const char*)sqlite3_column_text(stmt, 7);

            obj.item.sAnswer = (const char*)sqlite3_column_text(stmt, 8);
        }

        sqlite3_finalize(stmt);
	}
	else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
	}

    if (obj.item.nType != TQuestionType::EText)
    {
        for (int j = 0; j < obj.m_lisOption->size(); j++)
        {
            TOption& option = obj.m_lisOption->at(j);

            CHAR sqlOption[1024];
            sqlOption[0] = '\0';

            snprintf(sqlOption,sizeof(sqlOption),"SELECT id, description, rightanswer, oldanswer, checked FROM %s WHERE qid=? and id=?", "examoption");

            if (sqlite3_prepare_v2(db, sqlOption, -1, &stmt, NULL) == SQLITE_OK)
            {
                BindParam(stmt, 1, obj.item.sID.c_str());
                BindParam(stmt, 2, option.nID.c_str());

                if (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    option.nID = (const char*)sqlite3_column_text(stmt, 0);

                    option.sText = (const char*)sqlite3_column_text(stmt, 1);

                    //option->bRightAnswer = sqlite3_column_int(stmt, 2);

                    //option.bMyAnswer = sqlite3_column_int(stmt, 3);

                    option.bCheck = sqlite3_column_int(stmt, 4);
                }
                sqlite3_finalize(stmt);
            }
            else
            {
                CM_ERRP("sqlite3_step %s failed.error:%s", sqlOption, sqlite3_errmsg(db));
            }
        }
    }

	return ret;
}


BOOL CMExam::DoUpdate(const TQuestion& obj)
{
    BOOL ret = FALSE;
    //更新对象
    m_mutex.Lock();
    if(m_lstItem->size()>0){

    	for (int i = 0; i < m_lstItem->size(); i++)

        {
            TQuestion& item = m_lstItem->at(i);

            if (strcmp(item.item.sID.c_str(), obj.item.sID.c_str()) == 0) {
                item = obj;
                ret = TRUE;
                break;
            }
        }
    }

    m_mutex.UnLock();

    //保存入数据库
    sqlite3*db = CheckTable();

    if(db == NULL)
    {
        return FALSE;
    }
    
    if (obj.item.nType != TQuestionType::EText) //不是问答题
    {
        for (int i = 0; i < obj.m_lisOption->size(); i++)
        {
            TOption& option = obj.m_lisOption->at(i);
            
            CHAR sqlOption[1024];
            sqlite3_stmt *stmtOption;
            snprintf(sqlOption,sizeof(sqlOption),"REPLACE INTO %s(sumid, qid, id, description, rightanswer, oldanswer, checked) VALUES (?,?,?,?,?,?,?)", "examoption");
            if (sqlite3_prepare_v2(db, sqlOption, -1, &stmtOption, NULL) == SQLITE_OK)
            {
                char sumid[128];
                sprintf(sumid, "%s%s",obj.item.sID.c_str(),option.nID.c_str());
                BindParam(stmtOption, 1, sumid);
                BindParam(stmtOption, 2, obj.item.sID.c_str());
                BindParam(stmtOption, 3, option.nID.c_str());
                BindParam(stmtOption, 4, option.sText.c_str());
                BindParam(stmtOption, 5, option.bRightAnswer);
                BindParam(stmtOption, 6, option.bMyAnswer);
                BindParam(stmtOption, 7, option.bCheck);
                
                
                if(sqlite3_step(stmtOption) != SQLITE_DONE)
                {
                    CM_ERRP("exec %s failed.error:%s", sqlOption, sqlite3_errmsg(db));
                }
                
                sqlite3_finalize(stmtOption);
            }
            else
            {
                CM_ERRP("exec %s failed.error:%s", sqlOption, sqlite3_errmsg(db));
            }
        }
    }
    
    CHAR sqlQuestion[1024];
    sqlite3_stmt *stmtQuestion;
    snprintf(sqlQuestion,sizeof(sqlQuestion),"REPLACE INTO %s(eid, id, type, question, value, iswrong, description, rightanswer, oldanswer, newanswer) VALUES (?,?,?,?,?,?,?,?,?,?)", "examquestion");
    if (sqlite3_prepare_v2(db, sqlQuestion, -1, &stmtQuestion, NULL) == SQLITE_OK)
    {
        BindParam(stmtQuestion, 1, mID.c_str());
        BindParam(stmtQuestion, 2, obj.item.sID.c_str());
        BindParam(stmtQuestion, 3, obj.item.nType);
        BindParam(stmtQuestion, 4, obj.item.sQuestion.c_str());
        BindParam(stmtQuestion, 5, obj.item.nValue);
        BindParam(stmtQuestion, 6, obj.item.isWrong);
        BindParam(stmtQuestion, 7, obj.item.sDescription.c_str());
        BindParam(stmtQuestion, 8, obj.item.sRightAnswer.c_str());
        BindParam(stmtQuestion, 9, obj.item.sMyAnswer.c_str());
        BindParam(stmtQuestion, 10, obj.item.sAnswer.c_str());
        
        if(sqlite3_step(stmtQuestion) != SQLITE_DONE)
        {
            CM_ERRP("exec %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmtQuestion);
    }
    else
    {
        CM_ERRP("exec %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
    }
    
    return ret;
}


BOOL CMExam::DoPutItem(TiXmlElement* pItem, sqlite3* db, TQuestion& item)
{
    item = pItem;
    


    return TRUE;
}

BOOL CMExam::DoGetCacheItems(sqlite3* db)
{
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
	memset(sql,0,1024);

	snprintf(sql,sizeof(sql),"SELECT id, type, question, value, iswrong, description, rightanswer, oldanswer, newanswer FROM %s WHERE eid = ? order by _id ASC ", "examquestion");

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
            Qitem->item.sID = (const char*)sqlite3_column_text(stmt, 0);

            Qitem->item.nType = sqlite3_column_int(stmt, 1);

            Qitem->item.sQuestion = (const char*)sqlite3_column_text(stmt, 2);

            Qitem->item.nValue = sqlite3_column_int(stmt, 3);

            Qitem->item.isWrong = sqlite3_column_int(stmt, 4);

            Qitem->item.sDescription =(const char*)sqlite3_column_text(stmt, 5);

            Qitem->item.sRightAnswer =(const char*)sqlite3_column_text(stmt, 6);

            Qitem->item.sMyAnswer = (const char*)sqlite3_column_text(stmt, 7);

            Qitem->item.sAnswer = (const char*)sqlite3_column_text(stmt, 8);

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
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return TRUE;
}

BOOL CMExam::DoGetOptionCacheItems(sqlite3* db, TQuestion& item)
{
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

    snprintf(sql,1024,"SELECT * from %s WHERE qid = ?  order by _id ASC ","examoption");

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{

        BindParam(stmt, 1, item.item.sID.c_str());

        while(sqlite3_step(stmt)==SQLITE_ROW)
        {
            TOption option;

            option.sSID = (const char*) sqlite3_column_text(stmt, 1);

            option.nID = (const char*)sqlite3_column_text(stmt, 3);

            option.sText = (const char*) sqlite3_column_text(stmt, 4);

            option.bRightAnswer = sqlite3_column_int(stmt, 5);

            option.bMyAnswer = sqlite3_column_int(stmt, 6);

            option.bCheck = sqlite3_column_int(stmt, 7);


            m_mutex.Lock();

            item.m_lisOption->push_back(option);
            m_mutex.UnLock();

        }

        sqlite3_finalize(stmt);

        ret = TRUE;
	}
    return ret;

}

void CMExam::DoClear()
{
    m_mutex.Lock();
    Clear();
	m_mutex.UnLock();
    
	char* errorMsg;
    sqlite3* db = CheckTable();
    
	sqlite3_stmt *stmtQuestion;
	CHAR sqlQuestion[1024];
	sqlQuestion[0] = '\0';
    
	snprintf(sqlQuestion,sizeof(sqlQuestion),"DELETE FROM %s WHERE eid = ? ","examquestion");
    
	CM_ERRP("the sql:%s",sqlQuestion);

	if (sqlite3_prepare_v2(db, sqlQuestion, -1, &stmtQuestion, NULL) == SQLITE_OK)
	{
		BindParam(stmtQuestion, 1, mID.c_str());
		CM_ERRP("the sql1:%s",mID.c_str());
		if (sqlite3_step(stmtQuestion) != SQLITE_DONE)
		{
			CM_ERRP("exec %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
		}
        
		sqlite3_finalize(stmtQuestion);
	}else{
		CM_ERRP("exec %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
	}
    


//	sqlite3_stmt *stmtOption;
//	CHAR sqlOption[1024];
//	sqlOption[0] = '\0';
//
//	snprintf(sqlOption,sizeof(sqlOption),"DELETE FROM examoption");
//
//	if (sqlite3_prepare_v2(db, sqlOption, -1, &stmtOption, NULL) == SQLITE_OK)
//	{
//		if (sqlite3_step(stmtOption) != SQLITE_DONE)
//		{
//			CM_ERRP("exec %s failed.error:%s", sqlOption, errorMsg);
//		}
//
//		sqlite3_finalize(stmtOption);
//	}
}

//当前题目在数据库中是否存在
BOOL CMExam::ExamExist(TQuestion& item)
{
    BOOL ret = FALSE;
    
    sqlite3_stmt *stmt;
	CHAR sqlQuestion[1024];
	sqlQuestion[0] = '\0';
    
	sqlite3*db = CheckTable();
    
	if (db == NULL)
		return FALSE;
    
	snprintf(sqlQuestion,sizeof(sqlQuestion),"SELECT COUNT(*) FROM %s WHERE eid=? and id=?", "examquestion");
    
	if (sqlite3_prepare_v2(db, sqlQuestion, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, mID.c_str());
		BindParam(stmt, 2, item.item.sID.c_str());
        
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int nCount = sqlite3_column_int(stmt, 0);
            
            if (nCount > 0)
                ret = TRUE;
        }
        
        sqlite3_finalize(stmt);
	}
	else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
	}
    
    return ret;
}

//从XML获取上次做了没提交服务器的答案
BOOL CMExam::GetXMLData(TQuestion& item)
{
    BOOL bRet = FALSE;
    CMString sPath = CMGlobal::TheOne().GetUserDir() + L"examexercise.xml";
	TiXmlDocument *pDoc = new TiXmlDocument(sPath);
    
	if(!pDoc)
		return bRet;
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
                    
					if (strcmp(sid, mID.c_str()) == 0)
					{
                        //读取选项值
                        TiXmlElement* pItem = pQuestion->FirstChildElement("item");
                        while (pItem)
                        {
                            if(strcmp(pItem->Attribute("id"), item.item.sID.c_str()) == 0)
                            {
                                if (item.item.nType == TQuestionType::EText)
                                {
                                    item.item.sAnswer = pItem->Attribute("answer");
                                }
                                else
                                {
                                    //不是问答题
                                    TiXmlElement* pOptionItem = pItem->FirstChildElement("option");
                                    while (pOptionItem)
                                    {
                                        string id;

                                        const char* pStr = NULL;
                                        pStr = pOptionItem->Attribute("id");
                                        if(pStr)
                                        	id = pStr;

                                        int selected = 0;
                                        pOptionItem->Attribute("selected", &selected);
                                        
                                        for (CMList<TOption>::iterator it1 = item.m_lisOption->begin(); it1 != item.m_lisOption->end(); it1++)
                                        {
                                            TOption& option = (TOption&)*it1;
                                            
                                            if(strcasecmp(id.c_str(),option.nID.c_str()))
                                            {
                                                option.bCheck = (selected == 0?FALSE:TRUE);
                                                break;
                                            }
                                        }
                                        pOptionItem = pOptionItem->NextSiblingElement("option");
                                    }
                                }
                            }
                            pItem = pItem->NextSiblingElement("item");
                        }
                        
                        bRet = TRUE;
                 
						break;
					}
                    
					pQuestion = pQuestion->NextSiblingElement("question");
				}
			}
		}
	}
    
	SAFEDELETE(pDoc);
    
    return bRet;
}

BOOL CMExam::UpdateExam(TQuestion& obj)
{
    BOOL ret = FALSE;
    
    //更新对象
    m_mutex.Lock();
    
    for (int i = 0; i < m_lstItem->size(); i++)
    {
        TQuestion& item = m_lstItem->at(i);
        
        if (strcmp(item.item.sID.c_str(), obj.item.sID.c_str()) == 0) {
            item = obj;
            ret = TRUE;
            break;
        }
    }
    m_mutex.UnLock();
    
    //保存入数据库
    sqlite3*db = CheckTable();
    
    if(db == NULL)
    {
        return FALSE;
    }
    
	char *errorMsg;
    
    BOOL retQuestion = FALSE;
    BOOL retOption = FALSE;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMsg) == SQLITE_OK)
    {
        if (obj.item.nType != TQuestionType::EText) //不是问答题
        {
            for (int i = 0; i < obj.m_lisOption->size(); i++)
            {
                TOption option = obj.m_lisOption->at(i);
                
                CHAR sqlOption[1024];
                sqlite3_stmt *stmtOption;
                snprintf(sqlOption,sizeof(sqlOption),"REPLACE INTO %s(sumid, qid, id, description, rightanswer, oldanswer, checked) VALUES (?,?,?,?,?,?,?)", "examoption");
                if (sqlite3_prepare_v2(db, sqlOption, -1, &stmtOption, NULL) == SQLITE_OK)
                {
                    char sumid[128];
                    sprintf(sumid, "%s%s",obj.item.sID.c_str(),option.nID.c_str());
                    BindParam(stmtOption, 1, sumid);
                    BindParam(stmtOption, 2, obj.item.sID.c_str());
                    BindParam(stmtOption, 3, option.nID.c_str());
                    BindParam(stmtOption, 4, option.sText.c_str());
                    BindParam(stmtOption, 5, option.bRightAnswer);
                    BindParam(stmtOption, 6, option.bMyAnswer);
                    BindParam(stmtOption, 7, option.bCheck);
                    
                    
                    if(sqlite3_step(stmtOption) == SQLITE_DONE)
                    {
                        retOption = TRUE;
                    }
                    else
                    {
                        CM_ERRP("exec %s failed.error:%s", sqlOption, sqlite3_errmsg(db));
                    }
                    
                    sqlite3_finalize(stmtOption);
                }
                else
                {
                    CM_ERRP("exec %s failed.error:%s", sqlOption, sqlite3_errmsg(db));
                }
            }
        }
        else
        {
            retOption = TRUE;
        }
        
        CHAR sqlQuestion[1024];
        sqlite3_stmt *stmtQuestion;
        snprintf(sqlQuestion,sizeof(sqlQuestion),"REPLACE INTO %s(eid, id, type, question, value, iswrong, description, rightanswer, oldanswer, newanswer) VALUES (?,?,?,?,?,?,?,?,?,?)", "examquestion");
        if (sqlite3_prepare_v2(db, sqlQuestion, -1, &stmtQuestion, NULL) == SQLITE_OK)
        {
            BindParam(stmtQuestion, 1, mID.c_str());
            BindParam(stmtQuestion, 2, obj.item.sID.c_str());
            BindParam(stmtQuestion, 3, obj.item.nType);
            BindParam(stmtQuestion, 4, obj.item.sQuestion.c_str());
            BindParam(stmtQuestion, 5, obj.item.nValue);
            BindParam(stmtQuestion, 6, obj.item.isWrong);
            BindParam(stmtQuestion, 7, obj.item.sDescription.c_str());
            BindParam(stmtQuestion, 8, obj.item.sRightAnswer.c_str());
            BindParam(stmtQuestion, 9, obj.item.sMyAnswer.c_str());
            BindParam(stmtQuestion, 10, obj.item.sAnswer.c_str());
            
            if(sqlite3_step(stmtQuestion) == SQLITE_DONE)
            {
                retQuestion = TRUE;
            }
            else
            {
                CM_ERRP("exec %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
            }
            
            sqlite3_finalize(stmtQuestion);
        }
        else
        {
            CM_ERRP("exec %s failed.error:%s", sqlQuestion, sqlite3_errmsg(db));
        }
    }
    
    if (retQuestion && retOption)
    {
        if (sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("Failed to commit transaction: %s", errorMsg);
            sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &errorMsg);
            CM_ERRP("Failed to ROLLBACK transaction: %s", errorMsg);
            ret = FALSE;
        }
        
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
        sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &errorMsg);
    }
    return ret;
}

BOOL CMExam::LoadItemStatus(TiXmlElement* pQuestion)
{
    return TRUE;
}

BOOL CMExam::SaveItemStatus(TiXmlElement* pQuestion)
{
    return TRUE;
}

void CMExam::OnCmdResult(TiXmlElement* pItem)
{
    
}


void CMExam::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument *pDoc)
{

    if (nCmdID  ==  SERVICE_COMMITEXAM)
    {
        CMQuestionhandler::OnSessionCmd(nCmdID, nCode, pDoc);
    }
    else
    {
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

                        const char* pStr = NULL;
        				pStr = pItem->Attribute("_dts_");
						if(pStr)
						{
							UpdateItemDstime(mID.c_str(),pStr);
						}

                        sqlite3* db = CheckTable();
                        if (!m_lstItem)
                            m_lstItem = new CMList<TQuestion>;

                        pItem = pItem->FirstChildElement("item");
                        while (pItem)
                        {

                            TQuestion item;
                            
                            //解析网络数据
                            if (DoPutItem(pItem, db, item))
                            {


                                //判断数据库是否存在
                                if (ExamExist(item))
                                {

                                    Refresh(item);
                                }
                                else
                                {
                                    //不存在则从XML取对应数据
                                    GetXMLData(item);
                                }
                                //更新数据库
                                Update(item);

                                m_lstItem->push_back(item);
                            }

                            pItem = pItem->NextSiblingElement("item");
                        }
                        
                        
                        m_pListener->OnUpdateDataFinish(m_UserData,TResult::ESuccess);
                    }else if(nErr==TResult::EExamTimeOut)
                     	m_pListener->OnUpdateDataFinish(m_UserData,TResult::EExamTimeOut);
                    else if(nErr==TResult::ESameData)
                    {
                    	LoadFromDB();
                    	m_pListener->OnUpdateDataFinish(m_UserData,TResult::ESuccess);
                    }
                    else if(nErr == TResult::ENoPowerCourse)
                    {
                    	m_pListener->OnUpdateDataFinish(m_UserData,TResult::ENoPowerCourse);
                    }
                    else if(nErr == TResult::ECantExam)
                    	m_pListener->OnUpdateDataFinish(m_UserData,TResult::ECantExam);
                    else
                    	m_pListener->OnUpdateDataFinish(m_UserData,TResult::EUnknownError);
                }else
                	m_pListener->OnUpdateDataFinish(m_UserData,TResult::EUnknownError);
            }else
            	m_pListener->OnUpdateDataFinish(m_UserData,TResult::EUnknownError);
        }else{
        	m_pListener->OnUpdateDataFinish(m_UserData,TResult::EUnknownError);
        }
    }
}

BOOL CMExam::LoadFromDB()
{
	BOOL ret = FALSE;
	if(m_lstItem)
		m_lstItem->clear();
	else
		m_lstItem = new CMList<TQuestion>;

	sqlite3* db = CheckTable();

	if(!db)
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

}

BOOL CMExam::UpdateItemDstime(const char* examId,const char* dstime)
{
    BOOL ret = FALSE;

    //保存入数据库
    sqlite3*db=CheckTable(m_tablename);
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"REPLACE INTO %s(id, dts) VALUES (?,?)", "examdts");

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
        {
            BindParam(stmt, 1, examId);
            BindParam(stmt, 2, dstime);

            if(sqlite3_step(stmt) == SQLITE_DONE)
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

string CMExam::GetItemDstime(const char* examId)
{
	string dst="";

	//根据obj的sID属性更新
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db=CheckTable(m_tablename);

	if (db == NULL)
		return dst;

	snprintf(sql,sizeof(sql),"SELECT dts FROM %s WHERE id = ?", "examdts");

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		BindParam(stmt, 1, examId);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
        	if(sqlite3_column_text(stmt, 0))
        		dst = (const char*)sqlite3_column_text(stmt, 0);
        }

        sqlite3_finalize(stmt);
	}
	else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return dst;

}


