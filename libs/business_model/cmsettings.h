// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
////////////////////////////////////////////////////////////////////////////////

#ifndef CMSETTINGS_H_HEADER_INCLUDED_B19A6B88
#define CMSETTINGS_H_HEADER_INCLUDED_B19A6B88

#include "stdafx.h"
#include "cmcommon.h"
#include <string>

#define LoginInfoTable  "loginInfo"

#define SETTING  (*CMSettings::GetInstance())



using namespace std;


class CMSettings
{
  public:
    static CMSettings* GetInstance();

    ~CMSettings();

    //读取设置信息，需要登录后调用
    BOOL Load();
    
    //从指定的用户配置里读取设置信息，不需要用户登录。离线时使用
    BOOL Load(const char* customer, const char* user);

    BOOL Save();

    //清除缓存
    BOOL DeleteCache();

    // 接入点id，仅Symbian、OPhone使用
    int GetAPId();

    void SetAPId(int nID);

    // 缓冲大小,单位：秒，可选值：30、60、90、120、180
    int GetBufTime();

    void SetBufTime(int nSecond);

    // 播放模式：1"全屏"、2"普通"，Symbian/Windows Mobile默认为普通，iPhone/Android（Ophone）默认为全屏
    int GetPlayMode();

    void SetPlayMode(int nMode);

    // 全屏模式：1"保持宽高比例"、2"填满屏幕"，默认为"保持宽高比例"
    int GetFullScreenMode();

    void SetFullScreenMode(int nMode);

    // 桌面提醒，0不提醒，1提醒，默认值1

    BOOL GetNewContent();

    void SetNewContent(BOOL nFlag);
   // 摇一摇，0不摇动，1摇动，默认值1
      BOOL GetShake();

     void SetShake(BOOL nFlag);

    // 自动加载"更多"：0不自动加载，1自动加载，默认1
    BOOL GetAutoLoadMore();

    void SetAutoLoadMore(BOOL nFlag);

    // 自动登录，0不自动登录，1自动登录，默认1
    BOOL GetAutoLogin();

    void SetAutoLogin(BOOL bAutoLogin);
	
	const char*  GetUserName();
	void SetUserName(const char* name);
	
	const char*  GetUserPass();
	void SetUserPass(const char* pass);

	int GetRotation() {return m_nRotation;}
	
	const char* GetCenterServerUrl();
	void SetCenterServerUrl(const char* name);
	
	const char* GetServerUrl();
	void SetServerUrl(const char* name);

	const char* GetCustomer();
	void SetCustomer(const char* name);
	
	BOOL GetSelServer();
	void SetSelServer(BOOL bSelServer);
    
    const char*  GetUserId();
	void SetUserId(const char* uid);

	const char* GetSID();
	void SetSID(const char* sid);

    const char*  GetXMPPJid();
	void SetXMPPJid(const char* jid);

    const char*  GetXMPPPwd();
	void SetXMPPPwd(const char* pwd);

    const char*  GetXMPPHostname();
	void SetXMPPHostname(const char* hostname);

    const char*  GetXMPPManager();
    void SetXMPPManager(const char* managerjid);

    //企业信息
    const char*  GetDefautlEnterpriseID();
	const char*  GetDefautlEnterpriseTitle();
 	const char*  GetDefautlEnterpriseSlogan();

	BOOL Logout();

	BOOL LogoutWithClearSid();

  protected:
    CMSettings();

    BOOL DoCreate(sqlite3* db);

    BOOL DoGetSqlInfo(sqlite3* db);

    BOOL DoPutSqlInfo(sqlite3* db);

  private:
    // 以下三个私有设置，以友元方式供其他类使用
	
		//默认接入点, -1表示询问用户；>0表示一个可用的IapId（^_^至少曾经可用）
		//TCommDbConnPref::SetIapId()的输入参数
    INT32 m_nIapId;
		//#endif
		//缓冲大小,单位：秒，可选值：30、60、90、120、180
    UINT32 m_nBufTime;
	
		//旋转选项： 90左手习惯、270右手习惯
    UINT32  m_nRotation;
		//使用缩放
     BOOL m_nEnableRoom;

	// 桌面提醒，0不提醒，1提醒，默认值1
     BOOL m_nNewContent;
   // 摇一摇，0不摇动，1摇动，默认值1
      BOOL m_nShake;
	// 播放模式：1"全屏"、2"普通"，Symbian/Windows Mobile默认为普通，iPhone/Android（Ophone）默认为全屏
	BOOL m_nPlayMode;

	// 全屏模式：1"保持宽高比例"、2"填满屏幕"，默认为"保持宽高比例"
	BOOL m_nFullScreenMode;
	       
	//自动登录，0不自动登录，1自动登录，默认1
	UINT32 m_bAutoLogin;
	
		// 自动加载"更多"：0不自动加载，1自动加载，默认1
	BOOL m_bAutoLoadMore;
	
	    //服务器的地址形式为111.111.111.111:2222 或者srv.somware.com:2222，端口不输默认80
    char m_sCenterServerUrl[300];
	
    // 服务器的地址
    char m_sServerUrl[300];

	char m_sCustomer[100];//服务器名称

	BOOL m_bSelServer;
	
    // 用户名
    char m_sName[32];

    // 密码
    char m_sPass[32];
    
    // 用户设备 id
    char m_sUserid[50];
    
    // 默认的企业id
    char m_sEnterpriseID[19];

    // 默认的企业title
    char m_sEnterpriseTitle[50];
    
    // 默认的企业slogan
    char m_sEnterpriseSlogan[100];

    string m_sSid;

    string m_sXmppJid;

    string m_sXmppPwd;

    string m_sXmppHostname;

    string m_sXmppManager;

    static CMSettings* m_pTHIS;

	friend class CMSession;

	friend class CMLogin;
    
};



#endif /* CMSETTINGS_H_HEADER_INCLUDED_B19A6B88 */
