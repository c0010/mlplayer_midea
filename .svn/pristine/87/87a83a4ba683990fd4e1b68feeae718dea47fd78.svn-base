// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////


#include "cmsettings.h"
#include "cmstring.h"
#include "cmpath.h"
#include "tinyxml.h"
#include "cmmyinfo.h"
#include "cmglobal.h"
#include "cmnetworkmgr.h"
#include "cmqacategory.h"
#include "cmmyinfo.h"

CMSettings* CMSettings::m_pTHIS = NULL;


CMSettings* CMSettings::GetInstance()
{
	if(m_pTHIS == NULL)
	{
		m_pTHIS = new CMSettings;
		m_pTHIS->Load();
	}
	return m_pTHIS;
}

CMSettings::~CMSettings()
{
	
}

CMSettings::CMSettings()
{
	m_nIapId = -1;
	//缓冲大小,单位：秒，可选值：30、60、90、120、180
    m_nBufTime = 30;
	//旋转选项： 90左手习惯、270右手习惯
    m_nRotation = 270;
	//使用缩放
    m_nEnableRoom = FALSE;
	// 桌面提醒，0不提醒，1提醒，默认值1
	m_nNewContent = 1;
	// 摇一摇，0不摇，1摇动，默认值1
	m_nShake=1;
	//自动登录，0不自动登录，1自动登录，默认1
	m_bAutoLogin = 0;
	// 自动加载"更多"：0不自动加载，1自动加载，默认1
	m_bAutoLoadMore = 1;
	// 播放模式：1"全屏"、2"普通"，Symbian/Windows Mobile默认为普通，iPhone/Android（Ophone）默认为全屏
	m_nPlayMode = 1;
	// 全屏模式：1"保持宽高比例"、2"填满屏幕"，默认为"保持宽高比例"
	m_nFullScreenMode = 1;
	
	m_bSelServer = FALSE;

	  m_sCenterServerUrl[0]='\0';
         m_sServerUrl[0]='\0';
	  m_sCustomer[0]='\0';
	  m_sName[0] = '\0';
	  m_sPass[0] = '\0';
      m_sUserid[0] = '\0';
      m_sSid = "";
      m_sXmppJid="";
      m_sXmppPwd="";
      m_sXmppHostname="";
      m_sXmppManager="";
       m_pTHIS = NULL;
    
    memset(m_sEnterpriseSlogan, 0, 100);
    memset(m_sEnterpriseTitle, 0, 50);
    memset(m_sEnterpriseID, 0, 20);



}

