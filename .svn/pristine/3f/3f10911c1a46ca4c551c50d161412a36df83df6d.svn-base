//  Created by Tim on 13-1-15.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.

#import "CheckBoxButton.h"

@implementation CheckBoxButton
@synthesize Check;
@synthesize CheckType;
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self != nil)
    {
        self.titleLabel.font = [UIFont systemFontOfSize:14];
        [self setColor:[UIColor blackColor]];
        self.Check = NO;
        self.CheckType = 0;
        [self addTarget:(id)self action:@selector(onCheck) forControlEvents:UIControlEventTouchUpInside];
    }
    return self;
}
-(void)setColor:(UIColor*)color
{
    [self setTitleColor:color forState:UIControlStateNormal];
}
-(void)setTitle:(NSString*)title
{
    [self setTitle:title forState:UIControlStateNormal];
}

-(void)setCheck:(BOOL)bcheck
{
    self.tag = bcheck;
    if(bcheck)
    {
        if (CheckType) {
            [self setImage:[UIImage imageNamed:@"check_n1"] forState:UIControlStateNormal];
        }
        else
            [self setImage:[UIImage imageNamed:@"check_n"] forState:UIControlStateNormal];
    }
    else
    {
        if (CheckType) {
            [self setImage:[UIImage imageNamed:@"uncheck_n1"] forState:UIControlStateNormal];
        }
        else
            [self setImage:[UIImage imageNamed:@"uncheck_n"] forState:UIControlStateNormal];
    }
}


-(BOOL)Check
{
    return self.tag;
}

-(void)onCheck
{
    self.Check = !self.tag;
}
/*
 // Only override drawRect: if you perform custom drawing.
 // An empty implementation adversely affects performance during animation.
 - (void)drawRect:(CGRect)rect
 {
 // Drawing code
 }
 */



- (void)layoutSubviews
{
    // Allow default layout, then adjust image and label positions
    [super layoutSubviews];
    //  NSLog(@"layoutSubviews");
    
    UIImageView *imageView = [self imageView];
    UILabel *label = [self titleLabel];
    
    CGRect imageFrame = imageView.frame;
    imageFrame.origin.x = 0;
    imageView.frame = imageFrame;
    CGRect labelFrame = label.frame;
    labelFrame.origin.x = imageFrame.size.width + 4;
    //labelFrame.size.width -= 2;
    label.frame = labelFrame;
    
}

@end
