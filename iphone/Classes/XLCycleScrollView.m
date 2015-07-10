//
//  XLCycleScrollView.m
//
//  Created by Tim on 12/10/19.
//  Copyright (c) 2012 wunding. All rights reserved.

#import "XLCycleScrollView.h"

@implementation XLCycleScrollView

@synthesize scrollView = _scrollView;
@synthesize pageControl = _pageControl;
@synthesize currentPage = _curPage;
@synthesize datasource = _datasource;
@synthesize delegate = _delegate;
@synthesize pagecontrolcenter;


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        [self setFrame:frame];
        _scrollView = [[UIScrollView alloc] initWithFrame:self.bounds];
        
        
        _scrollView.delegate = self;
        _scrollView.contentSize = CGSizeMake(self.bounds.size.width * 3, self.bounds.size.height);
        
        _scrollView.showsHorizontalScrollIndicator = NO;
        _scrollView.contentOffset = CGPointMake(self.bounds.size.width, 0);
        _scrollView.pagingEnabled = YES;
        [self addSubview:_scrollView];
        
        CGRect rect = self.bounds;
        rect.origin.y = rect.size.height - 30;
        rect.size.height = 30;
        _pageControl = [[UIPageControl alloc] initWithFrame:rect];
        _pageControl.userInteractionEnabled = NO;
		_pageControl.backgroundColor = [UIColor clearColor];
        
        [self addSubview:_pageControl];
        
        _curPage = 0;
		pagecontrolcenter = false;
    }
    return self;
}

- (void)setDataource:(id<XLCycleScrollViewDatasource>)datasource
{
    _datasource = datasource;
}

- (void)reloadData
{
    _totalPages = [_datasource numberOfPages];
    if (_totalPages == 0) 
        return;
	_curPage = 0;
    _pageControl.numberOfPages = _totalPages;
    [self loadData];
}

- (void)loadData
{
    
    _pageControl.currentPage = _curPage;
    
    //从scrollView上移除所有的subview
    NSArray *subViews = [_scrollView subviews];
    if([subViews count] != 0) {
        [subViews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
	if (!_curViews)
        _curViews = [[NSMutableArray alloc] init];
    [_curViews removeAllObjects];
	
	if(_pageControl.numberOfPages == 1)
		[self addpage:_curPage posindex:0];
	else 
	{
		int pre = [self validPageValue:_curPage-1];
		int last = [self validPageValue:_curPage+1];
		[self addpage:_curPage posindex:1];
		[self addpage:pre posindex:0];
		[self addpage:last posindex:2];
	}
	int cn = _pageControl.numberOfPages >1 ?1:0;
    [_scrollView setContentOffset:CGPointMake(_scrollView.frame.size.width*cn, 0)];
}

- (void)addpage:(NSInteger)page posindex:(NSInteger)index
{
	UIView* v = [_datasource pageAtIndex:page];
	if(v == nil)
		return;
	[_curViews addObject:v];
    
	v.userInteractionEnabled = YES;
    
	UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self	action:@selector(handleTap:)];
	[v addGestureRecognizer:singleTap];
    
	v.frame = CGRectOffset(v.frame, v.frame.size.width * index, 0);
	[_scrollView addSubview:v];
}

- (int)validPageValue:(NSInteger)value {
    
    if(value == -1) value = _totalPages - 1;
    if(value == _totalPages) value = 0;
    
    return value;
    
}
- (void)layoutSubviews
{
	int cn = 3;
	if([_datasource numberOfPages] <= 1)
		cn = 1;
	CGRect rect = self.bounds;
	_scrollView.frame =rect;
	_scrollView.contentSize = CGSizeMake(rect.size.width * cn, rect.size.height);
	rect.origin.y = rect.size.height - 30;
	rect.size.height = 30;
	rect.size.width = _pageControl.numberOfPages*15;
	if(!pagecontrolcenter)
		rect.origin.x = self.bounds.size.width - rect.size.width-10;
	else
		rect.origin.x = (self.bounds.size.width - rect.size.width)/2;
	_pageControl.frame = rect;
}

- (void)handleTap:(UITapGestureRecognizer *)tap {
    
    if ([_delegate respondsToSelector:@selector(didClickPage:atIndex:)]) {
        [_delegate didClickPage:self atIndex:_curPage];
    }
    
}
#pragma mark - UIScrollViewDelegate
- (void)scrollViewDidScroll:(UIScrollView *)aScrollView {
   int x = aScrollView.contentOffset.x;
    //往下翻一张
    if(x >= (2*self.frame.size.width)) {
        _curPage = [self validPageValue:_curPage+1];
        [self loadData];
    }
    
    //往上翻
    if(x <= 0) {
        _curPage = [self validPageValue:_curPage-1];
        [self loadData];
    }
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)aScrollView {
	
	int cn = _pageControl.numberOfPages >1 ?1:0;
    [_scrollView setContentOffset:CGPointMake(_scrollView.frame.size.width*cn, 0) animated:YES];
}

@end
