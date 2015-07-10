//
//  XmppManager.m
//  MLPlayer
//
//  Created by water on 14-9-17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "XmppManager.h"
#import "MLPlayerAppDelegate.h"

@implementation XmppManager

- (instancetype)init
{
    self = [super init];
    if (self) {
        MLPlayerAppDelegate* appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
        [appDelegate.xmppHandler.xmppStream addDelegate:self delegateQueue:dispatch_get_main_queue()];
        self.xmppStream = appDelegate.xmppHandler.xmppStream;
    }
    return self;
}

@end
