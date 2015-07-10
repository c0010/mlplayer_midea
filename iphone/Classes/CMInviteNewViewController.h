//
//  CMInviteNewViewController.h
//  MLPlayer
//
//  Created by kyp on 14-6-18.
//  Copyright (c) 2014年 w. All rights reserved.
//
//  邀请新成员

#import "CMViewController.h"
#import "cmcontacts.h"
#import "tool.h"
#import "SDWebImage/UIImageView+WebCache.h"

#import "SDWebImage/SDWebImageDownloader.h"
#import "cmgroup.h"
#import "SDWebImage/SDWebImageManager.h"
#import "CMSearchBar.h"


@interface CMInviteNewViewController : CMViewController <UITableViewDelegate,UITableViewDataSource,UISearchBarDelegate, NSFetchedResultsControllerDelegate>
{
    UISearchDisplayController *searchDisplayController;

	CMContacts *m_pContacts;

    TGroupInfoItem* m_pGroupInfoItem;

    UIView* bgview;     //无数据logo

    
    NSMutableArray* mergeredRecentContacts ;//最近联系人，已与群成员合并
}

@property (strong,nonatomic) UITableView *tableView;
@property (strong,nonatomic) CMSearchBar *searchBar;
@property (assign,nonatomic) BOOL isChecked;
@property(nonatomic,strong) UIView* bottomView;
@property(nonatomic,strong) NSMutableArray* selectedArray;//已选择
@property(nonatomic,strong) NSMutableArray* searchResults;//搜索通讯录
@property(nonatomic,strong) NSMutableArray* occupantsList;//我的群组列表

@property(nonatomic,strong) UITableView* bottomTableView;

@property(nonatomic,strong) UIButton * commitBtn;

-(void)setItem:(TGroupInfoItem&)item;

@end

