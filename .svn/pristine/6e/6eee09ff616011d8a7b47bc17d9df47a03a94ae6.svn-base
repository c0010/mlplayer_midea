// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCOMMONINTERFACE_H_HEADER_INCLUDED_B5C1376C
#define CMCOMMONINTERFACE_H_HEADER_INCLUDED_B5C1376C

class CMSession;

#define SEQUENCE_NORMAL  "normal"
#define SEQUENCE_CHAT    "chat"

//命令类通知接受接口，用户实现
class IMNotifySession
{
public:
    //cmdID, 命令ID
    //pRoot，临时使用的xml信息，函数结束就不再有效
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc) = 0;
};

class CMDownloader;

//下载通知接收接口，用户实现
class IMNotifyDownload
{
public:
    //0-100,100表示下载完成，完成先调用OnProgress 再OnDownload，不要在OnProgress里做下载完成的处理
    virtual void OnProgress(unsigned int nRate) {};
    //nCode 返回值 0 成功
    //pDownloader 下载会话的句柄
    virtual void OnDownload(unsigned int nCode, CMDownloader* pDownloader) = 0;
};


#endif /* CMCOMMONINTERFACE_H_HEADER_INCLUDED_B5C1376C */
