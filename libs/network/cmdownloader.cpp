// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

//当前模块是网络模块
#define FILE_MOD CM_LOGM_NET


#include "stdafx.h"
#include "cmdownloader.h"
#include "cmnetworkmgr.h"
#include "cmfile.h"
#include "cmpath.h"
#ifdef PLAT_AND
#include "android/cmdownloader_jni.h"
#endif

const UINT32 REQ_SIZE = 204800;    //wap 跨网关的大小

CMDownloader::CMDownloader(IMNotifyDownload* pNotify)
{
#ifdef PLAT_AND
	m_pNotify = new CMNotifyDownloadAndroid(pNotify);
#else
    m_pNotify = pNotify;
#endif
    m_pHttp = NULL;
    m_pFile = NULL;
    m_nTotal = 0;
    m_nSize = 0;
    m_pBuf = NULL;
    m_nBufSize = 51200;
    m_nStatus = NONE;
    m_bProgress = FALSE;
    m_nRate = 0;
	m_nMaxFileSize = 0xFFFFFFFF;

    m_sRoot = CMPath(CMPath::DOWNLOAD_PATH).String();
}

CMDownloader::~CMDownloader()
{
	if (m_pHttp) {
		m_pHttp->Cancel();
		SAFEDELETE(m_pHttp);
	}

	if (m_pFile)
	{
		m_pFile->Close();
		SAFEDELETE(m_pFile);
	}
#ifdef PLAT_AND
	if (m_pNotify)
	{
		delete (CMNotifyDownloadAndroid*)m_pNotify;
		m_pNotify = NULL;
	}
#else
    m_pNotify = NULL;
#endif
    SAFEDELETE(m_pBuf);
}

void CMDownloader::Download(const CMString& sUrl, const CMString& sPathName)
{
    m_cInfo.sUrl = sUrl;
    if (sPathName.IsEmpty())
    {
    	m_cInfo.sPath = Url2DownFileName(sUrl);
    }
    else
    	m_cInfo.sPath = sPathName;

    CM_LOGP(CM_LOGL_DEBUG, "CMDownloader::Download local file %s", (const CHAR*)m_cInfo.sPath);

    m_cInfo.nSize = 0;
    m_cInfo.nDowned = 0;
    m_cInfo.nCurSpd = 0;
    m_cInfo.nAvgSpd = 0;
    CMDateTime dCur;
    m_cInfo.dStart = dCur.getTime();
    m_cInfo.dCurrent = dCur.getTime();

    //创建中间文件，直接在目标文件后再加tmp后缀
    m_sTmpFilaName = m_cInfo.sPath + ".tmp";//CMFile::GetTempFileName(m_cInfo.sPath, "tmp");

    m_nTotal = 0;
    m_nStart = 0;
    m_nEnd = 0;

    Download();
}

void CMDownloader::Download()
{
    m_nRate=0;
    
    if (CMFile::FileExist(m_sTmpFilaName))
    {
    	CM_LOGP(CM_LOGL_INFO, "temp file %s is exist, continue download", (const CHAR*)m_sTmpFilaName);
        
    	//文件已存在，断点续传
    	if (m_pFile == NULL)
    	{
    		m_pFile = new CMFile();
    	}

    	m_pFile->Close();

        if (m_pFile->Open(m_sTmpFilaName, CMFile::OPEN_W_EXIST, CMFile::SHARE_R))
        {
        	m_nStart = m_pFile->GetLength();
        	m_pFile->Seek(0, CMFile::FILESEEK_END);
        }
    }

    if (m_pHttp == NULL)
    {
    	m_pHttp = new CMHttpC(this);
    }
    m_pHttp->Cancel();

    CMHTTPReqHeader reqHeader;
    reqHeader.CreateDefault();
    reqHeader.AddValue(HH_ATYPE, CMString(L"*/*"));
    if(CMNetConnMgr::Instance().CurrentType() == CMNetConnMgr::CMWAP)
    {
        char sRange[128]={0,};
#if defined(USE_CURL)
        snprintf(sRange,128,"%d-%d", m_nStart, REQ_SIZE - 1);
#else
        snprintf(sRange,128,"bytes = %d-%d", m_nStart, REQ_SIZE - 1);
#endif
        reqHeader.AddValue(HH_RANGER, sRange);
    }
    else if (m_nStart > 0)
    {
        char sRange[128]={0,};
#if defined(USE_CURL)
        snprintf(sRange,128,"%d-", m_nStart);
#else
        snprintf(sRange,128,"bytes = %d-", m_nStart);
#endif
        reqHeader.AddValue(HH_RANGER, sRange);
    }

    reqHeader.SetUrl(m_cInfo.sUrl);

    m_nStatus = RUNNING;
    m_pHttp->Request(reqHeader);
}

