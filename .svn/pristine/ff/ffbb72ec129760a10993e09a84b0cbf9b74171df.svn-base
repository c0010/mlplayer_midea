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
#include "cmhttpc.h"

#if defined(PLAT_SYMBIAN)
#include <in_sock.h>
#include <STRING.H>
#elif defined(PLAT_WINCE)
#elif defined(PLAT_AND)
#include <arpa/inet.h>
#endif

const UINT32 REQ_SIZE = 204800;  //请求分块最大大小

CMUrl::CMUrl()
{
    m_nPort = 0;
}

CMUrl::CMUrl(const CMString& sUrl)
{
    CMUrl();
    m_sUrl = sUrl;
}

//parse后，下面的函数才有值
BOOL CMUrl::Parse()
{
    if (m_sUrl == L"")
        return FALSE;

    BOOL bHttp = FALSE;
    CMString sTmp;
    INT32 pos1 = m_sUrl.Find(L"://");
    if (pos1 != -1)
    {
        sTmp = m_sUrl.Left(pos1).MakeLower();
        
        if (sTmp == L"http")
        {
            bHttp = TRUE;
        }
        pos1 += 3;
    }
    else
    {
        //如果没有标识开头，则默认为http://
        bHttp = TRUE;
        pos1 = 0;
    }

    
    //Host and nPort
    INT32 pos2 = m_sUrl.Find(L"/", pos1);
    if (pos2 == pos1) return FALSE;
    if (pos2 == -1)
    {
        //可能没有/号，只有网址
        if (m_sUrl.GetLength() <= pos1)
        {
            //无内容，返回错误
            return FALSE;
        }
        else
        {
            sTmp = m_sUrl.Mid(pos1);
        }
    }
    else
    {
        sTmp = m_sUrl.Mid(pos1, pos2 - pos1);
    }
    
    //端口
    INT32 pos3 = sTmp.Find(L":");
    if (pos3 != -1)
    {
        CMString sTmp1 = sTmp.Mid(pos3 + 1);
        INT32 nPort = _mwtoi((const WCHAR*)sTmp1);
        if (nPort < 0 || nPort > 65535)
        {
            return FALSE;
        }
        m_nPort = nPort;
        sTmp = sTmp.Left(pos3);
    }
    else
    {
        if (bHttp)
            m_nPort = 80; //默认端口
        else
            //暂不支持除http以外的协议
            return FALSE;
    }
    
    //host
    m_sHost = sTmp;

    
    //路径和参数
    if (pos2 != -1)
    {
        //url带路径，检查路径里是否带参数，进行分离
        pos1 = pos2;
        pos2 = m_sUrl.Find(L"?", pos1 + 1);
        
        if (pos2 != -1)
        {
            m_sPath = m_sUrl.Mid(pos1, pos2 - pos1);

            m_sParam = m_sUrl.Mid(pos2);
        }
        else
        {
            m_sPath = m_sUrl.Mid(pos1);
            m_sParam = L"";
        }
    }
    else
    {
        //没指定path，补/
        m_sPath = L"/";
        m_sParam = L"";
    }
    
    ////替换path和param里的空格为%20
    //const CHAR* sPath = (const CHAR*)m_sPath;
    //INT32 nPathLen = strlen(sPath) * 3 + 1;
    //CHAR* pPath = new CHAR[nPathLen];
    //Encode(sPath, strlen(sPath), pPath, nPathLen);
    //m_sPath = pPath;
    //delete[] pPath;

    //const CHAR* sParam = (const CHAR*)m_sParam;
    //INT32 nParamLen = strlen(sParam) * 3 + 1;
    //CHAR* pParam = new CHAR[nParamLen];
    //Encode(sParam, strlen(sParam), pParam, nParamLen);
    //m_sParam = pParam;
    //delete[] pParam;


    ////转换
    //if (bAll)
    //{
    //    if (bAddr)
    //    {
    //        //目前从addr到name没什么意义，不管
    //    }
    //    else
    //    {
    //        //需要检查接入，如果当前没有接入，则不做转换
    //        CMNetConnMgr& mgr = CMGlobal::TheOne().NetConnMgr();
    //        if (mgr.CurrentType() != CMNetConnMgr::NONE)
    //        {
    //            m_sHostAddr = mgr.HostNameToIP(m_sHostName);
    //            if (m_sHostAddr.IsEmpty())
    //            {
    //                //转换失败
    //                CM_ERRP("Parse failed, wrong hostname %s, url is %s", (const CHAR*)m_sHostName, (const CHAR*)m_sUrl);
    //                return FALSE;
    //            }
    //        }
    //    }
    //}

    return TRUE;
}

