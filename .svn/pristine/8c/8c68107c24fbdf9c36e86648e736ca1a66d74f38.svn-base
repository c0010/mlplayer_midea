//
//  cmsessionMid.m
//  MLPlayer
//
//  Created by whf on 13-8-19.
//  Copyright (c) 2013. All rights reserved.
//
#include "stdafx.h"
#import "cmhttpc_iph.h"

@interface CMHttpCMid : NSObject{
@public
    unsigned int nCode;
    int          nLen;
    CMHTTPRspHeader* pRespHeader;
    
    IMNotifyHttpC*  m_pNotify;
    int          queueid; //使用queueid决定队列多余请求是否需要释放
}

@end

@implementation CMHttpCMid

- (id)init
{
    self = [super init];
    if (self != nil) {
        self->queueid = rand();
    }

    return self;
}

-(void)cancel
{
//    printf("cancel queueid old %d \n", queueid);
    queueid = rand(); //重建队列，原有队列不再使用
//    printf("cancel queueid new %d \n", queueid);
//    [NSObject cancelPreviousPerformRequestsWithTarget:self ];
//    [self performSelectorOnMainThread:@selector(cancelProcess) withObject:nil  waitUntilDone:NO];
}

-(void)cancelProcess
{
    
    [NSObject cancelPreviousPerformRequestsWithTarget:self];

}

/////////RESPONSE
-(void)run1
{
    //需要异步，当同步时，主线程Cancel，会锁
    [self performSelectorOnMainThread:@selector(response:) withObject:[NSNumber numberWithInt:queueid] waitUntilDone:NO];

}

/////////READ

-(void)run2
{
    //需要异步，当同步时，主线程Cancel，会锁
    [self performSelectorOnMainThread:@selector(read:) withObject:[NSNumber numberWithInt:queueid] waitUntilDone:NO];
}

/////////SEND

-(void)run3
{
    //需要异步，当同步时，主线程Cancel，会锁
    [self performSelectorOnMainThread:@selector(send:) withObject:[NSNumber numberWithInt:queueid] waitUntilDone:NO];
}

-(void)response:(NSNumber*)number
{
    if (queueid == [number intValue] && m_pNotify)
        m_pNotify->OnResponse(nCode, pRespHeader);
    else
        CM_LOGP(CM_LOGL_WARNING, "response queueid %d number %d", queueid, [number intValue]);
}

-(void)read:(NSNumber*)number
{
    if (queueid == [number intValue] && m_pNotify)
        m_pNotify->OnRead(nCode, nLen);
    else
        CM_LOGP(CM_LOGL_WARNING, "read queueid %d number %d", queueid, [number intValue]);
}

-(void)send:(NSNumber*)number
{
    if (queueid == [number intValue] && m_pNotify)
        m_pNotify->OnSend(nCode, nLen);
    else
        CM_LOGP(CM_LOGL_WARNING, "send queueid %d number %d", queueid, [number intValue]);
}

-(void)dealloc
{
    m_pNotify = NULL;
    pRespHeader = NULL;
    [super dealloc];
}
@end

CMNotifyHttpCIos::CMNotifyHttpCIos(IMNotifyHttpC* pNotify)
{
    
    mid=[[CMHttpCMid alloc]init];
    CMHttpCMid* cmid=(CMHttpCMid*)mid;
    cmid->m_pNotify=pNotify;


}

CMNotifyHttpCIos::~CMNotifyHttpCIos()
{
    CMHttpCMid* cmid=(CMHttpCMid*)mid;
    [cmid release];
}

void CMNotifyHttpCIos::Cancel()
{
    CMHttpCMid* cmid=(CMHttpCMid*)mid;
    [cmid cancel];
}

void CMNotifyHttpCIos::OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader)
{
    CMHttpCMid* cmid=(CMHttpCMid*)mid;
    cmid->nCode=nCode;
    cmid->pRespHeader=(CMHTTPRspHeader*)pRespHeader;
    
    [cmid run1];
}

void CMNotifyHttpCIos::OnRead(UINT32 nCode, INT32 nLen)
{
    CMHttpCMid* cmid=(CMHttpCMid*)mid;
    cmid->nCode=nCode;
    cmid->nLen=nLen;
    
    [cmid run2];
}

void CMNotifyHttpCIos::OnSend(UINT32 nCode, INT32 nLen)
{
    CMHttpCMid* cmid=(CMHttpCMid*)mid;
    cmid->nCode=nCode;
    cmid->nLen=nLen;
    
    [cmid run3];
}
