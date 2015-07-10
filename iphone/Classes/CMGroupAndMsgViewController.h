//
//  CMGroupAndMsgViewController.h
//  MLPlayer
//
//  Created by kyp on 14-6-17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"

@interface CMGroupAndMsgViewController : CMViewController <UITableViewDataSource,UITableViewDelegate,UISearchBarDelegate>
{
    UITableView *tableView;
    UISegmentedControl *segCtrl;
    UISearchBar *searchBar;
    UISearchDisplayController *searchDisplayController;
    
}

@property(strong,nonatomic) UITableView *tableView;
@property(strong,nonatomic) UISegmentedControl *segCtrl;
@property(strong,nonatomic) UISearchBar *searchBar;
@end
