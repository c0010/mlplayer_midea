//
//  CMAppVCCollectionViewCell.m
//  MLPlayer
//
//  Created by wangjianbin on 15/6/11.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMAppVCCollectionViewCell.h"

@implementation CMAppVCCollectionViewCell

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor whiteColor];
        float cellWidth = self.bounds.size.width;
        self.imaView = [[UIImageView alloc]initWithFrame:CGRectMake((cellWidth - 34) / 2, (cellWidth - 34) / 2 - 10, 34, 34)];
        self.imaView.backgroundColor = [UIColor clearColor];
        self.titleLab = [[UILabel alloc]init];
        self.titleLab.textAlignment = NSTextAlignmentCenter;
        [self.contentView addSubview:self.imaView];
        [self.contentView addSubview:self.titleLab];
        
        self.badgeIcon = [UIButton buttonWithType:UIButtonTypeCustom];
        UIImage *image = [UIImage imageNamed:@"leftbar_update_count"];
        [self.badgeIcon setBackgroundImage:[image resizableImageWithCapInsets:UIEdgeInsetsMake(6, 6, 6, 6)] forState:UIControlStateNormal];
        [self.badgeIcon setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        self.badgeIcon.titleLabel.font = [UIFont systemFontOfSize:9];
        [self.badgeIcon setBackgroundColor:[UIColor clearColor]];
        self.badgeIcon.frame = CGRectMake(CGRectGetMaxX(self.imaView.frame) - 6, CGRectGetMinY(self.imaView.frame) - 6, 15, 15);
        
        [self.contentView addSubview:self.badgeIcon];       //cell右侧的红色框数字
        
        self.badgeIcon.hidden = YES;

        self.layer.borderWidth = 0.5f;
        self.layer.borderColor = kColorBackground.CGColor;
        
        
    }
    return self;
}

- (void)layoutSubviews
{
    self.titleLab.font = [UIFont systemFontOfSize:kTextSizeMid];
    self.titleLab.frame = CGRectMake(0, 76, self.bounds.size.width, 16);
}

@end
