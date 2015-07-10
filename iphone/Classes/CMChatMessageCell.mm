//
//  CMChatMessageCell.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-9.
//  Copyright (c) 2014年 w. All rights reserved.
//



#import "CMChatMessageCell.h"
#import "tool.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "CMMyInfo.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "NSDate+Helper.h"
#import "CMMsgManager.h"
#import "SDWebImage/SDImageCache.h"
#import "CMMsgBlock.h"

#define SHARECOURSE_HEIGHT_MAX 100


@implementation CMChatMessageCell
@synthesize pressedState;
@synthesize cellDelegate;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier withItem:(CMBaseItem *)item
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];

    if (self) {

        //初始化消息体
        self.messageBtn = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, 10, 10)];
        self.messageBtn.backgroundColor = [UIColor clearColor];
        //设置背景
        UIImage* image = NULL;
        UIImage* selimage = NULL;
        
        if (MBlock.isFromMe(item)) {
            
            image = [UIImage imageNamed:@"myMessageBtn_nor"];
            image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 5 ,5, 10)];
            
            selimage = [UIImage imageNamed:@"myMessageBtn_sel"];
            selimage = [selimage resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 5 ,5, 10)];
            
            switch ([MBlock.sent(item) integerValue]) {
                case CMSendMessageStateFailure:
                {
                    self.afreshButton = [[CMButton alloc]initWithFrame:CGRectMake(0, 0, 20, 20)];
                    [self.afreshButton setBackgroundImage:[UIImage imageNamed:@"interact_send_again_btn"] forState:UIControlStateNormal];
                    [self.contentView  addSubview:self.afreshButton];
                }
                    break;
                case CMSendMessageStateSending:
                {
                    self.indicatorView = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
                    [self.indicatorView startAnimating];
                    self.indicatorView.hidesWhenStopped = YES;
                    [self.contentView  addSubview:self.indicatorView];
                }
                    break;
                default:
                    break;
            }
        }else{
            
            image = [UIImage imageNamed:@"my_img_message_bg_n"];
            image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 10 ,5, 5)];
            
            selimage = [UIImage imageNamed:@"my_img_message_bg_p"];
            selimage = [selimage resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 10 ,5, 5)];
            
            if (MBlock.isGroup(item)) {
                self.groupTitleLabel = [[UILabel alloc]init];
                self.groupTitleLabel .backgroundColor = [UIColor clearColor];
                self.groupTitleLabel .textColor = [UIColor darkGrayColor];
                self.groupTitleLabel .font = [UIFont systemFontOfSize:12.f];
                [self.contentView addSubview:self.groupTitleLabel];
            }
        }

        [self.messageBtn setBackgroundImage:image forState:UIControlStateNormal];
        [self.messageBtn setBackgroundImage:selimage forState:UIControlStateHighlighted];
        [self.contentView  addSubview:self.messageBtn];
        
        UILongPressGestureRecognizer *longGesture =[[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(longGestureRecognizerPressed:)];
        longGesture.minimumPressDuration = 2;
        
        UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapGestureRecognizerPressed:)];
        tapGesture.numberOfTapsRequired = 1;
        
        [self.messageBtn addGestureRecognizer:longGesture];
        [self.messageBtn addGestureRecognizer:tapGesture];

        if (MBlock.type(item) == CMMessageCourseType || MBlock.type(item) == CMMessageQAType) {
            //分享课件消息
            self.shareView = [[UIView alloc]initWithFrame:CGRectMake(10, 10, 195, SHARECOURSE_HEIGHT_MAX - 20)];
            self.shareView.backgroundColor = [UIColor clearColor];
            self.shareView.userInteractionEnabled = YES;
            
            self.titleLabel = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, 195, 15)];
            self.titleLabel .backgroundColor = [UIColor clearColor];
            self.titleLabel .textColor = [UIColor blackColor];
            self.titleLabel .font = [UIFont systemFontOfSize:14.f];
            self.titleLabel.userInteractionEnabled = YES;

            self.imageview = [[UIImageView alloc]initWithFrame:CGRectMake(0, 20, 60, 60)];
            self.imageview.backgroundColor = [UIColor clearColor];
            self.imageview.userInteractionEnabled = YES;

            self.descLabel = [[UILabel alloc]initWithFrame:CGRectMake(65, 20, 130, 60)];
            self.descLabel.backgroundColor = [UIColor clearColor];
            self.descLabel.textColor = [UIColor darkGrayColor];
            self.descLabel.font = [UIFont systemFontOfSize:12.f];
            self.descLabel.numberOfLines = 0;
            self.descLabel.lineBreakMode = NSLineBreakByWordWrapping|NSLineBreakByTruncatingTail;
            self.descLabel.userInteractionEnabled = YES;

            [self.shareView addSubview:self.titleLabel];
            [self.shareView addSubview:self.descLabel];
            [self.shareView addSubview:self.imageview];
            [self.messageBtn addSubview:self.shareView];
        }else if(MBlock.type(item) == CMMessageImageType){
            //分享图片消息
            self.pImageView = [[UIImageView alloc]init];
            self.pImageView.backgroundColor = [UIColor clearColor];
            self.pImageView.userInteractionEnabled = YES;
            self.pImageView.layer.masksToBounds = YES;
            self.pImageView.contentMode = UIViewContentModeScaleAspectFill;
            self.pImageView.clipsToBounds = YES;
            self.pImageView.layer.cornerRadius =3.0f;
            self.pImageView.image = Send_DefaultImage;
            if ([MBlock.sent(item) integerValue] == CMSendMessageStateSending) {
                self.shadowView = [[UIImageView alloc]init];
                self.shadowView.backgroundColor = [UIColor colorWithWhite:0.1 alpha:0.6];
                self.shadowView.userInteractionEnabled = YES;
                [self.pImageView addSubview:self.shadowView];
            }
            [self.messageBtn addSubview:self.pImageView];
        }else{
            //分享普通文字消息
            self.messageLbl = [[MessageView alloc]init];
            self.messageLbl.userInteractionEnabled = YES;
            [self.messageLbl setBackgroundColor:[UIColor clearColor]];
            if (MBlock.isFromMe(item))
            {
               [self.messageLbl setTextColor:[UIColor blackColor]];
            }else{
                [self.messageLbl setTextColor:[UIColor blackColor]];
            }
            [self.messageBtn addSubview:self.messageLbl];
        }

        //初始化头像
        self.iconImgView = [UIButton buttonWithType:UIButtonTypeCustom];
        self.iconImgView.layer.cornerRadius =2.f;
        self.iconImgView.layer.masksToBounds = YES;
        [self.iconImgView setImage:Icon_Image forState:UIControlStateNormal];
        [self.iconImgView addTarget:self action:@selector(iconButtonPreesd:) forControlEvents:UIControlEventTouchUpInside];
        [self.contentView addSubview:self.iconImgView];
        
        self.timeLabel = [[UIButton alloc]initWithFrame:CGRectMake(0, 15, 100, 20)];
        self.timeLabel.userInteractionEnabled = NO;
        [self.timeLabel setTitleColor:UIColorRGB(0x333333) forState:UIControlStateNormal];
        self.timeLabel.titleLabel.font = [UIFont systemFontOfSize:10.f];
        self.timeLabel.backgroundColor = [UIColor clearColor];
        
        UIImage *tImage = [[UIImage imageNamed:@"interact_time_bg"] resizableImageWithCapInsets:UIEdgeInsetsMake(5, 15, 5, 15)];
        [self.timeLabel setBackgroundImage:tImage forState:UIControlStateNormal];
        self.timeLabel.hidden = YES;
        
        [self.contentView  addSubview:self.timeLabel];

    }
    return self;
}

