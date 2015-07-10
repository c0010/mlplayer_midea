    //
//  CMHomeControl.m
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//




#import "CMBrowserControl.h"
#import "cmsettings.h"
#import "CMGetNewControl.h"
#import "GridCell.h"
#import "ImageRightButton.h"
#import "CMSearchHotControl.h"
#import "CMPersonController.h"
//#import "MobClick.h"
#import "cmshake.h"
#import "CMMainControl.h"
#include "cmmyinfo.h"
#import "SDWebImage/UIButton+WebCache.h"
#define kLeftPercentage   0.55
#define kSpeedMultiplier  0.4
#define kTabCellWidth     12

#define  PopDownCell_Height 44

@interface CMBrowserControl(Private)

- (void)shakeDown;

@end



@implementation CMBrowserControl
@synthesize gridView;



-(CMContenthandler*)GetContenthandler{
    
    
    for( UIView * view in self.view.subviews )
    {
        if([view isKindOfClass:[CMRefreshMoreView class]])
        {
            if([view isKindOfClass:[CMItemView class]])
            {
                CMItemView* itemview = (CMItemView*)view;
                
                return itemview.Contenthandler;
            }
//            else if([view isKindOfClass:[CMRecentView class]])
//            {
//                CMRecentView* itemview = (CMRecentView*)view;
//                return itemview.Contenthandler;
//            }
            
        }
        
        
    }
    
    return NULL;
}

#pragma mark -
#pragma mark navigation title pop down

-(void)popDownList {
    
    NSString *sFlag = [NSString stringWithUTF8String:m_sFlag];

    CGRect f = self.view.bounds;
    if ([sFlag isEqualToString:@"course"] || [sFlag isEqualToString:@"news"]) {
		if (gridView == nil) {
			gridView = [[UIGridView alloc] initWithFrame:CGRectMake(f.size.width/2, 0, 0, 0)];
			gridView.uiGridViewDelegate = self;
			[self.view addSubview:gridView];
            CMRELEASE(gridView);
			
        }
    }
    if (gridView.frame.size.height <= 0) {
		[UIView animateWithDuration:0.4 animations:^{gridView.frame = f;}];
		if(gridView.tag == 1)
		{
			[gridView reloadData];
			gridView.tag = 0;
		}
    } else {
		[UIView animateWithDuration:0.4 animations:^{gridView.frame = CGRectMake(f.size.width/2, 0, 0, 0);}];
    }
    
}

#pragma mark segment function

-(void)ChangeSegmentFont:(UIView *)aView{
	
	if ([aView isKindOfClass:[UILabel class]]) {
		UILabel *lb = (UILabel	*)aView;
		[lb setTextAlignment:UITextAlignmentCenter];
			//[lb setFrame:CGRectMake(0, 0, 120, 30)];
			//[lb setFont:[UIFont systemFontOfSize:12]];
		[lb setTextColor:[UIColor blackColor]];
		lb.font = [UIFont fontWithName:@"TrebuchetMS" size:12];
		
	}
	NSArray *na = [aView subviews];
	NSEnumerator *ne = [na objectEnumerator];
	UIView *subView;
	while (subView = [ne nextObject]) {
		[self ChangeSegmentFont:subView];
	}
	
}





#pragma mark system function
// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

- (void)reloadTableViewList{
    [browserview.tableviewlist reloadData];
}

-(void)viewWillAppear:(BOOL)animated 
{ 
		
    [self updateLeftHeadImage];
	//接收通知
	[[NSNotificationCenter defaultCenter] 
     addObserver:self selector:@selector(refreshPage:) name:@"reloadBrowserView" object:nil];
    

    
    [browserview.tableviewlist reloadData];
	
	//添加滑动监测
    NSString *strType = [NSString stringWithUTF8String:m_sFlag];
    
//    if ([strType isEqualToString:@"course"])
//    {
//        [MobClick beginEvent:@"LearnTime"];
//    }
//    else if ([strType isEqualToString:@"news"])
//    {
//        [MobClick beginEvent:@"NewsTime"];
//
//    }

    if(browserview && browserview.willRefreshList)
        [browserview automaticRefreshUseCache:YES];

    if(browserview)
        browserview.willRefreshList =YES;

	[super viewWillAppear:animated];
	
}

