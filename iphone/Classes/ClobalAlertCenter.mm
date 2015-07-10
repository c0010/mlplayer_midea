//
//  ClobalAlertCenter.m
//  MLPlayer
//
//  Created by sunjj on 13-8-21.
//  Copyright (c) 2013年 w. All rights reserved.
//
#import "stdafx.h"
#import "ClobalAlertCenter.h"
#import "tool.h"
#import "cmquestionupload.h"

@implementation ClobalAlertCenter

static  ClobalAlertCenter * sharedAlertCenter =nil;

+(ClobalAlertCenter *)sharedAlertCenter
{
	@synchronized(self){
		if(sharedAlertCenter == nil){
			sharedAlertCenter = [[self alloc] init];
            sharedAlertCenter->m_pSimpleListener=new AlertCenterSimpleListener();

            
		}
	}
	return sharedAlertCenter;
	
}

-(IMSimpleResultListener*)GetCallBack
{
    return m_pSimpleListener;
    
}
-(void)Alert
{
    
    [tool ShowAlert:@"提问成功!"];
    
}

@end
