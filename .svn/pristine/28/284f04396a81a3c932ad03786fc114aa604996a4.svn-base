//
//  cmgroup.cpp
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-16.
//  Copyright (c) 2014年 w. All rights reserved.
//
#include "stdafx.h"

#include "cmgroup.h"

#define TABLE_GROUPS "groups"

TGroupInfoItem::TGroupInfoItem()
{
    nUserCount = 0;

    nFlag = 0;

    nIsOccupant = -2;

    m_pSession = NULL;

    m_pListener = NULL;
}

TGroupInfoItem::~TGroupInfoItem()
{

}

void TGroupInfoItem::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}


void TGroupInfoItem::SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleListener)
{
    m_pListener = pUpdateDataListener;

    m_pSimpleListener = pSimpleListener;
}

void TGroupInfoItem::SetUserData(void*userdata)
{
    m_UserData = userdata;
}

TGroupInfoItem& TGroupInfoItem::operator=(const TiXmlElement* right)
{
    const char* pStr = NULL;

    pStr = right->Attribute("id");
    if(pStr)
    {
        sID = pStr;
    }

    pStr = right->Attribute("jid");
    if(pStr)
    {
        sJID = pStr;
    }

    pStr = right->Attribute("pwd");
    if(pStr)
    {
    	sPwd = pStr;
    }

    pStr = right->Attribute("desc");
    if(pStr)
    {
        sDescription = pStr;
    }

    pStr = right->Attribute("name");
    if(pStr)
    {
        sName = pStr;
    }

    pStr = right->Attribute("icon");
    if(pStr)
    {
        sIconUrl = pStr;
    }

    pStr = right->Attribute("orginator");
    if(pStr)
    {
        sOwner = pStr;
    }

    pStr = right->Attribute("orginatorId");
    if(pStr)
    {
        sOwnerId = pStr;
    }

    pStr = right->Attribute("roomnumber");
    if(pStr)
    {
        sRoomNumber = pStr;
    }

    pStr = right->Attribute("nickname");
    if(pStr)
    {
        sNickName = pStr;
    }

    right->QueryIntAttribute("isOccupant", &nIsOccupant);

    right->QueryIntAttribute("JoinType", &nFlag);

    right->QueryIntAttribute("userCount", &nUserCount);

    return *this;
}

void TGroupInfoItem::bindItem(sqlite3_stmt *stmt) const
{
    sqlite3_bind_text(stmt, 1, sID.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 2, sJID.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 3, sName.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 4, sDescription.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 5, sPwd.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 6, sNickName.c_str(), -1,NULL);
    sqlite3_bind_int(stmt, 7, nUserCount);
    sqlite3_bind_text(stmt, 8, sIconUrl.c_str(), -1,NULL);
    sqlite3_bind_int(stmt, 9, nFlag);
    sqlite3_bind_text(stmt, 10, sRoomNumber.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 11, sOwner.c_str(), -1,NULL);
    sqlite3_bind_text(stmt, 12, sOwnerId.c_str(), -1,NULL);
    sqlite3_bind_int(stmt, 13, nIsOccupant);
}

void TGroupInfoItem::fetchItem(sqlite3_stmt *stmt)
{
    sID = (const char*)sqlite3_column_text(stmt, 1);
    sJID =(const char*)sqlite3_column_text(stmt, 2);
    sName = (const char*)sqlite3_column_text(stmt, 3);
    sDescription = (const char*)sqlite3_column_text(stmt, 4);
    sPwd = (const char*)sqlite3_column_text(stmt, 5);
    sNickName = (const char*)sqlite3_column_text(stmt, 6);
    nUserCount = sqlite3_column_int(stmt, 7);
    sIconUrl = sqlite3_column_int(stmt, 8);
    nFlag = sqlite3_column_int(stmt, 9);
    sRoomNumber =  (const char*)sqlite3_column_text(stmt, 10);
    sOwner = (const char*)sqlite3_column_text(stmt, 11);
    sOwnerId = (const char*)sqlite3_column_text(stmt, 12);
    nIsOccupant = sqlite3_column_int(stmt, 13);
}

