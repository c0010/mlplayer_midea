//
//  CMMsgBlock.h
//  MLPlayer
//  用于获取baseItem属性
//  Created by water on 14-9-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CMInteractModel.h"

typedef NSInteger               (^Type)(CMBaseItem *item);
typedef BOOL                    (^IsFromMe)(CMBaseItem *item);
typedef BOOL                    (^IsShowSendTime)(CMBaseItem *item);
typedef BOOL                    (^IsGroup)(CMBaseItem *item);
typedef CMCourseMessageItem *   (^Coursemessage)(CMBaseItem *item);
typedef CMQaMessageItem *       (^QAmessage)(CMBaseItem *item);
typedef CMImageMessageItem *    (^Imagemessage)(CMBaseItem *item);
typedef NSString *              (^Content)(CMBaseItem *item);
typedef NSNumber *              (^Sent)(CMBaseItem *item);
typedef NSDate *                (^SendTime)(CMBaseItem *item);
typedef NSString *              (^Icon)(CMBaseItem *item);
typedef NSString *              (^FromName)(CMBaseItem *item);
typedef NSString *              (^ToJid)(CMBaseItem *item);
typedef NSString *              (^Uid)(CMBaseItem *item);
typedef NSString *              (^Mid)(CMBaseItem *item);

typedef NSString*               (^ChatTypeStr)(CMChatType chatType);

typedef void              (^SetFromName)(CMBaseItem *,NSString *);
typedef void              (^SetIcon)(CMBaseItem *,NSString *);

@interface CMMsgBlock : NSObject

@property (nonatomic,strong) Type type;
@property (nonatomic,strong) IsFromMe isFromMe;
@property (nonatomic,strong) IsShowSendTime isShowSendTime;
@property (nonatomic,strong) Coursemessage coursemessage;
@property (nonatomic,strong) QAmessage qamessage;
@property (nonatomic,strong) Content content;
@property (nonatomic,strong) IsGroup isGroup;
@property (nonatomic,strong) Sent sent;
@property (nonatomic,strong) SendTime sendTime;
@property (nonatomic,strong) Icon icon;
@property (nonatomic,strong) FromName fromName;
@property (nonatomic,strong) Imagemessage imagemessage;
@property (nonatomic,strong) ToJid toJid;
@property (nonatomic,strong) Uid uid;
@property (nonatomic,strong) Mid mid;
@property (nonatomic,strong) ChatTypeStr chatTypeStr;

@property (nonatomic,strong) SetFromName setFromName;
@property (nonatomic,strong) SetIcon setIcon;

+ (instancetype)sharedInstance;

@end
