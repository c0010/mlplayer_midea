
//
//  QCSlideSwitchView.m
//  QCSliderTableView
//
//  Created by “ hsw on 14-4-16.
//  Copyright (c) 2014年 Scasy. All rights reserved.
//

#import "QCSlideSwitchView.h"
#import "tool.h"
#import "cmcategory.h"
#import "CMBrowserControl.h"
#import "MarqueeLabel.h"
#import "CMMainControl.h"
static const CGFloat kHeightOfTopScrollView = 37.0f;
static const CGFloat kWidthOfButtonMargin = 10.0f;
static const CGFloat kFontSizeOfTabButton = 16.0f;
static const NSUInteger kTagOfRightSideButton = 999;

@interface UIScrollView(custom)
-(BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer;

@end


@implementation UIScrollView(custom)

-(BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{

    UIPanGestureRecognizer*   panParam = (UIPanGestureRecognizer*)gestureRecognizer;

    if(![panParam respondsToSelector:@selector(velocityInView:)])
        return YES;
    
    if([self.delegate isMemberOfClass:[QCSlideSwitchView class]] && [(QCSlideSwitchView*)self.delegate isRightChannel] )
    {

        if([panParam velocityInView:self].x<0)
        {
            if([(QCSlideSwitchView*)self.delegate isRootScrollView:self])
            {
                //[self setScrollEnabled:YES];
                return YES;
            }
        }

        if([panParam velocityInView:self].x>0)
        {
            if([(QCSlideSwitchView*)self.delegate isRootScrollView:self])
            {
                //[self setScrollEnabled:NO];
                return NO;
            }
        }
        return YES;
    }
    else
        return YES;
}

@end

@implementation QCSlideSwitchView


-(BOOL)isRootScrollView:(UIScrollView*)scrollview
{
    if (scrollview == _rootScrollView) {
        return YES;
    }
    else
        return NO;

}
-(BOOL)canScroll
{
//    return NO;
    if(self.canLeftScroll)
        NSLog(@"canleft scroll");
    else
        NSLog(@"can NOT left scroll");

    return self.canLeftScroll;

}

-(BOOL)isRightChannel
{
    return  _userSelectedChannelID==100;
}

-(void)enableScrollview
{
    [_rootScrollView setScrollEnabled:YES];
}
-(void)RestartMarqueeable
{
    for (UIView* v in _topScrollView.subviews) {
        if([v isKindOfClass:[UIButton class]])
        {
            for (UIView* subv in v.subviews) {
                if([subv isKindOfClass:[MarqueeLabel class]])
                    [subv performSelector:@selector(restartLabel) withObject:nil];

            }

        }
    }

}
#pragma mark - 初始化参数
- (void)initValues
{
    self.backgroundColor = kColorBackground;
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(RestartMarqueeable) name:@"RestartMarqueelabel" object:nil];


    //创建顶部可滑动的tab
    self.canLeftScroll  =YES;
    self.canRightScroll = YES;

    [[NSNotificationCenter defaultCenter]  addObserver:self selector:@selector (enableScrollview) name:@"LeftVcFinishMoved" object:nil];

    UIImageView *m_pBgImg= [[UIImageView alloc] init];
    m_pBgImg.backgroundColor = [UIColor clearColor];
    m_pBgImg.image = [[UIImage imageNamed:@"learn_tab_background"]resizableImageWithCapInsets:UIEdgeInsetsMake(1, 1, 1, 1)];
    m_pBgImg.clipsToBounds = YES;
    m_pBgImg.frame = CGRectMake(0, 0, self.bounds.size.width, kHeightOfTopScrollView);
    [self addSubview:m_pBgImg];
    
    _topScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, self.bounds.size.width, kHeightOfTopScrollView)];
