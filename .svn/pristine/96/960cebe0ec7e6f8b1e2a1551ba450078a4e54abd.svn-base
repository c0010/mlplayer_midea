// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMEXERCISE_H_HEADER_INCLUDED_B1853B57
#define CMEXERCISE_H_HEADER_INCLUDED_B1853B57

#include "cmwrongquestion.h"

class CMExercise : public CMWrongQuestion
{
  public:
    CMExercise();

    virtual ~CMExercise();

    void SetListener(IMUpdateDataListener* pListener,IMSimpleResultListener* pSimpleResultListener);

    //获取练习题目
    void GetExerciseQuestion(const char* sID);
    
    //网络异常时从本地数据库读取
    BOOL LoadFromDB();
    
    //获取做对的练习数目
    int GetRightCountExcise(const char* questionID);
    
    //获取错题count
    int GetWrongCountExcise(const char* questionID);
    
    //练习参与人数
    void SetCompleteNumber(int nNum);
    
  protected:
    
    //重载父类方法获取练习正确数
    virtual int DoGetRightCount(const char* questionID);
    //缓存建表
    virtual BOOL DoCreate(sqlite3* db) ;
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TQuestion& item) ;
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(TQuestion& obj) ;
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(const TQuestion& obj);
    
    virtual void DoClear();
    
    virtual void DoCommit();
    
    //更新选项
    BOOL DoUpdateOption(sqlite3* db,const TOption& obj);
    
    //刷新选项
    BOOL DoRefreshOption(sqlite3* db, TOption& obj);
    
    //从数据读到内存中
    BOOL DoGetOptionCacheItems(sqlite3* db, TQuestion& item);
    
    //保存进数据库
    BOOL SaveQuestion(sqlite3* db,TQuestionItem& questionitem);
    
    BOOL SaveOption(sqlite3* db,TOption& option);
    
    //更新错题库
    BOOL DoUpdateWrongs(const TQuestion& obj);
    
    BOOL DoGetWrongItems(sqlite3* db);
    
    BOOL DoGetWrongOptionItems(sqlite3* db, TQuestion& item);
    
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    virtual BOOL SetAnswerItem(TQuestion* itemoption,TiXmlElement* pItem);
    
    //保存练习当前状态
    virtual BOOL DoSaveExerciseStatus();
    
    //保存错题当前状态
    virtual BOOL DoSaveWrongStatus();
    
    //进入练习时，先加载本地读取上次做题进度状态
    virtual BOOL LoadStatus();
    
    //刷新练习列表(更新 正确数目 已答数目 本地练习状态等)
    BOOL  UpDateList();
    
    //获取列表缓存练习题总数
    int GetExerciseCount(const char* sID);

    //更新错题库数目(最外层练习列表nWrongCount)
    BOOL UpDateExerciseListWrongCount();
    
    //练习重做时,清除本地 内存中答案记录
    virtual BOOL DoClearAnswer(TQuestion& obj);
    
    BOOL DoClearOptionAnswer(sqlite3* db, TOption& obj);
    
    //刷新错题库当前题目的最新一次最题时间(错题排序时用到,按时间先后降序排列)
    virtual BOOL DoLastUpdate(int lasttime);
    
    //获取错题
    virtual void DoGetWrongQuestion(const char* sID);
    
    //检查改练习是否已经存在
    //FIXME 返回参数改为整数，用来判断是否应该刷新
    int CheckExerciseIsExit(const char* sID);


  private:

    char m_SubTablename[64];
    
    //练习参与人数
    int  m_nCompleteNumber;
    
    friend class CMDBHelper;

};



#endif /* CMEXERCISE_H_HEADER_INCLUDED_B1853B57 */
