#ifndef __STDAFX_H__
#define __STDAFX_H__
/*
 * Copyright (c) 2009,
 * All rights reserved.
 * 
 * FileName:stdafx.h
 * Description:预编译头文件，所有cpp的公共包含文件。
 *             包括类型定义，平台适配，全局定义等信息
 * Author:roy
 */

#include "base.h"

//平台相关定义
#if defined(PLAT_WINCE)
#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

// 注意 - 这个值与作为目标的 Windows CE OS 版本的关联性并不强
#define WINVER _WIN32_WCE

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define SHELL_AYGSHELL
#endif

#ifdef _CE_DCOM
#define _ATL_APARTMENT_THREADED
#endif

#include <aygshell.h>
#include <tpcshell.h>
#pragma comment(lib, "aygshell.lib") 


// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#include "DeviceResolutionAware.h"
#endif

#if _WIN32_WCE < 0x500 && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
	#pragma comment(lib, "ccrtrtti.lib")
	#ifdef _X86_	
		#if defined(_DEBUG)
			#pragma comment(lib, "libcmtx86d.lib")
		#else
			#pragma comment(lib, "libcmtx86.lib")
		#endif
	#endif
#endif

#include <altcecrt.h>
#include <atlbase.h>  
#include <atlcom.h>
#include <atlwin.h>
#include <atlctl.h>
#endif

#ifdef PLAT_SYMBIAN
    #include <f32file.h>
    #include <e32std.h>
    #include <e32base.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//配置
#include "config.h"
//版本
//#include "version.h"

//日志
#include "cmlog.h"

#if defined(PLAT_AND) || defined(PLAT_IOS)
#define USE_CURL 1
#endif

#endif
