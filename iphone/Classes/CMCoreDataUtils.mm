//
//  CMCoreDataUtils.m
//  MLPlayer
//
//  Created by water on 14-9-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMCoreDataUtils.h"
#import "XMPPChatMessageCoreDataStorage.h"
#import "CMSearchModel.h"
#import "pinyin.h"
#import "CMMsgBlock.h"
#import "cmgroup.h"

@implementation CMCoreDataUtils

+ (void)clearManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate{
    
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription entityForName:className inManagedObjectContext:MessageObjectContext];
    
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchLimit:1];
    
    [fetchRequest setPredicate:predicate];
    
    NSError *error = NULL;
    NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];
    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
    }
    
    if (array && [array count] > 0) {
        
        NSManagedObject *object = [array objectAtIndex:0];
        
        [MessageObjectContext deleteObject:object];
    }
    
    [MessageObjectContext save:NULL];
}

+ (void)clearManagedObjects:(NSString *)className withPredicate:(NSPredicate *)predicate{
    
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription entityForName:className inManagedObjectContext:MessageObjectContext];
    
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchLimit:CacheMaxForDialogueCount];
    
    [fetchRequest setPredicate:predicate];
    
    NSError *error = NULL;
    NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];
    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
    }
    
    NSArray *dataArray = [NSArray arrayWithArray:array];
    for (NSManagedObject *object in dataArray) {
        [MessageObjectContext deleteObject:object];
    }
    [MessageObjectContext save:&error];
}

+ (void)clearManagedObjects:(NSString *)className{
    
    [[self class] fetchManagedObjects:className withPredicate:nil];
}

+ (NSArray *)fetchManagedObjects:(NSString *)className withPredicate:(NSPredicate *)predicate{
    
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription entityForName:className inManagedObjectContext:MessageObjectContext];
    
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchBatchSize:CacheMaxForGroupCount];
    
    [fetchRequest setPredicate:predicate];
    
    NSError *error = NULL;
    __autoreleasing NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];
    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
        
        return nil;
    }
    
    return array;
}

+ (NSArray *)fetchManagedObjects:(NSString *)className{
    
    return  [[self class] fetchManagedObjects:className withPredicate:nil];
}

+ (NSManagedObject *)fetchManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate{
    
    return [self fetchManagedObject:className withPredicate:predicate sortDescriptor:nil];
}

+ (NSManagedObject *)fetchManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate sortDescriptor:(NSSortDescriptor *)sortDescriptor{
    
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription entityForName:className inManagedObjectContext:MessageObjectContext];
    
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchLimit:1];
    
    [fetchRequest setPredicate:predicate];
    
    if ( sortDescriptor ) {
        [fetchRequest setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    }
    
    NSError *error = NULL;
    NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];
    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
    }
    
    if (array && [array count] > 0) {
        NSManagedObject *object = [array objectAtIndex:0];
        return  object;
    }
    return nil;
}

+ (void) clearAllCacheWithRoomJid:(NSString *)roomJID{
    
    //移除缓存,包括聊天记录
    [CMCoreDataUtils clearManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(roomJID)];
    [CMCoreDataUtils clearManagedObject:NSStringFromClass([CMDialogueItem class]) withPredicate:Pre_RoomJid(roomJID)];
    [CMCoreDataUtils clearManagedObject:NSStringFromClass([CMGroupMessageItem class]) withPredicate:Pre_RoomJid(roomJID)];
}

+ (BOOL)existManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate
{
    
    return [self existManagedObject:className withPredicate:predicate sortDescriptor:nil];
}

+ (BOOL)existManagedObject:(NSString *)className withPredicate:(NSPredicate *)predicate sortDescriptor:(NSSortDescriptor *)sortDescriptor
{
    
    if ([[self class] fetchManagedObject:className withPredicate:predicate sortDescriptor:sortDescriptor]) {
        
        return YES;
    }
    
    return NO;
}

