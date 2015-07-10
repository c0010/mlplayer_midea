//
//  cmstring_iph.m
//  iphone
//
//  Created by luo on 11-4-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "stdafx.h"
#include "cmstring.h"
#include <string.h>
#include <wchar.h>
//#include <stdlib.h>
/*
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
*/
//
INT32 _mwtoi(const WCHAR* s)
{
	UINT32 nLen = wcslen(s);
	INT32 nRet = 0;
	UINT32 nCount = 1;
	while (nLen-- > 0)
	{
		WCHAR c = s[nLen];
		if (c > L'9' || c < L'0')
		{
			if (c == L'-' && nLen == 0)
				nRet = -nRet;
			else
				nRet = 0;

			return nRet;
		}
		nRet += (c - L'0') * nCount;
		nCount *= 10;
	}
	return nRet;
}
//INT64  _mwtol(const WCHAR* s)
//{
//  	return wcstol(s,NULL,10);
//}
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

	ASSERT(sizeof(wchar_t) == 4);
	 if (src == NULL)
		 return FALSE;
	 
	 wchar_t codepoint = 0;
	 int following = 0;
	 int pos = 0;
	 for (src;  *src != 0;  ++src)
	 {
		 if (len-- <= 0)
		 {
			 dest[pos] = L'\0';
			 break;
		 }

		 unsigned char ch = *src;
		 if (ch <= 0x7f)
		 {
			 codepoint = ch;
			 following = 0;
		 }
		 else if (ch <= 0xbf)
		 {
			 if (following > 0)
			 {
				 codepoint = (codepoint << 6) | (ch & 0x3f);
				 --following;
			 }
		 }
		 else if (ch <= 0xdf)
		 {
			 codepoint = ch & 0x1f;
			 following = 1;
		 }
		 else if (ch <= 0xef)
		 {
			 codepoint = ch & 0x0f;
			 following = 2;
		 }
		 else
		 {
			 codepoint = ch & 0x07;
			 following = 3;
		 }
		 if (following == 0)
		 {
			 dest[pos++] = codepoint;
			 codepoint = 0;
		 }
	 }
	 return TRUE;

}
//
// FuncName:
// Description: uincode转utf8
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态
BOOL ConvertUnicodeToUtf8(const WCHAR *src,CHAR*dest,INT32 len)
{

    ASSERT(sizeof(wchar_t) >= 4);
    //std::string out;
    if (src == NULL)
        return FALSE;
	int pos = 0;
    for (src;  *src != 0;  ++src)
    {
		 if (len-- <= 0)
		 {
			 dest[pos] = '\0';
			 break;
		 }

		 unsigned int codepoint = *src;
		
        if (codepoint <= 0x7f)
            dest[pos++] = char(codepoint);
        else if (codepoint <= 0x7ff)
        {
            dest[pos++] = char(0xc0 | ((codepoint >> 6) & 0x1f));
            dest[pos++] = char(0x80 | (codepoint & 0x3f));
        }
        else if (codepoint <= 0xffff)
        {
            dest[pos++] = char(0xe0 | ((codepoint >> 12) & 0x0f));
            dest[pos++] = char(0x80 | ((codepoint >> 6) & 0x3f));
            dest[pos++] = char(0x80 | (codepoint & 0x3f));
        }
        else
        {
            dest[pos++] = char(0xf0 | ((codepoint >> 18) & 0x07));
            dest[pos++] = char(0x80 | ((codepoint >> 12) & 0x3f));
            dest[pos++] = char(0x80 | ((codepoint >> 6) & 0x3f));
            dest[pos++] = char(0x80 | (codepoint & 0x3f));
        }
    }
	return TRUE;
}
BOOL ConvertUtf8ToUnicode(const CHAR* src, INT32 srcLen, WCHAR* dest, INT32 dstLen)
{
	return ConvertUtf8ToUnicode(src, dest, dstLen);
}
