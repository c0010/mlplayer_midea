//
//  cmitemcontroller.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//
//  Modified by 廖宏兴  on 2015.4.28
// 用SVPullToRefresh替代 EGORefreshHeaderTableView 实现列表的上拉刷新功能。
// 此类有点复杂，且是学习、资讯、问答、培训报名、培训签到等模块的界面的父类，且涉及上拉下载更多的功能。需重点测试查bug。


#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMClassTableViewCell.h"
#import "CMTableView.h"
#import "CMImage.h"
#import "CMNavgateItem.h"

@interface CMRefreshMoreView : UIView<UITableViewDelegate,UITableViewDataSource> {
	
	UIButton* btnMore;
    UIActivityIndicatorView *activityView;
    
	CMTableView* tableviewlist;
	BOOL  m_bHasMore;
    
    UIView* bgview;
    

}
@property(nonatomic,assign)BOOL HasMore;
@property(nonatomic,strong)CMTableView* tableviewlist;
@property(nonatomic,assign)BOOL isUseCache;
-(id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh;
-(void)GetBrowserList;
-(void)RequestMore:(UITableViewCell*)cell;
-(void)RefreshList;
-(BOOL)RefreshMore;
-(void)automaticRefresh;
-(void)automaticRefreshUseCache:(BOOL)useCache;
- (void)stopRefreshingMore;
@end