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
class AlertCenterUpdateDataListener;
@interface GlobalAlertCenter : NSObject
{
    NSString *strType;
@public
    AlertCenterSimpleListener*  m_pSimpleListener;
    AlertCenterUpdateDataListener *m_pUpdateDataListener;
}

- (void)Alert;
- (void)Warn;
- (IMSimpleResultListener*)GetCallBack;
- (IMUpdateDataListener*)GetUpdateDataCallBack;
- (void)setType:(NSString*)type;
+(GlobalAlertCenter *)sharedAlertCenter;

@end


class AlertCenterSimpleListener:public IMSimpleResultListener
{
    void  OnRequestFinish(void* UserData, int Result) 
    {
        GlobalAlertCenter *center = [GlobalAlertCenter sharedAlertCenter];
        
        if (Result==TResult::ESuccess) {
            //[[GlobalAlertCenter sharedAlertCenter] Alert];
            [center Alert];

        }else
        {
            //[[GlobalAlertCenter sharedAlertCenter] Warn];
            
            [center Warn];
        }
        
    }
    
};

class AlertCenterUpdateDataListener:public IMUpdateDataListener
{
public:
    AlertCenterUpdateDataListener(){};
    ~AlertCenterUpdateDataListener(){};
    
    void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
    }
    
    void OnUpdateDataFinish(void* UserData, int Result)
    {
        NSLog(@"AlertCenterUpdateDataListener OnUpdateDataFinish Result=%d",Result);
        
        GlobalAlertCenter *center = [GlobalAlertCenter sharedAlertCenter];
        
        if (Result==TResult::ESuccess) {
            [center Alert];
        }
        else
        {
            [center Warn];
        }

    }
    
};
