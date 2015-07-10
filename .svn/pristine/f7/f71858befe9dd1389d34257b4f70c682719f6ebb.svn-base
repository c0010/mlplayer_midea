//
//  CMGroupMembersCell.h
//  MLPlayer
//
//  Created by water on 14-7-10.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMButton.h"

#define CMGroupMembersCellHeight 55

enum CMGroupMembersCellType{
    CMGroupMembersCellTypeMain = 0,//群主 Label右
    CMGroupMembersCellTypeManager = 1,//管理员，Button右
    CMGroupMembersCellTypeMemberDefault = 2,
    CMGroupMembersCellTypeMemberEdit = 3,//移除成员
    CMGroupMembersCellTypeMemberMark = 4,//邀请好友
};

@interface CMGroupMembersCell : UITableViewCell

@property(nonatomic,strong) CMButton *headButton;
@property(nonatomic,strong) CMButton *optionButton;
@property(nonatomic,strong) CMButton *markButton;
@property(nonatomic,strong) UILabel *titlelabel, *accessoryLabel;

@property(nonatomic,assign) enum CMGroupMembersCellType cellType;

@end
