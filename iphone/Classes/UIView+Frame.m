//
//  UIView+Rect.m
//  MLPlayer
//
//  Created by water on 14-9-4.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "UIView+Frame.h"

@implementation UIView (Frame)

//设置Y坐标
- (void)setFrameY:(CGFloat)originY
{
    CGRect frame = self.frame;
    frame.origin.y = originY;
    self.frame = frame;
}

- (void)setFrameX:(CGFloat)originX
{
    CGRect frame = self.frame;
    frame.origin.x = originX;
    self.frame = frame;
}

- (void)setFrameY:(CGFloat)originY Height:(CGFloat)height
{
    CGRect frame = self.frame;
    frame.origin.y = originY;
    frame.size.height = height;
    self.frame = frame;
}

- (void)setFrameY:(CGFloat)originY Width:(CGFloat)width
{
    CGRect frame = self.frame;
    frame.origin.y = originY;
    frame.size.width = width;
    self.frame = frame;
}

- (void)setFrameX:(CGFloat)originX Width:(CGFloat)width
{
    CGRect frame = self.frame;
    frame.origin.x = originX;
    frame.size.width = width;
    self.frame = frame;
}

- (void)setFrameWidth:(CGFloat)width
{
    CGRect frame = self.frame;
    frame.size.width = width;
    self.frame = frame;
}

- (void)setFrameHeight:(CGFloat)height
{
    CGRect frame = self.frame;
    frame.size.height = height;
    self.frame = frame;
}

- (void)setCenterY:(CGFloat)originY{
    CGPoint point = self.center;
    point.y = originY;
    self.center = point;
}

- (void)setCenterX:(CGFloat)originX{
    CGPoint point = self.center;
    point.x = originX;
    self.center = point;
}

- (void)dumpView:(UIView *)aView atIndent:(int)indent into:(NSMutableString *)outstring

{
    
    for (int i = 0; i < indent; i++) [outstring appendString:@"--"];
    
    [outstring appendFormat:@"[%2d] %@\n", indent, [[aView class] description]];
    
    for (UIView *view in [aView subviews])
        
        [self dumpView:view atIndent:indent + 1 into:outstring];
    
}


// Start the tree recursion at level 0 with the root view

- (NSString *) displayViews: (UIView *) aView

{
    
    NSMutableString *outstring = [[NSMutableString alloc] init];
    
    [self dumpView: aView atIndent:0 into:outstring];
    
    return outstring;
    
}

- (void) logViewTree {
    NSLog(@"The view tree:%@",[self displayViews:self]);
}
@end
