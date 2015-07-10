// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMQUESTIONDETAIL_H_HEADER_INCLUDED_B17F8E47
#define CMQUESTIONDETAIL_H_HEADER_INCLUDED_B17F8E47


#include "cmhandler.h"
#include <string>
using namespace std;

class TAnswerItem
{
  public:
    
    TAnswerItem();
    
    ~TAnswerItem();
    
    string sID;

    string sAnswer;

    string sAnswerer_username;

    string sAnswerer_fullname;

    string sAnswerer_icon;

    string sPubdate;

	int nAnswerflag;//0无标记,1满意回答,2推荐答案,3精彩回答

	int nPV; //关注数目

	int    nIsliked;//0表示已未喜欢，1表示已经喜欢
	
	string sPic_url;
    
    string sThumburl;
    
    const char* GetAnswerItemID() const;
    
    const char* GetAnswerItemAnswer() const;
    
    const char* GetAnswerItemUserName() const;
    
    const char* GetAnswerItemFullName() const;
    
    const char* GetAnswerItemIcon() const;
    
    const char* GetAnswerItemPubdate() const;
    
    const char* GetAnswerItemPicurl() const;
    
    const char* GetAnswerItemThumburl() const;

};

class CMQuestionDetail : public CMHandler<TAnswerItem>
{
  public:
    CMQuestionDetail(IMUpdateDataListener* pListener, IMSimpleResultListener* pSimpleResultListener, IMRatingListener* pRatingListener);

     ~CMQuestionDetail();

    BOOL GetDetail(const char* sQuestionID);

    BOOL SetBestAnswer(const char* sQuestionID, const char* sAnswerID);

	BOOL HasAnswerFlag();

	int GetHasFlagAnswerItem(TAnswerItem& item);

	BOOL LikeAnswer(const char* sQuestionID, const char* sAnswerID);

  protected:
	virtual BOOL DoItem(TiXmlElement* pItem, TAnswerItem& item);

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TAnswerItem& item);
    
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    virtual BOOL DoRefresh(TAnswerItem& obj);
    
    virtual BOOL DoUpdate(const TAnswerItem& obj);
    
    virtual BOOL DoCreate(sqlite3* db);
    
    virtual void DoClear();
    
  private:
	IMSimpleResultListener* m_pSimpleResultListener;

	IMRatingListener* m_pRatingListener;

	TAnswerItem m_hasFlagAnswerItem;
    
    
    char sQuestionID[64];
    
    char sTAID[64];
    
    
};

#endif /* CMQUESTIONDETAIL_H_HEADER_INCLUDED_B17F8E47 */
