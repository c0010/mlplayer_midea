//
//  SameButton.m
//  WDKST
//
//  Created by yunpeng kong on 12-4-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ComplexButton.h"

@implementation ComplexButton


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
         [self.titleLabel setFont:[UIFont systemFontOfSize:12]];
		self.titleLabel.textAlignment = UITextAlignmentCenter;
    }
    return self;
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
    
    CGRect f = self.bounds;
	UIImageView *imageView = [self imageView];
	UILabel *label = [self titleLabel];
	
	CGRect imageFrame = imageView.frame;
	CGRect labelFrame = label.frame;
	
	imageFrame.origin.y = 6;
	imageFrame.origin.x = (f.size.width-imageFrame.size.width)/2;
	labelFrame.origin.y = imageFrame.size.height+5;
	labelFrame.origin.x = (f.size.width-labelFrame.size.width)/2;
	imageView.frame = imageFrame;
	label.frame = labelFrame;
    
}

@end
