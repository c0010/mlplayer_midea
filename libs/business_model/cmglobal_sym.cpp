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
#include "cmversion.h"

//#include <aknappui.h>
#include <APGCLI.H>
#include <sendui.h> 
#include <txtrich.h>
#include <senduiconsts.h>
#include <cmessagedata.h>
#include <EIKENV.H>

CMSystemInfo& CMGlobal::SystemInfo()
{
	if (m_pSystemInfo != NULL)
    {
        return *m_pSystemInfo;
    }
	m_pSystemInfo = new CMSystemInfo();

	TSize size(240, 320);
    CWsScreenDevice* screen = CCoeEnv::Static()->ScreenDevice(); 
    if (screen) 
    {
        TPoint pt(1440,1440);
        TPoint ptPixel = screen->TwipsToPixels(pt);
        TInt mode = screen->CurrentScreenMode(); 
        TPixelsTwipsAndRotation sizeAndRotation; 
        screen->GetScreenModeSizeAndRotation(mode, sizeAndRotation); 
        size = sizeAndRotation.iPixelSize;
    }
    m_pSystemInfo->ScreenWidth = size.iWidth;
    m_pSystemInfo->ScreenHeight = size.iHeight;
    
    CMVersion& sysVer = CMVersion::SystemVersion();
    if(sysVer.Platform == 21 || (sysVer.Platform == 22 && sysVer.Major == 3 && sysVer.Minor == 0))
        strcpy(m_pSystemInfo->AcceptType, "text/html,text/vnd.wap.wml,video/3mv,audio/3ma,audio/aac");
    else
        strcpy(m_pSystemInfo->AcceptType, "text/html,text/vnd.wap.wml,video/3mv,audio/3ma,audio/aac,application/x-shockwave-flash");

    return *m_pSystemInfo;
}


void CMGlobal::OpenDocument(CMString sDocument)
{
    HBufC* parameter = HBufC::NewLC(260); 
    parameter->Des().Copy( (const TUint16*)(const WCHAR*)sDocument ); 
    RApaLsSession appArcSession; 
    User::LeaveIfError(appArcSession.Connect()); 
    TThreadId id;
    appArcSession.StartDocument( *parameter,  id );
    appArcSession.Close();
    CleanupStack::PopAndDestroy();
}


//打电话
void CMGlobal::MakeCall(const CMString& sNumber)
{
#ifndef __WINSCW__ //真实设备 This only works on target machine
    if (m_pCall)
        SAFEDELETE(m_pCall);

    TPtrC ptc((const TUint16*)(const WCHAR*)sNumber);
    m_pCall = CCallDialer::NewL(this, ptc);

#else //模拟器 Return a fake IMEI when working onemulator
#endif
}

//发短信
void CMGlobal::OpenSMSG(const CMString& sNumber)
{
//    _LIT(KAddress, "07738123456");
//    _LIT(KAlias, "Sam");
//    _LIT(KBodyData, "This is the message body");
//    _LIT(KSubject, "This is the subject");
    TPtrC sAddr((const TUint16*)(const WCHAR*)sNumber);
     
    CSendUi* sendAppUi = CSendUi::NewLC();
    CMessageData* message = CMessageData::NewLC();
    CRichText* richText = CRichText::NewL(CEikonEnv::Static()->SystemParaFormatLayerL(),
            CEikonEnv::Static()->SystemCharFormatLayerL());
    CleanupStack::PushL(richText);

//    // Add an address
//    // Note, there are also options for the CC address 
//    // and Bcc adress used in email
//    message->AppendToAddressL(KAddress, KAlias);
//     
//    // Add a subject line
//    message->SetSubjectL(&KSubject);
//    richText->InsertL(0, KBodyData);
    
    message->AppendToAddressL(sAddr);    
    message->SetBodyTextL(richText);            
    sendAppUi->CreateAndSendMessageL(KSenduiMtmSmsUid, message, KNullUid, ETrue);
     
    CleanupStack::PopAndDestroy(3);
}

void CMGlobal::CallDialedL(TInt aError)
{
    SAFEDELETE(m_pCall);
}
