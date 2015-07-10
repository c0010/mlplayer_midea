// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:h264 解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cmcodecavc.h"



int process(void* This, const packet* Data, const flowstate* State)
{
    return 0;
}

CMAVCCodec::CMAVCCodec()
{
    m_pCodec = NULL;
}

CMAVCCodec::~CMAVCCodec()
{
    Close();
}

BOOL CMAVCCodec::Start()
{
#if !defined(__WINSCW__)
    if (m_pCodec)
    {
        NodeDelete((node*)m_pCodec);
        m_pCodec = NULL;
    }
    memset(&m_inPin, 0, sizeof(pin));
    memset(&m_outPin, 0, sizeof(pin));
    memset(&m_inFormat, 0, sizeof(packetformat));

    m_pCodec = (codec*)NodeCreate(FOURCC('A','V','C','_'));

    if(m_pCodec)
    {
        m_pCodec->Node.Set(m_pCodec, CODEC_INPUT, &m_inPin, sizeof(pin));
        m_pCodec->Node.Set(m_pCodec, CODEC_OUTPUT, &m_outPin, sizeof(pin));
        m_pCodec->Node.Set(m_pCodec, CODEC_OUTPUT|PIN_PROCESS, (void*)process, sizeof(packetprocess));
        m_pCodec->Node.Set(m_pCodec, CODEC_INPUT|PIN_FORMAT, &m_inFormat, sizeof(packetformat));
        return TRUE;
    }
    else
        return FALSE;
#else
    return TRUE;
#endif
}

BOOL CMAVCCodec::Close()
{
#if !defined(__WINSCW__)
    if (m_pCodec)
    {
        NodeDelete((node*)m_pCodec);
        m_pCodec = NULL;
    }
#endif
    
    return TRUE;
}
    
INT32 CMAVCCodec::Decode(INT8* in, INT32 size, MDecData& out)
{
#if !defined(__WINSCW__)    
    if(m_pCodec)
    {
        INT32 nRet = -1;

        if(in)
        {
            packet pk = {0};
            flowstate fs = {0};

            fs.CurrTime = 0;// CMGlobal::TheOne().GetTickCount();
            pk.Data[0] = in;
            pk.Length = size;
            nRet = m_pCodec->Process(m_pCodec, &pk, &fs);
        }
        else
            nRet = m_pCodec->Process(m_pCodec, NULL, NULL);

        if (nRet == 0)
        {
            out.data[0] = (UINT8*)m_pCodec->Packet.Data[0];
            out.data[1] = (UINT8*)m_pCodec->Packet.Data[1];
            out.data[2] = (UINT8*)m_pCodec->Packet.Data[2];
            out.size[0] = m_pCodec->Out.Format.Format.Video.Pitch;
            out.size[1] = m_pCodec->Out.Format.Format.Video.Pitch/2;
            out.size[2] = m_pCodec->Out.Format.Format.Video.Pitch/2;
            return size;
        }
        else if(nRet == ERR_INVALID_DATA || nRet == ERR_NEED_MORE_DATA)
            return 0;
        else
            return -1;
    }
    else
        return -1;
#else
    return size;
#endif
}
