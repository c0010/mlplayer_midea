//
//  CMTextView.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-4-18.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CMTextView : UITextView
{
    BOOL isShowColor;
}


@property (nonatomic, assign) BOOL isLineFeed;
@property (nonatomic, strong) NSMutableAttributedString *attriString;

-(void)setKeyWordTextArray:(NSArray *)keyWordArray WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor;
-(void)setText:(NSString *)text WithFont:(UIFont *)font AndColor:(UIColor *)color;
-(void)setKeyWordRange:(NSRange)range WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor;

-(void)setAllKeyWordTextArray:(NSArray *)keyWordArray WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor;
@end