//    _topScrollView.delegate = self;
    _topScrollView.backgroundColor = [UIColor whiteColor];
    _topScrollView.pagingEnabled = NO;
    _topScrollView.showsHorizontalScrollIndicator = NO;
    _topScrollView.showsVerticalScrollIndicator = NO;
    _topScrollView.scrollEnabled=YES;
    _topScrollView.scrollsToTop = NO;
    _topScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    [self addSubview:_topScrollView];
    _userSelectedChannelID = 100;
    
    //创建主滚动视图
    _rootScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, kHeightOfTopScrollView + 1, self.bounds.size.width, self.bounds.size.height - kHeightOfTopScrollView - 1)];
    _rootScrollView.delegate = self;
    _rootScrollView.pagingEnabled = YES;
    _rootScrollView.userInteractionEnabled = YES;
    _rootScrollView.bounces = NO;
    _rootScrollView.showsHorizontalScrollIndicator = NO;
    _rootScrollView.showsVerticalScrollIndicator = NO;
    _rootScrollView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleWidth;

    _userContentOffsetX = 0;

    [self addSubview:_rootScrollView];
    
    //_viewArray = [[NSMutableArray alloc] init];
    
    _isBuildUI = NO;







}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self initValues];
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self initValues];
    }
    return self;
}

#pragma mark getter/setter

- (void)setRigthSideButton:(UIButton *)rigthSideButton
{
    UIButton *button = (UIButton *)[self viewWithTag:kTagOfRightSideButton];
    [button removeFromSuperview];
    rigthSideButton.tag = kTagOfRightSideButton;
    _rigthSideButton = rigthSideButton;
    
    UIImageView *bg = [[UIImageView alloc] initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH - kHeightOfTopScrollView, 0, kHeightOfTopScrollView, kHeightOfTopScrollView)];
    [bg setImage:[UIImage imageNamed:@"learn_subscribe_rightbtn_bg"]];
    [self addSubview:bg];
    
    [self addSubview:_rigthSideButton];
    
}


- (void)setCategoryItem:(CMCategoryItem *)pCategoryItem
{
    m_pCategoryItem = pCategoryItem;
}

- (void)setCurrentIndex:(NSInteger)newIndex
{
    _curSlideView  = newIndex;
    
    if (_totalViewCount == 1) {
        [self addSlideSwitchView:0 atIndex:0];
    }
    else{
        NSInteger pre  = [self validPageValue:_curSlideView-1];
        NSInteger last = [self validPageValue:_curSlideView+1];
        [self addSlideSwitchView:pre atIndex:pre];
        [self addSlideSwitchView:_curSlideView atIndex:_curSlideView];
        [self addSlideSwitchView:last atIndex:last];

    }

}


#pragma mark - 创建控件

//当横竖屏切换时可通过此方法调整布局
- (void)layoutSubviews
{
    //创建完子视图UI才需要调整布局
    if (_isBuildUI) {
        
        //如果有设置右侧视图，缩小顶部滚动视图的宽度以适应按钮
        if (self.rigthSideButton.bounds.size.width > 0) {
            _rigthSideButton.frame = CGRectMake(self.bounds.size.width - self.rigthSideButton.bounds.size.width, 0,
                                                kHeightOfTopScrollView, kHeightOfTopScrollView);
            
            _topScrollView.frame = CGRectMake(0, 0,
                                              self.bounds.size.width - kHeightOfTopScrollView, kHeightOfTopScrollView);
        }
        
        //更新主视图的总宽度
        _rootScrollView.contentSize = CGSizeMake(self.bounds.size.width * _totalViewCount, 0);
        
        //更新主视图各个子视图的宽度
   
        _curSlideView = _userSelectedChannelID - 100;

        //滚动到选中的视图
        [_rootScrollView setContentOffset:CGPointMake((_userSelectedChannelID - 100)*self.bounds.size.width, 0) animated:NO];
        
        //调整顶部滚动视图选中按钮位置
        UIButton *button = (UIButton *)[_topScrollView viewWithTag:_userSelectedChannelID];
        [self adjustScrollViewContentX:button];
    }
}

- (void)initViewArray{
    if (!_viewArray) {
        _viewArray=[[NSMutableArray alloc]initWithCapacity:_totalViewCount];
    }
    [_viewArray removeAllObjects];
    
    if (!self.tabItemArray) {
        self.tabItemArray=[[NSMutableArray alloc]initWithCapacity:_totalViewCount];
    }
    [self.tabItemArray removeAllObjects];
    
    for (int i=0; i < _totalViewCount; i++) {
        [_viewArray addObject:[NSNull null]];
    }
}

/*!
 * @method 创建子视图UI
 * @abstract
 * @discussion
 * @param
 * @result
 */
