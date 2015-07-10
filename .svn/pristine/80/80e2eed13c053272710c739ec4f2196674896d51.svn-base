//
//  UITableViewCell+Helpper.m
//  MLPlayer
//
//  Created by water on 14-8-14.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "UITableViewCell+Helpper.h"

#define DefaultColor [UIColor colorWithRed:222.0/255.0f green:222.0/255.0f blue:222.0/255.0f alpha:1]
#define DefaultTag 2000

#define BACKGROUP_WIDTH 320
#define BACKGROUP_ROUND_WIDTH 300
#define BACKGROUP_BORDER_WIDTH 0.7
#define BACKGROUP_RADIUS_WIDTH 0.0
#define BACKGROUP_ORIGIN_Y 10
#define BACKGROUP_ORIGIN_X 10

#define BACKGROUP_SELECTED_COLOR [UIColor colorWithWhite:0.8 alpha:0.8]

@implementation UITableViewCell (Helpper)

- (UIView *)backViewFrame:(CGRect)bRect selectedRect:(CGRect)sRect fillColor:(UIColor *)color isRadius:(BOOL)radius{

    UIView *backView = [[UIView alloc]initWithFrame:bRect];
    backView.backgroundColor = color;
    backView.clipsToBounds = YES;
    
    UIView *innerView = [[UIView alloc]initWithFrame:sRect];
    innerView.backgroundColor = [UIColor clearColor];
    if (radius) {
        innerView.layer.cornerRadius = BACKGROUP_RADIUS_WIDTH;
        innerView.layer.masksToBounds = YES;
    }
    innerView.layer.borderColor = DefaultColor.CGColor;
    innerView.layer.borderWidth = BACKGROUP_BORDER_WIDTH;
    [backView addSubview:innerView];
    
    return backView;
}

- (UIView *)addSeparator:(UIView *)backView{
    
    UIView *sepView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.frame), BACKGROUP_BORDER_WIDTH)];
    sepView.backgroundColor = DefaultColor;
    [backView addSubview:sepView];
    
    return backView;
}

- (void)setTop:(CGFloat)height{
    
    CGRect bRect = CGRectMake(0, 0, BACKGROUP_WIDTH, height);
    CGRect sRect = CGRectMake(-BACKGROUP_ORIGIN_X, 0, BACKGROUP_WIDTH + 2*BACKGROUP_ORIGIN_X, height + BACKGROUP_ORIGIN_Y);
    self.backgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:[UIColor whiteColor] isRadius:NO];
    self.selectedBackgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:BACKGROUP_SELECTED_COLOR isRadius:NO];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setTopRound:(CGFloat)height{
    
    CGRect bRect = CGRectMake(0, 0, BACKGROUP_ROUND_WIDTH, height);
    CGRect sRect = CGRectMake(0, 0, BACKGROUP_ROUND_WIDTH, height + BACKGROUP_ORIGIN_Y);
    self.backgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:[UIColor whiteColor] isRadius:YES];
    self.selectedBackgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:BACKGROUP_SELECTED_COLOR isRadius:YES];
   
    self.backgroundColor = [UIColor clearColor];
}

- (void)setMiddleRound:(CGFloat)height{
    
    CGRect bRect = CGRectMake(0, 0, BACKGROUP_ROUND_WIDTH, height);
    CGRect sRect = CGRectMake(0, 0, BACKGROUP_ROUND_WIDTH, height + BACKGROUP_ORIGIN_Y);
    self.backgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:[UIColor whiteColor] isRadius:NO];
    self.selectedBackgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:BACKGROUP_SELECTED_COLOR isRadius:NO];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setMiddle:(CGFloat)height{
    
    CGRect bRect = CGRectMake(0, 0, BACKGROUP_WIDTH, height);
    CGRect sRect = CGRectMake(-BACKGROUP_ORIGIN_X, 0, BACKGROUP_WIDTH + 2*BACKGROUP_ORIGIN_X, height + BACKGROUP_ORIGIN_Y);
    self.backgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:[UIColor whiteColor] isRadius:NO];
    self.selectedBackgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:BACKGROUP_SELECTED_COLOR isRadius:NO];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setButtomRound:(CGFloat)height{
    
    CGRect bRect = CGRectMake(0, 0, BACKGROUP_ROUND_WIDTH, height);
    CGRect sRect = CGRectMake(0, -BACKGROUP_ORIGIN_Y, BACKGROUP_ROUND_WIDTH, height + BACKGROUP_ORIGIN_Y);
    
    UIView *backView = [self backViewFrame:bRect selectedRect:sRect fillColor:[UIColor whiteColor] isRadius:YES];
    backView = [self addSeparator:backView];
    self.backgroundView = backView;
    self.selectedBackgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:BACKGROUP_SELECTED_COLOR isRadius:YES];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setButtom:(CGFloat)height{
    
    CGRect bRect = CGRectMake(0, 0, BACKGROUP_WIDTH, height);
    CGRect sRect = CGRectMake(-BACKGROUP_ORIGIN_X, 0, BACKGROUP_WIDTH + 2*BACKGROUP_ORIGIN_X, height);
    
    self.backgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:[UIColor whiteColor] isRadius:NO];
    self.selectedBackgroundView = [self backViewFrame:bRect selectedRect:sRect fillColor:BACKGROUP_SELECTED_COLOR isRadius:NO];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setSingleRound:(CGFloat)height{
    
    CGRect rect = CGRectMake(0, 0, BACKGROUP_ROUND_WIDTH, height);
    self.backgroundView = [self backViewFrame:rect selectedRect:rect fillColor:[UIColor whiteColor] isRadius:YES];
    self.selectedBackgroundView = [self backViewFrame:rect selectedRect:rect fillColor:BACKGROUP_SELECTED_COLOR isRadius:YES];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setSingle:(CGFloat)height{
    
    CGRect rect = CGRectMake(-BACKGROUP_ORIGIN_X, 0, BACKGROUP_WIDTH + 2 * BACKGROUP_ORIGIN_X, height);
    self.backgroundView = [self backViewFrame:rect selectedRect:rect fillColor:[UIColor whiteColor] isRadius:NO];
    self.selectedBackgroundView = [self backViewFrame:rect selectedRect:rect fillColor:BACKGROUP_SELECTED_COLOR isRadius:NO];
    
    self.backgroundColor = [UIColor clearColor];
}

- (void)setRoundSection:(int)total atIndex:(int)index height:(CGFloat)height{
    
    if (total > 0) {
        if (total > 1) {
            if (index == 0) {
                [self setTopRound:height];
            }else if (index == total - 1) {
                [self setButtomRound:height];
            }else{
                [self setMiddleRound:height];
            }
        }else{
            [self setSingleRound:height];
        }
    }
}

- (void)setSection:(int)total atIndex:(int)index height:(CGFloat)height{
    
    if (total > 0) {
        if (total > 1) {
            if (index == 0) {
                [self setTop:height];
            }else if (index == total - 1) {
                [self setButtom:height];
            }else{
                [self setMiddle:height];
            }
        }else{
            [self setSingle:height];
        }
    }
}

@end
