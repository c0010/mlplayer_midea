//
//  CMSliderBrowseController.h
//  MLPlayer
//
//  Created by hushengwu on 14-6-11.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "QCSlideSwitchView.h"
#import <AudioToolbox/AudioToolbox.h>
#import "cmsettings.h"
#import "cmcommon.h"
#import "CMImage.h"
#import "CMBrowserView.h"
#import "MLPlayerAppDelegate.h"
#import "tool.h"
#import "CMSubscribeView.h"

@class CMBrowserControl;
@interface CMSliderBrowseController : CMViewController<QCSlideSwitchViewDelegate,QCSlideSwitchViewDataSource,UIGestureRecognizerDelegate>{
    char	m_sFlag[16];
    CMCategoryItem* m_pCategoryItem;
    
    NSInteger viewCounts;

    QCSlideSwitchView *_slideSwitchView;
    
}
@property (nonatomic, strong) IBOutlet QCSlideSwitchView *slideSwitchView;
@property(nonatomic,assign)BOOL bIsPush;

@property (nonatomic, strong) CMSubscribeView *subscribeView;
//@property (nonatomic, strong) UIView *coverView;

@property(nonatomic,assign)     NSInteger viewIndex;

@property(nonatomic,strong) UIButton *leftButton;


-(void)setFlag:(const char*)sflag;
- (void)reset;
- (void)loadShakeDate;
- (void)shakeToDetail;
- (void)scrollToTop;
//- (void)stopScrolling;

@end