//iOS8上 cell分割线置顶
-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    if ([browserview.tableviewlist respondsToSelector:@selector(setSeparatorInset:)]) {
        [browserview.tableviewlist setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([browserview.tableviewlist respondsToSelector:@selector(setLayoutMargins:)]) {
        [browserview.tableviewlist setLayoutMargins:UIEdgeInsetsZero];
    }
}



- (void) viewWillDisappear:(BOOL)animated {
	//去除消息接收
	[[NSNotificationCenter defaultCenter] removeObserver:self name:@"reloadBrowserView" object:nil];
    
    NSString *strType = [NSString stringWithUTF8String:m_sFlag];
    
//    if ([strType isEqualToString:@"course"])
//    {
//        [MobClick endEvent:@"LearnTime"];
//    }
//    else if ([strType isEqualToString:@"news"])
//    {
//        [MobClick endEvent:@"NewsTime"];
//    }
    
    //[self resignFirstResponder];
    [super viewWillDisappear:animated];
}


-(void)onAppFocus:(BOOL)isForeground
{
	[self viewDidLoad];
}

-(void)gotoPerson
{
	CMPersonController* personControl = [[CMPersonController alloc] init];
	
	personControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;	
	personControl.navigationController.navigationBarHidden = NO;
	personControl.tabBarController.tabBar.hidden = YES;
	personControl.hidesBottomBarWhenPushed = YES;
	[[self navigationController] pushViewController:personControl animated:YES];
    CMRELEASE(personControl);
}
-(void)gotoSearch
{
	CMSearchHotControl* searchControl = [[CMSearchHotControl alloc] init];
	
    //CMSweepViewController* searchControl=[[CMSweepViewController alloc]init];
	searchControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;	
	searchControl.navigationController.navigationBarHidden = NO;
	searchControl.tabBarController.tabBar.hidden = YES;
	searchControl.hidesBottomBarWhenPushed = YES;
	[searchControl.navigationItem setTitle:I(@"搜索")];
	searchControl.flag = [NSString stringWithUTF8String:m_sFlag];
	[[self navigationController] pushViewController:searchControl animated:YES];
    CMRELEASE(searchControl);
}

- (void)updateCategory{
    m_pCategoryItem = [browserview GetCategory:m_sFlag];
    [m_pTableView reloadData];
    [browserview.tableviewlist reloadData];
}

- (void)updateLeftHeadImage{
    [self.leftButton sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetHeadimage()]] forState:UIControlStateNormal placeholderImage:[UIImage imageNamed:@"user_img_small_left"]];
}

- (void)leftClickAction{
    [(CMMainControl*)self.tabBarController openSideBar];
}

- (void)enableScrollview{
    [CMMainControlHandler isForbidGesture:YES];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {	
	
	[super viewDidLoad];

    //[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateCategory) name:CM_NotificationCenter_ReloadCategory object:nil];
    

    self.titleLabel.text = self.navigationItem.title;
    self.navigationItem.leftBarButtonItem = nil;

    NSString *strAudio = [[NSBundle mainBundle] pathForResource:@"glass" ofType:@"wav"];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)[NSURL URLWithString:strAudio], &sysSoundID);
    
