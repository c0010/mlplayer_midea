//
//  CMParseXmppMessage.h
//  MLPlayer
//  将xml解析出messageItem对象属性
//  Created by water on 14-9-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XMPP.h"
#import "CMInteractModel.h"

@interface CMParseXmppMessage : NSObject

//解析课件
+ (CMCourseMessageItem *) parseXmppMessageToCourse:(XMPPMessage *)message;

//解析问答
+ (CMQaMessageItem *) parseXmppMessageToQa:(XMPPMessage *)message;

//解析图片
+ (CMImageMessageItem *) parseXmppMessageToImage:(XMPPMessage *)message;

@end
