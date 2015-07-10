//
//  UIProgressBar.h
//  
//
//  Created by xiangwei.ma
//  
//

#import <UIKit/UIKit.h>


@interface UIProgressBar : UIView 
{
	float minValue, maxValue;
	float currentValue;
	UIColor *lineColor, *progressRemainingColor, *progressColor;
}

@property (nonatomic,readwrite) float minValue, maxValue, currentValue;
@property (nonatomic, strong) UIColor *lineColor, *progressRemainingColor, *progressColor;

-(void)setNewRect:(CGRect)newFrame;

@end
