//
//  CMLabel.h
//  MLPlayer
//
//  Created by hushengwu on 13-10-15.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CMLabel : UILabel{
	NSMutableAttributedString* attriString;
    BOOL isShowColor;
}
@property (nonatomic, assign) BOOL isLineFeed;
@property (nonatomic, retain) NSMutableAttributedString *attriString;

-(void)setKeyWordTextArray:(NSArray *)keyWordArray WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor;
-(void)setText:(NSString *)text WithFont:(UIFont *)font AndColor:(UIColor *)color;
-(void)setKeyWordRange:(NSRange)range WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor;

-(void)setAllKeyWordTextArray:(NSArray *)keyWordArray WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor;


@end
