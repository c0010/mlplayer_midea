//
//  CMMsgPackageUtils.h
//  MLPlayer
//
//  将信息组装成coredata的模型
//  Created by water on 14-9-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XMPPFramework.h"
#import "cmqalist.h"

@interface CMMsgPackageUtils : NSObject

//组装xmppmessage
+ (XMPPMessage *)packageXmppMessage:(CMBaseItem *)baseItem;
/**
 *  发送文字消息
 *
 *  @param content   发送内容
 *  @param chatType  发送类型（单聊与群聊）
 *  @param toName    被发送者名称
 *  @param toJid     被发送者jid，单聊为用户jid，群聊为roomjid
 *  @return
 */
+ (CMBaseItem *)packageMessageWithContent:(NSString *)content chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid;

/**
 *  发送图片消息
 *
 *  @param path      图片的文件地址（本地）
 *  @param chatType  发送类型（单聊与群聊）
 *  @param toName    被发送者名称
 *  @param toJid     被发送者jid，单聊为用户jid，群聊为roomjid
 *  @return
 */
+ (CMBaseItem *)packageMessageWithImage:(NSString *)path chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid vertical:(BOOL)isVertical;

/**
 *  发送课件消息
 *
 *  @param currItem  课件
 *  @param chatType  发送类型（单聊与群聊）
 *  @param toName    被发送者名称
 *  @param toJid     被发送者jid，单聊为用户jid，群聊为roomjid
 *  @return
 */
+ (CMBaseItem *)packageMessageWithCourse:(TBrowserItem* )currItem chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid;
/**
 *  发送问答消息
 *
 *  @param currItem  问答
 *  @param chatType  发送类型（单聊与群聊）
 *  @param toName    被发送者名称
 *  @param toJid     被发送者jid，单聊为用户jid，群聊为roomjid
 *  @return
 */
+ (CMBaseItem *)packageMessageWithQa:(TQAItem* )currItem chatType:(CMChatType)chatType toName:(NSString *)toName toJid:(NSString *)toJid;
@end
