// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCOMMENT_H_HEADER_INCLUDED_B19B6617
#define CMCOMMENT_H_HEADER_INCLUDED_B19B6617

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

using namespace std;

template <typename T> class CMList;

class CMComment : public CMHandler<TCommentItem>
{
  public:
    CMComment();

    void setListener(IMUpdateDataListener* pUpdateDataListener, IMSimpleResultListener* pSimpleResultListener,IMRatingListener* pRatingListener);

    virtual ~CMComment();

//    void SetUserData(void* UserData);

    BOOL RequestCommentList(const char* sFlag, const char* ClassID, const char* CoursewareID);
    
//    BOOL RequestMore();

//    int GetItemCount();

//    BOOL GetItem(int nIndex, TCommentItem& item);

    //返回false：错误；true：正确
    //参数 1:类型(课程或资讯) 2:课程id 3.课件id（对课程操作时可为空） 4:回复内容 5:是否同步问答
    BOOL SendComment(const char* sFlag, const char* ClassID,  const char* CoursewareID,const char* sContent, BOOL bsyncqa);
	

    
	//返回false：错误；true：正确
	//参数 1:类型(课程或资讯) 2:改类型的id，3:回复评论的id 4:回复内容
//	BOOL ReplyComment(const char* sFlag,const char* sID,const char* sReplyID,const char* sContent);
	
	//参数:该条评论的id
	BOOL CommentLike(const char* sFlag,const char* ClassID,const char* CoursewareID,const char* sReplyID);
    


    
    //获得课件的前2条评论
    BOOL RequestBriefComment(const char* sFlag, const char* ClassID, const char* CoursewareID);

    int GetTotalCount();

//	void Cancel();

//    virtual BOOL IsEnd();
    
  protected:
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	void DoItem(TCommentItem& item,TiXmlElement* pItem);

//	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TCommentItem& item);
//
//	virtual BOOL DoGetCacheItems(sqlite3* db);
//
//	virtual BOOL DoRefresh(TCommentItem& obj);
//
//	virtual BOOL DoUpdate(const TCommentItem& obj);
//
//	virtual BOOL DoCreate(sqlite3* db);
//
//	virtual void DoClear();

  private:

//    BOOL CurrentComment(const char* param,int pageno,int pagesize);

//    IMUpdateDataListener* m_pUpdateDataListener;

    IMSimpleResultListener* m_pSimpleResultListener;
	
	IMRatingListener* m_pRatingListener;

//    void* m_UserData;

//	CMList<TCommentItem>* m_lstItem;

//	CMSession* m_pSession;

//	int m_nPageNo;
//
//	int m_nPageSize;
//
	int m_nPageCount;
	
	int m_nCmdId;

	char m_sReqComment[100];

    char ratingReplyID[64];

};



#endif /* CMCOMMENT_H_HEADER_INCLUDED_B19B6617 */
