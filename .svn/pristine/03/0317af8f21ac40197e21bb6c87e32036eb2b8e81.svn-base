//
//  MessageView.h
//  FaceBoardDome
//
//  Created by kangle1208 on 13-12-12.
//  Copyright (c) 2013年 Blue. All rights reserved.
//


#import <UIKit/UIKit.h>

#define KFacialSizeWidth    14

#define KFacialSizeHeight   14

#define KCharacterWidth     7


#define VIEW_LINE_HEIGHT    [@":-D" sizeWithFont:[UIFont systemFontOfSize:22]].height

#define VIEW_LEFT           0

#define VIEW_TOP            4

#define VIEW_WIDTH_MAX      200


@interface MessageView : UIView {

    CGFloat upX;

    CGFloat upY;

    CGFloat lastPlusSize;

    CGFloat viewWidth;

    CGFloat viewHeight;

    BOOL isLineReturn;
    
    NSDictionary *_faceMap;
    
    CGSize msgSize;
    
    NSString *wideString;
    
    
}

// 处理过后的用户绘图的富文本字符串
@property (nonatomic, strong) NSMutableAttributedString *attrEmotionString;

// 按顺序保存的 emotionString 中包含的表情名字
@property (nonatomic, strong) NSMutableArray *emotionNames;
@property (nonatomic, strong) NSDictionary *faceMap;

@property (nonatomic, strong) NSArray *emotionRanges;

@property (nonatomic, strong) NSMutableDictionary *emojiRanges;

@property (nonatomic, strong) NSMutableArray *messageRange;

@property (nonatomic, strong) NSString *text;
@property (nonatomic, assign) CGSize messageSize;

@property(nonatomic,strong)UIColor *textColor; //字体颜色

- (void)setText:(NSString *)message;

- (CGSize)getContentSizeWithMessage:(NSString *)message;

- (id)initWithFrame:(CGRect)frame emotionString:(NSString *)emotionString;

/// 将 emotionString 中的特殊字符串替换为空格
// @discussion 不要直接调用此方法
- (void)cookEmotionString;

@end
