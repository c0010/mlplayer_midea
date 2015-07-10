//
//  CMGroupChatMsgCellTableViewCell.m
//  MLPlayer
//
//  Created by kyp on 14-6-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupChatMsgCellTableViewCell.h"
#import "tool.h"
@implementation CMGroupChatMsgCellTableViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
        //初始化消息体
        //初始化消息体
        self.messageBtn = [[UIButton alloc]init];
        
        //设置背景
        UIImage* image = NULL;
        UIImage* selimage = NULL;
        if([reuseIdentifier isEqualToString:kMyMessageCell])
        {
            image = [UIImage imageNamed:@"myMessageBtn_nor"];
            image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 25 ,10, 15)];
            
            selimage = [UIImage imageNamed:@"myMessageBtn_sel"];
            selimage = [selimage resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 25 ,10, 15)];
        }
        else
        {
            image = [UIImage imageNamed:@"messageBtn_sel"];
            image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 20 ,10, 15)];
            
            selimage = [UIImage imageNamed:@"messageBtn_sel"];
            selimage = [selimage resizableImageWithCapInsets:UIEdgeInsetsMake(25 , 20 ,10, 15)];
        }
        
        [self.messageBtn setBackgroundImage:image forState:UIControlStateNormal];
        [self.messageBtn setBackgroundImage:selimage forState:UIControlStateHighlighted];
        [self addSubview:self.messageBtn];
        
        //加上文字
        self.messageLbl = [[MessageView alloc]init];
        self.messageLbl.userInteractionEnabled = YES;
        [self.messageLbl setBackgroundColor:[UIColor clearColor]];
        [self.messageBtn addSubview:self.messageLbl];
        
        //初始化头像
        self.iconImgView = [[UIImageView alloc]init];
        [self addSubview:self.iconImgView];
        
        self.timeBackView = [[UIView alloc]initWithFrame:CGRectMake(85, 15, 150, 20)];
        self.timeBackView.backgroundColor = [UIColor colorWithWhite:0.85 alpha:1.0];
        self.timeBackView.layer.masksToBounds = YES;
        self.timeBackView.layer.cornerRadius =10.0f;
        self.timeBackView.hidden = YES;
        
        self.timeLabel = [[UILabel alloc]initWithFrame:self.timeBackView.bounds];
        self.timeLabel .textColor = [UIColor blackColor];
        self.timeLabel .font = [UIFont systemFontOfSize:13.f];
        self.timeLabel.textAlignment = UITextAlignmentCenter;
        self.timeLabel.backgroundColor = [UIColor clearColor];
        
        [self.timeBackView addSubview:self.timeLabel];
        [self addSubview:self.timeBackView];
        
        self.nameLabel=[[CMLabel alloc]init];
        [self addSubview:self.nameLabel];
        
        
        
    }
    return self;
}

- (void)awakeFromNib
{
    // Initialization code
}


-(void)setMessageItem:(CMGroupMessageItem *)messageItem
{
    _messageItem = messageItem;
    
    
    [self.iconImgView setImage:[UIImage imageNamed:@"user_image"]];
    
    self.bubbleSize = [_messageItem.content sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(200, MAXFLOAT) ];
    
    self.messageLbl.text = _messageItem.content;
    
    //self.nameLabel.text=_messageItem.nickname;
    CGFloat timeViewHeight = self.timeBackView.hidden ? 0 : TimeView_Height;
    if(messageItem.isFromMe)
    {
        [self.messageBtn setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-(self.bubbleSize.width+10+20+kIconSize), 20+ timeViewHeight, self.bubbleSize.width+15, self.bubbleSize.height+15)];
        [self.messageLbl setFrame:CGRectMake(3, 5, self.bubbleSize.width, self.bubbleSize.height+5)];
        [self.iconImgView setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-(kIconSize+10), 5, kIconSize, kIconSize)];
        
        [self.nameLabel setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-(kIconSize+10)-60, 2, 60, 20)];
        
        self.nameLabel.text=messageItem.fromName;
        
    }
    else
    {
        [self.messageBtn setFrame:CGRectMake( kIconSize+20, 20+ timeViewHeight,self.bubbleSize.width+15, self.bubbleSize.height+15)];
        [self.messageLbl setFrame:CGRectMake(8, 5, self.bubbleSize.width, self.bubbleSize.height+5)];
        
        [self.iconImgView setFrame:CGRectMake(10, 5, kIconSize, kIconSize)];
        
        [self.nameLabel setFrame:CGRectMake(kIconSize+20, 2, 60, 20)];
        self.nameLabel.text=messageItem.fromName;
    }
    
}


-(CGFloat)getCellHeight:(CMGroupMessageItem*)item
{

    
    
    CGSize size = [self.messageLbl getContentSizeWithMessage:_messageItem.content];
    CGFloat timeViewHeight = self.timeBackView.hidden ? 0 : TimeView_Height;
    
    return (size.height+45 + timeViewHeight)+5;

}



-(void)drawRect:(CGRect)rect{
    
    [super drawRect:rect];
    
    
    
}


- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
