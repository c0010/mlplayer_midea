//
//  CMSendDeviceTokKen.mm
//  MLPlayer
//
//  Created by sunjj on 12-6-6.
//  Copyright 2012 w. All rights reserved.
//
#include "stdafx.h"
#import "CMPushMessage.h"


@implementation CMPushMessage

-(void)inits
{
	pListener = new CMDeviceToKeyListener();
	deviceToKen = new CMDeviceToKen(pListener);
	
}

-(void)SendDeviceTokey:(NSString*)strVale
{
	deviceToKen->SendDeviceToKen([strVale UTF8String]);
}

- (void)dealloc
{
	SAFEDELETE(deviceToKen);
	SAFEDELETE(pListener);
}
@end