- (void) iconButtonPreesd:(UIButton *)sender{
    if ([self.cellDelegate respondsToSelector:@selector(CMChatMessageCell:didSelectedIconAtIndex:)]) {
        [self.cellDelegate CMChatMessageCell:self didSelectedIconAtIndex:sender.tag];
    }
}

- (void)longGestureRecognizerPressed:(UILongPressGestureRecognizer *)gestureRecognizer{
    if(gestureRecognizer.state  == UIGestureRecognizerStateBegan){
        self.pressedState = CMChatMessageCellPressedStateLong;
        if ([self.cellDelegate respondsToSelector:@selector(CMChatMessageCell:didSelectedAtIndex:)]) {
            [self.cellDelegate CMChatMessageCell:self didSelectedAtIndex:gestureRecognizer.view.tag];
        }
    }
}

- (void)singleTapGestureRecognizerPressed:(UITapGestureRecognizer *)gestureRecognizer{
    self.pressedState = CMChatMessageCellPressedStateSingleTap;
    if ([self.cellDelegate respondsToSelector:@selector(CMChatMessageCell:didSelectedAtIndex:)]) {
        [self.cellDelegate CMChatMessageCell:self didSelectedAtIndex:gestureRecognizer.view.tag];
    }
}

- (enum CMChatMessageCellPressedState) singleTap{
    
    return CMChatMessageCellPressedStateSingleTap;
}

