//
//  CMVersionVerifyAgent.h
//  MLPlayer
//
//  Created by 廖宏兴 on 15/6/22.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CMVersionVerify.h"


class CMVersionVerifyListener;

@interface CMVersionVerifyAgent: NSObject{
    CMVersionVerifyListener *m_pVersionVerifyListener;
    CMVersionVerify *m_pVersionVerify;
    
    BOOL bCheckAtStartUp;
}

+ (instancetype)sharedVersionVerifyAgent;
- (void)checkUpdate;
- (void)checkUpdateWhenApplicationStart;
- (void)receivedVersionVerifyData;


@end


class CMVersionVerifyListener : public IMUpdateDataListener
{
//public:
//    CMVersionVerifyListener(){};
//    ~CMVersionVerifyListener(){}
//    
    
    void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    
    void OnUpdateDataFinish(void* UserData, int Result){
        CMVersionVerifyAgent *versionVerifyAgent = (__bridge CMVersionVerifyAgent*)UserData;
        if(Result == TResult::ESuccess)
        {
            [versionVerifyAgent receivedVersionVerifyData];
        }
        else if(Result == TResult::ENotSupportOffline || Result == TResult::ENetDisconnect)
        {
            [tool ShowAlert:I(@"网络不给力")];
        }
        else if(Result == TResult::ENetTimeout)
        {
            [tool ShowAlert:I(@"检测超时")];
        }
        else {
            [tool ShowError:Result];
        }
        
        
    };
};
