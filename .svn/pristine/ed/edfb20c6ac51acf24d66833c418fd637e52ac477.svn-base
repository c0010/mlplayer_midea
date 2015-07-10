#include "stdafx.h"
#include "cmhttpserver.h"
#include "cmnetworkmgr.h"
#include "cmfile.h"

#define REQ_HEAD_MAX_LEN      1024
const UINT32 BUF_SIZE = 4096;    //缓冲最大大小
const UINT32 REQ_SIZE = 204800;  //请求分块最大大小
CMHttpSNotify::CMHttpSNotify(CMSocketC* pSocketC, CMHttpS* pHttpS) : m_pSocketC(pSocketC), m_pHttpS(pHttpS)
{
    m_pSocketC->SetNotify(this);
    m_pHttpC = NULL;
    m_pFile = NULL;
    m_pHeadBuf = NULL;
    m_nHeadPos = 0;
    m_nTotalSize = 0;
    m_nSize = 0;
    m_nSendSize = 0;
    m_nPos = 0;
    m_pBuf = new INT8[BUF_SIZE + 1];
    m_bInService = FALSE;
    m_nStatus = 0;

    m_pHttpC = new CMHttpC(this);
}

CMHttpSNotify::~CMHttpSNotify()
{
    SAFEDELETE(m_pSocketC)

    SAFEDELETE(m_pBuf)

    SAFEDELETE(m_pHeadBuf)

    SAFEDELETE(m_pFile)

    SAFEDELETE(m_pHttpC)
}

void CMHttpSNotify::ChangeSocket(CMSocketC* pSocketC)
{
    SAFEDELETE(m_pSocketC);
    m_pSocketC = pSocketC;
    m_pSocketC->SetNotify(this);
}
void CMHttpSNotify::Start()
{
    m_bInService = TRUE;
    m_nStatus = 0;
    m_nTotalSize = 0;

    //开始接收请求头
    if (!m_pHeadBuf)
    {
        m_pHeadBuf = new INT8[REQ_HEAD_MAX_LEN];
    }

    memset(m_pHeadBuf, 0, REQ_HEAD_MAX_LEN);
    m_pSocketC->Recv(m_pHeadBuf, REQ_HEAD_MAX_LEN);
}

void CMHttpSNotify::OnConnect(UINT32 nCode)
{
    CM_ERR("CMHttpSNotify::OnConnect ");
}