//    NSString *sFlag = [NSString stringWithUTF8String:m_sFlag];
//
//    if ([sFlag isEqualToString:@"course"]) {
//        
//        [[NSNotificationCenter defaultCenter]  addObserver:self selector:@selector (enableScrollview) name:LeftVcFinishMove object:nil];
//
//        self.leftButton = [UIButton buttonWithType:UIButtonTypeCustom];
//        self.leftButton.frame = CGRectMake(0, 0.0, 28, 28);
//    
//        [self.leftButton sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetHeadimage()]] forState:UIControlStateNormal placeholderImage:[UIImage imageNamed:@"user_img_small_left"]];
//        self.leftButton.layer.masksToBounds = YES;
//        self.leftButton.layer.cornerRadius = 14;
//
//        [self.leftButton addTarget:self action:@selector(leftClickAction) forControlEvents:UIControlEventTouchUpInside];
//        [self.leftButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
//        UIBarButtonItem *leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:self.leftButton];
//        //self.navigationItem.leftBarButtonItem = leftBarButtonItem;
//        
//        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateLeftHeadImage) name:CM_NotificationCenter_HeadImageUpdate object:nil];
//        
//    }
//    
//
//	//搜索
//	UIButton *searchBtn = [UIButton buttonWithType:UIButtonTypeCustom];
//	searchBtn.frame = CGRectMake(0, 0, kBarItemWidth, kBarItemHeight);
//    searchBtn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
//	[searchBtn setImage:[UIImage imageNamed:@"NavSearch"] forState:UIControlStateNormal];
//	[searchBtn addTarget:self action:@selector(gotoSearch) forControlEvents:UIControlEventTouchUpInside];
//		UIBarButtonItem *searchBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:searchBtn];
//    
//    //self.navigationItem.rightBarButtonItem = searchBarButtonItem;
//    CMRELEASE(searchBarButtonItem);
    

	appDelegate = [UIApplication sharedApplication].delegate;
	
	if(strlen(m_sFlag) <= 0)
		return;
	
	
	//数据列表
	browserview = [[CMBrowserView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH,UI_IOS_VC_HEIGHT)];
	[[self view] addSubview:browserview];
    [browserview setCurrentPos:nSelectRow];
    browserview.tableviewlist.userInteractionEnabled = YES;
    
    trainlistview = [[CMTrainListView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_VC_HEIGHT)];
    trainlistview.tableviewlist.userInteractionEnabled = YES;

    
    
	UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
	horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
	//[browserview.tableviewlist addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);
    
    horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
    horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
    //[trainlistview.tableviewlist addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);
	
	horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
	horizontal.direction = UISwipeGestureRecognizerDirectionRight;
	[browserview.tableviewlist addGestureRecognizer:horizontal];
    //[trainlistview.tableviewlist addGestureRecognizer:horizontal];
	CMRELEASE(horizontal);
    
    horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
    horizontal.direction = UISwipeGestureRecognizerDirectionRight;
    //[trainlistview.tableviewlist addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);

    
    m_pCategoryItem = [browserview GetCategory:m_sFlag];
    if(!m_pCategoryItem)
        return;
    

  
    if (!popDownArr) {
        popDownArr = [[NSMutableArray alloc] init];
    }

  
  //  NSString *sFlag = [NSString stringWithUTF8String:m_sFlag];
//    if ([sFlag isEqualToString:@"news"] || [sFlag isEqualToString:@"course"]) {
//        for(int i = 0;i < m_pCategoryItem->FrontChildItemCount(); i++)
//        {
//            CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(i);
//            assert(m_pCategoryChildItem);
//
//            NSLog(@" count = %d, sID= %s, m_pCategoryItem->sTitle = %@", m_pCategoryItem->FrontChildItemCount(),m_pCategoryChildItem->sID,[NSString stringWithUTF8String:m_pCategoryChildItem->sTitle]);
//            NSString * titles = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
//            
//            //设置tab文字
//            [popDownArr addObject:titles];
//        }
//        
//    }
    
    utf8ncpy(browserview->m_sFlag, m_sFlag, 15);

	if(!m_pWebImage)
	{
		m_pListener = new CMBrowserGetImageListener();
		m_pWebImage = new CMWebImage(m_pListener);
		m_pWebImage->SetUserData((__bridge void*)self);
	}
	
	browserview.userInteractionEnabled = YES;
		
    
    UIImageView *pImgUp = [[UIImageView alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-125)/2, UI_IOS_WINDOW_HEIGHT/2-100, 125, 100)];
    pImgUp.backgroundColor = [UIColor clearColor];
    pImgUp.image = [UIImage imageNamed:@"shakeup"];
    
    m_pImgUp = [[UIView alloc] initWithFrame:CGRectMake(0, -UI_IOS_WINDOW_HEIGHT/2, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT/2)];
    m_pImgUp.backgroundColor = [UIColor colorWithRed:38/255.0 green:38/255.0 blue:38/255.0 alpha:1.0];
    [m_pImgUp addSubview:pImgUp];
    [appDelegate.window addSubview:m_pImgUp];
    
    UIImageView *pImgDown = [[UIImageView alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-125)/2, 0, 125, 100)];
    pImgDown.backgroundColor = [UIColor clearColor];
    pImgDown.image = [UIImage imageNamed:@"shakedown"];
    
    m_pImgDown = [[UIView alloc] initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT/2)];
    m_pImgDown.backgroundColor = [UIColor colorWithRed:38/255.0 green:38/255.0 blue:38/255.0 alpha:1.0];
    [m_pImgDown addSubview:pImgDown];
    [appDelegate.window addSubview:m_pImgDown];
    CMRELEASE(pImgUp);
    CMRELEASE(pImgDown);
    
    upImgHidden = YES;
    downImgHidden = YES;
    animationDone = YES;
    
   
    
    UIImageView *bgimg= [[UIImageView alloc] init];
    bgimg.backgroundColor = [UIColor clearColor];
    bgimg.image = [UIImage imageNamed:@"learn_tab_background"];
    bgimg.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, bgimg.image.size.height);
    //[self.view addSubview:bgimg];
    CMRELEASE(bgimg);
    
    m_pTableView = [[UITableView alloc] init];
    m_pTableView.backgroundColor = [UIColor clearColor];
    m_pTableView.frame = CGRectMake(0, 0, 42.5, UI_IOS_WINDOW_WIDTH);
    m_pTableView.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, 20);
    m_pTableView.transform = CGAffineTransformMakeRotation(-M_PI/2);
    m_pTableView.showsHorizontalScrollIndicator = NO;
    m_pTableView.showsVerticalScrollIndicator = NO;
    m_pTableView.delegate = self;
    m_pTableView.dataSource = self;
    m_pTableView.separatorColor = [UIColor clearColor];
    //[self.view addSubview:m_pTableView];
	
    //nSelectRow = 0;
    if (selview) {
        [selview removeFromSuperview];
        CMRELEASE(selview);
    }
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSString *openpush = [ud objectForKey:kUDOpenPush];
    NSString *pushtype = [ud objectForKey:kUDPushType];
    if ([openpush isEqualToString:@"1"]) {
        if ([pushtype isEqualToString:@"position_course"]) {
            nSelectRow = m_pCategoryItem->GetPositionCourseItem();
            [browserview setCurrentPos:nSelectRow];
            [ud removeObjectForKey:kUDOpenPush];
            [ud removeObjectForKey:kUDPushType];
        }
    }
    
    //标签
    CGSize size = [self getTabCategoryTitleSizeAtIndex:nSelectRow];
    selview = [[UIImageView alloc] init];
    selview.frame = CGRectMake(1.8, 6, 3.0, size.width + 10);
    selview.backgroundColor = kColorForeground;
    [m_pTableView addSubview:selview];
    
}

