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

#include <initguid.h>
#include <connmgr.h>
#include <Ws2tcpip.h>
#include <connmgr_proxy.h>
#include "cmnetwork.h"
#include "cmhttpserver.h"
#ifdef WINCE_OTHER
#include "wlan.h"
#endif
extern HWND GetSafeHwnd();



CMNetConnMgr::CMNetConnMgr()
{
    m_mType = NONE;
    m_nStatus = 0;
    m_pProxy = NULL;
    m_hConn = NULL;
    
    WSADATA  data;
    if (WSAStartup(MAKEWORD(2, 0), &data) != 0)
    {
        CM_ERR("Network init failed!");
    }
}

CMNetConnMgr::~CMNetConnMgr()
{
    Release();

    WSACleanup();
}

//建立网络接入连接，默认为NULL，系统选择
BOOL CMNetConnMgr::Establish(CMNetConnMgr::TYPE type)
{
    m_nCount = 0;

#ifdef WINCE_OTHER
	RASCONN ras;        
    ras.dwSize = sizeof(RASCONN);   
    DWORD dSize,dNumber,dCount=0L;     
    dSize = sizeof(ras);    
	CM_LOGP(CM_LOGL_INFO, "CMNetConnMgr::Establish");
	BOOL bConnect = FALSE;
    if(::RasEnumConnections(&ras, &dSize, &dNumber) == 0 )   //如果函数成功，则返回0   
    {   
		CM_LOGP(CM_LOGL_INFO, "dNumber: %d",dNumber);
        if(dNumber>0)   
        {   
			CMString str = ras.szEntryName;//usb
			CM_LOGP(CM_LOGL_INFO, "name: %s",(const CHAR*)str);
			str.MakeLower();
			bConnect = TRUE;
			if(str.Find(L"usb") >= 0 || str.Find(L"net") >= 0)
				m_mType = CMNET;
			else if(str.Find(L"wap") > 0) //wap
			{
				m_mType = CMWAP;
				CMString str = L"http://10.0.0.172:80";
				m_pProxy = new CMUrl(str);
				if (!m_pProxy->Parse())
				{
					CM_ERRP("wrong proxy server addr is %s", (const CHAR*)m_pProxy->Url());
					return NONE;
				}
			}
			else
				bConnect = FALSE;
		}
	}
	if(!bConnect)
	{
		WCHAR g_FirstWirelessCard[MAX_PATH];	// 第一个无线网卡
		GetFirstWirelessCard(g_FirstWirelessCard);
		if(_tcslen(g_FirstWirelessCard) > 0)
		{	
			//g_Config.WirelessQuery();
			INTF_ENTRY_EX Intf;
			DWORD dwOutFlags = 0;
			if (GetWirelessCardInfo(g_FirstWirelessCard, &Intf, &dwOutFlags))
			{
				if (IsAssociated(Intf, dwOutFlags))
				{
					CM_LOGP(CM_LOGL_INFO, "WLAN connect");
					m_mType = CMNET;
					bConnect = TRUE;
				}
			}
		}
	}
	if(bConnect)
		m_nStatus = 2;
	return bConnect;
	//if(!bConnect)
	//{
	//	RASDIALPARAMS RasDialParams;

	//	memset(&RasDialParams, 0, sizeof (RASDIALPARAMS)); 

	//	RasDialParams.dwSize  = sizeof(RASDIALPARAMS); 

	//	wcscpy(RasDialParams.szEntryName,L"CMNET");  //已建连接的名字

	//	TCHAR szLocalPhoneNumber[RAS_MaxPhoneNumber + 1] = {0}; 

	//	wsprintf(szLocalPhoneNumber,L"%s",_T("*99***1#"));

	//	wcscpy(RasDialParams.szPhoneNumber,szLocalPhoneNumber);

	//	wcscpy(RasDialParams.szCallbackNumber, _T(""));  

	//	wcscpy(RasDialParams.szUserName, _T(""));  

	//	wcscpy(RasDialParams.szPassword, _T("")); //**************** 

	//	wcscpy(RasDialParams.szDomain, _T("")); 

	//	CMScreen* pMain = CMGlobal::TheOne().GetDefaultScreen();
	//	if (!pMain)
	//		return FALSE;
	//	// Try to establish RAS connection. 
	//	DWORD hRasRet = RasDial(NULL,NULL,&RasDialParams,0xFFFFFFFF,pMain->GetSafeHwnd(),&m_hRasConn); 
	//	//DWORD hRasRet = RasDial(NULL,NULL,&RasDialParams,0x0,NULL,&m_hRasConn); 
	//	if ( hRasRet != 0) // Connection handle 
	//	{ 
	//		CM_ERR("RasDial failed");
	//		return FALSE;
	//	}
	//	m_nStatus = 1;
	//}
	//else
	//	m_nStatus = 2;
	//return TRUE;
#else
    HRESULT hr = S_OK;
//    GUID dest;
    CONNMGR_CONNECTIONINFO connInfo;

    // look up the URL and connect to the specified destination
    //hr = ConnMgrMapURL(SETTING.m_sServerUrl, &dest, NULL);//L"http://localhost:8010", &dest, NULL);
    //if (SUCCEEDED(hr)) {
        memset(&connInfo, 0, sizeof( connInfo));
        connInfo.cbSize = sizeof( connInfo );
        connInfo.bDisabled = FALSE;
        connInfo.bExclusive = FALSE;
        connInfo.hWnd = GetSafeHwnd();
        connInfo.guidDestNet = IID_DestNetInternet;
        connInfo.dwParams = CONNMGR_PARAM_GUIDDESTNET;
        connInfo.dwFlags = CONNMGR_FLAG_PROXY_HTTP | CONNMGR_FLAG_PROXY_WAP | CONNMGR_FLAG_PROXY_SOCKS4 | CONNMGR_FLAG_PROXY_SOCKS5;
        connInfo.dwPriority = CONNMGR_PRIORITY_USERINTERACTIVE;
        connInfo.uMsg = WM_USER+300;    // Message callback.
        hr = ConnMgrEstablishConnection(&connInfo, &m_hConn);

        if (!SUCCEEDED(hr)) {
            CM_ERR("ConnMgrEstablishConnection failed");

            return FALSE;
        }
        m_nStatus = 1;
        return TRUE;
    //}

#endif
    CM_ERR("ConnMgrMapURL failed");
    return FALSE;
}
HRESULT CMNetConnMgr::ProcessConnectionManagerMessage() {
#ifdef WINCE_OTHER
	m_nStatus = 2;
	return S_OK;
#endif
  HRESULT hr = S_OK;
  DWORD status = 0;

  // Connection Manager status change
  hr = ConnMgrConnectionStatus( m_hConn, &status);

  if (SUCCEEDED(hr)) {
      switch (status) {
      case CONNMGR_STATUS_CONNECTED:
          // Do something useful here…
          {
              PROXY_CONFIG pc = {0};
              hr = ConnMgrProviderMessage(m_hConn, &IID_ConnPrv_IProxyExtension, NULL, 0, 0, (PBYTE)&pc, sizeof(pc));
              if (hr == S_OK)
              {
                  CMString sTmp(pc.szProxyServer);
                  CM_LOGP(CM_LOGL_INFO, "network is cmwap, proxyServer is %s",(const CHAR*)sTmp);
                  m_mType = CMWAP;
				  m_pProxy = new CMUrl(sTmp);
                  if (!m_pProxy->Parse())
                  {
                      CM_ERRP("wrong proxy server addr is %s", (const CHAR*)m_pProxy->Url());
                      return NONE;
                  }

              }
              else if (hr == E_NOINTERFACE)
              {
                  CM_LOG(CM_LOGL_INFO, "network is cmnet");
                  m_mType = CMNET;
              }

              if (m_mType == CMWAP)
              {
                  //触发下,用于flash跨网关
				  CMHttpS::Instance();
              }

              m_nStatus = 2;


              break;
          }
      case CONNMGR_STATUS_NOPATHTODESTINATION:
      case CONNMGR_STATUS_CONNECTIONFAILED:
      case CONNMGR_STATUS_CONNECTIONCANCELED:
      case CONNMGR_STATUS_CONNECTIONLINKFAILED:
      case CONNMGR_STATUS_CONNECTIONDISABLED:
      case CONNMGR_STATUS_AUTHENTICATIONFAILED:
          // Non transient error state.
          ConnMgrReleaseConnection(m_hConn, 1);
          m_hConn = NULL;
          m_nStatus = 0;
      default:
          // These states will eventually end up at as connected 
          // or not. Just ignore for now.
          CM_ERRP("ConnMgrConnectionStatus failed %d", status);          
          break;
      }
  }

  return hr;
}

