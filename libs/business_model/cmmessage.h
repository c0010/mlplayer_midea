//
//  cmmessage.h
//  MLPlayer
//
//  Created by wdwp on 15-03-13.
//  Copyright (c) 2015年 w. All rights reserved.
//

#ifndef __MLPlayer__cmmessage__
#define __MLPlayer__cmmessage__


#include "cmcommon.h"
#include <string>
#include "cmsession.h"

class CMMessage : public IMNotifySession
{
public:

    CMMessage();

    ~CMMessage();

    void SetListener(IMSimpleResultListener* pListener);

    void SetUserData(void* userdata);

    //上传后图片地址
    string sUrl;

    //上传后缩略图片地址
    string sThumbUrl;

    //上传消息图片
    BOOL UploadPic(const char* filename);

protected:


private:

    virtual CMMessage& operator=(const TiXmlElement* right);

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

    IMSimpleResultListener* m_pSimpleListener;

    void* m_pUserData;

    string m_sParm;

    CMSession *m_pSession;

};

#endif /* defined(__MLPlayer__cmfileinfo__) */