- (void)setCurrentPos:(NSInteger)index{
    if (index >= 0) {
        nSelectRow = index;
    }
}

- (void)autoRefresh{
    
//    m_pCategoryItem = [browserview GetCategory:m_sFlag];
//    if(!m_pCategoryItem)
//        return;
    
    CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetSelectedChildItem(nSelectRow);
    assert(m_pCategoryChildItem);
    NSString *categoryID = [NSString stringWithUTF8String:m_pCategoryChildItem->sType];
    if ([categoryID isEqualToString:@"11"]) {
        if ([browserview superview]) {
            [browserview removeFromSuperview];
            [self.view addSubview:trainlistview];
        }
        
        [trainlistview automaticRefresh];
        
    }else{
        if ([trainlistview superview]) {
            [trainlistview removeFromSuperview];
            [self.view addSubview:browserview];
        }
        
        [browserview setCurrentPos:nSelectRow];
        
        utf8ncpy(browserview->m_sFlag, m_sFlag , 15);
        //strcpy(browserview->m_sFlag, m_sFlag);
        
      //  browserview->_reloading=NO;
        
        
        [browserview automaticRefreshUseCache:YES];
    }

    
//    [browserview setCurrentPos:nSelectRow];
//    
//    utf8ncpy(browserview->m_sFlag, m_sFlag , 15);
//    
//    browserview->_reloading=NO;
//    
//    //browserview.navigationControllerDelegate = navigationControllerDelegate;
//    
//    [browserview automaticRefreshUseCache:YES];
}


#pragma mark - setting tab title
- (CGSize)getTabCategoryTitleSizeAtIndex:(NSInteger)index{
    CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(index);
    assert(m_pCategoryChildItem);
    CGSize size;
    NSString *strTitle = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
    if ([strTitle length] <= 4) {
        size.width = 60.0;
    }
    else{
        size = [strTitle sizeWithFont:[UIFont systemFontOfSize:16] forWidth:UI_IOS_WINDOW_WIDTH lineBreakMode:NSLineBreakByWordWrapping];
    }
    return size;
}

#pragma mark - Handle Gesture for LeftPanel
  
- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap 
{
    
    if (nSelectRow == 0 && [[NSString stringWithUTF8String:m_sFlag] isEqualToString:@"course"])  {
        [((CMMainControl*)self.navigationControllerDelegate.tabBarController) isForbidGesture:NO];
        [(CMMainControl*)self.navigationControllerDelegate.tabBarController openSideBar];
    }
    return;
    
    NSInteger index = nSelectRow;
	if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
	{
		index ++;
        [CMMainControlHandler isForbidGesture:YES];
		
	}
	else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
	{
		index--;
        
        //添加滑动监测
        NSString *strType = [NSString stringWithUTF8String:m_sFlag];
        
        if (nSelectRow == 0 && [strType isEqualToString:@"course"]) {
            
            [CMMainControlHandler isForbidGesture:NO];
        }
	}
	if(index < 0 || index >= m_pCategoryItem->FrontChildItemCount())
		return;
    if (nSelectRow != index)
    {
        [UIView animateWithDuration:0.3 animations:^(void){
            //判断左右滑动手势，对应减去不同的宽度，UISwipeGestureRecognizerDirectionLeft 加上当前tab高度，UISwipeGestureRecognizerDirectionRight 减去将要滑向的tab 高度
            float width;
            float cellwidth;
            CGSize size = [self getTabCategoryTitleSizeAtIndex:index];
            width = size.width + 10;
            
            CGSize size_Current = [self getTabCategoryTitleSizeAtIndex:nSelectRow];
            cellwidth = size_Current.width;
            
            if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
            {
                cellwidth = size_Current.width + 20;
            }
            else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
            {
                cellwidth = width + 10;
            }
            
            CGRect newframe = selview.frame;
            newframe.origin.y = newframe.origin.y + (index - nSelectRow) * cellwidth;  //
            newframe.size.height = width;
            selview.frame = newframe;
        } completion:^(BOOL finish){
            nSelectRow = index;
            [m_pTableView reloadData];
            
            UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nSelectRow inSection:0]];
            CGRect rect = cell.frame;
            if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
            {
                if (rect.size.width == 0 && rect.size.height == 0.0) {
                [m_pTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:index inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];

                }
                
            }
            else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
            {
                if (rect.size.width == 0 && rect.size.height == 0.0) {
                    [m_pTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:index inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
                }
            }
            [m_pTableView scrollRectToVisible:rect animated:YES];
            
            
            CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(nSelectRow);
            assert(m_pCategoryChildItem);
            NSString *categoryID = [NSString stringWithUTF8String:m_pCategoryChildItem->sType];
            if ([categoryID isEqualToString:@"11"]) {
                if ([browserview superview]) {
                    [browserview removeFromSuperview];
                    [self.view addSubview:trainlistview];
                }
                
                [trainlistview automaticRefresh];
                
            }else{
                if ([trainlistview superview]) {
                    [trainlistview removeFromSuperview];
                    [self.view addSubview:browserview];
                }
                
                [browserview setCurrentPos:index];
                
                utf8ncpy(browserview->m_sFlag, m_sFlag , 15);
                //strcpy(browserview->m_sFlag, m_sFlag);
                
           //     browserview->_reloading=NO;
                
                
                [browserview automaticRefreshUseCache:YES];
            }
            
            
//            [browserview setCurrentPos:index];
//            
//            
//            utf8ncpy(browserview->m_sFlag, m_sFlag , 15);
////            strcpy(browserview->m_sFlag, m_sFlag);
//            
//            browserview->_reloading=NO;
//
//            [browserview automaticRefreshUseCache:YES];
        }];
    }

}



- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer;
{
    
	UIPanGestureRecognizer *pan=(UIPanGestureRecognizer*)gestureRecognizer;
    
    if(![pan isKindOfClass:[UIPanGestureRecognizer class]])
        return NO;
    
	return YES;
    
    
}

//判断是否接收滑动处理
-(BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{

	
//	
//	UIPanGestureRecognizer *pan=(UIPanGestureRecognizer*)gestureRecognizer;
//    
//    if(![pan isKindOfClass:[UIPanGestureRecognizer class]])
//        return NO;
//    
//	//CGPoint translate=[panRecognizer translationInView:self.view];
//
//
//    if(moveview.frame.origin.x==0&&[pan translationInView:moveview].x<0)
//		return NO;
//	
//	return YES;
    
    return YES;
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/



-(BOOL)canBecomeFirstResponder{
    return YES;
}
-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    //[self becomeFirstResponder];
    
}
#pragma mark - shake

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event
//- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (strcmp(m_sFlag, "course") == 0
        && !CMMainControlHandler.showingLeft
        && CMGlobal::TheOne().IsExistNetwork()
        && animationDone
        && SETTING.GetShake())
    {
        if (motion == UIEventSubtypeMotionShake)
        {
            [UIView transitionWithView:m_pImgUp
                              duration:0.5f
                               options:UIViewAnimationOptionCurveEaseInOut
                            animations:^{
                                CGRect upframe = m_pImgUp.frame;
                                while (upframe.origin.y <= -1)
                                {
                                    upframe.origin.y += 1;
                                }
                                m_pImgUp.frame = upframe;
                            }
                            completion:^(BOOL finished) {
                                upImgHidden = NO;
                                
                                if (!downImgHidden)
                                {
                                    [self performSelector:@selector(reset) withObject:nil afterDelay:0.3];
                                }
                            }];
            
            [UIView transitionWithView:m_pImgDown
                              duration:0.5f
                               options:UIViewAnimationOptionCurveEaseInOut
                            animations:^{
                                CGRect downframe = m_pImgDown.frame;
                                while (downframe.origin.y >= (UI_IOS_WINDOW_HEIGHT/2+1))
                                {
                                    downframe.origin.y -= 1;
                                }
                                m_pImgDown.frame = downframe;
                            }
                            completion:^(BOOL finished) {
                                downImgHidden = NO;
                                
                                if (!upImgHidden)
                                {
                                    [self performSelector:@selector(reset) withObject:nil afterDelay:0.3];
                                }
                            }];
        }
    }
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake)
    {
        [self performSelector:@selector(reset) withObject:nil afterDelay:0.3];
    }
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (motion == UIEventSubtypeMotionShake)
    {
        [self performSelector:@selector(reset) withObject:nil afterDelay:0.3];
    }
}

