//
//  CMSearchBar.h
//  MLPlayer
//
//  Created by water on 14-9-15.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CMSearchBar : UISearchBar

@end

@protocol CMSearchDisplayDelegate <NSObject>

- (void) CMSearchDisplayControllerWillBeginSearch:(UISearchDisplayController *)controller;
- (void) CMSearchDisplayControllerWillEndSearch:(UISearchDisplayController *)controller;

@end

@protocol CMSearchDisplayDelegate;

@interface CMSearchDisplayController : UISearchDisplayController<UISearchDisplayDelegate>

@property (nonatomic, strong) NSObject<CMSearchDisplayDelegate> *cmDelegate;

@property (nonatomic, strong) UINavigationController *navigationController;

@end