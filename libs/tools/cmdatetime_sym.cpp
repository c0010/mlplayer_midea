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

#include <tz.h>
#include <tzconverter.h>

CMDateTime::CMDateTime()
{
	m_dtLocal.HomeTime();
}

BOOL CMDateTime::Parse(CMString sDateTime)
{
	m_dtLocal.Parse(TPtrC((const TUint16*)(const WCHAR*)sDateTime));
	return TRUE;
}

CMString CMDateTime::toString()
{
	TBuf<32> theTime;
	_LIT(KFormatTxt,"%/0%1%/1%2%/2%3%/3 %-B%:0%J%:1%T%:2%S%:3%+B");
	m_dtLocal.FormatL(theTime,KFormatTxt); 

	return (const WCHAR*)theTime.PtrZ();
}

INT32 CMDateTime::getTime()
{
	TTime aTime(m_dtLocal);
    RTz tzServer;
    User::LeaveIfError(tzServer.Connect());
    CleanupClosePushL(tzServer);
    CTzConverter* tzConverter = CTzConverter::NewL(tzServer);
    CleanupStack::PushL(tzConverter);
    tzConverter->ConvertToUniversalTime(aTime);
    CleanupStack::PopAndDestroy(2);

	_LIT(s1970, "19700101:000000.000000");
	TTime t1970(s1970);
	TTimeIntervalSeconds secondfrom1970;
	aTime.SecondsFrom(t1970, secondfrom1970);
	return secondfrom1970.Int();
}
