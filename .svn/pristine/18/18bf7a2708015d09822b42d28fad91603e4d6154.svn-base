//
//  UIProgressBar.h
//  
//
//  Created by xiangwei.ma
//  
//

#import "UIProgressBar.h"


@implementation UIProgressBar

@synthesize  minValue, maxValue, currentValue;
@synthesize lineColor, progressRemainingColor, progressColor;
- (id)initWithFrame:(CGRect)frame 
{
    if (self = [super initWithFrame:frame])
	{
		minValue = 0;
		maxValue = 1;
		currentValue = 0;
		self.backgroundColor = [UIColor clearColor];
		lineColor = [UIColor whiteColor];
		progressColor = [UIColor darkGrayColor];
		progressRemainingColor = [UIColor lightGrayColor];
    }
    return self;
}


- (void)drawRect:(CGRect)rect
{
	CGContextRef context = UIGraphicsGetCurrentContext();
	
	CGContextSetLineWidth(context, 2);
	
	CGContextSetStrokeColorWithColor(context,[lineColor CGColor]);
//	CGContextSetFillColorWithColor(context, [[progressRemainingColor colorWithAlphaComponent:.7] CGColor]);
    CGContextSetFillColorWithColor(context, [progressRemainingColor CGColor]);

	
	float radius = (rect.size.height / 2) - 2;
	CGContextMoveToPoint(context, 2, rect.size.height/2);

	CGContextAddArcToPoint(context, 2, 2, radius + 2, 2, radius);
	CGContextAddLineToPoint(context, rect.size.width - radius - 2, 2);
	CGContextAddArcToPoint(context, rect.size.width - 2, 2, rect.size.width - 2, rect.size.height / 2, radius);
	CGContextFillPath(context);
	
	CGContextSetFillColorWithColor(context, [progressRemainingColor CGColor]);

	CGContextMoveToPoint(context, rect.size.width - 2, rect.size.height/2);
	CGContextAddArcToPoint(context, rect.size.width - 2, rect.size.height - 2, rect.size.width - radius - 2, rect.size.height - 2, radius);
	CGContextAddLineToPoint(context, radius + 2, rect.size.height - 2);
	CGContextAddArcToPoint(context, 2, rect.size.height - 2, 2, rect.size.height/2, radius);
	CGContextFillPath(context);
	
	CGContextMoveToPoint(context, 2, rect.size.height/2);
	
	CGContextAddArcToPoint(context, 2, 2, radius + 2, 2, radius);
	CGContextAddLineToPoint(context, rect.size.width - radius - 2, 2);
	CGContextAddArcToPoint(context, rect.size.width - 2, 2, rect.size.width - 2, rect.size.height / 2, radius);
	CGContextAddArcToPoint(context, rect.size.width - 2, rect.size.height - 2, rect.size.width - radius - 2, rect.size.height - 2, radius);
	
	CGContextAddLineToPoint(context, radius + 2, rect.size.height - 2);
	CGContextAddArcToPoint(context, 2, rect.size.height - 2, 2, rect.size.height/2, radius);
	CGContextStrokePath(context);
	
//	CGContextSetFillColorWithColor(context, [[progressColor colorWithAlphaComponent:.78] CGColor]);
    	CGContextSetFillColorWithColor(context, [progressColor CGColor]);


	//radius = radius - 2;
    CGFloat temp = 2.0;
	CGContextMoveToPoint(context, temp, rect.size.height/2);
	float amount = (currentValue/(maxValue - minValue)) * (rect.size.width);
	
	if (amount >= radius + temp && amount <= (rect.size.width - radius - temp)) {
		CGContextAddArcToPoint(context, temp, temp, radius + temp, temp, radius);
		CGContextAddLineToPoint(context, amount, temp);
		//CGContextAddLineToPoint(context, amount, radius + 4);
		CGContextAddArcToPoint(context, amount + radius + temp, temp,  amount + radius + temp, rect.size.height/2, radius);

		CGContextFillPath(context);
		
		CGContextSetFillColorWithColor(context, [progressColor CGColor]);
		CGContextMoveToPoint(context, temp, rect.size.height/2);
		CGContextAddArcToPoint(context, temp, rect.size.height - temp, radius + temp, rect.size.height - temp, radius);
		CGContextAddLineToPoint(context, amount, rect.size.height - temp);
		CGContextAddArcToPoint(context, amount + radius + temp, rect.size.height - temp,  amount + radius + temp, rect.size.height/2, radius);
		//CGContextAddLineToPoint(context, amount, radius + 4);
		CGContextFillPath(context);
	} else if (amount > radius + temp) {
		CGContextAddArcToPoint(context, temp, temp, radius + temp, temp, radius);
		CGContextAddLineToPoint(context, rect.size.width - radius - temp, temp);
		CGContextAddArcToPoint(context, rect.size.width - temp, temp, rect.size.width - temp, rect.size.height/2, radius);
		CGContextFillPath(context);
		
		CGContextSetFillColorWithColor(context, [progressColor CGColor]);
		CGContextMoveToPoint(context, temp, rect.size.height/2);
		CGContextAddArcToPoint(context, temp, rect.size.height - temp, radius + temp, rect.size.height - temp, radius);
		CGContextAddLineToPoint(context, rect.size.width - radius - temp, rect.size.height - temp);
		CGContextAddArcToPoint(context, rect.size.width - temp, rect.size.height - temp, rect.size.width - temp, rect.size.height/2, radius);
		CGContextFillPath(context);
	} else if (amount < radius + temp && amount > 0) {
		CGContextAddArcToPoint(context, temp, temp, radius + temp, temp, radius);
		CGContextAddLineToPoint(context, radius + temp, rect.size.height/2);
		CGContextFillPath(context);
		
		CGContextSetFillColorWithColor(context, [progressColor CGColor]);
		CGContextMoveToPoint(context, temp, rect.size.height/2);
		CGContextAddArcToPoint(context, temp, rect.size.height - temp, radius + temp, rect.size.height - temp, radius);
		CGContextAddLineToPoint(context, radius + temp, rect.size.height/2);
		CGContextFillPath(context);
	}
	
	
}

-(void)setNewRect:(CGRect)newFrame 
{
	self.frame = newFrame;
	[self setNeedsDisplay];

}

-(void)setMinValue:(float)newMin
{
	minValue = newMin;
	[self setNeedsDisplay];

}

-(void)setMaxValue:(float)newMax
{
	maxValue = newMax;
	[self setNeedsDisplay];

}

-(void)setCurrentValue:(float)newValue
{
	currentValue = newValue;
	[self setNeedsDisplay];
}

-(void)setLineColor:(UIColor *)newColor
{
	lineColor = newColor;
	[self setNeedsDisplay];

}

-(void)setProgressColor:(UIColor *)newColor
{
	progressColor = newColor;
	[self setNeedsDisplay];

}

-(void)setProgressRemainingColor:(UIColor *)newColor
{
	progressRemainingColor = newColor;
	[self setNeedsDisplay];

}



@end
