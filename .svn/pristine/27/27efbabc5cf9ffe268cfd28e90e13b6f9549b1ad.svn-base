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
	m_dtSystem = CFAbsoluteTimeGetCurrent();
}

BOOL CMDateTime::Parse(CMString sDateTime)
{
	int year = 1970;
	int month = 1;
	int day = 1;
	int hour = 0;
	int minute = 0;
	int second = 0;

	char time[100] = {0};
	strcpy(time, sDateTime);
	sscanf(time, "%04d-%02d-%02d %02d:%02d:%02d",&year, &month, &day,
		&hour, &minute, &second);
	
	CFGregorianDate date;	
	date.year = year;
	date.month = month;
	date.day = day;
	date.hour = hour;
	date.minute = minute;
	date.second = second;
	
	m_dtSystem = CFGregorianDateGetAbsoluteTime(date, CFTimeZoneCopySystem());

	return TRUE;
}

CMString CMDateTime::toString()
{
	CFGregorianDate date;
	date = CFAbsoluteTimeGetGregorianDate(m_dtSystem, CFTimeZoneCopySystem());

	CMString sDateTime;
	sDateTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d", (int)date.year, (int)date.month, (int)date.day,
		(int)date.hour, (int)date.minute, (int)date.second);
	return sDateTime;
}

INT32 CMDateTime::getTime()
{
	return (int)(m_dtSystem + kCFAbsoluteTimeIntervalSince1970);
}
