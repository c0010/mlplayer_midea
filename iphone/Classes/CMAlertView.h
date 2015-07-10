//
//  CMShareDialog.h
//  MLPlayer
//
//  Created by water on 14-6-30.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FaceBoard.h"

@class CMAlertView;

#define BUTTON_CANCEL_TAG                       100
#define BUTTON_CONFIRM_TAG                      101

static const int CMAlertViewCancel =  BUTTON_CANCEL_TAG;//取消按钮的标志
static const int CMAlertViewOk  =  BUTTON_CONFIRM_TAG;

typedef void (^CompletionBlock)(NSUInteger buttonIndex, CMAlertView *alertView);

@interface CMAlertView : UIView<FaceBoardDelegate,UITextFieldDelegate>
{
    CGFloat keyBoardHieght;
    
    UIWindow *alertLevelWindow;
    
    NSString *title;
    
    NSString *message;
    
    CGFloat origin_y;
    
    UIButton *cancleButton,*confirmButton;
        
    UIButton *avatarBtn;
    UIImageView* barView,*faceBoardView;

    
    UILabel *titleLabel;//标题
    
    UILabel *messageLabel;//内容

    UITapGestureRecognizer *tapGesture;
    
    FaceBoard *faceBoard;
}

@property (nonatomic,strong) UITextField *textfield;//默认输入框

@property (nonatomic,strong) CompletionBlock completionBlock;//事件回调

@property (nonatomic,strong) UIView *contentView;

@property (nonatomic,strong) UIView *customView;//添加自定义view

@property (nonatomic,assign) BOOL isAddFaceView;//是否添加表情

@property (nonatomic,assign) BOOL disabledOutSide;//是否可以点击阴影，使对话框消失



- (instancetype) initWithTitle:(NSString *)cm_title message:(NSString *)cm_message cancelButtonTitle:(NSString *)cancelButtonTitle otherButtonTitles:(NSString *)otherButtonTitles completionBlock:(CompletionBlock)block;

//生成自定义分享课件,问答的view
- (UIView *)customShareViewWithTitle:(NSString *)cm_title message:(NSString *)cm_message imageUrl:(NSString *)imgaeUrl isQa: (BOOL)isQa;
//生成默认textfield
- (UIView *) customTextFieldWithPlaceholder:(NSString *)placeholder;

- (void)show;

@end