BOOL CMSettings::DoCreate(sqlite3* db)
{
	char *errorMsg;
	char sql[1024];

    BOOL ret = FALSE;

    if(strlen(LoginInfoTable)!=0)
    {
        snprintf(sql,1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,sid TEXT,xmppjid TEXT,xmpppwd TEXT,xmpphostname TEXT,xmppmanager TEXT)", LoginInfoTable);

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

BOOL CMSettings::DoGetSqlInfo(sqlite3* db)
{
	CHAR sql[1024];

	BOOL ret = FALSE;

	sqlite3_stmt *stmt;

	snprintf(sql, 1024, "SELECT * FROM %s ", LoginInfoTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

		sqlite3_bind_text(stmt, 1, "0", -1, NULL);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			m_sSid = (const char*)sqlite3_column_text(stmt, 2);
			m_sXmppJid = (const char*)sqlite3_column_text(stmt, 3);
			m_sXmppPwd = (const char*)sqlite3_column_text(stmt, 4);
			m_sXmppHostname = (const char*)sqlite3_column_text(stmt, 5);
			m_sXmppManager = (const char*)sqlite3_column_text(stmt, 6);
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

BOOL CMSettings::DoPutSqlInfo(sqlite3* db)
{

    CHAR sql[1024];

    BOOL ret = FALSE;

	sqlite3_stmt *stmt;

    snprintf(sql,1024,"REPLACE INTO %s(id,sid,xmppjid,xmpppwd,xmpphostname,xmppmanager) VALUES (?,?,?,?,?,?)", LoginInfoTable);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

    	sqlite3_bind_text(stmt, 1, "0", -1,NULL);
    	sqlite3_bind_text(stmt, 2, m_sSid.c_str(), -1,NULL);
    	sqlite3_bind_text(stmt, 3, m_sXmppJid.c_str(), -1,NULL);
    	sqlite3_bind_text(stmt, 4, m_sXmppPwd.c_str(), -1,NULL);
    	sqlite3_bind_text(stmt, 5, m_sXmppHostname.c_str(), -1,NULL);
    	sqlite3_bind_text(stmt, 6, m_sXmppManager.c_str(), -1,NULL);

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

}

BOOL CMSettings::Load(const char* customer, const char* user)
{
	BOOL ret = FALSE;
    
    if (strcmp(customer, "") == 0 || strcmp(user, "") == 0)
    {
        return ret;
    }
    
    CMPath pPath(CMPath::DATA_PATH);
    CMString sDir = pPath.String();
    
    if (GetUserName())
    {
        sDir += customer;
        sDir += L"/";
        sDir += user;
    }

    //用户目录下cgf文件 用于保存每个成功登录过的用户信息
    TiXmlDocument *pSettingDoc = new TiXmlDocument(sDir + L"/mlplayer.cfg");
    
    if(pSettingDoc)
    {
        ret = pSettingDoc->LoadFile(TIXML_ENCODING_UTF8);
    }
    
    if(ret)
    {
        //获得根元素setting。
        TiXmlElement *RootElement = pSettingDoc->RootElement();
		
        int ret = 0;
        
        //读取是否自动登录
        TiXmlElement *pItem = RootElement->FirstChildElement("autologin");
        
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_bAutoLogin = ret;
        }
        
        //服务器地址
		pItem = RootElement->FirstChildElement("serverurl");
		if(pItem)
		{
            utf8ncpy(m_sServerUrl,  pItem->Attribute("value"), 299);
        }

		pItem = RootElement->FirstChildElement("customer");
		if(pItem)
		{
            utf8ncpy(m_sCustomer,  pItem->Attribute("value"), 99);
		}
        
        pItem = RootElement->FirstChildElement("userid");
		if(pItem)
		{
            utf8ncpy(m_sUserid,  pItem->Attribute("value"), 49);
		}
        
        //密码
        pItem = RootElement->FirstChildElement("pass");
		if(pItem)
        {
            utf8ncpy(m_sPass, pItem->Attribute("value"), 31);
        }

        //缓冲大小
		pItem = RootElement->FirstChildElement("buftime");
		
		if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nBufTime = ret;
        }
        
        //旋转选项
        pItem = RootElement->FirstChildElement("rotation");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nRotation = ret;
        }
		
        //使用缩放
        pItem = RootElement->FirstChildElement("enableroom");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nEnableRoom = ret;
        }
        //桌面提醒
		pItem = RootElement->FirstChildElement("newcontent");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nNewContent = ret;
        }
         //摇一摇
		pItem = RootElement->FirstChildElement("mshake");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nShake= ret;
        }
        //自动加载"更多"
		pItem = RootElement->FirstChildElement("autoloadmore");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_bAutoLoadMore = ret;
        }
        
        //播放模式
		pItem = RootElement->FirstChildElement("playmode");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nPlayMode = ret;
        }
        
        //全屏模式
		pItem = RootElement->FirstChildElement("fullscreenmode");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nFullScreenMode = ret;
        }
        
  
        
        

    }
    SAFEDELETE(pSettingDoc);
    
    
    return ret;
}


