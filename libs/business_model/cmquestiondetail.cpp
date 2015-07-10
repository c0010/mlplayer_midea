// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmquestiondetail.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "utf8ncpy.h"

//#include "cmnetworkdatalist.cpp"

TAnswerItem::TAnswerItem()
{
    nAnswerflag = 0;
    nPV = 0;
    nIsliked = 0;
}

TAnswerItem::~TAnswerItem()
{

}

const char* TAnswerItem::GetAnswerItemID() const{
    return sID.c_str();
}

const char* TAnswerItem::GetAnswerItemAnswer() const{
    return sAnswer.c_str();
}

const char* TAnswerItem::GetAnswerItemUserName() const{
    return sAnswerer_username.c_str();
}

const char* TAnswerItem::GetAnswerItemFullName() const{
    return sAnswerer_fullname.c_str();
}

const char* TAnswerItem::GetAnswerItemIcon() const{
    return sAnswerer_icon.c_str();
}

const char* TAnswerItem::GetAnswerItemPubdate() const{
    return sPubdate.c_str();
}

const char* TAnswerItem::GetAnswerItemPicurl() const{
    return sPic_url.c_str();
}

const char* TAnswerItem::GetAnswerItemThumburl() const{
    return sThumburl.c_str();
}


CMQuestionDetail::CMQuestionDetail(IMUpdateDataListener* pListener,
		IMSimpleResultListener* pSimpleResultListener,
		IMRatingListener* pRatingListener) :
		CMHandler<TAnswerItem>(), m_pSimpleResultListener(
				pSimpleResultListener), m_pRatingListener(pRatingListener) {

	this->SetPaging(TRUE);

	m_pListener = pListener;

	memset(sQuestionID, 0, 64);
	memset(sTAID, 0, 64);
}

CMQuestionDetail::~CMQuestionDetail() {
	m_pSimpleResultListener = NULL;

	m_pRatingListener = NULL;

}

BOOL CMQuestionDetail::GetDetail(const char* qID) {
	SetPaging(TRUE);
	char param[150];

	memset(sQuestionID, 0, 64);
	utf8ncpy(sQuestionID, qID, 63);

	snprintf(param,sizeof(param),"&questionid=%s", qID);
	snprintf(m_tablename,sizeof(m_tablename),"AnswerList");
	SetPaging(TRUE);
//	if (!CMGlobal::TheOne().IsOffline())
//		Clear();

	return Request(SERVICE_GETQADETAIL, param);
}

BOOL CMQuestionDetail::SetBestAnswer(const char* sQuestionID,
		const char* sAnswerID) {
	SetPaging(FALSE);
	char param[640];
	snprintf(param,sizeof(param),"&questionid=%s&answerid=%s", sQuestionID, sAnswerID);
	utf8ncpy(sTAID, sAnswerID, 63);
	sprintf(m_tablename, "");  //不缓存

	return Request(SERVICE_SETBESTANSWER, param);
}

BOOL CMQuestionDetail::HasAnswerFlag() {
	return m_hasFlagAnswerItem.nAnswerflag != 0;
}

int CMQuestionDetail::GetHasFlagAnswerItem(TAnswerItem& item) {
	item = m_hasFlagAnswerItem;
	return item.nAnswerflag;
}

BOOL CMQuestionDetail::LikeAnswer(const char* sQuestionID,
		const char* sAnswerID) {
	SetPaging(FALSE);
	char param[640];
	snprintf(param,sizeof(param),"&questionid=%s&answerid=%s", sQuestionID, sAnswerID);
	utf8ncpy(sTAID, sAnswerID, 63);
	sprintf(m_tablename, "");  //不缓存

	return Request(SERVICE_LIKEANSWER, param);
}

