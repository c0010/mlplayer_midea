// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: 
//  Description: 字符串处理类
//  Author: Tim
// //////////////////////////////////////////////////////////////////////////////
#ifndef CMSTRING_H_HEADER_INCLUDED_B5C8C1C3
#define CMSTRING_H_HEADER_INCLUDED_B5C8C1C3

#if defined(PLAT_AND)
#include <wchar.h>
extern size_t wcslen_and (const wchar_t *s);
extern int wcscmp_and (const wchar_t *s1, const wchar_t *s2);
extern wchar_t *wcscpy_and(wchar_t *dest, const wchar_t *src);
extern wchar_t *wcscat_and(wchar_t *dest, const wchar_t *src);
#define wcslen wcslen_and
#define wcscmp wcscmp_and
#define wcscpy wcscpy_and
#define wcscat wcscat_and
#endif


class CMString
{
  public:
	CMString();
	~CMString();	
	CMString(const WCHAR *s);
	CMString(const CMString &str);
	CMString(const CHAR*s);
    CMString(const CHAR* s,UINT32 nLen);
	CMString& operator=(CHAR *s);
	CMString& operator=(const CMString &str);
	CMString& operator=(const WCHAR *s);
	CMString  operator+(const CMString &str) const;
	CMString  operator+(const WCHAR *s) const;
	//CMString& operator+(INT32 size);
	CMString& operator+=(const CMString &str);
	CMString& operator+=(const WCHAR *s);
	WCHAR     operator[](INT32 index);
    CMString  Left(INT32 count) const;
    CMString  Right(INT32 count) const;
    CMString  Mid(INT32 start) const;//start开始的后面所有字符
    CMString  Mid(INT32 start,INT32 count) const;//start开始的后面count个字符
    CMString& MakeUpper();
    CMString& MakeLower();
    CMString& TrimRight(WCHAR ch = L' ');
    CMString& TrimLeft(WCHAR ch = L' ');
    CMString& Trim(WCHAR ch = L' ');
    CMString& Format(const WCHAR* fmt,...);
    INT32     GetLength() const;
    INT32     Find(const WCHAR *s, INT32 start = 0) const;
    INT32     ReverseFind(const WCHAR *s) const;
    BOOL operator==(const CMString &str) const;//区分大小写
    BOOL operator==(const WCHAR* str) const;//区分大小写
    BOOL operator!=(const CMString&str) const; //区分大小写
    BOOL operator!=(const WCHAR* str) const;//区分大小写
    BOOL operator<(const CMString &str) const; //区分大小写
    BOOL operator<=(const CMString &str) const; //区分大小写
    BOOL operator>(const CMString &str) const; //区分大小写
    BOOL operator>=(const CMString &str) const; //区分大小写
    operator  const WCHAR*()const{return (const WCHAR*)m_sData;};
    WCHAR* GetBuffer(){return (WCHAR*)m_sData;};
    operator  const CHAR*();//强转为CHAR
    BOOL IsEmpty()const;
	VOID Empty(); //清空
private:
    WCHAR  *m_sData;   //宽字字串数据
    CHAR   *m_cdata;   //单字字串数据
};
BOOL ConvertAnsiToUnicode(const CHAR *src,WCHAR *dest,INT32 len);//ansi转unicode
BOOL ConvertUnicodeToAnsi(const WCHAR *src,CHAR *dest,INT32 len);//unicode转ansi
BOOL ConvertUtf8ToUnicode(const CHAR *src,WCHAR *dest,INT32 len);//utf8转unicode
BOOL ConvertUnicodeToUtf8(const WCHAR *src,CHAR *dest,INT32 len);//uincode转utf8
INT32  _mwtoi(const WCHAR* s);//字串转整形
//INT64  _mwtol(const WCHAR* s);//字串转长整形
WCHAR* _mitow(INT32 val,WCHAR* s,INT32 radix);//整形按进制形式转字符串
INT32 Compare(const CMString &astr,const CMString &bstr);//不区分大小写
INT32 CompareS(const CMString &astr,const CMString &bstr);//区分大小写

BOOL ConvertUtf8ToUnicode(const CHAR* src, INT32 srcLen, WCHAR* dst, INT32 dstLen);//带长度utf8转unicode

#endif /* CMSTRING_H_HEADER_INCLUDED_B5C8C1C3 */