+ (void)removeNotExistGroupCache:(CMGroup *)m_pGroups{

    
    BOOL ( ^existGroup ) (NSString *) = ^(NSString *roomJid){
        
        for (int i = 0; i < m_pGroups->GetItemCount(); i ++) {
            
            TGroupInfoItem item;
            if (m_pGroups && m_pGroups->GetItem(i,  item)) {
                
                if ([[NSString stringWithUTF8String:item.sJID.c_str()] isEqualToString:roomJid]) {
                    
                    return YES;
                }
            }
        }
        
        return NO;
    };
    
    //移除群组缓存
    NSArray *gcaches = [[self class] fetchManagedObjects:NSStringFromClass([CMGroupItem class])];
    
    for (CMGroupItem *item in gcaches) {
        
        if ( !existGroup(item.roomJID)) {
            
            [MessageObjectContext deleteObject:item];
        }
    }
    
    //移除会话缓存
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"flag == 1"];
    NSArray *dcaches = [[self class] fetchManagedObjects:NSStringFromClass([CMDialogueItem class]) withPredicate:predicate];
    
    for (CMDialogueItem *item in dcaches) {
        
        if ( !existGroup(item.roomJID) && [item.roomJID rangeOfString:@"@conference.cmb.wd.test.trylose.cn"].location!=NSNotFound) {
            
            [MessageObjectContext deleteObject:item];
        }
    }
    
    NSError *error = NULL;
    [MessageObjectContext save:&error];
    
    if (error) {
        NSLog(@"removeNotExistGroupCache Error : %@\n", [error localizedDescription]);
    }
}

+ (NSMutableArray *)filterGroupCacheWithKeyword:(NSString *)keyWord
{
    __autoreleasing NSMutableArray *returnArray = [NSMutableArray array];

    if (keyWord.length == 0) {
        return returnArray;
    }
    
    //获取群组缓存
    NSArray *dataArray = [[self class] fetchManagedObjects:NSStringFromClass([CMGroupItem class])];

    if (![ChineseInclude isIncludeChineseInString:keyWord]) {
        for (int i=0; i<dataArray.count; i++) {
            CMGroupItem *item = [dataArray objectAtIndex:i];

            if ([ChineseInclude isIncludeChineseInString:item.roomName]) {
                NSString *tempPinYinStr = [PinYinForObjc chineseConvertToPinYin:item.roomName];
                NSRange titleResult=[tempPinYinStr rangeOfString:keyWord options:NSCaseInsensitiveSearch];
                if (titleResult.length>0) {
                    [returnArray addObject:item];
                }else{
                
                    NSString *tempPinYinHeadStr = [PinYinForObjc chineseConvertToPinYinHead:item.roomName];
                    NSRange titleHeadResult=[tempPinYinHeadStr rangeOfString:keyWord options:NSCaseInsensitiveSearch];
                    if (titleHeadResult.length>0) {
                        [returnArray addObject:item];
                    }
                }
            }
            else {
                NSRange titleResult=[item.roomName rangeOfString:keyWord options:NSCaseInsensitiveSearch];
                if (titleResult.length>0) {
                    [returnArray addObject:item];
                }
            }
        }
    } else {
        for (CMGroupItem *item in dataArray) {
            NSRange titleResult=[item.roomName rangeOfString:keyWord options:NSCaseInsensitiveSearch];
            if (titleResult.length>0) {
                [returnArray addObject:item];
            }
        }
    }
    return returnArray;
}

