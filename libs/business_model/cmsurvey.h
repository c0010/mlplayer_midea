// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSURVEY_H_HEADER_INCLUDED_B235FB61
#define CMSURVEY_H_HEADER_INCLUDED_B235FB61
#include "stdafx.h"
#include "cmcommon.h"
#include <string>

using namespace std;

template <typename T> class CMList;

class TSurveyQuestionType
{
  public:
    const static int ESingle = 1;

    const static int EMultiple = 2;

    const static int EText = 3;




};

class TSurveyItem
{
  public:

    string sID;
    // 取值自TSurveyQuestionType
    int nType;

    string sCategory;
    
    string sQuestion;
    
    string sAnswer;
    
    
};

class TSurveyOption
{
public:
	string sID;

	BOOL bCheck;

	string sText;
	
};




class CMSurvey:public IMNotifySession
{
  public:
    CMSurvey(IMUpdateDataListener* pUpdateDataListener, IMSimpleResultListener* pSimpleResultListener);

    virtual ~CMSurvey();

    void SetUserData(void* UserData);

    // 异步方法，得到调研问卷题目列表
    void GetSurvey(const char* sSurveyID);

	//题目数
    int GetItemCount();
	//当前选择题可选项数
    int GetItemOptionCount();

	//得到当前选择题第nIndex个选项
    BOOL GetItemOption(int nIndex, TSurveyOption& option);

	//设置当前题目的答案（问答题）
    void SetAnswer(const char* answer);

    //设置当前选择题第nIndex个选项的答案
    void SetAnswer(int nIndex, BOOL checked);

    void CommitAnswer();
	
	int GetCurIndex();

	//得到第nIndex个题目
    BOOL GetItem(int nIndex, TSurveyItem& item);

	BOOL GetCurItem(TSurveyItem& item);
	
	//获取当前题是否处理 Ｔ已处理 Ｆ 未处理
	BOOL GetCurIsAchieve();
	
	BOOL Prev();
	
	BOOL Next();

	BOOL isFirst();
	
	BOOL isLast();
    
    //保存当前题目状态
    BOOL SaveStatus();
    
    void Cancel();

  protected:
    
    struct TSurveyItemOption
	{
		TSurveyItem		tSurveyItem;
		CMList<TSurveyOption*>* m_lstOption;
	};
    
    // 提交答案前设置一个答案item，返回TRUE表示设置成功，返回FALSE表示这个item不提交
    virtual BOOL SetAnswerItem(TSurveyItemOption* itemoption, TiXmlElement* pItem);
    
    //保存状态 可重载 必须调用父类的此方法
    virtual BOOL SaveItemStatus(TiXmlElement *pQuestion);
    
    //读取状态 可重载 必须调用父类的此方法
    virtual BOOL LoadItemStatus(TiXmlElement *pQuestion);
    
    //读取状态 可重载 必须调用父类的此方法
    virtual void OnCmdResult(TiXmlElement *pItem);
	
  private:
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
	void Clear();
    
    //获取保存状态 内部调用
    BOOL LoadStatus();
    
    //清除保存状态
    BOOL ClearStatus();
    
  private:
    
	IMUpdateDataListener* m_pUpdateDataListener;

    IMSimpleResultListener* m_pSimpleResultListener;

    void* m_UserData;
		
	int m_nCurIndex;
	
	char m_sSurveyID[100];
	
	CMList<TSurveyItemOption*>* m_lstSurVeyItemOption;

	CMSession* m_pSession;
	
	INT32	m_nCount;				//本次返回的item数
};



#endif /* CMSURVEY_H_HEADER_INCLUDED_B235FB61 */