- (void)awakeFromNib
{
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

-(void)setMessageItem:(CMBaseItem *)messageItem
{

    if (MBlock.isShowSendTime(messageItem)) {
        self.timeLabel.hidden = NO;
        NSString *timeStr = [NSDate stringForDisplayFromDate:MBlock.sendTime(messageItem) prefixed:NO alwaysDisplayTime:YES];
        [self.timeLabel setTitle:timeStr forState:UIControlStateNormal];
        
        CGSize size = [timeStr sizeWithFont:self.timeLabel.titleLabel.font constrainedToSize:CGSizeMake(150,15)];

        [self.timeLabel setFrameWidth:size.width + 16];
        [self.timeLabel setCenterX:UI_IOS_WINDOW_WIDTH/2];
        
    }else{
        self.timeLabel.hidden = YES;
    }
    
    CGFloat timeViewHeight = 0.f;
    if (!self.timeLabel.hidden) {
        timeViewHeight = TimeView_Height;
    }
    
    if(MBlock.isFromMe(messageItem))
    {
        //修改分享信息字体颜色
        //self.titleLabel.textColor = [UIColor whiteColor];
        //self.descLabel.textColor = [UIColor whiteColor];
        
        if (MBlock.type(messageItem) == CMMessageCourseType) {
            self.titleLabel.text = MBlock.coursemessage(messageItem).title;
            self.descLabel.text = MBlock.coursemessage(messageItem).desc;
            [self.imageview sd_setImageWithURL:[NSURL URLWithString:MBlock.coursemessage(messageItem).icon] placeholderImage:Course_Image];
            
            CGSize maxSize = CGSizeMake(130, 60);
            CGSize descSize = [self.descLabel.text sizeWithFont:self.descLabel.font constrainedToSize:maxSize lineBreakMode:NSLineBreakByWordWrapping];
            self.descLabel.frame = CGRectMake(65, 20, descSize.width, descSize.height);
            [self.messageBtn setFrame:CGRectMake(50,15 + timeViewHeight, 215,  SHARECOURSE_HEIGHT_MAX)];
        }else if (MBlock.type(messageItem) == CMMessageQAType) {            
            self.titleLabel.text = [NSString stringWithFormat:@"%@的问题",MBlock.qamessage(messageItem).name];
            self.descLabel.text = MBlock.qamessage(messageItem).question;
//            [self.imageview setImageWithURL:[NSURL URLWithString:MBlock.qamessage(messageItem).image] placeholderImage:Course_Image];
            [self.imageview setImage:[UIImage imageNamed:@"qashare"]];
            
            CGSize maxSize = CGSizeMake(130, 60);
            CGSize descSize = [self.descLabel.text sizeWithFont:self.descLabel.font constrainedToSize:maxSize lineBreakMode:NSLineBreakByWordWrapping];
            self.descLabel.frame = CGRectMake(65, 20, descSize.width, descSize.height);
            [self.messageBtn setFrame:CGRectMake(50,15 + timeViewHeight, 215,  SHARECOURSE_HEIGHT_MAX)];
        }else if(MBlock.type(messageItem) == CMMessageImageType){
            if (![self hasCache:messageItem]) {
                self.pImageView.image = [UIImage imageWithContentsOfFile:MBlock.content(messageItem)];
            }
            [[CMMsgManager manager]  setImageView:self.pImageView withUrl:MBlock.imagemessage(messageItem).thumb_url withErrorImage:Send_ErrorImage];
            if ( [MBlock.imagemessage(messageItem).isVertical boolValue] ) {
                [self.pImageView setFrame:CGRectMake(2, 2, PICTURE_VER_HEIGHT + 20 - 6, PICTURE_VER_WIDTH -20)];
                [self.messageBtn setFrame:CGRectMake(151,15 + timeViewHeight, PICTURE_VER_HEIGHT + 20 + 4,  PICTURE_VER_WIDTH - 20 + 4)];
            }else{
                [self.pImageView setFrame:CGRectMake(2, 2, PICTURE_VER_WIDTH - 6, PICTURE_VER_HEIGHT)];
                [self.messageBtn setFrame:CGRectMake(111,15 + timeViewHeight, PICTURE_VER_WIDTH +4,  PICTURE_VER_HEIGHT + 4)];
            }
        }else{
            self.messageLbl.text = MBlock.content(messageItem);
            self.bubbleSize = [self.messageLbl getContentSizeWithMessage:MBlock.content(messageItem)];
            
            [self.messageBtn setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-(self.bubbleSize.width+10+20+kIconSize),15 + timeViewHeight, self.bubbleSize.width+15, self.bubbleSize.height+10)];
            [self.messageLbl setFrame:CGRectMake(5, 5, self.bubbleSize.width, self.bubbleSize.height)];
        }
        [self.iconImgView setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-(kIconSize+10), 15 + timeViewHeight, kIconSize, kIconSize)];
        
        if (self.indicatorView) {
            [self.indicatorView setCenter:CGPointMake(CGRectGetMinX(self.messageBtn.frame) - 20,self.messageBtn.center.y)];
            
            if ([MBlock.sent(messageItem) integerValue] == CMSendMessageStateSending) {
                self.indicatorView.hidden = NO;
            }else{
                self.indicatorView.hidden = YES;
            }
        }
        
        if (self.afreshButton) {
            [self.afreshButton setCenter:CGPointMake(CGRectGetMinX(self.messageBtn.frame) - 20,self.messageBtn.center.y)];
            
            if ([MBlock.sent(messageItem) integerValue]== CMSendMessageStateFailure) {
                self.afreshButton.hidden = NO;
            }else{
                self.afreshButton.hidden = YES;
            }
        }
        
        if (self.shadowView) {
            if ([MBlock.sent(messageItem) integerValue]== CMSendMessageStateSuccess) {
                self.shadowView.hidden = YES;
            }else{
                self.shadowView.hidden = NO;
                [self.shadowView setFrame:self.pImageView.bounds];
            }
        }
    }
    else
    {
        //self.titleLabel.textColor = [UIColor blackColor];
        //self.descLabel.textColor = [UIColor darkGrayColor];
        
        if (MBlock.type(messageItem) == CMMessageCourseType) {
            self.titleLabel.text = MBlock.coursemessage(messageItem).title;
            self.descLabel.text = MBlock.coursemessage(messageItem).desc;
            [self.imageview sd_setImageWithURL:[NSURL URLWithString:MBlock.coursemessage(messageItem).icon] placeholderImage:Course_Image];
            
            CGSize maxSize = CGSizeMake(130, 60);
            CGSize descSize = [self.descLabel.text sizeWithFont:self.descLabel.font constrainedToSize:maxSize lineBreakMode:NSLineBreakByWordWrapping];
            self.descLabel.frame = CGRectMake(65, 20, descSize.width, descSize.height);
            [self.messageBtn setFrame:CGRectMake( kIconSize + 15, 15 + timeViewHeight,215, SHARECOURSE_HEIGHT_MAX)];
            
            CGRect sRect = self.shareView.frame;
            sRect.origin.x = 15;
            self.shareView.frame = sRect;
        }else if (MBlock.type(messageItem) == CMMessageQAType) {
            self.titleLabel.text = [NSString stringWithFormat:@"%@的问题",MBlock.qamessage(messageItem).name];
            self.descLabel.text = MBlock.qamessage(messageItem).question;
//            [self.imageview setImageWithURL:[NSURL URLWithString:MBlock.qamessage(messageItem).image] placeholderImage:Course_Image];
            [self.imageview setImage:[UIImage imageNamed:@"qashare"]];
            
            CGSize maxSize = CGSizeMake(130, 60);
            CGSize descSize = [self.descLabel.text sizeWithFont:self.descLabel.font constrainedToSize:maxSize lineBreakMode:NSLineBreakByWordWrapping];
            self.descLabel.frame = CGRectMake(65, 20, descSize.width, descSize.height);
            [self.messageBtn setFrame:CGRectMake(50,15 + timeViewHeight, 215,  SHARECOURSE_HEIGHT_MAX)];
        }else if(MBlock.type(messageItem) == CMMessageImageType){
            
            [[CMMsgManager manager]  setImageView:self.pImageView withUrl:MBlock.imagemessage(messageItem).thumb_url withErrorImage:Send_ErrorImage];
            if ([MBlock.imagemessage(messageItem).isVertical boolValue]) {
                [self.pImageView setFrame:CGRectMake(8, 2, PICTURE_VER_HEIGHT + 20 - 6, PICTURE_VER_WIDTH - 20)];
                [self.messageBtn setFrame:CGRectMake( kIconSize + 15, 15 + timeViewHeight,PICTURE_VER_HEIGHT + 20 + 4,  PICTURE_VER_WIDTH - 20 + 4)];
            }else{
                [self.pImageView setFrame:CGRectMake(8, 2, PICTURE_VER_WIDTH - 6, PICTURE_VER_HEIGHT)];
                [self.messageBtn setFrame:CGRectMake( kIconSize + 15, 15 + timeViewHeight,PICTURE_VER_WIDTH + 4,  PICTURE_VER_HEIGHT + 4)];
            }
        }else{
            self.messageLbl.text = MBlock.content(messageItem);
            self.bubbleSize = [self.messageLbl getContentSizeWithMessage:MBlock.content(messageItem)];
            
            [self.messageBtn setFrame:CGRectMake( kIconSize + 15, 15 + timeViewHeight,self.bubbleSize.width+15, self.bubbleSize.height+10)];
            [self.messageLbl setFrame:CGRectMake(10, 5, self.bubbleSize.width, self.bubbleSize.height)];
        }
        [self.iconImgView setFrame:CGRectMake(10, 15 + timeViewHeight, kIconSize, kIconSize)];
        
        if (MBlock.isGroup(messageItem)) {
            CGRect btnFrame = self.messageBtn.frame;
            btnFrame.origin.y = 15 + timeViewHeight + GROUP_TITLE_HEIGHT;
            self.messageBtn.frame = btnFrame;
            
            self.groupTitleLabel.frame =CGRectMake(CGRectGetMinX(self.messageBtn.frame), 10 + timeViewHeight, 200, GROUP_TITLE_HEIGHT);
            self.groupTitleLabel.text = [NSString stringWithFormat:@"%@:",MBlock.fromName(messageItem)];
        }
    }
}

