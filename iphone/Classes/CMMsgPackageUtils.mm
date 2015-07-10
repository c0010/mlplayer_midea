//
//  CMMsgPackageUtils.m
//  MLPlayer
//
//  Created by water on 14-9-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMMsgPackageUtils.h"
#import "CMMsgManager.h"
#import "CMInteractModel.h"
#import "cmsettings.h"
#import "CMGroupManager.h"
#import "CMContactManager.h"
#import "CMMsgBlock.h"
#import "CMCoreDataUtils.h"
#import "CMFileUtils.h"

@implementation CMMsgPackageUtils

//组装message
+ (XMPPMessage *)packageXmppMessage:(CMBaseItem *)baseItem{
    
    NSString *messageType = MBlock.isGroup(baseItem) ? MsgTypeGroupChat : MsgTypeSingleChat;
    
    XMPPMessage *message = [XMPPMessage messageWithType: messageType to:[XMPPJID jidWithString:MBlock.toJid(baseItem)]elementID:MBlock.mid(baseItem)];
    [message addBody:MBlock.content(baseItem)];
    
    NSXMLElement *userInfo = [NSXMLElement elementWithName:@"userinfo" xmlns:@"xmpp:wunding"];
    
    [userInfo addAttributeWithName:@"id" stringValue:MBlock.uid(baseItem)];
    [userInfo addAttributeWithName:@"name" stringValue:MBlock.fromName(baseItem)];
    [userInfo addAttributeWithName:@"icon" stringValue:MBlock.icon(baseItem)];
	[message addChild:userInfo];
    
    
    if (MBlock.type(baseItem) == CMMessageCourseType && MBlock.coursemessage(baseItem)) {
        [message removeElementForName:@"body"];//移除body
        
        CMCourseMessageItem *coursemessage = MBlock.coursemessage(baseItem);
        NSXMLElement *browseitem = [NSXMLElement elementWithName:@"browseitem" xmlns:@"xmpp:wunding:share"];
        [browseitem addAttributeWithName:@"model" stringValue:coursemessage.model];
        [browseitem addAttributeWithName:@"title" stringValue:coursemessage.title];
        [browseitem addAttributeWithName:@"desc" stringValue:coursemessage.desc];
        [browseitem addAttributeWithName:@"icon" stringValue:coursemessage.icon];
        [browseitem addAttributeWithName:@"id" stringValue:coursemessage.sID];
        [browseitem addAttributeWithName:@"flag" stringValue:coursemessage.flag];
        [message addChild:browseitem];
    }else if (MBlock.type(baseItem) == CMMessageQAType && MBlock.qamessage(baseItem)) {
        [message removeElementForName:@"body"];//移除body
        
        CMQaMessageItem *qamessage = MBlock.qamessage(baseItem);
        NSXMLElement *browseitem = [NSXMLElement elementWithName:@"qaitem" xmlns:@"xmpp:wunding:qa"];
        [browseitem addAttributeWithName:@"qaname" stringValue:qamessage.name];
        [browseitem addAttributeWithName:@"question" stringValue:qamessage.question];
        [browseitem addAttributeWithName:@"qaimage" stringValue:qamessage.image];
        [browseitem addAttributeWithName:@"id" stringValue:qamessage.sID];
        [message addChild:browseitem];
    }
    return message;
}

+ (CMMessageItem *)packageMessageWithToName:(NSString *)toName toJid:(NSString *)toJid chatType:(CMChatType)chatType{
    
    //建立数据
    CMMessageItem* item = [NSEntityDescription insertNewObjectForEntityForName:@"CMMessageItem" inManagedObjectContext:MessageObjectContext];
    item.fromJID = kXMPPJid;
    item.fromName = kCurrUser.name;
    item.isFromMe = YES;
    item.mID = [XMPPStream generateUUID];
    
    item.toName = toName;
    item.toJID = toJid;
    item.uID = kCurrUser.uid;
    item.icon = kCurrUser.icon;
    item.sent = [NSNumber numberWithInteger:CMSendMessageStateSending];
    
    item.sendTime = [NSDate date];
    item.isShowSendTime = [CMCoreDataUtils isRequireSortMsgWithJid:toJid type:chatType date:item.sendTime];
    return item;
}

+ (CMGroupMessageItem *)packageGroupMessageWithToName:(NSString *)toName toJid:(NSString *)toJid chatType:(CMChatType)chatType{
    
    //建立数据
    CMGroupMessageItem* item = [NSEntityDescription insertNewObjectForEntityForName:@"CMGroupMessageItem" inManagedObjectContext:MessageObjectContext];
    item.fromJID = kXMPPJid;
    item.fromName = kCurrUser.name;
    item.fromID = kCurrUser.uid;
    item.isFromMe = YES;
    item.mID = [XMPPStream generateUUID];
    
    item.roomName = toName;
    item.roomJID = toJid;
    item.icon = kCurrUser.icon;
    item.sent = [NSNumber numberWithInteger:CMSendMessageStateSending];

    item.sendTime = [NSDate date];
    item.isShowSendTime = [CMCoreDataUtils isRequireSortMsgWithJid:toJid type:chatType date:item.sendTime];
    return item;
}