//释放网络接入连接
void CMNetConnMgr::Release()
{
    if (m_hConn)
    {
        ConnMgrReleaseConnection(m_hConn, TRUE);
        m_hConn = NULL;
    }
    if (m_pProxy)
    {
        delete m_pProxy;
        m_pProxy = NULL;
    }
    m_nStatus = 0;
    m_mType = NONE;
    m_nCount = 0;
}

CMNetConnMgr::TYPE CMNetConnMgr::CurrentType() 
{
    if (m_nStatus == 0)
    {
        if (!Establish())
		{
            CM_ERR("Establish failed");
            return NONE;
        }

    }
    else if (m_nStatus == 1)
    {
        //正在连接中，仍然返回None
        if (m_nCount++ > 5)
        {
            //重试次数
            Release();
        }
        CM_LOGP(CM_LOGL_WARNING, "CurrentType connectiong tryed %d times", m_nCount);
        return NONE;
    }
    else if ( m_nStatus == 2)
	{
        //还是要检测下连接有效性
		DWORD nStatus;
		HRESULT hr = ConnMgrConnectionStatus(m_hConn,&nStatus);
		//CM_ERRP("CMNetConnMgr::GetConnectionStatus() %d", nStatus);
		if(FAILED(hr) || nStatus != CONNMGR_STATUS_CONNECTED)
        {
			Release();
            return CurrentType();
        }
	}

    return m_mType;



//#if defined(SIMULATION)
//    if (m_nStatus == 0)
//    {
//        m_mType = CMNET;
//        m_nStatus = 2;
//
//        ////触发下
//        //CMGlobal::TheOne().HttpServer();
//    }
//    return m_mType;
//#endif
//
//    //做类型检查
//    if (m_hConn == NULL || m_nStatus == 0)
//    {
//        if (!Establish() || m_hConn == NULL || m_nStatus == 0)
//        {
//            CM_ERR("Establish failed");
//            return NONE;
//        }
//    }
//
//    DWORD nStatus = 0;
//    ConnMgrConnectionStatus(m_hConn, &nStatus);
//    
//    if (nStatus == CONNMGR_STATUS_CONNECTED)
//    {
//        //状态由连接中变成已连接
//        if (m_nStatus == 1)
//        {
//            PROXY_CONFIG pc = {0};
//
//            if (m_mType == NONE)
//            {
//                HRESULT iRet = ConnMgrProviderMessage(m_hConn, &IID_ConnPrv_IProxyExtension, NULL, 0, 0, (PBYTE)&pc, sizeof(pc));
//                if (iRet == S_OK)
//                {
//                    CMString sTmp(pc.szProxyServer);
//                    CM_LOGP(CM_LOGL_INFO, "network is cmwap, proxyServer is %s",(const CHAR*)sTmp);
//                    m_mType = CMWAP;
//                    m_pProxy = new CMUrl(sTmp);
//                    if (!m_pProxy->Parse())
//                    {
//                        CM_ERRP("wrong proxy server addr is %s", (const CHAR*)m_pProxy->Url());
//                        return NONE;
//                    }
//                    //触发下
//                    CMGlobal::TheOne().HttpServer();
//                }
//                else if (iRet == E_NOINTERFACE)
//                {
//                    CM_LOG(CM_LOGL_INFO, "network is cmnet");
//                    m_mType = CMNET;
//                }
//            }
//            m_nStatus = 2;
//
//        }
//        return m_mType;
//    }
//    else
//    {
//        if (m_nStatus == 2)
//        {
//            //连接已中断，释放连接
//            CM_ERR("CMNetConnMgr connect interupt");
//            Release();
//
//            if (!Establish())
//            {
//                CM_ERR("ReEstablish failed");
//            }
//        }
//    }
//
//    return NONE;
}

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

    int iRet = ::getaddrinfo((const CHAR*)(CMString)sName, szPort, &hints, &res);
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
    
    return  sValue;
}

INT32 CMNetConnMgr::GetConfig()
{
    if (m_nIapId == -1)
        return INT32(NONE);
    return m_nIapId;
}

BOOL CMNetConnMgr::EnumAccessPoint(CMMap<UINT32, CMString>& m_apList)
{
    m_apList.clear();

    m_apList.insert((UINT32)CMWAP, L"CMWAP");
    m_apList.insert((UINT32)CMNET, L"CMNET");
    return TRUE;
}