+ (NSMutableArray *)filterContacts:(NSMutableArray *)dataArray keyword:(NSString *)keyWord
{
    if (keyWord.length == 0) {
        return dataArray;
    }
    
   __autoreleasing NSMutableArray *returnArray = [NSMutableArray array];

    if (![ChineseInclude isIncludeChineseInString:keyWord]) {
        for (int i=0; i<dataArray.count; i++) {
            CMSearchModel *item = [dataArray objectAtIndex:i];
            
            if ([ChineseInclude isIncludeChineseInString:item.name]) {
                NSString *tempPinYinStr = [PinYinForObjc chineseConvertToPinYin:item.name];
                NSRange titleResult=[tempPinYinStr rangeOfString:keyWord options:NSCaseInsensitiveSearch];
                if (titleResult.length>0) {
                    [returnArray addObject:item];
                }else{
                    NSString *tempPinYinHeadStr = [PinYinForObjc chineseConvertToPinYinHead:item.name];
                    NSRange titleHeadResult=[tempPinYinHeadStr rangeOfString:keyWord options:NSCaseInsensitiveSearch];
                    if (titleHeadResult.length>0) {
                        [returnArray addObject:item];
                    }
                }
            }
            else {
                NSRange titleResult=[item.name rangeOfString:keyWord options:NSCaseInsensitiveSearch];
                if (titleResult.length>0) {
                    [returnArray addObject:item];
                }
            }
        }
    } else {
        for (CMSearchModel *item in dataArray) {
            NSRange titleResult=[item.name rangeOfString:keyWord options:NSCaseInsensitiveSearch];
            if (titleResult.length>0) {
                [returnArray addObject:item];
            }
        }
    }
    
    //排序
    [returnArray sortUsingComparator:^NSComparisonResult(CMSearchModel* obj1, CMSearchModel* obj2) {
        
        if (obj1.manager > obj2.manager) {
            return NSOrderedAscending;
        }else if (obj1.manager < obj2.manager){
            return NSOrderedDescending;
        }
        else
            return NSOrderedSame;
    }];
    
    return returnArray;
}

+ (NSMutableArray *)packageSearchModel:(NSMutableArray *)dataArray
{
    NSMutableArray *returnArray = [NSMutableArray array];
    
    for (int i = 0; i < dataArray.count;i++) {
        
        CMGroupItem *item = [dataArray objectAtIndex:i];
        
        [returnArray addObject:[[CMSearchModel model] toGModel:item index:i]];
        
    }
    return returnArray;
}

+ (void)saveGruopCacheFromSystemMessage:(CMSysMessageItem *)sysitem{
    
    if (!sysitem.roomJID || [sysitem.roomJID isEqualToString:@""]) {
        return;
    }
    
    if ([[self class] existManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(sysitem.roomJID)]) {
        return;
    }
    NSError *error = NULL;
    CMGroupItem *groupItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMGroupItem" inManagedObjectContext:MessageObjectContext];
    groupItem.roomID = sysitem.roomID;
    groupItem.roomName = sysitem.roomName;
    groupItem.roomJID = sysitem.roomJID;
    groupItem.password = sysitem.password;
    
    if (![MessageObjectContext save:&error]) {
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
}

+ (void)saveGruopCacheFromTGroupInfoItem:(TGroupInfoItem)item resetJoined:(BOOL)reset{
    
    NSError *error = NULL;
    
    NSString *roomJid = [NSString stringWithUTF8String:item.sJID.c_str()];
    
    if (!roomJid || [roomJid isEqualToString:@""]) {
        return;
    }
    
    CMGroupItem *groupItem = (CMGroupItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(roomJid)];
    if (groupItem != nil) {
        groupItem.isJoined = [NSNumber numberWithBool:!reset];

        groupItem.roomName= [NSString stringWithUTF8String:item.sName.c_str()];
        groupItem.desc= [NSString stringWithUTF8String:item.sDescription.c_str()];
        
        groupItem.icon = [NSString stringWithUTF8String:item.sIconUrl.c_str()];
    }else{
        CMGroupItem *groupItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMGroupItem" inManagedObjectContext:MessageObjectContext];
        groupItem.roomID = [NSString stringWithUTF8String:item.sID.c_str()];
        groupItem.roomJID = [NSString stringWithUTF8String:item.sJID.c_str()];
        groupItem.roomName = [NSString stringWithUTF8String:item.sName.c_str()];
        groupItem.desc = [NSString stringWithUTF8String:item.sDescription.c_str()];
        groupItem.icon = [NSString stringWithUTF8String:item.sIconUrl.c_str()];
        groupItem.password = [NSString stringWithUTF8String:item.sPwd.c_str()];
        groupItem.isJoined = [NSNumber numberWithBool:!reset];

    }
    
    CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForRoomJid:roomJid];
    if (dialogueItem) {
        groupItem.isJoined = [NSNumber numberWithBool:!reset];

        dialogueItem.password = [NSString stringWithUTF8String:item.sPwd.c_str()];
        dialogueItem.icon = [NSString stringWithUTF8String:item.sIconUrl.c_str()];
    }
    
    if (![MessageObjectContext save:&error]) {
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
}

+ (BOOL)isRequireSortMsgWithJid:(NSString *)jid type:(CMChatType)type date:(NSDate *)date{
    
    //设定以时间排序
    NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:NO];
    //过滤数据
    NSPredicate *predicate;
    if (type == CMSingleChatType) {
        predicate = [NSPredicate predicateWithFormat:@" ((fromJID == %@)  OR (toJID == %@)) AND (isShowSendTime == 1)",jid,jid];
    }else if (type == CMGroupChatType){
        predicate = [NSPredicate predicateWithFormat:@" (roomJID == %@) AND (isShowSendTime == 1)",jid];
    }

    CMBaseItem* baseItem = (CMBaseItem *)[self fetchManagedObject:MBlock.chatTypeStr(type) withPredicate:predicate sortDescriptor:sortDescriptor];
    
    if ( !baseItem ) {
        return YES;
    }
    
    NSDate *sendTime = MBlock.sendTime(baseItem);
    //判断是否需要分组
    if ([date compare:[NSDate dateWithTimeInterval:ChatSortInterval sinceDate:sendTime]] ==  NSOrderedDescending) {
        return YES;
    }
    
    return NO;
}

