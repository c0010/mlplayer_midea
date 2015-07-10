
// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmlogin.h"
#include "cmglobal.h"
#include "cmsettings.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "cmpath.h"
#include "cmfile.h"
#include "cmfavorites.h"
#include "cmcoursedownload.h"
#include "cmmyinfo.h"
#include "cmqacategory.h"

CMEnterpriseInfo::CMEnterpriseInfo()
{
    memset(sID, 0, 20);
    memset(sTitle, 0, 50);
    memset(sSlogan, 0, 100);
    
}

CMLogin::CMLogin(IMLoginListener* pListener)
{
	m_pListener = pListener;
	m_bLogin = FALSE;
	m_pSession = NULL;
	
#if defined(PLAT_IOS)	
	//copy raw file
	CMString sFileName = CMPath(CMPath::SYS_CONF_PATH).String() + L"mlplayer.cfg";
	if(!CMFile::FileExist(sFileName))
	{
		CMString sSrc = CMPath(CMPath::APP_PATH).String() + L"mlplayer.cfg";
		CMFile::CopyFile(sSrc, sFileName);
		
	}
	
	SETTING.Load();
	
	sFileName = CMPath(CMPath::DATA_PATH).String() + L"defaulticon.png";
	if(!CMFile::FileExist(sFileName))
	{
		CMString sSrc = CMPath(CMPath::APP_PATH).String() + L"defaulticon.png";
		CMFile::CopyFile(sSrc, sFileName);
	}
#endif
	
	//初始化一下SystemInfo
	CMGlobal::TheOne().SystemInfo();
    
    //数据库初始化
    utf8ncpy(m_tablename,"enterpriseInfo", 63);
    
    utf8ncpy(m_sADImagesTableName,"adimagesurl", 63);
    
    m_lisOption = new CMList<TADImages>;
    
    sqlite3* db = NULL;
    db = CheckRootTable();
    if(db)
    {
        DoCreate(db);
    }
    
    
    DoGetCacheItems(db);
}

CMLogin::~CMLogin()
{
	SAFEDELETE(m_pSession);
}

void CMLogin::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

const char* CMLogin::GetUserName()
{
	
	return SETTING.GetUserName();
}

const char* CMLogin::GetPassWord()
{
	return SETTING.GetUserPass();
}

//images 张数
int CMLogin::GetImagesItemCount()
{
    return m_lisOption->size();
}

//第nIndex个选项
BOOL CMLogin::GetImagesItem(int nIndex, TADImages& image)
{
    if (nIndex < 0 || nIndex >= GetImagesItemCount()) {
        return FALSE;
    }
    
    image = m_lisOption->at(nIndex);
    
    return true;
}

BOOL CMLogin::GetAutoLogin()
{	
	return SETTING.GetAutoLogin();
}
void CMLogin::LoginOffline(const char* sEid, const char* sUserName, const char* sPassWord, BOOL bAutoLogin)
{
	CMString str="";
	if (!CMGlobal::TheOne().GetSessionID(str))
	{
		//不存在sessionid 不能离线登陆
		if(m_pListener)
			m_pListener->OnLogin(m_UserData, TResult::ENetDisconnect, FALSE);
		return;
	}
//	const char* customer = SETTING.GetCustomer();
//	const char* user = SETTING.GetUserName();
//	const char* pass = SETTING.GetUserPass();
//
//	m_bLogin = FALSE;
//
//	if (strcasecmp(sEid, customer) == 0
//		&& strcmp(sUserName, user) == 0
//		&& strcmp(sPassWord, pass) == 0)
//	{
		CMGlobal::TheOne().SetOffline(TRUE);
//		SETTING.SetAutoLogin(bAutoLogin);
//		SETTING.Save();

//        CMFavorites::GetInstance()->LoadFromDB();
//
//        CMCourseDownload::GetInstance()->LoadFromFile();
//
//        //清除问答分类数据
//        CMQACategory::GetInstance()->ClearTree();


		if(m_pListener)
			m_pListener->OnLogin(m_UserData, TResult::ESuccess, FALSE);
//	}
//	else
//	{
//		if(m_pListener)
//			m_pListener->OnLogin(m_UserData, TResult::EUserOrPassError, FALSE);
//	}
	return ;

}

