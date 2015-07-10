//
//  CMButton.m
//  MLPlayer
//
//  Created by water on 14-8-19.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMButton.h"

@implementation CMButton

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        [self addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
        
    }
    return self;
}

- (void)buttonPressed:(CMButton *)sender{
    if (self.onClickListener) {
        self.onClickListener(sender);
    }
}

- (void)setIsRound:(BOOL)isRound{
    if (isRound) {
        self.layer.masksToBounds = YES;
        self.layer.cornerRadius =2.f;
        self.layer.borderColor = [UIColor lightGrayColor].CGColor;
        self.layer.borderWidth = 0.3;
    }
}

- (void)setImage:(UIImage *)image
{
    [self setImage:image forState:UIControlStateNormal];
}

- (void)setHightlightImage:(UIImage *)hightlightImage{
    [self setImage:hightlightImage forState:UIControlStateHighlighted];
}

- (void)setBackgroundImage:(UIImage *)image
{
    [self setBackgroundImage:image forState:UIControlStateNormal];
}

- (BOOL)becomeFirstResponder
{
    return YES;
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