BOOL CMSettings::Load()
{
    BOOL ret = FALSE;
	
    //创建一个XML的文档对象。
    //根目录cgf文件 用于保存最近一次登录用户信息
    CMString fDir = CMPath(CMPath::SYS_CONF_PATH).String() + L"mlplayer.cfg";
	TiXmlDocument *pSettingDoc = new TiXmlDocument(fDir);

	sqlite3 * db=  CMDBHelper::GetInstance(0)->GetConnection();
    DoCreate(db);

    //以UTF8编码方式读取cfg文件
    if(pSettingDoc)
    {
        ret = pSettingDoc->LoadFile(TIXML_ENCODING_UTF8);
    }
    
    if(ret)
    {
        //获得根元素setting。
        TiXmlElement *RootElement = pSettingDoc->RootElement();
		
        int ret = 0;
        
        //是否是ipad
        TiXmlElement *pItem = RootElement->FirstChildElement("iapid");
        
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nIapId = ret;
        }
        
        DoGetSqlInfo(db);

        //获取登录服务器地址
#ifdef __MideaCourse_in_uat__
        pItem = RootElement->FirstChildElement("centerserverurl_in");
#else
        pItem = RootElement->FirstChildElement("centerserverurl_test");
#endif
        if(pItem)
        {
            utf8ncpy(m_sCenterServerUrl, pItem->Attribute("value"), 299);
        }
        
        //读取是否自动登录
        pItem = RootElement->FirstChildElement("autologin");

        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_bAutoLogin = ret;
        }

        //服务器地址
		pItem = RootElement->FirstChildElement("serverurl");
		if(pItem)
		{
            utf8ncpy(m_sServerUrl, pItem->Attribute("value"), 299);
        }

		pItem = RootElement->FirstChildElement("customer");
		if(pItem)
		{
            utf8ncpy(m_sCustomer, pItem->Attribute("value"), 99);
        }

        //密码
        pItem = RootElement->FirstChildElement("name");
		if(pItem)
        {
            utf8ncpy(m_sName, pItem->Attribute("value"), 31);
        }



        //密码
        pItem = RootElement->FirstChildElement("pass");
		if(pItem)
        {
            utf8ncpy(m_sPass, pItem->Attribute("value"), 31);

        }
        
		//sid
//		pItem = RootElement->FirstChildElement("sid");
//		if(pItem)
//		{
//			m_sSid = pItem->Attribute("value");
//		}
//
//
//		pItem = RootElement->FirstChildElement("xmppjid");
//		if(pItem)
//		{
//			m_sXmppJid = pItem->Attribute("value");
//		}
//
//		pItem = RootElement->FirstChildElement("xmpppwd");
//		if(pItem)
//		{
//			m_sXmppPwd = pItem->Attribute("value");
//		}
//
//		pItem = RootElement->FirstChildElement("xmpphostname");
//		if(pItem)
//		{
//			m_sXmppHostname = pItem->Attribute("value");
//		}
//
//		pItem = RootElement->FirstChildElement("xmppmanager");
//		if(pItem)
//		{
//			m_sXmppManager = pItem->Attribute("value");
//		}


        pItem = RootElement->FirstChildElement("userid");
		if(pItem)
		{
            utf8ncpy(m_sUserid, pItem->Attribute("value"), 49);

        }
        //缓冲大小
		pItem = RootElement->FirstChildElement("buftime");

		if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nBufTime = ret;
        }

        //旋转选项
        pItem = RootElement->FirstChildElement("rotation");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nRotation = ret;
        }

        //使用缩放
        pItem = RootElement->FirstChildElement("enableroom");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nEnableRoom = ret;
        }

        //桌面提醒
		pItem = RootElement->FirstChildElement("newcontent");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nNewContent = ret;
        }

     //摇一摇
		pItem = RootElement->FirstChildElement("mshake");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nShake= ret;
        }
        //自动加载"更多"
		pItem = RootElement->FirstChildElement("autoloadmore");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_bAutoLoadMore = ret;
        }

        //播放模式
		pItem = RootElement->FirstChildElement("playmode");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nPlayMode = ret;
        }

        //全屏模式
		pItem = RootElement->FirstChildElement("fullscreenmode");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nFullScreenMode = ret;
        }
        
        
        
        //企业信息
        pItem = RootElement->FirstChildElement("enterprise");
        if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
        {
            m_nFullScreenMode = ret;
        }
        
        //企业信息
        pItem = RootElement->FirstChildElement("enterprise");
		if(pItem)
        {
            utf8ncpy(m_sEnterpriseID, pItem->Attribute("id"), 19);
            utf8ncpy(m_sEnterpriseTitle, pItem->Attribute("title"), 49);
            utf8ncpy(m_sEnterpriseSlogan, pItem->Attribute("slogan"), 99);

        }
        else
        {
            utf8ncpy(m_sEnterpriseID,"wd", 19);
            utf8ncpy(m_sEnterpriseTitle, "", 49);
            utf8ncpy(m_sEnterpriseSlogan, "", 99);
            
        }
    }
    else
    {
    	m_sCustomer[0] = '\0';
		m_sPass[0] = '\0';
		m_sName[0] = '\0';
	}
    SAFEDELETE(pSettingDoc);

    if (strlen(m_sName) > 0)
    {
    	//CMString sDir = CMGlobal::TheOne().GetUserDir();
        
        //用户目录下cgf文件 用于保存每个成功登录过的用户信息
        //此处不能使用GetUserDir()方法获取路径 否则会再次读取根目录cfg
        CMString sDir = CMPath(CMPath::DATA_PATH).String();
        sDir += m_sCustomer;
        sDir += L"/";
        sDir += m_sName;
        sDir += L"/mlplayer.cfg";
        
        pSettingDoc = new TiXmlDocument(sDir);

        if(pSettingDoc)
        {
            ret = pSettingDoc->LoadFile(TIXML_ENCODING_UTF8);
        }

        if(ret)
        {
            //获得根元素setting。
            TiXmlElement *RootElement = pSettingDoc->RootElement();

            int ret = 0;

            //读取是否自动登录
            TiXmlElement *pItem = RootElement->FirstChildElement("autologin");

            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_bAutoLogin = ret;
            }

            //服务器地址
			pItem = RootElement->FirstChildElement("serverurl");
			if(pItem)
			{
                utf8ncpy(m_sServerUrl, pItem->Attribute("value"), 299);
			}

			pItem = RootElement->FirstChildElement("customer");
			if(pItem)
			{
                
                utf8ncpy(m_sCustomer, pItem->Attribute("value"), 99);
			}

            //密码
            pItem = RootElement->FirstChildElement("pass");
    		if(pItem)
            {
                utf8ncpy(m_sPass, pItem->Attribute("value"), 31);
            }

            pItem = RootElement->FirstChildElement("userid");
            if(pItem)
            {
                utf8ncpy(m_sUserid, pItem->Attribute("value"), 49);
            }
            
            //缓冲大小
    		pItem = RootElement->FirstChildElement("buftime");

    		if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nBufTime = ret;
            }

            //旋转选项
            pItem = RootElement->FirstChildElement("rotation");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nRotation = ret;
            }

            //使用缩放
            pItem = RootElement->FirstChildElement("enableroom");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nEnableRoom = ret;
            }

            //桌面提醒
    		pItem = RootElement->FirstChildElement("newcontent");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nNewContent = ret;
            }
            //摇一摇
    		pItem = RootElement->FirstChildElement("mshake");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nShake= ret;
            }
            //自动加载"更多"
    		pItem = RootElement->FirstChildElement("autoloadmore");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_bAutoLoadMore = ret;
            }

            //播放模式
    		pItem = RootElement->FirstChildElement("playmode");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nPlayMode = ret;
            }

            //全屏模式
    		pItem = RootElement->FirstChildElement("fullscreenmode");
            if(pItem && pItem->QueryIntAttribute("value", &ret) == TIXML_SUCCESS)
            {
                m_nFullScreenMode = ret;
            }
        }
        SAFEDELETE(pSettingDoc);
    }

	CMNetConnMgr::Instance().SetConfig(m_nIapId);
    return ret;
}

