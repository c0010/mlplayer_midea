// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMEXAMLIST_H_HEADER_INCLUDED_B186213E
#define CMEXAMLIST_H_HEADER_INCLUDED_B186213E

//#include "stdafx.h"
#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

using namespace std;

template <typename T> class CMList;

class TExamListItem
{
  public:
    
    TExamListItem();
    
    ~TExamListItem();
    
    string sID;

    string sTitle;
    
//    BOOL bIsComplete;

    int nRequirecount;

    int nUncompletecount;

    string sTestscores;
    
    int nRanking;
    
    string sDesc;//课程简介

    string sCategory;
    
    BOOL bViewAnswer;//能否查看答案

    int  nUsercompletecount;

    string sPubdate;
    
    string sCompletetime; //完成时间

    int  nQuestioncount;
    
    int nDuration;//考试总时间

    int nRemainTime;//剩余时长

    int nCurrIndex;//当前第几题

    int  nPassmark;//及格分

    int  nFullmark;//总分

    //排名的url
    string sRankurl;
    
    int nTotalNumber;//总共可考试次数

    int nCurrNumber;//当前用户已考试的次数

    string sDstime;//时间戳,请求723协议获取考试题目时需要使用

protected:
    virtual TExamListItem& operator=(const TiXmlElement* right);

    friend class CMExamList;
};

class CMExamList : public CMHandler<TExamListItem>
{
  public:
    CMExamList();

    virtual ~CMExamList();
    
    void SetListener(IMUpdateDataListener* pListener);

    BOOL GetList();
    
    //获取培训班测验
    BOOL GetTrainList(const char* sTrainID);

    BOOL GetExamById(const char* examId);
    
    BOOL UpdateItem(TExamListItem& item);

  protected:
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TExamListItem& item);
    
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    virtual BOOL DoRefresh(TExamListItem& obj);
    
    virtual BOOL DoUpdate(const TExamListItem& obj);
    
    virtual BOOL DoCreate(sqlite3* db);
    
    virtual void DoClear();
    
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    //判断exam是否在数据库中存在
    BOOL ExamExistAtList(const char* eid);
    
    //从XML中读取对应Question的剩余时间和当前做到的题数
    BOOL GetExamData(const char* eid, TExamListItem& item);

  private:
    //void* m_UserData;

    //IMUpdateDataListener *m_pListener;

	//CMSession* m_pSession;

	//CMList<TExamListItem>* m_lstItem;

};



#endif /* CMEXAMLIST_H_HEADER_INCLUDED_B186213E */