//返回地址
CMString& CMUrl::Host()
{
    return m_sHost;
}

const CMString& CMUrl::Host() const
{
    return m_sHost;
}


//返回路径，不带地址信息
CMString& CMUrl::Path()
{
    return m_sPath;
}

const CMString& CMUrl::Path() const
{
    return m_sPath;
}

//返回参数
CMString& CMUrl::Param()
{
    return m_sParam;
}

const CMString& CMUrl::Param() const
{
    return m_sParam;
}

//返回port，如果类型是HTTP，Port默认为80，如果url里没带，且类型不知道，则为0，
UINT16& CMUrl::Port()
{
    return m_nPort;
}

const UINT16& CMUrl::Port() const
{
    return m_nPort;
}

//返回原始url
CMString& CMUrl::Url()
{
    return m_sUrl;
}

const CMString& CMUrl::Url() const
{
    return m_sUrl;
}

//重载等于
CMUrl& CMUrl::operator=(const CMUrl& cUrl)
{
    m_sUrl = cUrl.m_sUrl;
    m_sHost = cUrl.m_sHost;
    m_sPath = cUrl.m_sPath;
    m_sParam = cUrl.m_sParam;
    m_nPort = cUrl.m_nPort;

    return *this;
}

////重载等于，输入字符串类型
//CMUrl& CMUrl::operator=(const CMString& sUrl)
//{
//    m_sUrl = sUrl;
//    return *this;
//}

BOOL CMUrl::operator==(const CMUrl& cUrl) const
{
    if (m_sUrl == cUrl.m_sUrl)
        return TRUE;

    if (m_sHost != cUrl.m_sHost)
        return FALSE;

    if (m_sPath != cUrl.m_sPath)
        return FALSE;

    if (m_nPort != cUrl.m_nPort)
        return FALSE;

    if (m_sParam != cUrl.m_sParam)
        return FALSE;

    return TRUE;
}

BOOL CMUrl::IsIP(const CMString& sAddr)
{
#if defined(PLAT_SYMBIAN)
    TInetAddr addr;
    TBuf<20> buf;
    if (sAddr.GetLength() > 16)
        return FALSE;
    buf = (const UINT16*)(const WCHAR*)sAddr;
    INT32 nErr = addr.Input(buf);
    if (nErr != KErrNone)    
        return FALSE;
    return TRUE;
#elif defined(PLAT_WINCE) || defined(PLAT_AND)
    return INADDR_NONE != inet_addr((CMString)sAddr);
#elif defined(PLAT_IOS)
	return FALSE;//FIX ME
#endif
}

CMHttpHeader::CMHttpHeader()
{
}

CMHttpHeader::~CMHttpHeader()
{
}

BOOL CMHttpHeader::AddValue(const CMString &sKey, const CMString &sVal)
{
    CMMap<CMString, CMString>::iterator it = m_mValues.insert(sKey, sVal);
    return it != m_mValues.end();
}

BOOL CMHttpHeader::RmvValue(const CMString &sKey)
{
    int iCount = m_mValues.remove(sKey);
    return iCount != 0;
}

BOOL CMHttpHeader::SetValue(const CMString &sKey, const CMString &sVal)
{
    CMMap<CMString, CMString>::iterator it = m_mValues.find(sKey);
    if (it != m_mValues.end())
    {
        it.value() = sVal;
        return TRUE;
    }
    return FALSE;
}

