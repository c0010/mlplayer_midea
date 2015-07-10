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

#ifdef PLAT_SYMBIAN
    #include <BAUTILS.H>
    #include<COEMAIN.H>
    #include<EIKENV.H>
    #include<EIKAPPUI.H>
    #include<EIKAPP.H>
    #include <pathinfo.h>
#else
#include<stdio.h>
#include<projects.h>
#endif

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
   //     case CONF_PATH://用户配置文件路径
   //     {
   //     #ifdef PLAT_SYMBIAN
   //         TBuf<256> sApp;
   //         CCoeEnv::Static()->FsSession().PrivatePath(sApp);
   //         #ifdef __WINSCW__
   //         sApp.Insert( 0, _L("C:") );
   //         #else
   //         sApp.Insert( 0, CEikonEnv::Static()->EikAppUi()->Application()->AppFullName().Left(2) );
   //         #endif
   //         m_sPath =(const WCHAR*)sApp.PtrZ();
   //         BaflUtils::EnsurePathExistsL(CCoeEnv::Static()->FsSession(), sApp);
   //     #else
			//WCHAR sApp[256]=L"0";
			//::GetModuleFileName(NULL, sApp, 256);
			//for(INT32 i=wcslen(sApp)-1;i>0;i--)
			//{
			//	if(sApp[i]==L'\\')
			//	{
			//		sApp[i+1]=L'\0';
			//		break;
			//	}
			//}
			//m_sPath = sApp;
   //     #endif
   //         //CMString sID;
   //         //if(CMGlobal::TheOne().GetSessionID(sID) && !(SETTING.m_sName.IsEmpty()))
   //         //    AddDir(SETTING.m_sName + L"\\");
   //         break;
   //     }
        case SYS_CONF_PATH://系统配置文件路径
        case DATA_PATH://数据路径
		case APP_PATH:
        {
        #ifdef PLAT_SYMBIAN
            TBuf<256> sApp;
            CCoeEnv::Static()->FsSession().PrivatePath(sApp);
            #ifdef __WINSCW__
            sApp.Insert( 0, _L("C:") );
            #else
            sApp.Insert( 0, CEikonEnv::Static()->EikAppUi()->Application()->AppFullName().Left(2) );
            #endif
            m_sPath =(const WCHAR*)sApp.PtrZ();
            BaflUtils::EnsurePathExistsL(CCoeEnv::Static()->FsSession(), sApp);
        #else
			WCHAR sApp[256]=L"0";
			::GetModuleFileName(NULL, sApp, 256);
			for(INT32 i=wcslen(sApp)-1;i>0;i--)
			{
				if(sApp[i]==L'\\')
				{
					sApp[i+1]=L'\0';
					break;
				}
			}
			m_sPath = sApp;
        #endif
            break;
        }
		case TEMP_PATH:
		{
			m_sPath = CMPath::CMPath(DATA_PATH).String();
			CMString stmp = L"tmp";
			stmp += FILESEPARATOR;
			AddDir(stmp);
			break;
		}
		case DOWNLOAD_PATH:
		{
			m_sPath = CMPath::CMPath(CARD_PATH).String();
			if(!m_sPath.IsEmpty())
			{
				CMString stmp = L"download";
				stmp += FILESEPARATOR;
				AddDir(stmp);
			}
			break;
		}
        case CARD_PATH://存储卡根目录
        {
        #ifdef PLAT_SYMBIAN
            TBuf<30> mmcPath;
            mmcPath=PathInfo::MemoryCardRootPath();
            RFs iFs2;
            User::LeaveIfError(iFs2.Connect());
            if (iFs2.CheckDisk(mmcPath) == KErrNone)
                m_sPath =(const WCHAR*)mmcPath.PtrZ();
            else
            	m_sPath = CMPath::CMPath(DATA_PATH).String();
        #else
			HANDLE hFlashCard; 
			WIN32_FIND_DATA lpwfdFlashCard; 
			hFlashCard = FindFirstFlashCard(&lpwfdFlashCard);
			if (hFlashCard != INVALID_HANDLE_VALUE)
			{
				if(lpwfdFlashCard.cFileName[0] != '\\')
					m_sPath = L"\\";
				m_sPath += lpwfdFlashCard.cFileName;
				if(m_sPath[m_sPath.GetLength()-1] != '\\')
					m_sPath += L"\\";
			}
			else
				m_sPath = CMPath::CMPath(DATA_PATH).String();
			FindClose (hFlashCard); // Close the search handle.
        #endif
            break;
        }
        case WSYS_PATH://系统盘根目录
        {
            #ifdef PLAT_SYMBIAN 
                m_sPath = L"c:\\";
            #else
                m_sPath = L"\\";
            #endif
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
    const WCHAR* spath=strPath;
#ifdef PLAT_SYMBIAN
    TPtrC ptr((const TUint16*)spath,strPath.GetLength());
    BaflUtils::EnsurePathExistsL(CCoeEnv::Static()->FsSession(), ptr);
    if(BaflUtils::PathExists(CCoeEnv::Static()->FsSession(), ptr)==EFalse)
       return FALSE;
#else
	if(CreateDirectory(spath,NULL)==0)
	{
		if(::GetLastError()==ERROR_PATH_NOT_FOUND)
			return FALSE;
	}
#endif
    m_sPath = strPath;
	return TRUE;
}

BOOL CMPath::PathExist(const CMString& sPathName)
{
    CMString str = sPathName;
#ifdef PLAT_SYMBIAN
     TPtrC ptr((const TUint16*)str.GetBuffer(),str.GetLength());
    if(BaflUtils::PathExists(CCoeEnv::Static()->FsSession(), ptr)==EFalse)  
        return FALSE;
#else
	::WIN32_FIND_DATA fd;
	HANDLE hd=::FindFirstFile(str,&fd);
	if(hd==INVALID_HANDLE_VALUE)
		return FALSE;
	::CloseHandle(hd);
#endif
    return TRUE;
}

const CMString& CMPath::String()
{
    return m_sPath;
}

CMPath::DRV_TYPE CMPath::DriverType()
{
    return CMPath::CARD;
}
