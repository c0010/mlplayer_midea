#pragma once
#ifdef WINCE_OTHER
#include <windows.h>
#include <tchar.h>
#include <wzcmsq.h>
#include "ntddndis.h"
#include "wzcsapi.h"

#define DBG_MSG					1

//class CWLanConfig
//{
//public:
//	CWLanConfig()
//	{
//		m_fWZCInit = FALSE;
//		m_CardIndex = -1;			
//	}
//
//	BOOL InitZeroConfig(void);
//	void PrintfMacAddress(IN PRAW_DATA prdMAC);
//	void PrintSSID(PRAW_DATA prdSSID);
//	PTCHAR SupportedRate(IN BYTE ucbRawValue);
//	UINT ChannelNumber(IN ULONG ulFrequency_kHZ);
//	void PrintConfigList(PRAW_DATA prdBSSIDList);
//	void EnumWirelessNetwordCard(void);
//	void WirelessQuery(void);
//
//private:
//	typedef DWORD (*PFN_WZCQueryInterfaceEx)(LPWSTR pSrvAddr,DWORD dwInFlags,PINTF_ENTRY_EX pIntf,LPDWORD pdwOutFlags);
//	typedef DWORD (*PFN_WZCSetInterfaceEx)(LPWSTR pSrvAddr,DWORD dwInFlags,PINTF_ENTRY_EX pIntf,LPDWORD pdwOutFlags);
//	typedef DWORD (*PFN_WZCRefreshInterfaceEx)(LPWSTR pSrvAddr,DWORD dwInFlags,PINTF_ENTRY_EX pIntf,LPDWORD pdwOutFlags);
//	typedef DWORD (*PFN_WZCEnumEapExtensions)(DWORD *pdwNumOfExtensions,PEAP_EXTENSION_INFO *ppEapExtensions);
//	typedef DWORD (*PFN_WZCDeleteIntfObjEx)(PINTF_ENTRY_EX pIntf);
//	typedef DWORD (*PFN_WZCQueryContext)(LPWSTR pSrvAddr,DWORD dwInFlags,PWZC_CONTEXT pContext,LPDWORD pdwOutFlags);
//	typedef DWORD (*PFN_WZCSetContext)(LPWSTR pSrvAddr,DWORD dwInFlags,PWZC_CONTEXT pContext,LPDWORD pdwOutFlags);
//	typedef VOID  (*PFN_WZCPassword2Key)(PWZC_WLAN_CONFIG pwzcConfig, LPCSTR cszPassword);
//
//	PFN_WZCQueryInterfaceEx    pfnWZCQueryInterfaceEx;
//	PFN_WZCSetInterfaceEx      pfnWZCSetInterfaceEx;
//	PFN_WZCRefreshInterfaceEx  pfnWZCRefreshInterfaceEx;
//	PFN_WZCEnumEapExtensions   pfnWZCEnumEapExtensions;
//	PFN_WZCDeleteIntfObjEx     pfnWZCDeleteIntfObjEx;
//	PFN_WZCQueryContext        pfnWZCQueryContext;
//	PFN_WZCSetContext          pfnWZCSetContext;
//	PFN_WZCPassword2Key        pfnWZCPassword2Key;
//
//	BOOL			m_fWZCInit;
//	int				m_CardIndex;
//	TCHAR			m_WirelessCard[MAX_PATH];	
//};

BOOL IsWirelessCard(PTCHAR pCard);
BOOL GetFirstWirelessCard(PTCHAR pCard);
BOOL GetWirelessCardInfo(PTCHAR pCard, PINTF_ENTRY_EX pIntf, PDWORD pOutFlags);
BOOL IsAssociated(const INTF_ENTRY_EX Intf, const DWORD dwOutFlags);
#endif