#include "stdafx.h"
#include "cmlocaldatasource.h"
#include "cmanalyze.h"

const int  READ_MAX_LEN = 1024*50;
static int adts_sample_rates[] = {96000,88200,64000,48000,44100,32000,24000,22050,16000,12000,11025,8000,7350,0,0,0};

CMLocalDataSource::CMLocalDataSource()
{
	m_bRunning = FALSE;
	m_pMedPacket = NULL;
	m_pNotify = NULL;
	m_pStreamBuffer = NULL;	
	m_pTimer = NULL;
	m_pAnalyze = NULL;
	m_pReadBuf = NULL;
	m_nParseLen = 0;
	m_bSeek = FALSE;
	m_nMode= -1;
}
CMLocalDataSource::~CMLocalDataSource()
{
	Stop();
	m_File.Close();
	if(m_pTimer)
	{
		delete m_pTimer;
		m_pTimer = NULL;
	}
	if(m_pAnalyze)
	{
		delete m_pAnalyze;
		m_pAnalyze = NULL;
	}
}
BOOL CMLocalDataSource:: Init(IMDataNotify* pNetworkNotify, CMStreamBuffer* pStreamBuffer)
{
	ASSERT(pNetworkNotify != NULL && pStreamBuffer != NULL);	
	m_pStreamBuffer = pStreamBuffer;
	m_pNotify = pNetworkNotify; 
	if(!m_pTimer)
		m_pTimer = new CMTimer(this);
	return TRUE;
}
BOOL CMLocalDataSource ::Open(const CMString& sUrl, int mtype)
{
	this->Stop();
	if(!m_File.Open(sUrl))	
		return FALSE;
	m_nMode = mtype;
	return TRUE;
	
}
void CMLocalDataSource::Start()
{
	if(m_pTimer)
	{
		m_pTimer->Set(500);
		m_bRunning = TRUE;
		m_pTimer->Start();
	}
}
void CMLocalDataSource::Stop()
{
	//if(m_pTimer)
	//	m_pTimer->Stop();
	this->Reset();
}
void CMLocalDataSource::Seek(UINT32 msec)
{
	BOOL bFound = FALSE;
	if(m_pAnalyze && m_pAnalyze->GetMedIndex())
	{
		Med_Index* m_pIndex = m_pAnalyze->GetMedIndex();
		for(int i=0;i<m_pAnalyze->GetMedIndexCount();i++)
		{
			if(msec>m_pIndex[i].present_time)
				i++;
			else
			{
				bFound = TRUE;
				m_bRunning = FALSE;
				if(m_pTimer)
					m_pTimer->Stop();
				m_pStreamBuffer->Reset();
				m_bSeek = TRUE;
				m_pMedPacket = NULL;
				m_nParseLen = m_pIndex[i].offset;
				//CM_ERRP("CMLocalDataSource::Seek:pos%d",m_nParseLen);
				m_File.Seek(m_nParseLen);
				m_pNotify->OnSeekTime(m_pIndex[i].present_time);
				this->Start();
				break;
			}
		}

	}
	if(!bFound && m_pNotify)
	{
		this->Stop();
		m_pStreamBuffer->Reset();
		m_pNotify->OnAllCompleted();
	}
	
}
void CMLocalDataSource::GetHeadInfo(Med_Info& HeadInfo)
{
	if(m_bHeadComplete && m_pAnalyze)
	{
		HeadInfo =*m_pAnalyze->GetMedInfo();
	}
}

