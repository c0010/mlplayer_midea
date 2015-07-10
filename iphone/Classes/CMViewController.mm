//
//  CMViewController.m
//  OCplusplus
//
//  Created by sunjj on 11-4-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMViewController.h"
#import "CMMainControl.h"
#import <QuartzCore/QuartzCore.h>
/*
@implementation UINavigationBar(CustomImage)


-(void)drawRect:(CGRect)rect
{
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    
    if (version >= 5.0)
    {
        [self setBackgroundImage:[UIImage imageNamed:@"NaviBg"] forBarMetrics:UIBarMetricsDefault];
        //self.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"NaviBg"]];
        
    }else{
        
        
       // self.navigationController.navigationBar.layer.contents=(id)[UIImage imageNamed:@"top_bar.png"].CGImage;
        self.layer.contents=(id)[UIImage imageNamed:@"NaviBg"].CGImage;
    }
    
    
	//UIImage *BackImage = [UIImage imageNamed: @"NaviBg"];
    //[BackImage drawInRect:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
}


@end
*/
#import "CMImage.h"
@implementation CMViewController

@synthesize titleLabel,bAppStateIsBackground,bIsPush;
@synthesize bIsShowTabbar,bIsShowTagbar;
@synthesize openAutoKeyboard;



static CGFloat sNavibarHeight , sTabbarHeight;

- (CGFloat)navibarHeight{

    if ( sNavibarHeight == 0 ) {
        sNavibarHeight = CGRectGetHeight([[UINavigationController alloc]init].navigationBar.frame);
    }
    
    if ( !self.navigationController.navigationBarHidden ) {
        return sNavibarHeight;
    }
    return 0;
}

- (CGFloat)tabbarHeight{

    if ( sTabbarHeight == 0 ) {
        sTabbarHeight = CGRectGetHeight([[UITabBarController alloc]init].tabBar.frame);
    }
    
    if ( self.bIsShowTabbar ) {
        
        return sTabbarHeight;
    }
    return 0;
}

- (CGFloat)tagbarHeight{
    
    if ( self.bIsShowTagbar ) {
        
        if ( _tagbarHeight == 0 ) {
            return 37.0f;//默认高度37
        }
        return _tagbarHeight;
    }
    return 0;
}

- (void)gotoBack
{
    //首先 判断是否是推送消息
    if (bIsPush) {
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud setObject:@"0" forKey:kUDOpenPush];
        //判断 推送消息的app 状态
    }
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)gotoBackTo:(NSString *)name
{

}

- (void)viewDidLoad {
    [super viewDidLoad];
	//搜索按钮
	UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
	backBtn.frame = CGRectMake(0, 0, kBarItemWidth, kBarItemHeight);
    backBtn.imageEdgeInsets = [self itemFitDifferentVersion:YES];
	[backBtn setImage:[UIImage imageNamed:@"back"] forState:UIControlStateNormal];
	[backBtn addTarget:self action:@selector(gotoBack) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem *backBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
	self.navigationItem.leftBarButtonItem = backBarButtonItem;
    
    
#if ! __has_feature(objc_arc)

    self.titleLabel = [[[UILabel alloc] init] autorelease];
    
# else
    
    self.titleLabel = [[UILabel alloc] init];

# endif

    
    self.titleLabel.frame = CGRectMake(0, 0, 200, 44);
    self.titleLabel.textAlignment = NSTextAlignmentCenter;
    self.titleLabel.backgroundColor = [UIColor clearColor];
    self.titleLabel.textColor = [UIColor blackColor];
    self.titleLabel.font = [UIFont boldSystemFontOfSize:20];;
    
    self.titleLabel.text = self.navigationItem.title;
    self.navigationItem.titleView = self.titleLabel;
    
    self.view.backgroundColor = kColorBackground;
//    if ( __iOS7 ) {
//      
//        if ([self respondsToSelector:@selector(edgesForExtendedLayout)]){
//        
//            self.edgesForExtendedLayout = UIRectEdgeNone;
//            self.automaticallyAdjustsScrollViewInsets = NO;
//            self.extendedLayoutIncludesOpaqueBars = YES;
//        }
//    }else{
//    
//        float barHeight =0;
//        
//        if (![[UIApplication sharedApplication] isStatusBarHidden]) {
//            
//            barHeight+=([[UIApplication sharedApplication] statusBarFrame]).size.height;
//            
//        }
//        
//        if(self.navigationController &&!self.navigationController.navigationBarHidden) {
//            
//            barHeight+=self.navigationController.navigationBar.frame.size.height;
//            
//        }
//        
//        for (UIView *view in self.view.subviews) {
//            
//            
//            
//            if ([self.view isKindOfClass:[UIScrollView class]]) {
//                
//                self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y +barHeight, self.view.frame.size.width, self.view.frame.size.height - barHeight);
//                
//            } else {
//                
//                self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y +barHeight, self.view.frame.size.width, self.view.frame.size.height);
//                
//            }
//            
//        }
//    }
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    
    //开启摇一摇功能时，进入界面，开启摇一摇功能
    if (_openShake)[self becomeFirstResponder];
    

    if (__iOS7){
        if (bIsShowTabbar) {
            self.tabBarController.tabBar.hidden = NO;
            self.hidesBottomBarWhenPushed = NO;
        }
        else{
            self.tabBarController.tabBar.hidden = YES;
            self.hidesBottomBarWhenPushed = YES;
        }
    }
    
    if( openAutoKeyboard ){
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(kKeyboardWillShow:)
                                                     name:UIKeyboardWillShowNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(kKeyboardWillHide:)
                                                     name:UIKeyboardWillHideNotification object:nil];
    }
    
}

