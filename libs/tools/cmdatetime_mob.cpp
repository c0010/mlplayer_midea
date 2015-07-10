// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmdatetime.h"

CMDateTime::CMDateTime()
{
	GetLocalTime(&m_dtLocal);
}

BOOL CMDateTime::Parse(CMString sDateTime)
{
	char time[100] = {0};
	strcpy(time, sDateTime);
	sscanf(time, "%04d-%02d-%02d %02d:%02d:%02d",&m_dtLocal.wYear, &m_dtLocal.wMonth, &m_dtLocal.wDay,
		&m_dtLocal.wHour, &m_dtLocal.wMinute, &m_dtLocal.wSecond);
	m_dtLocal.wMilliseconds = 0;
	m_dtLocal.wDayOfWeek = 7;
	return TRUE;
}

CMString CMDateTime::toString()
{
	CMString sDateTime;
	sDateTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d",m_dtLocal.wYear, m_dtLocal.wMonth, m_dtLocal.wDay,
		m_dtLocal.wHour, m_dtLocal.wMinute, m_dtLocal.wSecond);
	return sDateTime;
}

INT32 CMDateTime::getTime()
{
	FILETIME lf = {0};
	if(SystemTimeToFileTime(&m_dtLocal, &lf))
	{
		FILETIME sft = {0};
		LocalFileTimeToFileTime(&lf, &sft);

		ULARGE_INTEGER e = {sft.dwLowDateTime, sft.dwHighDateTime};
		return (INT32)((e.QuadPart - 0x19DB1DED53E8000)/10000000);
	}
	else
		return 0;
}
