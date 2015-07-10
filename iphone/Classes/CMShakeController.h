//
//  CMShakeController.h
//  MLPlayer
//
//  Created by 王 浩沣 on 13-7-13.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import "cmcommon.h"

#import "tool.h"
#import "MLPlayerAppDelegate.h"
//#import "MobClick.h"
#import "CMViewController.h"

#import "CMNavgateItem.h"
#import "cmshake.h"

class CMShakeUpdateListener;
@interface CMShakeController : CMViewController
{
   
    MLPlayerAppDelegate *appDelegate;

   
    CMShakeUpdateListener *m_pShakeListener;

@public
    CMShake* m_pShake;

}

-(void)shakeToDetail;

class CMShakeUpdateListener: public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMShakeController *control = (__bridge CMShakeController*)UserData;
        //        CMShake* pShake = (CMShake*)browser.Contenthandler;
        //        [browser setHasMore:!pShake->IsEnd()];
        if (Result == TResult::ESuccess)
        {
            [control shakeToDetail];
        }
    }
};

@end