- (void)buildUI
{
    NSUInteger number = [self.slideSwitchViewDataSource numberOfTab:self];
    
    _totalViewCount = number;
    
    if (_totalViewCount <= 0) {
        return;
    }
    
    [self initViewArray];

    //从scrollView上移除所有的subview
    NSArray *subViews = [_topScrollView subviews];
    if([subViews count] != 0) {
        [subViews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
    NSArray *subViews2 = [_rootScrollView subviews];
    if([subViews2 count] != 0) {
        [subViews2 makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
    
    _userSelectedChannelID = 100;
    
    _curSlideView  = _userSelectedChannelID - 100;

    [self setCurrentIndex:0];

    [self createNameButtons];
    
    //选中第一个view
    if (self.slideSwitchViewDelegate && [self.slideSwitchViewDelegate respondsToSelector:@selector(slideSwitchView:didselectTab:)]) {
        CMBrowserControl *vCtrl = [_viewArray objectAtIndex:_userSelectedChannelID - 100];
        [self.slideSwitchViewDelegate slideSwitchView:vCtrl didselectTab:_userSelectedChannelID - 100];
    }
    
    _isBuildUI = YES;
    
    //创建完子视图UI才需要调整布局
    [self setNeedsLayout];
}

/*!
 * @method 初始化顶部tab的各个按钮
 * @abstract
 * @discussion
 * @param
 * @result
 */
- (void)createNameButtons
{
    if (!_shadowImageView) {
        _shadowImageView = [[UIImageView alloc] init];
    }
    [_shadowImageView setImage:_shadowImage];
    [_topScrollView addSubview:_shadowImageView];
    
    //顶部tabbar的总长度
    CGFloat topScrollViewContentWidth = kWidthOfButtonMargin;
    //每个tab偏移量
    CGFloat xOffset = kWidthOfButtonMargin;
    NSInteger count = _totalViewCount;
    for (int i = 0; i < count; i++) {
        
        NSString *strTitle_;
        
        if (m_pCategoryItem != nil)
        {
            
            CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetSelectedChildItem(i);
            assert(m_pCategoryChildItem);
            
            
            
            strTitle_ = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
        }
        else
        {
            strTitle_ = [self.tabTitleArray objectAtIndex:i];
        }
        
        CGFloat textWidth = 0;

        UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];

        CGSize textSize = CGSizeZero;
        
        UIColor *color = (i == 0) ? self.tabItemSelectedColor : self.tabItemNormalColor;

        CGFloat textSize_MAX=0.0f;
        if (count < 4) {

            textSize_MAX = (UI_IOS_WINDOW_WIDTH-10*count - kWidthOfButtonMargin)/count;
            textSize = [strTitle_ sizeWithFont:[UIFont systemFontOfSize:kFontSizeOfTabButton]
                            constrainedToSize:CGSizeMake(_topScrollView.bounds.size.width, kHeightOfTopScrollView)
                                lineBreakMode:NSLineBreakByTruncatingTail];

        }
        else{

            textSize_MAX = 68;
            textSize = [strTitle_ sizeWithFont:[UIFont systemFontOfSize:kFontSizeOfTabButton]
                               constrainedToSize:CGSizeMake(_topScrollView.bounds.size.width, kHeightOfTopScrollView)
                                   lineBreakMode:NSLineBreakByTruncatingTail];
             }


            textWidth = textSize.width;
            if (textSize.width > textSize_MAX)
            {
                textSize.width = textSize_MAX;

            }
            else{
            }

        //累计每个tab文字的长度
        topScrollViewContentWidth += kWidthOfButtonMargin+textSize_MAX;

        if(textWidth>textSize_MAX )
        {
            MarqueeLabel*   categoryLbl =[[MarqueeLabel alloc]initWithFrame:CGRectMake(0,0,textSize.width, kHeightOfTopScrollView) duration:4.0 andFadeLength:0.0f];

            [categoryLbl setBackgroundColor:[UIColor clearColor]];
            [categoryLbl setText:strTitle_];
            [categoryLbl setTextAlignment:NSTextAlignmentCenter];
            [categoryLbl setFont:[UIFont systemFontOfSize:kFontSizeOfTabButton]];

            [categoryLbl setTextColor:color];
            [categoryLbl setAnimationCurve:UIViewAnimationOptionCurveLinear];
            [categoryLbl setFrame:CGRectMake(0,0,
                                             textSize_MAX, kHeightOfTopScrollView)];
            [categoryLbl setCenter:CGPointMake(textSize_MAX/2, kHeightOfTopScrollView/2)];
            [button addSubview:categoryLbl];
            
            [self.tabItemArray addObject:categoryLbl];

        }
        else
        {

            UILabel* categoryLbl = [[UILabel alloc]init];

            [categoryLbl setBackgroundColor:[UIColor clearColor]];
            [categoryLbl setText:strTitle_];
            [categoryLbl setTextAlignment:NSTextAlignmentCenter];
            [categoryLbl setFont:[UIFont systemFontOfSize:kFontSizeOfTabButton]];
            [categoryLbl setTextColor:color];
            [categoryLbl setFrame:CGRectMake(0,0,
                                             textWidth, kHeightOfTopScrollView)];
            [categoryLbl setCenter:CGPointMake(textSize_MAX/2, kHeightOfTopScrollView/2)];

            [button addSubview:categoryLbl];
            
            [self.tabItemArray addObject:categoryLbl];


        }

        //设置label尺寸
        [button setFrame:CGRectMake(xOffset,0,
                                    textSize_MAX, kHeightOfTopScrollView)];

        //计算下一个tab的x偏移量
        xOffset += textSize_MAX + kWidthOfButtonMargin;

        [button setTag:i+100];
        if (i == 0) {

//            _shadowImageView.frame = CGRectMake(kWidthOfButtonMargin, 0, textSize_MAX, _shadowImage.size.height - 0.0);
            _shadowImageView.frame = CGRectMake(kWidthOfButtonMargin, 0, textSize_MAX, kHeightOfTopScrollView - 0.0);
            if (count == 1) {
                _shadowImageView.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, kHeightOfTopScrollView - 0.0);
            }
            button.selected = YES;
        }

        [button setBackgroundColor:[UIColor clearColor]];

        [button addTarget:self action:@selector(selectNameButton:) forControlEvents:UIControlEventTouchUpInside];

        [_topScrollView addSubview:button];
    }

    //设置顶部滚动视图的内容总尺寸
    _topScrollView.contentSize = CGSizeMake(topScrollViewContentWidth, kHeightOfTopScrollView);
}


#pragma mark - 刷新数据

- (void)reloadData
{
    _userSelectedChannelID = 100;
    [self buildUI];
}

- (int)validPageValue:(NSInteger)value {
//    if(value == -1) value = _totalViewCount - 1;
//    if(value == _totalViewCount) value = 0;
    
    return value;
}

- (void)addSlideSwitchView:(NSInteger)page atIndex:(NSInteger)index{
    
    if (index < 0 || index >= _totalViewCount) {
        return;
    }
    
    if (page < 0 || page >= _totalViewCount) {
        return;
    }
    
    //_viewArray 已经装载 就重用,否则 init
    id currentSlideSwitchView = [_viewArray objectAtIndex:index];
    if (![currentSlideSwitchView isKindOfClass:[CMBrowserControl class]]) {
        
        UIViewController *vc = [self.slideSwitchViewDataSource slideSwitchView:self viewOfTab:index];
        
        if (!vc) {
            return;
        }
        
        
        [_viewArray replaceObjectAtIndex:index withObject:vc];
        
        vc.view.frame = CGRectMake(0+_rootScrollView.bounds.size.width*index, 0,
                                   _rootScrollView.bounds.size.width, _rootScrollView.bounds.size.height);
        
        [_rootScrollView addSubview:vc.view];


    }
    
}

- (void)removeSlideSwitchView:(NSInteger)page atIndex:(NSInteger)index{
    if (index < 0 || index >= _totalViewCount) {
        return;
    }
    
    id currentSlideSwitchView = [_viewArray objectAtIndex:index];
    if ([currentSlideSwitchView isKindOfClass:[CMBrowserControl class]]) {
        [currentSlideSwitchView removeFromSuperview];
        [_viewArray replaceObjectAtIndex:index withObject:[NSNull null]];
    }

}


#pragma mark - 顶部滚动视图逻辑方法

/*!
 * @method 选中tab时间
 * @abstract
 * @discussion
 * @param 按钮
 * @result
 */
- (void)selectNameButton:(UIButton *)sender
{
 
    //如果点击的tab文字显示不全，调整滚动视图x坐标使用使tab文字显示全
    [self adjustScrollViewContentX:sender];
    
    //如果更换按钮
    if (sender.tag != _userSelectedChannelID) {
        //取之前的按钮
        UIButton *lastButton = (UIButton *)[_topScrollView viewWithTag:_userSelectedChannelID];
        lastButton.selected = NO;
        //赋值按钮ID
        _userSelectedChannelID = sender.tag;
    }

    //按钮选中状态
    if (!sender.selected) {
        
        sender.selected = YES;
        
        [self setCurrentIndex:_userSelectedChannelID - 100];
        
        NSUInteger tabIndex = _userSelectedChannelID - 100;
        
        for (int i = 0; i < [self.tabItemArray count]; i++) {
            if (i == tabIndex) {
                [[self.tabItemArray objectAtIndex:i] setTextColor:self.tabItemSelectedColor];
            }
            else{
                [[self.tabItemArray objectAtIndex:i] setTextColor:self.tabItemNormalColor];
            }
        }
        
        //__weak typeof(self) weakSelf = self;
        WEAKSELF;
        
        [UIView animateWithDuration:0.25 animations:^{
            STRONGSELF;
            [sself->_shadowImageView setFrame:CGRectMake(sender.frame.origin.x, 0, sender.frame.size.width, kHeightOfTopScrollView - 0.0)];
        }
        completion:^(BOOL finished) {
            STRONGSELF;
            if (finished) {
                //设置新页出现
                if (!sself->_isRootScroll) {
                    [sself->_rootScrollView setContentOffset:CGPointMake((sender.tag - 100)*self.bounds.size.width, 0) animated:NO];
                }
                sself->_isRootScroll = NO;
            
                if (sself.slideSwitchViewDelegate && [sself.slideSwitchViewDelegate respondsToSelector:@selector(slideSwitchView:didselectTab:)]) {
                        CMBrowserControl *vCtrl = [sself.viewArray objectAtIndex:_userSelectedChannelID - 100];

                        [sself.slideSwitchViewDelegate slideSwitchView:vCtrl didselectTab:_userSelectedChannelID - 100];
                }
            }
        }];
        
    }
    //重复点击选中按钮
    else {
        
    }
}

/*!
 * @method 调整顶部滚动视图x位置
 * @abstract
 * @discussion
 * @param
 * @result
 */
- (void)adjustScrollViewContentX:(UIButton *)sender
{
    //如果 当前显示的最后一个tab文字超出右边界
    if (sender.frame.origin.x - _topScrollView.contentOffset.x > self.bounds.size.width - (kWidthOfButtonMargin+sender.bounds.size.width)) {
        //向左滚动视图，显示完整tab文字
        [_topScrollView setContentOffset:CGPointMake(sender.frame.origin.x - (_topScrollView.bounds.size.width- (kWidthOfButtonMargin+sender.bounds.size.width)), 0)  animated:YES];
    }
    
    //如果 （tab的文字坐标 - 当前滚动视图左边界所在整个视图的x坐标） < 按钮的隔间 ，代表tab文字已超出边界
    if (sender.frame.origin.x - _topScrollView.contentOffset.x < kWidthOfButtonMargin) {
        //向右滚动视图（tab文字的x坐标 - 按钮间隔 = 新的滚动视图左边界在整个视图的x坐标），使文字显示完整
        [_topScrollView setContentOffset:CGPointMake(sender.frame.origin.x - kWidthOfButtonMargin, 0)  animated:YES];
    }
}

#pragma mark 主视图逻辑方法

//滚动视图开始时
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    self.haveSetDistance = NO;

    if (scrollView == _rootScrollView) {
        _userContentOffsetX = scrollView.contentOffset.x;

    }

}

//滚动视图结束
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    if (scrollView == _rootScrollView) {
        //判断用户是否左滚动还是右滚动
        if (_userContentOffsetX < scrollView.contentOffset.x) {
            self.canRightScroll = YES;
            _isLeftScroll = YES;
            if(self.haveSetDistance == NO)
            {
                NSInteger nextTag = _userSelectedChannelID+1;
                UIButton *button = (UIButton *)[_topScrollView viewWithTag:nextTag];
                self.distanceToNextButton=fabs(button.frame.origin.x-_shadowImageView.frame.origin.x);
                self.haveSetDistance = YES;

            }

        }
        else {
            self.canRightScroll = NO;
            _isLeftScroll = NO;

            if(self.haveSetDistance == NO)
            {
                NSInteger nextTag = _userSelectedChannelID-1;
                UIButton *button = (UIButton *)[_topScrollView viewWithTag:nextTag];
                self.distanceToNextButton=fabs(button.frame.origin.x-_shadowImageView.frame.origin.x);
                self.haveSetDistance = YES;
            }
        }


        int count = _totalViewCount;

        if(count>4)
            count =4;

        CGFloat oldX = (self.userSelectedChannelID - 100) * CGRectGetWidth(scrollView.frame);
        CGFloat ratio = (scrollView.contentOffset.x - oldX) / CGRectGetWidth(scrollView.frame);
        
        //当前button
        UIButton *button = (UIButton *)[_topScrollView viewWithTag:_userSelectedChannelID];
        
        //移动shadowImageView
        CGRect f = _shadowImageView.frame;
      //  f.origin.x = scrollView.contentOffset.x/count+((5-count)*5);
        f.origin.x = self.distanceToNextButton*ratio + button.frame.origin.x;
        [_shadowImageView setFrame:f];

    }
}

