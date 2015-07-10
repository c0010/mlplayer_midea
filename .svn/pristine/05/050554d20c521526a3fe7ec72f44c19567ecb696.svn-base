// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMWRONGQUESTION_H_HEADER_INCLUDED_B1855149
#define CMWRONGQUESTION_H_HEADER_INCLUDED_B1855149

#include "cmquestionhandler.h"

class CMWrongQuestion : public CMQuestionhandler
{
  public:
    CMWrongQuestion();

    virtual ~CMWrongQuestion();

    void GetWrongQuestion(const char* sID);

	//当前题（仅限选择题）用户答案是否正确，问答题返回TRUE
	BOOL isOptionAnswerRight();
    
    BOOL isOptionAnswerRight(int nIndex);
    
    //（仅限查看测验）之前的答案是否正确，问答题返回TRUE
    BOOL isMyAnswerRight();

	//当前题是否在错题库
    BOOL isWrong();

	//当前题加入/移除错题库
    void SetWrong(BOOL isWrong);

	//返回当前题文本答案供显示，选择题取选择项文本的第一个字符（多选题空格隔开），判断题取选择项文本全部
    const char* GetRightAnswer();

	void Commit();
    
    //获取错题数
	int GetWrongCount(const char* questionID);
    
    //保存练习状态(子类实现)
    void SaveExerciseStatus();
    
    //保存错题状态
    void SaveWrongStatus();
    
    //清除答案，重做
    BOOL ClearAnswer();
    
    //刷新错题时间
    BOOL UpdateWrongTime(int lasttime);
    
  protected:
    
    virtual void DoCommit();
    
    virtual BOOL DoSaveExerciseStatus();
    
    virtual BOOL DoSaveWrongStatus();
    
    virtual BOOL SetAnswerItem(TQuestion* itemoption, TiXmlElement* pItem);
    
    virtual BOOL DoLastUpdate(int lasttime);
    
    virtual BOOL DoClearAnswer(TQuestion& obj);
    
    virtual void DoGetWrongQuestion(const char* sID);

	string m_sRightAnswer;
    
    //错题数
    int m_nWrongs;
    
    //该错题最新做题时间
    int sLastUpdate;

};



#endif /* CMWRONGQUESTION_H_HEADER_INCLUDED_B1855149 */
