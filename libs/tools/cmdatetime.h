// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmsetting.h
//  Description: Provides the functionality of read and write system setting.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMDATETIME_H_HEADER_INCLUDED_B58D4B11
#define CMDATETIME_H_HEADER_INCLUDED_B58D4B11

#include "cmstring.h"
//#include <CFDate.h>

class CMDateTime
{
  public:
    CMDateTime();

    ~CMDateTime();

	BOOL		Parse(CMString sDateTime);

	CMString	toString();

	//Return the time as seconds elapsed since midnight, January 1, 1970, Coordinated Universal Time (UTC).
	INT32		getTime();

private:
#if defined(PLAT_WINCE)
	SYSTEMTIME m_dtLocal;
#elif defined(PLAT_SYMBIAN)
	TTime m_dtLocal;
#elif defined(PLAT_IOS)
	double m_dtSystem;
#endif
};



#endif /* CMDATETIME_H_HEADER_INCLUDED_B58D4B11 */
