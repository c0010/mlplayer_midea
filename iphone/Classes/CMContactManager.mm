//
//  CMContactManager.m
//  MLPlayer
//
//  Created by water on 14-8-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMContactManager.h"
#include "cmmyinfo.h"
#import "cmfileinfo.h"
#import "CMAddressInfoControl.h"
#import "CMMsgManager.h"
#import "CMMsgBlock.h"
#import "CMCoreDataUtils.h"

@implementation CMContactManager


+ (id)manager{
    return [[CMContactManager alloc] init];
}

- (id)init{
    self= [super init];
    if (self) {
        contactManagerListener = new CMContactManagerListener();
        
        contacts = new CMContacts(contactManagerListener);
        contacts->SetUserData((__bridge void*)self);
    }
    return self;
}

//搜索通讯录
- (void)doQuickSearch:(NSString*)skey success:(CMContactManagerSuccess)success{
    
    self.contactManagerSuccess = success;
    
    contacts->QuickSearch([skey UTF8String]);
}

//搜索通讯录翻页
- (void)doQuickSearchMore:(NSString*)skey success:(CMContactManagerSuccess)success
{
    self.contactManagerSuccess = success;
    
    if (contacts) {
        contacts->RequestMore();
    };
}


//获取群成员
- (void)doRequestOccupantsList:(NSString*)roomID success:(CMContactManagerSuccess)success failure:(CMContactManagerFailureNone)failure{
    
    self.contactManagerSuccess = success;
    self.contactManagerFailureNone = failure;

    contacts->RequestOccupantsList([roomID UTF8String]);
}

//获取培训班成员
- (void)doRequestTrainOccupantsList:(NSString*)trainID success:(CMContactManagerSuccess)success failure:(CMContactManagerFailureNone)failure{
    
    self.contactManagerSuccess = success;
    self.contactManagerFailureNone = failure;
    
    contacts->RequestTrainList([trainID UTF8String]);
}

//跳转到用户界面
- (void)doGotoUserAddress:(NSString *)jid navigation:(UINavigationController *)controler{
    self.contactManagerGotoUserInfoSuccess = ^{};
    self.navigationController = controler;
    
	contacts->RequestByJid([jid UTF8String]);
}

//获取用户详细信息
- (void)doRequestUserInfoWithJid:(NSString *)jid listener:(CMContactManagerSuccess)success{
    self.contactManagerSuccess = success;
    
	contacts->RequestByJid([jid UTF8String]);
}

//获取自己的用户信息
- (void)doRequestOwnerUserInfo{
    
//	CMMyInfo::GetInstance()->SetListener(NULL);
//    CMMyInfo::GetInstance()->UpdateData();
    
    __block CMUserItem *ownerUser = (CMUserItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMUserItem class]) withPredicate:Pre_UserJid(kXMPPJid)];
    
    if (ownerUser) {
        
        XMPPChatStorage.currUser = ownerUser;
        
    }else{
    
        [self doRequestUserInfoWithJid:kXMPPJid listener:^(CMContacts *) {
            TContactsItem item;
            
            if(contacts && contacts->GetItem(0, item)){
                
                ownerUser = [NSEntityDescription insertNewObjectForEntityForName:@"CMUserItem" inManagedObjectContext:MessageObjectContext];
                ownerUser.uid = [NSString stringWithUTF8String:item.sID.c_str()];
                ownerUser.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
                ownerUser.name = [NSString stringWithUTF8String:item.sName.c_str()];
                ownerUser.jid = kXMPPJid;

                NSError *error = NULL;

                if (![MessageObjectContext save:&error]) {
                    NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
                    abort();
                }
                
                XMPPChatStorage.currUser = ownerUser;

            }

        }];
    }

}

- (void)checkUserInfo:(CMBaseItem *)item success:(GetOwnerInfoSuccessCallback)success failure:(GetOwnerInfoFailureCallback)failure{
    
    self.getOwnerInfoSuccessCallback = success;
    self.getOwnerInfoFailureCallback = failure;
    
    if ([MBlock.fromName(item) isEqualToString:@""] && [MBlock.icon(item) isEqualToString:@""]) {
        [self doRequestOwnerUserInfo:^{
            NSString *fromName = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetFullName()];
            NSString *icon = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetHeadimage()];
            
            self.getOwnerInfoSuccessCallback(fromName,icon);
        } failure:^(int errorCode) {
            self.getOwnerInfoFailureCallback();
        }];
    }else{
        self.getOwnerInfoSuccessCallback(MBlock.fromName(item),MBlock.icon(item));
    }
}

- (void)doRequestOwnerUserInfo:(CMContactManagerSuccessNone)success failure:(CMContactManagerFailureNone)failure{
    self.contactManagerSuccessNone = success;
    self.contactManagerFailureNone = failure;

    CMMyInfo::GetInstance()->SetListener(contactManagerListener, NULL);
    CMMyInfo::GetInstance()->SetUserData((__bridge void*)self);

    [self doRequestOwnerUserInfo];
}

- (void)doContactManagerSuccess{
    if (self.contactManagerSuccess) {
        self.contactManagerSuccess(contacts);
        self.contactManagerSuccess = nil;
    }
    if (self.contactManagerSuccessNone) {
        self.contactManagerSuccessNone();
        self.contactManagerSuccessNone= nil;
    }
    if (self.contactManagerGotoUserInfoSuccess) {
        self.contactManagerGotoUserInfoSuccess= nil;
        
        [self gotoUserInfo];
    }
}

//跳转
- (void)gotoUserInfo{
    TContactsItem item;
    if(contacts && contacts->GetItem(0, item)){
        UIViewController *controller = self.navigationController.topViewController;
        if (![controller isKindOfClass:[CMAddressInfoControl class]]) {
            //点击头像跳转到用户信息界面
            CMAddressInfoControl* control = [[CMAddressInfoControl alloc] init];
            control.title = [NSString stringWithUTF8String:item.sName.c_str()];
            control.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            control.navigationController.navigationBarHidden = NO;
            control.tabBarController.tabBar.hidden = YES;
            control.hidesBottomBarWhenPushed = YES;
            [control getAddItem:item];
            control.isFromChat = YES;
            [self.navigationController pushViewController:control animated:YES];
        }
    }
}

- (void)doContactManagerFailure:(int)errorCode
{
    
    if (self.contactManagerFailureNone) {
        self.contactManagerFailureNone(errorCode);
        self.contactManagerFailureNone = nil;
    }else{
        
        if (self.contactManagerFailure) {
            self.contactManagerFailure(errorCode);
            self.contactManagerFailureNone= nil;
        }
        
        [tool ShowError:errorCode];
    }
}
-(void)dealloc{
    
    SAFEDELETE(contactManagerListener);
    SAFEDELETE(contacts);
    
}

@end
