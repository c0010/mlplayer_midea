#include "stdafx.h"
#include "cmnetdatasource.h"
#include "cmnetworkmgr.h"

const UINT32 REQUESTSIZE = 204800; //请求大小

CMNetDataSource::CMNetDataSource()
{
	m_nHeadInfo.extdata = NULL;
	m_pIndex = NULL;
	m_pPack = NULL;
	m_pTimer = NULL;
	m_pHttpC = NULL;
	m_pNetworkNotify = NULL;
	m_pStreamBuffer = NULL;
	m_pHeadBuf = NULL;
	//BOOL bp = file.Open(L"c:\\data\\123.3mv",CMFile::CREATE_W);//c:\\data\\123.3mv
}

CMNetDataSource::~CMNetDataSource()
{
	if(m_pTimer)
	{
		delete m_pTimer;
		m_pTimer = NULL;
	}
	if(m_pHttpC)
	{
		delete m_pHttpC;
		m_pHttpC = NULL;
	}
	

}

BOOL CMNetDataSource::Init(IMDataNotify* pNetworkNotify, CMStreamBuffer* pStreamBuffer)
{
	m_pNetworkNotify = pNetworkNotify ;
	m_pStreamBuffer =  pStreamBuffer ;
	if(!m_pTimer)
		m_pTimer = new CMTimer(this);
    if(m_pHttpC)
		delete m_pHttpC;
	m_pHttpC  = new CMHttpC(this, TRUE);
	return TRUE;
	
}


BOOL CMNetDataSource::Open(const CMString& sUrl, int mtype)
{
	Stop();
	if(sUrl.IsEmpty())
		return FALSE;
	if(mtype != NET_LIVE && mtype != NET_VOD)
		return FALSE;
	m_sUrl = sUrl;
	m_eType = (EMediaType)mtype;
    return TRUE;
}
void CMNetDataSource::Start()
{
	RequestData();
}

void CMNetDataSource::Reset()
{
	m_bRunning  = FALSE;
	if(m_pTimer)
		m_pTimer->Stop();
	if(m_nHeadInfo.extdata)
	{
		delete []m_nHeadInfo.extdata;
		m_nHeadInfo.extdata = NULL;
	}
	if(m_pIndex)
	{
		delete []m_pIndex;
		m_pIndex = NULL;
	}
    if(m_pHeadBuf)
	{
		delete []m_pHeadBuf;
		m_pHeadBuf = NULL;
	}
	if(m_pStreamBuffer)
		m_pStreamBuffer->Reset();
	m_pPack = NULL;
	m_nLength = 0;
	m_nCurPos = 0;
	m_nCurPackLen = 0;
	m_nTryTimes = 0;
	m_nHttpStatus = 0;
	m_nIndexCount = 0;
	m_nRcvPackLen = 0;
	m_nOnceLen = 0 ;
	m_nSize = 0;
	//m_sUrl.Empty();
	m_bHeadComplete = FALSE;
	memset(&m_nHeadInfo,0,sizeof(Med_Info));
	memset(&m_nPackHead,0,sizeof(m_nPackHead));
}
void CMNetDataSource::Stop()
{
    CM_LOG(CM_LOGL_DEBUG, "CMNetDataSource::Stop");
	m_pHttpC->Cancel();
	Reset();
}