void CMHttpSNotify::OnRecv(UINT32 nCode, INT32 nLen)
{
    if (nCode == MER_OK)
    {
        //是不是请求头
        INT32 nTmp = nLen;
        if (!m_cReqHeader.Parse(m_pHeadBuf, nTmp))
        {
            m_nHeadPos += nLen;
            if (nTmp == -1 && m_nHeadPos < REQ_HEAD_MAX_LEN)
            {
                //可能头还没收全，继续收
                CM_LOGP(CM_LOGL_DEBUG, "CMHttpSNotify::OnRecv header part %d",  nLen);
                m_pSocketC->Recv(m_pHeadBuf + m_nHeadPos , REQ_HEAD_MAX_LEN - m_nHeadPos);
                return;
            }
            CM_LOGP(CM_LOGL_DEBUG, "CMHttpSNotify::OnRecv header failed is %s", (const CHAR*)CMString((const CHAR*)m_pHeadBuf, nLen));
            return;
        }

        CMString sRange;
        m_cReqHeader.GetValue(HH_RANGER, sRange);

        //是外部请求，构造CMHttp请求
        m_rUrl = m_pHttpS->ToRemote(m_cReqHeader.GetUrl());
        if (!m_rUrl.Url().IsEmpty())
        {
            CMHTTPReqHeader header;
            header.CreateDefault();

            if (sRange.IsEmpty())
            {
				if(CMNetConnMgr::Instance().CurrentType() == CMNetConnMgr::CMWAP)
	            {
    	            sRange.Format(L"bytes = 0-%d", REQ_SIZE - 1);
                    header.AddValue(HH_RANGER, sRange);
	            }
	            else
                {
                    //请求没有指定range，不发送此参数	
                }
            }
            else
            {
                //暂时此流程不支持
                ASSERT(FALSE);
             //   if(CMGlobal::TheOne().NetConnMgr().CurrentType() == CMNetConnMgr::CMWAP)
	            //{
             //       //如果请求包含range信息，对于跨CMWAP网关也需要处理
             //       UINT32 nStart = 0;
             //       UINT32 nEnd = 0;

             //       INT32 nPos1 = sRange.Find(L"-");
             //       if (nPos1 > 0)
             //       {
             //           INT32 nPos2 = sRange.Find(L"=");
             //           nStart= _mwtoi((const WCHAR*)sRange.Mid(nPos2 + 2, nPos1 - nPos2 - 2));
             //           INT32 nLen = sRange.GetLength();
             //           if (nLen > nPos1 + 1)
             //           {
             //               nEnd = _mwtoi((const WCHAR*)sRange.Mid(nPos2 + 1, nLen - 1));
             //           }
             //       }

             //       if (nEnd != 0)
             //       {
             //           m_nSendSize = nEnd - nStart + 1;
             //       }
             //       else
             //       {
             //           m_nSendSize = m_pFile->GetLength() - nStart;
             //           nEnd = nStart + m_nSendSize - 1;
             //       }
             //   }
             //   else
             //       header.AddValue(HH_RANGER, sRange);
            }

            header.SetUrl(m_rUrl);
            m_pHttpC->Request(header);
            m_nStatus = 1;
            return;
        }

        //是本地文件请求，构造发送信息
        //const CMString* pFile = m_pHttpS->GetFile(m_cReqHeader.GetUrl());
        //if (pFile)
        //{
        //    if (!m_pFile)
        //    {
        //        m_pFile = new CMFile();
        //    }
        //    if (!m_pFile->Open(*pFile, CMFile::OPEN_R_EXIST, CMFile::SHARE_R))
        //    {
        //        //打开失败
        //        CM_ERRP("CMHttpSNotify::OnRecv Open file  %s not exist", (const CHAR*)CMString(*pFile));
        //        return;
        //    }

        //    UINT32 nStart = 0;
        //    UINT32 nEnd = 0;
        //    if (!sRange.IsEmpty())
        //    {
        //        INT32 nPos1 = sRange.Find(L"-");
        //        if (nPos1 > 0)
        //        {
        //            INT32 nPos2 = sRange.Find(L"=");
        //            nStart= _mwtoi((const WCHAR*)sRange.Mid(nPos2 + 2, nPos1 - nPos2 - 2));
        //            INT32 nLen = sRange.GetLength();
        //            if (nLen > nPos1 + 1)
        //            {
        //                nEnd = _mwtoi((const WCHAR*)sRange.Mid(nPos2 + 1, nLen - 1));
        //            }
        //        }
        //    }

        //    if (nStart != 0)
        //        m_pFile->Seek(nStart);
        //    if (nEnd != 0)
        //    {
        //        m_nSendSize = nEnd - nStart + 1;
        //    }
        //    else
        //    {
        //        m_nSendSize = m_pFile->GetLength() - nStart;
        //        nEnd = nStart + m_nSendSize - 1;
        //    }

        //    //获取成功，返回响应头结果到Socket处
        //    CMHTTPRspHeader resp;
        //    resp.SetRet(200, CMString("OK"));
        //    if (!sRange.IsEmpty())
        //    {
        //        //如果有range，就要返回range,  bytes 0-2668566/2668567
        //        CMString sSendRange;
        //        sSendRange.Format(L"bytes %d-%d/%d", nStart, nEnd, m_nSendSize);
        //        resp.AddValue(HH_CRANGE, sSendRange);
        //    }
        //    else
        //    {
        //        //否则返回content-lengthW
        //        CMString sSendSize;
        //        sSendSize.Format(L"%d", m_nSendSize);
        //        resp.AddValue(HH_CLENGTH, sSendSize);
        //    }
        //    resp.AddValue(HH_CTYPE, L"application/x-shockwave-flash");
        //    CMString sHeader = resp.ToString();
        //    CM_LOGP(CM_LOGL_DEBUG, "%s", (const CHAR*)sHeader);

        //    m_pSocketC->Send((const INT8*)(const CHAR*)sHeader, sHeader.GetLength());

        //    m_nStatus = 3;
        //    return;
        //}
    }
    else
    {
        CM_ERRP("CMHttpSNotify::OnRecv ret %d error", nCode);
    }
err:
    //未成功获取信息，清理，等待下次获取

    m_bInService = FALSE;
    m_nSize = 0;

    if (nCode == MERN_TIMEOUT)
    {
        m_pSocketC->Close();
    }
    else
    {
        char response[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
        m_pSocketC->Send((INT8*)response, strlen(response));
    }

    //重置http
    m_pHttpC->Cancel();

}

void CMHttpSNotify::OnSend(UINT32 nCode, INT32 nLen)
{
    if (nCode == MER_OK)
    {
        switch(m_nStatus)
        {
        case 1:
            if (m_nSize != 0)
            {
                nLen = m_nSize; //重用nLen
                if (m_nSize > BUF_SIZE)
                {
                    nLen = BUF_SIZE;
                }

                m_pHttpC->Read(m_pBuf, nLen);

                m_nStatus = 2;
            }
            else
            {
                //m_nSize为0表示有错误，中止继续操作
                CM_ERR("CMHttpSNotify::OnSend 0");
                m_pSocketC->Close();
            }
            break;
        case 2:
            if (nLen < m_nSendSize)
            {
                m_nPos += nLen;
                m_nSendSize -= nLen;
                m_pSocketC->Send(m_pBuf + m_nPos, m_nSendSize);
            }
            else
            {
                //判断是否完成
                if (m_nSize > 0)
                {
                    //还有剩余，继续请求
                    nLen = m_nSize;  //nLen无意义了，复用下
                    if (m_nSize > BUF_SIZE)
                    {
                        nLen = BUF_SIZE;
                    }
                    m_pHttpC->Read(m_pBuf, nLen);
                }
                else if (m_nTotalSize > 0 && m_nEnd < m_nTotalSize - 1)
                {
                    //仅当前http请求完毕，
                    CMHTTPReqHeader header;
                    header.CreateDefault();

                    CMString sRange;
                    if (m_nEnd + REQ_SIZE < m_nTotalSize - 1)
                        sRange.Format(L"bytes = %d-%d", m_nEnd + 1, m_nEnd + REQ_SIZE);
                    else
                        sRange.Format(L"bytes = %d-", m_nEnd + 1);
                    header.AddValue(HH_RANGER, sRange);
                    header.SetUrl(m_rUrl);
                    m_pHttpC->Request(header);
                }
                else
                {
                    //已完成，开始等待后续接收
                    Start();
                    //m_bInService = FALSE;
                    //m_pSocketC->Close();
                    //m_pHttpC->Cancel();
                }
            }
            break;
        case 3:

            if (m_nSendSize > BUF_SIZE)
            {
                nLen = BUF_SIZE;
            }
            else
            {
                nLen = m_nSendSize;
            }
            //if (m_pBuf)
            //{
            //    delete m_pBuf;
            //    m_pBuf = NULL;
            //}
            //m_pBuf = new INT8[nLen + 1];
            m_nPos = 0;
            m_pFile->Read((CHAR*)m_pBuf, nLen);
            m_pSocketC->Send(m_pBuf, nLen);
            m_nStatus = 4;
            break;
        case 4:
            if (nLen < m_nSendSize && m_nPos + nLen < BUF_SIZE)   
            {
                //没有发送完
                m_nPos += nLen;
                m_nSendSize -= nLen;
                m_pSocketC->Send(m_pBuf + m_nPos, m_nSendSize);
            }
            else
            {
                m_nSendSize -= nLen;
                if (m_nSendSize > 0)
                {
                    nLen = m_nSendSize;
                    if (m_nSendSize > BUF_SIZE)
                    {
                        nLen = BUF_SIZE;
                    }
                    m_nPos = 0;
                    m_pFile->Read((CHAR*)m_pBuf, nLen);
                    m_pSocketC->Send(m_pBuf, nLen);
                }
                else
                {
                    //已完成，开始等待后续接收
                    Start();
                    //m_bInService = FALSE;
                    //m_pHttpC->Cancel();
                }
            }
            break;
        default:
            CM_ERR("CMHttpSNotify::OnSend status 0");
        }

        return;
    }

    CM_ERRP("CMHttpSNotify::OnSend ret %d error", nCode);
    m_bInService = FALSE;
    m_pSocketC->Close();
    m_pHttpC->Cancel();

}

void CMHttpSNotify::OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader)
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
                    m_pHttpC->Request();
                    return;
                }
            }            

            sVal.Empty();
            pRespHeader->GetValue(HH_CRANGE, sVal);

            sVal.Trim();

            CMHTTPRspHeader header;
            header.SetRet(200, CMString("OK"));
            header.AddValue(HH_CTYPE, L"application/x-shockwave-flash");

            if (!sVal.IsEmpty())
            {
                INT32 nPos1 = sVal.Find(L" ");
                INT32 nPos2 = sVal.Find(L"-");
                INT32 nPos3 = sVal.Find(L"/");
                if (nPos1 <= 0 || nPos2 <= 0 || nPos3 <= 0)
                {
                    CM_ERRP("CMHttpSNotify::OnResponse wrong content-range %s", (const CHAR*)sVal);
                    goto err;
                }

                m_nStart= _mwtoi((const WCHAR*)sVal.Mid(nPos1 + 1, nPos2 - nPos1 - 1));
                m_nEnd = _mwtoi((const WCHAR*)sVal.Mid(nPos2 + 1, nPos3 - nPos2 - 1));
                m_nSize = m_nEnd - m_nStart + 1;

                if (m_nTotalSize == 0)
                {
                    //对于第一次http返回，需要返回结果给socket
                    m_nTotalSize = _mwtoi((const WCHAR*)sVal.Mid(nPos3 + 1));
                    CMString sSendSize;
                    sSendSize.Format(L"%d", m_nTotalSize);
                    header.AddValue(HH_CLENGTH, sSendSize);
                    CMString sHeader = header.ToString();

                    CM_LOGP(CM_LOGL_INFO, "%s", (const CHAR*)sHeader);

                    m_pSocketC->Send((INT8*)(const CHAR*)sHeader, sHeader.GetLength());
                }
                else
                {
                    ASSERT(m_nTotalSize == _mwtoi((const WCHAR*)sVal.Mid(nPos3 + 1)));
                    ASSERT(m_nStatus == 2);
                    ASSERT(m_nEnd - m_nStart < REQ_SIZE);

                    UINT32 nLen = m_nSize;
                    if (m_nSize > BUF_SIZE)
                    {
                        nLen = BUF_SIZE;
                    }
                    m_pHttpC->Read(m_pBuf, nLen);
                }
            }
            else
            {
                if (!pRespHeader->GetValue(HH_CLENGTH, sVal))
                {
                    CM_ERR("CMHttpSNotify::OnResponse no content-length");
                    goto err;
                }

                m_nTotalSize = 0;  //此值无效
                m_nSize = _mwtoi(sVal);

                //获取响应头成功，返回结果到Socket处
                CMString sSendSize;
                sSendSize.Format(L"%d", m_nSize);
                header.AddValue(HH_CLENGTH, sSendSize);
                CMString sHeader = header.ToString();

                CM_LOGP(CM_LOGL_INFO, "%s", (const CHAR*)sHeader);

                m_pSocketC->Send((INT8*)(const CHAR*)sHeader, sHeader.GetLength());
            }
           
            return;
        }
        else
        {
            CM_ERRP("CMHttpSNotify::OnResponse http ret %d error", httpRet);
            nRet = httpRet;
        }
    }
    else
    {
        CM_ERRP("CMHttpSNotify::OnResponse ret %d error", nCode);
        nRet = nCode;
    }