//暂停后http不停
void CMDownloader::Pause()
{
	if (m_nStatus != RUNNING) return;

	m_nStatus = PAUSED;

	if (m_pHttp) {
		m_pHttp->Cancel();
	}
}

//停止后http也停止，
void CMDownloader::Cancel()
{
	if (m_nStatus != RUNNING) return;

	m_nStatus = STOPED;

	if (m_pHttp) {
		m_pHttp->Cancel();
		SAFEDELETE(m_pHttp);
	}

	if (m_pFile)
	{
		m_pFile->Close();
		SAFEDELETE(m_pFile);
	}
}

//恢复下载，PAUSED STOPED
void CMDownloader::Resume()
{
	if (m_nStatus == RUNNING || m_nStatus == NONE || m_nStatus == COMPLETED) return;

	Download();
}

void CMDownloader::SetBufferSize(UINT32 nSize)
{
    //必须保证m_pBuf也同步变化
    if (!m_pHttp || (m_pHttp && !m_pHttp->IsRunning()))
    {
        m_nBufSize = nSize;
    }
}

void CMDownloader::SetProgress(BOOL bFlag)
{
    m_bProgress = bFlag;
}

void CMDownloader::GetUrl(CMString& sUrl)
{
    sUrl = m_cInfo.sUrl;
}

void CMDownloader::GetPathName(CMString& sPathName)
{
    sPathName = m_cInfo.sPath;
}

const TDownloadInfo& CMDownloader::GetCurrentInfo()
{
	if (m_cInfo.dCurrent != m_cInfo.dStart)
		m_cInfo.nAvgSpd = m_cInfo.nDowned / (m_cInfo.dCurrent - m_cInfo.dStart);
	else
		m_cInfo.nAvgSpd = 0;
	return m_cInfo;
}

//下载状态
CMDownloader::STATUS CMDownloader::GetStatus()
{
	return m_nStatus;
}

void CMDownloader::SetStatusCompleded() {
    m_nStatus = CMDownloader::COMPLETED;
}

//自动计算的url到下载文件名
CMString CMDownloader::Url2DownFileName(const CMString& sUrl)
{
	CMString sOrgUrl;
   	INT32 pos = sUrl.ReverseFind(L"sid=");
    	if(pos > 0)
    		sOrgUrl = sUrl.Left(pos-1);
    	else
    		sOrgUrl = sUrl;
	return m_sRoot + CMFile::GetTempFileName(sOrgUrl, "");
}

IMNotifyDownload* CMDownloader::SetNotify(IMNotifyDownload* pNotify)
{
#ifdef PLAT_AND
	return ((CMNotifyDownloadAndroid*)m_pNotify)->SetNotify(pNotify);
#else
    IMNotifyDownload* pTmp = m_pNotify;

    m_pNotify = pNotify;

    return pTmp;
#endif
}