void CMLogin::Login(const char* sEid, const char* sUserName, const char* sPassWord,const char* sUserId, BOOL bAutoLogin)
{
	if(m_bLogin) return;
		m_bLogin = TRUE;

	CMGlobal::TheOne().SetOffline(FALSE);

	SETTING.SetCustomer(sEid);
	SETTING.SetUserName(sUserName);
	SETTING.SetUserPass(sPassWord);
    SETTING.SetUserId(sUserId);
	SETTING.SetAutoLogin(bAutoLogin);
	SETTING.Save();
	CMString sEID(sEid), sName(sUserName), sPass(sPassWord), sUid(sUserId);
	
	const char* sNewName = (const char *)sName;
		
	if(sNewName == SETTING.GetUserName())
		CMGlobal::TheOne().SetUserStatus(FALSE);
	else
		CMGlobal::TheOne().SetUserStatus(TRUE);	

	if(m_pSession == NULL)
		m_pSession = new CMSession(this);
	if(m_pSession)
		m_pSession->LogIn(sEID, sName, sPass, sUid,FALSE, 1);
}

void CMLogin::LoginByMidea(const char* sEid, const char* sMideaUid, const char* sMideaPwd)
{
	if(m_bLogin)
		return;
	m_bLogin = TRUE;
	CMGlobal::TheOne().SetOffline(FALSE);

	SETTING.SetCustomer(sEid);
	SETTING.SetUserName("");
	SETTING.SetUserPass("");
	SETTING.Save();

	CMGlobal::TheOne().SetUserStatus(FALSE);

	if(m_pSession == NULL)
		m_pSession = new CMSession(this);
	if(m_pSession)
		m_pSession->LogIn(sEid,sMideaUid,sMideaPwd,"",FALSE,2);

}

void CMLogin::CancelLogin()
{
	if(m_pSession)
		m_pSession->Cancel();
}

void CMLogin::LoadFromDbs()
{
	CMFavorites::GetInstance()->LoadFromDB();

	CMCourseDownload::GetInstance()->LoadFromFile();
	//清除问答分类数据
	CMQACategory::GetInstance()->ClearTree();

}

