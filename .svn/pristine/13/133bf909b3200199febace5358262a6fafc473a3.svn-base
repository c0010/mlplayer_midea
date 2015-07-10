//
//  CMMsgBlock.m
//  MLPlayer
//
//  Created by water on 14-9-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMMsgBlock.h"


@implementation CMMsgBlock

+ (CMMsgBlock*)sharedInstance
{
    static CMMsgBlock *sharedInstance;
    //检查是否运行过
    static dispatch_once_t predicate;
    
    dispatch_once(&predicate, ^{
        if(sharedInstance == nil)
            sharedInstance = [[CMMsgBlock alloc] init];
    });
    
    return sharedInstance;
    
}

- (id)init
{
    self = [super init];
    if (self) {
        [self initBlock];
    }
    return self;
}

//初始化block
- (void)initBlock{
    
    self.type = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.type;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.type;
        }
        NSInteger n = 0;
        return n;
    };
    
    self.isFromMe = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.isFromMe;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.isFromMe;
        }
        return NO;
    };
    self.isShowSendTime = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.isShowSendTime;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.isShowSendTime;
        }
        return NO;
    };
    self.coursemessage = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.coursemessage;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.coursemessage;
        }
        return [[CMCourseMessageItem alloc]init];
    };
    self.qamessage = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.qamessage;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.qamessage;
        }
        
        return [[CMQaMessageItem alloc]init];
    };
    self.imagemessage = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.imageMessage;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.imageMessage;
        }
        return [[CMImageMessageItem alloc]init];
    };
    self.content = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.content;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.content;
        }
        return @"";
    };
    self.sent = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.sent;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.sent;
        }
        return [NSNumber numberWithInteger:CMSendMessageStateSuccess];
    };
    self.sendTime = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.sendTime;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.sendTime;
        }
        return [NSDate date];
    };
    self.icon = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.icon;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.icon;
        }
        return @"";
    };
    self.isGroup = ^(CMBaseItem *baseItem) {
        if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            return YES;
        }
        return NO;
    };
    self.fromName = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.fromName;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.fromName;
        }
        return @"";
    };
    self.toJid = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.toJID;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.roomJID;
        }
        return @"";
    };
    self.uid = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.uID;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.fromID;
        }
        return @"";
    };
    self.mid = ^(CMBaseItem *baseItem) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            return item.mID;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            return item.mID;
        }
        return @"";
    };
    
    self.setFromName = ^(CMBaseItem *baseItem,NSString *fromName) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            item.fromName = fromName;
            baseItem = item;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            item.fromName = fromName;
            baseItem = item;
        }
    };
    
    self.setIcon = ^(CMBaseItem *baseItem,NSString *icon) {
        if ([baseItem isKindOfClass:[CMMessageItem class]]) {
            CMMessageItem *item = (CMMessageItem *)baseItem;
            item.icon = icon;
            baseItem = item;
        }else if([baseItem isKindOfClass:[CMGroupMessageItem class]]){
            CMGroupMessageItem *item = (CMGroupMessageItem *)baseItem;
            item.icon = icon;
            baseItem = item;
        }
    };
    
    self.chatTypeStr = ^(CMChatType chatType) {
        if (chatType == CMSingleChatType) {
            return @"CMMessageItem";
        }else if(chatType == CMGroupChatType){
            return @"CMGroupMessageItem";
        }
        return @"";
    };
}

@end
