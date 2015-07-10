//
//  CMAppVCTableViewCell.m
//  MLPlayer
//
//  Created by sunjj on 15/1/8.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMAppVCTableViewCell.h"

@implementation CMAppVCTableViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
        self.LeftImageView = [[UIImageView alloc] initWithFrame:CGRectMake(15, 12, 20, 20)];
//        self.LeftTitle = [[UILabel alloc] initWithFrame:CGRectMake(50, 12, 100, 20)];
        self.LeftTitle = [[UILabel alloc] init];
        [self.contentView addSubview:self.LeftImageView];
        [self.contentView addSubview:self.LeftTitle];
        
        self.badgeIcon = [UIButton buttonWithType:UIButtonTypeCustom];
        UIImage *image = [UIImage imageNamed:@"leftbar_update_count"];
        image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(0, 10, 0, 10)];
        [self.badgeIcon setBackgroundImage:image forState:UIControlStateNormal];
        [self.badgeIcon setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        self.badgeIcon.titleLabel.font = [UIFont systemFontOfSize:11];
        [self.badgeIcon setBackgroundColor:[UIColor clearColor]];
        self.badgeIcon.frame = CGRectMake(CGRectGetMaxX(self.LeftTitle.frame), 16, 24, 12);
        
        [self.contentView addSubview:self.badgeIcon];       //cell右侧的红色框数字
        
        self.badgeIcon.hidden = YES;
        
        
        self.accessoryImageView = [[UIImageView alloc] initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-15-12, 15, 12, 12)];
        self.accessoryImageView.contentMode = UIViewContentModeScaleAspectFit;
        self.accessoryImageView.image = [UIImage imageNamed:@"accessory_right"];
        [self.contentView addSubview:self.accessoryImageView];
        
        self.sepV = [[UIImageView alloc] initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-15-12, 15, 12, 12)];
        self.sepV.contentMode = UIViewContentModeScaleAspectFit;

        [self.sepV setImage:[UIImage imageNamed:@"learn_cell_sep1"]];
        
        [self.contentView addSubview:self.sepV];
        
    }
    return self;
}

- (void)awakeFromNib
{
    // Initialization code
}

- (void)layoutSubviews{
    [super layoutSubviews];
    self.sepV.frame = CGRectMake(20, self.bounds.size.height - 1, UI_IOS_WINDOW_WIDTH-20, 1);
    self.LeftTitle.font = [UIFont systemFontOfSize:kTextSizeMid];
    self.LeftTitle.frame = CGRectMake(CGRectGetMaxX(self.LeftImageView.frame) + 15, 11, 200, 24);
    NSString *str = self.LeftTitle.text;
    CGSize size = [str sizeWithFont:self.LeftTitle.font constrainedToSize:CGSizeMake(200, 24)];
    self.badgeIcon.frame = CGRectMake(self.LeftTitle.frame.origin.x + size.width + 16, 16, 22, 12);
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    
    // Configure the view for the selected state
}


@end