void CMLogin::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;
	BOOL hasNewVersion = FALSE;
    if (nCode == MER_OK && SERVICE_LOGIN == nCmdID)
    {
		ASSERT(pDoc);
		TiXmlElement *pItem = pDoc->RootElement();

		INT32 nErr = 0;
		if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
		{
			if (nErr == 0)
			{
				result = TResult::ESuccess;
				CMGlobal::TheOne().SetUserStatus(TRUE);

				CMString sFileName = CMGlobal::TheOne().GetUserDir() + L"mlplayer.cfg";
				if(!CMFile::FileExist(sFileName))
				{
					CMString sSrc = CMPath(CMPath::SYS_CONF_PATH).String() + L"mlplayer.cfg";
					CMFile::CopyFile(sSrc, sFileName);
					SETTING.Save();
				}

                //处理xmpp信息
                if(pItem)
                {


                   const char* sNode = pItem->Attribute("xmpppwd");
					if(sNode)
					{
						SETTING.SetXMPPPwd(sNode);
					}

                    sNode = NULL;


                    sNode = pItem->Attribute("xmpphost");
					if(sNode)
					{
						SETTING.SetXMPPHostname(sNode);
					}

                    sNode = pItem->Attribute("xmppid");
					if(sNode)
					{
                        char jid[200];
                        memset(jid , 0, 200);

                        const char* host = SETTING.GetXMPPHostname();
                        const char* port = strstr(host, ":");
                        char h[60];  //服务器地址长度不超过59
                        if (port == NULL)
                        {
                        	strncpy(h, host, 60);
                        }
                        else
                        {
                        	//去掉多余port信息
                        	int len = port - host;
                        	strncpy(h, host, len > 60 ? 60 : len);
                        }

                        snprintf(jid, 200, "%s@%s",sNode,h);


                        SETTING.SetXMPPJid(jid);

//                        SETTING.SetXMPPJid(sNode);
					}
                    sNode = NULL;

                    sNode = pItem->Attribute("xmppmanager");
					if(sNode)
					{
                        SETTING.SetXMPPManager(sNode);
					}
                    sNode = NULL;

                }


				TiXmlElement *pChild =  pItem->FirstChildElement("liveupdate");
				if(pChild)
				{
					INT32 nflag = 0;
					if(pChild->QueryIntAttribute("flag",&nflag) == TIXML_SUCCESS)
					{
						if(nflag == 1)
						{
							const char* sNode = pChild->Attribute("url");
							if(sNode)
							{
								CMGlobal::TheOne().SetUpdateUrl(sNode);
								hasNewVersion = TRUE;
							}
						}
					}
				}

				pChild =  pItem->FirstChildElement("server");
				if(pChild)
				{
					const char* sNode = pChild->Attribute("url");
					if(sNode)
					{
						SETTING.SetServerUrl(sNode);
						SETTING.Save();
					}

				}
                
                pChild =  pItem->FirstChildElement("enterprise");
				if(pChild)
				{
                    char *errorMsg;
                    
                    CMEnterpriseInfo item;
                    sqlite3* db = CheckRootTable();
                    
                    if (sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMsg) == SQLITE_OK)
                    {
                        DoPutItem(pChild, db, item);
                    }
                    else
                    {
                        CM_ERRP("Failed to begin transaction: %s", errorMsg);
                    }
                    
                    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                    {
                        sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &errorMsg);
                        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
                    }
				}
                
                
                pChild =  pItem->FirstChildElement("pushinfo");
//				if(pChild)
//				{
//                    const char* stag = pChild->Attribute("tags");
//                    const char* suid = pChild->Attribute("uid");
//
//                    //更新推送信息
//                    CMMyInfo::GetInstance()->UpdatePushInfo(stag, suid);
//
//
//				}
             
                CMDBHelper::GetInstance(1)->CloseConnection();
                
             
//                CMFavorites::GetInstance()->LoadFromDB();
//
//                CMCourseDownload::GetInstance()->LoadFromFile();
//
//                //清除问答分类数据
//                CMQACategory::GetInstance()->ClearTree();
                
         
                
            }
			else if (nErr == MERS_USERNAMEPWD)
			{
				result = TResult::EUserOrPassError;
				CM_ERR("wrong user name or password");
			}
			else if(nErr == MERS_USERUSING)
			{
				result = TResult::EUserusing;
				CM_ERR("user was Logon");
			}
			else if(nErr == -13)
			{
				result = TResult::EUserdisabled;
				CM_ERR("user was Disabled");
			}
			else if(nErr == MERS_VERSION)
			{
				result = TResult::EVersionError;
				CM_ERR("version error");
			}
            else if (nErr == -16)
            {
                result = TResult::EBound;
            }
            else if(nErr == -27)
            {
            	result = TResult::ENotMideaUid;
            }
			else
			{
				result = TResult::EUnknownError;
				CM_ERRP("server return xml errorno %d", nErr);
			}
		}
		else
			result = TResult::EProtocolFormatError;
    }
    else if(nCode == TResult::EUserOrPassError)
    {
		result = TResult::EUserOrPassError;
    }
    else if(nCode == MERN_INITIALIZE)
    {
		result = TResult::ENetDisconnect;
    }
    else
		result = TResult::ENetTimeout;
	
    m_bLogin = FALSE;
	
	if(m_pListener)
		m_pListener->OnLogin(m_UserData, result, hasNewVersion);
}


BOOL CMLogin::DoCreate(sqlite3* db) {
    BOOL ret = FALSE;
    
	char *errorMsg;
	char sql[512];
	snprintf(sql,512,
             "CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,title TEXT,slogan TEXT)",
             m_tablename);
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg) == SQLITE_OK) {
		ret = TRUE;
	} else {
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}
    
    memset(sql, 0, 512);
    
    if (strlen(m_sADImagesTableName) == 0)
    {
        return FALSE;
    }
    snprintf(sql, 512, "CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,imageurl TEXT)",m_sADImagesTableName);
    
    if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
        return ret;
    }
    else{
        CM_ERRP("exec %s failed.error:%s",sql,errorMsg);
        return FALSE;
    }
}

