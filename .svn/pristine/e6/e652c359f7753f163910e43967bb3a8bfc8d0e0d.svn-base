#include "stdafx.h"
#include "cmstring.h"
#include <CHARCONV.H>
#include <UTF.H>
CMString& CMString::Format(const WCHAR *fmt,...)
{
    ASSERT(fmt!=NULL);

    VA_LIST va;
    VA_START(va,fmt);
    HBufC *s=HBufC::NewL(1024);
    TPtrC pfmt((const TUint16*)fmt,wcslen(fmt));
    s->Des().AppendFormatList(pfmt,va);
    VA_END(va);
    if(m_sData)
    {
        delete []m_sData;
        m_sData = NULL;
    }
    m_sData=new WCHAR[s->Length()+1];
    ASSERT(m_sData!=NULL);
    wcscpy(m_sData,(const WCHAR*)s->Des().PtrZ());
    delete s;
    return *this;
}
INT32 _mwtoi(const WCHAR* s)
{
    int val=0;
    TLex lex;
    lex.Assign((const TUint16*)s);
    lex.Val(val);
    return val;
}
INT64  _mwtol(const WCHAR* s)
{
    INT64 val=0;
    TLex lex;
    lex.Assign((const TUint16*)s);
    lex.Val(val);
    return val;      
}
// FuncName:
// Description:整形按进制形式输出字串
// Variables:val 整数, s 输出字串,  radix 进制 :EDecimal 10  EHex 16 EHex 8 EBinary 2
// Return: 转出字串
WCHAR* _mitow(INT32 val,WCHAR* s,INT32 radix)
{
    TBuf<30> buf;
    int rex=EDecimal;
    if (radix==16) {
        rex=EHex;
    }else if (radix==8) {
        rex=EOctal;
    }else if (radix==2) {
        rex=EBinary;
    }
    buf.AppendNum(val,rex);
    const wchar_t* res=(const wchar_t*)buf.PtrZ();
    if (wcscpy(s,res)) 
        return s;
    else  
        return NULL;
}
// FuncName:
// Description: ansi转unicode
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertAnsiToUnicode(const CHAR *src,WCHAR*dest,INT32 len)
{
    CCnvCharacterSetConverter * m_CharConv =  CCnvCharacterSetConverter::NewL();
    RFs m_RFsObstacle;
    m_RFsObstacle.Connect();
    if(m_CharConv->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk, m_RFsObstacle)!=CCnvCharacterSetConverter::EAvailable)
    {
        delete m_CharConv;
        m_RFsObstacle.Close();
        User::Leave(KErrNotSupported); //KCharacterSetIdentifierGb2312
    }

    INT32  state=CCnvCharacterSetConverter::KStateDefault; 
    TPtrC8 psrc((UINT8*)src,strlen(src)); 
    TPtr   pdest((UINT16*)dest,len);
    if(m_CharConv->ConvertToUnicode(pdest, psrc, state)==CCnvCharacterSetConverter::EErrorIllFormedInput)
    {
        delete m_CharConv;
        m_RFsObstacle.Close();
        return FALSE;
    }
    delete m_CharConv;
    m_RFsObstacle.Close();
    return TRUE;
}
// FuncName:
// Description: unicode转ansi
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUnicodeToAnsi(const WCHAR *src,CHAR*dest,INT32 len)
{
    CCnvCharacterSetConverter * m_CharConv =  CCnvCharacterSetConverter::NewL();
    RFs m_RFsObstacle;
    m_RFsObstacle.Connect();
    if(m_CharConv->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk, m_RFsObstacle)!=CCnvCharacterSetConverter::EAvailable)
    {
        delete m_CharConv;
        m_RFsObstacle.Close();        
        User::Leave(KErrNotSupported);
    }
    TPtr8 pdest((UINT8*)dest,len);
    TPtrC psrc ((UINT16*)src,wcslen(src)); 
    INT32 state=CCnvCharacterSetConverter::KStateDefault ;
    if(m_CharConv->ConvertFromUnicode(pdest,psrc,state)==CCnvCharacterSetConverter::EErrorIllFormedInput)
    {
        delete m_CharConv;
        m_RFsObstacle.Close(); 
        return FALSE;
    }
    delete m_CharConv;
    m_RFsObstacle.Close(); 
    return TRUE;            
}
// FuncName:
// Description: utf8转unicode
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUtf8ToUnicode(const CHAR *src,WCHAR*dest,INT32 len)
{
    TPtrC8 psrc((UINT8*)src,strlen(src));
    TPtr  pdest((UINT16*)dest,len);
    if(CnvUtfConverter::ConvertToUnicodeFromUtf8(pdest,psrc)==CnvUtfConverter::EErrorIllFormedInput)
        return FALSE;
    return TRUE;
    }
//
// FuncName:
// Description: uincode转utf8
// Variables: src ansi字串 ,dest unicode字串 ,len dest长度
// Return:状态 
BOOL ConvertUnicodeToUtf8(const WCHAR *src,CHAR*dest,INT32 len)
{
     TPtr8 pdest((UINT8*)dest,len);
     TPtrC psrc ((UINT16*)src,wcslen(src)); 
     if(CnvUtfConverter::ConvertFromUnicodeToUtf8(pdest,psrc)==CnvUtfConverter::EErrorIllFormedInput)
         return FALSE;
     return TRUE;
    
}

BOOL ConvertUtf8ToUnicode(const CHAR* src, INT32 srcLen, WCHAR* dst, INT32 dstLen)
{
    TPtrC8 psrc((UINT8*)src, srcLen);
    TPtr  pdst((UINT16*)dst, dstLen);
    if(CnvUtfConverter::ConvertToUnicodeFromUtf8(pdst,psrc)==CnvUtfConverter::EErrorIllFormedInput)
        return FALSE;
    dst[dstLen] = L'\0';
    return TRUE;
}
