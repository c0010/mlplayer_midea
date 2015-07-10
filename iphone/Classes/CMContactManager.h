//
//  CMContactManager.h
//  MLPlayer
//  通讯录相关
//  Created by water on 14-8-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cmcontacts.h"
#import "tool.h"
#import "CMInteractModel.h"

typedef void(^CMContactManagerSuccess)(CMContacts*);
typedef void(^CMContactManagerFailure)(int errorCode);
typedef void(^CMContactManagerSuccessNone)();
typedef void(^CMContactManagerFailureNone)(int errorCode);

//发送信息时检测用户信息是否获取
typedef void(^GetOwnerInfoSuccessCallback)(NSString *,NSString *);
typedef void(^GetOwnerInfoFailureCallback)();

typedef void(^CMContactManagerGotoUserInfoSuccess)();

class CMContactManagerListener;
@interface CMContactManager : NSObject
{
    CMContacts* contacts;
    CMContactManagerListener *contactManagerListener;
}

@property(nonatomic,strong)CMContactManagerSuccess contactManagerSuccess;
@property(nonatomic,strong)CMContactManagerFailure contactManagerFailure;
@property(nonatomic,strong)CMContactManagerSuccessNone contactManagerSuccessNone;
@property(nonatomic,strong)CMContactManagerFailureNone contactManagerFailureNone;
@property(nonatomic,strong)CMContactManagerGotoUserInfoSuccess contactManagerGotoUserInfoSuccess;

@property(nonatomic,strong)GetOwnerInfoSuccessCallback getOwnerInfoSuccessCallback;
@property(nonatomic,strong)GetOwnerInfoFailureCallback getOwnerInfoFailureCallback;

@property(nonatomic,strong)UINavigationController *navigationController;

+ (id)manager;

- (void)doContactManagerSuccess;
- (void)doContactManagerFailure:(int)errorCode;

- (void)doQuickSearch:(NSString*)skey success:(CMContactManagerSuccess)success;

- (void)doQuickSearchMore:(NSString*)skey success:(CMContactManagerSuccess)success;


- (void)doRequestOccupantsList:(NSString*)roomID success:(CMContactManagerSuccess)success failure:(CMContactManagerFailureNone)failure;

- (void)doRequestTrainOccupantsList:(NSString*)trainID success:(CMContactManagerSuccess)success failure:(CMContactManagerFailureNone)failure;

- (void)doRequestUserInfoWithJid:(NSString *)jid listener:(CMContactManagerSuccess)success;

- (void)doGotoUserAddress:(NSString *)jid navigation:(UINavigationController *)controler;

- (void)doRequestOwnerUserInfo;
- (void)doRequestOwnerUserInfo:(CMContactManagerSuccessNone)success failure:(CMContactManagerFailureNone)failure;

- (void)checkUserInfo:(CMBaseItem *)item success:(GetOwnerInfoSuccessCallback)success failure:(GetOwnerInfoFailureCallback)failure;

@end

class CMContactManagerListener : public IMUpdateDataListener
{
    
public:
    
    CMContactManagerListener(){};
    ~CMContactManagerListener(){};
    void OnUpdateDataProgress(void* UserData, int nPercent) {}
    
    void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMContactManager * control = (__bridge CMContactManager*)UserData;
        [tool DisimissActivityIndicator];

        if(Result == TResult::ESuccess || Result == TResult::ENothing)
        {
            [control doContactManagerSuccess];
        }else
        {
            [control doContactManagerFailure:Result];
        }
    }
};