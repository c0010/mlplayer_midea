// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSURVEYLIST_H_HEADER_INCLUDED_B235FC36
#define CMSURVEYLIST_H_HEADER_INCLUDED_B235FC36

#include "cmcommon.h"
#include "cmhandler.h"
template <typename T> class CMList;

class TSurveyListItem
{
public:
    char sID[100];

    char sTitle[100];

    int nInvitecount;

	int nCompletecount;

	char sDesc[600];

	char sExpiredate[100];//调研的截止日期


};

class CMSurveyList:public CMHandler<TSurveyListItem>
{
  public:
    CMSurveyList(IMUpdateDataListener* pListener);

    virtual ~CMSurveyList();

     // 异步方法，获取调研问卷列表
    BOOL GetList();
    //获取培训班调研
    BOOL GetTrainSurveyList(const char* trainid);
    
    BOOL GetSurveyById(const char* surveyId);

    BOOL RemoveItem(int index);

  protected:
    //缓存建表
    virtual BOOL DoCreate(sqlite3* db);
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TSurveyListItem& item);
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(TSurveyListItem& obj);
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(TSurveyListItem const & obj);

};



#endif /* CMSURVEYLIST_H_HEADER_INCLUDED_B235FC36 */