//滚动视图释放滚动
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{

    self.haveSetDistance = NO;

    if (scrollView == _rootScrollView) {
        _isRootScroll = NO;

        //调整顶部滑条按钮状态
        int tag = (int)scrollView.contentOffset.x/self.bounds.size.width +100;
        UIButton *button = (UIButton *)[_topScrollView viewWithTag:tag];
        [self selectNameButton:button];
    }
}

//传递滑动事件给下一层
-(void)scrollHandlePan:(UIPanGestureRecognizer*) panParam
{

    if(_userSelectedChannelID!=100)
    {

        return;
    }

    //当滑道左边界时，传递滑动事件给代理
    if(_rootScrollView.contentOffset.x <= 0) {
        if (self.slideSwitchViewDelegate
            && [self.slideSwitchViewDelegate respondsToSelector:@selector(slideSwitchView:panLeftEdge:)]) {

            self.canRightScroll = NO;
            self.canLeftScroll = YES;

            [self.slideSwitchViewDelegate slideSwitchView:self panLeftEdge:panParam];
        }
    } else if(_rootScrollView.contentOffset.x >= _rootScrollView.contentSize.width - _rootScrollView.bounds.size.width) {
        if (self.slideSwitchViewDelegate
            && [self.slideSwitchViewDelegate respondsToSelector:@selector(slideSwitchView:panRightEdge:)]) {

            [self.slideSwitchViewDelegate slideSwitchView:self panRightEdge:panParam];
        }
    }
    
}

