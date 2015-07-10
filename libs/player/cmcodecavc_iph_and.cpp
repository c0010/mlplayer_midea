// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:h264 解码实现
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
//#include "cmglobal.h"
#include "cmcodecavc.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#include "libavutil/common.h"
#include "libavcodec/avcodec.h"

#ifdef __cplusplus
}
#endif

CMAVCCodec::CMAVCCodec()
{
    cdc = NULL;
	frm = NULL;
	avcodec_init();
	avcodec_register_all();
}

CMAVCCodec::~CMAVCCodec()
{
	if (cdc) {
		avcodec_close(cdc);
		av_free(cdc);
		cdc = NULL;
	}
	if (frm) {
		av_free(frm);
		frm = NULL;
	}
}

BOOL CMAVCCodec::Start()
{
	if (cdc) {
		avcodec_close(cdc);
		av_free(cdc);
		cdc = NULL;
	}
	if (frm) {
		av_free(frm);
		frm = NULL;
	}
	
	AVCodec* codec = avcodec_find_decoder(CODEC_ID_H264);
	
	if (!codec) {
		return FALSE;
	}
	
	//allocate codec context
	cdc = avcodec_alloc_context();
	
	if(!cdc){
		return FALSE;
	}
	//open codec
	if (avcodec_open(cdc, codec) < 0) {
		return FALSE;
	}
	
	//allocate frame buffer
	frm = avcodec_alloc_frame();
	if(!frm){
		return FALSE;
	}

	
	
    return TRUE;
}

BOOL CMAVCCodec::Close()
{

    
    return TRUE;
}
    
INT32 CMAVCCodec::Decode(INT8* in, INT32 size, MDecData& out)
{
	INT8* pData = NULL;
	UINT32 nRet = 0;
	int got_picture = 0;
	
	if (cdc == NULL || frm == NULL)
	{
		CM_ERR("Maybe Open failed, Context null, can't play");
		return 0;
	}
	
	// get the pointer for the audio data from the java array
	//decode
	
	pData = in;
	if (pData == NULL)
	{
		nRet = -1;
		goto end;
	}
	
	nRet = avcodec_decode_video(cdc, frm, &got_picture, (UINT8*)pData, size);
	
	//CM_LOGP(CM_LOGL_INFO, "Decode return %d", nRet);
	if (got_picture > 0)
	{
		out.data[0] = (UINT8*)frm->data[0];
		out.data[1] = (UINT8*)frm->data[1];
		out.data[2] = (UINT8*)frm->data[2];
		out.size[0] = frm->linesize[0];
		out.size[1] = frm->linesize[1];
		out.size[2] = frm->linesize[2];
		
		
		nRet = size;
	}
	else
	{
		CM_LOGP(CM_LOGL_WARNING, "decode failed, %d", nRet);
		out.size[0] = 0;
		nRet = size;
	}
	
end:

	return nRet;

}