BOOL CMHttpHeader::GetValue(const CMString &sKey, CMString &sVal) const
{
    //全小写后再进行比较
    CMString sKeyCopy(sKey);
    sKeyCopy.MakeLower();
    for (CMMap<CMString, CMString>::const_iterator it = m_mValues.begin(); 
        it != m_mValues.end(); it++)
    {
        CMString mKeyCopy(it.key());
        mKeyCopy.MakeLower();
        if (sKeyCopy == mKeyCopy)
        {
            sVal = *it;
            return TRUE;
        }
    }

    return FALSE;
}

void CMHttpHeader::Clean()
{
    m_mValues.clear();
}

//CMString CMHttpHeader::ToString() const
//{
//    //目前默认HTTP 1.1
////    CMString sTmp;
////    sTmp.
//    return CMString("");
//}

//CMHttpHeader& CMHttpHeader::operator=(const CMHttpHeader& cHeader)
//{
//    return *this;
//}
FormData::FormData()
{
    dataType = 0;
}

FormData::FormData(const FormData& right)
{
	key = right.key;
	value = right.value;
	dataType = right.dataType;
}

FormData& FormData::operator=(const FormData& right)
{
	key = right.key;
	value = right.value;
	dataType = right.dataType;
	return *this;
}

BOOL FormData::operator==(const FormData& right)
{
	if (key == right.key && value == right.value && dataType == right.dataType)
	{
		return TRUE;
	}
	return FALSE;
}

CMHTTPReqHeader::CMHTTPReqHeader(TYPE type)
{
    m_mMtd = type;
    m_pPostData = NULL;
    m_nPostLen = 0;
}

CMHTTPReqHeader::~CMHTTPReqHeader()
{
    if (m_pPostData)
    {
        SAFEDELETE(m_pPostData);
        m_nPostLen = 0;
    }
}

BOOL CMHTTPReqHeader::CreateDefault()
{
	Clean();
    AddValue(HH_HOST, CMString());
    AddValue(HH_AGENT, CMString(L"MLPlayer"));
    AddValue(HH_ATYPE, CMString(L"*/*"));
    //AddValue(HH_AECODER, CMString(L"gzip,deflate"));
    //AddValue(HH_ACHARSET, CMString(L"utf-8"));
    //AddValue(CMString(L"Keep-Alive"), CMString(L"300"));
    AddValue(CMString(L"Connection"), CMString(L"keep-alive"));
    return TRUE;
}

BOOL CMHTTPReqHeader::SetUrl(const CMString& sUrl)
{
    CMUrl cUrl(sUrl);

    return SetUrl(cUrl);
}

BOOL CMHTTPReqHeader::SetUrl(const CMUrl& cUrl)
{
    m_cUrl = cUrl;
    
    //解析地址
    if (!m_cUrl.Parse())
    {
        CM_ERRP("CMHTTPReqHeader::SetUrl parse %s failed", (const CHAR*)(CMString)m_cUrl.Url());
        m_cUrl = CMString("");
        return FALSE;
    }

//    CM_LOGP(CM_LOGL_INFO, "Request URL is %s.", (const CHAR*)(CMString)m_cUrl.Url());

    //添加host信息,优先addr
    CHAR sTmp[100];
    snprintf(sTmp, 100,"%s:%u", (const CHAR*)m_cUrl.Host(), m_cUrl.Port());

    AddValue(HH_HOST, CMString(sTmp));
    return TRUE;    
}

CMUrl& CMHTTPReqHeader::GetUrl()
{
    return m_cUrl;
}

CMHTTPReqHeader& CMHTTPReqHeader::operator=(const CMHTTPReqHeader& cHeader)
{
    m_cUrl = cHeader.m_cUrl;
    m_mMtd = cHeader.m_mMtd;

    m_mValues.clear();
    //for (CMMap<CMString, CMString>::const_iterator it = cHeader.m_mValues.begin();
    //    it != cHeader.m_mValues.end(); it++)
    //{
    //    m_mValues.insert(it.key(), it.value());
    //}
    m_mValues.unite(cHeader.m_mValues);

    if (m_pPostData)
    {
        SAFEDELETE(m_pPostData);
        m_nPostLen = 0;
    }

    if (cHeader.m_nPostLen > 0)
    {
		m_pPostData = new CHAR[cHeader.m_nPostLen];
		memcpy(m_pPostData, cHeader.m_pPostData, cHeader.m_nPostLen);
		m_nPostLen = cHeader.m_nPostLen;
    }

    m_lstPost = cHeader.m_lstPost;
    return *this;
}

