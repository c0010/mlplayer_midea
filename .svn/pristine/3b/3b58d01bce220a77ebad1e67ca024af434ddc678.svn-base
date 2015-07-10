//
//  CMShareDialog.m
//  MLPlayer
//
//  Created by water on 14-6-30.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMAlertView.h"
#import "tool.h"
#import "CMImage.h"
#import "MLPlayerAppDelegate.h"
#import "SDWebImage/UIImageView+WebCache.h"

#define WINDOW_COLOR                            [UIColor colorWithRed:0 green:0 blue:0 alpha:0.4]
#define TEXT_SPACING_X                           20
#define ANIMATE_DURATION                        0.25f
#define BACKGROUND_WIDTH                        280
#define BACKGROUND_HEIGHT                       175
#define BACKGROUND_COLOR                        [UIColor colorWithRed:245.0f/255.0f green:245.0f/255.0f blue:245.0f/255.0f alpha:1.0f]
#define DESC_MAXHEIGHT                          100

#define TitleMaxHeight                          100
#define MessageMaxHeigth                        200

#define ButtonWidth                             44


@interface CMAlertView ()

@property (nonatomic,strong) UIView *backGroundView,*shadowView;
@property (nonatomic,assign) BOOL isHadImage;

@end


@implementation CMAlertView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void) initWithSubView{

    alertLevelWindow = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    alertLevelWindow.windowLevel = UIWindowLevelAlert;
    alertLevelWindow.backgroundColor = [UIColor clearColor];
    
    self.frame = alertLevelWindow.bounds;
    self.backgroundColor = [UIColor clearColor];
    self.userInteractionEnabled = YES;
    
    
    self.shadowView = [[UIView alloc]initWithFrame:alertLevelWindow.bounds];
    self.shadowView.backgroundColor = WINDOW_COLOR;
    self.shadowView.alpha = 0.f;
    
    tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tappedCancel)];
    [self.shadowView addGestureRecognizer:tapGesture];
    
    [self addSubview:self.shadowView];
    
    origin_y = 20;
    
}

- (void)setDisabledOutSide:(BOOL)disabledOutSide{

    if (disabledOutSide && tapGesture) {
        
        [self.shadowView removeGestureRecognizer:tapGesture];
    }
}

