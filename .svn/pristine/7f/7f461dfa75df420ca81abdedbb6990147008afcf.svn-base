// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description: 文件路径类
//  Author:roy, lss
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmpath.h"
#include "cmfile.h"
#include "../business_model/cmsettings.h"
#import <Foundation/Foundation.h>
#import <sys/xattr.h>

CMPath::CMPath(const CMString& sPathName)
{
    m_sPath = sPathName;
}

CMPath::CMPath(const CMPath& cPath)
{
    m_sPath = cPath.m_sPath;
}

CMPath::CMPath(DEF_TYPE nDefType)
{
    switch(nDefType)
    {
//        case CONF_PATH://用户配置文件路径
//        {
//			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//			NSString *documentsDirectory = [paths objectAtIndex:0];
//			m_sPath = [documentsDirectory UTF8String];
//			m_sPath += L"/";
//			CMString sID;
//            if(CMGlobal::TheOne().GetSessionID(sID) && !(SETTING.m_sName.IsEmpty()))
//                AddDir(SETTING.m_sName + L"/");
//            break;
//        }
        case SYS_CONF_PATH://系统配置文件路径
        case DATA_PATH://数据路径
		{

			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
			NSString *documentsDirectory = [paths objectAtIndex:0];
			m_sPath = [documentsDirectory UTF8String];	
			m_sPath += L"/";
                        AddDir(L"ulp/");

			break;
		}
		case TEMP_PATH:
		{
			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
			NSString *cachesDirectory = [paths objectAtIndex:0];
			m_sPath = [cachesDirectory UTF8String];	
			m_sPath += L"/";
			break;
		}
		case DOWNLOAD_PATH:
		{
			m_sPath = CMPath::CMPath(DATA_PATH).String();
			if(!m_sPath.IsEmpty()) {
				AddDir(L"download/");
 
				const char* filePath = (const CHAR*)m_sPath;
				
				const char* attrName = "com.apple.MobileBackup";
				u_int8_t attrValue = 1;				
				setxattr(filePath, attrName, &attrValue, sizeof(attrValue), 0, 0);
			}
			break;
		}
        case UNZIP_PATH://下载课件解压缩后目录
        {
            m_sPath = CMPath::CMPath(DATA_PATH).String();
			if(!m_sPath.IsEmpty()) {
				AddDir(L"download/courseware/");
                
				const char* filePath = (const CHAR*)m_sPath;
				
				const char* attrName = "com.apple.MobileBackup";
				u_int8_t attrValue = 1;
				setxattr(filePath, attrName, &attrValue, sizeof(attrValue), 0, 0);
			}
			break;
        }
		case APP_PATH:
        {
			m_sPath = [[[NSBundle mainBundle] bundlePath] UTF8String];
			m_sPath += L"/";
            break;
        }
        case CARD_PATH://存储卡根目录
        {
			m_sPath = CMPath::CMPath(DATA_PATH).String();
            break;
        }
        case WSYS_PATH://系统盘根目录
        {
            m_sPath = [NSHomeDirectory() UTF8String];
			m_sPath += L"/";
            break;
        }
        default:
            break;
    }
}

CMPath::~CMPath()
{
}

BOOL CMPath::AddDir(const CMString& sPathName)
{
    CMString strPath=m_sPath+sPathName;

	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString* sPath = [NSString stringWithUTF8String : ((const CHAR*)strPath)];
	if(![fileManager fileExistsAtPath: sPath])
		[fileManager createDirectoryAtPath:sPath withIntermediateDirectories:YES attributes:nil error:nil];

    m_sPath = strPath;
	return TRUE;
}

BOOL CMPath::PathExist(const CMString& sPathName)
{
    CMString str = sPathName;
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString* sPath = [NSString stringWithUTF8String : ((const CHAR*)str)];
	return [fileManager fileExistsAtPath: sPath];
}

const CMString& CMPath::String()
{
    return m_sPath;
}

CMPath::DRV_TYPE CMPath::DriverType()
{
    return CMPath::CARD;
}
