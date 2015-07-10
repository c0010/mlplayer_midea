//
//  cmsessionMid.h
//  MLPlayer
//
//  Created by whf on 13-8-19.
//  Copyright (c) 2013 All rights reserved.
//

#ifndef CMNotifyHttpCIos_HEADER_INCLUDED_B249D7FB
#define CMNotifyHttpCIos_HEADER_INCLUDED_B249D7FB

#import "tinyxml.h"
#include "cmhttpc.h"

class CMNotifyHttpCIos: public IMNotifyHttpC {

public:
    CMNotifyHttpCIos(IMNotifyHttpC* pNotify);
    
    virtual ~CMNotifyHttpCIos();
    
    void Cancel();

    virtual void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader);
    //完成，缓冲满，或者错误
    virtual void OnRead(UINT32 nCode, INT32 nLen);
    //完成，缓冲发送完，或者错误
    virtual void OnSend(UINT32 nCode, INT32 nLen);
    
private:
    void* mid;

};


#endif
