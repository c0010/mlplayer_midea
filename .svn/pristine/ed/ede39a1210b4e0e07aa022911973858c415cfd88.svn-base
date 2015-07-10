//
//  JKCustomAlert.m
//  CustomAlert
//
//  Created by Joris Kluivers on 4/2/09.
//  Copyright 2009 Tarento Software Solutions & Projects. All rights reserved.
//

#import "CustomBGAlert.h"
#import "tool.h"


@implementation CustomBGAlert

@synthesize indicatorView,titleLabel;
-(id)init
{
	self = [super init];
	if(self != nil)
	{
		self.delegate = self;
		indicatorView = [[UIActivityIndicatorView alloc] init];
		
		indicatorView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
		indicatorView.hidden = NO;
		
		[self addSubview:indicatorView]; 
		
		
		titleLabel = [[UILabel alloc] init];
		titleLabel.text = I(@"加载中…");//@"加载中...";
		titleLabel.backgroundColor = [UIColor clearColor];
		titleLabel.textColor = [UIColor whiteColor];
		titleLabel.font = [UIFont systemFontOfSize:14];
		[self addSubview:titleLabel];
	}
	return self;
}
-(void)show
{
	[super show];
    
	for (UIView *view in self.subviews) {
        // change the background image
        if ([view isKindOfClass:[UIImageView class]]) {
            UIImage *theImage = [UIImage imageNamed:@"textHintBG.png"];    
			//((UIImageView *)view).image = [theImage resizableImageWithCapInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
            ((UIImageView *)view).image = theImage;
			
        }
	}
    
	[indicatorView startAnimating]; 
}
//- (void) show {
//	
//	[self performSelectorOnMainThread:@selector(ShowAlert) withObject:nil waitUntilDone:NO];
//}

- (void)willPresentAlertView:(CustomBGAlert *)alertView
{  
	[alertView setBGAlertViewX:110 alertFrameY:200 alertFrameWidth:100 alertFrameHeight:100];   
}

-(void)setBGAlertViewX: (NSInteger) alertFrameX alertFrameY:(NSInteger )alertFrameY alertFrameWidth:(NSInteger)alertFrameW alertFrameHeight: (NSInteger)alertFrameH {

    self.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-alertFrameW)/2, (UI_IOS_WINDOW_HEIGHT-alertFrameH)/3, alertFrameW, alertFrameH);
    
    
    self.alpha = 0.6;
    NSInteger progressFrameW = 30;
    NSInteger progressFrameX = alertFrameW/2 - progressFrameW/2;
    NSInteger progressFrameY = alertFrameH/2 - progressFrameW/2 - 20;
    
    NSInteger titleLableFrameW = 60;
    NSInteger titleLabelFrameX = alertFrameW/2 - titleLableFrameW/2;
    NSInteger titleLabelFrameY =  alertFrameH/2 - titleLableFrameW/2 + 20;
    
    self.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-alertFrameW)/2, (UI_IOS_WINDOW_HEIGHT-alertFrameH)/3, alertFrameW, alertFrameH);
	indicatorView.frame = CGRectMake(progressFrameX, progressFrameY, progressFrameW, progressFrameW);
	titleLabel.frame = CGRectMake(titleLabelFrameX, titleLabelFrameY, titleLableFrameW, titleLableFrameW);
}
@end
