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
#include "cmnetwork.h"
#include "cmsettings.h"
#include "Reachability.h"
#include "utf8ncpy.h"

//#include <phone.h>

UINT32 CMGlobal::GetTickCount()
{
    return 0;
}

void CMGlobal::OpenDocument(CMString sDocument)
{
}

//打电话
//void CMGlobal::MakeCall(const CMString& sNumber)
//{
//}

//发短信
//void CMGlobal::OpenSMSG(const CMString& sNumber)
//{
//}

void CMGlobal::ChangeDesktopPrompt(int nNewMsgPrompt)
{
}
CMSystemInfo& CMGlobal::SystemInfo()
{
	if (m_pSystemInfo != NULL)
    {
        return *m_pSystemInfo;        
    }
	float f_scale = 1.0;
	UIScreen* screen = [UIScreen mainScreen];
	if ([screen respondsToSelector:@selector(scale)]) {
		f_scale = [screen scale];
	}

	
	CGRect rc = [screen bounds];
	m_pSystemInfo = new CMSystemInfo;
	m_pSystemInfo->ScreenWidth = rc.size.width * f_scale;
	m_pSystemInfo->ScreenHeight = rc.size.height * f_scale;
    
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    NSArray *langArr = [userDefault objectForKey:@"AppleLanguages"];
    
    if ([langArr count] > 0)
    {
        strcpy(m_pSystemInfo->CurrLang, [[langArr objectAtIndex:0] UTF8String]);
    }
    else
    {
        utf8ncpy(m_pSystemInfo->CurrLang, "zh-Hans", 19);
    }
    utf8ncpy(m_pSystemInfo->AcceptType, "text/html,text/vnd.wap.wml,video/3mv,audio/3ma,audio/aac", 199);

	return *m_pSystemInfo;
}

void CMGlobal::Sleep(UINT32 intevel)
{
	[NSThread sleepForTimeInterval:(intevel / 1000.0)];
}

BOOL CMGlobal::IsExistNetwork()
{
    BOOL isExist = NO;
    
    Reachability *reach = [Reachability reachabilityForInternetConnection];
    
    switch ([reach currentReachabilityStatus])
    {
        case NotReachable:
        {
            isExist = NO;
            break;
        }
        case ReachableViaWiFi:	
        {
            isExist = YES;
            break;
        }
        case ReachableViaWWAN:
        {
            isExist =YES;
            break;
        }
        default:
            break;
    }
    
    return isExist;
}
