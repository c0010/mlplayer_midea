// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

//当前模块是网络模块
#define FILE_MOD CM_LOGM_NET


#include "stdafx.h"
#include "cmnetworkmgr.h"

#include <jni.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <curl/curl.h>

#include "android/env.h"

CMNetConnMgr::CMNetConnMgr()
{
	m_pProxy = NULL;
	m_nStatus = 0;
	curl_global_init(CURL_GLOBAL_ALL);
}

CMNetConnMgr::~CMNetConnMgr()
{
	curl_global_cleanup();
	SAFEDELETE(m_pProxy);
}

//当前的连接类型状态，NONE表示未连接。所有public API，都必须调用CurrentType返回有效类型后才能正确调用成功
CMNetConnMgr::TYPE CMNetConnMgr::CurrentType()
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("GetEnv failed");
		return NONE;
	}

	jmethodID method = env->GetStaticMethodID(GetGlobalCls(), "getInstance", "()Lcom/wunding/mlplayer/CMGlobal;");
	if(!method)
		return NONE;
	jobject obj = (jobject)env->CallStaticObjectMethod(GetGlobalCls(), method);
	if(!obj)
		return NONE;

	method = env->GetMethodID(GetGlobalCls(), "CurrentType", "()I");
	if(!method)
	{
		CM_ERR("GetActiveConnection jni failed");
		return NONE;
	}

	int ret = env->CallIntMethod(obj, method);
	CM_LOGP(CM_LOGL_DEBUG, "GetActiveConnection return %d", ret);
	return (TYPE)ret;
}

//dns解析名称到ip地址
CMString CMNetConnMgr::HostNameToIP(const CMString& sName)
{
    m_dnsMutex.Lock();
    if (m_dnsCache.contains(sName))
    {
        CMString sValue = m_dnsCache.value(sName);
        m_dnsMutex.UnLock();
        return sValue;
    }
    m_dnsMutex.UnLock();
    
    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags    = AI_CANONNAME;
    hints.ai_family  = AF_INET;      // only support IPv4
    hints.ai_socktype = SOCK_STREAM;  // only support TCP
    hints.ai_protocol = IPPROTO_TCP;  // TCP protocol

    char szPort[10] = {"80"};

    int iRet = getaddrinfo((const CHAR*)(CMString)sName, szPort, &hints, &res);
    if( iRet != 0 )
    {
        CM_ERRP("getaddrinfo failed, errno %d", iRet);
        return CMString();
    }

    CMString sValue(inet_ntoa(((sockaddr_in*)(res->ai_addr))->sin_addr));
    freeaddrinfo(res);
    m_dnsMutex.Lock();
    m_dnsCache.insert(sName, sValue);
    m_dnsMutex.UnLock();

    return sValue;
}

//释放网络接入连接，恢复错误
void CMNetConnMgr::Release()
{

}

//输入空的apList ， 返回接入点列表，带有ID和用户理解描述
BOOL CMNetConnMgr::EnumAccessPoint(CMMap<UINT32, CMString>& apList)
{
	return TRUE;
}

INT32 CMNetConnMgr::GetConfig()
{
    if (m_nIapId == -1)
        return INT32(NONE);
    return m_nIapId;
}

CMUrl* CMNetConnMgr::Proxy()
{
	if (m_pProxy == NULL) {
		JNIEnv*  env ;
		if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		{
			CM_ERR("GetEnv failed");
			return NULL;
		}

		jmethodID method = env->GetStaticMethodID(GetGlobalCls(), "CurrentProxy", "()Ljava/lang/String;");
		if(!method)
			return NULL;
		jstring obj = (jstring)env->CallStaticObjectMethod(GetGlobalCls(), method);
		if (obj != NULL) {
			const char* str = env->GetStringUTFChars(obj, NULL);
			m_pProxy = new CMUrl(CMString(str));
			m_pProxy->Parse();
			env->ReleaseStringUTFChars(obj, str);
		}
		else return NULL;

	}
	return m_pProxy;
}
