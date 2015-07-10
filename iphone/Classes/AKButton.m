//
//  AKButton.m
//  MLPlayer
//
//  Created by hushengwu on 13-8-12.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "AKButton.h"
#import <QuartzCore/QuartzCore.h>
#define degreesToRadians(degrees) (M_PI * degrees / 180.0)

@implementation AKButton
@synthesize bg,arrows;
@synthesize selectType,delegate;
@synthesize isOpen;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        bg = [[UIImageView alloc]initWithFrame:CGRectMake(0.0, 0.0, frame.size.width, frame.size.height)];
        bg.backgroundColor = [UIColor clearColor];
        bg.image = [UIImage imageNamed:@"myAnswer_normal"];
        [self addSubview:bg];
        
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(0.0, 0.0, CGRectGetWidth(frame) *4 /5, CGRectGetHeight(frame))];
        label.text = I(@"我来回答");
        label.font = [UIFont systemFontOfSize:15.0];
        label.textAlignment = UITextAlignmentCenter;
        label.backgroundColor = [UIColor clearColor];
        [self addSubview:label];
        
        arrows = [[UIImageView alloc]initWithFrame:CGRectMake(CGRectGetMaxX(label.frame), 12.0, 10.0, 10.0)];
        arrows.image = [UIImage imageNamed:@"myAnswer_arrows"];
        arrows.backgroundColor = [UIColor clearColor];
        [self addSubview:arrows];
    }
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    bg.image = [UIImage imageNamed:@"myAnswer_select"];
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    if ([delegate respondsToSelector:@selector(didSelectButtonControl:withEvent:)]) {
        [delegate didSelectButtonControl:touches withEvent:event];
    }
    
    bg.image = [UIImage imageNamed:@"myAnswer_normal"];
    if (!isOpen) {
        [self CloseAnimaon];
    }
    else{
        [self OpenAnimaon];
    }

}

- (void)setAKButtonStatus:(BOOL)statue{
    isOpen = statue;
    if (statue) {
        [self OpenAnimaon];
    }
    else{
        [self CloseAnimaon];
    }
}

- (void)OpenAnimaon{
    [UIView beginAnimations:@"rotate" context:nil];
    [UIView setAnimationDuration:0.1];
    arrows.transform = CGAffineTransformMakeRotation(degreesToRadians(90.0));
    [UIView commitAnimations];
}
- (void)CloseAnimaon{
    [UIView beginAnimations:@"rotate" context:nil];
    [UIView setAnimationDuration:0.1];
    arrows.transform = CGAffineTransformMakeRotation(degreesToRadians(0.0));
    [UIView commitAnimations];
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