void CMHTTPReqHeader::SetPostData(const CHAR* pData, INT32 nLen)
{
    ClearPostData();

    CM_LOGP(CM_LOGL_DEBUG, "SetPostData len %d value %s", nLen, pData);

    m_nPostLen = nLen;
    m_pPostData = new CHAR[nLen];
    memcpy(m_pPostData, pData, nLen);

    //设置头
    CHAR sPostLen[16];
    snprintf(sPostLen, 16,"%d", m_nPostLen);
    AddValue(HH_CLENGTH, CMString(sPostLen));

}

void CMHTTPReqHeader::ClearPostData()
{
    if (m_pPostData)
    {
        SAFEDELETE(m_pPostData);
        m_nPostLen = 0;
    }
}

//由Format改为使用sprintf
CHAR* CMHTTPReqHeader::ToString(INT32& nLen)
{
    CMString sTmp, sTmp1;

    if (m_mMtd == POST)
    {
        sTmp = L"POST";
    }
    else if (m_mMtd == HEAD)
    {
        sTmp = L"HEAD";
    }
    else 
    {
        sTmp = L"GET";        
    }
    
    //计算总长度
	nLen = sTmp.GetLength() + m_cUrl.Path().GetLength() + m_cUrl.Param().GetLength() + 12;
    for(CMMap<CMString, CMString>::const_iterator it = m_mValues.begin(); it != m_mValues.end(); it++)
    {
        nLen += it.key().GetLength() + it.value().GetLength() + 4;
    }
    if (m_mMtd == POST)
    {
        nLen += 2;  //开始的额外换行
        nLen += m_nPostLen;
        if (m_nPostLen < 2 || m_pPostData[m_nPostLen - 2] != '\r' || m_pPostData[m_nPostLen - 2] != '\r')
        {
            nLen += 2; //xml最后不是换行，发送时需要添加
        }
    }
    nLen += 2;  //最后的换行
//    CM_ERRP("len %d", nLen);

    //拷贝到指定新建缓存
    CHAR* pRet = new CHAR[nLen + 1];
    memset(pRet, 0, nLen + 1);
    CHAR* pCur = pRet;
    snprintf(pCur, nLen + 1,"%s %s HTTP/1.1\r\n", (const CHAR*)sTmp, (const CHAR*)(m_cUrl.Path() +
            m_cUrl.Param()));
    pCur += strlen(pCur);

    for(CMMap<CMString, CMString>::const_iterator it = m_mValues.begin(); it != m_mValues.end(); it++)
    {
    	//!这里无视了const
    	snprintf(pCur, nLen + 1,"%s: %s\r\n", (const CHAR*)(CMString)it.key(), (const CHAR*)(CMString)it.value());
        pCur += strlen(pCur);
    }

    if (m_mMtd == POST)
    {
        *pCur = '\r';
        pCur++;
        *pCur = '\n';
        pCur++;

        memcpy(pCur, m_pPostData, m_nPostLen);
        pCur += m_nPostLen;

        if (m_nPostLen < 2 || m_pPostData[m_nPostLen - 2] != '\r' || m_pPostData[m_nPostLen - 2] != '\r')
        {
            //添加换行
            *pCur = '\r';
            pCur++;
            *pCur = '\n';
            pCur++;
        }
    }

    //添加换行
    *pCur = '\r';
    pCur++;
    *pCur = '\n';
    pCur++;

    return pRet;
}

BOOL CMHTTPReqHeader::SetFormPostData(CMList<FormData>& lstData)
{
	m_lstPost = lstData;

    for(CMList<FormData>::const_iterator it = m_lstPost.begin(); it != m_lstPost.end(); it++)
    {
    	const FormData& fd = *it;

    	CM_LOGP(CM_LOGL_DEBUG, "SetFormPostData type %d key %s value %s", fd.dataType, fd.key.c_str(), fd.value.c_str());
    }

	return TRUE;
}

void CMHTTPReqHeader::Clean()
{
	CMHttpHeader::Clean();

	ClearPostData();
	m_lstPost.clear();
}

