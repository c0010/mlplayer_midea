// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:全局对象类，不允许其他全局函数/变量存在
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmglobal.h"


CMSystemInfo& CMGlobal::SystemInfo()
{
	if (m_pSystemInfo)
		return *m_pSystemInfo;

	m_pSystemInfo = new CMSystemInfo();

	m_pSystemInfo->ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	m_pSystemInfo->ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	strcpy(m_pSystemInfo->AcceptType, "text/html,text/vnd.wap.wml,video/3mv,audio/3ma,audio/aac,application/x-shockwave-flash");

	return *m_pSystemInfo;
}

void CMGlobal::OpenDocument(CMString sDocument)
{
	SHELLEXECUTEINFO sei = {0};
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpVerb = _T("open");
	sei.lpFile = sDocument;
	sei.nShow = SW_SHOWNORMAL;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	::ShellExecuteEx(&sei);
}


//打电话
void CMGlobal::MakeCall(const CMString& sNumber)
{
    //PHONEMAKECALLINFO makeCallInfo;
    //makeCallInfo.cbSize=sizeof(PHONEMAKECALLINFO);
    //makeCallInfo.dwFlags=PMCF_PROMPTBEFORECALLING;
    //makeCallInfo.pszComment=(const WCHAR*)sNumber;
    //makeCallInfo.pszAppName=NULL;
    //makeCallInfo.pszCalledParty=NULL;
    //makeCallInfo.pszComment=NULL;
    //PhoneMakeCall(&makeCallInfo);

    SHELLEXECUTEINFO info;
    memset(&info,0,sizeof(SHELLEXECUTEINFO));
    info.cbSize = sizeof(info);
    info.fMask = SEE_MASK_FLAG_NO_UI;
    info.hwnd = NULL;
    info.lpVerb = _T("open");
    info.lpFile = _T("\\windows\\cprog.exe");
    CMString sParam;
    sParam.Format(L"-n -url tel:%s", (const WCHAR*)sNumber); //
    info.lpParameters = (const WCHAR*)sParam;
    info.lpDirectory = _T("");
    info.nShow = SW_SHOWNORMAL;
    info.hInstApp = NULL;
    ShellExecuteEx(&info); 
}

//发短信
void CMGlobal::OpenSMSG(const CMString& sNumber)
{
    SHELLEXECUTEINFO sheci = {0};
    sheci.cbSize = sizeof(sheci);
    sheci.fMask = SEE_MASK_FLAG_NO_UI;
    sheci.hwnd = NULL;
    sheci.lpVerb = TEXT("OPEN");
    sheci.nShow = SW_SHOW;
    sheci.lpFile = _T("\\Windows\\tmail.exe");
    CMString sParam;
    sParam.Format(L"-service \"SMS\" -to \"%s\"", (const WCHAR*)sNumber);
    sheci.lpParameters =  (const WCHAR*)sParam;

    ShellExecuteEx(&sheci);
}
