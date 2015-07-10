// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cmcodec.h"
#include "cmcodecavc.h"
#include "cmcodecamr.h"
#include "cmcodecaac.h"

#if defined(PLAT_SYMBIAN) || defined(PLAT_WINCE)
#ifdef __cplusplus
extern "C" {
#endif
#include "avc/context.h"
#ifdef __cplusplus
}
#endif
#endif

CMCodecFactory* CMCodecFactory::m_pTHIS = NULL;

CMCodecFactory* CMCodecFactory::GetInstance()
{
	if(!m_pTHIS)
		m_pTHIS = new CMCodecFactory();
	return m_pTHIS;
}
CMCodecFactory::CMCodecFactory()
{
#if defined(PLAT_SYMBIAN) || defined(PLAT_WINCE)
#if !defined(__WINSCW__)
    INT32 Id = 3;
    Context_Init(L"TCPMP", L"0.72RC1", Id, NULL, NULL);
#endif
#endif
}

CMCodecFactory::~CMCodecFactory()
{
#if defined(PLAT_SYMBIAN) || defined(PLAT_WINCE)
#if !defined(__WINSCW__)
    Context_Done();
#endif
#endif
}

IMCodec*   CMCodecFactory::Create(UINT32 type)
{
    IMCodec* pNew = NULL;
    switch (type)
    {
    case CODECID_H264:
        pNew = new CMAVCCodec;
        break;
    case CODECID_AMRNB:
        pNew = new CMAMRCodec;
        break;
	case CODECID_AAC:
		pNew = new CMAACCodec;
		break;
    default:
        break;
    }

    return pNew;
}
