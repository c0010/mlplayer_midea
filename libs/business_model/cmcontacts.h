// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCONTACTS_H_HEADER_INCLUDED_B236C6E0
#define CMCONTACTS_H_HEADER_INCLUDED_B236C6E0

#include "stdafx.h"
#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

using namespace std;

template <typename T> class CMList;


class TContactsItem
{
  public:
    string sID;
    string sName;
    
    string sIcon;
    
    string sSex;
    
    string sOrg;
    
    string sDep;
    
    string sPosition;
    
    string sMobilenumber;
    
    string sShortnumber;
    
    string sPhonenumber;
    
    string sEmail;
    
    string sFax;

    string sJid;

    int nIsManager; //2是管理员  5是创始人(也是管理员) 0为普通成员

    TContactsItem();
    ~TContactsItem();


protected:

    //TODO: jid
    void fetchItem(sqlite3_stmt* stmt);
    
    void bindItem(sqlite3_stmt* stmt) const;
    
    TContactsItem& operator=(const TiXmlElement* right);

    friend class CMContacts;
};

class CMContacts : public CMHandler<TContactsItem>
{
  public:
    CMContacts(IMUpdateDataListener* pListener);

    virtual ~CMContacts();

    void SetListener(IMUpdateDataListener* pListener);

 /**
  *	返回联系人搜索结果，较慢
  *
  *	@param	skey	关键字
  */
    BOOL Search(const char* skey);
    
 /**
  *	快速返回联系人搜索结果,返回的数据是全的
  *
  *	@param	skey	关键字,可为中文，或英文
  *
  *	@return 是否成功发出请求
  */
    BOOL QuickSearch(const char* skey);

    /**
     *	根据jid返回cmcontact信息
     *
     *	@param	jid
     *
     *	@return 是否成功发出请求
     */
    BOOL RequestByJid(const char* jid);

    /**
     *	根据id返回cmcontact信息
     *
     *	@param	id
     *
     *	@return 是否成功发出请求
     */
    BOOL RequestById(const char* id);

 /**
  *	加入最近联系人，打电话，发邮件，发短信时调用
  *
  *	@param	item	要加入的item
  *
  *	@return 是否成功加入数据库
  */
    BOOL addRecentContact(const TContactsItem& item);
    
    
 /**
  *	检查联系人是否已是最近联系人
  *
  *	@param	item	联系人信息
  *
  *	@return	是否已是最近联系人
  */
    BOOL isAdded(const TContactsItem& item);


    /**
     *  获得群的用户列表
     *
     *  @param groupid 群id
     *
     *  @return 返回是否请求成功
     */
    BOOL RequestOccupantsList(const char* groupid);
    

    /**
     * 获得培训班用户列表
     *
     * @param trainId 培训班id
     *
     * @return 返回是否请求成功
     */
    BOOL RequestTrainList(const char* trainId);
    
 /**
  *得到最近联系人列表,调用后会清空list，list内数据变为最近联系人
  *
  *	@param
  *
  *	@return
  */
    BOOL getRecentContacts();

    /**
     * 获取问题分类的专家列表， 不分页，不做缓存
     */
    BOOL SearchByQaCategory(const char* sCatID);

protected:
    //缓存建表
    virtual BOOL DoCreate(sqlite3* db) ;
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TContactsItem& item) ;
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db) ;
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(TContactsItem& obj);
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(const TContactsItem& obj) ;
    //清除内存以及缓存里的相关数据
    virtual void DoClear();

  private:

	char m_sKey[256];

};

#endif /* CMCONTACTS_H_HEADER_INCLUDED_B236C6E0 */
