//
//  SameButton.m
//  WDKST
//
//  Created by yunpeng kong on 12-4-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ImageRightButton.h"

@implementation ImageRightButton


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
         [self.titleLabel setFont:[UIFont systemFontOfSize:18]];
         [self setImage:[UIImage imageNamed:@"PopupArrow"] forState:UIControlStateNormal];
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
    
        UIImageView *imageView = [self imageView];
        UILabel *label = [self titleLabel];
        
        CGRect imageFrame = imageView.frame;
        CGRect labelFrame = label.frame;
        
        labelFrame.origin.x = self.center.x - labelFrame.size.width/2 - 13 - 6;
    
//        labelFrame.size.width= 30+self.titleLabel.text.length*10;

        imageFrame.origin.x = labelFrame.origin.x + CGRectGetWidth(labelFrame);
        imageFrame.origin.y = 6.0;
        imageFrame.size.width = 13.0;
        imageFrame.size.height = 13.0;
        
        imageView.frame = imageFrame;
    
    
        label.frame = labelFrame;
        
    

    
}

@end
