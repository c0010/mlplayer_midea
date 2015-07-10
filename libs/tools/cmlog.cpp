// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmlog.h"

#include "cmfile.h"
#include "cmpath.h"
#include "cmdatetime.h"
#include "cmmutex.h"
#if defined(PLAT_AND)
#include <stdarg.h>
#include <android/log.h>
#endif


static CMLogger* g_logger = NULL;

CMLogger::CMLogger()
{

#if defined(PLAT_AND)
	//android 直接使用logcat
	m_logtype = CM_LOGT_CONSOLE;
	m_loglvl = CM_LOGL_TRACE;
#else
	m_logtype = CM_LOGT_FILE;
	m_loglvl  = CM_LOGL_ERR;
#endif
	m_logmod  = CM_LOGM_ALL;
	m_logfile = NULL;
    m_pMutex = new CMMutex;
}

CMLogger::~CMLogger(void)
{
	if (m_logfile)
	{
		m_logfile->Close();
		delete m_logfile;
	}

    SAFEDELETE(m_pMutex);
}

void CMLogger::Release()
{
    if(g_logger)
    {
        delete g_logger;
        g_logger = NULL;
    }
}

CMLogger* CMLogger::GetLogger()
{
	if (!g_logger)
		g_logger = new CMLogger;
	return g_logger;
}

void CMLogger::Log(LOG_LVL lvl, UINT32 line, FILNAME_TYPE pathname, const CHAR* fmt, ...)
{
    m_pMutex->Lock();

#if defined(PLAT_AND)
	if (m_logtype != CM_LOGT_FILE)
	{
		va_list arglist;
		va_start(arglist, fmt);

		int prio = ANDROID_LOG_ERROR;
		switch (lvl)
		{
		case CM_LOGL_TRACE:
			prio = ANDROID_LOG_VERBOSE;
			break;
		case CM_LOGL_DEBUG:
			prio = ANDROID_LOG_DEBUG;
			break;
		case CM_LOGL_INFO:
			prio = ANDROID_LOG_INFO;
			break;
		case CM_LOGL_WARNING:
			prio = ANDROID_LOG_WARN;
			break;
		case CM_LOGL_ERR:
			prio = ANDROID_LOG_ERROR;
			break;
		case CM_LOGL_CRIT:
			prio = ANDROID_LOG_ERROR;
			break;
		}

		CHAR sTmp[CM_LOG_MAX_LINE+1];
		CHAR* pTmp = sTmp;
		snprintf(pTmp, CM_LOG_MAX_LINE, "FN:%s FL:%d :::", pathname, line);
		pTmp = pTmp + strlen(pTmp);
		vsnprintf(pTmp, CM_LOG_MAX_LINE - (pTmp - sTmp) - 1, fmt, arglist);
		pTmp = pTmp + strlen(pTmp);
		pTmp[0] = '\0';
		va_end(arglist);

		__android_log_print(prio, "mlplayer-jni", "%s", sTmp);

		m_pMutex->UnLock();
		return;
	}
#endif
    //生成log内容
	//样例 LT:FN:.\MLPlayer.cpp FL:32 :::main start
	va_list arglist;
	va_start(arglist, fmt);
	CHAR sTmp[CM_LOG_MAX_LINE];
	CHAR* pTmp = sTmp;

	pTmp[0] = 'L';
	switch (lvl)
	{
	case CM_LOGL_TRACE:
		pTmp[1] = 'T';
		break;
	case CM_LOGL_DEBUG:
		pTmp[1] = 'D';
		break;		
	case CM_LOGL_INFO:
		pTmp[1] = 'I';
		break;
	case CM_LOGL_WARNING:
		pTmp[1] = 'W';
		break;
	case CM_LOGL_ERR:
		pTmp[1] = 'E';
		break;
	case CM_LOGL_CRIT:
		pTmp[1] = 'C';
		break;	
	}
	pTmp[2] = ':';
	pTmp = pTmp + 3;
	CMDateTime dt;
	snprintf(pTmp, CM_LOG_MAX_LINE - 5, "TM:%u FN:%s FL:%d :::", dt.getTime(), pathname, line);

	pTmp = pTmp + strlen(pTmp);
	vsnprintf(pTmp, CM_LOG_MAX_LINE - (pTmp - sTmp) - 2, fmt, arglist);

	pTmp = pTmp + strlen(pTmp);
	pTmp[0] = '\n';
	pTmp[1] = '\0';

	ASSERT(pTmp + 2 - sTmp <= CM_LOG_MAX_LINE);

	va_end(arglist);
    
#if defined(PLAT_IOS)
    if(m_logtype != CM_LOGT_FILE)
    {
        IPHLogColor(sTmp, lvl);
        m_pMutex->UnLock();

        return;
    }
#endif

	Output(sTmp);
    m_pMutex->UnLock();
}

