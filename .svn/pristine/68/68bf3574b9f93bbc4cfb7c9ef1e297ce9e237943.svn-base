//
//  CMInteractModel.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMInteractModel.h"

@implementation CMBaseItem

@end

@implementation CMSysMessageItem
@dynamic key;
@dynamic rawSenderID;
@dynamic rawSenderName;
@dynamic roomID;
@dynamic roomName;
@dynamic messageinfo;
@dynamic messagegroupinfo;
@dynamic state;//0未知，1同意，2拒绝
@dynamic password;
@dynamic roomJID;
@dynamic skip;

@end

@implementation CMCourseMessageItem
@dynamic model;
@dynamic title;
@dynamic desc;
@dynamic icon;
@dynamic flag;
@dynamic sID;
@dynamic messageinfo;
@dynamic messagegroupinfo;
@end

@implementation CMImageMessageItem
@dynamic isVertical;
@dynamic url;
@dynamic thumb_url;
@dynamic messageinfo;
@dynamic messagegroupinfo;

@end

@implementation CMMessageItem
@dynamic sendTime;
@dynamic type;
@dynamic content;
@dynamic fromJID;
@dynamic fromName;
@dynamic isFromMe;
@dynamic toJID;
@dynamic toName;
@dynamic sysmessage;
@dynamic icon;
@dynamic uID;
@dynamic coursemessage;
@dynamic isShowSendTime;
@dynamic sent;
@dynamic imageMessage;
@dynamic mID;
@dynamic qamessage;

- (void) awakeFromInsert
{
    [super awakeFromInsert];
}

- (NSString *)getFromJid{
    return self.fromJID;
}


@end

@implementation CMGroupMessageItem
@dynamic sendTime;
@dynamic type;
@dynamic content;
@dynamic fromJID;
@dynamic fromID;
@dynamic fromName;
@dynamic nickName;
@dynamic sysgroupmessage;
@dynamic icon;
@dynamic roomName;
@dynamic roomJID;
@dynamic isFromMe;
@dynamic isShowSendTime;
@dynamic sent;
@dynamic coursemessage;
@dynamic imageMessage;
@dynamic mID;
@dynamic qamessage;

- (void) awakeFromInsert
{
    [super awakeFromInsert];
}

@end

@implementation CMGroupItem
@dynamic roomID;
@dynamic roomJID;
@dynamic roomName;
@dynamic desc;
@dynamic icon;
@dynamic password;
@dynamic isJoined;
@dynamic roomOwner;
@dynamic roomNumber;
@dynamic userCount;
@dynamic flag;
@dynamic occupant;

- (void) awakeFromInsert
{
    [super awakeFromInsert];
    
}

@end


@implementation CMDialogueItem
@dynamic fromJID,fromName,lastMessage,sendTime,icon,unread,roomJID,roomName,flag,roomID,password,isJoined,fromID,draft;

- (void) awakeFromInsert
{
    [super awakeFromInsert];

    [self setSendTime:[NSDate date]];
}

@end

@implementation CMUserItem

@dynamic icon;
@dynamic name;
@dynamic uid;
@dynamic jid;
@dynamic sDep;
@dynamic sMobilenumber;
@dynamic sPhonenumber;
@dynamic sEmail;
@dynamic sPosition;

@end

@implementation CMVersion

@dynamic version;

@end

@implementation CMMemberItem

@dynamic icon;
@dynamic name;
@dynamic uid;
@dynamic jid;
@dynamic roomID;
@dynamic type;

@end


@implementation CMQaMessageItem

@dynamic image;
@dynamic sID;
@dynamic name;
@dynamic question;
@dynamic messageinfo;
@dynamic messagegroupinfo;

@end