- (void)viewWillDisappear:(BOOL)animated {
    //开启摇一摇功能时，退出界面，取消摇一摇功能
    if (_openShake)[self resignFirstResponder];
    
    if( openAutoKeyboard ){
        
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:UIKeyboardWillShowNotification
                                                      object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:UIKeyboardWillHideNotification
                                                      object:nil];
    }
    
    [super viewWillDisappear:animated];
}


- (UIEdgeInsets)itemFitDifferentVersion:(BOOL)leftItem
{
    if (__iOS7)
    {
        //leftItem YES表示左边item NO表示右边item
        if (leftItem)
        {
            return UIEdgeInsetsMake(0, -20, 0, 0);
        }
        else
        {
            return UIEdgeInsetsMake(0, 0, 0, -20);
        }
    }
    else
    {
        return UIEdgeInsetsMake(0, 0, 0, 0);
    }
}

- (UITableViewCell *)buttonSuperCell:(UIButton *)btn
{
    
#if ! __has_feature(objc_arc)
    [btn retain];
    
    for (UIView* next = [btn superview]; next; next = next.superview) {
        if ([next isKindOfClass:[UITableViewCell class]]) {
            return (UITableViewCell*)next;
        }
    }
    
# else
    
    
# endif

    //ios7.0 多了一层view
    if (__iOS7 && !__iOS8)
    {
        return (UITableViewCell *)btn.superview.superview.superview;
        
    }
    else
    {
        return (UITableViewCell *)btn.superview.superview;
    }
}

- (void)setOpenShake:(BOOL)openShake{
    
    _openShake = openShake;
    
    if ( _openShake ) {
        
        [self becomeFirstResponder];
        
        NSString *strAudio = [[NSBundle mainBundle] pathForResource:@"glass" ofType:@"wav"];
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)[NSURL URLWithString:strAudio], &sysSoundID);
    }
}

#pragma mark - shake

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake)
    {
        
    }
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake)
    {
        
    }
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake && _openShake && !CMGlobal::TheOne().IsOffline()
        && SETTING.GetShake())
    {
        UIView *showView = [AppDelegate.window viewWithTag:5201314];
        if (  showView ) {
            [[AppDelegate.window viewWithTag:5201314] removeFromSuperview ];
        }
        
        if ( AppDelegate.m_pImgUp.hidden && AppDelegate.m_pImgUp.hidden ) {
            
            AppDelegate.m_pImgUp.hidden = NO;
            AppDelegate.m_pImgDown.hidden = NO;
            
            [UIView animateWithDuration:0.5f animations:^{
                
                CGRect upframe = AppDelegate.m_pImgUp.frame;
                upframe.origin.y = 0;
                AppDelegate.m_pImgUp.frame = upframe;
                
                CGRect downframe = AppDelegate.m_pImgDown.frame;
                downframe.origin.y = UI_IOS_WINDOW_HEIGHT/2;
                AppDelegate.m_pImgDown.frame = downframe;
                
            } completion:^(BOOL finished) {
                
                if ( finished ) {
                    
                    AudioServicesPlaySystemSound(sysSoundID);
                    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
                    
                    [self performSelector:@selector(backtoSetup) withObject:nil afterDelay:0.3];
                    
                }
            }];
        }
    }
}

- (void) backtoSetup{
    
    [UIView animateWithDuration:0.5f animations:^{
        
        CGRect upframe = AppDelegate.m_pImgUp.frame;
        upframe.origin.y = - (UI_IOS_WINDOW_HEIGHT/2);
        AppDelegate.m_pImgUp.frame = upframe;
        
        CGRect downframe = AppDelegate.m_pImgDown.frame;
        downframe.origin.y = UI_IOS_WINDOW_HEIGHT;
        AppDelegate.m_pImgDown.frame = downframe;
        
    } completion:^(BOOL finished) {
        
        if ( finished ) {
            
            AppDelegate.m_pImgUp.hidden = YES;
            AppDelegate.m_pImgDown.hidden = YES;
            
            if ( [self respondsToSelector:@selector(gotoShake)] ) {
                [self gotoShake];
            }
        }
    }];
}

- (void)kKeyboardWillShow:(NSNotification *)aNotification
{
    if ( [self respondsToSelector:@selector(keyboardWillShow:)] ) {
        [self keyboardWillShow:aNotification];
    }
}

- (void)kKeyboardWillHide:(NSNotification *)aNotification
{
    if ( [self respondsToSelector:@selector(keyboardWillHide:)] ) {
        [self keyboardWillHide:aNotification];
    }
}



@end
