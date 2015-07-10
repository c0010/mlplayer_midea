//
//  CMCoreDataUpdate.m
//  MLPlayer
//
//  Created by water on 14/11/4.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMCoreDataUpdate.h"
#import <version.h>
#import "CMCoreDataUtils.h"

#define Version3_0_2  302

@implementation CMCoreDataUpdate


+ (id)create{
    return [[CMCoreDataUpdate alloc] init];
}

- (id)init
{
    self = [super init];
    if (self) {
        
    
        
    }
    return self;
}

- (void)doUpdate{

    for (int i = 0; i <= MLPAYER_VER; i++) {
        
        switch (i) {
            case Version3_0_2:
            {
            
                NSPredicate *predicate = [NSPredicate predicateWithFormat:@"version == %d", Version3_0_2];

                if ( ![CMCoreDataUtils existManagedObject:NSStringFromClass([CMVersion class]) withPredicate:predicate] ) {
                    
                    NSError *error = NULL;
                    
                    CMVersion *mVersion = [NSEntityDescription insertNewObjectForEntityForName:NSStringFromClass([CMVersion class]) inManagedObjectContext:MessageObjectContext];
                    mVersion.version = [NSNumber numberWithInt:Version3_0_2];
                    
                    [MessageObjectContext save:&error];
                    
                    if (error) {
                        NSLog(@"Error : %@\n", [error localizedDescription]);
                    }
                    
                    
                    //移除所有群组缓存
                    [CMCoreDataUtils clearManagedObjects:NSStringFromClass([CMGroupItem class])];

                }
            }
                break;
                
            default:
                break;
        }
    }
}

@end