#pragma mark - 工具方法

/*!
 * @method 通过16进制计算颜色
 * @abstract
 * @discussion
 * @param 16机制
 * @result 颜色对象
 */
+ (UIColor *)colorFromHexRGB:(NSString *)inColorString
{
    UIColor *result = nil;
    unsigned int colorCode = 0;
    unsigned char redByte, greenByte, blueByte;
    
    if (nil != inColorString)
    {
        NSScanner *scanner = [NSScanner scannerWithString:inColorString];
        (void) [scanner scanHexInt:&colorCode]; // ignore error
    }
    redByte = (unsigned char) (colorCode >> 16);
    greenByte = (unsigned char) (colorCode >> 8);
    blueByte = (unsigned char) (colorCode); // masks off high bits
    result = [UIColor
              colorWithRed: (float)redByte / 0xff
              green: (float)greenByte/ 0xff
              blue: (float)blueByte / 0xff
              alpha:1.0];
    return result;
}

-(void)dealloc
{

    [[NSNotificationCenter defaultCenter] removeObserver:self
         ];
    
    [_viewArray removeAllObjects];
    [self.tabItemArray removeAllObjects];
}

- (void)scrollToTop{
    CMBrowserControl *browserControl = (CMBrowserControl *)[_viewArray objectAtIndex:_userSelectedChannelID - 100];
    if (browserControl != nil && [browserControl respondsToSelector:@selector(scrollToTop)]) {
        [browserControl scrollToTop];
        
    }
}

//- (void)stopScrolling{
//    CMBrowserControl *browserControl = (CMBrowserControl *)[_viewArray objectAtIndex:_userSelectedChannelID - 100];
//    if (browserControl != nil && [browserControl respondsToSelector:@selector(scrollToTop)]) {
//        [browserControl stopScrolling];
//        
//    }
//}

@end
