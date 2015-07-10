// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#ifndef __BASE_H__
#define __BASE_H__

#if defined(_WIN32_WCE)
//平台类型wince
#define PLAT_WINCE
#if defined(WIN32_PLATFORM_WFSP)
//编译版本ce smartphone
#define PLAT_CESP
#define PLAT_ID      12
#elif defined(WIN32_PLATFORM_PSPC)
//编译版本ce pocketpc
#define PLAT_CEPPC
#define PLAT_ID      11 
#else
#define PLAT_ID      13 
#define WIN32_PLATFORM_PSPC
#define WINCE_OTHER
//#error Unknown ce platform
#endif
#elif defined(__SYMBIAN32__)
//平台类型symbian
#define PLAT_SYMBIAN
#if defined(__SERIES60_2X__)
//编译版本symbian2版
#define PLAT_SYMBIAN2
#define PLAT_ID      21
#elif defined(__SERIES60_3X__) && !defined(__S60_50__)
//编译版本symbian3版
#define PLAT_SYMBIAN3
#define PLAT_ID      22
#elif defined(__S60_50__)
#define PLAT_SYMBIAN5
#define PLAT_ID      23
#else
#error Unknown symbian platform
#endif
#elif defined(__IPHONE_OS__)
#define PLAT_IOS
//#define PLAT_ID		44 //动态获取((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) ? 44 : 45)
#elif defined(ANDROID)
#define PLAT_AND
//#define PLAT_ID      33//从java层动态获取
#else
#error Unsupport platform
#endif

//全局定义
#if defined(PLAT_WINCE)
//库的头文件控制宏，windows有用
#ifdef PF_EXPORTS
#define P1_PAPI __declspec(dllexport)
#else
#define P1_PAPI __declspec(dllimport)
#endif
#endif

//常量单字节字串到双字节字串的预定义宏
//#ifndef TEXT
//#define TEXT(a) L ## a
//#endif

////修改symbian断言定义
//#if defined(PLAT_SYMBIAN) && defined(ASSERT)
//#undef ASSERT
//#define ASSERT(x) (void)((x)||(p,0))
//#endif

#if defined(DrawText)
#undef DrawText
#endif

//#if defined(SetWindowText)
//#undef SetWindowText
//#endif

//断言
#if defined(PLAT_IOS) || defined(PLAT_AND)
#ifdef _DEBUG
#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(exp)  {if (!(exp))  {CM_LOG(CM_LOGL_CRIT, "ASSERT FALSE"); exit(-1);}}
#else
#ifndef ASSERT
#define ASSERT(exp)
#endif
#endif
#endif

//NULL的定义
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#if defined(_DEBUG)
#define UNUSED(v)  v
#else
#define UNUSED(v)
#endif

#define SAFEDELETE(x) if(x){delete x;x=NULL;}
#define SAFECLOSE(x) if(x){x.Close();}
#define SAFERELEASE(x) if(x){x.Release();}

#if defined(PLAT_IOS) || defined(PLAT_AND)
#define TRUE  1
#define FALSE 0
#define MAX_PATH 260
#endif

#if defined(PLAT_SYMBIAN) || defined(PLAT_IOS)
#define _stricmp strcasecmp
#endif

//类型定义
typedef unsigned char   UINT8;
typedef char            CHAR;
typedef float           FLOAT;
typedef double          DOUBLE;

#if defined(PLAT_WINCE)
typedef wchar_t          WCHAR;
typedef short            INT16;
typedef unsigned short   UINT16;
typedef int              INT32;
typedef unsigned int     UINT32;

#elif defined(PLAT_SYMBIAN)
#include <string.h>
#include <e32def.h>
typedef void  			 VOID;
typedef char             INT8;
typedef wchar_t          WCHAR;
typedef TInt16           INT16;
typedef TUint16          UINT16;
typedef TInt             INT32;
typedef TUint32          UINT32;
typedef int              BOOL;
#if defined(PLAT_SYMBIAN2)
	typedef long long           INT64;
	typedef unsigned long long  UINT64;
#else 
	typedef __int64             INT64;
	typedef TUint64             UINT64;
#endif
//typedef unsigned int   UINT;
typedef INT32            INT;
#define	INT_MAX 0x7fffffff
#elif defined(PLAT_IOS) || defined(PLAT_AND)

typedef void  			 VOID;
typedef wchar_t          WCHAR;
typedef char             INT8;
typedef short            INT16;
typedef unsigned short   UINT16;
typedef int              INT32;

#if defined(__LP64__)
typedef unsigned long    UINT32;
#else
typedef unsigned int     UINT32;
#endif

/// Type to represent a boolean value.
#if !defined(OBJC_BOOL_DEFINED)
#if defined(__LP64__)
typedef bool BOOL;
#else
typedef signed char BOOL;
#endif
#endif

typedef long long           INT64;
typedef unsigned long long  UINT64;

#if !defined(_PTRDIFF_T)
#define _PTRDIFF_T
typedef int              ptrdiff_t;
#endif
#if !defined(INT_MAX)
#define	INT_MAX 0x7fffffff
#endif
#endif //类型定义结束

#endif //__BASE_H__