- (instancetype)initWithTitle:(NSString *)cm_title message:(NSString *)cm_message cancelButtonTitle:(NSString *)cancelButtonTitle otherButtonTitles:(NSString *)otherButtonTitles completionBlock:(CompletionBlock)block
{
    
    self = [super init];
    if (self) {
        
        [self initWithSubView];
        
        self.completionBlock = block;
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(keyboardWillShow:)
                                                     name:UIKeyboardWillShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(dismissKeyboard)
                                                     name:UIKeyboardWillHideNotification object:nil];
        
        self.contentView = [[UIView alloc] initWithFrame:CGRectZero];
        self.contentView.backgroundColor =  UIColorRGB(0xf5f5f5);
        self.contentView.center = self.center;
        self.contentView.layer.masksToBounds = YES;
        self.contentView.layer.cornerRadius = 2.f;
        
        
        CGFloat titleWidth = BACKGROUND_WIDTH - 2 * TEXT_SPACING_X;

        title = cm_title;
        if (title) {
            
            titleLabel = [[UILabel alloc]initWithFrame:CGRectZero];
            titleLabel .backgroundColor = [UIColor clearColor];
            titleLabel .text = title;
            titleLabel.textAlignment = NSTextAlignmentCenter;
            titleLabel .textColor = [UIColor blackColor];
            titleLabel.numberOfLines = 0;
            titleLabel.lineBreakMode = NSLineBreakByWordWrapping|NSLineBreakByTruncatingTail;
            titleLabel .font = [UIFont boldSystemFontOfSize:15.f];
            
            CGSize size = [title sizeWithFont:titleLabel.font constrainedToSize:CGSizeMake(titleWidth, TitleMaxHeight) lineBreakMode:NSLineBreakByWordWrapping];
            titleLabel.frame = CGRectMake(TEXT_SPACING_X, origin_y, titleWidth, size.height);
            [self.contentView addSubview:titleLabel];
            
            origin_y = origin_y + 10 + CGRectGetHeight(titleLabel.frame);

        }
       
        message = cm_message;

        if (message) {
            
            messageLabel = [[UILabel alloc]initWithFrame:CGRectZero];
            messageLabel.backgroundColor = [UIColor clearColor];
            messageLabel.text = message;
//            self.messageLabel.textColor = UIColorRGB(0xa4a4a4);
            messageLabel.textColor = [UIColor blackColor];

            messageLabel.font = [UIFont systemFontOfSize:14.f];
            messageLabel.numberOfLines = 0;
            messageLabel.textAlignment = NSTextAlignmentCenter;
            messageLabel.lineBreakMode = NSLineBreakByWordWrapping|NSLineBreakByTruncatingTail;
            
            CGSize descSize = [message sizeWithFont:messageLabel.font constrainedToSize:CGSizeMake(titleWidth, MessageMaxHeigth) lineBreakMode:NSLineBreakByWordWrapping];
            messageLabel.frame = CGRectMake(TEXT_SPACING_X, origin_y, titleWidth, descSize.height);
            
            [self.contentView addSubview:messageLabel];
            
            
            origin_y = origin_y + CGRectGetHeight(messageLabel.frame);
        }
   
        origin_y = origin_y + 20;
        
        CGFloat otherBtnWidth = BACKGROUND_WIDTH + 2;
        CGFloat otherBtnX = 0;

        if (cancelButtonTitle) {
            
            cancleButton = [UIButton buttonWithType:UIButtonTypeCustom];
            cancleButton.frame = CGRectMake(-1, origin_y, BACKGROUND_WIDTH / 2 + 2, ButtonWidth);
            [cancleButton setTitle:cancelButtonTitle forState:UIControlStateNormal];
//            [cancleButton setTitleColor:UIColorRGB(0xa4a4a4) forState:UIControlStateHighlighted];
            [cancleButton setTitleColor:kColorForeground forState:UIControlStateNormal];

            cancleButton.titleLabel.font = [UIFont systemFontOfSize:18.f];
            cancleButton.tag = BUTTON_CANCEL_TAG;
            [cancleButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0xf5f5f5)] forState:UIControlStateNormal];
            [cancleButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0xe1e1e1)]forState:UIControlStateHighlighted];
            [cancleButton addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
            cancleButton.layer.borderColor = UIColorRGB(0xdcdcdc).CGColor;
            cancleButton.layer.borderWidth = 0.8f;
            
            [self.contentView addSubview:cancleButton];
            
            otherBtnWidth = (BACKGROUND_WIDTH + 2) / 2;
            otherBtnX = BACKGROUND_WIDTH / 2;
        }
        
        confirmButton = [UIButton buttonWithType:UIButtonTypeCustom];
        confirmButton.frame = CGRectMake(otherBtnX, origin_y, otherBtnWidth, ButtonWidth);
        [confirmButton setTitle:otherButtonTitles forState:UIControlStateNormal];
        [confirmButton setTitleColor:kColorForeground forState:UIControlStateNormal];
        confirmButton.tag = BUTTON_CONFIRM_TAG;
        confirmButton.titleLabel.font = [UIFont systemFontOfSize:18.f];
        [confirmButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0xf5f5f5)] forState:UIControlStateNormal];
        [confirmButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0xe1e1e1)]forState:UIControlStateHighlighted];
        [confirmButton addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
        confirmButton.layer.borderColor = UIColorRGB(0xdcdcdc).CGColor;
        confirmButton.layer.borderWidth = 0.8f;
        
        [self.contentView addSubview:confirmButton];
        
        origin_y = origin_y  + CGRectGetHeight(confirmButton.frame);
        
        [self.contentView setFrame:CGRectMake(0, 0, BACKGROUND_WIDTH, origin_y)];
        self.contentView.center = self.center;
        
        [self addSubview:self.contentView];
        
        [UIView animateWithDuration:ANIMATE_DURATION animations:^{
            self.shadowView.alpha = 1.0;
        }];
        
    }
    return self;
    
}

- (void)setCustomView:(UIView *)customView
{

    customView.frame = CGRectMake((BACKGROUND_WIDTH  - CGRectGetWidth(customView.frame)) / 2, origin_y - ButtonWidth -((origin_y > ButtonWidth + 40) ? 0 : 20) , CGRectGetWidth(customView.frame), CGRectGetHeight(customView.frame));
    
    [self.contentView addSubview:customView];
    
    if (cancleButton) {
        [cancleButton setFrameY:CGRectGetMaxY(customView.frame) + 20];
    }
    
    [confirmButton setFrameY:CGRectGetMaxY(customView.frame) + 20];
    [self.contentView setFrameHeight:CGRectGetMaxY(confirmButton.frame)];
    self.contentView.center = self.center;
    
    
}

