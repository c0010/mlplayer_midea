#include "stdafx.h"
#include "WLan.h"
#ifdef WINCE_OTHER
#pragma comment(lib,  "wzcsapi.lib")

//TCHAR* g_szAuthenticationMode[] =
//{
//	L"Ndis802_11AuthModeOpen",
//	L"Ndis802_11AuthModeShared",
//	L"Ndis802_11AuthModeAutoSwitch",
//	L"Ndis802_11AuthModeWPA",
//	L"Ndis802_11AuthModeWPAPSK",
//	L"Ndis802_11AuthModeWPANone",
//	L"Ndis802_11AuthModeWPA2",
//	L"Ndis802_11AuthModeWPA2PSK"
//};
//
//TCHAR* g_szcPrivacyMode[] =
//{
//	TEXT("Ndis802_11WEPEnabled"),                                                         
//	TEXT("Ndis802_11WEPDisabled"),
//	TEXT("Ndis802_11WEPKeyAbsent"),
//	TEXT("Ndis802_11WEPNotSupported"),
//	TEXT("Ndis802_11Encryption2Enabled"),
//	TEXT("Ndis802_11Encryption2KeyAbsent"),
//	TEXT("Ndis802_11Encryption3Enabled"),
//	TEXT("Ndis802_11Encryption3KeyAbsent")
//};
//
//
//TCHAR g_szSupportedRate[32];// = { L"1", L"2", L"5.5", L"11", L"" };   // Mbit/s
//
//BOOL CWLanConfig::InitZeroConfig()
//{
//	HINSTANCE hWZCLib = NULL;
//	
//	if (m_fWZCInit) {
//		return TRUE; // Already initialized
//	}
//
//	// See if zero config API present in system
//	if ((hWZCLib = LoadLibrary(L"wzcsapi.dll")) == NULL) {
//		RETAILMSG(1,(TEXT("!WZCUI: WZCAPI.DLL not present in system\r\n")));
//		return FALSE;
//	}
//
//	pfnWZCQueryInterfaceEx    = (PFN_WZCQueryInterfaceEx)GetProcAddress(hWZCLib,L"WZCQueryInterfaceEx");
//	pfnWZCSetInterfaceEx      = (PFN_WZCSetInterfaceEx)GetProcAddress(hWZCLib,L"WZCSetInterfaceEx");
//	pfnWZCRefreshInterfaceEx  = (PFN_WZCRefreshInterfaceEx)GetProcAddress(hWZCLib,L"WZCRefreshInterfaceEx");
//	pfnWZCEnumEapExtensions = (PFN_WZCEnumEapExtensions)GetProcAddress(hWZCLib,L"WZCEnumEapExtensions");
//	pfnWZCDeleteIntfObjEx     = (PFN_WZCDeleteIntfObjEx)GetProcAddress(hWZCLib,L"WZCDeleteIntfObjEx");
//	pfnWZCQueryContext		= (PFN_WZCQueryContext)GetProcAddress(hWZCLib,L"WZCQueryContext");
//	pfnWZCSetContext		= (PFN_WZCSetContext)GetProcAddress(hWZCLib,L"WZCSetContext");
//	pfnWZCPassword2Key      = (PFN_WZCPassword2Key)GetProcAddress(hWZCLib,L"WZCPassword2Key");
//
//	if ((pfnWZCQueryInterfaceEx == NULL)   ||
//		(pfnWZCSetInterfaceEx == NULL)     ||
//		(pfnWZCRefreshInterfaceEx == NULL) ||
//		(pfnWZCEnumEapExtensions == NULL)||
//		(pfnWZCDeleteIntfObjEx == NULL)    ||
//		(pfnWZCSetContext == NULL)       ||
//		(pfnWZCQueryContext == NULL)) {
//			RETAILMSG(1,(TEXT("!WZCUI: WZC APis not present in system\r\n")));
//			FreeLibrary(hWZCLib);
//			return FALSE;
//	}
//
//	m_fWZCInit = TRUE;
//
//	return TRUE;
//}
//
//void CWLanConfig::EnumWirelessNetwordCard()
//{
//	INTFS_KEY_TABLE IntfsTable;
//	IntfsTable.dwNumIntfs = 0;
//	IntfsTable.pIntfs = NULL;
//	
//	_tcscpy(m_WirelessCard, TEXT(""));
//
//	DWORD dwStatus = WZCEnumInterfaces(NULL, &IntfsTable);
//
//	if (dwStatus != ERROR_SUCCESS)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("WZCEnumInterfaces() error 0x%08X\n"),dwStatus));
//		return;
//	}
//
//	if (!IntfsTable.dwNumIntfs)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("System has no wireless card.\n")));
//		return;
//	}
//	
//	m_CardIndex = IntfsTable.dwNumIntfs;
//
//	RETAILMSG(DBG_MSG, (TEXT("Enum %d Wiless Net Card:\n"),m_CardIndex));
//
//	for (uint i = 0; i < IntfsTable.dwNumIntfs; i++)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("WIFI Card [%d] = %s\n"), i, IntfsTable.pIntfs[i].wszGuid));
//	}
//
//	_tcscpy(m_WirelessCard, IntfsTable.pIntfs[0].wszGuid);
//
//	LocalFree(IntfsTable.pIntfs);
//}
//
//void CWLanConfig::PrintfMacAddress(IN PRAW_DATA prdMAC)
//{
//	if (prdMAC == NULL || prdMAC->dwDataLen == 0)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("<NULL>")));
//	}
//	else if (prdMAC->dwDataLen != 6)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("<INVLID MAC>")));
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("%02X:%02X:%02X:%02X:%02X:%02X"),
//			prdMAC->pData[0],
//			prdMAC->pData[1],
//			prdMAC->pData[2],
//			prdMAC->pData[3],
//			prdMAC->pData[4],
//			prdMAC->pData[5]));
//	}
//}
//
//void CWLanConfig::PrintSSID(PRAW_DATA prdSSID)
//{
//	if (prdSSID == NULL || prdSSID->dwDataLen == 0)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("<null>")));
//	}
//	else
//	{
//		TCHAR szSsid[33];
//		uint i;
//		for (i = 0; i < prdSSID->dwDataLen; i++)
//		{
//			szSsid[i] = prdSSID->pData[i];
//		}
//
//		szSsid[i] = TEXT('\0');
//
//		RETAILMSG(DBG_MSG, (TEXT("%s"),szSsid));
//	}
//}
//
//
//PTCHAR CWLanConfig::SupportedRate(IN BYTE ucbRawValue)
//{
//	double fRate = ((double)(ucbRawValue & 0x7F)) * 0.5;
//	swprintf(g_szSupportedRate, L"%.1f", fRate);
//	return g_szSupportedRate;
//} 
//
//UINT CWLanConfig::ChannelNumber(IN ULONG ulFrequency_kHz)
//{
//	ULONG ulFrequency_MHz = ulFrequency_kHz / 1000;
//	if((2412 <= ulFrequency_MHz) && (ulFrequency_MHz < 2484))
//		return ((ulFrequency_MHz - 2412) / 5) + 1;
//	else if(ulFrequency_MHz == 2484)
//		return 14;
//	return 0;   // invalid channel number
//}
//
//void CWLanConfig::PrintConfigList(PRAW_DATA prdBSSIDList)
//{
//	if (prdBSSIDList == NULL || prdBSSIDList->dwDataLen	 == 0)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("<null> entry.")));
//	}
//	else
//	{
//		PWZC_802_11_CONFIG_LIST pConfigList = (PWZC_802_11_CONFIG_LIST)prdBSSIDList->pData;
//
//		RETAILMSG(DBG_MSG, (TEXT("[%d] entries.\n\n"), pConfigList->NumberOfItems));
//
//		uint i;
//
//		for (i = 0; i < pConfigList->NumberOfItems; i++)
//		{
//			PWZC_WLAN_CONFIG pConfig = &(pConfigList->Config[i]);
//			RETAILMSG(DBG_MSG, (TEXT("************ List Entry Number [%d] ************\n"),i));
//			RETAILMSG(DBG_MSG, (TEXT("	Length	= %d bytes.\n"), pConfig->Length));
//			RETAILMSG(DBG_MSG, (TEXT("	dwCtlFlags	= 0x%08X\n"), pConfig->dwCtlFlags));
//			RETAILMSG(DBG_MSG, (TEXT("	MacAddress	= %02X:%02X:%02X:%02X:%02X:%02X\n"),
//				pConfig->MacAddress[0],
//				pConfig->MacAddress[1],
//				pConfig->MacAddress[2],
//				pConfig->MacAddress[3],
//				pConfig->MacAddress[4],
//				pConfig->MacAddress[5]));
//			RETAILMSG(DBG_MSG, (TEXT("	SSID	= ")));
//			RAW_DATA rdBuffer;
//			rdBuffer.dwDataLen = pConfig->Ssid.SsidLength;
//			rdBuffer.pData = pConfig->Ssid.Ssid;
//			PrintSSID(&rdBuffer);
//			RETAILMSG(DBG_MSG, (TEXT("\n")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Privacy	= %d "),pConfig->Privacy));
//			if (pConfig->Privacy == 1)
//			{
//				RETAILMSG(DBG_MSG, (TEXT("Privacy disabled (wireless data is not encrypted)\n")));
//			}
//			else
//			{
//				RETAILMSG(DBG_MSG, (TEXT("Privacy enabled (encryted with [%s])\n"), g_szcPrivacyMode[pConfig->Privacy]));
//			}
//
//			RETAILMSG(DBG_MSG, (TEXT("	RSSI	= %d dBm (0=excellent, -100=weak signal)\n"), pConfig->Rssi));
//			RETAILMSG(DBG_MSG, (TEXT("	NetworkTypeInUse	= %s\n"),
//				(pConfig->NetworkTypeInUse == Ndis802_11FH) ? TEXT("NDIS802_11FH") :
//				(pConfig->NetworkTypeInUse == Ndis802_11DS) ? TEXT("NDIS802_11DS") : 
//				(pConfig->NetworkTypeInUse == Ndis802_11DS) ? TEXT("NDIS802_11DS") : 
//				TEXT("<UNKONWN SHOULD NOT BE !!>")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Configuration:\n")));
//			RETAILMSG(DBG_MSG, (TEXT("		Struct Length	= %d\n"),pConfig->Configuration.Length));
//			RETAILMSG(DBG_MSG, (TEXT("		BeaconPeriod	= %d kusec\n"), pConfig->Configuration.BeaconPeriod));
//			RETAILMSG(DBG_MSG, (TEXT("		ATIMWindow	= %d kusec\n"), pConfig->Configuration.ATIMWindow));
//			RETAILMSG(DBG_MSG, (TEXT("		DSConfig	= %d kHz (ch - %d)\n"), pConfig->Configuration.DSConfig, ChannelNumber(pConfig->Configuration.DSConfig)));
//			RETAILMSG(DBG_MSG, (TEXT("		FHConfig:\n")));
//			RETAILMSG(DBG_MSG, (TEXT("			Struct Length	= %d\n"),pConfig->Configuration.FHConfig.Length));
//			RETAILMSG(DBG_MSG, (TEXT("			HopPattern =	%d\n"),pConfig->Configuration.FHConfig.HopPattern));
//			RETAILMSG(DBG_MSG, (TEXT("			HopSet =	%d\n"),pConfig->Configuration.FHConfig.HopSet));
//			RETAILMSG(DBG_MSG, (TEXT("			DwellTime =	%d\n"),pConfig->Configuration.FHConfig.DwellTime));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Infrastructure	= %s\n"),
//				(pConfig->InfrastructureMode == Ndis802_11IBSS) ? TEXT("NDIS802_11IBSS") :
//				(pConfig->InfrastructureMode == Ndis802_11Infrastructure) ? TEXT("Ndis802_11Infrastructure") :
//				(pConfig->InfrastructureMode == Ndis802_11AutoUnknown) ? TEXT("Ndis802_11AutoUnknown") :
//				TEXT("<UNKNOWN! SHOULD NOT BE!!>")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	SupportedRates	= ")));
//			for (int j = 0; j < 8; j++)
//			{
//				if (pConfig->SupportedRates[j])
//				{
//					RETAILMSG(DBG_MSG, (TEXT("%s,"), SupportedRate(pConfig->SupportedRates[j])));
//				}
//			}
//
//			RETAILMSG(DBG_MSG, (TEXT("(Mbit/s)\n")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Authentication	= %d "), pConfig->AuthenticationMode));
//
//			if (pConfig->AuthenticationMode < Ndis802_11AuthModeMax)
//			{
//				RETAILMSG(DBG_MSG, (TEXT("%s\n"), g_szAuthenticationMode[pConfig->AuthenticationMode]));
//			}
//			else
//			{
//				RETAILMSG(DBG_MSG, (TEXT("<unknown>\n")));
//			}
//			RETAILMSG(DBG_MSG, (TEXT("	KeyIndex	= %d \n"), pConfig->KeyIndex));
//			RETAILMSG(DBG_MSG, (TEXT("	Key length	= %d bytes.\n"), pConfig->KeyLength));
//			RETAILMSG(DBG_MSG, (TEXT("	rdUserData length	= %d bytes.\n"), pConfig->rdUserData));
//		}
//	}
//}
//
//void CWLanConfig::WirelessQuery(void)
//{
//	TCHAR *szWiFiCard = NULL;
//
//	if (!*m_WirelessCard)
//	{
//		EnumWirelessNetwordCard();
//
//		if (!*m_WirelessCard)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("No Wireless Card.\n")));
//			return;
//		}		
//	}
//
//	szWiFiCard = m_WirelessCard;
//
//	INTF_ENTRY_EX Intf;
//	DWORD dwOutFlgs = 0;
//	ZeroMemory(&Intf, sizeof(INTF_ENTRY_EX));
//
//	Intf.wszGuid = szWiFiCard;
//
//	DWORD dwStatus = WZCQueryInterfaceEx(NULL, INTF_ALL, &Intf, &dwOutFlgs);
//
//	if (dwStatus != ERROR_SUCCESS)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("WZCQueryInterfaceEx() error 0x%08X\n"), dwStatus));
//		return;
//	}
//
//	RETAILMSG(DBG_MSG, (TEXT("WZCQueryInterfaceEx() for %s\n"),szWiFiCard));
//	RETAILMSG(DBG_MSG, (TEXT("In flags used	=[0x%08X]\n"),INTF_ALL));
//	RETAILMSG(DBG_MSG, (TEXT("Return out flag	=[0x%08X]\n"),dwOutFlgs));
//	RETAILMSG(DBG_MSG, (TEXT("wzcGuid	=[%s]\n"),Intf.wszGuid));
//	RETAILMSG(DBG_MSG, (TEXT("wzcDescr	=[%s]\n"),Intf.wszDescr));
//
//	if (dwOutFlgs & INTF_BSSID)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("BSSID=")));
//		PrintfMacAddress(&Intf.rdBSSID);
//
//		PRAW_DATA prdMAC = &Intf.rdBSSID;
//
//		if (prdMAC == NULL || prdMAC->dwDataLen == 0 || 
//			(!prdMAC->pData[0] && !prdMAC->pData[1] && !prdMAC->pData[2] &&
//			!prdMAC->pData[3] && !prdMAC->pData[4] && !prdMAC->pData[5]))
//		{
//			RETAILMSG(DBG_MSG, (TEXT("(This wifi card is not associated to any)\n")));
//		}
//		else
//		{
//			RETAILMSG(DBG_MSG, (TEXT("(This wifi card is associated state)\n")));
//		}
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("BSSID = <unknown> (not connected)\n")));
//	}
//
//	if (dwOutFlgs & INTF_NDISMEDIA)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Media Type	=[%d]\n"),Intf.ulMediaType));
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Media Type	=<unknown>\n")));
//	}
//
//	if (dwOutFlgs & INTF_ALL_FLAGS)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Configuration Mode = [0x%08X]\n"), Intf.dwCtlFlags));
//
//		if (Intf.dwCtlFlags & INTFCTL_ENABLED)
//		{
//			RETAILMSG(DBG_MSG, (TEXT(" Zero conf enabled for this interface\n")));
//		}
//
//		if (Intf.dwCtlFlags & INTFCTL_FALLBACK)
//		{
//			RETAILMSG(DBG_MSG, (TEXT(" Attempt to connect to visible non-preferred networks also\n")));
//		}
//
//		if (Intf.dwCtlFlags & INTFCTL_OIDSSUPP)
//		{
//			RETAILMSG(DBG_MSG, (TEXT(" 802.11 OIDs are supported by the driver/firmware\n")));
//		}
//
//		if (Intf.dwCtlFlags & INTFCTL_VOLATILE)
//		{
//			RETAILMSG(DBG_MSG, (TEXT(" the service parameters are volatile\n")));
//		}
//
//		if (Intf.dwCtlFlags & INTFCTL_POLICY)
//		{
//			RETAILMSG(DBG_MSG, (TEXT(" the service parameters policy enforced\n")));
//		}
//	}
//
//	if (dwOutFlgs & INTF_INFRAMODE)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Infrastructure Mode = [%d] "), Intf.nInfraMode));
//
//		if (Intf.nInfraMode == Ndis802_11IBSS)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("IBSS net (adhoc net)\n")));
//		}
//		else if (Intf.nInfraMode == Ndis802_11Infrastructure)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("Infrastructure net (connected to an Access Point)\n")));
//		}
//		else
//		{
//			RETAILMSG(DBG_MSG, (TEXT("Ndis802_11AutoUnkonwn\n")));
//		}
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Infrastructure mode = <unknown>\n")));
//	}
//
//	if (dwOutFlgs & INTF_AUTHMODE)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Authentication Mode = [%0d] "), Intf.nAuthMode));
//
//		if ((DWORD)Intf.nAuthMode < Ndis802_11AuthModeMax)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("%s\n"),g_szAuthenticationMode[Intf.nAuthMode]));
//		}
//		else
//		{
//			RETAILMSG(DBG_MSG, (TEXT("<unkonwn>\n")));
//		}
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Authentication Mode = <unkonwn>\n")));
//	}
//
//	RETAILMSG(DBG_MSG, (TEXT("rdNicCapabilities = %d bytes\n"), Intf.rdNicCapabilities.dwDataLen));
//
//	if (Intf.rdNicCapabilities.dwDataLen)
//	{
//		PINTF_80211_CAPABILITY pCapability = (PINTF_80211_CAPABILITY)Intf.rdNicCapabilities.pData;
//		DWORD i;
//
//		RETAILMSG(DBG_MSG, (TEXT(" dwNumOfPMKIDs	: [%d]\n"), pCapability->dwNumOfPMKIDs));
//		RETAILMSG(DBG_MSG, (TEXT(" dwNumOfAuthEncryptPairs	: [%d]\n"), pCapability->dwNumOfAuthEncryptPairs));
//
//		for (i = 0; i < pCapability->dwNumOfAuthEncryptPairs; i++)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("	Pair[%d]\n"), i+1));
//			RETAILMSG(DBG_MSG, (TEXT("	AuthmodeSupported	[%s]\n"),
//				g_szAuthenticationMode[pCapability->AuthEncryptPair[i].AuthModeSupported]));
//			RETAILMSG(DBG_MSG, (TEXT("	EncryptStatusSupported	[%s]\n"),
//				g_szcPrivacyMode[pCapability->AuthEncryptPair[i].EncryptStatusSupported]));
//		}
//	}
//
//	RETAILMSG(DBG_MSG, (TEXT("rdPMKCache = %u bytes\n"), Intf.rdPMKCache.dwDataLen));
//
//	if (Intf.rdPMKCache.dwDataLen)
//	{
//		PNDIS_802_11_PMKID	pCache = (PNDIS_802_11_PMKID)Intf.rdPMKCache.pData;
//		DWORD i;
//
//		RETAILMSG(DBG_MSG, (TEXT("  BSSIDInfoCount	:[%u]\n"), pCache->BSSIDInfoCount));
//
//		for (i = 0; i < pCache->BSSIDInfoCount; i++)
//		{
//			PBYTE pMac = &pCache->BSSIDInfo[i].BSSID[0];
//			PBYTE pId = &pCache->BSSIDInfo[i].PMKID[0];
//			RETAILMSG(DBG_MSG, (TEXT("	BSSID=%02X%02X%02X%02X%02X%02X PMKID=%02X%02X..%02X\n"),
//				pMac[0], pMac[1], pMac[2], pMac[3], pMac[4], pMac[5],
//				pId[0], pId[1], pId[14], pId[15]));
//		}
//	}
//
//	if (dwOutFlgs & INTF_WEPSTATUS)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("WEP Status	= [%d] "), Intf.nWepStatus));
//
//		WCHAR* szWepStatus[] =
//		{
//			L"Ndis802_11WEPEnabled",
//			L"Ndis802_11WEPDisabled",
//			L"Ndis802_11WEPKeyAbsent",
//			L"Ndis802_11WEPNotSupported"
//		};
//
//		if (Intf.nWepStatus < 4)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("%s\n"), szWepStatus[Intf.nWepStatus]));
//		}
//		else
//		{
//			RETAILMSG(DBG_MSG, (TEXT("<unkonwn value>\n")));
//		}
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("WEP Status	= <unkonwn>\n")));
//	}
//
//	if (dwOutFlgs & INTF_SSID)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("SSID = ")));
//		PrintSSID(&Intf.rdSSID);
//		RETAILMSG(DBG_MSG, (TEXT("\n")));
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("SSID = <unkonwn>\n")));
//	}
//
//
//	if (dwOutFlgs & INTF_CAPABILITIES)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("Capabilities = \n")));
//
//		if (Intf.dwCapabilities & INTFCAP_SSN)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("	WPA/TKIP capable\n")));
//		}
//		if (Intf.dwCapabilities & INTFCAP_80211I)
//		{
//			RETAILMSG(DBG_MSG, (TEXT("	WPA/AES capable\n")));
//		}
//	}
//
//	RETAILMSG(DBG_MSG, (TEXT("\n")));
//	RETAILMSG(DBG_MSG, (TEXT("[Availavle Networks] SSID List ")));
//	PrintConfigList(&Intf.rdBSSIDList);
//
//	RETAILMSG(DBG_MSG, (TEXT("\n")));
//	RETAILMSG(DBG_MSG, (TEXT("[Preferred Networks] SSID List ")));
//	PrintConfigList(&Intf.rdStSSIDList);
//
//	RETAILMSG(DBG_MSG, (TEXT("\n")));
//	RETAILMSG(DBG_MSG, (TEXT("rdCtrlData length = %d bytes.\n"), Intf.rdCtrlData.dwDataLen));
//
//	WZCDeleteIntfObjEx(&Intf);
//
//	RETAILMSG(DBG_MSG, (TEXT("\n")));
//	RETAILMSG(DBG_MSG, (TEXT("Paramter setting in Zero Config\n")));
//
//	WZC_CONTEXT	WzcContext;
//
//	dwStatus = WZCQueryContext(NULL, 0x00, &WzcContext, NULL);
//
//	if (dwStatus != ERROR_SUCCESS)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("!!! Failed WZCQueryContext() Err = [0x%08X] !!!\n"), dwStatus));
//	}
//	else
//	{
//		RETAILMSG(DBG_MSG, (TEXT("tmTr = %d mili-seconds (Scan time out)\n"), WzcContext.tmTr));
//		RETAILMSG(DBG_MSG, (TEXT("tmTp = %d mili-seconds (Association time out)\n"), WzcContext.tmTp));
//		RETAILMSG(DBG_MSG, (TEXT("tmTc = %d mili-seconds (Periodic scan when conected)\n"), WzcContext.tmTc));
//		RETAILMSG(DBG_MSG, (TEXT("tmTf = %d mili-seconds (Periodic scan when disconnected)\n"), WzcContext.tmTf));
//	}
//}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
BOOL IsWirelessCard(PTCHAR pCard)
{
	if (!pCard)
	{
		return FALSE;
	}

	INTFS_KEY_TABLE IntfsTable;
	IntfsTable.dwNumIntfs = 0;
	IntfsTable.pIntfs = NULL;
	
	DWORD dwStatus = WZCEnumInterfaces(NULL, &IntfsTable);

	if (dwStatus != ERROR_SUCCESS)
	{
		RETAILMSG(DBG_MSG, (TEXT("WZCEnumInterfaces() error 0x%08X\n"),dwStatus));
		return FALSE;
	}

	if (!IntfsTable.dwNumIntfs)
	{
		RETAILMSG(DBG_MSG, (TEXT("System has no wireless card.\n")));
		return FALSE;
	}

	for (uint i = 0; i < IntfsTable.dwNumIntfs; i++)
	{
		RETAILMSG(DBG_MSG, (TEXT("WIFI Card [%d] = %s\n"), i, IntfsTable.pIntfs[i].wszGuid));
		if (_tcscmp(pCard, IntfsTable.pIntfs[i].wszGuid) == 0)
		{
			LocalFree(IntfsTable.pIntfs);

			RETAILMSG(DBG_MSG, (TEXT("Netcard = %s is Wireless Card\n"), pCard));
			return TRUE;
		}
		
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
BOOL GetFirstWirelessCard(PTCHAR pCard)
{
	if (!pCard)
	{
		return FALSE;
	}


	INTFS_KEY_TABLE IntfsTable;
	IntfsTable.dwNumIntfs = 0;
	IntfsTable.pIntfs = NULL;

	_tcscpy(pCard, TEXT(""));

	DWORD dwStatus = WZCEnumInterfaces(NULL, &IntfsTable);

	if (dwStatus != ERROR_SUCCESS)
	{
		RETAILMSG(DBG_MSG, (TEXT("WZCEnumInterfaces() error 0x%08X\n"),dwStatus));
		return FALSE;
	}

	if (!IntfsTable.dwNumIntfs)
	{
		RETAILMSG(DBG_MSG, (TEXT("System has no wireless card.\n")));
		return FALSE;
	}

	_tcscpy(pCard, IntfsTable.pIntfs[0].wszGuid);

	LocalFree(IntfsTable.pIntfs);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// pCard: 无线网卡 GUID
// pIntf: 无线网卡配置信息结果体
// pOutFlags: 网卡配置信息掩码标志
//////////////////////////////////////////////////////////////////////////
BOOL GetWirelessCardInfo(PTCHAR pCard, PINTF_ENTRY_EX pIntf, PDWORD pOutFlags)
{
	TCHAR *szWiFiCard = NULL;

	// 参数校验
	if (!pCard || !pIntf || !pOutFlags)
	{
		RETAILMSG(DBG_MSG, (TEXT("Param Error.\n")));
		return FALSE;
	}		

	szWiFiCard = pCard;
	
	*pOutFlags = 0;
	
	// 初始化无线网卡信息
	ZeroMemory(pIntf, sizeof(INTF_ENTRY_EX));
	
	// 设置 GUID 号
	pIntf->wszGuid = szWiFiCard;

	// 查询无线网卡信息
	DWORD dwStatus = WZCQueryInterfaceEx(NULL, INTF_ALL, pIntf, pOutFlags);

	if (dwStatus != ERROR_SUCCESS)
	{
		RETAILMSG(DBG_MSG, (TEXT("WZCQueryInterfaceEx() error 0x%08X\n"), dwStatus));
		return FALSE;
	}
	
	return TRUE;
}

BOOL IsAssociated(const INTF_ENTRY_EX Intf, const DWORD dwOutFlags)
{	
	if (dwOutFlags & INTF_BSSID)
	{
		PRAW_DATA prdMAC = (PRAW_DATA)(&Intf.rdBSSID);

		if (prdMAC == NULL || prdMAC->dwDataLen == 0 || 
			(!prdMAC->pData[0] && !prdMAC->pData[1] && !prdMAC->pData[2] &&
			!prdMAC->pData[3] && !prdMAC->pData[4] && !prdMAC->pData[5]))
		{
			RETAILMSG(DBG_MSG, (TEXT("(This wifi card is not associated to any)\n")));
			return FALSE;
		}
		else
		{
			RETAILMSG(DBG_MSG, (TEXT("(This wifi card is associated state)\n")));
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}	
}

//void GetWirelseeList(const PRAW_DATA prdBSSIDList)
//{
//	if (prdBSSIDList == NULL || prdBSSIDList->dwDataLen	 == 0)
//	{
//		RETAILMSG(DBG_MSG, (TEXT("<null> entry.")));
//	}
//	else
//	{
//		PWZC_802_11_CONFIG_LIST pConfigList = (PWZC_802_11_CONFIG_LIST)prdBSSIDList->pData;
//
//		RETAILMSG(DBG_MSG, (TEXT("[%d] entries.\n\n"), pConfigList->NumberOfItems));
//
//		uint i;
//
//		for (i = 0; i < pConfigList->NumberOfItems; i++)
//		{
//			PWZC_WLAN_CONFIG pConfig = &(pConfigList->Config[i]);
//			RETAILMSG(DBG_MSG, (TEXT("************ List Entry Number [%d] ************\n"),i));
//			RETAILMSG(DBG_MSG, (TEXT("	Length	= %d bytes.\n"), pConfig->Length));
//			RETAILMSG(DBG_MSG, (TEXT("	dwCtlFlags	= 0x%08X\n"), pConfig->dwCtlFlags));
//			RETAILMSG(DBG_MSG, (TEXT("	MacAddress	= %02X:%02X:%02X:%02X:%02X:%02X\n"),
//				pConfig->MacAddress[0],
//				pConfig->MacAddress[1],
//				pConfig->MacAddress[2],
//				pConfig->MacAddress[3],
//				pConfig->MacAddress[4],
//				pConfig->MacAddress[5]));
//			RETAILMSG(DBG_MSG, (TEXT("	SSID	= ")));
//			RAW_DATA rdBuffer;
//			rdBuffer.dwDataLen = pConfig->Ssid.SsidLength;
//			rdBuffer.pData = pConfig->Ssid.Ssid;
//			PrintSSID(&rdBuffer);
//			RETAILMSG(DBG_MSG, (TEXT("\n")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Privacy	= %d "),pConfig->Privacy));
//			if (pConfig->Privacy == 1)
//			{
//				RETAILMSG(DBG_MSG, (TEXT("Privacy disabled (wireless data is not encrypted)\n")));
//			}
//			else
//			{
//				RETAILMSG(DBG_MSG, (TEXT("Privacy enabled (encryted with [%s])\n"), g_szcPrivacyMode[pConfig->Privacy]));
//			}
//
//			RETAILMSG(DBG_MSG, (TEXT("	RSSI	= %d dBm (0=excellent, -100=weak signal)\n"), pConfig->Rssi));
//			RETAILMSG(DBG_MSG, (TEXT("	NetworkTypeInUse	= %s\n"),
//				(pConfig->NetworkTypeInUse == Ndis802_11FH) ? TEXT("NDIS802_11FH") :
//				(pConfig->NetworkTypeInUse == Ndis802_11DS) ? TEXT("NDIS802_11DS") : TEXT("<UNKONWN SHOULD NOT BE !!>")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Configuration:\n")));
//			RETAILMSG(DBG_MSG, (TEXT("		Struct Length	= %d\n"),pConfig->Configuration.Length));
//			RETAILMSG(DBG_MSG, (TEXT("		BeaconPeriod	= %d kusec\n"), pConfig->Configuration.BeaconPeriod));
//			RETAILMSG(DBG_MSG, (TEXT("		ATIMWindow	= %d kusec\n"), pConfig->Configuration.ATIMWindow));
//			RETAILMSG(DBG_MSG, (TEXT("		DSConfig	= %d kHz (ch - %d)\n"), pConfig->Configuration.DSConfig, ChannelNumber(pConfig->Configuration.DSConfig)));
//			RETAILMSG(DBG_MSG, (TEXT("		FHConfig:\n")));
//			RETAILMSG(DBG_MSG, (TEXT("			Struct Length	= %d\n"),pConfig->Configuration.FHConfig.Length));
//			RETAILMSG(DBG_MSG, (TEXT("			HopPattern =	%d\n"),pConfig->Configuration.FHConfig.HopPattern));
//			RETAILMSG(DBG_MSG, (TEXT("			HopSet =	%d\n"),pConfig->Configuration.FHConfig.HopSet));
//			RETAILMSG(DBG_MSG, (TEXT("			DwellTime =	%d\n"),pConfig->Configuration.FHConfig.DwellTime));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Infrastructure	= %s\n"),
//				(pConfig->InfrastructureMode == Ndis802_11IBSS) ? TEXT("NDIS802_11IBSS") :
//				(pConfig->InfrastructureMode == Ndis802_11Infrastructure) ? TEXT("Ndis802_11Infrastructure") :
//				(pConfig->InfrastructureMode == Ndis802_11AutoUnknown) ? TEXT("Ndis802_11AutoUnknown") :
//				TEXT("<UNKNOWN! SHOULD NOT BE!!>")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	SupportedRates	= ")));
//			for (int j = 0; j < 8; j++)
//			{
//				if (pConfig->SupportedRates[j])
//				{
//					RETAILMSG(DBG_MSG, (TEXT("%s,"), SupportedRate(pConfig->SupportedRates[j])));
//				}
//			}
//
//			RETAILMSG(DBG_MSG, (TEXT("(Mbit/s)\n")));
//
//			RETAILMSG(DBG_MSG, (TEXT("	Authentication	= %d "), pConfig->AuthenticationMode));
//
//			if (pConfig->AuthenticationMode < Ndis802_11AuthModeMax)
//			{
//				RETAILMSG(DBG_MSG, (TEXT("%s\n"), g_szAuthenticationMode[pConfig->AuthenticationMode]));
//			}
//			else
//			{
//				RETAILMSG(DBG_MSG, (TEXT("<unknown>\n")));
//			}
//
//			RETAILMSG(DBG_MSG, (TEXT("	rdUserData length	= %d bytes.\n"), pConfig->rdUserData));
//		}
//	}
//}
#endif