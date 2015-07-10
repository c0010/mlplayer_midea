//
//  UINavigationController+Customer.m
//  MLPlayer
//
//  Created by hushengwu on 14-9-9.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "UINavigationController+Customer.h"

@implementation UINavigationController (Customer)

-(void)viewDidLoad
{
    [super viewDidLoad];
    //自定义navigationBar
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    
    UIImage *NaviBgImage = [self imageWithColor:UIColorRGB(0xF9F9F9)];
    
    if (version >= 5.0)
    {
        if (version >= 7.0)
        {
            [self.navigationBar setBackgroundImage:NaviBgImage forBarPosition:UIBarPositionTopAttached barMetrics:UIBarMetricsDefault];
        }
        else
        {
            [self.navigationBar setBackgroundImage:NaviBgImage forBarMetrics:UIBarMetricsDefault];
        }
        //self.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"NaviBg"]];
        
    }else{
        
        self.navigationBar.layer.contents=(id)NaviBgImage.CGImage;
    }
}


- (UIImage*) imageWithColor: (UIColor*) color

{
    CGRect rect=CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage*theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_6_0

-(BOOL)shouldAutorotate
{
    return self.topViewController.shouldAutorotate;
}

-(NSUInteger)supportedInterfaceOrientations
{
    return self.topViewController.supportedInterfaceOrientations;
}

#endif

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // You do not need this method if you are not supporting earlier iOS Versions
    return [self.topViewController  shouldAutorotateToInterfaceOrientation:interfaceOrientation];
}



@end
