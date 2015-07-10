// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
#include "tinyxml.h"
#include "cmsession.h"

template <typename T>
CMNetworkDataList<T>::CMNetworkDataList(IMUpdateDataListener* pListener)
:m_UserData(NULL)
,m_pSession(NULL)
,m_bPaging(FALSE)
, m_nPageNo(0)
, m_nPageSize(30)
, m_nTotalCount(0)
, m_nServiceNo(0)
{
	m_pListener = pListener;
	m_lstItem = new CMList<T>;
}

template <typename T>
CMNetworkDataList<T>::~CMNetworkDataList()
{
	if(m_lstItem)
		m_lstItem->clear();
	SAFEDELETE(m_lstItem);
	SAFEDELETE(m_pSession);
}

template <typename T>
void CMNetworkDataList<T>::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

template <typename T>
void CMNetworkDataList<T>::SetPaging(BOOL bPaging)
{
	m_bPaging = bPaging;
}

template <typename T>
BOOL CMNetworkDataList<T>::RequestMore()
{
	if(m_bPaging)
	{
		if(m_nTotalCount <= m_nPageSize)
			return FALSE;
		int count = m_nTotalCount/m_nPageSize;
		if(m_nTotalCount%m_nPageSize > 0)
			count++;
		if(m_nPageNo < count)	
		{
			count = m_nPageNo + 1;
			return CurrentRequest(m_sParam,count,m_nPageSize);
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}
template <typename T>
BOOL CMNetworkDataList<T>::CurrentRequest(const char* param,int pageno,int pagesize)
{
	char sParam[640];
	snprintf(sParam,640,"%s&pageno=%d&pagesize=%d",m_sParam,pageno,pagesize);
	if(m_pSession)
		m_pSession->Command(m_nServiceNo,sParam);
	return TRUE;
}
template <typename T>
void CMNetworkDataList<T>::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

template <typename T>
int CMNetworkDataList<T>::GetItemCount()
{
	if(!m_lstItem)
		return 0;
	return m_lstItem->size();
}

template <typename T>
BOOL CMNetworkDataList<T>::GetItem(int nIndex, T& item)
{
	if(!m_lstItem)
		return FALSE;
	if(nIndex >= m_lstItem->size() || nIndex < 0)
		return FALSE;
	item = m_lstItem->at(nIndex);
	return TRUE;

}
template <typename T>
void CMNetworkDataList<T>::Clear()
{
	if(m_lstItem)
		m_lstItem->clear();
}
template <typename T>
BOOL CMNetworkDataList<T>::Request(int nServiceNo, const char* sParam)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;

	if(m_bPaging)
	{
		m_nServiceNo = nServiceNo;
		m_nPageNo = 0;
   		m_nTotalCount = 0;
		strcpy(m_sParam,sParam);
		CurrentRequest(m_sParam, 1, m_nPageSize);
	}
	else
		m_pSession->Command(nServiceNo, sParam);
	return TRUE;
}

template <typename T>
void CMNetworkDataList<T>::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;
	if (nCode == MER_OK)
	{
		TiXmlElement *pItem = pDoc->RootElement();

		INT32 nErr = -1;
		if(m_bPaging)
		{
			pItem->QueryIntAttribute("totalcount", &m_nTotalCount);
			pItem->QueryIntAttribute("pageno", &m_nPageNo);
		}
		pItem->QueryIntAttribute("errno", &nErr);
		if (nErr == 0)
		{
			if(!pItem->NoChildren())
			{
				T t;
				memset(&t, 0, sizeof(T));
				pItem = pItem->FirstChildElement("item");
				while(pItem)
				{
					if(this->DoItem(pItem, t))
						this->m_lstItem->push_back(t);
					pItem = pItem->NextSiblingElement("item");
				}
			}
			if(this->m_lstItem->size() > 0)
				result = TResult::ESuccess;
			else
				result = TResult::ENothing;
		}
		else
			result = TResult::EUnknownError;
	}
	else if(nCode == MERN_OFFLINE)
	{
		result = TResult::ENotSupportOffline;
	}
	else if(nCode == MERN_INITIALIZE)
	{
		result = TResult::ENetDisconnect;
	}
	else if(nCode == MERN_OFFLINE)
	{
		result = TResult::ENotSupportOffline;
	}
	else
		result = TResult::ENetTimeout;
	
	if(this->m_pListener)
		this->m_pListener->OnUpdateDataFinish(this->m_UserData, result);
}

template <typename T>
CMList<T>* CMNetworkDataList<T>::GetList()
{
	return m_lstItem;
}

template <typename T>
BOOL CMNetworkDataList<T>::IsEnd()
{
	if(!m_bPaging)
		return TRUE;
//	 CM_ERRP("CMNetworkDataList<T>::IsEnd() %d error", m_nTotalCount);
	int count = m_nTotalCount/m_nPageSize;
	if(m_nTotalCount%m_nPageSize > 0)
		count++;
	return m_nPageNo >= count;	
}
template <typename T>
BOOL CMNetworkDataList<T>::IsRunning()
{
	if(m_pSession)
		return m_pSession->IsRunning();
	else
		return FALSE;
}