BOOL TGroupInfoItem::RequestDetailInfo()
{
    if(m_pSession == NULL)
        m_pSession = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    if(strcmp(sID.c_str(), "")==0)
        return false;

	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';

	sqlite3*db=CMDBHelper::GetInstance(1)->GetConnection();

	if (db)
	{
		//从现有缓存内取值
		snprintf(sql,1024,"SELECT * FROM %s WHERE id = ?", TABLE_GROUPS);

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
		{
		    sqlite3_bind_text(stmt, 1, sID.c_str(), -1,NULL);

	        if (sqlite3_step(stmt) == SQLITE_ROW)
	        {
	            fetchItem(stmt);
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
	}


    char sParam[200];
    memset(sParam, 0, 200);

    snprintf(sParam, 200,"id=%s",this->sID.c_str());

    m_pSession->Command(SERVICE_GETGROUPDETAIL, sParam);

    return true;
}

BOOL TGroupInfoItem::RequestEnterGroup(const char*key)
{
    if(m_pSession == NULL)
        m_pSession = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    char sParam[200];
    memset(sParam, 0, 200);

    if(key==NULL|| strlen(key)==0)
        snprintf(sParam, 200,"id=%s",this->sID.c_str());
    else
        snprintf(sParam, 200, "id=%s&key=%s",this->sID.c_str(),key);

    m_pSession->Command(SERVICE_ENTERGROUP, sParam);

    return true;
}


BOOL TGroupInfoItem::ApplyEnterGroup(const char * reason)
{
    if(m_pSession == NULL)
        m_pSession = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    char sParam[1000];
    memset(sParam, 0, 1000);

    if(reason==NULL|| strlen(reason)==0)
        snprintf(sParam, 1000,"id=%s",this->sID.c_str());
    else
    	snprintf(sParam, 1000,"id=%s&msg=%s",this->sID.  c_str(),CMGlobal::TheOne().Encode(reason));

    m_pSession->Command(SERVICE_APPLYENTERGROUP, sParam);

    return true;
}


BOOL TGroupInfoItem::KickGroupOccupant(const char* sids)
{
    return this->GroupManagement(3, sids,NULL);
}

BOOL TGroupInfoItem::InviteToGroup(const char* sids)
{
    return this->GroupManagement(1, sids,NULL);
}

BOOL TGroupInfoItem::SetGroupAdmin(const char* sids)
{
    return this->GroupManagement(2, sids,NULL);
}
BOOL TGroupInfoItem::RemoveGroupAdmin(const char* sids)
{
    return this->GroupManagement(4, sids,NULL);
}

BOOL TGroupInfoItem::AcceptUserApply(const char* sids)
{
    return this->GroupManagement(5, sids,NULL);
}


BOOL TGroupInfoItem::RefuseUserApply(const char* sids, const char* reason)
{
    return this->GroupManagement(6, sids,reason);
}

BOOL TGroupInfoItem::updateGruopInfoWithName(const char* reason)
{
    return this->UpdateGroupInfo(7,reason);
}

BOOL TGroupInfoItem::updateGruopInfoWithDesc(const char *reason)
{
    return this->UpdateGroupInfo(8,reason);
}

BOOL TGroupInfoItem::updateGruopInfoWithPermis(const char *reason)
{
    return this->UpdateGroupInfo(9,reason);
}

BOOL TGroupInfoItem::ExitGroup()
{

    if(m_pSession == NULL)
        m_pSession = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    if(strlen(sID.c_str())==0)
        return false;

    char sParam[1000];
    memset(sParam, 0, 1000);

    snprintf(sParam, 1000,"id=%s",this->sID.c_str());


    m_pSession->Command(SERVICE_EXITRGROUP, sParam);

    return true;
}

BOOL TGroupInfoItem::DisbandGroup()
{

    if(m_pSession == NULL)
        m_pSession = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    if(strlen(sID.c_str())==0)
        return false;

    char sParam[1000];
    memset(sParam, 0, 1000);

    snprintf(sParam, 1000,"id=%s",this->sID.c_str());


    m_pSession->Command(SERVICE_DISBANDGROUP, sParam);

    return true;

}


BOOL TGroupInfoItem::UpdateGroupInfo(int operateType,const char* reason)
{
    if(m_pSession == NULL)
        m_pSession  = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    if(strlen(sID.c_str())==0)
        return false;

    TiXmlElement* pItem =new TiXmlElement("group");

    //设置操作类型
    pItem->SetAttribute("type",operateType);

    pItem->SetAttribute("id", sID.c_str());

    TiXmlText * reasontext = new TiXmlText(reason);
    pItem->LinkEndChild(reasontext);

    //输出
    TiXmlPrinter printer;

    pItem->Accept(&printer);

    string xmlstr= printer.CStr();

    CMList<FormData>* list= new CMList<FormData>;

    FormData data;
    data.key =string("content");
    data.value = printer.CStr();
    data.dataType = 1;
    list->push_back(data);


    m_pSession->CommandPost(SERVICE_GROUPMANAGEMENT, NULL, *list);
    SAFEDELETE(list);
	return TRUE;
}

BOOL TGroupInfoItem::GroupManagement(int operateType,const char* sids,const char* reason)
{

    if(m_pSession == NULL)
        m_pSession  = new CMSession(this);

    if(m_pSession->IsRunning())
        return false;

    if(strlen(sID.c_str())==0)
        return false;

    char temp[strlen(sids)+1];
    temp[strlen(sids)] = '\0';
    strncpy(temp, sids, strlen(sids));

    TiXmlElement* pItem =new TiXmlElement("group");

    //设置操作类型
    pItem->SetAttribute("type",operateType);

    pItem->SetAttribute("id", sID.c_str());

    //遍历需要操作用户的id，添加到xml
    char * key =  strtok(temp, ",");

    while (key !=NULL) {

        TiXmlElement *pChildItem = new TiXmlElement("item");

        if(reason!=NULL && strlen(reason)!=0 )
            pChildItem->SetAttribute("msg", reason);

        TiXmlText * tempKey = new TiXmlText(key);

        pChildItem->LinkEndChild(tempKey);

        pItem->LinkEndChild(pChildItem);

        key = strtok(NULL, ",");

    }

    //输出
    TiXmlPrinter printer;

    pItem->Accept(&printer);

    string xmlstr= printer.CStr();

    CM_LOGP(CM_LOGL_DEBUG, "xml:%s",xmlstr.c_str());

    CMList<FormData>* list= new CMList<FormData>;

    FormData data;
    data.key =string("content");
    data.value = printer.CStr();
    data.dataType = 1;
    list->push_back(data);


    m_pSession->CommandPost(SERVICE_GROUPMANAGEMENT, NULL, *list);
    SAFEDELETE(list);
	return TRUE;
}

BOOL TGroupInfoItem::UploadHead(const char* filename)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;

	CMList<FormData> list;

	FormData data;

	if(filename && strlen(filename) > 0)
	{
		data.key = CMString("pic");
		data.value = CMString(filename);
		data.dataType = 2;
		list.push_back(data);
	}
	else
	{
		return FALSE;
	}
	char param[640];

	snprintf(param, 640,"id=%s", sID.c_str());

	m_pSession->CommandPost(SERVICE_UPGROUPHEADER,param,list,SEQUENCE_NORMAL);

	return TRUE;
}

TGroupInfoItem& TGroupInfoItem::operator=(const TGroupInfoItem& right)
{
    sID=right.sID;
    sJID = right.sJID;
    sName = right.sName;
    sDescription = right.sDescription;
    sPwd = right.sPwd;
    sNickName = right.sNickName;
    nUserCount = right.nUserCount;
    sIconUrl = right.sIconUrl;
    nFlag = right.nFlag;
    sRoomNumber = right.sRoomNumber;
    sOwner = right.sOwner;
    sOwnerId = right.sOwnerId;
    nIsOccupant = right.nIsOccupant;

    return *this;



}



void TGroupInfoItem::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    INT32 result = TResult::EUnknownError;

    if(nCmdID == SERVICE_UPGROUPHEADER)
    {
    	if (nCode == MER_OK) {
			TiXmlElement *pItem = pDoc->RootElement();

			int nErr = TResult::EUnknownError;

			pItem->QueryIntAttribute("errno", &nErr);
			if (nErr == TResult::ESuccess)
			{
				result = TResult::ESuccess;
			}
			else
				result = TResult::EUnknownError;
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

    	if(m_pSimpleListener)
    		m_pSimpleListener->OnRequestFinish(m_UserData, result);

    }
    else
    {
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

					result = TResult::ESuccess;
					if(nCmdID == SERVICE_GETGROUPDETAIL)
					{
						if(pItem->FirstChildElement("item"))
						{
							*this=pItem->FirstChildElement("item");

							sqlite3*db=CMDBHelper::GetInstance(1)->GetConnection();
							if(db)
							{
								sqlite3_stmt *stmt;
								CHAR sql[512];
								snprintf(sql,512,"REPLACE INTO %s(id,jid,name,desc,pwd,nick,uc,icon,flag,roomno,owner,ownerid,isoccupant) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)", TABLE_GROUPS);

								if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
									bindItem(stmt);

									if(sqlite3_step(stmt)==SQLITE_DONE)
									{
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

							if(m_pListener)
								m_pListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
						}
						else
						{
							if(m_pListener)
								m_pListener->OnUpdateDataFinish(m_UserData, TResult::ENothing);
						}

						return;
					}
				}
				else if(nErr == -14 && nCmdID == SERVICE_RATING)
				{
					result = TResult::EDuplicaterating;
				}
				else if(nErr == -26)
				{
					result = TResult::EGroupInexistence;
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

		if(m_pListener)
			m_pListener->OnUpdateDataFinish(m_UserData, result);


    }

}


void CMGroup::SetListener(IMUpdateDataListener* m_pListener,IMSimpleResultListener* pSimpleListener)
{
    this->m_pListener = m_pListener;
    this->m_pSimpleListener = pSimpleListener;
}

BOOL CMGroup::CreateNewGroup(const char* name,const char* desc,const char* iconPath,int flag)
{
    if(!m_pSession)
        m_pSession = new CMSession(this);
    if(m_pSession->IsRunning())
        return FALSE;

    char param[600];

    const CHAR* sName = CMGlobal::TheOne().Encode(name);

    snprintf(param, 600,"&flag=%d&name=%s", flag, sName);  //有修改

    CMList<FormData> list;

    if (iconPath && strlen(iconPath) > 0)
    {
    	FormData data;
        data.key = "pic";
        data.value = iconPath;
        data.dataType = 2;
        list.push_back(data);
    }

    FormData data1;
    data1.key = "desc";
    data1.value = desc;
    data1.dataType = 1;
    list.push_back(data1);

    m_pSession->CommandPost(SERVICE_CREATEGROUP,param,list,SEQUENCE_NORMAL);

}

BOOL CMGroup::RequestMyGroup()
{
    if(IsRunning())
        return false;

    char sParam[200];
    memset(sParam, 0, 200);

    SetPaging(FALSE);
    sprintf(m_tablename,TABLE_GROUPS); //触发建表

    return  CMHandler<TGroupInfoItem>::Request(SERVICE_GETMYGROUP,sParam);
}


BOOL CMGroup::SearchGroup(const char*keyword)
{
    if(IsRunning())
        return false;


    char sParam[200];
    snprintf(sParam,200,"&key=%s",keyword);

    SetPaging(TRUE);
    sprintf(m_tablename,"");  //查找不缓存

    return  CMHandler<TGroupInfoItem>::Request(SERVICE_SEARCHGROUP,sParam);
}


CMGroup::CMGroup():CMHandler<TGroupInfoItem>()
{


}

CMGroup::~CMGroup()
{


}

BOOL CMGroup::DoCreate(sqlite3* db)
{
	if (db == NULL)
		return FALSE;

	if (strcmp(m_tablename, "") == 0)
		return FALSE;

	char *errorMsg;
	char sql[1024];
	snprintf(sql, sizeof(sql),
			"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,jid TEXT DEFAULT '',name TEXT DEFAULT '',desc TEXT DEFAULT '',pwd TEXT DEFAULT '',nick TEXT DEFAULT '',uc INTEGER,icon TEXT DEFAULT '',flag INTEGER,roomno TEXT DEFAULT '',owner TEXT DEFAULT '',ownerid TEXT DEFAULT '',isoccupant INTEGER);",
			m_tablename);

	int i = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);

	if (i == SQLITE_OK)
	{
		return TRUE;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
}


BOOL CMGroup::DoPutItem(TiXmlElement* pItem, sqlite3* db, TGroupInfoItem& item)
{
    item = pItem;

    return  TRUE;
}

void CMGroup::DoClear()
{
	//目前列表没有清除，可能有多余数据，因此不应该使用SetRequestType(1)
	m_mutex.Lock();
    if(m_lstItem)
        m_lstItem->clear();
	m_mutex.UnLock();
}

void CMGroup::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	int result = TResult::ENothing;
	if(SERVICE_CREATEGROUP == nCmdID)
	{
		if (nCode == MER_OK) {
			TiXmlElement *pItem = pDoc->RootElement();

			int nErr = TResult::EUnknownError;

			pItem->QueryIntAttribute("errno", &nErr);
			if (nErr == TResult::ESuccess)
			{
				result = TResult::ESuccess;
			}
			else
				result = TResult::EUnknownError;
		}
		else
			result = ResultHandle(nCode);

		m_pSimpleListener->OnRequestFinish(this->m_UserData, result);

	}
	else
	{
		CMHandler<TGroupInfoItem>::OnSessionCmd(nCmdID, nCode, pDoc);
	}
}
