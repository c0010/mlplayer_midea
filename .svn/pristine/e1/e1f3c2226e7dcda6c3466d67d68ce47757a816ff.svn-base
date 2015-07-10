//
//  CMSegmentedControl.m
//  MLPlayer
//
//  Created by water on 14-8-14.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMSegmentedControl.h"
#import "tool.h"

#define SELECTED_COLOR	[UIColor colorWithRed:27.0/255.0 green:109.0/255.0 blue:179.0/255.0 alpha:1.0f]

@implementation CMSegmentedControl

- (id)initWithFrame:(CGRect)frame leftTitle:(NSString *)leftTitle rightTitle:(NSString *)rightTitle didSelectedIndex:(SegmentedListener)listener
{
    self = [super initWithFrame:frame];
    if (self) {
        
        leftButton = [UIButton buttonWithType:UIButtonTypeCustom];
        leftButton.frame = CGRectMake(0, 0, CGRectGetWidth(frame)/2, CGRectGetHeight(frame));
        [leftButton setBackgroundImage:[UIImage imageNamed:@"segmentedControl_left_normal"] forState:UIControlStateNormal];
        [leftButton setBackgroundImage:[UIImage imageNamed:@"segmentedControl_left_selected"] forState:UIControlStateSelected];
        leftButton.adjustsImageWhenHighlighted = NO;
        [leftButton setTitleColor:UIColorRGB(0x165992) forState:UIControlStateNormal];
        [leftButton setTitleColor:[UIColor whiteColor] forState:UIControlStateSelected];
        [leftButton addTarget:self action:@selector(leftButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [leftButton setTitle:leftTitle forState:UIControlStateNormal];
        leftButton.titleLabel.font = [UIFont systemFontOfSize:16.f];
        leftButton.selected = YES;
        leftButton.userInteractionEnabled = NO;

        rightButton = [UIButton buttonWithType:UIButtonTypeCustom];
        rightButton.frame = CGRectMake(CGRectGetWidth(frame)/2, 0, CGRectGetWidth(frame)/2, CGRectGetHeight(frame));
        [rightButton setBackgroundImage:[UIImage imageNamed:@"segmentedControl_right_normal"] forState:UIControlStateNormal];
        [rightButton setBackgroundImage:[UIImage imageNamed:@"segmentedControl_right_selected"] forState:UIControlStateSelected];
        rightButton.adjustsImageWhenHighlighted = NO;
        [rightButton setTitleColor:UIColorRGB(0x165992) forState:UIControlStateNormal];
        [rightButton setTitleColor:[UIColor whiteColor] forState:UIControlStateSelected];
        [rightButton addTarget:self action:@selector(rightButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [rightButton setTitle:rightTitle forState:UIControlStateNormal];
        rightButton.titleLabel.font = [UIFont systemFontOfSize:16.f];

        [self addSubview:leftButton];
        [self addSubview:rightButton];
        
        self.segmentedListener = listener;
    }
    return self;
}

- (void)leftButtonPressed:(UIButton *)sender{
    if (!leftButton.selected) {
        leftButton.selected = YES;
        leftButton.userInteractionEnabled = NO;
        rightButton.selected = NO;
        rightButton.userInteractionEnabled = YES;
    }
    
    if (self.segmentedListener) {
        self.segmentedListener(0);
    }
}

- (void)rightButtonPressed:(UIButton *)sender{
    if (!rightButton.selected) {
        leftButton.selected = NO;
        leftButton.userInteractionEnabled = YES;
        rightButton.selected = YES;
        rightButton.userInteractionEnabled = NO;
    }
    
    if (self.segmentedListener) {
        self.segmentedListener(1);
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