+ (int)fetchUnreadAmount{
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init] ;
    
    NSEntityDescription *entity = [NSEntityDescription entityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];
    [fetchRequest setEntity:entity];
    
    [fetchRequest setFetchBatchSize:CacheMaxForDialogueCount];
    
    NSArray *allObjects = [MessageObjectContext executeFetchRequest:fetchRequest  error:nil];
    int total = 0;
    for (CMDialogueItem *item in allObjects) {
        total += item.unread;
    }
    return total;
}

+ (void)updateBadgeValueWithTabBar:(UITabBarItem *)barItem{
    int total = [[self class] fetchUnreadAmount];
    if (total > 0 && barItem.tag == InteractItemTag) {
        if (total > 99) {
            barItem.badgeValue = @"99+";
        }else{
            barItem.badgeValue = [NSString stringWithFormat:@"%d",total];
        }
    }else{
        barItem.badgeValue = nil;
    }
}

+ (void)updateUserCacheWithIcon:(NSString *)icon{
        
    CMUserItem *ownerUser = (CMUserItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMUserItem class]) withPredicate:Pre_UserJid(kXMPPJid)];
    
    if (ownerUser && ![ownerUser.icon isEqualToString:icon]) {
        ownerUser.icon = icon;
        
        XMPPChatStorage.currUser = ownerUser;
        
    }
    
    CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForJid:kXMPPJid];
    if (dialogueItem) {
        
        dialogueItem.icon = icon;
    }
    
    [MessageObjectContext save:NULL];
}

+ (BOOL)existSystemMessageWithRoomJid:(NSString *)roomJid type:(CMInteractSystemMessageType)type{

    //设定以时间排序
    NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:NO];
    
    //过滤数据
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"(fromJID == %@ ) AND (type == %d )  AND (SELF.sysmessage.roomJID == %@ ) AND (SELF.sysmessage.skip == 0) AND (SELF.sysmessage.state == 0)",kXMPPManager,type,roomJid];
    
    return [self existManagedObject:NSStringFromClass([CMMessageItem class]) withPredicate:predicate sortDescriptor:sortDescriptor];
}

+ (void)saveGroupMembersWithTContactsItem:(TContactsItem)item roomID:(NSString *)roomID{

    NSError *error = NULL;

    CMMemberItem *memberItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMMemberItem" inManagedObjectContext:MessageObjectContext];
    memberItem.roomID = roomID;
    memberItem.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
    memberItem.uid = [NSString stringWithUTF8String:item.sID.c_str()];
    memberItem.jid= [NSString stringWithUTF8String:item.sJid.c_str()];
    memberItem.name = [NSString stringWithUTF8String:item.sName.c_str()];
    memberItem.type = [NSNumber numberWithInt:item.nIsManager];

    [MessageObjectContext save:&error];
    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
    }
}
@end