err:
    //未成功获取信息，清理，等待下次获取
    //if (m_pBuf)
    //{
    //    delete m_pBuf;
    //    m_pBuf = NULL;
    //}

    m_bInService = FALSE;

    //if (nCode == MERN_TIMEOUT)
    //{
    //    m_pSocketC->Close();
    //}
    //else
    //{
        char response[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
        m_nSize = 0;
        m_pSocketC->Send((INT8*)response, strlen(response));
    //}

    //重置http
    m_pHttpC->Cancel();
}

void CMHttpSNotify::OnRead(UINT32 nCode, INT32 nLen)
{
    if (nCode == MER_OK)
    {
        if (m_nSize > (UINT32)nLen)
        {
            //还有没有下载完成
            m_nSize -= nLen;
        }
        else
        {
            m_nSize = 0;
        }

        //接收完成，往回传
        m_nSendSize = nLen;
        m_nPos = 0;
        m_pSocketC->Send(m_pBuf, nLen);

        return;
    }

    CM_ERRP("CMHttpSNotify::OnRead ret %d error", nCode);

    m_bInService = FALSE;

    m_pSocketC->Close();

    m_pHttpC->Cancel();
}

CMHttpS* CMHttpS::m_pHttpS = NULL;

CMHttpS& CMHttpS::Instance()
{
    if (!m_pHttpS)
    {
        m_pHttpS = new CMHttpS();
        m_pHttpS->Start();
    }
    return *m_pHttpS;
}

