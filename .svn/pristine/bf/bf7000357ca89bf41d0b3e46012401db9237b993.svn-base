//
//  FaceButton.h
//
//  Created by blue on 12-9-26.
//  Copyright (c) 2012年 blue. All rights reserved.
//  Email - 360511404@qq.com
//  http://github.com/bluemood
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
@protocol FaceEmojiViewDelegate;

@interface FaceButton : UIView{
    NSInteger _touchedIndex;   
}
@property (weak, nonatomic) id<FaceEmojiViewDelegate> delegate;
@property (strong, nonatomic) UIImage *image;
@property (assign, nonatomic) NSInteger touchedIndex;
@property (strong, nonatomic) NSMutableArray *emojiImages;

- (void)preparEmojiImages;

@end

@protocol FaceEmojiViewDelegate<NSObject>
@optional
/**
 *	点击开始点击到的emoji的 index位置
 *
 */
- (void)didTouchEmojiViewBeganIndex:(NSInteger)index;

/**
 *	点击移动时 更新气泡框最新位置的emoji表情
 *
 */
- (void)didTouchEmojiViewMovedIndex:(NSInteger)index;

/**
 *	点击手势结束，获取emoji表情在plist里的text文本
 *
 */
- (void)didTouchEmojiView:(FaceButton*)emojiView touchedEmoji:(NSString*)string;
@end
