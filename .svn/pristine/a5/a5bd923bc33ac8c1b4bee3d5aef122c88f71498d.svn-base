// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cmglobal.h"
#include "cmpath.h"
#include "cmfile.h"
//#include "md5.h"
#include "cmsettings.h"
#include "cmdbhelper.h"
#include <openssl/md5.h>
#ifdef PLAT_SYMBIAN
#include <aknenv.h>
#endif

CMGlobal* g_cGlobal = NULL;

CMGlobal::CMGlobal()
{
#ifdef PLAT_WINCE
    m_pHttpS = NULL;
#endif
	m_pSystemInfo = NULL;
	m_bUserChange = FALSE;
	m_bOffline = FALSE;
}
void CMGlobal::Release()
{
    SAFEDELETE(g_cGlobal);
}
CMGlobal::~CMGlobal()
{
#ifdef PLAT_WINCE
    //SAFEDELETE(m_pHttpS);
#endif
	SAFEDELETE(m_pSystemInfo);
}

CMGlobal& CMGlobal::TheOne()
{
    if (g_cGlobal != NULL)
    {
        return *g_cGlobal;
    }
    
    g_cGlobal = new CMGlobal();
    return *g_cGlobal;
}

BOOL CMGlobal::GetSessionID(CMString& sID)
{
    if (m_sID.IsEmpty())
    {
    	m_sID = CMSettings::GetInstance()->GetSID();
    }

    if (m_sID.IsEmpty())
    		return FALSE;

    sID = m_sID;
    return TRUE;
}

void CMGlobal::SetSessionID(const CMString& sID)
{
    m_sID = sID;
}

CMString CMGlobal::GetUpdateUrl()
{
	return m_sUpdateUrl;
}

void CMGlobal::SetUpdateUrl(CMString sUpdateUrl)
{
	m_sUpdateUrl = sUpdateUrl;
}

CMString CMGlobal::EncryptPass(const CHAR* src)
{
#if ENCRYPT_PASSWORD
    char digest[33] = {0};
    
    MD5_CTX ctx;
    
    unsigned char md5[17]={0};
    
    MD5_Init(&ctx);
    
    MD5_Update(&ctx, src, strlen(src));
    
    MD5_Final(md5, &ctx);
    

	//MD5Init(&ctx , 0);

    //MD5Update (&ctx, (unsigned char *)src, strlen(src));

	//MD5Final (&ctx) ;

    for(INT32 i = 0;i < 16;i++)
        snprintf(digest, 33,"%s%02X", digest, md5[i]);

    CMString ret(digest);

	return ret.Mid(1, 30);
#else
	return src;
#endif
}

BOOL CMGlobal::ClearCache()
{
	//清除内容列表缓冲文件
    
    
    if(CMFile::DeleteFileList(CMPath(CMPath::TEMP_PATH).String()) && CMDBHelper::GetInstance(1)->ClearCacheTable())
        return true;
    else
        return false;
	//清除浏览器缓冲（平台相关，暂不实现）
}

CMString CMGlobal::GetRootDir()
{
    CMPath pPath(CMPath::DATA_PATH);
    
	CMString sPath = pPath.String();
    
    return pPath.String();

}

CMString CMGlobal::GetUserDir()
{
	CMPath pPath(CMPath::DATA_PATH);
        
	CMString sPath = pPath.String();
	CMString sID;
    BOOL ret = FALSE;
    
    if (CMGlobal::TheOne().IsOffline())
    {
        ret=TRUE;
    }
    else
    {
        ret=GetSessionID(sID);
    }
    
    
	if(ret && CMSettings::GetInstance()->GetUserName())
	{
		sID = CMSettings::GetInstance()->GetCustomer();
        sID += FILESEPARATOR;
        if (!pPath.AddDir(sID))
        	return "";
        sID = CMSettings::GetInstance()->GetUserName();
		sID += FILESEPARATOR;
		if(!pPath.AddDir(sID))
			return "";
	}	
	return pPath.String();
}
CHAR* CMGlobal::Encode(const CHAR* sIn/* = NULL*/)
{
	if(sIn == NULL && strlen(sIn) <= 0)
		return NULL;

	INT32 nInLen = strlen(sIn);
	INT32 nOutLen = nInLen*3+1;
	CHAR* st = new CHAR[nOutLen];
	CHAR* sOut = st;
	memset(st,0,nOutLen);

    char sTmp[4];
    for (INT32 i = 0; i < nInLen; i++)
    {
        switch (*sIn)
        {
        case '\r':
        	*sOut++ = '%';
            *sOut++ = '0';
            *sOut   = 'D';
        	break;
        case '\n':
        	*sOut++ = '%';
            *sOut++ = '0';
            *sOut   = 'A';
        	break;
        case ' ':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = '0';
            break;
		case '<':
            *sOut++ = '%';
            *sOut++ = '3';
            *sOut   = 'C';
            break;
		case '>':
            *sOut++ = '%';
            *sOut++ = '3';
            *sOut   = 'E';
            break;
		 case '.':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = 'E';
            break;
		 case '#':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = '3';
            break;
		 case '{':
            *sOut++ = '%';
            *sOut++ = '7';
            *sOut   = 'B';
            break;
		 case '}':
            *sOut++ = '%';
            *sOut++ = '7';
            *sOut   = 'D';
            break;
		case '|':
            *sOut++ = '%';
            *sOut++ = '7';
            *sOut   = 'C';
            break;
			case '\\':
            *sOut++ = '%';
            *sOut++ = '5';
            *sOut   = 'C';
            break;
		case '^':
            *sOut++ = '%';
            *sOut++ = '5';
            *sOut   = 'E';
            break;
		 case '~':
            *sOut++ = '%';
            *sOut++ = '7';
            *sOut   = 'E';
            break;
		 case '[':
            *sOut++ = '%';
            *sOut++ = '5';
            *sOut   = 'B';
            break;
		case ']':
            *sOut++ = '%';
            *sOut++ = '5';
            *sOut   = 'D';
            break;
		case '`':
            *sOut++ = '%';
            *sOut++ = '6';
            *sOut   = '0';
            break;
		case '+':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = 'B';
            break;
		case '/':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = 'F';
            break;
		case '?':
            *sOut++ = '%';
            *sOut++ = '3';
            *sOut   = 'F';
            break;
		case '&':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = '6';
            break;
        case '%':
            *sOut++ = '%';
            *sOut++ = '2';
            *sOut   = '5';
            break;
//        case '@':
//            *sOut++ = '%';
//            *sOut++ = '4';
//            *sOut   = '0';
//            break;
        case '=':
            *sOut++ = '%';
            *sOut++ = '3';
            *sOut   = 'd';
            break;
        default:
            if ((UINT8)(*sIn) > 127)
            {
                snprintf(sTmp, 4,"%%%.2X", (UINT8)(*sIn));
                *sOut++ = sTmp[0];
                *sOut++ = sTmp[1];
                *sOut   = sTmp[2];
            }
            else 
                *sOut = *sIn;
        }
        sIn++;
        sOut++;
    }

    *sOut = L'\0';
    return st;
}

//是否离线登录
BOOL CMGlobal::IsOffline()
{
	return m_bOffline;
}

BOOL CMGlobal::SetOffline(BOOL off)
{
	m_bOffline = off;
}

