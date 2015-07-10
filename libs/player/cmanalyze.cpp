#include "stdafx.h"
#include "cmanalyze.h"

CMAnalyze::CMAnalyze()
{
	m_pHeadInfo = NULL;
	m_pMedIndex = NULL;
	m_nIndexCount = 0;
}
CMAnalyze::~CMAnalyze()
{
	if(m_pHeadInfo)
	{
		delete m_pHeadInfo;
		m_pHeadInfo = NULL;
	}
	if(m_pMedIndex)
	{
		delete []m_pMedIndex;
		m_pMedIndex = NULL;
	}
}
Med_Info* CMAnalyze::GetMedInfo()
{
	return m_pHeadInfo;
}
Med_Index* CMAnalyze::GetMedIndex()
{
	return m_pMedIndex;		
}
BOOL CMAnalyze::AnalyzeHead(CHAR *buf,int len)
{
	ASSERT(buf != NULL);
	if(len >= 1024)
	{
		if(m_pHeadInfo)
			delete m_pHeadInfo;
		m_pHeadInfo = new Med_Info;
		memset(m_pHeadInfo,0,sizeof(Med_Info));
		CHAR stemp[5];
		memset(stemp,0,5);
		CHAR* str = buf;
		memcpy(stemp,str,2);
		m_pHeadInfo->len = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->bitRate = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,4);
		m_pHeadInfo->duration = *(UINT32*)stemp;
		memset(stemp,0,5);
		//video
		str += 4;
		memcpy(stemp,str,2);
		m_pHeadInfo->vcodec = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->fps = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->weight = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->height = *(UINT16*)stemp;
		//audio
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->acodec = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->channels = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->samplerate = *(UINT16*)stemp;
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->samplebit = *(UINT16*)stemp;
		//ext
		str += 2;
		memcpy(stemp,str,2);
		m_pHeadInfo->version = *(UINT16*)stemp;

		//索引个数
		str = buf+m_pHeadInfo->len;
		UINT32 pos = m_pHeadInfo->len;
		while(pos<=1024)
		{
			memcpy(stemp,str,4);
			if(*(UINT32*)stemp == 0)
				break;
			str += 4;
			pos += 4;
			if(*(UINT32*)stemp == 0)
				break;
			if(pos>1024)
				break;
			m_nIndexCount++;
			str += 4;
			pos += 4;
		}

		if(m_pMedIndex)
		{
			delete[]m_pMedIndex;
			m_pMedIndex = NULL;
		}
		m_pMedIndex =new Med_Index[m_nIndexCount];
		ASSERT(m_pMedIndex != NULL);
		str = buf+m_pHeadInfo->len;

		for(int i=0;i<m_nIndexCount;i++)
		{
			memcpy(stemp,str,4);
			m_pMedIndex[i].present_time = *(UINT32*)stemp;
			//					int time = m_pIndex[i].present_time;
			str += 4;
			memcpy(stemp,str,4);
			m_pMedIndex[i].offset = *(UINT32*)stemp;
			//					int off = m_pIndex[i].offset;
			str +=4;
		}
		return TRUE;
	}
	return FALSE;
}
