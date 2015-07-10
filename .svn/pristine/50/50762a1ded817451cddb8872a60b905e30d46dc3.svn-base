// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMQUESTIONHANDLER_H_HEADER_INCLUDED_B18542E8
#define CMQUESTIONHANDLER_H_HEADER_INCLUDED_B18542E8

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

using namespace std;

template <typename T> class CMList;

class TQuestionType
{
  public:
    const static int ESingle = 1;

    const static int EMultiple = 2;

    const static int EText = 3;
};

class TQuestionItem
{
public:
    
    TQuestionItem();
    
    ~TQuestionItem();

    string sID;

    // 取值自TQuestionType
    int nType;
    
    // 题目分类，调研专用
    string sCategory;

    // 题目标题
    string sQuestion;

    // 题目详情
    string sDescription;

    // 分值，考试专用
    int nValue;

    // 是否在错题库（当前动态编辑）
    BOOL isWrong;

    // 正确答案
    string sRightAnswer;

    // 上次答题我的答案
    string sMyAnswer;

	//本次答题答案
	string sAnswer;

	// 是否在错题库(服务器原始值)
    BOOL isWrongOrig;

    //是否正确(本地保存时使用)
    BOOL isRight;
    
    //是否已做
    BOOL isChecked;
    
    const char* GetQuestionItemID() const;
    
    int GetQuestionItemType() const;
    
    const char* GetQuestionItemCategory() const;
    
    const char* GetQuestionItemQuestion() const;
    
    const char* GetQuestionItemDescription() const;
    
    int GetQuestionItemValue() const;
    
    const char* GetQuestionItemRightAnswer() const;
    
    const char* GetQuestionItemMyAnswer() const;
    
    const char* GetQuestionItemAnswer() const;
    
    BOOL GetQuestionItemRight() const;
    
    BOOL GetQuestionItemChecked() const;
    
protected:
    
    int BindParam(sqlite3_stmt* stmt,int col,int value) const;
    
    int BindParam(sqlite3_stmt* stmt,int col,const char* value) const;
    
    int BindParam(sqlite3_stmt* stmt,int col,float value) const;
    
    //绑定属性,sql中使用
    virtual   void bindItem(sqlite3_stmt * stmt) const;
	
    friend class CMDBHelper;
    
};

class TOption
{
public:
    TOption();
    
    ~TOption();
    
    string sSID;//每道题的id

	string nID;//每道题的选择项编号

	BOOL bCheck;//每道题的选择项选中

	BOOL bMyAnswer;//每道题的选择项答案

    BOOL bRightAnswer;//每道题的选择项正确答案

	string sText;//每道题的选择项内容

    const char* GetOptionItemsID() const;
    
    const char* GetOptionItemnID() const;
    
    const char* GetOptionItemText() const;
    
    BOOL GetOptionItemCheck() const;
    
    BOOL GetOptionItemMyAnswer() const;
    
    BOOL GetOptionItemRightAnswer() const;
    
protected:
    
    int BindParam(sqlite3_stmt* stmt,int col,int value) const;
    
    int BindParam(sqlite3_stmt* stmt,int col,const char* value) const;
    
    int BindParam(sqlite3_stmt* stmt,int col,float value) const;
    
    //绑定属性,sql中使用
    virtual   void bindItem(sqlite3_stmt * stmt) const;
	
    friend class CMDBHelper;

};

class TQuestion
{
    
public:
    TQuestion& operator=(const TQuestion& right);
    
    TQuestion(const TQuestion& right);

    TQuestion();
    ~TQuestion();
    
protected:
    virtual TQuestion& operator=(const TiXmlElement* right);
    
private:
    TQuestionItem item;
    CMList<TOption>* m_lisOption;
        
    friend class CMExam;
    friend class CMExercise;
    friend class CMQuestionhandler;
    friend class CMWrongQuestion;
    friend class CMDBHelper;
};


class CMQuestionhandler : public CMHandler<TQuestion>
{
  public:

	CMQuestionhandler();

    virtual ~CMQuestionhandler();

    void SetListener(IMUpdateDataListener* pListener,IMSimpleResultListener* pSimpleResultListener);

	//当前选择题可选项数
    int GetItemOptionCount();

	//得到当前选择题第nIndex个选项
    BOOL GetItemOption(int nIndex, TOption& option);

	//设置当前题目的答案（问答题），nIndex忽略
    void SetAnswer(const char* answer);

	//设置当前选择题第nIndex个选项的答案
    void SetAnswer(int nIndex, BOOL checked);

    int GetCurIndex();
    
    //设置当前第几题
    void SetCurIndex(int nIndex);

    BOOL GetCurItem(TQuestionItem& item);
    
    BOOL GetQuestionItem(int nIndex, TQuestionItem& item);

    BOOL Prev();

    BOOL Next();

	BOOL isFirst();
	
	BOOL isLast();

	//保存当前题目状态，目前只保存当前题目位置
    BOOL SaveStatus();
    
    //是否显示答案(根据是否选择了选项)
    void SetExerciseAnswer(BOOL checked);
    
    //显示答案(点击查看按钮显示)
    void SetIsChecked(BOOL checked);

    //已做几题
    int GetDoneCount();
    
    //该题是否已做
    BOOL IsQuestionComplete(int nIndex);
    
    //获取正确数
	int GetRightCount(const char* questionID);
    
 	// 练习是否已经提交
    BOOL isExciseCommit();

    //设置当前题目做对了
    void setRight();

  protected:

    void GetQuestion(int nServiceNo, const char* sID, BOOL isView);

    void GetQuestionStart(int nServiceNo, const char* sID, const char* sDst);

    void Commit(int sServiceNo, const char* sParam);
    
    virtual int DoGetRightCount(const char* questionID);

    // 提交答案前设置一个答案item，返回TRUE表示设置成功，返回FALSE表示这个item不提交
    virtual BOOL SetAnswerItem(TQuestion* itemoption, TiXmlElement* pItem);

	//保存状态，可重载，必须调用父类的此方法
	virtual BOOL SaveItemStatus(TiXmlElement* pQuestion);

	//读取状态，可重载，必须调用父类的此方法
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
	
    //整套练习，测验id
	string mID;
    
	//获取保存状态，这里只内部调用
	virtual BOOL LoadStatus();
    
	//清除保存状态
	BOOL ClearStatus();
    
    // 正确数
    int nRightCount;
    
	void Clear();
    
    //练习是否已经提交
    BOOL isExCommit;
    
    IMSimpleResultListener *m_pSimpleResultListener;

  private:
    
    //当前题目做对了 是否已保存
    BOOL IsItemSaved();
    
	int m_nCurIndex;
    
    
};



#endif /* CMQUESTIONHANDLER_H_HEADER_INCLUDED_B18542E8 */
