// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmcontacts.h"
#include "cmglobal.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"


#define TABLE_RECENT      "contacts_recent"
#define TABLE_MEMBER      "contacts_member"
#define TABLE_GROUPMEMBER "contacts_groupmember"
#define TABLE_TRAINMEMBER "contacts_trainmember"

void TContactsItem::fetchItem(sqlite3_stmt* stmt)
{
    sID =(const char*)sqlite3_column_text(stmt, 1);
    sName = (const char*)sqlite3_column_text(stmt, 2);
    sIcon = (const char*)sqlite3_column_text(stmt, 3);
    sSex = (const char*)sqlite3_column_text(stmt, 4);
    sOrg = (const char*)sqlite3_column_text(stmt, 5);
    sDep = (const char*)sqlite3_column_text(stmt, 6);
    sPosition = (const char*)sqlite3_column_text(stmt, 7);
    sMobilenumber = (const char*)sqlite3_column_text(stmt, 8);
    sShortnumber = (const char*)sqlite3_column_text(stmt, 9);
    sPhonenumber = (const char*)sqlite3_column_text(stmt, 10);
    sEmail = (const char*)sqlite3_column_text(stmt, 11);
    sFax = (const char*)sqlite3_column_text(stmt, 12);
    sJid = (const char*)sqlite3_column_text(stmt, 13);
    nIsManager = -1;
//    nIsManager = sqlite3_column_int(stmt, 14);
}


void TContactsItem::bindItem(sqlite3_stmt* stmt) const
{
    sqlite3_bind_text(stmt, 1, sID.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 2, sName.c_str(), -1,NULL);

    sqlite3_bind_text(stmt, 3, sIcon.c_str(), -1,NULL);

    sqlite3_bind_text(stmt, 4, sSex.c_str(), -1,NULL);

    sqlite3_bind_text(stmt, 5, sOrg.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 6, sDep.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 7, sPosition.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 8, sMobilenumber.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 9, sShortnumber.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 10, sPhonenumber.c_str(), -1,NULL);

    sqlite3_bind_text(stmt, 11, sEmail.c_str(), -1,NULL);

    sqlite3_bind_text(stmt, 12, sFax.c_str(), -1,NULL);

    sqlite3_bind_text(stmt, 13, sJid.c_str(), -1,NULL);

//    sqlite3_bind_int(stmt, 14 , nIsManager);

}

TContactsItem::TContactsItem()
{
    nIsManager = -1;
}

TContactsItem::~TContactsItem()
{
    nIsManager = -1;
}

TContactsItem& TContactsItem::operator=(const TiXmlElement* pItem)
{
    const char* pStr = pItem->Attribute("uid");
    if(pStr)
        sID = pStr;

    pStr = pItem->Attribute("id");

    if(pStr)
        sID = pStr;


    pStr = pItem->Attribute("name");

    if(pStr)
        sName = pStr;

    pStr = pItem->Attribute("icon");
    if(pStr)
       sIcon = pStr;

    pStr = pItem->Attribute("sex");
    if(pStr)
        sSex = pStr;

    pStr = pItem->Attribute("organization");
    if(pStr)
        sOrg = pStr;

    pStr = pItem->Attribute("department");
    if(pStr)
        sDep = pStr;

    pStr = pItem->Attribute("position");
    if(pStr)
        sPosition = pStr;

    pStr = pItem->Attribute("mobilenumber");
    if(pStr)
        sMobilenumber = pStr;

    pStr = pItem->Attribute("shortnumber");
    if(pStr)
        sShortnumber = pStr;

    pStr = pItem->Attribute("phonenumber");
    if(pStr)
        sPhonenumber = pStr;

    pStr = pItem->Attribute("email");
    if(pStr)
        sEmail = pStr;

    pStr = pItem->Attribute("fax");
    if(pStr)
        sFax = pStr;

    pStr = pItem->Attribute("jid");
    if(pStr)
        sJid = pStr;


    pItem->QueryIntAttribute("ismanager", &nIsManager);
    return *this;

}


