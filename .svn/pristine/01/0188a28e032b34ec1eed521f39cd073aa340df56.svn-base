//
//  CMInteractModel.h
//  MLPlayer
//
//  互动数据model
//  Created by 王浩沣 on 14-6-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "cmgroup.h"
#import "CMInteractConfig.h"

@class CMMessageItem;
@class CMGroupMessageItem;
@class CMBaseItem;

@interface CMBaseItem : NSManagedObject

@end

@interface CMSysMessageItem : NSManagedObject
@property(nonatomic,strong)NSString* key;
@property(nonatomic,strong)NSString* rawSenderID;//发送者信息
@property(nonatomic,strong)NSString* rawSenderName;
@property(nonatomic,strong)NSString* roomID;//接收者信息
@property(nonatomic,strong)NSString* roomJID;//接收者信息
@property(nonatomic,strong)NSString* roomName;
@property(nonatomic,strong)NSString* password;
@property(nonatomic,assign)NSInteger state;//1已同意，2已拒绝
@property(nonatomic,strong)CMMessageItem* messageinfo;
@property(nonatomic,assign)BOOL skip;
@property(nonatomic,strong)CMGroupMessageItem* messagegroupinfo;

@end

@interface CMCourseMessageItem : NSManagedObject
@property(nonatomic,strong)NSString* title;
@property(nonatomic,strong)NSString* desc;
@property(nonatomic,strong)NSString* icon;
@property(nonatomic,strong)NSString* model;
@property(nonatomic,strong)NSString* sID;
@property(nonatomic,strong)NSString* flag;//"course,news等"
@property(nonatomic,strong)CMMessageItem* messageinfo;
@property(nonatomic,strong)CMGroupMessageItem* messagegroupinfo;
@end

@interface CMQaMessageItem : NSManagedObject
@property(nonatomic,strong)NSString* name;
@property(nonatomic,strong)NSString* question;
@property(nonatomic,strong)NSString* image;
@property(nonatomic,strong)NSString* sID;
@property(nonatomic,strong)CMMessageItem* messageinfo;
@property(nonatomic,strong)CMGroupMessageItem* messagegroupinfo;
@end

@interface CMImageMessageItem : NSManagedObject
@property(nonatomic,assign)NSNumber *isVertical;//图片的显示方向
@property(nonatomic,strong)NSString* url;//原图地址
@property(nonatomic,strong)NSString* thumb_url;//缩略图地址
@property(nonatomic,strong)CMMessageItem* messageinfo;
@property(nonatomic,strong)CMGroupMessageItem* messagegroupinfo;
@end


@interface CMMessageItem : CMBaseItem{
   
}
@property(nonatomic,strong)NSString* content;
@property(nonatomic,strong)NSString* fromName;//发送者信息
@property(nonatomic,strong)NSString* fromJID;
@property(nonatomic,strong)NSString* toName;//接收者信息
@property(nonatomic,strong)NSString* toJID;
@property(nonatomic,strong)NSString* icon;
@property(nonatomic,strong)NSString* uID;
@property(nonatomic,strong)NSString* mID;//唯一标示此条消息;
@property(nonatomic,strong)NSDate* sendTime;
@property(nonatomic,assign)NSNumber* sent;//发送失败-1,发送中0,发送成功1
@property(nonatomic)NSInteger type;//type 课程课件分享 10
@property(nonatomic,strong)CMSysMessageItem* sysmessage;
@property(nonatomic,strong)CMCourseMessageItem* coursemessage;
@property(nonatomic,strong)CMQaMessageItem* qamessage;
@property(nonatomic,assign)BOOL isShowSendTime;
@property(nonatomic,assign)BOOL isFromMe;
@property(nonatomic,strong)CMImageMessageItem* imageMessage;

@end

@interface CMGroupMessageItem : CMBaseItem

@property(nonatomic,strong)NSString* content;
@property(nonatomic,strong)NSString* fromName;//发送者信息
@property(nonatomic,strong)NSString* fromJID;
@property(nonatomic,strong)NSString* fromID;
@property(nonatomic,strong)NSString* icon;
@property(nonatomic,strong)NSDate* sendTime;
@property(nonatomic,assign)NSInteger type;
@property(nonatomic,strong)CMSysMessageItem* sysgroupmessage;
@property(nonatomic) BOOL isFromMe;
@property(nonatomic,strong)NSString* mID;//唯一标示此条消息;
@property(nonatomic,strong)NSString* nickName;
@property(nonatomic,strong)NSString* roomJID;
@property(nonatomic,strong)NSString* roomName;
@property(nonatomic,assign)BOOL isShowSendTime;
@property(nonatomic,assign)NSNumber *sent;//发送失败-1,发送中0,发送成功1
@property(nonatomic,strong)CMCourseMessageItem* coursemessage;
@property(nonatomic,strong)CMQaMessageItem* qamessage;
@property(nonatomic,strong)CMImageMessageItem* imageMessage;

@end

@interface CMGroupItem : NSManagedObject
@property(nonatomic,strong)NSString* roomID;
@property(nonatomic,strong)NSString* roomJID;
@property(nonatomic,strong)NSString* roomName;
@property(nonatomic,strong)NSString* desc;
@property(nonatomic,strong)NSString* icon;
@property(nonatomic,strong)NSString* password;
@property(nonatomic,strong)NSNumber* isJoined;
@property(nonatomic,strong)NSString* roomOwner;
@property(nonatomic,strong)NSString* roomNumber;
@property(nonatomic,strong)NSNumber* userCount;
@property(nonatomic,strong)NSNumber* flag;
@property(nonatomic,strong)NSNumber* occupant;

@end

@interface CMDialogueItem : NSManagedObject
@property(nonatomic,strong)NSString* fromJID;
@property(nonatomic,strong)NSString* fromID;
@property(nonatomic,strong)NSString* fromName;
@property(nonatomic,strong)NSString* lastMessage;
@property(nonatomic,strong)NSDate* sendTime;
@property(nonatomic,strong)NSString* icon;
@property(nonatomic,assign)NSInteger unread;
@property(nonatomic,strong)NSString* roomName;
@property(nonatomic,strong)NSString* roomJID;
@property(nonatomic,strong)NSString* roomID;
@property(nonatomic,strong)NSString* password;
@property(nonatomic)int32_t flag;//区分0单聊会话，1群会话
@property(nonatomic,strong)NSNumber *isJoined;
@property(nonatomic,strong)NSString *draft;

@end

@interface CMUserItem : NSManagedObject

@property (nonatomic, strong) NSString * icon;
@property (nonatomic, strong) NSString * name;
@property (nonatomic, strong) NSString * uid;
@property (nonatomic, strong) NSString * jid;
@property (nonatomic, strong) NSString * sDep;
@property (nonatomic, strong) NSString * sPosition;
@property (nonatomic, strong) NSString * sMobilenumber;
@property (nonatomic, strong) NSString * sPhonenumber;
@property (nonatomic, strong) NSString * sEmail;

@end

@interface CMVersion : NSManagedObject

@property (nonatomic, strong) NSNumber* version;

@end

@interface CMMemberItem : NSManagedObject

@property (nonatomic, strong) NSString * icon;
@property (nonatomic, strong) NSString * name;
@property (nonatomic, strong) NSString * uid;
@property (nonatomic, strong) NSString * jid;
@property (nonatomic, strong) NSString * roomID;
@property (nonatomic, strong) NSNumber * type;

@end