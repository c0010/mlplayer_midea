//
//  ClobalAlertCenter.h
//  MLPlayer
//
//  Created by sunjj on 13-8-21.
//  Copyright (c) 2013年 w. All rights reserved.
//
#import "cmcommon.h"

#import <Foundation/Foundation.h>

class AlertCenterSimpleListener;
@interface ClobalAlertCenter : NSObject
{

@public
AlertCenterSimpleListener* m_pSimpleListener;
}

-(void)Alert;
-(IMSimpleResultListener*)GetCallBack;
+(ClobalAlertCenter *)sharedAlertCenter;

@end


class AlertCenterSimpleListener:public IMSimpleResultListener
{
    void  OnRequestFinish(void* UserData, int Result) 
    {
        
        [[ClobalAlertCenter sharedAlertCenter] Alert];
        
    }
    
    
    
};
