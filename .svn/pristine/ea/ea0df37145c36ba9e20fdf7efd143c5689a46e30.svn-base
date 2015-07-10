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

//#include "cmglobal.h"
#import <Foundation/Foundation.h>
#import "ASIHTTPRequest.h"

@interface CMMidHandleHttp:NSObject
{
	CMHttpC* m_pMHttC;
	IMNotifyHttpC*  m_pNotify; 
	ASIHTTPRequest  *request;
	INT8*           m_pBuf;          
	INT32           m_nLen;   
	INT32           m_nRcv;
	INT8*           m_pCurr;         
	INT32           m_nLeft;         
	INT32           m_nStatus; //-1 no start or fail, 0 success
}
- (id)InitMidHandleHttp:(CMHttpC*)phttpc notify:(IMNotifyHttpC*)pnotify;

- (void)Read:(INT8*)pBuf len:(INT32)nLen;

-(void) Cancel;

-(void) Request;

-(BOOL) IsRunning;

-(void) Reset;

@property (retain, nonatomic) ASIHTTPRequest *request;
@end

@implementation CMMidHandleHttp

- (id)InitMidHandleHttp:(CMHttpC*)phttpc notify:(IMNotifyHttpC*)pnotify
{
//	CMMidHandleHttp* inst = [[[CMMidHandleHttp alloc]init]autorelease];
//	inst->m_pMHttC = phttpc;
//	inst->m_pNotify = pnotify;
//	inst->m_pBuf = nil;          
//    inst->m_nLen = 0;  
//	inst->m_nRcv = 0;
//    inst-> m_pCurr = nil;         
//    inst->m_nLeft = 0;         
//	inst->m_nStatus = -1; //-1 no start or fail, 0 success
//	[inst setMRequest:nil];
//	return inst;
	self = [super init];
	m_pMHttC = phttpc;
	m_pNotify = pnotify;
	m_pBuf = nil;          
    m_nLen = 0;  
	m_nRcv = 0;
    m_pCurr = nil;         
    m_nLeft = 0;         
	m_nStatus = -1; //-1 no start or fail, 0 success
	[self setRequest:nil];
	return self;
}
-(void) Reset
{
	m_pBuf = nil;          
    m_nLen = 0;  
	m_nRcv = 0;
    m_nLeft = 0;  
	if(m_pCurr)
	{
		free(m_pCurr);
		m_pCurr = nil;
	}
}
-(void) Request
{
	if(request)
	{
		[self Cancel];
		//[request release];
	}
	CMString str = m_pMHttC->GetReqHeader().GetUrl().Url();

	NSString *pStr = [NSString stringWithUTF8String:(const char*)str];
	NSLog(@"%@",pStr);
	NSURL*url =  [NSURL URLWithString:pStr];
	[self setRequest:[ASIHTTPRequest requestWithURL:url]];
	[request setAllowCompressedResponse:NO];
	[request setNumberOfTimesToRetryOnTimeout:2];
	
	NSString *pValue = nil;
	for(CMMap<CMString, CMString>::const_iterator it = m_pMHttC->GetReqHeader().GetMapValue().begin(); it != m_pMHttC->GetReqHeader().GetMapValue().end(); it++)
	{
		CMString s = it.key();
		pStr = [NSString stringWithUTF8String:(const char*)s];
			//NSLog(@"~~~~~~~~~~~%@~~~~~~~~~~~~",pStr);
		s = it.value();
		pValue = [NSString stringWithUTF8String:(const char*)s];
			//NSLog(@"~~~~~~~~~~~~~%@~~~~~~~~~",pValue);
		[request addRequestHeader:pStr value:pValue];	
	}

	
	if(m_pMHttC->GetReqHeader().GetType() == CMHTTPReqHeader::POST)
	{
		[request setRequestMethod:@"POST"];
		char *pbytes = m_pMHttC->GetReqHeader().GetPostData();
		if(pbytes != NULL)
		{
			NSMutableData *pData = [NSMutableData dataWithBytes:(void *)pbytes length:m_pMHttC->GetReqHeader().GetPostDataLength()];
			[request setPostBody:pData];
		}
	}
	m_nStatus = -1;
	[request setShouldRedirect:false];
	[request setDelegate:self];
	[request startAsynchronous];
}
- (void)request:(ASIHTTPRequest *)request didReceiveResponseHeaders:(NSDictionary *)responseHeaders
{
	if(!m_pMHttC)
		return;
	[request setPause:TRUE];
	
	int retcode = [request responseStatusCode];
	if(retcode == 301 || retcode == 302 || retcode == 303)
	{
		CMString sUrl = [[responseHeaders valueForKey:@"Location"] UTF8String];
		m_pMHttC->GetReqHeader().SetUrl(sUrl);
		[self Request];
		return;
	}
	m_pMHttC->GetRspHeader().Clean();
	NSString *pStatus = [request responseStatusMessage];
	CMString sStatus = [pStatus UTF8String];
	m_pMHttC->GetRspHeader().SetRet( [request responseStatusCode],sStatus);
	NSArray *allkey = [responseHeaders allKeys];
	NSArray *allValue = [responseHeaders allValues];
	NSUInteger cnt = [responseHeaders count];
	for (NSUInteger i= 0; i < cnt; i++) 
	{
		NSString *pkey = (NSString*)[allkey objectAtIndex:i];
		NSString *pvalue = (NSString*)[allValue objectAtIndex:i];
		if(pkey != nil && pvalue != nil)
			m_pMHttC->GetRspHeader().AddValue([pkey UTF8String],[pvalue UTF8String]);
	}
	m_nStatus = 0;
	if(m_pNotify)
		m_pNotify->OnResponse(MER_OK,&m_pMHttC->GetRspHeader());
}
- (void)request:(ASIHTTPRequest *)request didReceiveData:(NSData *)data
{
	int len = [data length];
		//NSLog(@"didReceiveData recv..............%d",len);
	char* pdata = (char*)[data bytes];
	int nreadlen = m_nLen - m_nRcv;
	if(len >= nreadlen)
	{
		[request setPause: TRUE];
		memcpy(m_pBuf+m_nRcv,pdata,nreadlen);
		m_pCurr = (char*)malloc(len-nreadlen);
		ASSERT(m_pCurr!=nil);
		memcpy(m_pCurr,pdata+nreadlen,len-nreadlen);
		m_nLeft = len - nreadlen;
		if(m_pNotify)
			m_pNotify->OnRead(MER_OK,m_nLen);
	}
	else 
	{
		memcpy(m_pBuf+m_nRcv,pdata,len);
		m_nRcv += len;
	}
}

