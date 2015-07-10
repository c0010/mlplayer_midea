// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
//
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMHANDLER_H_HEADER_INCLUDED_B249C5C7
#define CMHANDLER_H_HEADER_INCLUDED_B249C5C7

#include "cmcommon.h"
#include "cmdbhelper.h"
#include "cmmutex.h"
#include <string>


template <typename T> class CMList;
using namespace std;

//获取数据业务逻辑基类，实现翻页/缓存/通用操作等功能
//1、当T为指针时，DoClear、DoGetItem需要继承实现自己，析构函数需要实现自己的数据清理。OnSessionCmd调用DoPutItem的地方也有不同。具体参见CMContentHandler
//2、当T为类时，成员变量都为为简单类型，可以不用实现拷贝构造和赋值构造函数。成员有类等复杂类型，必须实现拷贝构造和赋值构造函数。
//   拷贝构造函数是CMList构造对象时需要。赋值构造函数时GetItem时需要
//3、重载实现OnSessionCmd时，要么调用父类的OnSessionCmd；要么需要参见CMHandler实现，m_nRequestType赋值，成功时UpdateCacheTime
template <typename T>
class CMHandler : public IMNotifySession {
public:
	//设置异步通知接口
    CMHandler();
    //析构函数里清除内存里的数据。一般不动缓存里的相关数据
    virtual ~CMHandler();

    void SetUserData(void* UserData);
    
    //获取对象数量
    int GetItemCount();
    
    //获取对象，返回的T应该是内部对象的拷贝
    BOOL GetItem(int nIndex, T& item);
    
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    BOOL Refresh(T& obj);

    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    BOOL Update(const T& obj);

    //还有更多对象
	BOOL IsEnd();
	
    //异步通知，获取更多对象列表.只有在SetPaging(TRUE)时有效，需要IsEnd返回FALSE
    BOOL RequestMore();

	//当前正在请求
	BOOL IsRunning();
    
	BOOL IsRefresh();

	//取消请求
	void Cancel();
    
    //设置m_nRequestType值，一次有效，并不会修改默认值。0 表示不用缓存   1 表示在未超时的时候用缓存
	//virtual only for ios bug
    virtual void SetRequestType(int nType);


protected:
    //绑定参数
    static int BindParam(sqlite3_stmt* stmt,int col,int value);
    static int BindParam(sqlite3_stmt* stmt,int col,const char* value);
    static int BindParam(sqlite3_stmt* stmt,int col,float value);

   	//统一错误处理
	static int ResultHandle(unsigned int nResult);

    void SetPaging(BOOL bPaging);

   	//异步通知，成功异步请求返回成功，只供子类调用
    BOOL Request(int nServiceNo, const char* sParam);

    sqlite3* CheckTable(const char* table);
    sqlite3* CheckTable();
    
    //检查root数据库
    sqlite3* CheckRootTable();


    //清除内存以及缓存里的相关数据
    void Clear();

    //用于封装DoGetCacheItems
    BOOL GetCacheItems(sqlite3* db);

    //缓存建表
    virtual BOOL DoCreate(sqlite3* db);
    //网络回来数据，要加入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, T& item);
    //缓存回来数据，读取缓存到对象列表
    virtual BOOL DoGetCacheItems(sqlite3* db);
    //从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
    virtual BOOL DoRefresh(T& obj);
    //更新缓存，一般先GetItem或者Refresh后，修改，再Update
    virtual BOOL DoUpdate(T const & obj);
    //GetItem的可扩展实现
    virtual BOOL DoGetItem(int nIndex, T& item);
    //清除内存以及缓存里的相关数据
    virtual void DoClear();

    //设置m_nRequestDuration值 单位秒
    void SetCacheDuration(unsigned int nTime);
    
    //更新缓存的时间
    BOOL UpdateCacheTime(time_t time);

    //使用当前时间更新缓存时间
    BOOL UpdateCacheTime();

    //获取缓存的时间，0 表示未有缓存时间
    time_t GetCacheTime();

    //获取当前时间。一般用于河缓存时间比较或者更新缓存时间
    time_t GetCurrentTime();

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	void* m_UserData;
	
	CMSession* m_pSession;
    
	IMUpdateDataListener *m_pListener;

    char  m_tablename[64];

    CMList<T>* m_lstItem;

    CMMutex    m_mutex;

    BOOL m_bPaging;
    
    BOOL m_bRefresh;

	//为分页使用
	int m_nPageNo;       //当前页，初始为1
	int m_nPageSize;     //每页对象数
    int m_nTotalCount;   //返回总数
    BOOL  m_bEnd;         //是否最后页

    int  m_nServiceNo;
    
    //请求类型
    //0正常请求
    //1先读取数据库 超过m_nRequestDuration指定时间间隔后 重新请求
    int m_nRequestType;//0不启用  1启用缓存
    
    //默认的请求类型
    int m_nDefRequestType;//0不启用  1启用缓存

    //上次的请求类型
    int m_nLastRequestType;

    //专为m_nRequestType使用，单位秒
    int m_nCacheDuration;

    // cache字段
    string m_sCache;

private:

    BOOL CurrentRequest(const char* param,int pageno,int pagesize);

    BOOL DoOffline();

	char m_sParam[1800];

    BOOL CommonRequest(int nServiceNo, const char* sParam);

};

#include "cmhandler.inl"

#endif
