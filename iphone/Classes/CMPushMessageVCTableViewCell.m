//
//  CMPushMessageVCTableViewCell.m
//  MLPlayer
//
//  Created by wangjianbin on 15/6/17.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMPushMessageVCTableViewCell.h"

@interface CMPushMessageVCTableViewCell()

@property (strong, nonatomic) UIView *separatorLine;

@end

@implementation CMPushMessageVCTableViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self)
    {
        self.imageViewLeftIcon = [[UIImageView alloc]initWithFrame:CGRectMake(14, 25, 30, 30)];
        [self.contentView addSubview:self.imageViewLeftIcon];
        
        self.labelTitle = [[UILabel alloc]initWithFrame:CGRectMake(58, 12, 250, 60)];
        self.labelTitle.font = [UIFont systemFontOfSize:kTextSizeMidLess];
        self.labelTitle.textColor = [UIColor blackColor];
        self.labelTitle.backgroundColor = [UIColor clearColor];
        self.labelTitle.numberOfLines = 2;
        [self.contentView addSubview:self.labelTitle];
        
        self.labelTime = [[UILabel alloc]initWithFrame:CGRectMake(210, 50, 95, 15)];
        self.labelTime.font = [UIFont systemFontOfSize:kTextSizeMidLess];
        self.labelTime.textColor = [UIColor blackColor];
        self.labelTime.backgroundColor = [UIColor clearColor];
        self.labelTime.numberOfLines = 1;
        [self.contentView addSubview:self.labelTime];
        
        self.separatorLine = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 0, 0)];
        self.separatorLine.backgroundColor = kColorBackground;
        [self.contentView addSubview:self.separatorLine];
        
    }
    return self;
}

- (void)awakeFromNib {
    // Initialization code
}

- (void)layoutSubviews{
    self.contentView.frame = self.bounds;
    CGSize leftImaSize = self.imageViewLeftIcon.image.size;
    self.imageViewLeftIcon.frame = CGRectMake(14, (self.bounds.size.height - leftImaSize.width) / 2, leftImaSize.width, leftImaSize.height);
    
    CGSize titleSize = [self.labelTitle.text sizeWithFont:[UIFont systemFontOfSize:kTextSizeMidLess] constrainedToSize:CGSizeMake(self.bounds.size.width - self.imageViewLeftIcon.frame.origin.x - leftImaSize.width - 13, MAXFLOAT) lineBreakMode:NSLineBreakByCharWrapping];
    self.labelTitle.frame = CGRectMake(self.imageViewLeftIcon.frame.origin.x + leftImaSize.width + 13, 12, titleSize.width, titleSize.height + 10);
    
    CGSize timeSize = [self.labelTime.text sizeWithFont:[UIFont systemFontOfSize:kTextSizeMidLess]];
    self.labelTime.frame = CGRectMake(self.bounds.size.width - timeSize.width - 14, self.bounds.size.height - timeSize.height - 17, timeSize.width, timeSize.height + 10);
    
    self.separatorLine.frame = CGRectMake(10, self.bounds.size.height - 1, self.bounds.size.width - 20, 1);
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
