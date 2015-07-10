//
//  CMViewController.h
//  OCplusplus
//
//  Created by sunjj on 11-4-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "tool.h"
#import "MLPlayerAppDelegate.h"
#import "CMRationViewController.h"
#import <AudioToolbox/AudioToolbox.h>

@interface CMViewController : CMRationViewController<UINavigationBarDelegate> {

    SystemSoundID sysSoundID;

}

@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, assign) BOOL bAppStateIsBackground;
@property (nonatomic, assign) BOOL bIsPush;
@property (nonatomic, assign) BOOL bIsShowTabbar;   //是否显示tabbar
@property (nonatomic, assign) BOOL bIsShowTagbar;   //是否显示tagbar标签栏
@property (nonatomic, assign) CGFloat tabbarHeight;   //tabbar高度
@property (nonatomic, assign) CGFloat tagbarHeight;   //tagbar标签栏高度
@property (nonatomic, assign) CGFloat navibarHeight;   //导航栏高度

@property (nonatomic, assign) BOOL openShake;  //是否开启摇一摇功能
@property (nonatomic, assign) BOOL openAutoKeyboard;  //是否开启键盘自动监听

//摇一摇事件处理，供子类覆写
- (void) gotoShake;

//开启键盘监听，供子类覆写
- (void)keyboardWillHide:(NSNotification *)aNotification;
- (void)keyboardWillShow:(NSNotification *)aNotification;


//返回到上一界面
- (void)gotoBack;

//返回到某一界面
//- (void)gotoBackTo:(NSString *)name;

//跳转到
- (void)gotoTop;

- (UIEdgeInsets)itemFitDifferentVersion:(BOOL)leftItem;

//从button索引到TableCell
- (UITableViewCell *)buttonSuperCell:(UIButton *)btn;

//回到最顶端
- (void)scrollToTop;
@end
