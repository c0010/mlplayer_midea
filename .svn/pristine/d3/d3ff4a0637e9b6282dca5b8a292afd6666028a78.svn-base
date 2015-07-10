// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef __CMNETWORKMGR_H__
#define __CMNETWORKMGR_H__

#if defined(PLAT_SYMBIAN)
#include "cmconnectionnotifier.h"
#endif
#include "cmstring.h"
#include "cmhttpc.h"
#include "cmmap.h"
#include "cmmutex.h"

//网络接入管理
//接入网络耗时差值很大，做同步会阻塞用户响应。采用异步。同时由于接入只做一次，因此不提供回调接口，采用CurrentType检查
//拨号次序：
//1、有配置文件取配置文件里的拨号方式
//2、mobile取系统"Internet 连接"的拨号方式、symbian弹出选择窗口用户选择
//3、如采用配置文件方式必须提供界面修改拨号方式
class CMNetConnMgr
#if defined(PLAT_SYMBIAN)
    : public CActive,IMConnectionObserver
#endif
{
public:
    typedef enum _TYPE {
        NONE = 0,
        CMWAP,
        CMNET,
		//       WIFI,
    } TYPE;
    static CMNetConnMgr& Instance();

    ~CMNetConnMgr();

    //当前的连接类型状态，NONE表示未连接。所有public API，都必须调用CurrentType返回有效类型后才能正确调用成功
    TYPE CurrentType();

    //当前的连接状态，//0、未连接  1、连接中   2、已连接
    UINT32 CurrentState() {return m_nStatus;};

    //dns解析名称到ip地址
    CMString HostNameToIP(const CMString& sName);

    //获取wap连接方式的proxy
    CMUrl* Proxy();

    //释放网络接入连接，恢复错误
    void Release();

    //输入空的apList ， 返回接入点列表，带有ID和用户理解描述
    BOOL EnumAccessPoint(CMMap<UINT32, CMString>& apList);
#if defined(PLAT_SYMBIAN)
    BOOL IsWifi(); 

    RSocketServ& SocketServer() {return m_cSockServ;};
    RConnection& Connection() {return m_cConn;};
    BOOL LinkLayerOpen();
#elif defined(PLAT_WINCE)
    HRESULT ProcessConnectionManagerMessage();
#endif
	void SetConfig(INT32 nIapId){m_nIapId = nIapId;};
private:
    CMNetConnMgr();

    //建立网络接入连接，默认为NONE，根据策略选择。TRUE也不表示连接已经成功建立，使用CurrentType 进行检查
    BOOL Establish(TYPE type = NONE);

    //获取连接设置，返回值在2个平台含义不同
    //mobile平台是连接类型
    //symbian是接入点
    INT32 GetConfig();

	INT32 m_nIapId;

    //连接类型
    TYPE     m_mType;

    //连接状态
    UINT32   m_nStatus;       //0、未连接  1、连接中   2、已连接
    INT32    m_nCount;        //连接当前重试次数

    //当连接类型为wap时，此值有效
    CMUrl*    m_pProxy;

    //dns cache
    CMMap<CMString, CMString>  m_dnsCache;
    CMMutex                    m_dnsMutex;

    friend class CMGlobal;

#if defined(PLAT_SYMBIAN)
    RConnection    m_cConn;
    RSocketServ    m_cSockServ;
    RHostResolver  m_cHostRsv;
    BOOL           m_bWifi;
    BOOL           m_bManualCancel;
    CMConnectionNotifier* m_pConnectionNotifier; 

    void IAPType(UINT32 iapid);
protected:
    //默认返回cmnet连接
    UINT32       GetSapID(TYPE type);
    virtual void DoCancel();
    virtual void RunL();
	virtual void OnConnectionNotifier( TInt aStage, TInt aError);
	virtual void OnConnectionClose();
#elif defined(PLAT_WINCE)
    HANDLE         m_hConn;
#endif
};

#endif /* __CMNETWORKMGR_H__ */

