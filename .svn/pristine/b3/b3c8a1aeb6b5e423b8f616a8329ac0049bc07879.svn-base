// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCATEGORY_H_HEADER_INCLUDED_B19B36D9
#define CMCATEGORY_H_HEADER_INCLUDED_B19B36D9

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

class CMCategoryItem;

class CMCategory : public CMHandler<CMCategoryItem*>
{
  public:
    static CMCategory* GetInstance();

    virtual ~CMCategory();

	void SetListener(IMUpdateDataListener* pListener);

    BOOL UpdateData();
    
    BOOL UpdateCategoryList();

    int TopItemCount();

    CMCategoryItem* GetTopItem(int nIndex);
    
    //2000协议更新各模块未完成count
    void SetExamSurveyCount(int count, const char* type);

    BOOL GetCacheData();

  protected:
    CMCategory();

    //更改读取网络数据后不在网络数据范围被的数据库数据
	BOOL UpdateCache();

    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, CMCategoryItem*& item);
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    virtual BOOL DoRefresh(CMCategoryItem*& obj);
    virtual BOOL DoUpdate(CMCategoryItem*  const &obj);
    virtual BOOL DoCreate(sqlite3* db);
    virtual void DoClear();

  private:
    static CMCategory* m_pTHIS;

    string sqlNotin;

	void ClearTree(CMList<CMCategoryItem*>*plist);
	BOOL DoGetCacheTreeItems(sqlite3* db, CMList<CMCategoryItem*>* plist, const char* topid);


	void InitSubscription();

	CMCategoryItem* GetCategoryItem(const char* sTopID, const char* sID);

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

};

class CMCategoryItem
{
  public:
    CMCategoryItem();

    ~CMCategoryItem();

	// 分隔符前面的项数（包含分隔符本身），用于在主界面的上方横排显示
    int FrontChildItemCount();

    int ChildItemCount();

    CMCategoryItem* GetChildItem(int nIndex);
    
    int GetPositionCourseItem();

    int EnablesubscriptionChildItemCount();
    
    int SelectedChildItemCount();  //返回被用户选择订阅的样栏目数
    
    CMCategoryItem* GetSelectedChildItem(int nIndex);  //返回第nIndex个被选中订阅的子栏目；
    
    void RemoveChildItem(int nIndex);

    CMCategoryItem* GetEnablesubscriptionChildItem(int nIndex);
    
    BOOL GetSubscription();

    void SetSubscription(BOOL bFlag);

    char sID[64];

    char sType[16];

    char sTitle[100];

    char sImage[300];

    BOOL bEnablesubscription;

	int nItemcount;

	BOOL bIsSelected; //栏位订阅属性

	friend class CMCategory;

  private:

    CMCategoryItem* GetCategoryItem(const char* sID);

    CMList<CMCategoryItem*> *m_lstItem;
    
    BOOL m_bSubscription;

	char m_sTopID[64];
};

#endif /* CMCATEGORY_H_HEADER_INCLUDED_B19B36D9 */