BOOL CMSettings::Save()
{
	BOOL ret = FALSE;
		
	//保存根目录cgf文件 用于保存最近一次登录用户信息
    TiXmlDocument *pSettingDoc = new TiXmlDocument(CMPath(CMPath::SYS_CONF_PATH).String() + L"mlplayer.cfg");
    
    if(pSettingDoc)
    {
        ret = pSettingDoc->LoadFile(TIXML_ENCODING_UTF8);
    }
    
    if(ret)
    {
        //获得根元素setting。
        TiXmlElement *RootElement = pSettingDoc->RootElement();
        
        TiXmlElement *pItem = RootElement->FirstChildElement("iapid");
        if(pItem)
        {
            pItem->SetAttribute("value", m_nIapId);
		}
        
//        //保存登录服务器地址
//        pItem = RootElement->FirstChildElement("centerserverurl");
//        if(pItem)
//        {
//            strcpy(m_sCenterServerUrl, pItem->Attribute("value"));
//        }
        sqlite3 * db=  CMDBHelper::GetInstance(0)->GetConnection();
        DoPutSqlInfo(db);
        
        pItem = RootElement->FirstChildElement("customer");
        if(pItem)
        {
            pItem->SetAttribute("value", m_sCustomer);
		}
        
//        pItem = RootElement->FirstChildElement("sid");
//        if(pItem)
//        {
//        	pItem->SetAttribute("value",m_sSid.c_str());
//        }
//
//		pItem = RootElement->FirstChildElement("xmppjid");
//		if(pItem)
//		{
//			pItem->SetAttribute("value",m_sXmppJid.c_str());
//		}
//
//		pItem = RootElement->FirstChildElement("xmpppwd");
//		if(pItem)
//		{
//			pItem->SetAttribute("value",m_sXmppPwd.c_str());
//		}
//
//		pItem = RootElement->FirstChildElement("xmpphostname");
//		if(pItem)
//		{
//			pItem->SetAttribute("value",m_sXmppHostname.c_str());
//		}
//
//		pItem = RootElement->FirstChildElement("xmppmanager");
//		if(pItem)
//		{
//			pItem->SetAttribute("value",m_sXmppManager.c_str());
//		}
        pItem = RootElement->FirstChildElement("name");
        if(pItem)
        {
            pItem->SetAttribute("value", m_sName);
		}

        ret = pSettingDoc->SaveFile();
    }
    SAFEDELETE(pSettingDoc);
    
    
    //保存用户目录下cgf文件 用于保存每个成功登录过的用户信息
    CMString sDir = CMGlobal::TheOne().GetUserDir();
    
    pSettingDoc = new TiXmlDocument(sDir  + L"/mlplayer.cfg");

    if(pSettingDoc)
    {
        ret = pSettingDoc->LoadFile(TIXML_ENCODING_UTF8);
    }
    
    if(ret)
    {
			//获得根元素setting。
        TiXmlElement *RootElement = pSettingDoc->RootElement();
        
        TiXmlElement *pItem = RootElement->FirstChildElement("buftime");
        if(pItem)
            pItem->SetAttribute("value", m_nBufTime);
		
        pItem = RootElement->FirstChildElement("rotation");
        if(pItem)
            pItem->SetAttribute("value", m_nRotation);
		
        pItem = RootElement->FirstChildElement("enableroom");
        if(pItem)
            pItem->SetAttribute("value", m_nEnableRoom);

		pItem = RootElement->FirstChildElement("newcontent");
        if(pItem)
            pItem->SetAttribute("value", m_nNewContent);

		pItem = RootElement->FirstChildElement("mshake");
        if(pItem)
            pItem->SetAttribute("value", m_nShake);

		pItem = RootElement->FirstChildElement("autoloadmore");
        if(pItem)
            pItem->SetAttribute("value", m_bAutoLoadMore);

		pItem = RootElement->FirstChildElement("playmode");
        if(pItem)
            pItem->SetAttribute("value", m_nPlayMode);

		pItem = RootElement->FirstChildElement("fullscreenmode");
        if(pItem)
            pItem->SetAttribute("value", m_nFullScreenMode);
		
		pItem = RootElement->FirstChildElement("customer");
        if(pItem)
            pItem->SetAttribute("value", m_sCustomer);
        
        pItem = RootElement->FirstChildElement("serverurl");
        if(pItem)
            pItem->SetAttribute("value", m_sServerUrl);
		
        pItem = RootElement->FirstChildElement("pass");
        if(pItem)
            pItem->SetAttribute("value", m_sPass);
        
        pItem = RootElement->FirstChildElement("userid");
		if(pItem)
            pItem->SetAttribute("value", m_sUserid);
		
		pItem = RootElement->FirstChildElement("autologin");
        if(pItem)
            pItem->SetAttribute("value", m_bAutoLogin);
        
        ret = pSettingDoc->SaveFile();        
    }
    SAFEDELETE(pSettingDoc);
	
    return ret;
}


