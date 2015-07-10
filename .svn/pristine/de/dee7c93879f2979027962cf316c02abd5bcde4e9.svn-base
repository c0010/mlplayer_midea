//
//  CMParseXmppMessage.m
//  MLPlayer
//
//  Created by water on 14-9-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMParseXmppMessage.h"

#import "XMPPChatMessageCoreDataStorage.h"

@implementation CMParseXmppMessage

+ (CMCourseMessageItem *) parseXmppMessageToCourse:(XMPPMessage *)message{
    
    NSXMLElement *browseitem  = [message elementForName:@"browseitem" xmlns:@"xmpp:wunding:share"];
    
    CMCourseMessageItem* courseitem = [NSEntityDescription insertNewObjectForEntityForName:@"CMCourseMessageItem" inManagedObjectContext:MessageObjectContext];
    courseitem.title = [browseitem attributeStringValueForName:@"title"];
    courseitem.desc = [browseitem attributeStringValueForName:@"desc"];
    courseitem.model = [browseitem attributeStringValueForName:@"model"];
    courseitem.icon = [browseitem attributeStringValueForName:@"icon"];
    courseitem.sID = [browseitem attributeStringValueForName:@"id"];
    courseitem.flag = [browseitem attributeStringValueForName:@"flag"];
    return courseitem;
}

+ (CMQaMessageItem *) parseXmppMessageToQa:(XMPPMessage *)message{
    
    NSXMLElement *browseitem  = [message elementForName:@"qaitem" xmlns:@"xmpp:wunding:qa"];
    
    CMQaMessageItem* qaitem = [NSEntityDescription insertNewObjectForEntityForName:@"CMQaMessageItem" inManagedObjectContext:MessageObjectContext];
    qaitem.name = [NSString stringWithFormat:@"%@",[browseitem attributeStringValueForName:@"qaname"]];
    qaitem.question = [browseitem attributeStringValueForName:@"question"];
    qaitem.image = [browseitem attributeStringValueForName:@"qaimage"];
    qaitem.sID = [browseitem attributeStringValueForName:@"id"];
    return qaitem;
}

+ (CMImageMessageItem *) parseXmppMessageToImage:(XMPPMessage *)message{
    
    NSXMLElement *imageitem  = [message elementForName:@"imageitem" xmlns:@"xmpp:wunding:image"];
    
    CMImageMessageItem* imageMessageItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMImageMessageItem" inManagedObjectContext:MessageObjectContext];
    imageMessageItem.isVertical = [NSNumber numberWithBool:[imageitem attributeBoolValueForName:@"vertical"]];
    imageMessageItem.url = [imageitem attributeStringValueForName:@"url"];
    imageMessageItem.thumb_url = [imageitem attributeStringValueForName:@"thumb_url"];
    return imageMessageItem;
}
@end
