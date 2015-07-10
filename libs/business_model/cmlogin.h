// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMLOGIN_H_HEADER_INCLUDED_B249C5C7
#define CMLOGIN_H_HEADER_INCLUDED_B249C5C7

#include "cmcommon.h"
#include "cmhandler.h"

template <typename T> class CMList;

class TADImages
{
public:
	char   sImage[200];
};

class CMEnterpriseInfo
{
public:
    //企业id,如wd,wdxx
    char sID[20];
    
    //页面大标识
    char sTitle[50];
    
    //页面标语
    char sSlogan[100];
    
    CMEnterpriseInfo();
    
};

class CMLogin : public CMHandler<CMEnterpriseInfo>
{
  public:
    CMLogin(IMLoginListener* pListener);

    virtual ~CMLogin();

    void SetUserData(void* UserData);
    
    //images 张数
    int GetImagesItemCount();
    
	//第nIndex个选项(目前默认一张, nIndex设为0)
    BOOL GetImagesItem(int nIndex, TADImages& image);

    const char* GetUserName();

    const char* GetPassWord();

    BOOL GetAutoLogin();

    void LoginOffline(const char* sEid, const char* sUserName, const char* sPassWord, BOOL bAutoLogin);
    void Login(const char* sEid, const char* sUserName, const char* sPassWord,const char* sUserId, BOOL bAutoLogin);

    void LoginByMidea(const char* sEid, const char* sMideaUid, const char* sMideaPwd);

    void CancelLogin();

    BOOL GetEnterpriseInfo(CMEnterpriseInfo& item);
    
    void LoadFromDbs();

protected:
    virtual BOOL DoCreate(sqlite3* db);
	virtual BOOL DoGetCacheItems(sqlite3* db);
	virtual BOOL DoRefresh(CMEnterpriseInfo& obj);
	virtual BOOL DoUpdate(const CMEnterpriseInfo& obj);
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, CMEnterpriseInfo& item);

    //adimages保存
    BOOL DoSaveADImages(sqlite3* db, TADImages& img, const char* sID);
    
    //读取adimages
    BOOL DoGetCacheImages(sqlite3* db);
    
    IMLoginListener* m_pListener;

    void* m_UserData;
private:
	//interface from IMNotifySession
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	BOOL m_bLogin;
	
	CMSession* m_pSession;
    
    //登录广告图片
    CMList<TADImages>* m_lisOption;
    
    //存储广告图片数据表
    char  m_sADImagesTableName[64];

};



#endif /* CMLOGIN_H_HEADER_INCLUDED_B249C5C7 */
