// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMQALIST_H_HEADER_INCLUDED_B17F8E47
#define CMQALIST_H_HEADER_INCLUDED_B17F8E47

#include "cmhandler.h"
#include <string>
using namespace std;

class TQAItem
{
public:
    
    TQAItem();
    
    ~TQAItem();
    
    string sID;

    string sQuestion;

    string sQuestioner_username;

    string sQuestioner_fullname;

    string sQuestioner_icon;

    string sPubdate;
    
    string sQcategorytitle;            //问题类别，新增加
    
    string sQcategoryid;               //问题类别ID, 新增加

    BOOL bIsanonymity;               //问题是否匿名

    //浏览数
    int nVC;

    //喜欢数
	int nPV;

	int nAnswercount;

	int nValue;

	int nAttention; //是否关注 0 未关注    1 已关注

	BOOL   bIsresolved; //是否关注 0 未设置正确答案  1 已设置正确答案
    
    string sPic_url;

    string sThumburl;

protected:
    friend class CMQAList;

    void fetchItem(sqlite3_stmt* stmt);
    
    void bindItem(sqlite3_stmt* stmt) const;

};

class CMQAList : public CMHandler<TQAItem>
{
  public:
    CMQAList();

    void SetListener(IMUpdateDataListener* pListener, IMSimpleResultListener* pSimpleResultListener, IMRatingListener* pRatingListener);

    virtual ~CMQAList();

    //此接口返回flag all
    BOOL GetNew();

    //目前版本没有使用
    BOOL GetHot();
    
    BOOL GetQuestionbyId(const char* QaId);
    
    BOOL GetAllQAByCategoryId(const char* categoryId);


    BOOL GetMyQuestion();

	BOOL GetMyAnswer();

	BOOL GetMyAttention();

    BOOL GetByCategory(const char* sCategoryID);

	//sFlag：all所有问题；resolved已解决问题；unresolved待解决问题
	BOOL Search(const char* sFlag, const char* sCategoryID, const char* sKey);

    BOOL NewQuestion(const char* sCategoryID, int nAnonymous, int nValue, const char* sQuestion);

    BOOL AnswerQuestion(const char* sQuestionID, int nAnonymous, const char* sAnswer);

    //带图片的回答问题
    BOOL AnswerQuestion(const char* sQuestionID, int nAnonymous, const char* sAnswer,const char* filename);

    BOOL AskQuestion(const char* sCategoryID, int nAnonymous, int nValue, const char* sQuestion, const char* filename, const char* expertsID);

    BOOL AttentionQuestion(const char* sQuestionID);

  protected:
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TQAItem& item);
    
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    virtual BOOL DoRefresh(TQAItem& obj);

    virtual BOOL DoUpdate(const TQAItem& obj);

    virtual BOOL DoCreate(sqlite3* db);

    virtual void DoClear();
 //   CMList<TQAItem>* m_lstHeadItem;
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

  private:
	IMSimpleResultListener* m_pSimpleResultListener;

	IMRatingListener* m_pRatingListener;

	char m_sCategoryID[64];
	char sQAID[64];
};

#endif /* CMQALIST_H_HEADER_INCLUDED_B17F8E47 */
