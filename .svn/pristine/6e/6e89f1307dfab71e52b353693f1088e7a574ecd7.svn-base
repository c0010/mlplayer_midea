//
//  CMHomeControl.h
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import "cmcommon.h"
#import "CMImage.h"
#import "CMBrowserView.h"
#import "UIGridView.h"
#import "UIGridViewDelegate.h"
#import "LPanelTableview.h"
#import "MLPlayerAppDelegate.h"
#import "tool.h"
#import "CMTrainListView.h"


@class ImageRightButton;
class CMBrowserGetImageListener;
@interface CMBrowserControl : CMViewController <UITableViewDataSource,UITableViewDelegate,UIGridViewDelegate,UIGestureRecognizerDelegate,CMNavgateItemDelegate>{
    
	UISegmentedControl* segmentedControl;
	UIImageView *SegmentBgView;
    
    UITableView *m_pTableView; // 滑动标签
    NSInteger nSelectRow;
    UIImageView *selview; //tab滑动指示
    CGRect preRect;

	CMBrowserView* browserview;
    CMTrainListView *trainlistview;
	
	MLPlayerAppDelegate *appDelegate;
    UITableView *popDowntablview;
	
	char	m_sFlag[16];
    NSMutableArray *popDownArr;
    UIGridView *gridView;
	

	CMCategoryItem* m_pCategoryItem;
	CMBrowserGetImageListener* m_pListener;
	CMWebImage* m_pWebImage;
		
    UIView *m_pImgUp;
    UIView *m_pImgDown;
    BOOL upImgHidden;
    BOOL downImgHidden;
    
    BOOL upAnimation;
    BOOL downAnimaiton;
    BOOL animationDone;
}
@property(nonatomic,strong)	UIGridView * gridView;
@property(nonatomic,strong) UIButton *leftButton;
@property (nonatomic, strong) UIViewController* navigationControllerDelegate;

//-(void)slideView:(UIView*)v translate:(CGPoint)translate;
//-(void)slideViewToX:(UIView*)v xCoordinate:(int)x;

//-(void)completeSlide;
//-(void)undoSlide;

-(void)onAppFocus:(BOOL)isForeground;
-(void)setFlag:(const char*)sflag;
- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap;
//-(void)slideView:(UIView*)v translate:(CGPoint)translate;

- (void)reset;

- (void)scrollToTop;
//- (void)stopScrolling;
- (void)setCurrentPos:(NSInteger)index;
- (void)autoRefresh;
- (void)reloadTableViewList;
- (void)scrollToTop;
@end

class CMBrowserGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMBrowserControl* browser = (__bridge CMBrowserControl*)UserData;
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
			browser.gridView.tag = 1;
		}else {
			//[tool ShowError:Result];			
		}
	}
};



