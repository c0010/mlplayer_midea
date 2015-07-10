//
//  CMSearchBar.m
//  MLPlayer
//
//  Created by water on 14-9-15.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMSearchBar.h"
#import "tool.h"

@implementation CMSearchBar

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        self.placeholder = I(@"搜索");
        self.barStyle = UIBarStyleDefault;
        self.backgroundColor = [UIColor clearColor];
        if ([self respondsToSelector:@selector(setBarTintColor:)]) {
            [self setBarTintColor:UIColorMakeRGBA(223.0f, 46.0f, 227.0f, 0.8f)];
        }
        [self sizeToFit];

        if (__iOS7) {
            UIView *backview = self.subviews[0];
            
            UIView *back = [[UIView alloc]initWithFrame:backview.bounds];
            back.backgroundColor = UIColorRGB(0xdfe2e3);
            [backview insertSubview:back atIndex:0];

            for (UIView *subview in backview.subviews) {
                if ([subview isKindOfClass:NSClassFromString(@"UISearchBarBackground")])
                {
                    [subview removeFromSuperview];

                    break;
                }
            }
        }else{
//            [self logViewTree];

            UIView *back = [[UIView alloc]initWithFrame:CGRectMake(-1, 0, 322, 44)];
            back.backgroundColor = UIColorRGB(0xdfe2e3);
            [self insertSubview:back atIndex:0];
            
            for (UIView *subview in self.subviews) {
                if ([subview isKindOfClass:NSClassFromString(@"UISearchBarBackground")])
                {
                    [subview removeFromSuperview];
                    break;
                }
            }
        }

    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end

@implementation CMSearchDisplayController

- (id)initWithSearchBar:(UISearchBar *)searchBar contentsController:(UIViewController *)viewController{
    self = [super initWithSearchBar:searchBar contentsController:viewController];
    if (self) {
        self.delegate = self;
        self.searchResultsTableView.backgroundColor = kColorBackground;
        self.searchResultsTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        
        @try
        {
            //设置默认无结果
            [self setValue:I(@"暂无数据") forKey:[@[@"no", @"Results", @"Message"] componentsJoinedByString:@""]];
        }
        @catch (NSException *exception) {}
    }
    return self;
}

- (void)searchDisplayControllerWillBeginSearch:(UISearchDisplayController *)controller {
    if (__iOS7) {
        UIView *backview = self.searchBar.subviews[0];
        
        for (UIView *subview in backview.subviews) {
            if ([subview isKindOfClass:NSClassFromString(@"UIView")])
            {
                subview.frame = CGRectMake(0, -20, 320, 64);
                break;
            }
        }
        
      //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault];
    }
    
    self.navigationController.navigationBar.translucent = YES;
    if (self.cmDelegate) {
        [self.cmDelegate CMSearchDisplayControllerWillBeginSearch:self];
    }
}

- (void)searchDisplayControllerDidEndSearch:(UISearchDisplayController *)controller {
    if (__iOS7) {
        UIView *backview = self.searchBar.subviews[0];
        
        for (UIView *subview in backview.subviews) {
            if ([subview isKindOfClass:NSClassFromString(@"UIView")])
            {
                subview.frame = CGRectMake(0, 0, 320, 44);
                break;
            }
        }
      //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
    }
    
    self.navigationController.navigationBar.translucent = NO;
    if (self.cmDelegate) {
        [self.cmDelegate CMSearchDisplayControllerWillEndSearch:self];
    }
}
@end