CMHttpS::CMHttpS() : m_pSocketS(NULL)
{
    m_nPort = 8010;
}

CMHttpS::~CMHttpS()
{
    Stop();
    if (m_pSocketS)
        delete m_pSocketS;

    //for(CMMap<CMUrl*, CMUrl>::iterator i = m_mapUrl.begin();i != m_mapUrl.end();i++)
    //{
    //    CMUrl* pKey = i.key();
    //    delete pKey;
    //}
    //m_mapUrl.clear();

    //for(CMMap<CMUrl*, CMString>::iterator i = m_mapFile.begin();i != m_mapFile.end();i++)
    //{
    //    CMUrl* pKey = i.key();
    //    delete pKey;
    //}
    //m_mapFile.clear();

}

//void CMHttpS::SetUrl(const CMUrl& rUrl, const CMUrl& lUrl)
//{
//    CMUrl* pNew = new CMUrl(lUrl);
//    pNew->Parse();
//    m_mapUrl.insert(pNew, rUrl);
//}
//
//void CMHttpS::SetFile(const CMString& sFileName, const CMUrl&  lUrl)
//{
//    CMUrl* pNew = new CMUrl(lUrl);
//    pNew->Parse();
//    m_mapFile.insert(pNew, sFileName);
//}
//
//const CMUrl* CMHttpS::GetUrl(const CMUrl& lUrl)
//{
//    for(CMMap<CMUrl*, CMUrl>::iterator i = m_mapUrl.begin();i != m_mapUrl.end();i++)
//    {
//        CMUrl* pKey = i.key();
//        if (lUrl == *pKey)
//        {
//            return  &i.value();            
//        }
//    }
//
//    return NULL;
//}
//
//const CMString* CMHttpS::GetFile(const CMUrl& lUrl)
//{
//    for(CMMap<CMUrl*, CMString>::iterator i = m_mapFile.begin();i != m_mapFile.end();i++)
//    {
//        CMUrl* pKey = i.key();
//        if (lUrl == *pKey)
//        {
//            return &i.value();            
//        }
//    }
//
//    return NULL;
//}

