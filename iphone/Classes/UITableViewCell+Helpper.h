//
//  UITableViewCell+Helpper.h
//  MLPlayer
//
//  Created by water on 14-8-14.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UITableViewCell (Helpper)

- (void)setTop:(CGFloat)height;
- (void)setTopRound:(CGFloat)height;
- (void)setMiddle:(CGFloat)height;
- (void)setButtom:(CGFloat)height;
- (void)setButtomRound:(CGFloat)height;

- (void)setSingle:(CGFloat)height;
- (void)setSingleRound:(CGFloat)height;

- (void)setRoundSection:(int)total atIndex:(int)index height:(CGFloat)height;
- (void)setSection:(int)total atIndex:(int)index height:(CGFloat)height;
@end