- (void)reset
{
    if (!upImgHidden && !downImgHidden)
    {
        AudioServicesPlaySystemSound(sysSoundID);
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
        
        [browserview loadShakeDate:self];
        animationDone = NO;
        
        [UIView transitionWithView:m_pImgUp
                          duration:0.5f
                           options:UIViewAnimationOptionCurveEaseInOut
                        animations:^{
                            CGRect upframe = m_pImgUp.frame;
                            while (upframe.origin.y >= -(UI_IOS_WINDOW_HEIGHT/2 -1))
                            {
                                upframe.origin.y -= 1;
                            }
                            m_pImgUp.frame = upframe;
                            upImgHidden = YES;
                        }
                        completion:^(BOOL finished) {
                        }];
        
        [UIView transitionWithView:m_pImgDown
                          duration:0.5f
                           options:UIViewAnimationOptionCurveEaseInOut
                        animations:^{
                            CGRect downframe = m_pImgDown.frame;
                            while (downframe.origin.y <= UI_IOS_WINDOW_HEIGHT-1)
                            {
                                downframe.origin.y += 1;
                            }
                            m_pImgDown.frame = downframe;
                            downImgHidden = YES;
                        }
                        completion:^(BOOL finished) {
                            
                        }];
    }
}

- (void)shakeDown
{
    animationDone = YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;

}

-(void)setFlag:(const char*)sflag
{
	if(sflag)
        utf8ncpy(m_sFlag,sflag, 15);
}

- (void)dealloc {
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
	
	CMRELEASE(segmentedControl);
	CMRELEASE(SegmentBgView);
	CMRELEASE(browserview);
    CMRELEASE(trainlistview);
	SAFEDELETE(m_pListener);
	SAFEDELETE(m_pWebImage);
    CMRELEASE(selview);

# if ! __has_feature(objc_arc)
    [super dealloc];
#endif
    
}


#pragma mark - Table View Datasource