BOOL CMQuestionDetail::DoItem(TiXmlElement* pItem, TAnswerItem& item) {
	if (!pItem)
		return FALSE;
	const CHAR* pStr = NULL;

	pStr = pItem->Attribute("id");
	if (pStr)
        item.sID = pStr;

	pStr = pItem->Attribute("answer");
	if (pStr)
        item.sAnswer = pStr;

	pStr = pItem->Attribute("answerer_username");
	if (pStr)
        item.sAnswerer_username = pStr;

	pStr = pItem->Attribute("answerer_fullname");
	if (pStr)
        item.sAnswerer_fullname = pStr;
    
	if (strlen(item.sAnswerer_fullname.c_str()) <= 0)
        item.sAnswerer_fullname = item.sAnswerer_username;

	pStr = pItem->Attribute("answerer_icon");
	if (pStr)
        item.sAnswerer_icon = pStr;

	pStr = pItem->Attribute("pubdate");
	if (pStr)
        item.sPubdate = pStr;

	pItem->QueryIntAttribute("answerflag", &item.nAnswerflag);

	pItem->QueryIntAttribute("pv", &item.nPV);

	pItem->QueryIntAttribute("isliked", &item.nIsliked);

	// int tmp=0;
	//pItem->QueryIntAttribute("isliked",&  tmp);
	//item.bIsliked=tmp;

	TiXmlElement *pChildItem = pItem->FirstChildElement("pic");
	if (pChildItem) {
		pStr = pChildItem->Attribute("url");
        item.sPic_url = pStr;
        pStr = NULL;
        
        pStr = pChildItem->Attribute("thumburl");
        item.sThumburl = pStr;
        
	}

	if (item.nAnswerflag != 0) {
		m_hasFlagAnswerItem = item;
		return FALSE;
	} else
		return TRUE;
}

void CMQuestionDetail::OnSessionCmd(unsigned int nCmdID, unsigned int nCode,
		TiXmlDocument* pDoc) {

	if (nCmdID == SERVICE_GETQADETAIL)
		CMHandler<TAnswerItem>::OnSessionCmd(nCmdID, nCode, pDoc);
	else if (nCmdID == SERVICE_SETBESTANSWER) {
		if (m_pSimpleResultListener) {
			INT32 result = TResult::EUnknownError;
			if (nCode == MER_OK) {
				TiXmlElement *pItem = pDoc->RootElement();

				INT32 nErr = -1;
				pItem->QueryIntAttribute("errno", &nErr);
				if (nErr == 0) {
					TAnswerItem item;
                    item.sID = sTAID;
                    Refresh(item);
                    
                        if (item.nAnswerflag == 0)
                            item.nAnswerflag = 1;
                        else
                            item.nAnswerflag = 0;
                        //item.nPV = nRatting;
                        Update(item);
                    
					result = TResult::ESuccess;
				} else
					result = TResult::EUnknownError;
			} else if (nCode == MERN_INITIALIZE) {
				result = TResult::ENetDisconnect;
			} else if (nCode == MERN_OFFLINE)
				result = TResult::ENotSupportOffline;
			else
				result = TResult::ENetTimeout;

			m_pSimpleResultListener->OnRequestFinish(this->m_UserData, result);
		}
	} else if (nCmdID == SERVICE_LIKEANSWER) {
		if (m_pRatingListener) {
			INT32 result = TResult::EUnknownError;
			INT32 nRatting = 0;
			if (nCode == MER_OK) {
				TiXmlElement *pItem = pDoc->RootElement();

				INT32 nErr = -1;
				pItem->QueryIntAttribute("errno", &nErr);
				if (nErr == 0) {
					pItem->QueryIntAttribute("pv", &nRatting);

                    if (strcmp(sTAID, m_hasFlagAnswerItem.sID.c_str()) == 0) {
                        
                        m_hasFlagAnswerItem.nPV = nRatting;
                        m_hasFlagAnswerItem.nIsliked = 1;
                        
                    }
                    else{
                        
                        TAnswerItem item;
                        item.sID = sTAID;
                        Refresh(item);
                        item.nPV = nRatting;
                        item.nIsliked = 1;
                        Update(item);
                        
                    }
                   
                    
					result = TResult::ESuccess;
				} else
					result = nErr;
			} else if (nCode == MERN_INITIALIZE) {
				result = TResult::ENetDisconnect;
			} else if (nCode == MERN_OFFLINE)
				result = TResult::ENotSupportOffline;
			else
				result = TResult::ENetTimeout;

			m_pRatingListener->OnRating(this->m_UserData, nRatting, result);
		}
	}
}

