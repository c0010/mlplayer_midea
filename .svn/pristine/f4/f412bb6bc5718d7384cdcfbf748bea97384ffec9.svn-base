#pragma once

#include "cmhttpc.h"

class CMHttpS;

class CMHttpSNotify : public IMNotifySocketC, IMNotifyHttpC
{
public:
    CMHttpSNotify(CMSocketC* pSocketC, CMHttpS* pHttpS);
    ~CMHttpSNotify();

    BOOL IsInService() {return m_bInService;};
    void ChangeSocket(CMSocketC* pSocketC);

    //开始接收http数据
    void Start();

    void OnConnect(UINT32 nCode);
    //接收到请求
    void OnRecv(UINT32 nCode, INT32 nLen);
    //回应发送成功
    void OnSend(UINT32 nCode, INT32 nLen);

    void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader);
    void OnRead(UINT32 nCode, INT32 nLen);
private:
    CMSocketC* m_pSocketC;
    CMHttpS*   m_pHttpS;             //对应http Server
    CMHttpC*   m_pHttpC;             //外部http连接
    CMFile*    m_pFile;              //本地file
    CMHTTPReqHeader    m_cReqHeader;    //本地Http请求头
//    CMHTTPRspHeader    m_cRspHeader;    //本地Http响应头
    CMUrl              m_rUrl;          //请求的外部地址
    INT8*              m_pHeadBuf;      //存放头的缓冲区，需要管理生存期
    UINT32             m_nHeadPos;      //头缓冲区的当前指针位置
    UINT32             m_nTotalSize;    //总的请求大小
    UINT32             m_nStart;        //当前起始
    UINT32             m_nEnd;          //当前截止
    UINT32             m_nSize;            //还需向http接收文件大小
    UINT32             m_nSendSize;        //还需向socket发送文件大小
    INT8*              m_pBuf;             //http接收缓冲
    //UINT32             m_nBufSize;         //http接收缓冲大小
    UINT32             m_nPos;             //http接收缓冲向socket发送位置
    BOOL               m_bInService;
    UINT32             m_nStatus;          //0 空闲, 1 网络请求头 2 网络请求  3本地文件请求头 4本地文件请求

};

//把远端url射成本地url，提供http服务，作用类似iis。不同的是iis提供目录映射，此服务器只提供文件和远程url映射
class CMHttpS : public IMNotifySocketS
{
public:
	static CMHttpS& Instance();

    //析构时删除所有连接
    ~CMHttpS();

    ////设置外部链接
    //void SetUrl(const CMUrl& rUrl, const CMUrl& lUrl);
    ////设置本地文件链接
    //void SetFile(const CMString& sFileName, const CMUrl&  lUrl);

    //const CMUrl* GetUrl(const CMUrl& lUrl);

    //const CMString* GetFile(const CMUrl& lUrl);

    //远程http://11.22.33.44:555/ccc/ddd/ 本地http://localhost/ccc/ddd/, ， SetRemote("http://11.22.33.44:555/ccc/ddd/"=SetRemote("http://11.22.33.44:555");
    void SetRemote(const CMUrl& rUrl);
    // SetFolder("//");
    void SetFolder(const CMString& sFolder);

    //把本地url变成远程url
    CMUrl ToRemote(const CMUrl& lUrl);
    //把远程url变成本地url
    CMUrl GetLocal(const CMUrl& rUrl);

    //设置服务端口
    void SetPort(UINT16 nPort);
    //启动服务
    BOOL Start();
    //停止服务，断掉所有链接
    void Stop();

protected:
    CMHttpS();

private:
    void OnAccept(UINT32 nCode, CMSocketC* pSocketC);

    CMSocketS* m_pSocketS;
    CMList<CMHttpSNotify*>      m_lstNotify;
    //CMMap<CMUrl*, CMUrl>        m_mapUrl;
    //CMMap<CMUrl*, CMString>     m_mapFile;
    CMUrl                       m_remote;     //映射的远端url
    CMString                    m_folder;     //映射的本地目录
    UINT16                      m_nPort;

	static CMHttpS* m_pHttpS;
};