void CMLogger::Dump(LOG_LVL lvl, UINT32 line, FILNAME_TYPE pathname, INT8* mem, UINT32 len)
{
    m_pMutex->Lock();

    //生成log内容
	char sTmp[CM_LOG_MAX_LINE];
	CHAR* pTmp = sTmp;

	pTmp[0] = 'L';
	switch (lvl)
	{
	case CM_LOGL_TRACE:
		pTmp[1] = 'T';
		break;
	case CM_LOGL_DEBUG:
		pTmp[1] = 'D';
		break;		
	case CM_LOGL_INFO:
		pTmp[1] = 'I';
		break;
	case CM_LOGL_WARNING:
		pTmp[1] = 'W';
		break;
	case CM_LOGL_ERR:
		pTmp[1] = 'E';
		break;
	case CM_LOGL_CRIT:
		pTmp[1] = 'C';
		break;	
	}
	pTmp[2] = ':';
	pTmp = sTmp + 3;
	snprintf(pTmp, CM_LOG_MAX_LINE, "FN:%s FL:%d DUMP:%0x LEN:%d", pathname, line, (UINT32)mem, len);

	Output(sTmp);

	INT8* pMem = mem;

	UINT32 i;
	for (i = 0; i < len; i++)
	{
		if (i % 8 == 0)
		{
			if (i != 0)
			{
				//初始化完一行
				pTmp[0] = '\0';
				Output(sTmp);
			}
			pTmp = sTmp;
			pTmp[0] = '\n';
			pTmp[1] = '\t';
			pTmp += 2;
		}
		CHAR c[3];
		sprintf(c, "%02x", (UINT8)(*pMem));
		pMem++;
		pTmp[0] = c[0];
		pTmp[1] = c[1];
		pTmp[2] = ' ';
		pTmp += 3;
	}

	//最后行没有输出，输出先
    pTmp[0] = '\n';
	pTmp[1] = '\0';
	Output(sTmp);

    m_pMutex->UnLock();
}

void CMLogger::Output(const CHAR* s)
{
	//输出log
	switch (m_logtype)
	{
	case CM_LOGT_FILE:
	{
		//如果是文件方式，检查log文件
		if (!m_logfile)
		{
			m_logfile = new CMFile();
            CMPath path(CMPath::WSYS_PATH);

            if (!m_logfile->Open((path.String() + L"a.txt"), CMFile::CREATE_W, CMFile::SHARE_R))
			{
				//此处写法仅做调试时使用
				ASSERT(FALSE);
				return;
			}
			m_logfile->Seek(0, CMFile::FILESEEK_END);
		}

		m_logfile->Write((CHAR*)s, strlen(s));
		break;		
	}
	case CM_LOGT_CONSOLE:
	case CM_LOGT_DEBUGER:
	case CM_LOGT_SCREEN:
	default:
	{
#if defined(PLAT_WINCE)	    
		WCHAR wsTmp[CM_LOG_MAX_LINE];
		ConvertAnsiToUnicode(s, wsTmp, CM_LOG_MAX_LINE);
		OutputDebugString(wsTmp);
#elif defined(PLAT_SYMBIAN)
		printf(s);
#elif defined(PLAT_IOS)
		IPHLog("%s", s);
#elif defined(PLAT_AND)
		ASSERT(FALSE);  //错误分支
#endif
	}
	}
}
