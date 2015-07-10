// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
#ifndef __CMCODEC__H__
#define __CMCODEC__H__



typedef struct _MDecData{
    UINT8* data[4];
    INT32  size[4];
}MDecData;

const UINT16 CODECID_NONE = 0;
const UINT16 CODECID_H264 = 1;
const UINT16 CODECID_AMRNB = 2;
const UINT16 CODECID_AAC = 3;


class IMCodec
{
public:
    virtual BOOL Start() = 0;
    virtual BOOL Close() = 0;

    //out的含义根据解码器不同而不同
    //返回值是使用了in的多少byte。0表示数据不够，-1表示解码错误
    virtual INT32 Decode(INT8* in, INT32 size, MDecData& out) = 0;
};

class CMCodecFactory
{
public:

	static CMCodecFactory* GetInstance();

	IMCodec*   Create(UINT32 type);
private:

    CMCodecFactory();

    ~CMCodecFactory();
    
	static CMCodecFactory* m_pTHIS;
};


#endif
