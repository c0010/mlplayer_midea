//
//  FaceBoard.h
//
//  Created by blue on 12-9-26.
//  Copyright (c) 2012年 blue. All rights reserved.
//  Email - 360511404@qq.com
//  http://github.com/bluemood

#import <UIKit/UIKit.h>
#import "FaceButton.h"
#import "GrayPageControl.h"


@protocol FaceBoardDelegate <NSObject>

@optional

- (void)textViewDidChange:(UITextView *)textView;

@end

@interface FaceBoard : UIView<UIScrollViewDelegate,FaceEmojiViewDelegate>{
    UIScrollView *faceView;
    GrayPageControl *facePageControl;
    NSDictionary *_faceMap;
}
@property (nonatomic, weak) id<FaceBoardDelegate> delegate;

@property (nonatomic, strong) UITextField *inputTextField;
@property (nonatomic, strong) UITextView *inputTextView;

+ (FaceBoard*)sharedFaceBoard;

//表情键盘删除键
- (void)backFace;

@end
