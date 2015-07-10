//
//  CMChatMessageCell.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-9.
//  Copyright (c) 2014年 w. All rights reserved.
//
#define kMyMessageCell @"com.ulp.mymessagecell"
#define kTalkerMessageCell   @"com.ulp.talkermessagecell"
#define kShareMessageCell   @"com.ulp.sharemessagecell"

#define kIconSize  40
#define TimeView_Height 40
#define GROUP_TITLE_HEIGHT  15 //群聊时对方名字高度

#define Send_DefaultImage  [UIImage imageNamed:@"interact_sendimage_default"] //默认图片
#define Send_ErrorImage  [UIImage imageNamed:@"interact_sendimage_error"] //默认图片

#define Icon_Image  [UIImage imageNamed:@"headbig"] //头像默认图片
#define Course_Image  [UIImage imageNamed:@"ulp"] //课件封面默认图片

#define Horizontal(image) ((image.size.width >= image.size.height) ? YES : NO)//判断图片显示方向

#define PICTURE_VER_HEIGHT  90
#define PICTURE_VER_WIDTH  150
//#define PICTURE_HOR_HEIGHT  15
//#define PICTURE_HOR_WIDTH  15

#import <UIKit/UIKit.h>
#import "cmsettings.h"
#import <CoreData/CoreData.h>
#import "CMInteractModel.h"
#import "MessageView.h"
#import "CMButton.h"


enum CMChatMessageCellPressedState{
    CMChatMessageCellPressedStateSingleTap = 0,
    CMChatMessageCellPressedStateLong = 1,
};

@protocol CMChatMessageCellDelegate;

@interface CMChatMessageCell : UITableViewCell

@property(nonatomic,strong)CMBaseItem* messageItem;
@property(nonatomic,strong)MessageView* messageLbl;
@property(nonatomic,strong)UIButton* messageBtn;
@property(nonatomic,strong)UIButton* iconImgView;
@property(nonatomic,assign)CGSize bubbleSize;
@property(nonatomic,strong)UIButton *timeLabel;

@property (nonatomic,strong) UILabel *titleLabel;
@property (nonatomic,strong) UILabel *descLabel;
@property (nonatomic,strong) UIImageView *imageview;
@property (nonatomic,strong) UIView *shareView;
@property (nonatomic,assign) enum CMChatMessageCellPressedState pressedState;
@property (nonatomic, weak) NSObject<CMChatMessageCellDelegate> *cellDelegate;
@property (nonatomic,strong) UIActivityIndicatorView *indicatorView;
@property (nonatomic,strong) CMButton *afreshButton;//发送失败
@property (nonatomic,strong) UILabel *groupTitleLabel;
@property (nonatomic,strong) UIImageView *pImageView,*shadowView;

@property(nonatomic,strong)NSString* icon;

- (CGFloat)getCellHeight:(CMBaseItem*)item;
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier withItem:(CMBaseItem*)item;

- (enum CMChatMessageCellPressedState) singleTap;
@end

@protocol CMChatMessageCellDelegate <NSObject>

@optional
//点击消息
- (void)CMChatMessageCell:(CMChatMessageCell *)chatMessageCell didSelectedAtIndex:(NSInteger)row;
//点击头像
- (void)CMChatMessageCell:(CMChatMessageCell *)chatMessageCell didSelectedIconAtIndex:(NSInteger)row;

@end