+ (CMCourseMessageItem *)packageCourseMessageWithCourse:(TBrowserItem* )currItem {
    
    CMCourseMessageItem* courseitem = [NSEntityDescription insertNewObjectForEntityForName:@"CMCourseMessageItem" inManagedObjectContext:MessageObjectContext];
    courseitem.model = [NSString stringWithFormat:@"%d",currItem->nModel];
    courseitem.title = [NSString stringWithUTF8String:currItem->sTitle];
    courseitem.desc = [NSString stringWithUTF8String:currItem->sDescription];
    courseitem.icon = [NSString stringWithUTF8String:currItem->sThumbs];
    courseitem.flag = [NSString stringWithUTF8String:currItem->sFlag];
    courseitem.sID = [NSString stringWithUTF8String:currItem->sID];
    return courseitem;
}

+ (CMQaMessageItem *)packageQaMessageWithQa:(TQAItem* )currItem {
    
    CMQaMessageItem* qaitem = [NSEntityDescription insertNewObjectForEntityForName:@"CMQaMessageItem" inManagedObjectContext:MessageObjectContext];
    
    NSString *fullName = @"";
    if ( currItem->bIsanonymity ) {
        fullName = I(@"匿名");
    }else{
        fullName = [NSString stringWithUTF8String:currItem->sQuestioner_fullname.c_str()];
    }
    
    qaitem.name = fullName;
    qaitem.question = [NSString stringWithUTF8String:currItem->sQuestion.c_str()];
    qaitem.image = [NSString stringWithUTF8String:currItem->sThumburl.c_str()];
    qaitem.sID = [NSString stringWithUTF8String:currItem->sID.c_str()];
    return qaitem;
}

+ (CMImageMessageItem *)packageImageMessageWithVertical:(BOOL)isVertical {
    
    CMImageMessageItem* imageMessageItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMImageMessageItem" inManagedObjectContext:MessageObjectContext];
    imageMessageItem.isVertical = [NSNumber numberWithBool:isVertical];
    return imageMessageItem;
}

+ (CMBaseItem *)packageMessageWithContent:(NSString *)content chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid
{
    if (chatType == CMSingleChatType) {
        
        CMMessageItem *item = [[self class] packageMessageWithToName:toName toJid:toJid chatType:chatType];
        item.content = content;
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        return item;

        
    }else if (chatType == CMGroupChatType){
        
        CMGroupMessageItem *item = [[self class] packageGroupMessageWithToName:toName toJid:toJid chatType:chatType];
        item.content = content;
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        return item;

    }
    
    return nil;

}

+ (CMBaseItem *)packageMessageWithImage:(NSString *)path chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid vertical:(BOOL)isVertical
{
    if (chatType == CMSingleChatType) {
        
        CMMessageItem *item = [[self class] packageMessageWithToName:toName toJid:toJid chatType:chatType];
        item.content = path;
        item.type = CMMessageImageType;
        item.imageMessage = [[self class] packageImageMessageWithVertical:isVertical];
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        return item;
        
    }else if (chatType == CMGroupChatType){
        
        CMGroupMessageItem *item = [[self class] packageGroupMessageWithToName:toName toJid:toJid chatType:chatType];
        item.content = path;
        item.type = CMMessageImageType;
        item.imageMessage = [[self class] packageImageMessageWithVertical:isVertical];
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        return item;
    }
    
    return nil;
}

+ (CMBaseItem *)packageMessageWithCourse:(TBrowserItem* )currItem chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid
{
    
    if (chatType == CMSingleChatType) {
        
        CMMessageItem* item = [[self class] packageMessageWithToName:toName toJid:toJid chatType:chatType];
        
        item.type = CMMessageCourseType;
        item.coursemessage = [[self class] packageCourseMessageWithCourse:currItem];
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        return item;


    }else if (chatType == CMGroupChatType){
        
        CMGroupMessageItem* item = [[self class] packageGroupMessageWithToName:toName toJid:toJid chatType:chatType];
        item.type = CMMessageCourseType;
        item.coursemessage = [[self class] packageCourseMessageWithCourse:currItem];
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        return item;

    }
    
    return nil;

}

+ (CMBaseItem *)packageMessageWithQa:(TQAItem* )currItem chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid
{
    
    if (chatType == CMSingleChatType) {
        
        CMMessageItem* item = [[self class] packageMessageWithToName:toName toJid:toJid chatType:chatType];
        
        item.type = CMMessageQAType;
        item.qamessage = [[self class] packageQaMessageWithQa:currItem];
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        return item;
        
        
    }else if (chatType == CMGroupChatType){
        
        CMGroupMessageItem* item = [[self class] packageGroupMessageWithToName:toName toJid:toJid chatType:chatType];
        item.type = CMMessageQAType;
        item.qamessage = [[self class] packageQaMessageWithQa:currItem];
        
        __block NSError *error = NULL;
        if (![MessageObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        return item;
        
    }
    
    return nil;
    
}

@end
