// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:h264 解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#if !defined(__CMCODECAVC__H__)
#define __CMCODECAVC__H__

#include "cmcodec.h"
#if defined(PLAT_SYMBIAN) || defined(PLAT_WINCE)
#ifdef __cplusplus
extern "C" {
#endif
#include "avc/portab.h"
#include "avc/mem.h"
#include "avc/buffer.h"
#include "avc/node.h"
#include "avc/video.h"
#include "avc/flow.h"
#include "avc/codec.h"
#include "avc/err.h"

#ifdef __cplusplus
}
#endif

struct codec;

#elif defined(PLAT_IOS) || defined(PLAT_AND)

class AVCodecContext;
class AVFrame;

#endif


class CMAVCCodec : public IMCodec
{
public:
    CMAVCCodec();
    virtual ~CMAVCCodec();

    virtual BOOL Start();
    virtual BOOL Close();
    
    virtual INT32 Decode(INT8* in, INT32 size, MDecData& out);

private:
#if defined(PLAT_SYMBIAN) || defined(PLAT_WINCE)
    codec*         m_pCodec;
    pin            m_inPin;
    pin            m_outPin;
    //packetprocess  m_outProcess;
    packetformat   m_inFormat;
#elif defined(PLAT_IOS) || defined(PLAT_AND)
	AVCodecContext*    cdc;
	AVFrame*           frm;
#endif
};

#endif