CMContacts::CMContacts(IMUpdateDataListener* pListener)
:CMHandler<TContactsItem>()
{
//    m_nPageSize = 10;
	SetPaging(TRUE);
//    m_bPaging = true;

    m_pListener = pListener;
    utf8ncpy(m_tablename, TABLE_RECENT, 63);
}

CMContacts::~CMContacts()
{

}
void CMContacts::SetListener(IMUpdateDataListener* pListener)
{
    m_pListener = pListener;

}

BOOL CMContacts::Search(const char* skey)
{
    if(IsRunning())
        return FALSE;

	utf8ncpy(m_tablename, "", 63);

    const CHAR* pKey = CMGlobal::TheOne().Encode(skey);
    utf8ncpy(m_sKey, pKey, 255);
    SAFEDELETE(pKey);

	CMString sParam = L"key=";
	sParam += m_sKey;

	return Request(SERVICE_QUICKFINDCONTACTS, sParam);
}
BOOL CMContacts::QuickSearch(const char* skey)
{
    if(IsRunning()) {
    	//快速查找会取消上次的操作
    	Cancel();
    }

    if(strlen(skey)==0)
        return FALSE;

	utf8ncpy(m_tablename, "", 63);

    const CHAR* pKey = CMGlobal::TheOne().Encode(skey);
    utf8ncpy(m_sKey, pKey, 255);
	SAFEDELETE(pKey);

	CMString sParam = L"key=";
	sParam += m_sKey;

    return Request(SERVICE_QUICKFINDCONTACTS, sParam);;
}

BOOL CMContacts::RequestByJid(const char* jid)
{
    if(IsRunning())
        return FALSE;

    if(strlen(jid)==0)
        return FALSE;

    utf8ncpy(m_tablename, "", 63);

    char sParam[200];
    snprintf(sParam,200,"jid=%s",jid);

    return Request(SERVICE_GETDETAILBYUSERID, sParam);
}

BOOL CMContacts::RequestById(const char* id)
{
    if(IsRunning())
        return FALSE;

    if(strlen(id)==0)
        return FALSE;

    utf8ncpy(m_tablename, "", 63);

    char sParam[200];
    snprintf(sParam,200,"id=%s",id);

    return Request(SERVICE_GETDETAILBYUSERID, sParam);
}

BOOL CMContacts::RequestOccupantsList(const char* groupid)
{

    if(IsRunning())
        return FALSE;

    if(groupid == NULL || strlen(groupid)==0)
        return FALSE;

    m_nCacheDuration = 0;
    utf8ncpy(m_tablename, TABLE_MEMBER, 63);
    utf8ncpy(m_sKey, groupid, 255);

    char sParam[200];
    memset(sParam, 0, 200);
    snprintf(sParam, 200, "id=%s",groupid);

    return Request(SERVICE_GETGROUPMEMBERLIST, sParam);
}

BOOL CMContacts::SearchByQaCategory(const char* sCatID)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);

	if(IsRunning())
		return FALSE;

	if(sCatID == NULL || strlen(sCatID) == 0)
		return FALSE;

	SetPaging(FALSE);

	if (m_lstItem)
	{
		m_lstItem->clear();
	}

	utf8ncpy(m_tablename, "", 63);//不做缓存

	char sParam[256];
	memset(sParam,0,256);
	snprintf(sParam, 256, "categoryid=%s", sCatID);

	return Request(SERVICE_GETEXPERTS, sParam);
}

BOOL CMContacts::RequestTrainList(const char* trainId)
{
	if(IsRunning())
	        return FALSE;

	if(trainId == NULL || strlen(trainId)==0)
		return FALSE;

	utf8ncpy(m_tablename,TABLE_MEMBER,63);
	utf8ncpy(m_sKey,trainId,255);

	char sParam[200];
	memset(sParam, 0, 200);
	snprintf(sParam, 200, "id=%s",trainId);

	return Request(SERVICE_GETEXPERTS, sParam);

}

