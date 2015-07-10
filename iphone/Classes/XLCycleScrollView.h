//
//  XLCycleScrollView.h
//
//  Created by Tim on 12/10/19.
//  Copyright (c) 2012 wunding. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol XLCycleScrollViewDelegate;
@protocol XLCycleScrollViewDatasource;

@interface XLCycleScrollView : UITableViewCell<UIScrollViewDelegate>
{
    UIScrollView *_scrollView;
    UIPageControl *_pageControl;
    
    id<XLCycleScrollViewDelegate> __weak _delegate;
    id<XLCycleScrollViewDatasource> __weak _datasource;
    
    NSInteger _totalPages;
    NSInteger _curPage;
    
    NSMutableArray *_curViews;
	BOOL    pagecontrolcenter;
}

@property (nonatomic,readonly) UIScrollView *scrollView;
@property (nonatomic,readonly) UIPageControl *pageControl;
@property (nonatomic,assign) NSInteger currentPage;
@property (nonatomic,weak,setter = setDataource:) id<XLCycleScrollViewDatasource> datasource;
@property (nonatomic,weak,setter = setDelegate:) id<XLCycleScrollViewDelegate> delegate;
@property (nonatomic,assign) BOOL pagecontrolcenter;

- (void)reloadData;
- (void)loadData;
- (int)validPageValue:(NSInteger)value;
- (void)addpage:(NSInteger)page posindex:(NSInteger)index;
- (void)layoutSubviews;
@end

@protocol XLCycleScrollViewDelegate <NSObject>

@optional
- (void)didClickPage:(XLCycleScrollView *)csView atIndex:(NSInteger)index;

@end

@protocol XLCycleScrollViewDatasource <NSObject>

@required
- (NSInteger)numberOfPages;
- (UIView *)pageAtIndex:(NSInteger)index;

@end
