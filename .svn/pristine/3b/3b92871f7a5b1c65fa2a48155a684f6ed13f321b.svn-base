//
//  cmfileinfo.h
//  MLPlayer
//
//  Created by wmgwd on 13-11-11.
//  Copyright (c) 2013年 w. All rights reserved.
//

#ifndef __MLPlayer__cmfileinfo__
#define __MLPlayer__cmfileinfo__


#include "cmcommon.h"
#include <string>
#include "cmsession.h"
#include  "cmlist.h"
using namespace std;

class CMFileInfo
{
public:
    CMFileInfo(const CMFileInfo& right);

    CMFileInfo();

    CMFileInfo& operator=(const CMFileInfo& right);

    virtual ~CMFileInfo();
    
    void SetListener(IMSimpleResultListener* pListener);
    

    void SetUserData(void* UserData);

    /**
     *  建立新群
     *
     *  @param name     群名
     *  @param desc     群简介
     *  @param iconPath 群图片路径（可为空）
     *  @param flag     0为不可加入 1为不需要验证 2为需要验证
     */
    void CreateNewRoom(const char* name,const char* desc,const char* iconPath,int flag);

    //提问
    BOOL AskQuestion(const char* sCategoryID, int nAnonymous, int nValue, const char* sQuestion,const char* filename, const char* expertsID);
    
    //回答问题
    BOOL AnswerQuestion(const char* sQuestionID, int nAnonymous, const char* sAnswer,const char* filename);
    
    BOOL UploadImage(const char* filename,int cmdID);
    //上传头像
    BOOL UpheadPhoto(const char* filename);
    //上传消息图片
    BOOL UpLoadMessageWithPicture(const char* filename);

    //上传消息图片
	BOOL UpLoadMessageWithPicture(const char* filename,const char* msgId);

    //上传群头像
    BOOL UpLoadGroupHeader(const char* roomid , const char* filename);

    BOOL operator==(const CMFileInfo& right);

protected:

private:
    friend class CMFileUpload;
    
    IMSimpleResultListener* m_pSimpleListener;

    void* m_pUserData;
    
    void OnSimpleResultFinish(int Result);

    CMList<FormData> m_list;

    string m_sParm;

    int  m_nCmdID;
    
    string sMsgCode;

//    CMSession* m_pSession;
    

};

#endif /* defined(__MLPlayer__cmfileinfo__) */