void CMLocalDataSource::OnTimer(CMTimer &cTimer)
{
	if(m_pTimer && m_bRunning)
	{
		BOOL ret = TRUE;
		if(m_nMode == EMode_aac)
			ret = ParseAAC();
		if(m_nMode == EMode_3mv || m_nMode == EMode_3ma)
			ret = ParseData();
		if(ret)
		{
			m_pTimer->Set(100);
			m_pTimer->Start();
		}
	}
		
}
BOOL CMLocalDataSource::ParseAAC()
{
	if(!m_pReadBuf)
		m_pReadBuf = new CHAR[READ_MAX_LEN];
	if(!m_pReadBuf && m_pNotify)
	{
		m_pNotify->OnError();
		return FALSE;
	}
	memset(m_pReadBuf,0,READ_MAX_LEN);
	int retlen = m_File.Read(m_pReadBuf,READ_MAX_LEN);
	if(retlen < 7 && m_pNotify)
	{
		m_pTimer->Stop();
		m_pNotify->OnAllCompleted();
		return FALSE;
	}
	UINT8 b0 = m_pReadBuf[0], b1 = m_pReadBuf[1],b2 = m_pReadBuf[2];
	if (!((b0 == 0xFF)&&((b1 & 0xF6) == 0xF0)))
	{
		m_pTimer->Stop();
		m_pNotify->OnAllCompleted();
		return FALSE;
	}
	int samplerate = adts_sample_rates[(b2&0x3c)>>2];
	float msec_per_frames = (float)1024.0f*1000/samplerate;
	if(!m_bHeadComplete)
	{
		Med_Info headinfo = {0};
		headinfo.acodec = 0x03;
		//short int dwst;
		UINT8 st[2];
		memcpy(st,m_pReadBuf+2,2);
		headinfo.channels = 2;//(st[0]&0x01) + (st[1]>>6);
		if(samplerate<=24000)
			samplerate = samplerate*2;
		headinfo.samplerate = samplerate;
		headinfo.samplebit = 16;
		headinfo.bitRate = 0;
		
		m_bHeadComplete = TRUE;
		m_pNotify->OnHeadCompleted(headinfo);
		if(!IsRunning())
			return FALSE;
	}
	//int handlelen = this->ParsePacket(m_pReadBuf, retlen);
	//adts ˝âÎö 5ÖĄ
	UINT8* pstr = (UINT8*)m_pReadBuf;
	int i = 0;
	int handlelen = 0;
	int frame_length = 0;
	while(i<10)
	{
            frame_length += ((((unsigned int)pstr[3] & 0x3)) << 11)
        | (((unsigned int)pstr[4]) << 3) | (pstr[5] >> 5);
            if(frame_length > retlen )
				break;
			handlelen = frame_length;
			i++;
			pstr = (UINT8*)m_pReadBuf + frame_length;
	}

	if(i > 0)
	{

		int size = handlelen+sizeof(Med_Packet);
		if(!m_pMedPacket && m_pStreamBuffer)
			m_pMedPacket = m_pStreamBuffer->GetWriteBuf(size);
		if(m_pMedPacket && m_pNotify)
		{
			m_pMedPacket->len = handlelen;
			m_pMedPacket->mediatype = 0x02;
			m_pMedPacket->timestamp = (UINT32)msec_per_frames*i;
			memcpy(m_pMedPacket->data,m_pReadBuf,handlelen);
			m_pStreamBuffer->WriteFinish(m_pMedPacket,size);
			m_pMedPacket = NULL;
			m_pNotify->OnProgressChanged();
		}
		else
		{
			m_File.Seek(m_nParseLen);
			return TRUE;
		}		
	}
	m_nParseLen += handlelen;
	if(m_nParseLen >= m_File.GetLength())
	{
		m_pTimer->Stop();
		m_pNotify->OnAllCompleted();
		return FALSE;
	}
	m_File.Seek(m_nParseLen);
	return TRUE;
}
BOOL CMLocalDataSource::ParseData()
{
	if(!m_bHeadComplete )//&& m_bSeek
	{
		if(m_pReadBuf)
			delete m_pReadBuf;
		m_pReadBuf = new CHAR[1024];
		memset(m_pReadBuf,0,1024);
		if(	m_File.Read(m_pReadBuf,1024) < 1024)
		{
			m_pNotify->OnError();
			return FALSE;
		}
		if(m_pAnalyze)
			delete m_pAnalyze;
		m_pAnalyze = new CMAnalyze;
		if(m_pAnalyze)
		{
			m_pAnalyze->AnalyzeHead(m_pReadBuf,1024);
			delete []m_pReadBuf;
			m_pReadBuf = NULL;
			if(m_pAnalyze->GetMedInfo() && m_pNotify)
			{
				m_pNotify->OnHeadCompleted(*m_pAnalyze->GetMedInfo());
				if(!IsRunning())
					return FALSE;
			}
		}
		m_nParseLen = 1024;
		m_bHeadComplete = TRUE;
	}
	if(!m_pReadBuf)
		m_pReadBuf = new CHAR[READ_MAX_LEN];
	if(!m_pReadBuf && m_pNotify)
	{
		m_pNotify->OnError();
		return FALSE;
	}
	memset(m_pReadBuf,0,READ_MAX_LEN);
	int retlen = m_File.Read(m_pReadBuf,READ_MAX_LEN);
	if(retlen <= 0 && m_pNotify)
	{
		m_pTimer->Stop();
		m_pNotify->OnAllCompleted();
		return FALSE;
	}
	int handlelen = this->ParsePacket(m_pReadBuf, retlen);
	m_nParseLen += handlelen;
	if(m_nParseLen >= m_File.GetLength())
	{
		m_pTimer->Stop();
		m_pNotify->OnAllCompleted();
		return FALSE;
	}
	m_File.Seek(m_nParseLen);

	return TRUE;

}
int CMLocalDataSource::ParsePacket(CHAR* pbuf,int len)
{
	ASSERT(pbuf != NULL && len > 0);
	UINT8 st[5],datahead[7];
	int size = 0;
	int datalen = 0;
	int ret = 0;
	while(len > 0 && m_bRunning)
	{
		if(len <= 7)
			break;
		memset(datahead,0,7);
		memset(st,0,5);
		memcpy(datahead,pbuf,6);
		pbuf += 6;
		len -= 6;
		memcpy(st,datahead,2);
		datalen = *(UINT16*)st;
		if(len < datalen)
			break;
		size = datalen+sizeof(Med_Packet);
		memcpy(st,&datahead[2],4);
		if(!m_pMedPacket && m_pStreamBuffer)
			m_pMedPacket = m_pStreamBuffer->GetWriteBuf(size);
		if(m_pMedPacket && m_pNotify)
		{
			m_pMedPacket->len = datalen;
			m_pMedPacket->mediatype = st[0];
			m_pMedPacket->timestamp = UINT32(st[3]<<16)+UINT32(st[2]<<8)+UINT32(st[1]);
			//CM_ERRP("CMLocalDataSource::ParsePacket:addr:m_pMedPacket->data:0x%X,type:%d",m_pMedPacket->data,m_pMedPacket->mediatype);
			memcpy(m_pMedPacket->data,pbuf,datalen);
			m_pStreamBuffer->WriteFinish(m_pMedPacket,size);
			m_pNotify->OnProgressChanged();

		}
		else
			break;
		m_pMedPacket = NULL;
		pbuf += datalen;
		len -= datalen;
		ret += datalen + 6;
	}
	return ret;
}
void CMLocalDataSource::Reset()
{
	m_bRunning = FALSE;
	if(m_pTimer)
		m_pTimer->Stop();
	if(m_pStreamBuffer)
		m_pStreamBuffer->Reset();
	if(m_pReadBuf)
	{
		delete []m_pReadBuf;
		m_pReadBuf = NULL;
	}
	m_File.Seek(0);
	m_pMedPacket = NULL;
	m_bHeadComplete = FALSE;
	m_bSeek = FALSE;    
	m_nParseLen = 0;
}
