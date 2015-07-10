//
//  CMGroupManagementViewController.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmcontacts.h"
#import "cmgroup.h"
#import "tool.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "CMSearchBar.h"


enum CMGroupMemberEditType{
    CMGroupMemberEditTypeUnkown = 0,
    CMGroupMemberEditTypeInvite = 1,
    CMGroupMemberEditTypeManager = 2,
    CMGroupMemberEditTypeRemove = 3,
    CMGroupMemberEditTypeTrain = 4,
};

@interface CMGroupManagementViewController :CMViewController<UITableViewDelegate,UITableViewDataSource,UISearchBarDelegate>{

    TGroupInfoItem* m_pGroupInfoItem;

    
}
@property (strong,nonatomic) CMSearchBar *searchBar;

@property (strong,nonatomic) NSString *trainID;

@property(nonatomic,strong) UITableView* occupantTableView;
@property(strong,nonatomic) UIButton *commitBtn;
@property(strong,nonatomic) NSMutableArray *members,*originalMembers;

@property(nonatomic,assign) enum CMGroupMemberEditType editType;//界面显示类型：1.邀请加入群 2.设为管理员  3.踢人 4.取消管理员

-(void)setItem:(TGroupInfoItem&)item;

@end