//BOOL CMHTTPReqHeader::Parse(const INT8* pData, INT32& nLen)
//{
//    INT32 nSize = nLen;
//    INT32 nTmp = 0;
//    const CHAR* pTmp = (const CHAR*)pData;
//
//    //找到头的结束符，2个LRCF
//    BOOL bFound = FALSE;
//    while (*pTmp != '\0' && nTmp <= nSize - 4)
//    {
//        if (*pTmp == '\r' && *(pTmp+1) == '\n' && *(pTmp+2) == '\r' && *(pTmp+3) == '\n')
//        {
//            bFound = TRUE;
//            break;
//        }
//        pTmp++;
//        nTmp++;
//    }
//
//    if (!bFound)
//    {
//        nLen = -1;       //返回没有结束符的情况需要特殊处理
//        return FALSE;
//    }
//
//    const CHAR* pTmp1 = (const CHAR*)pData;
//    const CHAR* pTmp2 = pTmp1;
//    //解析第一行 GET/POST/HEAD
//    if (*pTmp1 == 'G' && *(pTmp1+1) == 'E' && *(pTmp1+2) == 'T' && *(pTmp1+3) == ' ')
//    {
//        m_mMtd = GET;
//        pTmp1 += 4;
//    }
//    else if (*pTmp1 == 'P' && *(pTmp1+1) == 'O' && *(pTmp1+2) == 'S' && *(pTmp1+3) == 'T')
//    {
//        m_mMtd = POST;
//        pTmp1 += 5;
//    }
//    else if (*pTmp1 == 'H' && *(pTmp1+1) == 'E' && *(pTmp1+2) == 'A' && *(pTmp1+3) == 'D')
//    {
//        m_mMtd = HEAD;
//         pTmp1 += 5;
//   }
//    else
//    {
//        nLen = -1;
//        return FALSE;
//    }
//
//    //去掉可能的空格
//    while (*pTmp1 == '\t' || *pTmp1 == ' ')
//    {
//        pTmp1++;
//    }
//
//    //接下来是请求内容
//    pTmp2 = pTmp1;
//    while (pTmp2 < pTmp && (*pTmp2 != '\r' || *(pTmp2+1) != '\n'))
//    {
//        pTmp2++;
//    }
//
//    CMString sTmp(pTmp1, pTmp2 - pTmp1 - 9);
//    //指针挪到下行开始
//    pTmp1 = pTmp2 + 2;
//
//    //解析余下内容
//    while (pTmp1 < pTmp)
//    {
//        pTmp2 = pTmp1;
//        bFound = FALSE;  //分界符:
//        while (*pTmp2 != '\r' || *(pTmp2+1) != '\n')
//        {
//            if (*pTmp2 == ':')
//            {
//                bFound = TRUE;
//                break;
//            }
//            pTmp2++;
//        }
//        if (!bFound)
//        {
//            return FALSE;
//        }
//        CMString sKey(pTmp1, pTmp2 - pTmp1);
//
//        pTmp2++;
//
//        //去掉可能的空格
//        while (*pTmp2 == '\t' || *pTmp2 == ' ')
//        {
//            pTmp2++;
//        }
//
//        pTmp1 = pTmp2;
//        while (pTmp2 < pTmp && (*pTmp2 != '\r' || *(pTmp2+1) != '\n'))
//        {
//            pTmp2++;
//        }
//        //要去掉末尾的Http1.1
//        CMString sValue(pTmp1, pTmp2 - pTmp1);
//
//        AddValue(sKey, sValue);
//
//        pTmp1 = pTmp2 + 2;
//
//        //如果是host参数，则构造sql
//        if (sKey == HH_HOST)
//        {
//            SetUrl(sValue + sTmp);
//        }
//    }
//
//    nLen = pTmp - (const CHAR*)pData + 4; //末尾的回车符也算长度
//    return TRUE;
//}

CMHTTPRspHeader::CMHTTPRspHeader()
{
	m_bChunked = FALSE;
}

