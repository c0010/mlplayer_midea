// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmrecentcontent.h"
#include "cmsession.h"

CMRecentContent::CMRecentContent(IMUpdateDataListener* pListener)
:CMContenthandler()
{
	m_nPageSize = 30;
    SetListener(pListener, NULL);
}


CMRecentContent::~CMRecentContent()
{
}

BOOL CMRecentContent::Update()
{
	SetPaging(TRUE);
	return CMContenthandler::Request(SERVICE_GETRECENTCONTENT, "");
}