BOOL CMSettings::DeleteCache()
{
	return CMGlobal::TheOne().ClearCache();
}

int CMSettings::GetBufTime()
{
	return m_nBufTime;
}

void CMSettings::SetBufTime(int nSecond)
{
	m_nBufTime = nSecond;
}

int CMSettings::GetAPId()
{
	return m_nIapId;
}

void CMSettings::SetAPId(int nID)
{
	m_nIapId = nID;
}

int CMSettings::GetPlayMode()
{
	return m_nPlayMode;
}

void CMSettings::SetPlayMode(int nMode)
{
	m_nPlayMode = nMode;
}

int CMSettings::GetFullScreenMode()
{
	return m_nFullScreenMode;
}

void CMSettings::SetFullScreenMode(int nMode)
{
	m_nFullScreenMode = nMode;
}

BOOL CMSettings::GetNewContent()
{
	return m_nNewContent;
}

void CMSettings::SetNewContent(BOOL nFlag)
{
	m_nNewContent= nFlag;
}
BOOL CMSettings::GetShake()
{
	return m_nShake;
}

void CMSettings::SetShake(BOOL nFlag)
{
	m_nShake = nFlag;
}
BOOL CMSettings::GetAutoLoadMore()
{
	return m_bAutoLoadMore;
}

