//
//  CMGroupinfoViewController.h
//  MLPlayer
//
//  Created by kyp on 14-6-11.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "cmgroup.h" 
#import "CMGroupManagementViewController.h"
#import "CMInviteNewViewController.h"

@interface CMGroupinfoViewController : CMViewController <UITableViewDataSource,UITableViewDelegate>{
    UITableView* tableView;
    UIButton* btnadd;
    
    TGroupInfoItem m_TGroupInfoItem;
    
}

-(void)loadTableList;

-(void)getItem:(TGroupInfoItem)item;

@property (strong,nonatomic) UITableView* tableView;
@property (strong,nonatomic) UIButton* btnadd;
@end

