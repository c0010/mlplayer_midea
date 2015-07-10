//
//  cmquestionupload.h
//  MLPlayer
//
//  Created by whf on 13-8-6.
//  Copyright (c) 2013年 w. All rights reserved.
//

#ifndef __MLPlayer__cmquestionupload__
#define __MLPlayer__cmquestionupload__


#include "cmcommon.h"
#include "cmhandler.h"
#include "cmqalist.h"
#include "cmsession.h"


class  CMQuestionUpload:public
IMNotifySession
{
    
    
public:
    static CMQuestionUpload * GetInstance();
    
    virtual ~CMQuestionUpload();
    
    void SetListener(IMSimpleResultListener* pListener);
    
    void SetUserData(void* UserData);
    
    //数据操作
    
    BOOL AskQuestion(const char* sCategoryID, int nAnonymous, int nValue, const char* sQuestion,const char* filename);
    
    BOOL AnswerQuestion(const char* sQuestionID, int nAnonymous, const char* sAnswer,const char* filename);
    //上传头像
    BOOL UpheadPhtho(const char* filename);

protected:

    CMQuestionUpload();
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

    
private:
    static CMQuestionUpload *m_pTHIS;
	CMSession* m_pSession;
    

    IMSimpleResultListener* m_pSimpleListener;
    void* UserData;

    
};




#endif /* defined(__MLPlayer__cmquestionupload__) */





