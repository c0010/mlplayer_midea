// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:aac音频解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#if !defined(__CMCODECAAC__H__)
#define __CMCODECAAC__H__

#include "cmcodec.h"
#include "cmfile.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "faad/common.h"
#include "faad/structs.h"
#include "faad/decoder.h"
#ifdef __cplusplus
}
#endif

const int adts_sample_rates[] = {96000,88200,64000,48000,44100,32000,24000,22050,16000,12000,11025,8000,7350,0,0,0};

class CMAACCodec : public IMCodec
{
public:
    CMAACCodec();
    virtual ~CMAACCodec();

    virtual BOOL Start();
    virtual BOOL Close();
    
    //out里面data[0]如果有指针，则直接使用，否则内部new内存出来，调用者释放
    virtual INT32 Decode(INT8* in, INT32 size, MDecData& out);

private:
    NeAACDecHandle m_hDecoder;
    NeAACDecFrameInfo m_frameInfo;

    BOOL              m_bInit;
};

#endif
