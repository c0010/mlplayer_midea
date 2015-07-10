// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: cmstreambuffer.h
//  Description: Provides the functionality of managing buffer for player.
//  Author: wxp
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSTREAMBUFFER_H_HEADER_INCLUDED_B5C12EBB
#define CMSTREAMBUFFER_H_HEADER_INCLUDED_B5C12EBB

#include "cmmutex.h"

const UINT16 MEDIATYPE_NONE = 0;
const UINT16 MEDIATYPE_VIDEO = 1;
const UINT16 MEDIATYPE_AUDIO = 2;
const UINT16 MEDIATYPE_TEXT = 3;

typedef struct _Med_Info {
    UINT16	len;			//文件说明信息的长度
    UINT16	bitRate;		//预设码流，单位kbps
    UINT32	duration;		//片长，单位ms
    //video
    UINT16	vcodec;         //编码格式
    UINT16	fps;			//帧率
    UINT16	weight;			//宽pixel
    UINT16	height;			//高pixel    
    //audio
    UINT16	acodec;			//编码格式
    UINT16  channels;       //声道数
    UINT16	samplerate;		//采样率
    UINT16	samplebit;		//采样大小
    //ext
    UINT16	version;		//文件格式的版本号
    UINT16  extlen;
    UINT8*  extdata;
} Med_Info;

typedef struct _Med_Index{
    UINT32	present_time;   //时间点，单位ms
    UINT32	offset;         //相对文件头的偏移位置，单位byte
}Med_Index;

typedef struct _Med_Packet{
    UINT16	len;			//媒体数据长度，不包括本结构长度
    UINT32  mediatype : 8;  //媒体类型:1 视频， 2 语音
    UINT32  timestamp : 24;	//相对于上一个同类型包的时间戳增量，单位ms    
    UINT8*  data;
}Med_Packet;

class CMStreamBuffer
{
  public:
    CMStreamBuffer();

    ~CMStreamBuffer();

    // 初始化
    BOOL Init(
        // 分配的总缓冲大小
        UINT32 nSize,
        //流的数目
        UINT32 nStreamCount);

    // 得到下一块可写buffer
    Med_Packet* GetWriteBuf(
        // 申请的可写缓冲大小，包括包头在内
        UINT32 nSize);

    // 得到下一个流Buffer
    Med_Packet* GetNextPacket(
        // 流ID：0 无效， 1 视频， 2 语音， 3 字幕
        UINT32 nStreamID);

    // 返回缓冲百分比
    UINT32 GetPercent();

    // 置为Init后状态
    void Reset();

    void WriteFinish(
        // 上一次获取的Buffer地址
        Med_Packet* pBuffer, 
        // 上一次获取的Buffer长度
        UINT32 nLen);

	UINT32 StreamCount(){return m_nStreamCount;};

  private:
    UINT8* m_pData;

    UINT32 m_nSize;

    UINT32 m_nStreamCount;

    UINT32 m_nWritePos;

    UINT32 m_nLockWritePos;

    UINT32 m_nReadPos[3];

    UINT32 m_nLockReadPos[3];

    UINT32 m_nMinReadPos;

    CMMutex m_cMutex;
};



#endif /* CMSTREAMBUFFER_H_HEADER_INCLUDED_B5C12EBB */
