// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmgeneral.h"
#include "cmglobal.h"
#include "utf8ncpy.h"
#include "cmfile.h"
#include "cmpath.h"
#include "cmdbhelper.h"
CMGeneral::CMGeneral()
{
	m_pNewUrl = NULL;
}

CMGeneral::~CMGeneral()
{
	if(m_pNewUrl)
	{
		delete[] m_pNewUrl;
		m_pNewUrl = NULL;
	}
}

const char* CMGeneral::FormatUrlBySID(const char* sOrgUrl)
{
	if(!sOrgUrl)
		return NULL;
	if(m_pNewUrl)
	{
		delete[] m_pNewUrl;
		m_pNewUrl = NULL;
	}

	int size = strlen(sOrgUrl) + 100; //足够放下sid
	m_pNewUrl = new char[size];

	if (strstr(sOrgUrl, "sid=") == NULL)
    {
        CMString sID;
        if (CMGlobal::TheOne().GetSessionID(sID))
        {

            if (strstr(sOrgUrl, "?") == NULL)
            	snprintf(m_pNewUrl, size, "%s?sid=%s", sOrgUrl, (const char*)sID);
            else
            	snprintf(m_pNewUrl, size, "%s&sid=%s", sOrgUrl, (const char*)sID);

            return m_pNewUrl;
		}
    }


	utf8ncpy(m_pNewUrl, sOrgUrl, size-1);

	return m_pNewUrl;
}

BOOL CMGeneral::ResetPasswordEnabled()
{
#if RESET_PASSWORD
	return TRUE;
#else
	return FALSE;
#endif
}

BOOL CMGeneral::IsOffline()
{
	return CMGlobal::TheOne().IsOffline();
}

BOOL CMGeneral::ClearCache()
{
	return CMDBHelper::GetInstance(1)->ClearCacheTable();
}

BOOL CMGeneral::IsSidExist()
{
	CMString str="";
	return CMGlobal::TheOne().GetSessionID(str);
}

void CMGeneral::setOffline(BOOL off){
	CMGlobal::TheOne().SetOffline(off);
}