- (void)requestFinished:(ASIHTTPRequest *)request
{
		//NSLog(@"requestFinished");
	CMString sVal;
	if(m_pNotify && m_pMHttC->GetRspHeader().GetValue(L"Transfer-Encoding", sVal))
		m_pNotify->OnRead(MER_OK, m_nRcv);
}

- (void)requestFailed:(ASIHTTPRequest *)request
{
		//NSLog(@"requestFailed");
	NSError *error = [request error];
	if([error code] == ASIRequestCancelledErrorType)
		return;
	if(m_pNotify)
		m_pNotify->OnResponse(MERN_RECV_FAILED,&m_pMHttC->GetRspHeader());
}
- (void)Read:(INT8*)pBuf len:(INT32)nLen
{
	if(![self IsRunning])
	{
		if(m_pNotify)
				m_pNotify->OnRead(MER_OK,0);
		return;
	}
		//NSLog(@"read..............%d",nLen);
	m_pBuf = pBuf;
	m_nLen = nLen;
	m_nRcv = 0;

	if(m_nLeft > 0)
	{
		if(nLen <=  m_nLeft)
		{
			memcpy(m_pBuf, m_pCurr,nLen);
			char* m_pTmp  = nil;
			m_nLeft-= nLen;
			if(m_nLeft > 0)
			{
				m_pTmp = (char*)malloc(m_nLeft);
				ASSERT(m_pTmp != nil);
				memcpy(m_pTmp,m_pCurr+nLen,m_nLeft);
			}
			free(m_pCurr);
			m_pCurr = m_pTmp;
			if(m_pNotify)
				m_pNotify->OnRead(MER_OK,m_nLen);
			return;
		}
		else
		{
			memcpy(m_pBuf, m_pCurr,m_nLeft);
			free(m_pCurr);
			m_pCurr = nil;
			m_nRcv = m_nLeft;
			m_nLeft = 0;
		}
	}
	[request setPause: FALSE];
		//NSLog(@"read..............pause");
}

-(void) Cancel
{
	if(	request)
	{
		[request setPause:FALSE];
		//if(![request isCancelled])
		[self Reset];
		[request clearDelegatesAndCancel];
		[request release];
		request = nil;
	}
}

-(BOOL) IsRunning
{
	return ![request isFinished];
}
@synthesize request;
@end

///////////////////////////////////////////////////////////////////////////////////
CMHttpC::CMHttpC(IMNotifyHttpC* pNotify, BOOL bAutoReloate)
{
	ASSERT(m_pNotify != NULL);
	m_pMidHandleHttp = [[CMMidHandleHttp alloc] InitMidHandleHttp:this notify:pNotify];
}

CMHttpC::CMHttpC()
{
}

CMHttpC::~CMHttpC()
{
	CMMidHandleHttp* http = (CMMidHandleHttp*)m_pMidHandleHttp;
	[http Cancel];
	[http release];
}

void CMHttpC::Request(CMHTTPReqHeader &header)
{
	m_cReqHeader = header;
	Request();
}

void CMHttpC::Request()
{
	CMMidHandleHttp* http = (CMMidHandleHttp*)m_pMidHandleHttp;
	[http Request];
}

const CMHTTPRspHeader& CMHttpC::LastResponse() const 
{
	return m_cRspHeader;
}

void CMHttpC::Read(INT8* pBuf, INT32 nLen)
{
	CMMidHandleHttp* http = (CMMidHandleHttp*)m_pMidHandleHttp;
	[http Read:pBuf len:nLen];
}

void CMHttpC::Cancel()
{
	CMMidHandleHttp* http = (CMMidHandleHttp*)m_pMidHandleHttp;
	[http Cancel];
}

BOOL CMHttpC::IsRunning()
{
	CMMidHandleHttp* http = (CMMidHandleHttp*)m_pMidHandleHttp;
	return [http IsRunning];
}
