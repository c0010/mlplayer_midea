// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:amr音频解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cmcodecamr.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "amrnb/sp_dec.h"
#include "amrnb/interf_dec.h"
#ifdef __cplusplus
}
#endif

const UINT16 block_size[16]={ 12, 13, 15, 17, 19, 20, 26, 31, 5, 0, 0, 0, 0, 0, 0, 0 };

CMAMRCodec::CMAMRCodec()
{
    m_pState = NULL;
}

CMAMRCodec::~CMAMRCodec()
{
    Close();
}

BOOL CMAMRCodec::Start()
{
    if (m_pState)
    {
        Decoder_Interface_exit(m_pState);
        m_pState = NULL;
    }

    m_pState = (INT32*)Decoder_Interface_init();

    return m_pState != NULL;
}

BOOL CMAMRCodec::Close()
{
    if (m_pState)
    {
        Decoder_Interface_exit(m_pState);
        m_pState = NULL;
    }
    
    return TRUE;
}
    
INT32 CMAMRCodec::Decode(INT8* in, INT32 size, MDecData& out)
{
    INT16* pOut = (INT16*)out.data[0];
    if (pOut == NULL)
    {
        pOut = new INT16[160];
    }
    UINT16 dec_mode = (in[0] >> 3) & 0x000F;
    INT32 read_size = block_size[dec_mode] + 1;

    Decoder_Interface_Decode(m_pState, (UINT8*)in, pOut, 0);

    out.data[0] = (UINT8*)pOut;
    out.size[0] = 320;
    
    return read_size;
}
