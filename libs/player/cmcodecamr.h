// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:amr音频解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#if !defined(__CMCODECAMR__H__)
#define __CMCODECAMR__H__

#include "cmcodec.h"

class CMAMRCodec : public IMCodec
{
public:
    CMAMRCodec();
    virtual ~CMAMRCodec();

    virtual BOOL Start();
    virtual BOOL Close();
    
    //out里面data[0]如果有指针，则直接使用，否则内部new内存出来，调用者释放
    virtual INT32 Decode(INT8* in, INT32 size, MDecData& out);

private:
    INT32* m_pState;
};

#endif