- (CGFloat)getCellHeight:(CMBaseItem*)item
{
    CGFloat cellHeight=0.0;
    CGFloat timeViewHeight=0.0;
    if (!self.timeLabel.hidden) {
        timeViewHeight = TimeView_Height;
    }
    cellHeight = timeViewHeight + cellHeight + 40;
    
    if (MBlock.type(item) == CMMessageCourseType)
    {
         cellHeight = cellHeight +SHARECOURSE_HEIGHT_MAX;
    }else if (MBlock.type(item) == CMMessageQAType)
    {
        cellHeight = cellHeight +SHARECOURSE_HEIGHT_MAX;
    }else if(MBlock.type(item) == CMMessageImageType)
    {
        if ([MBlock.imagemessage(item).isVertical boolValue]) {
            cellHeight = cellHeight + PICTURE_VER_WIDTH - 30 + 4;
        }else{
            cellHeight = cellHeight + PICTURE_VER_HEIGHT -10 + 4;
        }
    }else
    {
        CGSize size = [self.messageLbl getContentSizeWithMessage:MBlock.content(item)];
        cellHeight = cellHeight + size.height;
    }
    
    if (MBlock.isGroup(item) && (!MBlock.isFromMe(item))) {
        cellHeight = cellHeight + GROUP_TITLE_HEIGHT;
    }
    
    return cellHeight;
}

//是否存在缓存
- (BOOL)hasCache:(CMBaseItem *)baseItem{
    NSString *url = MBlock.imagemessage(baseItem).thumb_url;
    if (!url) {
        return NO;
    }else{
        UIImage *image = [[SDImageCache sharedImageCache] imageFromDiskCacheForKey:url];
        if (!image) {
            return NO;
        }
    }
    return YES;
}

-(void)drawRect:(CGRect)rect{

    [super drawRect:rect];
}

@end
