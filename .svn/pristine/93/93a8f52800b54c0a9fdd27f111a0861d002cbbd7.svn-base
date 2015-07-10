// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: 
//  Description: 网络播放数据处理类
//  Author: Tim
// //////////////////////////////////////////////////////////////////////////////
#ifndef CMNETDATASOURCE_H_HEADER_INCLUDED_B5B55C04
#define CMNETDATASOURCE_H_HEADER_INCLUDED_B5B55C04
#include "mplayerinterface.h"
#include "cmhttpc.h"
#include "cmtimer.h"
#include "cmfile.h"
class CMStreamBuffer;

//网路数据处理
class CMNetDataSource : public IMNotifyHttpC, public IMNotifyTimer, public IMDataInter
{
  public:

	    CMNetDataSource();
		virtual ~CMNetDataSource();
		virtual BOOL Init(IMDataNotify* pNetworkNotify, CMStreamBuffer* pStreamBuffer);
		virtual BOOL Open(const CMString& sUrl, int mtype);
		virtual BOOL IsRunning(){return m_bRunning;};
		virtual void Start();
		virtual void Stop() ;
		virtual void Seek(UINT32 msec) ;
		virtual void GetHeadInfo(Med_Info& HeadInfo) ;

				//成功读取结果头，或者错误
		virtual void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader) ;
		//完成，缓冲满，或者错误
		virtual void OnRead(UINT32 nCode, INT32 nLen) ;

		void OnTimer(CMTimer &cTimer) ;
private:
	    void RequestData();
		void Reset();
		BOOL VerifyRsp(const CMString& sRsp);
		
public:
		Med_Info              m_nHeadInfo;			//头信息
        Med_Index*            m_pIndex;				//索引
		Med_Packet*           m_pPack;				//数据包
		CMTimer*              m_pTimer;
		CMHttpC*              m_pHttpC;
		IMDataNotify*         m_pNetworkNotify;
        CMStreamBuffer*       m_pStreamBuffer;
private:
		CMString              m_sUrl;
		BOOL                  m_bRunning;
		EMediaType            m_eType;
        BOOL                  m_bHeadComplete;
		UINT32                m_nLength;      //总长度
		UINT32                m_nOnceLen;     //本次可获取长度
		UINT32                m_nCurPos;      //当前位置
		UINT32                m_nCurPackLen;  //当前包长度
		UINT32                m_nRcvPackLen;  //当前包接收长度
		UINT32                m_nIndexCount;  //索引数目
		UINT32                m_nTryTimes;
		UINT32                m_nHttpStatus;
		UINT32                m_nSize;
		INT8*                 m_pHeadBuf;     
		INT8                  m_nPackHead[7]; 

		//CMFile                file;

};

#endif /* CMNETDATASOURCE_H_HEADER_INCLUDED_B5B55C04 */