BOOL CMContacts::getRecentContacts()
{

	utf8ncpy(m_tablename, TABLE_RECENT, 63);

	if(m_pSession&&m_pSession->IsRunning()){
		m_pSession->Cancel();
	}

	if (m_lstItem)
	{
		m_lstItem->clear();
	}

    sqlite3* db = CheckTable(TABLE_RECENT);
    if (!db)
    	return FALSE;

	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

    snprintf(sql,1024,"SELECT *   FROM %s ORDER BY _id DESC; ",TABLE_RECENT );

    if (m_bPaging)
    {
        snprintf(sql,1024,"%s LIMIT %d OFFSET %d", sql, m_nPageSize, (m_nPageNo - 1)*m_nPageSize);
    }

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        if(!m_bPaging || m_nPageNo==1)
        {
            m_mutex.Lock();
            m_lstItem->clear();
            m_mutex.UnLock();
        }

        while(sqlite3_step(stmt)==SQLITE_ROW)
        {

            TContactsItem item;
            item.fetchItem(stmt);
            m_mutex.Lock();

            if(m_lstItem)
                m_lstItem->push_back(item);

            m_mutex.UnLock();

            ret = TRUE;
        }

        if (ret)
        {
            m_nTotalCount = 0;
            snprintf(sql,1024,"SELECT COUNT(*) FROM %s ;",TABLE_RECENT);

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
            {
                if (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    m_nTotalCount = sqlite3_column_int(stmt, 0);
                }

            }
            else
                CM_ERRP("db fail; %s",sqlite3_errmsg(db));

            sqlite3_finalize(stmt);

        }



        ret = TRUE;
	}
    else
    {
        sqlite3_finalize(stmt);

        CM_ERRP("db fail; %s",sqlite3_errmsg(db));
    }

	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData,	TResult::ESuccess);

	return ret;
}


BOOL CMContacts::isAdded(const TContactsItem&item)
{
    sqlite3* db = CheckTable(TABLE_RECENT);

    if(db == NULL || strlen(TABLE_RECENT)== 0)
        return FALSE;

    CHAR sql[1024];

    BOOL ret = FALSE;

	sqlite3_stmt *stmt;

    //查看是否存在数据库
    snprintf(sql,1024,"SELECT COUNT(*) FROM %s WHERE id =? ;", TABLE_RECENT);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

        BindParam(stmt, 1, item.sID.c_str());

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int result = 0;
            result = sqlite3_column_int(stmt, 0);

            if(result <= 0)
                ret = FALSE;
            else
                ret = TRUE;
        }
        else
        {
        	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
    }
    else {
        CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));

    }
    sqlite3_finalize(stmt);


    return  ret;

}



BOOL CMContacts::addRecentContact(const TContactsItem&item)
{
	utf8ncpy(m_tablename, TABLE_RECENT, 63);

    sqlite3* db = CheckTable(TABLE_RECENT);

    //存入数据库
    if(db == NULL)
        return FALSE;

    CHAR sql[1024];

    BOOL ret = FALSE;

	sqlite3_stmt *stmt;

    snprintf(sql,1024,"REPLACE INTO %s(id,name,icon,sex,org,dep,position,mobile_number,short_number,phone_number,email,fax,jid ) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)", TABLE_RECENT);

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
    }
    else {
        CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));

    }
    sqlite3_finalize(stmt);

    return  ret;
}



