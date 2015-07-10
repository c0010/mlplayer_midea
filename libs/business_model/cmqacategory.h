// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMQACATEGORY_H_HEADER_INCLUDED_B1865D3B
#define CMQACATEGORY_H_HEADER_INCLUDED_B1865D3B

#include "cmcommon.h"
#include "cmhandler.h"
class CMQACategoryItem;
template <typename T> class CMList;

class CMQACategory : public CMHandler<CMQACategoryItem*>
{
  public:
    
    static CMQACategory* GetInstance();    //单例
    
    virtual ~CMQACategory();

    void SetUserData(void* UserData);
    
    void SetListener(IMUpdateDataListener* pListener);      

    BOOL UpdateData();

    void CancelUpdate();

    int TopItemCount();

    CMQACategoryItem* GetTopItem(int nIndex);

    void ClearTree();

  private:
    CMQACategory();

    CMQACategory(const CMQACategory& other);

    void* m_UserData;

    CMList<CMQACategoryItem*> *m_lstCategoryItem;    //有修改

    IMUpdateDataListener *m_pListener;

	CMSession* m_pSession;

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	void Clear(CMList<CMQACategoryItem*>* plist);

	void CycParser(TiXmlElement *pItem, CMQACategoryItem* pfather);

protected:
    BOOL IsUpdate;

    static CMQACategory* m_pTHIS;      //单例

    
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, CMQACategoryItem* & item);
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    virtual BOOL DoRefresh(CMQACategoryItem* & obj);
    virtual BOOL DoUpdate(CMQACategoryItem* const & obj);
    virtual BOOL DoCreate(sqlite3* db);


    friend class CMLogin;
    
    
 
};

class CMQACategoryItem
{
  public:
    CMQACategoryItem();

    virtual ~CMQACategoryItem();

    int ChildItemCount();

    CMQACategoryItem* GetChildItem(int nIndex);
    
   

    char sID[64];       //categoryid
    char sFlag[20];        //新添加
    char sCategoryTitle[100]; //categoryatitle
    int nQuestioncount;

	friend class CMQACategory;
  private:
    CMList<CMQACategoryItem*> *m_lstCategoryItem;

};

#endif /* CMQACATEGORY_H_HEADER_INCLUDED_B1865D3B */