- (IBAction)btnPressed:(id)sender
{
    UIButton *btn = (UIButton*)sender;
    UITableViewCell *cell = [self buttonSuperCell:btn];
    NSIndexPath *indexPath = [m_pTableView indexPathForCell:cell];
    if (nSelectRow != indexPath.row)
    {
        CGRect frame = [m_pTableView  convertRect:btn.frame fromView:btn.superview];
        [UIView animateWithDuration:0.3 animations:^(void){
            CGRect newframe = selview.frame;
            newframe.origin.y = frame.origin.y;  //由于tableview，transform与 selview.transform 差异，正好他们的x，y对应
            newframe.size.height = btn.frame.size.width;
            selview.frame = newframe;
        } completion:^(BOOL finish){
            nSelectRow = indexPath.row;
            [m_pTableView reloadData];
            
            UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nSelectRow inSection:0]];
            CGRect rect = cell.frame;
            [m_pTableView scrollRectToVisible:rect animated:YES];
            
            
            CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(nSelectRow);
            assert(m_pCategoryChildItem);
            NSString *categoryID = [NSString stringWithUTF8String:m_pCategoryChildItem->sID];
            if ([categoryID isEqualToString:@"11"]) {
                if ([browserview superview]) {
                    [browserview removeFromSuperview];
                    [self.view addSubview:trainlistview];
                }
                
                [trainlistview automaticRefresh];
                
            }else{
                if ([trainlistview superview]) {
                    [trainlistview removeFromSuperview];
                    [self.view addSubview:browserview];
                }
                
                [browserview setCurrentPos:indexPath.row];
                
                strcpy(browserview->m_sFlag, m_sFlag);
                
            //    browserview->_reloading=NO;
                
                
                [browserview automaticRefreshUseCache:YES];
            }
            
            
            
        }];
       
    }

   // UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:indexPath];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
	if(!m_pCategoryItem)
		return 0;
    return m_pCategoryItem->FrontChildItemCount();
    
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(!m_pCategoryItem)
            return 0;

    CGSize size = [self getTabCategoryTitleSizeAtIndex:indexPath.row];
    return size.width + 20;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
        if(!m_pCategoryItem)
            return nil;
        
        float width;
        float cellwidth;
        CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(indexPath.row);
        assert(m_pCategoryChildItem);
        
        NSString *strTitle_ = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
        if ([strTitle_ length] <= 4) {
            width = 70;
            cellwidth = width + 10;
        }
        else{
            CGSize size = [strTitle_ sizeWithFont:[UIFont systemFontOfSize:16] forWidth:UI_IOS_WINDOW_WIDTH lineBreakMode:NSLineBreakByWordWrapping];
            width = size.width + 10;
            cellwidth = width + 10;
        }
    
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"browsecell"];
        
        if (cell == nil)
        {
#if ! __has_feature(objc_arc)
            cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                           reuseIdentifier:@"browsecell"] autorelease];
#else
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                           reuseIdentifier:@"browsecell"];
#endif
            UIButton *button = [[UIButton alloc] init];
            button.tag = 2013;
            [button addTarget:self action:@selector(btnPressed:) forControlEvents:UIControlEventTouchUpInside];
            [cell.contentView addSubview:button];
            CMRELEASE(button);
            cell.backgroundColor = [UIColor clearColor];

            cell.selectionStyle = UITableViewCellSelectionStyleNone;
        }
        cell.transform = CGAffineTransformMakeRotation(M_PI/2);
        
        UIButton *btn = (UIButton *)[cell.contentView viewWithTag:2013];
        cell.frame = CGRectMake(0, 0, cellwidth, 42.5);
        btn.frame = CGRectMake(0, 0, width, 28);
        btn.center = cell.center;
        btn.backgroundColor = [UIColor clearColor];
        [btn setTitleColor:UIColorRGB(0x3a3a3a) forState:UIControlStateNormal];
        [btn.titleLabel setFont:[UIFont systemFontOfSize:16]];

        if (nSelectRow == indexPath.row)
        {
            CGRect frame = selview.frame;
            CGRect cell_frame = [m_pTableView  rectForRowAtIndexPath:indexPath];
            frame.origin.y = cell_frame.origin.y + 6;
            selview.frame = frame;
            [btn setTitleColor:kColorForeground forState:UIControlStateNormal];

        }
        else
        {
            [btn setBackgroundImage:nil forState:UIControlStateNormal];
            [btn setBackgroundImage:nil forState:UIControlStateHighlighted];
        }
        
        [btn setTitle:strTitle_ forState:UIControlStateNormal];
        return cell;    
    
}

- (void)gotoTop{
    [browserview.tableviewlist setContentOffset:CGPointMake(0, 0) animated:YES];
}
#pragma mark - Table View Delegate
//- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
//    
//    [browserview setCurrentPos:indexPath.row];
//    [browserview LoadData:m_sFlag refresh:true];
//    
//
//	[self popDownList];
//    
//    //create title view for navigation bar
//    [titleBtn setTitle:[popDownArr objectAtIndex:indexPath.row] forState:UIControlStateNormal];
//    
//}
#pragma mark - Grid View Delegate
- (CGFloat) gridView:(UIGridView *)grid widthForColumnAt:(int)columnIndex
{
	return 107;
}

- (CGFloat) gridView:(UIGridView *)grid heightForRowAt:(int)rowIndex
{
	return 107;
}

- (NSInteger) numberOfColumnsOfGridView:(UIGridView *) grid
{
	return 3;
}


- (NSInteger) numberOfCellsOfGridView:(UIGridView *) grid
{
	if(!m_pCategoryItem)
		return 0;
	return m_pCategoryItem->FrontChildItemCount();
}

