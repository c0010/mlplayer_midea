    //
//  CMTableView.m
//  MLPlayer
//
//  Created by sunjj on 11-9-19.
//  Copyright 2011 w. All rights reserved.
//

#import "CMTableView.h"


@implementation CMTableView


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event  
{   
//	NSLog(@"touchesBegan");
	[super touchesBegan:touches withEvent:event]; 
}    

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event 
{    
//	NSLog(@"touchesMoved");
	[super touchesMoved:touches withEvent:event];  
}    

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event 
{ 
//	NSLog(@"touchesEnded");
	[super touchesEnded:touches withEvent:event]; 
	[[self superview] touchesEnded:touches withEvent:event]; 
}      

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event  
{    
//	NSLog(@"touchesCancelled");
	[super touchesCancelled:touches withEvent:event];
}

@end
