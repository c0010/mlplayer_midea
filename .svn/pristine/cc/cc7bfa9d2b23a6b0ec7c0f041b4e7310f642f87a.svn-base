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

#include <in_sock.h>
#include <arpa/INET.H>
#include <COMMDB.H>
#include <CommDbConnPref.h>
#include "cmstring.h"

//part code from http://blog.csdn.net/alex_hua/archive/2008/09/03/2870072.aspx
CMNetConnMgr::CMNetConnMgr() : CActive(EPriorityStandard)
{
	m_nIapId = -1;
    m_mType = NONE;
    m_nStatus = 0;
    m_pProxy = NULL;
    m_bWifi = FALSE;
    m_bManualCancel = FALSE;
    m_pConnectionNotifier = NULL;
    CActiveScheduler::Add(this);
}

CMNetConnMgr::~CMNetConnMgr()
{
	SAFEDELETE(m_pConnectionNotifier);
    this->Release();
}

//建立网络接入连接，默认为NULL，系统选择
BOOL CMNetConnMgr::Establish(CMNetConnMgr::TYPE type)
{
    if (m_nStatus == 0) 
    {
        TCommDbConnPref pref;
        pref.SetBearerSet(ECommDbBearerGPRS | ECommDbBearerWLAN | ECommDbBearerLAN);
        pref.SetDirection(ECommDbConnectionDirectionOutgoing);
        
        INT32 nSapID = 0;
        if (type == NONE)
        {
            //未设置，从配置文件获取
            nSapID = GetConfig();
            if (nSapID == -1)
            {
                //配置错误，默认CMWAP
                CM_LOG(CM_LOGL_WARNING, "config sapid -1");
                type = CMWAP;
            }
        }
        IAPType(nSapID);
		switch (type)
		{
		case CMWAP:
		case CMNET:
			nSapID = GetSapID(type);
			CM_ERRP("CMNetConnMgr::Establish:nSapID = GetSapID(type):%d-------------",nSapID);
		case NONE:
			pref.SetIapId(nSapID);
//            {
//                //设置NetID
//                CCommsDatabase* commDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
//                CleanupStack::PushL(commDb); 
//                CCommsDbTableView* commView = commDb->OpenViewMatchingUintLC(TPtrC(IAP), TPtrC(COMMDB_ID), nSapID);
//                if (commView->GotoFirstRecord() == KErrNone)
//                {
//                    UINT32 nNetID = 0;
//                    commView->ReadUintL(TPtrC(IAP_NETWORK), nNetID);
//                    pref.SetNetId(nNetID);
//                    CM_ERRP("----------CMNetConnMgr::Establish--nNetID:%d",nNetID);
//                }
//                CM_ERR("----------CMNetConnMgr::Establish none");
//                CleanupStack::PopAndDestroy(2);                  
//            }  
			
			pref.SetDialogPreference(ECommDbDialogPrefDoNotPrompt); //联网时不出现对话框
			break;
		default:
			CM_ERR("type unknown");
			ASSERT(FALSE);
//            pref.SetDialogPreference(ECommDbDialogPrefPrompt); //弹出用户选择
		}        
        INT32 nRet = m_cSockServ.Connect();
        ASSERT(nRet == KErrNone);
        nRet = m_cConn.Open(m_cSockServ);   
        ASSERT(nRet == KErrNone);

        m_nStatus = 1;
        m_mType = type;
        m_bManualCancel = FALSE;
        m_nCount = 0;
        m_cConn.Start(pref, iStatus);
        SetActive();
    }
    
    return TRUE;
}

//释放网络接入连接
void CMNetConnMgr::Release()
{
    CActive::Cancel();
    
    m_cConn.Close();
    m_cSockServ.Close();    
    if (m_pProxy)
    {
        delete m_pProxy;
        m_pProxy = NULL;
    }
    m_nStatus = 0;
    m_mType = NONE;
    m_nCount = 0;
    m_bWifi = FALSE;
}

