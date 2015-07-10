//
//  CMMainControl.h
//  iphone_Learning
//
//  tabbar 

//  Created by sunjj on 11-4-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "LPanelTableview.h"

@class CMLeftView;


@interface CustomTabBarItem : UITabBarItem
{
	UIImage *HighlightedImage;
}

@property(nonatomic,strong) UIImage *HighlightedImage;

@end

@interface CMMainControl : UITabBarController<UIGestureRecognizerDelegate>{

	UINavigationController *learnNavigationController; 
	UINavigationController *newsNavigationController; 
	UINavigationController *interactNavigationController; 
	UINavigationController *appNavigationController; 
	UINavigationController *knowledgeNavigationController;
    UINavigationController *examNavController;
    UINavigationController *qaNavController;
    UINavigationController *mycenterController;
    
    BOOL bIsPush;
    
    UIImageView *examTips;
    UIImageView *moreTips;
    
    NSString *strExam;
    NSString *strMore;
    
    UITapGestureRecognizer *_tapGestureRec;
    UIPanGestureRecognizer *_panGestureRec;
    
    UIView *_mainContentView;    //中间视图滑动载体
    CMLeftView *_leftSideView;       //左边菜单
    UIButton *_centerButton;     //响应中间视图点击
    UIImageView *bgView;
    
}
@property (nonatomic,strong)UIImageView *moreTips;
@property (nonatomic,assign)BOOL bIsPush;

//@property(nonatomic,strong)UIView *LeftSideView;
@property (nonatomic, assign) BOOL canShowLeft;   //是否设置左边菜单
@property (nonatomic, assign) BOOL showingLeft;   //左边菜单打开/隐藏
@property (nonatomic, assign) CGFloat LeftSCloseDuration;  //动画关闭时间
@property (nonatomic, assign) CGFloat LeftSOpenDuration;   //动画开始时间

@property (nonatomic, assign) CGFloat LeftSContentScale;   //缩放尺寸
@property (nonatomic, assign) CGFloat LeftSContentOffset;  //滑动距离
@property (nonatomic, assign) CGFloat LeftSJudgeOffset;    //手势弹回边界

@property (nonatomic, assign) CGFloat minScaleLeftView;  //左视图缩放动画最小比列
@property (nonatomic, assign) CGFloat minAlphaLeftView;  //左视图缩放动画透明度

@property (nonatomic, strong) UINavigationController *learnNavigationController;


- (void)moveViewWithGesture:(UIPanGestureRecognizer *)panGes;   //缩放手势

- (void)isForbidGesture:(BOOL)isForbid;   //禁止手势

- (void)openSideBar;

- (void)closeSideBar;

//-(void)setNarBarBtn:(id)sender;
-(void)gotoPlay:(id)sender;
-(id)init;
- (void)setNoHighlightTabBar;
@end 