BOOL CMHTTPRspHeader::Parse(const INT8* pData, INT32& nLen)
{
    INT32 nSize = nLen;
    INT32 nTmp = 0;
    const CHAR* pTmp = (const CHAR*)pData;
    
    //找到头的结束符，2个LRCF
    BOOL bFound = FALSE;
    while (*pTmp != '\0' && nTmp <= nSize - 4)
    {
        if (*pTmp == '\r' && *(pTmp+1) == '\n' && *(pTmp+2) == '\r' && *(pTmp+3) == '\n')
        {
            bFound = TRUE;
            break;
        }
        pTmp++;
        nTmp++;
    }
    
    if (!bFound)
    {
        nLen = -1;       //返回没有结束符的情况需要特殊处理
        return FALSE;
    }
    
    const CHAR* pTmp1 = (const CHAR*)pData;
    const CHAR* pTmp2 = pTmp1;
    //解析第一行 HTTP/1.0200OK
    if (*pTmp1 == 'H' && *(pTmp1+1) == 'T' && *(pTmp1+2) == 'T' && *(pTmp1+3) == 'P' && 
        *(pTmp1+4) == '/' && *(pTmp1+5) == '1' && *(pTmp1+6) == '.')
    {
        pTmp1 += 8;
        
        //去掉可能的空格
        while (*pTmp1 == '\t' || *pTmp1 == ' ')
        {
            pTmp1++;
        }
        
        //接下来是3位的错误码
        CMString sRet(pTmp1, 3);
        INT32 nRet = _mwtoi(sRet);
        if (nRet == -1)
            //没有值
            return FALSE;
        m_nRet = nRet;
        pTmp1 += 3;
        
        //去掉可能的空格
        while (*pTmp1 == '\t' || *pTmp1 == ' ')
        {
            pTmp1++;
        }
        
        pTmp2 = pTmp1;        
        while (pTmp2 < pTmp && (*pTmp2 != '\r' || *(pTmp2+1) != '\n'))
        {
            pTmp2++;
        }
        
        m_sRet = CMString(pTmp1, pTmp2 - pTmp1);
        //指针挪到下行开始
        pTmp1 = pTmp2 + 2;
    }
    else
        return FALSE;
    
    //解析余下内容
    while (pTmp1 < pTmp)
    {
        pTmp2 = pTmp1;
        bFound = FALSE;  //分界符:
        while (*pTmp2 != '\r' || *(pTmp2+1) != '\n')
        {
            if (*pTmp2 == ':')
            {
                bFound = TRUE;
                break;
            }
            pTmp2++;
        }
        if (!bFound)
        {
            return FALSE;
        }
        CMString sKey(pTmp1, pTmp2 - pTmp1);
        pTmp2++;
        
        //去掉可能的空格
        while (*pTmp2 == '\t' || *pTmp2 == ' ')
        {
            pTmp2++;
        }
        
        pTmp1 = pTmp2;        
        while (pTmp2 < pTmp && (*pTmp2 != '\r' || *(pTmp2+1) != '\n'))
        {
            pTmp2++;
        }
        CMString sValue(pTmp1, pTmp2 - pTmp1);
        
        AddValue(sKey, sValue);
        pTmp1 = pTmp2 + 2;
    }
    nLen = pTmp - (const CHAR*)pData + 4; //末尾的回车符也算长度
    return TRUE;
}

CMString CMHTTPRspHeader::ToString() const
{
	char chead[1024] = {0,};
	char ctmp[200] = {0,};

	CMString sret = m_sRet;

	snprintf(chead,1024,"HTTP/1.1 %d %s\r\n",m_nRet,(const CHAR*)sret);

	CMString skey,svalue;

    for(CMMap<CMString, CMString>::const_iterator it = m_mValues.begin(); it != m_mValues.end(); it++)
    {
		skey = it.key();
		svalue = it.value();
		snprintf(ctmp,200,"%s: %s\r\n", (const CHAR*)skey, (const CHAR*)svalue);
		strcat(chead,ctmp);
    }
	strcat(chead,"\r\n");
    return chead;
}

UINT32 CMHTTPRspHeader::GetHttpReturn(CMString* sDisp) const
{
    if (sDisp != NULL)
    {
        *sDisp = m_sRet;
    }
    return m_nRet;
}

