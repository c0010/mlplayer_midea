//
//  ClobalAlertCenter.m
//  MLPlayer
//
//  Created by sunjj on 13-8-21.
//  Copyright (c) 2013年 w. All rights reserved.
//
#import "stdafx.h"
#import "GlobalAlertCenter.h"
#import "tool.h"
#import "cmquestionupload.h"
#import "MLPlayerAppDelegate.h"
#import "CMPositionCourseControl.h"

@implementation GlobalAlertCenter

//static  GlobalAlertCenter * sharedAlertCenter =nil;

#pragma mark - Singleton

+(GlobalAlertCenter *)sharedAlertCenter
{
    static  GlobalAlertCenter * sharedAlertCenter =nil;
    //检查是否运行过
    static dispatch_once_t alertpredicate;

    dispatch_once(&alertpredicate, ^{
        if(sharedAlertCenter == nil)
            sharedAlertCenter = [[GlobalAlertCenter alloc] init];
    });

    return sharedAlertCenter;

	
}



#pragma mark - Life Cycle


- (id)init
{
    self = [super init];
    if (self) {
        self->m_pSimpleListener=new AlertCenterSimpleListener();
    }
    return self;
}

#pragma mark - APIs


- (IMSimpleResultListener*)GetCallBack
{
    if (!m_pSimpleListener)
    {
        m_pSimpleListener = new AlertCenterSimpleListener();
    }
    return m_pSimpleListener;
}

- (IMUpdateDataListener*)GetUpdateDataCallBack
{
    if (!m_pUpdateDataListener) {
        m_pUpdateDataListener = new AlertCenterUpdateDataListener();
    }
    return m_pUpdateDataListener;
}


- (void)setType:(NSString*)type
{
    strType = type;
}

- (void)Warn
{
    if ([strType isEqualToString:CM_NotificationCenter_ReloadView]) {
        return;
    }
    else{
        [tool ShowAlert:@"提交失败!"];
        if ([strType isEqual:@"answerquestion"])
        {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"submit_answer_faild" object:nil];
        }
    }
}

- (void)Alert
{

    
    if ([strType isEqual:@"askquestion"])
    {
        [tool ShowAlert:I(@"提交成功")];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"submit_success" object:nil];
    }
    else if ([strType isEqual:@"answerquestion"])
    {
        [tool ShowAlert:I(@"提交成功")];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"questiondetailrefresh"
                                                            object:nil
                                                          userInfo:nil];
    }
    else if ([strType isEqual:@"headphoto"])
    {
        [tool ShowAlert:I(@"上传成功")];
        [[NSNotificationCenter defaultCenter] postNotificationName:CM_NotificationCenter_HeadImageUpload
                                                            object:nil
                                                          userInfo:nil];
    }
    else if ([strType isEqualToString:CM_NotificationCenter_ReloadView]){
        [[NSNotificationCenter defaultCenter] postNotificationName:CM_NotificationCenter_ReloadView
                                                            object:nil
                                                          userInfo:nil];
    }
    else
    {
        [tool ShowAlert:I(@"提交成功")];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"submit_success" object:nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"questiondetailrefresh"
                                                            object:nil
                                                          userInfo:nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:CM_NotificationCenter_HeadImageUpload
                                                            object:nil
                                                          userInfo:nil];
    }
}

@end