- (UIView *)customShareViewWithTitle:(NSString *)cm_title message:(NSString *)cm_message imageUrl:(NSString *)imgaeUrl isQa: (BOOL)isQa
{
    
    __autoreleasing UIView *customView = [[UIView alloc]initWithFrame:CGRectZero];
    customView.backgroundColor = [UIColor clearColor];
    customView.userInteractionEnabled = YES;
    
    UIImageView *imageview = [[UIImageView alloc]initWithFrame:CGRectMake(10, 0, 70, 70)];
    if (!isQa) {
        [imageview sd_setImageWithURL:[NSURL URLWithString:imgaeUrl] placeholderImage:[UIImage imageNamed:@"ulp"]];
    }else{
        [imageview setImage:[UIImage imageNamed:@"qashare"]];
    }
    imageview.backgroundColor = [UIColor clearColor];
    [customView addSubview:imageview];
    
    CGFloat origin_x = CGRectGetWidth(imageview.frame) + 20;
    
    UILabel *cm_titleLabel = [[UILabel alloc]initWithFrame:CGRectMake(origin_x, 0 , BACKGROUND_WIDTH - origin_x - 10, 18)];
    cm_titleLabel .backgroundColor = [UIColor clearColor];
    cm_titleLabel .text = cm_title;
    cm_titleLabel .textColor = UIColorRGB(0x4a4a4a);
    cm_titleLabel .font = [UIFont systemFontOfSize:15.f];
    [customView addSubview:cm_titleLabel];

    UILabel *cm_messageLabel = [[UILabel alloc]initWithFrame:CGRectZero];
    cm_messageLabel.backgroundColor = [UIColor clearColor];
    cm_messageLabel.text = cm_message;
    cm_messageLabel.textColor = UIColorRGB(0xa4a4a4);
    cm_messageLabel.font = [UIFont systemFontOfSize:13.f];
    cm_messageLabel.numberOfLines = 0;
    cm_messageLabel.lineBreakMode = NSLineBreakByWordWrapping|NSLineBreakByTruncatingTail;
    
    CGFloat c_origin_y;
    
    c_origin_y = CGRectGetMaxY(cm_titleLabel.frame) + 7;
    
    CGSize descSize = [cm_message sizeWithFont:cm_messageLabel.font constrainedToSize:CGSizeMake(CGRectGetWidth(cm_titleLabel.frame), 50) lineBreakMode:NSLineBreakByWordWrapping];
    cm_messageLabel.frame = CGRectMake(origin_x, c_origin_y , BACKGROUND_WIDTH - origin_x - 10, descSize.height);
    
    [customView addSubview:cm_messageLabel];
    
    c_origin_y = CGRectGetHeight(imageview.frame) + 20;

    self.isAddFaceView = YES;

    UIView *textFieldBackView = [self customTextFieldWithPlaceholder:I(@"说点什么")];
    [textFieldBackView setFrameY:c_origin_y];
    
    [customView addSubview:textFieldBackView];
    
    c_origin_y = c_origin_y + CGRectGetHeight(textFieldBackView.frame);
    
    customView.frame = CGRectMake(0, 0, BACKGROUND_WIDTH, c_origin_y);

    return customView;
}


