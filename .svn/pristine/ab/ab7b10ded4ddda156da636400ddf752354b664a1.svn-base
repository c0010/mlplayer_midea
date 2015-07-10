//
//  XMPPChatMessageCoreDataStorage.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-20.
//  Copyright (c) 2014年 w. All rights reserved.
//
#import "CMInteractModel.h"
#import <Foundation/Foundation.h>
#import "XMPPCoreDataStorage.h"

#define XMPPChatStorage  [XMPPChatMessageCoreDataStorage sharedInstance]

#define MessageObjectContext  [XMPPChatStorage mainThreadManagedObjectContext]


@interface XMPPChatMessageCoreDataStorage : XMPPCoreDataStorage

+ (instancetype)sharedInstance;

- (NSArray *)dialogueWithGroupItems;
- (CMDialogueItem*)dialogueItemExistForRoomJid:(NSString*)jid;
- (CMDialogueItem*)dialogueItemExistForJid:(NSString*)jid;


@property (nonatomic,strong) CMUserItem *currUser;//我的个人信息

@end
