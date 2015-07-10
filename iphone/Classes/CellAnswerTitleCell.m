//
//  CellAnswerTitleCell.m
//  MLPlayer
//
//  Created by hushengwu on 13-8-12.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CellAnswerTitleCell.h"

@implementation CellAnswerTitleCell
@synthesize imageView,label;
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor clearColor];

        UIView *bg = [[UIView alloc]initWithFrame:CGRectMake(10.0, 0.0, 300.0, 33.0)];
        bg.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"cell_title_bg"]];
        [self.contentView addSubview:bg];
        
        imageView = [[UIImageView alloc]initWithFrame:CGRectMake(10.0, 6.0, 21.0, 21.0)];
        imageView.backgroundColor = [UIColor clearColor];
        [bg addSubview:imageView];
        
        label = [[UILabel alloc]initWithFrame:CGRectMake(41.0, 0.0, 120.0, 33.0)];
        label.backgroundColor = [UIColor clearColor];
        [bg addSubview:label];
        [self setSelectionStyle:UITableViewCellSelectionStyleNone];
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
