//
//  cmundone.h
//  MLPlayer
//
//  Created by hushengwu on 14/11/17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#ifndef __MLPlayer__cmundone__
#define __MLPlayer__cmundone__

#include <stdio.h>
#include "cmcommon.h"
#include "cmhandler.h"
#include <string>
using namespace std;

template <typename T> class CMList;


class TUnDoneItem
{
public:
    string sType;
    
    int   nItemCount;
    
    TUnDoneItem();

    ~TUnDoneItem();

};


class CMUnDone : public CMHandler<TUnDoneItem>
{
public:
    
    static CMUnDone* GetInstance();
    
    ~CMUnDone();
    
    //获取请求
    BOOL  GetUnDone();
    
    void SetListener(IMUpdateDataListener* pListener);

    
protected:
    
    CMUnDone();
    
    //缓存建表
    virtual BOOL DoCreate(sqlite3* db) ;
    //网络回来数据，要入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TUnDoneItem& item) ;
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db) ;
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(TUnDoneItem& obj);
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(const TUnDoneItem& obj) ;
    //清除内存以及缓存里的相关数据
    virtual void DoClear();

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
private:
    
    static CMUnDone* m_pTHIS;
    
    IMUpdateDataListener *m_pSimpleListener;
    
};

#endif /* defined(__MLPlayer__cmundone__) */
