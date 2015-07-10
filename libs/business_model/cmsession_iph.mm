//
//  cmsessionMid.m
//  MLPlayer
//
//  Created by whf on 13-8-19.
//  Copyright (c) 2013. All rights reserved.
//
#include "stdafx.h"
#import "cmsession_iph.h"
#import "cmcommon.h"




@interface CmSessionMid : NSObject{
@public
    unsigned int nCmdID;
    unsigned int nCode;
    TiXmlDocument* pDoc;
    
    IMNotifySession*  m_pNotify;
}

- (void)run;
@end

@implementation CmSessionMid

-(void)run
{

    [self performSelectorOnMainThread:@selector(process) withObject:nil waitUntilDone:YES];
    
}

-(void)process
{
    if (m_pNotify) 
        m_pNotify->OnSessionCmd(nCmdID, nCode, pDoc);
    else
        CM_ERRP("nCmdID: %d, nCode:%d, pDoc:%p",nCmdID,nCmdID,pDoc);
    
}

-(void)dealloc
{
    m_pNotify=NULL;
}
@end

CMNotifySessionIos::CMNotifySessionIos(IMNotifySession* pNotify)
{
    
    mid= (__bridge_retained void *)[[CmSessionMid alloc]init];
    CmSessionMid* cmid=(__bridge CmSessionMid*)mid;
    cmid->m_pNotify=pNotify;


}

CMNotifySessionIos::~CMNotifySessionIos()
{
    CmSessionMid* cmid=(__bridge CmSessionMid*)mid;

}

void CMNotifySessionIos::OnSessionCmd(unsigned int nCmdID,unsigned int nCode , TiXmlDocument* pDoc)
{
    
    CmSessionMid* cmid=(__bridge CmSessionMid*)mid;
    cmid->nCmdID=nCmdID;
    cmid->nCode=nCode;
    cmid->pDoc=pDoc;
    
    [cmid run];
       
};