//interface from IMNotifyHttpC
void CMDownloader::OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader)
{
    UINT32 nRet = MER_OK;
    if (nCode == MER_OK)
    {
        ASSERT(pRespHeader != NULL);

        UINT32 httpRet = pRespHeader->GetHttpReturn();

        if (httpRet == 200 || httpRet == 206)
        {
            CMString sVal;

            //判断是否wap网关的无聊返回，如果是则继续请求一次
            if (pRespHeader->GetValue(HH_CTYPE, sVal))
            {
                if (sVal.Find(L"text/vnd.wap.wml") >= 0)
                {
                    m_pHttp->Request();
                    return;
                }
            }            

            if (pRespHeader->GetValue(HH_CRANGE, sVal))
            {
                
//                {
//                    CM_ERR("CMDownloader::OnResponse no content-length and range");
//                    goto err;
//                }

                INT32 nPos1 = sVal.Find(L" ");
                INT32 nPos2 = sVal.Find(L"-");
                INT32 nPos3 = sVal.Find(L"/");
                if (nPos1 <= 0 || nPos2 <= 0 || nPos3 <= 0)
                {
                    CM_ERRP("CMDownloader::OnResponse wrong content-range %s", (const CHAR*)sVal);
                    goto err;
                }

                m_nStart= _mwtoi((const WCHAR*)sVal.Mid(nPos1 + 1, nPos2 - nPos1 - 1));
                m_nEnd = _mwtoi((const WCHAR*)sVal.Mid(nPos2 + 1, nPos3 - nPos2 - 1));  //大于0
                m_nSize = m_nEnd - m_nStart + 1;

                if (m_nTotal == 0)
                {
                    //对于第一次http返回，需要返回结果给socket
                    m_nTotal = _mwtoi((const WCHAR*)sVal.Mid(nPos3 + 1));
                }
                else
                {
                    ASSERT(m_nTotal == _mwtoi((const WCHAR*)sVal.Mid(nPos3 + 1)));
                    //ASSERT(m_nEnd - m_nStart < REQ_SIZE);
                }
				if(m_nTotal > m_nMaxFileSize)
					goto err;

                UINT32 nLen = m_nSize;
                if (m_nSize > m_nBufSize)
                {
                    nLen = m_nBufSize;
                }
                if (!m_pBuf)
                {
                    m_pBuf = new INT8[m_nBufSize + 1];
                }

                m_pHttp->Read(m_pBuf, nLen);
            }
            else if (pRespHeader->GetValue(HH_CLENGTH, sVal))
            {
                sVal.Trim();
                m_nTotal = m_nSize = _mwtoi(sVal);
				if(m_nTotal > m_nMaxFileSize)
					goto err;

                UINT32 nLen = m_nSize;
                if (m_nSize > m_nBufSize)
                {
                    nLen = m_nBufSize;
                }

                if (!m_pBuf)
                {
                    m_pBuf = new INT8[m_nBufSize + 1];
                }

                m_pHttp->Read(m_pBuf, nLen);
            }
            else if(pRespHeader->GetValue(HH_CTENCODER, sVal))
            {
            	//不支持断点续传
            	if (m_pFile)
            	{
                    m_pFile->Close();
                    SAFEDELETE(m_pFile);
                    CMFile::DeleteFile(m_sTmpFilaName);
            	}
                m_nStart = 0;
                m_nEnd = 0;

            	m_nTotal = m_nSize = 0xFFFFFFFF;
            	UINT32 nLen = m_nSize;
                if (m_nSize > m_nBufSize)
                {
                    nLen = m_nBufSize;
                }
                if (!m_pBuf)
                {
                    m_pBuf = new INT8[m_nBufSize + 1];
                }

                m_pHttp->Read(m_pBuf, nLen);
            }
            else
            	goto err;

            m_cInfo.nSize = m_nTotal;
            m_cInfo.nDowned = m_nStart;
            return;
        }
        else
        {
            CM_ERRP("CMDownloader::OnResponse http ret %d error", httpRet);
            nRet = httpRet;
        }
    }
    else
    {
        
        
        //长度错误，之前的tmp文件未改名成功
        if(nCode==416)
        {
            //删除中间文件
            CMFile::DeleteFile(m_sTmpFilaName);
            
        }
        
        
        CM_ERRP("CMDownloader::OnResponse ret %d error", nCode);
        nRet = nCode;
    }

err:
    //未成功获取信息，清理，等待下次获取
    if (m_pBuf)
    {
        delete m_pBuf;
        m_pBuf = NULL;
    }
	if(nRet == MER_OK)
		nRet = MERN_ERROR;
    m_nStatus = STOPED;
    //重置http
    m_pHttp->Cancel();
    SAFEDELETE(m_pFile);
    if (m_pNotify)
        m_pNotify->OnDownload(nRet, NULL);
}

