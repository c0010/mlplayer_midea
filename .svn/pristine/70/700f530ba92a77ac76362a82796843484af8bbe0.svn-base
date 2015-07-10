//
//  UITabBarController+Rotation.m
//  MLPlayer
//
//  Created by hushengwu on 14-9-9.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "UITabBarController+Rotation.h"

@implementation UITabBarController (Rotation)

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // You do not need this method if you are not supporting earlier iOS Versions
    return [self.selectedViewController shouldAutorotateToInterfaceOrientation:interfaceOrientation];
}

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_6_0

-(NSUInteger)supportedInterfaceOrientations
{
    return [self.selectedViewController supportedInterfaceOrientations];
}

-(BOOL)shouldAutorotate
{
    return self.selectedViewController.shouldAutorotate;
}
#endif

@end
