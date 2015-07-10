// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
//当前模块是网络模块
#define FILE_MOD 16

#include "stdafx.h"
#include "cmstreambuffer.h"

CMStreamBuffer::CMStreamBuffer()
{
    m_pData = NULL;
    m_nSize = 0;
    m_nStreamCount = 0;
    Reset();
}

CMStreamBuffer::~CMStreamBuffer()
{
    m_cMutex.Lock();    
    if(m_pData)
    {
        free(m_pData);
        m_pData = NULL;
    }
    m_nSize = 0;
    m_cMutex.UnLock();
}

BOOL CMStreamBuffer::Init(UINT32 nSize, UINT32 nStreamCount)
{
    BOOL ret = FALSE;

    Reset();
    m_cMutex.Lock();

    if(nStreamCount > 0 && nStreamCount < 3)
    {
        m_nStreamCount = nStreamCount;
        ret = TRUE;
    }

    if(ret)
    {
        if(m_pData == NULL)
        {
            m_pData = (UINT8*)malloc(nSize + sizeof(Med_Packet));
            m_nSize = nSize;
        }
        else if(m_nSize < nSize)
        {
            UINT8* pData = (UINT8*)realloc(m_pData, nSize + sizeof(Med_Packet));
            if(pData)
            {
                m_pData = pData;
                m_nSize = nSize;
            }
        }
	    if(m_pData)
		    ret = TRUE;
        else
            m_nStreamCount = 0;
        CM_LOGP(CM_LOGL_DEBUG, "Init %0x %d, %0x", m_pData, nSize, m_pData + nSize);
    }
    m_cMutex.UnLock();
    return ret;
}

Med_Packet* CMStreamBuffer::GetWriteBuf(UINT32 nSize)
{
	Med_Packet* pRet = NULL;
	UINT32 nLockWritePos, nShortWritePos;
	m_cMutex.Lock();

	ASSERT(m_nWritePos == m_nLockWritePos);

    nSize = (nSize+3) & 0xFFFFFFFC;
//    CM_LOGP(CM_LOGL_DEBUG, "GetWriteBuf start %d", nSize);

	nLockWritePos = m_nWritePos + nSize;
	nShortWritePos = m_nWritePos % m_nSize;

	if(nLockWritePos - m_nMinReadPos < m_nSize //总剩余空间还够分配
        && nShortWritePos + nSize > m_nSize) //buf末尾已经不够了
	{//回转到head
		((Med_Packet*)(m_pData + nShortWritePos))->len = 0;
		m_nReadPos[0] = m_nReadPos[0] % m_nSize;
        m_nReadPos[1] = m_nReadPos[1] % m_nSize;
        m_nReadPos[2] = m_nReadPos[2] % m_nSize;
        m_nLockReadPos[0] = m_nLockReadPos[0] % m_nSize;
        m_nLockReadPos[1] = m_nLockReadPos[1] % m_nSize;
        m_nLockReadPos[2] = m_nLockReadPos[2] % m_nSize;
        m_nMinReadPos = m_nMinReadPos % m_nSize;
		m_nLockWritePos = m_nWritePos = m_nSize;
		nLockWritePos = m_nWritePos + nSize;
		nShortWritePos = 0;	
	}

	if(nLockWritePos - m_nMinReadPos < m_nSize) 
	{
		pRet = (Med_Packet*)(m_pData + nShortWritePos);
        pRet->data = m_pData + nShortWritePos + sizeof(Med_Packet);
		m_nLockWritePos = nLockWritePos;
	}
//    CM_LOGP(CM_LOGL_DEBUG, "GetWriteBuf return %0x ", pRet);
    ASSERT(m_nLockWritePos > m_nMinReadPos);
	m_cMutex.UnLock();
	return pRet;
}