CMNetConnMgr::TYPE CMNetConnMgr::CurrentType() 
{
    //做类型检查
    if (m_nStatus == 0)
    {
        if (!Establish() || m_nStatus == 0)
        {
            CM_ERR("Establish failed");
            return NONE;
        }        
    }
    else if (m_nStatus == 1)
    {
        //正在连接中，仍然返回None
        //symbian的wifi，会弹出系统对话框，因此不做重试次数限制，由用户自行决定
        if ((!IsWifi() && m_nCount++ > 5) || m_bManualCancel)
        {
            Release();
        }

        CM_LOGP(CM_LOGL_WARNING, "CurrentType connectiong tryed %d times", m_nCount);
        return NONE;
    }

    else if (m_nStatus == 2)
    {
        return m_mType;
    }

    return m_mType;
}

INT32 CMNetConnMgr::GetConfig()
{
    //目前未实现
    return m_nIapId;
}

BOOL CMNetConnMgr::EnumAccessPoint(CMMap<UINT32, CMString>& m_apList)
{
    m_apList.clear();
    
    TBuf<KCommsDbSvrMaxColumnNameLength> apnName;
    TUint32 aIapId = 0;
    
    CCommsDatabase* commDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
    CleanupStack::PushL(commDb); 
    CCommsDbTableView* commView =commDb->OpenTableLC(TPtrC(IAP));
    if (commView->GotoFirstRecord() == KErrNone)
    {
        do
        {
            commView->ReadTextL((TPtrC)COMMDB_NAME, apnName);
            commView->ReadUintL(TPtrC(COMMDB_ID), aIapId);        
            m_apList.insert(aIapId, (const WCHAR*)apnName.PtrZ());
        }while(commView->GotoNextRecord() == KErrNone);
    }
    CleanupStack::PopAndDestroy(2);  
    return TRUE;
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
    
    //需要传入m_cConn避免弹出接入点选择框
    INT32 nRet = m_cHostRsv.Open( m_cSockServ , KAfInet , KProtocolInetTcp , m_cConn );
    if (nRet != KErrNone && nRet != KErrAlreadyExists)
    {
        return CMString();
    }    
    
    TNameEntry resolved;
    TRequestStatus aStatus;

    m_cHostRsv.GetByName(TPtrC((const UINT16*)(const WCHAR*)sName) , resolved , aStatus);
    User::WaitForRequest(aStatus);
    if (aStatus == KErrNone)
    {
        TInetAddr hostAddr;
        hostAddr = resolved().iAddr;
        TBuf<200> buf;
        hostAddr.Output(buf);
        buf.TrimAll();
        //CM_LOGP(CM_LOGL_DEBUG, "CMNetConnMgr::HostNameToIP size %d", (const CHAR*)CMString((const WCHAR*)buf.PtrZ()));
        
        CMString sValue((const WCHAR*)buf.PtrZ());
        m_dnsMutex.Lock();
        m_dnsCache.insert(sName, sValue);
        m_dnsMutex.UnLock();
        return sValue;
    }
    
    return CMString();
}

UINT32 CMNetConnMgr::GetSapID(CMNetConnMgr::TYPE type)
{
    TBuf<KCommsDbSvrMaxColumnNameLength> apnName;
    TBuf<10> defApn;
    TUint32 fakeIapId;
    TUint32 aIapId = 0;
    
    switch (type)
    {
        case CMWAP:
            defApn = _L("cmwap");
            break;
        case CMNET:
        default:
            defApn = _L("cmnet");
    }
    
#if defined(__WINSCW__)
    defApn = _L("Winsock");
#endif
    
    CCommsDatabase* commDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
    CleanupStack::PushL(commDb); 
    CCommsDbTableView* commView =commDb->OpenTableLC(TPtrC(OUTGOING_GPRS));
    if (commView->GotoFirstRecord() == KErrNone)
    {
        do
        {
            commView->ReadTextL((TPtrC)GPRS_APN, apnName);
            commView->ReadUintL(TPtrC(COMMDB_ID), fakeIapId);
            if (apnName.Find(defApn) >= 0) //不区分大小写
            {
                CCommsDbTableView* pIAPView = commDb->OpenViewMatchingUintLC(TPtrC(IAP), TPtrC(IAP_SERVICE), fakeIapId);
                if(pIAPView)
                {
					TInt nErr = pIAPView->GotoFirstRecord();
					if(nErr == KErrNone)
					{
						pIAPView->ReadUintL(TPtrC(COMMDB_ID), fakeIapId);
						aIapId = fakeIapId;
						CleanupStack::PopAndDestroy(); //pIAPView
						break;
					}
					else
						CleanupStack::PopAndDestroy(); //pIAPView
                }
            }
        }while(commView->GotoNextRecord() == KErrNone);
    }
    CleanupStack::PopAndDestroy(2);
    
    return aIapId;
}