BOOL CMContacts::DoCreate(sqlite3* db)
{
    char *errorMsg;
	char sql[1024];

    BOOL ret = FALSE;

    if(strlen(m_tablename)!=0)
    {
        snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,name TEXT,icon TEXT,sex TEXT,org TEXT,dep TEXT,position TEXT,mobile_number TEXT,short_number TEXT,phone_number TEXT,email TEXT,fax TEXT,jid TEXT)", m_tablename);

        if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
            ret = TRUE;
        }
        else
        {
            CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
            ret = FALSE;
        }

        if (ret && m_nServiceNo == SERVICE_GETGROUPMEMBERLIST)
        {
        	snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(id TEXT, mid TEXT)", TABLE_GROUPMEMBER, m_tablename);
            if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
                ret = TRUE;
            }
            else
            {
                CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
                ret = FALSE;
            }
        }
        else if(ret && m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
        {
        	snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(id TEXT, mid TEXT)", TABLE_TRAINMEMBER, m_tablename);
			if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
				ret = TRUE;
			}
			else
			{
				CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
				ret = FALSE;
			}
        }

    }

    return ret;
}

 BOOL CMContacts::DoPutItem(TiXmlElement* pItem, sqlite3* db, TContactsItem& item)
{
    if(!pItem)
        return FALSE;

    //存入链表
    item = pItem;

    string tabname = m_tablename;

    //存入数据库
    if(db == NULL || strlen(m_tablename)== 0 ||tabname.compare(TABLE_RECENT)==0)
    {
    	//仍然加入列表
        return TRUE;
    }

    CHAR sql[1024];

    BOOL ret = FALSE;

	sqlite3_stmt *stmt;



    snprintf(sql,1024,"REPLACE INTO %s(id,name,icon,sex,org,dep,position,mobile_number,short_number,phone_number,email,fax,jid ) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)", m_tablename);

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
    }
    else {
        CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));

    }
    sqlite3_finalize(stmt);

    if (ret && m_nServiceNo == SERVICE_GETGROUPMEMBERLIST)
    {
        snprintf(sql,1024,"INSERT INTO %s(id, mid) VALUES(?,?) ", TABLE_GROUPMEMBER, m_tablename);

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) \
        {
//        	CM_ERRP("exec %s value %s %s", sql, m_sKey, item.sID.c_str());
            BindParam(stmt, 1, m_sKey);
            BindParam(stmt, 2, item.sID.c_str());

            if(sqlite3_step(stmt) == SQLITE_DONE)
            {
            	ret = TRUE;
            }
            else
            {
            	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
            }
        }
        else {
            CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));

        }
        sqlite3_finalize(stmt);
    }
    else if (ret && m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
    {
        snprintf(sql,1024,"INSERT INTO %s(id, mid) VALUES(?,?) ", TABLE_TRAINMEMBER, m_tablename);

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) \
        {
//        	CM_ERRP("exec %s value %s %s", sql, m_sKey, item.sID.c_str());
            BindParam(stmt, 1, m_sKey);
            BindParam(stmt, 2, item.sID.c_str());

            if(sqlite3_step(stmt) == SQLITE_DONE)
            {
            	ret = TRUE;
            }
            else
            {
            	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
            }
        }
        else {
            CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));

        }
        sqlite3_finalize(stmt);
    }

    return  ret;
}