BOOL CMSettings::GetAutoLogin()
{
	return m_bAutoLogin;
}

void CMSettings::SetAutoLoadMore(BOOL nFlag)
{
	m_bAutoLoadMore = nFlag;
}


void CMSettings::SetAutoLogin(BOOL bAutoLogin)
{
	m_bAutoLogin = bAutoLogin;
}


const char * CMSettings::GetUserName()
{
	return m_sName;
}

void CMSettings::SetUserName(const char* name)
{
    utf8ncpy(m_sName, name, 31);
}

const char* CMSettings::GetUserPass()
{
	return m_sPass;
}

void CMSettings::SetUserPass(const char* pass)
{
    utf8ncpy(m_sPass, pass, 31);
}

const char* CMSettings::GetSID()
{
	return m_sSid.c_str();
}

void CMSettings::SetSID(const char* sid)
{
	m_sSid = sid;
	Save();
}

const char* CMSettings::GetUserId()
{
    return m_sUserid;
}

void CMSettings:: SetUserId(const char* uid)
{
    utf8ncpy(m_sUserid, uid, 49);
}

const char* CMSettings::GetCenterServerUrl()
{
	return m_sCenterServerUrl;
}
void CMSettings::SetCenterServerUrl(const char* url)
{
    utf8ncpy(m_sCenterServerUrl, url, 299);
}

const char* CMSettings::GetServerUrl()
{
	return m_sServerUrl;
}

void CMSettings::SetServerUrl(const char* url)
{
    utf8ncpy(m_sServerUrl, url, 299);
}

const char* CMSettings::GetCustomer()
{
	return m_sCustomer;
}

void CMSettings::SetCustomer(const char* name)
{
    utf8ncpy(m_sCustomer, name, 99);
}

BOOL CMSettings::GetSelServer()
{
	return m_bSelServer;
}

void CMSettings::SetSelServer(BOOL bSelServer)
{
	m_bSelServer = bSelServer;
}

BOOL CMSettings::Logout()
{
	CMMyInfo::ClearAll();
    CMGlobal::TheOne().SetSessionID(L"");
	return TRUE;
}

BOOL CMSettings::LogoutWithClearSid()
{
    CMGlobal::TheOne().SetSessionID(L"");
    m_sSid="";
    m_sXmppJid="";
    m_sXmppPwd="";
    m_sXmppHostname="";
    m_sXmppManager="";
    Save();
    CMQACategory::GetInstance()->ClearTree();
    CMMyInfo::ClearAll();
	return TRUE;
}

const char* CMSettings::GetDefautlEnterpriseTitle()
{
	return SETTING.m_sEnterpriseTitle;
    
}

const char* CMSettings::GetDefautlEnterpriseSlogan()
{
	return SETTING.m_sEnterpriseSlogan;
    
}
const char* CMSettings::GetDefautlEnterpriseID()
{
	return SETTING.m_sEnterpriseID;
    
}


const char*  CMSettings::GetXMPPJid()
{
    return m_sXmppJid.c_str();

}
void CMSettings::SetXMPPJid(const char* jid)
{

    m_sXmppJid = jid;
}

const char*  CMSettings::GetXMPPPwd()
{

    return m_sXmppPwd.c_str();


}
void CMSettings::SetXMPPPwd(const char* pwd)
{
    m_sXmppPwd = pwd;
}

const char*  CMSettings::GetXMPPHostname(){

    return m_sXmppHostname.c_str();

}
void CMSettings::SetXMPPHostname(const char* hostname){
    m_sXmppHostname = hostname;
}
const char*  CMSettings::GetXMPPManager()
{
    return m_sXmppManager.c_str();

}
void CMSettings::SetXMPPManager(const char* managerjid)
{

    m_sXmppManager = managerjid;
}
