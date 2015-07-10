//
//  CMInteractCell.m
//  MLPlayer
//
//  Created by water on 14-7-18.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMInteractCell.h"
#import "tool.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "NSDate+Helper.h"
#import "CMImage.h"

@implementation CMInteractCell
@synthesize badgeValue=_badgeValue;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        
        self.headButton = [CMButton buttonWithType:UIButtonTypeCustom];
        [self.headButton setFrame:CGRectMake(10, 7.5, 50, 50)];
        self.headButton.layer.masksToBounds = YES;
        self.headButton.layer.cornerRadius = 2.0;
        self.headButton.userInteractionEnabled = NO;
        [self addSubview:self.headButton];
        
        self.titleLabel = [[UILabel alloc]initWithFrame:CGRectMake(70, CMInteractCell_Title_Y, 200, 20)];
        self.titleLabel.backgroundColor = [UIColor clearColor];
        self.titleLabel.textColor = UIColorRGB(0x333333);
        self.titleLabel.font = [UIFont systemFontOfSize:15.f];
        [self addSubview:self.titleLabel];
        
        self.DescLabel = [[CMLabel alloc]initWithFrame:CGRectMake(70, 35, 200, 20)];
        self.DescLabel.backgroundColor = [UIColor clearColor];
        self.DescLabel.textColor = [UIColor lightGrayColor];
        self.DescLabel.font = [UIFont systemFontOfSize:13.f];
        [self addSubview:self.DescLabel];
        
        self.badgeView = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, 20, 20)];
        [self.badgeView setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0xff6600)] forState:UIControlStateNormal];
        [self.badgeView setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        self.badgeView.titleLabel.font = [UIFont systemFontOfSize:14.f];
        self.badgeView.layer.masksToBounds = YES;
        [self addSubview:self.badgeView];

        self.timeLabel = [[UILabel alloc]initWithFrame:CGRectMake(270, 10, 40, 15)];
        self.timeLabel.backgroundColor = [UIColor clearColor];
        self.timeLabel.textAlignment = UITextAlignmentRight;
        self.timeLabel.textColor = UIColorRGB(0xc1c1c1);
        self.timeLabel.font = [UIFont systemFontOfSize:11.f];
        [self addSubview:self.timeLabel];
        
        self.phoneLabel = [[UILabel alloc]initWithFrame:CGRectMake(200, CMInteractCell_Title_Y, 110, 15)];
        self.phoneLabel.backgroundColor = [UIColor clearColor];
        self.phoneLabel.textAlignment = UITextAlignmentRight;
        self.phoneLabel.textColor = UIColorRGB(0x333333);
        self.phoneLabel.font = [UIFont systemFontOfSize:13.f];
        [self addSubview:self.phoneLabel];
        
        self.draftImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"interact_lastmsg_draft"]];
        self.draftImgView.frame = CGRectMake(self.DescLabel.frame.origin.x, self.DescLabel.frame.origin.y + 4, 12, 12);
        [self.contentView addSubview:self.draftImgView];
        self.draftImgView.hidden = YES;
        
    }
    return self;
}

- (void)setBadgeValue:(NSInteger)badgeValue{
    if (badgeValue > 0) {
        
        self.badgeView.hidden = NO;

        _badgeValue = badgeValue;
        
        NSString *badgeStr = [NSString stringWithFormat:@"%d",_badgeValue];
        if (_badgeValue > 99) {
            badgeStr = @"99+";
        }
        [self.badgeView setTitle:badgeStr forState:UIControlStateNormal];
        [self.badgeView setTitleEdgeInsets:UIEdgeInsetsMake(0, 2, 0, 0)];
        CGSize size = [badgeStr sizeWithFont:self.badgeView.titleLabel.font constrainedToSize:CGSizeMake(30,18) lineBreakMode:UILineBreakModeWordWrap];
        self.badgeView.frame = CGRectMake(30, 5, size.width + 10, 18);
        self.badgeView.center = CGPointMake(CGRectGetMaxX(self.headButton.frame) - 3, CGRectGetMinY(self.headButton.frame) + 3);
        self.badgeView.layer.cornerRadius = CGRectGetHeight(self.badgeView.frame)/2;

    }else{
        self.badgeView.hidden = YES;
    }
   
}

- (void)bindDialogueItem:(CMDialogueItem *)item{
    
    self.draftImgView.hidden = YES;

    if([item.fromJID isEqualToString:kXMPPManager])
    {
        //保存到系统消息
        self.titleLabel.text = item.fromName;
        [self.headButton setImage:[UIImage imageNamed:@"interact_message_warm.png"] forState:UIControlStateNormal];
        self.DescLabel.text = item.lastMessage;
        [self setDoubleCell];
    }else
    {
        if (item.flag == 1) {
            self.titleLabel.text = item.roomName;
            [self.headButton sd_setImageWithURL:[NSURL URLWithString:item.icon] forState:UIControlStateNormal placeholderImage:DefaultGroupImage];
        }else{
            self.titleLabel.text = item.fromName;
            [self.headButton sd_setImageWithURL:[NSURL URLWithString:item.icon] forState:UIControlStateNormal placeholderImage:DefaultBigHeaderImage];

        }
        
        if ( item.draft && item.draft.length > 0 ) {
            
            self.DescLabel.text = [NSString stringWithFormat:@"     %@" , item.draft];
          //  [self.DescLabel setKeyWordRange:NSMakeRange(0 , 5) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0xff6600)];
            self.draftImgView.hidden = NO;
        }else{
        
            self.DescLabel.text = item.lastMessage;
        }
        
        [self setDoubleCell];
    }
    self.badgeValue = item.unread;
    self.timeLabel.text = [NSDate stringForDisplayFromDate:item.sendTime];
}

- (void) setSingleCell{
    self.DescLabel.hidden = YES;
    [self.titleLabel setFrameY:(CMInteractCellHeight - CGRectGetHeight(self.titleLabel.frame))/2];
}

- (void) setDoubleCell{
    self.DescLabel.hidden = NO;
    [self.titleLabel setFrameY:CMInteractCell_Title_Y];
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
@end
