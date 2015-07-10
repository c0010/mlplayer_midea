//
//  cmupload.h
//  MLPlayer
//
//  Created by wmgwd on 13-11-11.
//  Copyright (c) 2013年 w. All rights reserved.
//

#ifndef __MLPlayer__cmupload__
#define __MLPlayer__cmupload__


#include "cmfileinfo.h"
#include "cmhandler.h"
#include <string>

template <typename T> class CMList;

class CMFileUpload : public CMHandler<CMFileInfo>
{
public:
    static CMFileUpload* GetInstance();
    
    virtual ~CMFileUpload();
    
    void SetListener(IMSimpleResultListener* pListener);
    
    void SetUserData(void* userData);
    
    //加入队列 -1为失败 否则返回列表中当前正在上传文件的index
    int Append(const CMFileInfo& file);
    
    //从队列删除
    void Delete(int nIndex);
    
    //开始上传
    BOOL Start(int nIndex);
    
    //暂停上传 保留接口
    void Stop();
    
    //图片消息原图地址



    string url;
    //图片消息缩略图地址
    string thumb_url;

    //msgCode
    string sMsgCode;

protected:
    
    CMFileUpload();
    
    //缓存建表
    virtual BOOL DoCreate(sqlite3* db);
    
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, CMFileInfo& item);
    
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(CMFileInfo& obj);
    
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(const CMFileInfo& obj);
    
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
private:
    static CMFileUpload* m_pTHIS;
    
    IMSimpleResultListener* m_pSimpleListener;
    
    //CMSession* m_pSession;
    

    BOOL m_bUploaded;
    
    UINT32 m_nCurrIndex;
};

#endif /* defined(__MLPlayer__cmupload__) */