void CMNetDataSource::RequestData()
{
	if(m_sUrl.IsEmpty())
		return;
    CM_LOG(CM_LOGL_DEBUG, "CMNetDataSource::RequestData");
    //m_pHttpC->Cancel();

	m_nCurPackLen = 0;
	m_nRcvPackLen = 0;
	m_nOnceLen = 0;
	CMHTTPReqHeader RepHeader;
	//RepHeader.AddValue(m_sVerb,m_sUrl);
	RepHeader.CreateDefault();
   // RepHeader.AddValue(HH_ATYPE, CMString(L"video/*"));
	RepHeader.SetUrl(m_sUrl);
    char sRange[128] = {0,};
	if(m_eType==NET_VOD)
	{
		
        if(CMNetConnMgr::Instance().CurrentType() == CMNetConnMgr::CMWAP
            || m_nHttpStatus == 413)//请求实体过大
		{
			if(m_nLength == 0 || m_nLength-m_nCurPos>REQUESTSIZE)
#if defined(USE_CURL)
				snprintf(sRange,sizeof(sRange),"%d-%d",m_nCurPos,m_nCurPos+REQUESTSIZE-1);
#else
				snprintf(sRange,sizeof(sRange),"bytes = %d-%d",m_nCurPos,m_nCurPos+REQUESTSIZE-1);
#endif
			else
#if defined(USE_CURL)
				snprintf(sRange,sizeof(sRange),"%d-%d",m_nCurPos,m_nLength-1);
#else
				snprintf(sRange,sizeof(sRange),"bytes = %d-%d",m_nCurPos,m_nLength-1);
#endif
		}
		else
#if defined(USE_CURL)
			snprintf(sRange,sizeof(sRange),"%d-",m_nCurPos);
#else
			snprintf(sRange,sizeof(sRange),"bytes = %d-",m_nCurPos);
#endif
	}
	else
#if defined(USE_CURL)
		strcpy(sRange,"0-");
#else
		strcpy(sRange,"bytes = 0-");
#endif
	
	RepHeader.AddValue(HH_RANGER,sRange);
	m_bRunning = TRUE;
    //UINT32 nCount1 = CMGlobal::TheOne().GetTickCount();
	m_pHttpC->Request(RepHeader);
    //UINT32 nCount2 = CMGlobal::TheOne().GetTickCount();
//    if (nCount2 - nCount1 > 5000)
//    {
//        //发送请求超过5秒
//        CM_ERRP("Too snow Request, take %d ms", nCount2 - nCount1);
//    }

}
void CMNetDataSource::Seek(UINT32 msec)
{
	BOOL bFound = FALSE;
	if(m_pIndex)
	{
		for(UINT32 i=0;i<m_nIndexCount;i++)
		{
			if(msec>m_pIndex[i].present_time)
				i++;
			else
			{
				bFound = TRUE;
                m_bRunning  = FALSE;
				m_nCurPos = m_pIndex[i].offset;
				m_nRcvPackLen = 0;
				m_nCurPackLen = 0;
				m_pPack = NULL;
				m_pHttpC->Cancel();
				m_pStreamBuffer->Reset();
				m_pNetworkNotify->OnSeekTime(m_pIndex[i].present_time);
				this->RequestData();
				break;
			}
		}

	}
	if(!bFound && m_pNetworkNotify)
	{
		this->Stop();
		m_pStreamBuffer->Reset();
		m_pNetworkNotify->OnAllCompleted();
	}

}

void CMNetDataSource::GetHeadInfo(Med_Info& HeadInfo)
{
	HeadInfo = m_nHeadInfo;
}
void CMNetDataSource::OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader)
{
    CM_LOGP(CM_LOGL_DEBUG, "CMNetDataSource::OnResponse %u", nCode);

	if(pRespHeader && nCode == MER_OK)
	{
		m_nHttpStatus = pRespHeader->GetHttpReturn();

		CMString sRcv;
		if(m_nHttpStatus == 200||m_nHttpStatus ==206)
		{
			if(pRespHeader->GetValue(HH_CTYPE,sRcv)) //content-type
			{
				if(!VerifyRsp(sRcv))
				{
                    CM_LOG(CM_LOGL_WARNING, "VerifyRsp return false");
					RequestData();
					return;
				}
			}

			if(m_eType == NET_VOD)
			{

				if(!pRespHeader->GetValue(HH_CRANGE,sRcv))
					m_pNetworkNotify->OnError();
				 CM_LOGP(CM_LOGL_DEBUG, "CMNetDataSource::OnResponse  HH_CRANGE%s", (const char*)sRcv);
				INT32 pos = sRcv.ReverseFind(L"/");
				if(pos<0)
					m_pNetworkNotify->OnError();
				if(m_nLength == 0)
					m_nLength = _mwtoi(sRcv.Right(sRcv.GetLength()-pos-1));
				CMString sLeft = sRcv.Left(pos);
				pos = sLeft.ReverseFind(L"-");
				if(pos<0)
					m_pNetworkNotify->OnError();
				UINT32 nAfter = _mwtoi(sLeft.Right(sLeft.GetLength()-pos-1));

				//	
				CMString sFirst = sLeft.Left(pos);
				sFirst.Trim(L' ');
				pos = sFirst.Find(L" ");
				if(pos < 0)
					m_pNetworkNotify->OnError();
				UINT32 nbef =  _mwtoi(sFirst.Right(sFirst.GetLength()-pos-1));
				if(nbef > nAfter)
					m_pNetworkNotify->OnError();

				m_nOnceLen = nAfter - nbef +1;
                CM_LOGP(CM_LOGL_INFO, "CMNetDataSource::OnResponse head success, need read %d data", m_nOnceLen);
			}
			if(!m_bHeadComplete)
			{
				if(!m_pHeadBuf)
				{
					m_pHeadBuf = new INT8[1024];
					memset(m_pHeadBuf,0,1024);
				}
				ASSERT(m_pHeadBuf != NULL);
				m_pHttpC->Read(&m_pHeadBuf[m_nRcvPackLen],1024-m_nRcvPackLen);
			}
			else
			{
				if(m_nRcvPackLen<6)  //当前包头接收
				{
					m_pHttpC->Read(&m_nPackHead[m_nRcvPackLen],6-m_nRcvPackLen);
				}
				else
				{
					if(m_pPack)
						m_pHttpC->Read((INT8*)m_pPack->data + (m_nRcvPackLen-6),m_nCurPackLen-m_nRcvPackLen);
				}
			}
			return;
		}
		else if(m_nHttpStatus == 301|| m_nHttpStatus == 302 ||m_nHttpStatus == 303)
		{
			pRespHeader->GetValue(HH_LOCATION,sRcv);
			m_sUrl = sRcv;
			RequestData();
			return;
		}
		else if(m_nHttpStatus == 413)//请求实体过大
		{
			RequestData();
			return;
		}
        else if(m_nHttpStatus == 404)
        {
            CM_ERR("CMNetDataSource::OnResponse http 404 failed");
            m_pNetworkNotify->OnError();
            return;
        }
	}
//错误处理
    {
        CM_ERRP("CMNetDataSource::OnResponse failed %u, header %0x, http %d", nCode, pRespHeader, m_nHttpStatus);
	    m_nTryTimes++;
	    if(m_nTryTimes>10)
		    m_pNetworkNotify->OnError();
	    else
        {
            m_pHttpC->Cancel();
		    RequestData();
        }
    }
}
BOOL CMNetDataSource::VerifyRsp(const CMString& sRsp)
{
	if(sRsp.Find(L"text/vnd.wap.wml")>=0)
		return FALSE;
	return TRUE;

}