void CMQuestionDetail::DoClear() {
	m_mutex.Lock();
	if (m_lstItem)
		m_lstItem->clear();
	m_mutex.UnLock();

	sqlite3* db = CheckTable(m_tablename);
	if (db != NULL) {

		CHAR sql[1024];
		sql[0] = '\0';
		sqlite3_stmt *stmt;

		snprintf(sql,sizeof(sql),"DELETE FROM %s WHERE questionid = ? ", m_tablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			BindParam(stmt, 1, sQuestionID);

			if (sqlite3_step(stmt) != SQLITE_DONE) {
				CM_ERRP("exec %s failed.", sql);
			}


		}

	}
}

BOOL CMQuestionDetail::DoCreate(sqlite3* db) {
	char *errorMsg;
	char sql[2048];


	if (strlen(m_tablename) == 0)
		return FALSE;

	snprintf(sql,sizeof(sql),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT,answer TEXT,answer_username TEXT,answer_fullname TEXT,answer_icon TEXT,pubdate TEXT,answerflag INTEGER,pv INTEGER,questionid  TEXT,isliked  INTEGER,pic_url TEXT,thumburl TEXT)",
			m_tablename);

	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK) {
		return TRUE;
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}

}

BOOL CMQuestionDetail::DoPutItem(TiXmlElement* pItem, sqlite3* db,
		TAnswerItem& item) {

	BOOL ret = FALSE;
	if (!pItem)
		return FALSE;
	const CHAR* pStr = NULL;

	pStr = pItem->Attribute("id");
	if (pStr)
        item.sID = pStr;

	pStr = pItem->Attribute("answer");
	if (pStr)
        item.sAnswer = pStr;

	pStr = pItem->Attribute("answerer_username");
	if (pStr)
        item.sAnswerer_username = pStr;

	pStr = pItem->Attribute("answerer_fullname");
	if (pStr)
        item.sAnswerer_fullname = pStr;
	if (strlen(item.sAnswerer_fullname.c_str()) <= 0)
        item.sAnswerer_fullname = item.sAnswerer_username;

	pStr = pItem->Attribute("answerer_icon");
	if (pStr)
        item.sAnswerer_icon = pStr;

	pStr = pItem->Attribute("pubdate");
	if (pStr)
        item.sPubdate = pStr;

	pItem->QueryIntAttribute("answerflag", &item.nAnswerflag);

	pItem->QueryIntAttribute("pv", &item.nPV);

	pItem->QueryIntAttribute("isliked", &item.nIsliked);

	//int tmp=0;
//	pItem->QueryIntAttribute("isliked",&  tmp);
	// item.bIsliked=tmp;
	TiXmlElement *pChildItem = pItem->FirstChildElement("pic");
	if (pChildItem) {
		pStr = pChildItem->Attribute("url");
        item.sPic_url = pStr;
        pStr=NULL;
        
        pStr = pChildItem->Attribute("thumburl");
        item.sThumburl = pStr;
        
	}

	if (item.nAnswerflag != 0) {
		m_hasFlagAnswerItem = item;
		ret = FALSE;
	} else
		ret = TRUE;

	if (!db)
		return FALSE;

	if (strlen(m_tablename) == 0)
		return FALSE;

	CHAR sql[2048];

	sqlite3_stmt *stmt;

	snprintf(sql,sizeof(sql),"INSERT INTO %s(id,answer,answer_username,answer_fullname,answer_icon,pubdate,answerflag,pv,questionid,isliked,pic_url,thumburl) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)",
			m_tablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, item.sID.c_str());
		BindParam(stmt, 2, item.sAnswer.c_str());
		BindParam(stmt, 3, item.sAnswerer_username.c_str());
		BindParam(stmt, 4, item.sAnswerer_fullname.c_str());
		BindParam(stmt, 5, item.sAnswerer_icon.c_str());
		BindParam(stmt, 6, item.sPubdate.c_str());
		BindParam(stmt, 7, item.nAnswerflag);
		BindParam(stmt, 8, item.nPV);
		BindParam(stmt, 9, sQuestionID);
		BindParam(stmt, 10, item.nIsliked);
		BindParam(stmt, 11, item.sPic_url.c_str());
        BindParam(stmt, 12, item.sThumburl.c_str());


		if (sqlite3_step(stmt) == SQLITE_DONE) {
//            if(ret==TRUE)
//                ret = TRUE;
		} else {
			CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
	}

	return ret;

}

