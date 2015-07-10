#include "stdafx.h"
#include "cmstring.h"
CMString& CMString::Format(const WCHAR *fmt,...)
{
    ASSERT(fmt!=NULL);
    if(m_sData)
    {
        delete []m_sData;
        m_sData = NULL;
    }
    va_list va;
    va_start(va, fmt);
    INT32 len = 1023;//vwprintf(NULL,fmt,va);
    m_sData = new WCHAR[len+1];
    ASSERT(m_sData!=NULL);
    _vsnwprintf(m_sData,1023,fmt,va);
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
    return *this;
}
INT32 _mwtoi(const WCHAR* s)
{
    return _wtoi(s);
}
INT64  _mwtol(const WCHAR* s)
{
    return _wtol(s);
}
// FuncName:
// Description:整形按进制形式输出字串
// Variables:val 整数, s 输出字串,  radix 进制 :EDecimal 10  EHex 16 EHex 8 EBinary 2
// Return: 转出字串
WCHAR* _mitow(INT32 val,WCHAR* s,INT32 radix)
{
    return _itow(val,s,radix);
}
// FuncName:
// Description: ansi转unicode
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertAnsiToUnicode(const CHAR *src,WCHAR*dest,INT32 len)
{
    INT32 width=MultiByteToWideChar(CP_ACP,0,src,-1,NULL,0);   
    if(width>len)
        return FALSE;
    MultiByteToWideChar(CP_ACP,0,src,-1,dest,len);
    return TRUE;
}
// FuncName:
// Description: unicode转ansi
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUnicodeToAnsi(const WCHAR *src,CHAR*dest,INT32 len)
{
    INT32 width=WideCharToMultiByte(CP_ACP,0,src,-1,NULL,0,NULL,NULL);   
     if(width>len)
         return FALSE;
     WideCharToMultiByte(CP_ACP,0,src,-1,dest,len,NULL,NULL);  
    return TRUE;            
}
// FuncName:
// Description: utf8转unicode
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUtf8ToUnicode(const CHAR *src,WCHAR*dest,INT32 len)
{
    INT32 width=MultiByteToWideChar(CP_UTF8,0,src,-1,NULL,0);   
    if(width>len)
        return FALSE;
    MultiByteToWideChar(CP_UTF8,0,src,-1,dest,len);
    return TRUE;
    }
//
// FuncName:
// Description: uincode转utf8
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUnicodeToUtf8(const WCHAR *src,CHAR*dest,INT32 len)
{
    INT32 width=WideCharToMultiByte(CP_UTF8,0,src,-1,NULL,0,NULL,NULL);   
     if(width>len)
         return FALSE;
     WideCharToMultiByte(CP_UTF8,0,src,-1,dest,len,NULL,NULL);  
     return TRUE;
    
}

BOOL ConvertUtf8ToUnicode(const CHAR* src, INT32 srcLen, WCHAR* dst, INT32 dstLen)
{
    INT32 width=MultiByteToWideChar(CP_UTF8,0,src,srcLen,NULL,0);   
    if(width>dstLen)
        return FALSE;
    MultiByteToWideChar(CP_UTF8, 0, src, srcLen, dst, dstLen);
    //补字串末尾\0
    dst[dstLen] = L'\0';
    dst[dstLen] = L'\0';
    return TRUE;
}
