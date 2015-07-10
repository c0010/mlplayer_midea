//
//  cmstring_iph.m
//  iphone
//
//  Created by luo on 11-4-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "stdafx.h"
#include "cmstring.h"
#import <string.h>
#import <wchar.h>
//#import <xlocale/_wchar.h>

CMString& CMString::Format(const WCHAR *fmt,...)
{
 ASSERT(fmt!=NULL && wcslen(fmt) > 2);
    if(m_sData)
    {
        delete []m_sData;
        m_sData = NULL;
    }
	int fmtlen = wcslen(fmt); 
	WCHAR *cpyfmt  = new WCHAR[fmtlen +1];
	ASSERT(cpyfmt != NULL);
	wcscpy(cpyfmt,fmt);
	for(int i = 0; i<fmtlen;i++)
	{
		if(cpyfmt[i] == L's')
		{
			if(i > 0)
				if(cpyfmt[i-1] == L'%')
					cpyfmt[i] = L'S';
		}
	}
	va_list va;
    va_start(va, cpyfmt);
    INT32 len = 1023;	//vwprintf(NULL,fmt,va);
    m_sData = new WCHAR[len+1];
	memset(m_sData,0,sizeof(WCHAR)*(len+1));
    ASSERT(m_sData!=NULL);
    vswprintf(m_sData,1023,cpyfmt,va);
	len = wcslen(m_sData);
	if(len < 512)
	{
		WCHAR *pstr = new WCHAR[len+1];
		if(pstr)
		{
			wcscpy(pstr,m_sData);
			delete []m_sData;
			m_sData = pstr;
		}
	}
    va_end(va);
	delete[]cpyfmt;
	cpyfmt = NULL;
    return *this;
}
INT32 _mwtoi(const WCHAR* s)
{
	return wcstol(s,NULL,10);
}
INT64  _mwtol(const WCHAR* s)
{
  	return wcstoll(s,NULL,10);
}
// FuncName:
// Description:整形按进制形式输出字串
// Variables:val 整数, s 输出字串,  radix 进制 :EDecimal 10  EHex 16 EHex 8 EBinary 2
// Return: 转出字串
WCHAR* _mitow(INT32 val,WCHAR* s,INT32 radix)
{
   return NULL;
}

// FuncName:
// Description: ansi转unicode
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertAnsiToUnicode(const CHAR *src,WCHAR*dest,INT32 len)
{
    return ConvertUtf8ToUnicode(src, dest, len);
}
// FuncName:
// Description: unicode转ansi
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUnicodeToAnsi(const WCHAR *src,CHAR*dest,INT32 len)
{
	return ConvertUnicodeToUtf8(src, dest, len);
}

// FuncName:
// Description: utf8转unicode
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUtf8ToUnicode(const CHAR *src,WCHAR*dest,INT32 len)
{
	ASSERT(dest != NULL);
	NSString *pNs = [NSString stringWithUTF8String:src];
    //pNs = [pNs stringByReplacingCharactersInRange:NSMakeRange(len-1, (pNs.length - len)+1) withString:@""];
    if(!pNs)
		return FALSE;
	//	if(![pNs getBytes:(void *)dest maxLength:dstLen*sizeof(WCHAR) usedLength:NULL encoding:NSUTF32StringEncoding])
	//		return FALSE;
	len = len*sizeof(WCHAR);
	memset(dest, 0, len);
	return [pNs getCString:(char*)dest maxLength:len encoding:NSUTF32LittleEndianStringEncoding];
}
//
// FuncName:
// Description: uincode转utf8
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUnicodeToUtf8(const WCHAR *src,CHAR*dest,INT32 len)
{
	ASSERT(dest != NULL);
	NSString *pNs = [[NSString alloc] initWithBytes:src length:sizeof(WCHAR)*wcslen(src) encoding:NSUTF32LittleEndianStringEncoding];
	//NSString *pNs = [NSString stringWithCString:(const char *)src encoding:NSUTF32StringEncoding];
	//NSLog(@"&&&&&&&&&&&%@&&&&&&&&&&",pNs);
	if(pNs)
	{
		const char * pTmp = [pNs UTF8String];
		if(pTmp && len > strlen(pTmp))
		{
			memcpy(dest,pTmp,strlen(pTmp));
			[pNs release];
			return TRUE;
		}
		else
			[pNs release];
	}	
	return FALSE;
}
BOOL ConvertUtf8ToUnicode(const CHAR* src, INT32 srcLen, WCHAR* dest, INT32 dstLen)
{
	return ConvertUtf8ToUnicode(src, dest, dstLen);
}