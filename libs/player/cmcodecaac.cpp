// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:amr音频解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#define FILE_MOD CM_LOGM_SOUND 
#include "stdafx.h"
#include "cmcodecaac.h"


CMAACCodec::CMAACCodec()
{
    m_hDecoder = NULL;
    m_bInit = FALSE;
}

CMAACCodec::~CMAACCodec()
{
    Close();
}

BOOL CMAACCodec::Start()
{
    if (m_hDecoder)
    {
        NeAACDecClose(m_hDecoder);
        m_hDecoder = NULL;
    }

    m_hDecoder = NeAACDecOpen();
    ASSERT(m_hDecoder != NULL);

    /* Set the default object type and samplerate */
    /* This is useful for RAW AAC files */
    NeAACDecConfigurationPtr config = NeAACDecGetCurrentConfiguration(m_hDecoder);
    config->defSampleRate = 44100;
    config->defObjectType = 2; //LC;  //default
    config->outputFormat = FAAD_FMT_16BIT;
    config->downMatrix = 1;          //maybe 6 to 2
    config->useOldADTSFormat = 0;
    //config->dontUpSampleImplicitSBR = 1;
    NeAACDecSetConfiguration(m_hDecoder, config);

    //重置初始化开关
    m_bInit = FALSE;
    return TRUE;
}

BOOL CMAACCodec::Close()
{
    NeAACDecClose(m_hDecoder);
    
    return TRUE;
}
    
INT32 CMAACCodec::Decode(INT8* in, INT32 size, MDecData& out)
{
    if (!m_bInit)
    {
        int bread = -1;
        uint32_t samplerate = 0;
        uint8_t channels = 0;
        if ((bread = NeAACDecInit(m_hDecoder, (UINT8*)in,
            size, &samplerate, &channels)) < 0)
        {
            /* If some error initializing occured, skip the file */
            CM_ERR("Error initializing decoder library.\n");

            return -1;
        }
        CM_LOGP(CM_LOGL_INFO, "current music samplerate is %d, channels is %d", samplerate, channels);

        m_bInit = TRUE;
    }
    void* sample_buffer = NeAACDecDecode2(m_hDecoder, &m_frameInfo,
        (UINT8*)in, size, (void**)(&out.data[0]), out.size[0]);
    out.data[0] = (UINT8*)sample_buffer;
    out.size[0] = m_frameInfo.samples * 16 / 8; //16bit 2 channel

    if (sample_buffer == NULL)
        return -1;    

    //m_file.Write((CHAR*)in, m_frameInfo.bytesconsumed);
    return m_frameInfo.bytesconsumed;
}
