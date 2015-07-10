//
//  CMSendDeviceTokKen.h
//  MLPlayer
//
//  Created by sunjj on 12-6-6.
//  Copyright 2012 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "cmdevicetoken.h"


class CMDeviceToKeyListener;

@interface CMPushMessage : NSObject {

	CMDeviceToKen* deviceToKen;
	CMDeviceToKeyListener* pListener;
}

-(void)inits;
-(void)SendDeviceTokey:(NSString*)strVale;




@end


class CMDeviceToKeyListener : public IMSimpleResultListener
{
public:
	CMDeviceToKeyListener(){};
	~CMDeviceToKeyListener(){};	
	
	void OnRequestFinish(void* UserData, int Result)
	{
		//CMSendDeviceTokKen* device= (CMSendDeviceTokKen*)UserData;
		
		NSLog(@"CMSendDeviceTokKen OnRequestFinish=%d",Result);
		
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{			
			
			
		}else {
			
		}
		
	}
	
	
};