- (UIView *)customTextFieldWithPlaceholder:(NSString *)placeholder
{

    __autoreleasing UIView *textFieldBackView = [[UIView alloc]initWithFrame:CGRectMake(10, 0 , BACKGROUND_WIDTH - 20, 34)];
    textFieldBackView.backgroundColor = UIColorRGB(0xfbfbfb);
    textFieldBackView.userInteractionEnabled = YES;
    textFieldBackView.layer.masksToBounds = YES;
    textFieldBackView.layer.cornerRadius = 2.f;
    textFieldBackView.layer.borderColor = UIColorRGB(0xdcdcdc).CGColor;
    textFieldBackView.layer.borderWidth = 0.5f;
    
    self.textfield = [[UITextField alloc]initWithFrame:CGRectMake(5, 2,BACKGROUND_WIDTH - 30 ,30)];
    self.textfield.font = [UIFont systemFontOfSize:16.f];
    self.textfield.placeholder = placeholder;
    self.textfield.returnKeyType = UIReturnKeyDone;
    self.textfield.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.textfield.clearButtonMode = UITextFieldViewModeWhileEditing;
    self.textfield.backgroundColor = [UIColor clearColor];
    self.textfield.delegate = self;
    [self.textfield addTarget:self action:@selector(textfieldreturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    
    [textFieldBackView addSubview:self.textfield];
    
    if (self.isAddFaceView) {
        
        barView=[[UIImageView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT, 320, 35)];
        barView.backgroundColor = UIColorRGB(0xfbfbfb);
        barView.userInteractionEnabled = YES;
        
        avatarBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [avatarBtn setFrame:CGRectMake(10, 5, 25, 25)];
        [avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
        [avatarBtn addTarget:self action:@selector(avatarBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
        [barView addSubview:avatarBtn];
        
        faceBoardView = [[UIImageView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT, 320,216)];
        faceBoardView.backgroundColor = [UIColor redColor];
        faceBoardView.userInteractionEnabled = YES;
        
        faceBoard = [[FaceBoard alloc]initWithFrame:faceBoardView.bounds];
        faceBoard.delegate = self;
        faceBoard.inputTextField = self.textfield;
        [faceBoardView addSubview:faceBoard];
        
        [self addSubview:barView];
        [self addSubview:faceBoardView];
    }
    return textFieldBackView;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string{

    if (self.isAddFaceView) {
        if([string isEqualToString:@""]){
            
            [faceBoard backFace];
            
            return NO;
        }
    }
    
    return YES;
}

- (void)keyboardWillShow:(NSNotification *)aNotification {
    NSDictionary* info=[aNotification userInfo];
    keyBoardHieght=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size.height;
    
    [UIView animateWithDuration:ANIMATE_DURATION animations:^{
        
        CGFloat contentMinY = CGRectGetMaxY(self.contentView.frame);

        CGFloat remainHeight = UI_IOS_WINDOW_HEIGHT - keyBoardHieght;
        
        if (self.isAddFaceView) {
            
            remainHeight -= 35;
            
            [barView setFrameY:UI_IOS_WINDOW_HEIGHT - keyBoardHieght - 35];
        }
        
        
        [self.contentView setFrameY:CGRectGetMinY(self.contentView.frame) - (contentMinY - remainHeight) - 10];
    }];
}

-(void)dismissKeyboard
{
    [UIView animateWithDuration:ANIMATE_DURATION animations:^{
        
        if (!self.isAddFaceView) {
            self.contentView.center = self.center;
        }

    }];
}

- (void)avatarBtnPressed:(UIButton *)sender{
    
    sender.selected = !sender.selected;
    [UIView animateWithDuration:ANIMATE_DURATION animations:^{
        
        if(sender.selected){
            [sender setImage:[UIImage imageNamed:@"interact_keyboard_btn_normal"] forState:UIControlStateNormal];
            
            [self.textfield resignFirstResponder];
            
            [faceBoardView setFrameY:UI_IOS_WINDOW_HEIGHT - 216];
            [barView setFrameY:UI_IOS_WINDOW_HEIGHT - 216 - 35];
            
        }else{
            
            [sender setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
            
            [self.textfield becomeFirstResponder];
            
            [faceBoardView setFrameY:UI_IOS_WINDOW_HEIGHT];
            [barView setFrameY:UI_IOS_WINDOW_HEIGHT - keyBoardHieght - 35];

        }
    }];
}

- (void)buttonPressed:(UIButton *)sender{

    [self tappedCancel];

    if (self.completionBlock) {
        self.completionBlock(sender.tag,self);
        self.completionBlock = nil;
    }
}

- (void)textfieldreturn:(UITextField *)sender{
    
    if (self.isAddFaceView) {
        [UIView animateWithDuration:0.3 animations:^{
            [faceBoardView setFrameY:UI_IOS_WINDOW_HEIGHT];
            [barView setFrameY:UI_IOS_WINDOW_HEIGHT];
        }];
    }
    
    [UIView animateWithDuration:ANIMATE_DURATION animations:^{
        self.contentView.center = self.center;
    }];
    
    [sender resignFirstResponder];
}

- (void)show{
    
    [alertLevelWindow addSubview:self];
    
    [alertLevelWindow makeKeyAndVisible];
}

- (void)tappedCancel
{
    [self.textfield resignFirstResponder];
    [UIView animateWithDuration:ANIMATE_DURATION animations:^{
        self.shadowView.alpha = 0.f;
        self.contentView.alpha = 0.f;
    } completion:^(BOOL finished) {
        
        if (finished) {
            [self removeFromSuperview];
            
            alertLevelWindow.windowLevel = UIWindowLevelNormal;
            
            MLPlayerAppDelegate* appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
            [appDelegate.window makeKeyAndVisible];

        }
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }];
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