void CMNetConnMgr::DoCancel()
{
//    m_cConn.CancelWaitForIncoming();
}

void CMNetConnMgr::RunL()
{
    if (iStatus == KErrNone || iStatus == KErrAlreadyExists)
    {
        if (m_nStatus == 1)
        {    
			if(m_bWifi)
				m_mType = CMNET;
			else if (m_mType == NONE)
            {//尚未获取接入点类型，从conn中获取
                TBuf<KCommsDbSvrMaxColumnNameLength*2> col;
                col.Format(TPtrC(_L("%s\\%s")), IAP, IAP_SERVICE);
                TUint32 fakeIapId;
                INT32 nRet = m_cConn.GetIntSetting(col, fakeIapId);
                if (nRet != KErrNone)
                {
                    CMString sTmp((const WCHAR*)col.PtrZ());
                    CM_ERRP("get connection info %s failed", (const CHAR*)sTmp);
                    Release();
                    return;
                }
                
                CCommsDatabase* commDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
                CleanupStack::PushL(commDb); 
                
                TBuf<KCommsDbSvrRealMaxFieldLength> sType;                
                CCommsDbTableView* commView = commDb->OpenViewMatchingUintLC(TPtrC(OUTGOING_GPRS), TPtrC(COMMDB_ID), fakeIapId);
                nRet = commView->GotoFirstRecord();
#if defined(__WINSCW__)
                sType = (const TText*)L"cmnet";
#else
                if(nRet == KErrNone)
                {
                    commView->ReadTextL((TPtrC)GPRS_APN, sType);
                }
                else
                {
                    CleanupStack::PopAndDestroy(2);
                    
                    CM_ERRP("fakeIapId %d has no APN name", fakeIapId);
                    Release();
                    return;                    
                }
#endif
                CleanupStack::PopAndDestroy(2);
                
//                INT32 nRet = m_cConn.GetDesSetting(col, sType);
//                if (nRet != KErrNone)
//                {
//                    CMString sTmp((const WCHAR*)col.PtrZ());
//                    CM_ERRP("get connection info %s failed", (const CHAR*)sTmp);
//                    Release();
//                    return;
//                }
                
                sType.LowerCase();
                if (sType.Find(TPtrC(_L("cmwap"))) >= 0 || sType.Find(TPtrC(_L("ctwap"))) >= 0 || sType.Find(TPtrC(_L("uniwap"))) >= 0 || sType.Find(TPtrC(_L("3gwap"))) >= 0)
                {
                    m_mType = CMWAP;
                }
                else
                    m_mType = CMNET;
            }
            if (m_mType == CMWAP)
            {//wap连接方式获取接入点信息
//                TBuf<KCommsDbSvrMaxColumnNameLength*2> col;
//                TBuf<KCommsDbSvrRealMaxFieldLength> address;
//                TUint32  port = 0;
//                TUint32 iapId;
//                
//                col.Format(TPtrC(_L("%s\\%s")), IAP, COMMDB_ID);
//                INT32 nRet = m_cConn.GetIntSetting(col, iapId);
//                if (nRet != KErrNone)
//                {
//                    CMString sTmp((const WCHAR*)col.PtrZ());
//                    CM_ERRP("get connection info %s failed", (const CHAR*)sTmp);
//                    Release();
//                    return;
//                }
//                
//                CM_LOG(CM_LOGL_DEBUG, "1");
//                CCommsDatabase* commDb = CCommsDatabase::NewL(EDatabaseTypeIAP);
//                CleanupStack::PushL(commDb); 
//                
//                TBuf<KCommsDbSvrRealMaxFieldLength> sType;                
//                CCommsDbTableView* commView = commDb->OpenViewMatchingUintLC(TPtrC(WAP_IP_BEARER), TPtrC(IAP), iapId);
//                nRet = commView->GotoFirstRecord();
//                if(nRet == KErrNone)
//                {
//                    CM_LOG(CM_LOGL_DEBUG, "2");
//                    
//                    commView->ReadTextL((TPtrC)WAP_GATEWAY_ADDRESS, address);
//                    commView->ReadUintL((TPtrC)WAP_PROXY_PORT, port);
//                }
//                else
//                {
//                    CleanupStack::PopAndDestroy(2);
//                    
//                    CM_ERRP("iapId %d has no WAPIPBearer info", iapId);
//                    Release();
//                    return;                    
//                }
//                CleanupStack::PopAndDestroy(2);
//                CM_LOG(CM_LOGL_DEBUG, "3");
                
//                m_pProxy = new CMUrl(CMString((const WCHAR*)address.Ptr()));
                //目前写死
                m_pProxy = new CMUrl(CMString(L"10.0.0.172:80"));
                if (!m_pProxy->Parse())
                {
                    CM_ERRP("wrong proxy server addr is %s", (const CHAR*)m_pProxy->Url());
                    return;
                }
                
//                m_pProxy->Port() = port;
                
                CM_LOGP(CM_LOGL_DEBUG, "wap proxy is %s:%d", (const CHAR*)m_pProxy->Host(), m_pProxy->Port());
            }
    
            m_nStatus = 2;
            if(!m_pConnectionNotifier)
                m_pConnectionNotifier = new CMConnectionNotifier(this,m_cConn);
            m_pConnectionNotifier->Start();
        }
    }
    else if (iStatus == KErrCancel)
    {
		m_bManualCancel = TRUE;
    }
    else
    {
        Release();
        //m_nStatus = 3;  //symbian专有，表示失败，不用再重连
        CM_ERRP("RConntion start failed, errno is %d", iStatus.Int());
    }
}
void CMNetConnMgr::IAPType(UINT32 iapid)
{
	CCommsDatabase* db = CCommsDatabase::NewL( EDatabaseTypeIAP );
	CleanupStack::PushL(db); 
	TUint32 id = 0; 
	//TBuf iapName; 
	TUint32 iapService; 
	TBuf<64> serviceType;
	m_bWifi = FALSE;
	CCommsDbTableView* view = db->OpenTableLC(TPtrC(IAP)); //IAP is the table name 
	TInt result = view->GotoFirstRecord(); 
	while (result == KErrNone ) 
	{ 
		view->ReadUintL(TPtrC(COMMDB_ID), id); 
//		view->ReadTextL(TPtrC(COMMDB_NAME), iapName); 
//		view->ReadUintL(TPtrC(IAP_SERVICE), iapService); 
		view->ReadTextL(TPtrC(IAP_SERVICE_TYPE), serviceType); 
		if (iapid == id) 
		{ 
			if (serviceType.Compare(TPtrC(OUTGOING_GPRS)) !=0)
				{
					m_bWifi = TRUE;
					CM_ERR("CMNetConnMgr::IAPType(UINT32 iapid) wifi ");
				}
			break; 
		} 
		result = view->GotoNextRecord(); 
	} 
	CleanupStack::PopAndDestroy(2); 	
	return ;
}
BOOL CMNetConnMgr::IsWifi()
{
	return m_bWifi;
}

void CMNetConnMgr::OnConnectionNotifier( TInt aStage, TInt aError)
{
	m_nStatus = 0;
	CM_ERRP("CMNetConnMgr::OnConnectionNotifier stage:%d,error:%d", aStage,aError);
}
void CMNetConnMgr::OnConnectionClose()
{
	m_nStatus = 0;
	CM_ERR("CMNetConnMgr::OnConnectionClose().....");
}


