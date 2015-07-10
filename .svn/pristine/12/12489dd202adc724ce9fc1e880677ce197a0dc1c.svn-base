//
//  XMPPChatMessageCoreDataStorage.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-20.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "XMPPChatMessageCoreDataStorage.h"

@implementation XMPPChatMessageCoreDataStorage

+ (XMPPChatMessageCoreDataStorage*)sharedInstance
{
    static XMPPChatMessageCoreDataStorage *sharedInstance;
    //检查是否运行过
    static dispatch_once_t predicate;

    dispatch_once(&predicate, ^{
        if(sharedInstance == nil)
        sharedInstance = [[XMPPChatMessageCoreDataStorage alloc] init];
    });

    return sharedInstance;

}

- (NSArray *)dialogueWithGroupItems{
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription  entityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];
    
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchLimit:30];
    
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"flag = 1"];
    [fetchRequest setPredicate:predicate];
    
    NSError * error = nil;
    
    NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];
    return array;
}

- (CMDialogueItem*)dialogueItemExistForRoomJid:(NSString*)jid
{

    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription  entityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];

    [fetchRequest setEntity:entity];
    [fetchRequest setFetchLimit:1];

    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"(roomJID = %@) AND (flag = 1)",jid];
    [fetchRequest setPredicate:predicate];

    NSError * error = nil;

    NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];

    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
    }

    if(array && [array count]>0)
    {

        CMDialogueItem * dialogueItem  = [array objectAtIndex:0];
        return dialogueItem;
    }
    else
        return nil;

}

- (CMDialogueItem*)dialogueItemExistForJid:(NSString*)jid
{

    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    NSEntityDescription *entity = [NSEntityDescription entityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];

    [fetchRequest setEntity:entity];
    [fetchRequest setFetchLimit:1];

    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"(fromJID = %@) AND (flag = 0)",jid];
    [fetchRequest setPredicate:predicate];

    NSError * error = nil;

    NSArray *array = [MessageObjectContext executeFetchRequest:fetchRequest error:&error];

    if (error) {
        NSLog(@"Error : %@\n", [error localizedDescription]);
    }

    if(array && [array count]>0)
    {

        CMDialogueItem * dialogueItem  = [array objectAtIndex:0];
        return dialogueItem;
    }
    else
        return nil;

    
}

@end