BOOL CMQuestionDetail::DoGetCacheItems(sqlite3* db) {
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	//	sprintf(sql, "SELECT id,flag,title,largeimage,image,thumb,type,coursewarecount,url,pubdate,vc,pv,commentcount,enablecomment,enabledownload,enablerating,description,category,tag,specialtopic,credit,studyduration,studyprogress,laststudydate,favoritedate,mycompany,isheaditem FROM %s ORDER BY _id ASC", m_tablename);

	snprintf(sql,sizeof(sql),"SELECT * FROM %s WHERE questionid = ? ORDER BY _id ASC ",
			m_tablename);

	if (m_bPaging) {
		snprintf(sql,sizeof(sql),"%s LIMIT %d OFFSET %d", sql, m_nPageSize,
				(m_nPageNo - 1) * m_nPageSize);
	}

	// printf("error:%d \n",sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) );

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    
		BindParam(stmt, 1, sQuestionID);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			TAnswerItem item;

            item.sID =(const char*) sqlite3_column_text(stmt, 1);

            item.sAnswer = (const char*) sqlite3_column_text(stmt, 2);

            item.sAnswerer_username =(const char*) sqlite3_column_text(stmt, 3);

            item.sAnswerer_fullname =(const char*) sqlite3_column_text(stmt, 4);

            item.sAnswerer_icon =(const char*) sqlite3_column_text(stmt, 5);

            item.sPubdate = (const char*) sqlite3_column_text(stmt, 6);

			item.nAnswerflag = sqlite3_column_int(stmt, 7);

			item.nPV = sqlite3_column_int(stmt, 8);
            
            //9 IS QUESTIONID

			item.nIsliked = sqlite3_column_int(stmt, 10);

            item.sPic_url = (const char*) sqlite3_column_text(stmt, 11);
            
            item.sThumburl = (const char*) sqlite3_column_text(stmt, 12);

			m_mutex.Lock();

			if (m_lstItem)
				m_lstItem->push_back(item);
			m_mutex.UnLock();

			if (item.nAnswerflag != 0) {
				m_hasFlagAnswerItem = item;
			}

		}

		if (ret) {
			//计算总数
			m_nTotalCount = 0;
			snprintf(sql,sizeof(sql),"SELECT COUNT(*) FROM %s WHERE questionid = ? ",
					m_tablename);
			if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
				if (sqlite3_step(stmt) == SQLITE_ROW) {
					BindParam(stmt, 1, sQuestionID);

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

BOOL CMQuestionDetail::DoRefresh(TAnswerItem& obj) {
    BOOL ret = FALSE;

    
    m_mutex.Lock();
    for (int i = 0; i < m_lstItem->size(); i++) {
        TAnswerItem& item = m_lstItem->at(i);
        
        if (strcmp(item.sID.c_str(), obj.sID.c_str()) == 0) {
            obj=item;
            ret = TRUE;
            break;
        }
    }
    m_mutex.UnLock();
    
    
	if (strcmp(m_tablename, "") == 0)
		return FALSE;

	//根据obj的sID属性更新
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db = CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;

	snprintf(sql,sizeof(sql),"SELECT  * FROM %s WHERE id = ? ", m_tablename);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		BindParam(stmt, 1, obj.sID.c_str());

		if (sqlite3_step(stmt) == SQLITE_ROW) {

			TAnswerItem item;

            item.sID =  (const char*) sqlite3_column_text(stmt, 1);

            item.sAnswer = (const char*) sqlite3_column_text(stmt, 2);

            item.sAnswerer_username =(const char*) sqlite3_column_text(stmt, 3);

            item.sAnswerer_fullname =(const char*) sqlite3_column_text(stmt, 4);

            item.sAnswerer_icon = (const char*) sqlite3_column_text(stmt, 5);

            item.sPubdate = (const char*) sqlite3_column_text(stmt, 6);

			item.nAnswerflag = sqlite3_column_int(stmt, 7);

			item.nPV = sqlite3_column_int(stmt, 8);

			//strcpy(sQuestionID, (const char*)sqlite3_column_text(stmt, 9));

			utf8ncpy(sQuestionID, (const char*) sqlite3_column_text(stmt, 9),
					63);

			item.nIsliked = sqlite3_column_int(stmt, 10);

	
            item.sPic_url =  (const char*) sqlite3_column_text(stmt, 11);
            
            item.sThumburl =(const char*) sqlite3_column_text(stmt, 12);

	
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

BOOL CMQuestionDetail::DoUpdate(const TAnswerItem& obj) {
    BOOL ret = FALSE;

    //更新对象
    m_mutex.Lock();
    for (int i = 0; i < m_lstItem->size(); i++) {
        TAnswerItem& item = m_lstItem->at(i);
        
        if (strcmp(item.sID.c_str(), obj.sID.c_str()) == 0) {
            item = obj;
            //若设了最佳答案，踢出链表
            if(item.nAnswerflag!=0)
            {
                
                if(m_lstItem)
                {
                    m_hasFlagAnswerItem=item;

                    m_lstItem->removeAt(i);
                }
                
            }
            ret = TRUE;
            break;
        }
    }
    m_mutex.UnLock();
	if (strlen(sQuestionID) == 0)
		return FALSE;

	if (strcmp(m_tablename, "") == 0) {
		//表名为空表示不需同步数据库，直接返回成功。
		return TRUE;
	}

	//保存入数据库
	sqlite3*db = CheckTable(m_tablename);
	if (db) {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql,sizeof(sql),"UPDATE %s SET id=?, answer=?, answer_username=?, answer_fullname=?, answer_icon=?, pubdate=?, answerflag=?, pv=?, questionid=?, isliked=?, pic_url=?, thumburl=? WHERE id=? ",
				m_tablename);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			BindParam(stmt, 1, obj.sID.c_str());
			BindParam(stmt, 2, obj.sAnswer.c_str());
			BindParam(stmt, 3, obj.sAnswerer_username.c_str());
			BindParam(stmt, 4, obj.sAnswerer_fullname.c_str());
			BindParam(stmt, 5, obj.sAnswerer_icon.c_str());
			BindParam(stmt, 6, obj.sPubdate.c_str());
			BindParam(stmt, 7, obj.nAnswerflag);
			BindParam(stmt, 8, obj.nPV);
			BindParam(stmt, 9, sQuestionID);
			BindParam(stmt, 10, obj.nIsliked);
			BindParam(stmt, 11, obj.sPic_url.c_str());
            BindParam(stmt, 12, obj.sThumburl.c_str());

            BindParam(stmt, 13,obj.sID.c_str());

			if (sqlite3_step(stmt) == SQLITE_DONE) {
			
			} else {
				CM_ERRP("sqlite3_step %s failed.error:%s",
						sql, sqlite3_errmsg(db));
			}
		} else {
			CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	}

	return ret;
}

