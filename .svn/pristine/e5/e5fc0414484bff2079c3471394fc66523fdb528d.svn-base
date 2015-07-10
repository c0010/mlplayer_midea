// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMEXAM_H_HEADER_INCLUDED_B1853320
#define CMEXAM_H_HEADER_INCLUDED_B1853320

#include "cmwrongquestion.h"

class CMExam : public CMWrongQuestion
{
  public:
    CMExam();

    virtual ~CMExam();

    void SetListener(IMUpdateDataListener* pListener,IMSimpleResultListener* pSimpleResultListener);

    void ViewExamQuestion(const char* sID);

    void StartExam(const char* sID);

	//考试剩余时间，单位秒,-1表示时间无限制
	int GetDuration();

	void SetDuration(int second);

	//本地获取数据
	BOOL LoadFromDB();

  protected:

    //更新测验的时间戳
    BOOL UpdateItemDstime(const char* examId,const char* dstime);

    //获取测验的时间戳
    string GetItemDstime(const char* examId);

	virtual void DoCommit();
    
    virtual BOOL SetAnswerItem(TQuestion* itemoption, TiXmlElement* pItem);

	//保存状态，可重载，必须先调用父类的此方法
	virtual BOOL SaveItemStatus(TiXmlElement* pQuestion);

	//读取状态，可重载，必须先调用父类的此方法
	virtual BOOL LoadItemStatus(TiXmlElement* pQuestion);

	//读取状态，可重载，必须调用父类的此方法
	virtual void OnCmdResult(TiXmlElement* pItem);
    
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TQuestion& item);
    
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    virtual BOOL DoRefresh(TQuestion& obj);
    
    virtual BOOL DoUpdate(const TQuestion& obj);
    
    virtual BOOL DoCreate(sqlite3* db);
    
    virtual void DoClear();
    
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    //当前题目在数据库中是否存在
    BOOL ExamExist(TQuestion& item);
    
    //从XML获取上次做了没提交服务器的答案
    BOOL GetXMLData(TQuestion& item);
    
    //从缓存读取选项
    BOOL DoGetOptionCacheItems(sqlite3* db, TQuestion& item);
  private:
    
    BOOL UpdateExam(TQuestion& obj);
    
    BOOL m_bView;//TRUE表示查看考试结果

	char m_sID[100];

	int  m_nDuration;
};



#endif /* CMEXAM_H_HEADER_INCLUDED_B1853320 */
