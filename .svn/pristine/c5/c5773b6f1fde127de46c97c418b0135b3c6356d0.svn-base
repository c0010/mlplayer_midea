#include "stdafx.h"
#include "cmnetwork.h"
#import "Reachability.h"


CMNetConnMgr::TYPE CMNetConnMgr::CurrentType() 
{
    //监测有无网络
    Reachability *reach = [Reachability reachabilityForInternetConnection];
    
    switch ([reach currentReachabilityStatus])
    {
        case NotReachable:
        return NONE;

        default:
            break;
    }

	CFDictionaryRef dicRef = CFNetworkCopySystemProxySettings();
	CFStringRef proxy = (CFStringRef)CFDictionaryGetValue(dicRef, kCFNetworkProxiesHTTPProxy);
//    CFStringRef port = (CFStringRef)CFDictionaryGetValue(dicRef, kCFNetworkProxiesHTTPPort);

    
    
	if(!proxy)
		m_mType = CMNET;
	else 
		m_mType = CMWAP;
	return m_mType;
}
CMNetConnMgr::CMNetConnMgr()
{
    m_mType = NONE;
    m_nStatus = 0;
    m_pProxy = NULL;
}

CMNetConnMgr::~CMNetConnMgr()
{
}

//建立网络接入连接，默认为NULL，系统选择
BOOL CMNetConnMgr::Establish(CMNetConnMgr::TYPE type)
{
    return  TRUE;
}

//释放网络接入连接
void CMNetConnMgr::Release()
{
    if (m_pProxy)
    {
        delete m_pProxy;
        m_pProxy = NULL;
    }
    m_nStatus = 0;
    m_mType = NONE;
}

CMUrl* CMNetConnMgr::Proxy()
{
    
	if (m_pProxy == NULL) {

        CFDictionaryRef dicRef = CFNetworkCopySystemProxySettings();
        CFStringRef proxy = (CFStringRef)CFDictionaryGetValue(dicRef, kCFNetworkProxiesHTTPProxy);
        CFStringRef port = (CFStringRef)CFDictionaryGetValue(dicRef, kCFNetworkProxiesHTTPPort);
        
        char temp[20];
        memset(temp , 0, 20);
        sprintf(temp, "%s:%d",[(NSString *)proxy UTF8String],[(NSString*)port intValue]);
        
        m_pProxy = new CMUrl(CMString(temp));

        m_pProxy->Parse();
        
		}
    
    return m_pProxy;
    
	
}

CMString CMNetConnMgr::HostNameToIP(const CMString& sName)
{
    return sName;
}

INT32 CMNetConnMgr::GetConfig()
{
	return INT32(NONE);
}

BOOL CMNetConnMgr::EnumAccessPoint(CMMap<UINT32, CMString>& m_apList)
{
    m_apList.clear();
	m_apList.insert((UINT32)CMWAP, L"CMWAP");
	m_apList.insert((UINT32)CMNET, L"CMNET");
    return TRUE;
}
