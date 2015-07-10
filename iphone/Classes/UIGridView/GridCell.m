//
//  Cell.m
//  naivegrid
//
//  Created by Apirom Na Nakorn on 3/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "GridCell.h"
#import <QuartzCore/QuartzCore.h> 

@implementation GridCell


@synthesize thumbnail;
@synthesize label;


- (id)init {
	
    if (self = [super init]) {
		
        self.frame = CGRectMake(0, 0, 80, 80);
		
		[[NSBundle mainBundle] loadNibNamed:@"GridCell" owner:self options:nil];
		
        [self addSubview:self.view];
		
		self.thumbnail.layer.cornerRadius = 4.0;
		self.thumbnail.layer.masksToBounds = YES;
//		self.thumbnail.layer.borderColor = [UIColor lightGrayColor].CGColor;
//		self.thumbnail.layer.borderWidth = 1.0;
        self.label.textColor = UIColorFromRGB(0x2e2e2e);
        self.backgroundColor = UIColorFromRGB(0xcbcbcb);
	}
	
    return self;
	
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
}
*/



@end