- (UIGridViewCell *) gridView:(UIGridView *)grid cellForRowAt:(int)rowIndex AndColumnAt:(int)columnIndex
{
	GridCell *cell = (GridCell *)[grid dequeueReusableCell];
	
	if (cell == nil) {
#if ! __has_feature(objc_arc)
		cell = [[[GridCell alloc] init] autorelease];
# else
        cell = [[GridCell alloc] init];
# endif
        
    }
	int pos  = rowIndex*3+columnIndex;
	cell.label.text = [popDownArr objectAtIndex:pos];
	
	CMCategoryItem* pCategoryChildItem = m_pCategoryItem->GetChildItem(pos);
	if(pCategoryChildItem)
	{
		const char*  sid = pCategoryChildItem->sID;
		
			if(m_pWebImage->GetFromUrl(0,pCategoryChildItem->sImage))
			{	
				UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(pCategoryChildItem->sImage)]];// m_image;
				cell.thumbnail.image = loadImage;
				
			}
			else
			{
				NSString *sFlag = [NSString stringWithUTF8String:m_sFlag];
				if ([sFlag isEqualToString:@"course"])
				{
					if(strcmp(sid, "5") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Recommand"];												
					}
					else if(strcmp(sid, "10") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"ProfessionalSkills"];
					}
					else if(strcmp(sid, "15") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Market"];
					}
					else if(strcmp(sid, "20") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"HumanResource"];
					}												 
					else if(strcmp(sid, "25") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"CustomerService"];						
					}
					else if(strcmp(sid, "30") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"CourseDefault"];
					}
					else if(strcmp(sid, "35") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"OfficeSkills"];
					}
					else if(strcmp(sid, "40") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"CourseDefault"];
					}
					else if(strcmp(sid, "45") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Laws"];						
					}
					else if(strcmp(sid, "50") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Stratege"];
					}
					else if(strcmp(sid, "55") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Management"];
					}
					else if(strcmp(sid, "60") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"PublicCourse"];
					}
					else if(strcmp(sid, "65") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Courses"];
					}
					else if(strcmp(sid, "70") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"CourseDefault"];
					}
					else if(strcmp(sid, "75") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Security"];
					}
					else if(strcmp(sid, "80") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Soulmate"];
					}
					else if(strcmp(sid, "85") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Marriage"];						
					}
					else if(strcmp(sid, "90") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"SelfDicipline"];
					}
					else if(strcmp(sid, "95") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"NewTraining"];
					}
					else if(strcmp(sid, "98") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"ManageSkills"];
					}
					else if(strcmp(sid, "100") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Fromulas"];
					}
					else
						cell.thumbnail.image = [UIImage imageNamed:@"CourseDefault"];
				}
				else if([sFlag isEqualToString:@"news"]) 
				{
					if(strcmp(sid, "105") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Hotlines"];
					}
					else if(strcmp(sid, "110") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Annnouce"];
					}
					else if(strcmp(sid, "115") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Training"];
					}
					else if(strcmp(sid, "120") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"Industry"];
					}
					else if(strcmp(sid, "125") == 0)
					{
						cell.thumbnail.image = [UIImage imageNamed:@"News"];
					}
					else
						cell.thumbnail.image = [UIImage imageNamed:@"News"];
					
				}
		}
	}
	
	return cell;
}

- (void) gridView:(UIGridView *)grid didSelectRowAt:(int)rowIndex AndColumnAt:(int)colIndex
{
    [browserview setCurrentPos:rowIndex*3+colIndex];
    [browserview LoadData:m_sFlag refresh:true];
	[self popDownList];
    //create title view for navigation bar
     //[titleBtn setTitle:[popDownArr objectAtIndex:rowIndex*3+colIndex]  forState:UIControlStateNormal];
}


- (void)scrollToTop{
    if ([browserview superview] && browserview.tableviewlist != nil){
        [browserview.tableviewlist setContentOffset:CGPointMake(0, 0) animated:YES];
    }
    else if ([trainlistview superview] && trainlistview.tableviewlist != nil){
        [trainlistview.tableviewlist setContentOffset:CGPointMake(0, 0) animated:YES];
    }
}

//- (void)stopScrolling{
//    if ([browserview superview] && browserview.tableviewlist != nil && browserview.tableviewlist.decelerating){
//            [browserview.tableviewlist setContentOffset:browserview.tableviewlist.contentOffset animated:YES];
//    }
//    else if ([trainlistview superview] && trainlistview.tableviewlist != nil && trainlistview.tableviewlist.decelerating){
//        [trainlistview.tableviewlist setContentOffset:trainlistview.tableviewlist.contentOffset animated:YES];
//    }
//}

@end