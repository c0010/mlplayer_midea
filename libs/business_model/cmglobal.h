// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:全局对象类，不允许其他全局函数/变量存在
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMGLOBAL_H_HEADER_INCLUDED_B5B49169
#define CMGLOBAL_H_HEADER_INCLUDED_B5B49169

#include "cmstring.h" 

class CMHttpS;

#ifdef PLAT_SYMBIAN
#include "makecall.h"
#endif

typedef struct _tagSystemInfo {
	INT32	ScreenWidth;
	INT32	ScreenHeight;
	char	AcceptType[200];
	char    CurrLang[20];		//当前系统语言
}CMSystemInfo;

typedef struct _tagIDValue {
	char sID[100];
	char sValue[100];
}IDValue;


//存放全局信息用
//如果有全局实例对象的，建议采用NetConnMgr方式保存
//调用方式CMGlobal::TheOne().NetConnMgr()
//直接返回引用，避免指针判空
class CMGlobal
#ifdef PLAT_SYMBIAN
    : MDialObserver
#endif
{
public:
    static CMGlobal& TheOne();
    static void Release();
    virtual ~CMGlobal();
    
    
    //工具类
    //获取计时值，有时间
    UINT32 GetTickCount();

    //CMHttpS&  HttpServer();

    //会话ID
    BOOL GetSessionID(CMString& sID);
    void SetSessionID(const CMString& sID);

	//软件升级Url
	CMString GetUpdateUrl();
	void SetUpdateUrl(CMString sUpdateUrl);

	//打开一个文档
	void OpenDocument(CMString sDocument);
	
	CMSystemInfo& SystemInfo();

    //打电话
    void MakeCall(const CMString& sNumber);

    //新短信
    void OpenSMSG(const CMString& sNumber);

	void ChangeDesktopPrompt(int nNewMsgPrompt);

	void SetUserStatus(BOOL bChange){ m_bUserChange = bChange;};

	BOOL GetUserStatus(){return m_bUserChange;};

	CMString EncryptPass(const CHAR* src);

	BOOL ClearCache();

	static void Sleep(UINT32 intevel);

    //得到用户目录
	CMString GetUserDir();
    
    //得到根目录
    CMString GetRootDir();


	CHAR* Encode(const CHAR* sIn = NULL);

	//是否离线登录
	BOOL IsOffline();

	BOOL SetOffline(BOOL off);
    
    //是否存在网络
    BOOL IsExistNetwork();
private:
    CMGlobal(); 
    
#ifdef PLAT_WINCE
    CMHttpS*            m_pHttpS;
#endif

    CMString            m_sID;

	CMString			m_sUpdateUrl;
	
	CMSystemInfo*		m_pSystemInfo;

	BOOL                m_bUserChange; //注销换用户名标志

	BOOL                m_bOffline;
#ifdef PLAT_SYMBIAN
	void CallDialedL(TInt aError);
	
	CCallDialer*        m_pCall;
#endif
};



#endif /* CMGLOBAL_H_HEADER_INCLUDED_B5B49169 */
