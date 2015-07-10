// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:网络Http层拨号管理类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

//当前模块是网络模块
#define FILE_MOD CM_LOGM_NET


#include "stdafx.h"

#include "cmnetworkmgr.h"

CMNetConnMgr& CMNetConnMgr::Instance()
{
    static CMNetConnMgr mgr;
    return mgr;
}

