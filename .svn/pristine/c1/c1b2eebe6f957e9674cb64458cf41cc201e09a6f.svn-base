//
//  CMSysMessageDetailyViewController.h
//  MLPlayer
//
//  Created by water on 14-6-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"

#define kSysMessageDetailyCell @"com.ulp.CMSysMessageDetaily"

typedef void(^ButtonListener)(UIButton *sender);

@interface CMSysMessageDetailyViewController : CMViewController<UITableViewDataSource,UITableViewDelegate>
{
    UITableView *theTableView;
}

@property (nonatomic, strong) UITableView *theTableView;
@property (nonatomic, strong) CMMessageItem *currMessageItem;
@property (nonatomic, strong) ButtonListener buttonListener;
@end