void CMNetDataSource::OnRead(UINT32 nCode, INT32 nLen)
{
//    CM_LOGP(CM_LOGL_DEBUG, "CMNetDataSource::OnRead %u,%d", nCode, nLen);

	if(!IsRunning())
		return;

	if(nCode == MER_OK && nLen > 0)//成功读取数据
	{
		m_nTryTimes = 0;
		m_nRcvPackLen+=nLen;
		if(!m_bHeadComplete)
		{
			if(m_nRcvPackLen>=1024)//头接收完成
			{
				CHAR stemp[5];
				memset(stemp,0,5);
				INT8* str = m_pHeadBuf;
				memcpy(stemp,str,2);
				m_nHeadInfo.len = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.bitRate = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,4);
				m_nHeadInfo.duration = *(UINT32*)stemp;
				memset(stemp,0,5);
				//video
				str += 4;
				memcpy(stemp,str,2);
				m_nHeadInfo.vcodec = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.fps = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.weight = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.height = *(UINT16*)stemp;
				//audio
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.acodec = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.channels = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.samplerate = *(UINT16*)stemp;
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.samplebit = *(UINT16*)stemp;
				//ext
				str += 2;
				memcpy(stemp,str,2);
				m_nHeadInfo.version = *(UINT16*)stemp;
                
				//索引个数
				str = m_pHeadBuf+m_nHeadInfo.len;
				UINT32 pos = m_nHeadInfo.len;
				while(pos<=1024)
				{
					pos += 4;
					if(pos>1024)
						break;
					memcpy(stemp,str,4);
					if(*(UINT32*)stemp == 0)
						break;
					str += 4;

					pos += 4;
					if(pos>1024)
						break;
					memcpy(stemp,str,4);
					if(*(UINT32*)stemp == 0)
						break;
					str += 4;
					m_nIndexCount++;
				}
				
				m_pIndex =new Med_Index[m_nIndexCount];
				ASSERT(m_pIndex != NULL);
				str = m_pHeadBuf+m_nHeadInfo.len;

				for(UINT32 i=0;i<m_nIndexCount;i++)
				{
					memcpy(stemp,str,4);
					m_pIndex[i].present_time = *(UINT32*)stemp;
//					int time = m_pIndex[i].present_time;
					str += 4;
					memcpy(stemp,str,4);
					m_pIndex[i].offset = *(UINT32*)stemp;
//					int off = m_pIndex[i].offset;
					str +=4;
				}
				//file.Write((const char*)m_pHeadBuf,1024);
				delete []m_pHeadBuf;
				m_pHeadBuf = NULL;
				m_nCurPos = 1024;
				m_nOnceLen -= 1024;
				m_nRcvPackLen = 0;
				m_bHeadComplete = TRUE;
				m_pNetworkNotify->OnHeadCompleted(m_nHeadInfo);
				if(!IsRunning())
					return;
				m_pHttpC->Read(m_nPackHead,6);
			}
			else
			{
				//上层不处理,由下层处理
				//m_pHttpC->Read(&m_nHeadBuf[m_nRcvPackLen],1024-m_nRcvPackLen);

			}
		}
		else
		{
			if(m_nRcvPackLen == 6)
			{
				UINT8 st[5];
				memset(st,0,5);
				memcpy(st,m_nPackHead,2);
				m_nCurPackLen = *(UINT16*)st+6;//数据+包头
				if(m_nOnceLen >= m_nCurPackLen)
				{
					memcpy(st,&m_nPackHead[2],4);
					if(!m_pPack)
					{
						m_nSize = m_nCurPackLen-6 + sizeof(Med_Packet);
						m_pPack = m_pStreamBuffer->GetWriteBuf(m_nSize);
					}
					if(m_pPack)
					{		
						m_pPack->len = m_nCurPackLen-6;
						m_pPack->mediatype = st[0];
						m_pPack->timestamp = (UINT32)(st[3]<<16) + (UINT32)(st[2]<<8) + (UINT32)(st[1]);
                        ASSERT(m_pPack->len+sizeof(Med_Packet) == m_nSize);
						m_pHttpC->Read((INT8*)m_pPack->data + (m_nRcvPackLen-6),m_nCurPackLen-m_nRcvPackLen);
					}
					else
					{	//缓冲已满
						//m_pNetworkNotify->OnError();
						m_pTimer->Set(30);
						m_pTimer->Start();
					}
				}
				else
				{
      				m_pHttpC->Cancel();
					this->RequestData();
				}
			}
			else if(m_nRcvPackLen>=m_nCurPackLen)
				{

					//file.Write((const char*)m_nPackHead,6);
					//file.Write((const char*)m_pPack->data,m_nCurPackLen-6);
					//file.Flush();
					m_pStreamBuffer->WriteFinish(m_pPack,m_nSize);
					if(m_pPack && m_pPack->mediatype == 0x02)
						m_pNetworkNotify->OnProgressChanged();
					m_pPack = NULL;
					m_nCurPos += m_nCurPackLen;
					m_nOnceLen -= m_nCurPackLen;
					m_nRcvPackLen = 0;
					m_nCurPackLen = 0;
					m_nSize = 0;
					if( m_nCurPos <m_nLength)
					{
						if(m_nOnceLen >= 6)
							m_pHttpC->Read(m_nPackHead,6);
						else
                        {
                            m_pHttpC->Cancel();
							this->RequestData();
                        }
					}
					else
					{
						//file.Close();
						m_pNetworkNotify->OnAllCompleted();
					}
				}
			if(m_nRcvPackLen<m_nCurPackLen)
			{
				//上层不处理,由底层处理
				//m_pHttpC->Read((INT8*)&m_nPack.data[m_nRcvPackLen],m_nCusPackLen-m_nRcvPackLen);

			}

		}
		return;
	}
	if(m_nCurPos>=m_nLength)
		m_pNetworkNotify->OnAllCompleted();
	else
	{
		m_nTryTimes++;
		if(m_nTryTimes>10)
			m_pNetworkNotify->OnError();// 通知上层
		else
		{
			m_nCurPackLen = 0;
			m_nRcvPackLen = 0;
            m_pHttpC->Cancel();
			RequestData();
		}
	}


}

void CMNetDataSource::OnTimer(CMTimer &cTimer)
{
	if(!m_pPack && m_nRcvPackLen == 6)
	{
		UINT8 st[5];
		memset(st,0,5);
		memcpy(st,m_nPackHead,2);
		m_nCurPackLen = *(UINT16*)st+6;//数据+包头
		memcpy(st,&m_nPackHead[2],4);
		if(!m_pPack)
		{
			m_nSize = m_nCurPackLen-6 + sizeof(Med_Packet);
			m_pPack = m_pStreamBuffer->GetWriteBuf(m_nSize);
		}
		if(m_pPack)
		{		
			m_pPack->len = m_nCurPackLen-6;
			m_pPack->mediatype = st[0];
			m_pPack->timestamp = UINT32(st[3]<<16)+UINT32(st[2]<<8)+UINT32(st[1]);
			m_pHttpC->Read((INT8*)m_pPack->data + (m_nRcvPackLen-6),m_nCurPackLen-m_nRcvPackLen);
		}
		else
		{	//缓冲已满
			//m_pNetworkNotify->OnError();
			m_pTimer->Set(30);
			m_pTimer->Start();
		}

	}
}