BOOL CMLogin::DoPutItem(TiXmlElement* pItem, sqlite3* db, CMEnterpriseInfo& item) {
	
    BOOL ret = FALSE;
    
    if(!pItem || !db)
        return FALSE;
    
    if(strlen(m_tablename)==0)
        return FALSE;
    
    const CHAR* pStr= NULL;
    
    pStr = pItem->Attribute("id");
    if(pStr)
        utf8ncpy(item.sID,pStr, 19);
    
    pStr = pItem->Attribute("title");
    if(pStr)
        utf8ncpy(item.sTitle,pStr, 49);
    
    
    pStr = pItem->Attribute("slogan");
    if(pStr)
        utf8ncpy(item.sSlogan,pStr, 99);
    
    TiXmlElement* pOptionItem = pItem->FirstChildElement();
    
    while (pOptionItem)
    {
        TADImages imageitem;
        
        pStr = pOptionItem->Attribute("url");
        if (pStr) {
            utf8ncpy(imageitem.sImage, pStr, 199);
        }
        
        m_lisOption->push_back(imageitem);
        
        DoSaveADImages(db, imageitem, item.sID);
        
        pOptionItem = pOptionItem->NextSiblingElement("images");
    }
    
	CHAR sql[1024];
	sqlite3_stmt *stmt;
    snprintf(sql, 1024,"REPLACE INTO %s(id,title,slogan) VALUES (?,?,?)",  m_tablename);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        
        CMHandler<CMEnterpriseInfo>::BindParam(stmt, 1, item.sID);
        CMHandler<CMEnterpriseInfo>::BindParam(stmt, 2, item.sTitle);
        CMHandler<CMEnterpriseInfo>::BindParam(stmt, 3, item.sSlogan);
        
        if(sqlite3_step(stmt) == SQLITE_DONE)
        {
            ret = TRUE;
        }
        else
        {
            ret = FALSE;
            CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
        }

    }
    if(ret)
        DoGetCacheItems(db);
        
    return TRUE;
}

BOOL CMLogin::DoSaveADImages(sqlite3* db, TADImages& img, const char* sID){
    BOOL ret = FALSE;
    
    if (strcmp(m_sADImagesTableName, "") == 0) {
		return TRUE;
	}
    
    CHAR sql[1024];
	sqlite3_stmt *stmt;
	snprintf(sql,1024,
             "REPLACE INTO  %s(id,imageurl) values (?,?)",
             m_sADImagesTableName);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        BindParam(stmt, 1, sID);
        BindParam(stmt, 2, img.sImage);
        
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

BOOL CMLogin::DoRefresh(CMEnterpriseInfo& obj) {
	return false;
}

BOOL CMLogin::DoUpdate(const CMEnterpriseInfo& obj) {
	return false;
}

BOOL CMLogin::DoGetCacheItems(sqlite3* db) {
    
    if(m_lstItem)
        m_lstItem->clear();
    
    BOOL ret = FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	snprintf(sql,1024,"SELECT id,title,slogan from %s order by _id ASC", m_tablename);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {

		while(sqlite3_step(stmt) == SQLITE_ROW) {
            
            CMEnterpriseInfo item;
            
			utf8ncpy(item.sID,
                     (const char*) sqlite3_column_text(stmt, 0), 19);
			utf8ncpy(item.sTitle,
                     (const char*) sqlite3_column_text(stmt, 1), 49);
			utf8ncpy(item.sSlogan, (const char*) sqlite3_column_text(stmt, 2),99);
            
            
            m_mutex.Lock();
            if(!m_lstItem)
                m_lstItem = new CMList<CMEnterpriseInfo>;
            
                m_lstItem->push_back(item);
            m_mutex.UnLock();
            
		}
        ret=TRUE;
    }
    else
        ret = FALSE;
    
    sqlite3_finalize(stmt);
    
    ret = DoGetCacheImages(db);

    
    return ret;
}

BOOL CMLogin::DoGetCacheImages(sqlite3* db)
{
    if(m_lisOption)
        m_lisOption->clear();
    
    BOOL ret = FALSE;
    
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	snprintf(sql,1024,"SELECT imageurl from %s order by _id ASC", m_sADImagesTableName);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        
		while(sqlite3_step(stmt) == SQLITE_ROW) {
            
            TADImages item;
            
			utf8ncpy(item.sImage,
                     (const char*) sqlite3_column_text(stmt, 0), 199);
            
            
            m_mutex.Lock();
            if(!m_lisOption)
                m_lisOption = new CMList<TADImages>;
            
            m_lisOption->push_back(item);
            m_mutex.UnLock();
            
		}
        ret=TRUE;
    }
    else
        ret = FALSE;
    
    sqlite3_finalize(stmt);
    
    return ret;
}
    
BOOL CMLogin::GetEnterpriseInfo(CMEnterpriseInfo& item)
{
    if(!m_lstItem || strlen(item.sID)== 0)
    {
 
        return true;
    }

    for (int i= 0 ; i<GetItemCount(); i++) {
        CMEnterpriseInfo info;
        GetItem(i, info);
        if(strcmp(info.sID, item.sID)==0)
        {
            item=info;
            return true;
        }
    }


    return true;

}




