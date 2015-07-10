//
//  CMCoreDataUtils.h
//  MLPlayer
//  操作coredata数据库
//  Created by water on 14-9-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CMInteractModel.h"
#import "CMMsgManager.h"

@interface CMCoreDataUtils : NSObject

//根据条件清除多条数据
+ (void)clearManagedObjects:(NSString *)className;
+ (void)clearManagedObjects:(NSString *)className withPredicate:(NSPredicate *)predicate;

//根据条件清楚单条数据
+ (void)clearManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate;

//根据条件获取多条数据
+ (NSArray *)fetchManagedObjects:(NSString *)className;
+ (NSArray *)fetchManagedObjects:(NSString *)className withPredicate:(NSPredicate *)predicate;

//根据条件获取单条数据
+ (NSManagedObject *)fetchManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate;
+ (NSManagedObject *)fetchManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate sortDescriptor:(NSSortDescriptor *)sortDescriptor;

//根据条件判断某条数据是否存在
+ (BOOL)existManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate;
+ (BOOL)existManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate sortDescriptor:(NSSortDescriptor *)sortDescriptor;

//移除不存在的群组缓存
+ (void)removeNotExistGroupCache:(CMGroup *)m_pGroups;

//通过关键字搜索群组缓存
+ (NSMutableArray *) filterGroupCacheWithKeyword:(NSString *)keyWord;

//通过关键字搜索群组成员
+ (NSMutableArray *)filterContacts:(NSMutableArray *)dataArray keyword:(NSString *)keyWord;

//把groupitem组装成searchModel
+ (NSMutableArray *) packageSearchModel:(NSMutableArray *)dataArray;

//从系统消息获取群组信息并保存
+ (void)saveGruopCacheFromSystemMessage:(CMSysMessageItem *)sysitem;

//从TGroupInfoItem获取群组信息并保存
+ (void)saveGruopCacheFromTGroupInfoItem:(TGroupInfoItem)item resetJoined:(BOOL)reset;

//判断消息时间与最后一个分组时间的时间差,如果超过时间差，则分组，否则合并消息。
+ (BOOL)isRequireSortMsgWithJid:(NSString *)jid type:(CMChatType)type date:(NSDate *)date;

//未读消息总数
+ (int)fetchUnreadAmount;

//设置tabbar的消息提醒
+ (void)updateBadgeValueWithTabBar:(UITabBarItem *)barItem;

//更新用户头像
+ (void)updateUserCacheWithIcon:(NSString *)icon;

//过滤同一个群重复的系统消息（可交互的系统消息）
+ (BOOL)existSystemMessageWithRoomJid:(NSString *)roomJid type:(CMInteractSystemMessageType)type;

+ (void)saveGroupMembersWithTContactsItem:(TContactsItem)item roomID:(NSString *)roomID;

//清除群组所有缓存
+ (void) clearAllCacheWithRoomJid:(NSString *)roomJID;
@end