//缓存回来数据，读取缓存到对象列表
BOOL CMContacts::DoGetCacheItems(sqlite3* db)
{

    if(strlen(m_tablename)==0)
        return FALSE;

//    m_bPaging = FALSE;

	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

    snprintf(sql,1024,"SELECT * FROM %s ",m_tablename );

    if (m_nServiceNo == SERVICE_GETGROUPMEMBERLIST)
    {
    	snprintf(sql,1024,"%s WHERE id IN (SELECT mid FROM %s WHERE id=?)", sql, TABLE_GROUPMEMBER);
    }
    else if (m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
    {
    	snprintf(sql,1024,"%s WHERE id IN (SELECT mid FROM %s WHERE id=?)", sql, TABLE_TRAINMEMBER);
    }

//    strcat(sql, "ORDER BY _id ");
    if (m_bPaging)
    {
        snprintf(sql,1024,"%s LIMIT %d OFFSET %d", sql, m_nPageSize, (m_nPageNo - 1)*m_nPageSize);
    }

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        if(!m_bPaging || m_nPageNo==1)
        {
            m_mutex.Lock();
            m_lstItem->clear();
            m_mutex.UnLock();
        }

        if (m_nServiceNo == SERVICE_GETGROUPMEMBERLIST||m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
        {
        	BindParam(stmt, 1, m_sKey);
        }

        while(sqlite3_step(stmt)==SQLITE_ROW)
        {

            TContactsItem item;
            item.fetchItem(stmt);
            m_mutex.Lock();

            if(m_lstItem)
                m_lstItem->push_back(item);

            m_mutex.UnLock();

            ret = TRUE;
        }

        if (ret)
        {
            m_nTotalCount = 0;
            snprintf(sql,1024,"SELECT COUNT(*) FROM %s",m_tablename);

            if (m_nServiceNo == SERVICE_GETGROUPMEMBERLIST)
            {
            	snprintf(sql,1024,"%s WHERE id IN (SELECT mid FROM %s WHERE id=?)", sql, TABLE_GROUPMEMBER);
            }
            else if (m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
            {
            	snprintf(sql,1024,"%s WHERE id IN (SELECT mid FROM %s WHERE id=?)", sql, TABLE_TRAINMEMBER);
            }
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
            {
                if (m_nServiceNo == SERVICE_GETGROUPMEMBERLIST || m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
                {
                	BindParam(stmt, 1, m_sKey);
                }

                if (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    m_nTotalCount = sqlite3_column_int(stmt, 0);
                }

                sqlite3_finalize(stmt);
            }
            else
                CM_ERRP("db fail; %s",sqlite3_errmsg(db));

        }


        sqlite3_finalize(stmt);

        ret = TRUE;
	}
    else
    {
        sqlite3_finalize(stmt);

        CM_ERRP("db fail; %s",sqlite3_errmsg(db));
    }

	if(m_pListener)
		m_pListener->OnUpdateDataFinish(m_UserData,	TResult::ESuccess);

	return ret;
}
//从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
 BOOL CMContacts::DoRefresh(TContactsItem& obj)
{
   //do nothing...
    return FALSE;

}
//更新缓存，一般先GetItem或者Refresh后，修改，再Update
BOOL CMContacts::DoUpdate(const TContactsItem& obj)
{
	return FALSE;
//    m_mutex.Lock();
//    for (int i = 0; i < m_lstItem->size(); i++) {
//        TContactsItem *item = &(m_lstItem->at(i));
//
//        if (item->sID == obj.sID) {
//            *item = obj;
////            CM_ERRP("DoRefresh %s success. t \n", item->sID);
//            break;
//        }
//    }
//
//    m_mutex.UnLock();
//
//    if(strlen(m_tablename)==0)
//        return FALSE;
//
//    BOOL ret = FALSE;
//
//    sqlite3*db=CheckTable(m_tablename);
//    if(db)
//    {
//
//		sqlite3_stmt *stmt;
//		CHAR sql[512];
//		snprintf(sql,512,"UPDATE %s SET id=?, name=?, icon=?, sex=?, org=?, dep=?, position=?, mobile_number=?, short_number=?, phone_number=?, email=?, fax=?, jid=? WHERE id=? ", m_tablename);
//
//        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
//
//        	obj.bindItem(stmt);
//
//            BindParam(stmt, 14, obj.sID.c_str());
//
//            if(sqlite3_step(stmt)==SQLITE_DONE)
//            {
//            	ret = TRUE;
//
//            }
//            else {
//            	CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
//            }
//        }
//        else {
//        	CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
//        }
//
//        sqlite3_finalize(stmt);
//    }
//
//    return ret;
}

void CMContacts::DoClear()
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

        if (m_nServiceNo == SERVICE_GETGROUPMEMBERLIST)
        {
        	sqlite3_stmt *stmt;

            snprintf(sql, 1024,"DELETE FROM %s WHERE id=?", TABLE_GROUPMEMBER);

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
            {
               	BindParam(stmt, 1, m_sKey);

                if (sqlite3_step(stmt) != SQLITE_DONE)
                {
                	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
                }

                sqlite3_finalize(stmt);
            }
            else
                CM_ERRP("db fail; %s",sqlite3_errmsg(db));
        }
        else if(m_nServiceNo == SERVICE_GETMYTRAINUSERLIST)
        {
        	sqlite3_stmt *stmt;

            snprintf(sql, 1024,"DELETE FROM %s WHERE id=?", TABLE_TRAINMEMBER);

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
            {
               	BindParam(stmt, 1, m_sKey);

                if (sqlite3_step(stmt) != SQLITE_DONE)
                {
                	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
                }

                sqlite3_finalize(stmt);
            }
            else
                CM_ERRP("db fail; %s",sqlite3_errmsg(db));
        }

        else {
            snprintf(sql, 1024,"DELETE FROM %s", m_tablename);

            if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) != SQLITE_OK)
            {
                CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
            }
        }
    }

}