void CMHttpS::SetRemote(const CMUrl& rUrl)
{
    m_remote = rUrl;
    CMString& sUrl =m_remote.Url();
    //只保留主机和端口
    sUrl.Format(L"http://%s:%d", (const WCHAR*)rUrl.Host(), rUrl.Port());
    if (!m_remote.Parse())
    {
        CM_ERR("CMHttpS::SetRemote failed");
    }
}
void CMHttpS::SetFolder(const CMString& sFolder)
{
    m_folder = sFolder;
}

//把本地url变成远程url
CMUrl CMHttpS::ToRemote(const CMUrl& lUrl)
{
    CMUrl rUrl;
    CMString& sUrl = rUrl.Url();
    if (lUrl.Param().IsEmpty())
        sUrl.Format(L"http://%s:%d%s", (const WCHAR*)m_remote.Host(), m_remote.Port(), (const WCHAR*)lUrl.Path());
    else
        sUrl.Format(L"http://%s:%d%s%s", (const WCHAR*)m_remote.Host(), m_remote.Port(), (const WCHAR*)lUrl.Path(), (const WCHAR*)lUrl.Param());
    if (rUrl.Parse())
        return rUrl;
    else
        return CMUrl();
}

//把远程url变成本地url
CMUrl CMHttpS::GetLocal(const CMUrl& rUrl)
{
    CMUrl lUrl;
    CMString& sUrl = lUrl.Url();
    if (rUrl.Param().IsEmpty())
        sUrl.Format(L"http://localhost:%d%s", m_nPort, (const WCHAR*)rUrl.Path());
    else
        sUrl.Format(L"http://localhost:%d%s%s", m_nPort, (const WCHAR*)rUrl.Path(), (const WCHAR*)rUrl.Param());
    if (lUrl.Parse())
        return lUrl;
    else
        return CMUrl();
}

void CMHttpS::SetPort(UINT16 nPort)
{
    m_nPort = nPort;
}

BOOL CMHttpS::Start()
{
    if (!m_pSocketS)
    {
        m_pSocketS = new CMSocketS(this);
    }

    m_pSocketS->Bind(m_nPort);

    m_pSocketS->Listen();

    return TRUE;
}

void CMHttpS::Stop()
{
    if (m_pSocketS)
        m_pSocketS->Stop();

    //断开所有连接
    for (CMList<CMHttpSNotify*>::iterator it = m_lstNotify.begin(); it != m_lstNotify.end(); it++)
    {
        CMHttpSNotify* pNotify = *it;
        delete pNotify;
    }
    m_lstNotify.clear();
}

void CMHttpS::OnAccept(UINT32 nCode, CMSocketC* pSocketC)
{
    if (nCode == MER_OK && pSocketC != NULL)
    {
        //如果现有处理类有空余，直接重用，否则才创建
        CMHttpSNotify* pNotify = NULL;
        for (CMList<CMHttpSNotify*>::iterator it = m_lstNotify.begin(); it != m_lstNotify.end(); it++)
        {
            pNotify = *it;
            if (!pNotify->IsInService())
            {
                break;
            }
        }
        if (pNotify != NULL)
        {
            pNotify->ChangeSocket(pSocketC);
        }
        else
        {
            pNotify = new CMHttpSNotify(pSocketC, this);
            m_lstNotify.push_back(pNotify);
        }
        pNotify->Start();
    }
}