void CMDownloader::OnRead(UINT32 nCode, INT32 nLen)
{
    UINT32 nRet = MER_OK;

    if (nCode == MER_OK)
    {
    	if(nLen == 0 && m_nSize == 0xFFFFFFFF)
    	{
    		//已完成，
    		CM_ERR("this path shoud not pass");
            m_pFile->Close();
            CMFile::ChangeFileName(m_sTmpFilaName, m_cInfo.sPath);
            SAFEDELETE(m_pFile);
            
            m_nStatus = COMPLETED;
            m_pHttp->Cancel();
            if (m_pNotify)
                m_pNotify->OnDownload(nRet, this);
            return;
    	}
        if (m_nSize > (UINT32)nLen)
        {
            //还有没有下载完成
            m_nSize -= nLen;
        }
        else
        {
            m_nSize = 0;
        }

        m_cInfo.nDowned = m_nEnd > 0 ? m_nEnd - m_nSize : m_nTotal - m_nSize;

        CMDateTime dCur;
        INT32 dLast = m_cInfo.dCurrent;
        m_cInfo.dCurrent = dCur.getTime();
        if (m_cInfo.dCurrent != dLast)
        	m_cInfo.nCurSpd = nLen / (m_cInfo.dCurrent - dLast);

        //写文件
        if (!m_pFile)
        {
            m_pFile = new CMFile();

            if (!m_pFile->Open(m_sTmpFilaName, CMFile::CREATE_W, CMFile::SHARE_R))
            {
                CM_ERRP("CMDownloader::OnRead open file %s failed", (const CHAR*)m_cInfo.sPath);
                nRet = MER_FILEOPEN;
                goto err;
            }
        }
        ASSERT(m_pFile);
        m_pFile->Write((CHAR*)m_pBuf, nLen);

        //回调进度
        if (m_bProgress)
        {
            //UINT32 nRate = m_nEnd > 0 ? m_nEnd * 100 / m_nTotal : (m_nTotal - m_nSize)*100 / m_nTotal ;
            UINT32 nRate = (m_nTotal - m_nSize)*100 / m_nTotal ;
            if (nRate > m_nRate+5 || nRate==100)
            {
                m_nRate = nRate;
                m_pNotify->OnProgress(m_nRate);
            }
        }

        //判断是否完成
        if (m_nSize > 0)
        {
            //还有剩余，继续请求
            nLen = m_nSize;  //nLen无意义了，复用下
            if (m_nSize > m_nBufSize)
            {
                nLen = m_nBufSize;
            }
            m_pHttp->Read(m_pBuf, nLen);
        }
        else if (m_nEnd > 0 && m_nEnd < m_nTotal - 1)
        {
            //仅当前http请求完毕，还有数据
            CMHTTPReqHeader header;
            header.CreateDefault();
            header.AddValue(HH_ATYPE, CMString(L"*/*"));

            char sRange[128]={0,};
            if (m_nEnd + REQ_SIZE < m_nTotal - 1)
#if defined(USE_CURL)
                snprintf(sRange,128,"%d-%d", m_nEnd + 1, m_nEnd + REQ_SIZE);
#else
                snprintf(sRange,128,"bytes = %d-%d", m_nEnd + 1, m_nEnd + REQ_SIZE);
#endif
            else
#if defined(USE_CURL)
                snprintf(sRange,128,"%d-", m_nEnd + 1);
#else
                snprintf(sRange,128,"bytes = %d-", m_nEnd + 1);
#endif
            header.AddValue(HH_RANGER, sRange);
            header.SetUrl(m_cInfo.sUrl);
            m_pHttp->Request(header);
        }
        else
        {
            //已完成，
            m_pFile->Close();
            
            //改名前先删除目标文件
            CMFile::DeleteFile(m_cInfo.sPath);
            
            CMFile::ChangeFileName(m_sTmpFilaName, m_cInfo.sPath);
            
            
            SAFEDELETE(m_pFile);
            
            m_nStatus = COMPLETED;
            m_pHttp->Cancel();
            if (m_pNotify)
                m_pNotify->OnDownload(nRet, this);
        }
        return;
    }
    else
    {
        nRet = nCode;
    }

err:
    m_nStatus = STOPED;
    m_pHttp->Cancel();
	if (m_pFile)
	{
		m_pFile->Close();
		SAFEDELETE(m_pFile);
	}
    if (m_pNotify)
        m_pNotify->OnDownload(nRet, NULL);
}
