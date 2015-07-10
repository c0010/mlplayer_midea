//
//  CMGroupChatMsgCellTableViewCell.h
//  MLPlayer
//
//  Created by kyp on 14-6-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#define kMyMessageCell @"com.ulp.mymessagecell"
#define kTalkerMessageCell   @"com.ulp.talkermessagecell"
#define kIconSize  40
#define TimeView_Height 50
#import <UIKit/UIKit.h>
#import "cmsettings.h"
#import <CoreData/CoreData.h>
#import "CMInteractModel.h"
#import "MessageView.h"
#import "CMLabel.h"


@interface CMGroupChatMsgCellTableViewCell : UITableViewCell

@property(nonatomic,strong)CMGroupMessageItem* messageItem;

@property(nonatomic,strong)MessageView* messageLbl;

@property(nonatomic,strong)UIButton* messageBtn;
@property(nonatomic,strong)UIImageView* iconImgView;
@property(nonatomic,assign)CGSize bubbleSize;
@property(nonatomic,strong)UILabel *timeLabel;
@property(nonatomic,strong)UIView *timeBackView;
@property(nonatomic,strong)CMLabel *nameLabel;

- (CGFloat)getCellHeight:(CMGroupMessageItem*)item;



@end
