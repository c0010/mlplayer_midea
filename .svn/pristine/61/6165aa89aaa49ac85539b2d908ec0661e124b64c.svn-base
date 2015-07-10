// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmversion.h
//  Description: Provides the functionality of a mutex.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMVERSION_H_HEADER_INCLUDED_B5C11131
#define CMVERSION_H_HEADER_INCLUDED_B5C11131

class CMVersion
{
  public:
    CMVersion();

    ~CMVersion();

	static CMVersion& SystemVersion();

	UINT32 Platform;
	UINT32 Major;
	UINT32 Minor;
	UINT32 Build;

private:
	static CMVersion* m_pSystemVersion;
	
	UINT32 GetPlatID();
};

#endif /* CMVERSION_H_HEADER_INCLUDED_B5C11131 */
