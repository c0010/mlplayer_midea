// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMGETNEWCONTENT_H_HEADER_INCLUDED_B19B2DC3
#define CMGETNEWCONTENT_H_HEADER_INCLUDED_B19B2DC3


#include "cmcommon.h"
#include "cmsurveylist.h"
#include "cmexamlist.h"
#include "cmexerciselist.h"
#include "cmqalist.h"
#include "cmtrainapplylist.h"
#include "cmmytrainlist.h"
#include "cmtrainsigninlist.h"
#include <string>
using namespace std;
class CMNewContentListener;

template <typename T> class CMList;

class TContentType
{
public:
    const static int TCourse = 1;
    
    const static int TNews = 2;
    
    const static int TExam = 3;
    
    const static int TExercise = 4;
    
    const static int TSurvey = 5;
    
    const static int TQuestion = 6;

};


class TNewContentItem
{
public:
    //对应的类型：course news exam exercise survey
    char sType[20];
    
    char sTitle[100];
    
    char sDescription[250];
    
    int nModel;
    
    friend class CMGetNewContent;
private:
    void* item;
};

class CMGetNewContent: public IMNotifySession
{
  public:
    static CMGetNewContent* GetInstance();

    virtual ~CMGetNewContent();
    
    void SetListener(IMUpdateDataListener* pListener);

    void Update();
    
    void GetNewContent(const char* sID, const char* sType);
    
    //当前正在请求
	BOOL IsRunning();
    
	//取消请求
	void Cancel();
    
	BOOL Load();
    
    void SetUserData(void* UserData);
    
    //0 课程，1课件
    int GetBrowserItemModel(int nIndex);
    
    //item总数
    int GetItemCount();
    
    //item类型
    int GetItemType(int nIndex);
    
    //通用item
    BOOL GetContentItem(int nIndex, TNewContentItem& item);
    
    //item为课程或资讯
    BOOL GetBrowserItem(int nIndex, TBrowserItem& bitem);
    
    //item为调研
    BOOL GetSurveyItem(int nIndex, TSurveyListItem& item);
    
    //item为考试
    BOOL GetExamItem(int nIndex, TExamListItem& item);
    
    //item为练习
    BOOL GetExerciseItem(int nIndex, TExerciseListItem& item);
    
    //item为qa
    BOOL GetQuestionItem(int nIndex, TQAItem& item);

    BOOL GetApplyItem(int nIndex,TTrainApplyItem& item);

    BOOL GetSignInItem(int nIndex,TTrainSignInItem& item);

    BOOL GetMyTrainItem(int nIndex,TMyTrainItem& item);

  protected:
    CMGetNewContent();
    

  private:
    static CMGetNewContent* m_pTHIS;
    
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    CMList<TNewContentItem*>* m_lstItem;
    
    CMSession* m_pSession;
    
    IMUpdateDataListener* m_pListener;
    
    void* m_pUserData;

  public:
      BOOL m_isPush;					  //是否推送

      string m_cmdtype;			  	  //推送类型

      string m_cmdID;				  //推送ID

};



#endif /* CMGETNEWCONTENT_H_HEADER_INCLUDED_B19B2DC3 */