Med_Packet* CMStreamBuffer::GetNextPacket(UINT32 nStreamID)
{
	Med_Packet* pRet = NULL;
	m_cMutex.Lock();

//    CM_LOG(CM_LOGL_DEBUG, "GetNextPacket start");
    ASSERT(m_nWritePos >= m_nReadPos[nStreamID-1]);

	while(pRet == NULL && m_nReadPos[nStreamID-1] < m_nWritePos)
	{
        m_nLockReadPos[nStreamID-1] = m_nReadPos[nStreamID-1];
		pRet = (Med_Packet*)(m_pData + m_nReadPos[nStreamID-1] % m_nSize);
        if(pRet->len <= 0)//buf末尾无效
        {
            CM_LOGP(CM_LOGL_DEBUG, "GetNextPacket m_nReadPos[%d] % m_nSize(%d) = 0", nStreamID-1, m_nSize);
            ASSERT(m_nReadPos[nStreamID-1] % m_nSize != 0);
            m_nReadPos[nStreamID-1] += m_nSize - m_nReadPos[nStreamID-1] % m_nSize;
            pRet = NULL;
            continue;
        }
        else
        {
    		m_nReadPos[nStreamID-1] += (pRet->len + sizeof(Med_Packet) + 3) & 0xFFFFFFFC;
        }

		//if(m_nReadPos[nStreamID-1] % m_nSize <= sizeof(Med_Packet) 
		//	|| ((Med_Packet*)(m_pData + m_nReadPos[nStreamID-1] % m_nSize))->data == NULL)
		//	m_nReadPos[nStreamID-1] += m_nSize - m_nReadPos[nStreamID-1] % m_nSize;
        ASSERT(m_nWritePos >= m_nReadPos[nStreamID-1]);
        if(pRet->mediatype != nStreamID)
            pRet = NULL;
	}
    if(m_nStreamCount == 1)
        m_nMinReadPos = m_nLockReadPos[nStreamID-1];
    else if(m_nStreamCount == 2)
        m_nMinReadPos = m_nLockReadPos[0] < m_nLockReadPos[1] ? m_nLockReadPos[0] : m_nLockReadPos[1];
    //else if(m_nStreamCount == 3)//暂不支持
    //{
    //    m_nMinReadPos = m_nReadPos[0] < m_nReadPos[1] ? m_nReadPos[0] : m_nReadPos[1];
    //    m_nMinReadPos = m_nMinReadPos < m_nReadPos[2] ? m_nMinReadPos : m_nReadPos[2];
    //}
//    CM_LOGP(CM_LOGL_DEBUG, "GetNextPacket %d %0x %d", nStreamID, pRet, pRet ? pRet->len : 0);
	m_cMutex.UnLock();
    return pRet;
}

UINT32 CMStreamBuffer::GetPercent()
{
	UINT32 ret = 0;
	m_cMutex.Lock();

	if(m_nSize)
        ret = 100*(m_nWritePos - m_nMinReadPos) / (m_nSize < 102400 ? m_nSize : 102400);//m_nSize;

    if(ret > 100)
        ret = 100;

	m_cMutex.UnLock();
	return ret;
}

void CMStreamBuffer::Reset()
{
    m_cMutex.Lock();
    m_nWritePos = 0;
    m_nLockWritePos = 0;
    m_nReadPos[0] = 0;
    m_nReadPos[1] = 0;
    m_nReadPos[2] = 0;
    m_nLockReadPos[0] = 0;
    m_nLockReadPos[1] = 0;
    m_nLockReadPos[2] = 0;
    m_nMinReadPos = 0;
    m_cMutex.UnLock();
}

void CMStreamBuffer::WriteFinish(Med_Packet* pBuffer, UINT32 nLen)
{
	m_cMutex.Lock();

    nLen = (nLen+3) & 0xFFFFFFFC;
	ASSERT((m_pData + m_nWritePos % m_nSize) == (UINT8*)pBuffer && (m_nLockWritePos - m_nWritePos) == nLen);
	m_nWritePos = m_nLockWritePos;

//    CM_LOGP(CM_LOGL_DEBUG, "WriteFinish %0x %d", pBuffer, nLen);
	m_cMutex.UnLock();
}
