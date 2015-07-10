//
//  CMNavControl.h
//  MLPlayer
//
//  Created by Tim on 12-12-26.
//  Copyright 2013 w. All rights reserved.
//

//btn1 = [UIButton buttonWithType:UIButtonTypeCustom];
//btn1.frame = CGRectMake(100, 200, 72, 0);
//CGRect originalFrame1 = CGRectMake(0, 113, 150, 37);
//[UIView animateWithDuration:0.5 animations:^{btn1.frame = originalFrame1 ;}];

#import "CMSearchHotControl.h"
#import "CMSearchControl.h"
#import "CMQaSearchControl.h"
#import "CMSearchQRCode.h"

#define pagecount   7
#define BUTTON_WIDTH_TWO     40.0//61.0
#define BUTTON_WIDTH_THREE   55.0//76.0
#define BUTTON_WIDTH_FOUR    70.0//91.0
#define BUTTON_WIDTH_DEFAULTE  99.0//120.0
#define BUTTON_HEIGHT        28.0//38.0

typedef enum {
    SearchItemTypeCageGory,
    SearchItemTypeHighUse
}SearchItemType;


@implementation CMSearchHotControl
@synthesize flag;
@synthesize blankView=_blankView;
@synthesize m_pActivityView;
@synthesize searchBtn   = _searchBtn;
@synthesize searchField = _searchField;
@synthesize searchCourse = m_pSearchCourse;
@synthesize autoarray;
- (void)dealloc {
    
    if (m_pSearchCourse) {
        m_pSearchCourse->Cancel();
    }
    
    CMSearchHotKey::GetInstance()->SetListener(NULL);
    CMSearchHotKey::GetInstance()->SetUserData(NULL);
    
    CMRELEASE(flag);
    CMRELEASE(hotkeyarray);
    CMRELEASE(m_pActivityView);
    CMRELEASE(_searchField);
    CMRELEASE(_blankView);
    CMRELEASE(suggList);
    CMRELEASE(autoarray);
    SAFEDELETE(m_pSearchCourse);
    SAFEDELETE(m_pHistoryListener);
	SAFEDELETE(m_pListener);
    
    if (m_pSearch) {
        m_pSearch->Cancel();
        m_pSearch->SetUserData(NULL);
    }
    
    SAFEDELETE(m_pQuicklyListener);
    SAFEDELETE(m_pSearch);
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self getHistoryList];
    if(!m_pQuicklyListener)
        m_pQuicklyListener = new CMSearchQuicklyUpdateDataListener();
    
    if (!m_pSearch) {
        m_pSearch = new CMSearch(m_pQuicklyListener);
    }
    
    m_pSearch->SetUserData((__bridge void*)self);
    
    if(!m_pListener)
        m_pListener = new CMSearchHotUpdateDataListener();
    if(!m_pHistoryListener)
        m_pHistoryListener = new CMSearchHistoryListener();
    
    [self refreshData];
    _searchField.text = @"";
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.titleLabel.text = self.navigationItem.title;
    
	CGRect f = self.view.bounds;
	
	CGRect rc = f;
	rc.size.height = 48;
    //底
    UIImageView* inputBack=[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 42)];
    UIImage *image = [UIImage imageNamed:@"searchbar"];
    UIEdgeInsets insets = UIEdgeInsetsMake(0, 1, 0, 1);
    image = [image resizableImageWithCapInsets:insets];
    [inputBack setImage:image];
    [inputBack setUserInteractionEnabled:YES];
    [self.view addSubview:inputBack];
    
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setFrame:CGRectMake(0, 0, 44, 40)];
    btn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
    [btn setImage:[UIImage imageNamed:@"code"] forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(gotoSweep:) forControlEvents:UIControlEventTouchUpInside];
    
    
    //只有课程才显示扫一扫
    if ([self.flag isEqualToString:@"course"])
    {
        UIBarButtonItem *rightitem = [[UIBarButtonItem alloc]initWithCustomView:btn];
        self.navigationItem.rightBarButtonItem = rightitem;
    }
    else
    {
        self.navigationItem.rightBarButtonItem = nil;
    }
    
    
    //放大镜
    UIImage* zoominIconImg = [UIImage imageNamed:@"search_icon"];
    
# if ! __has_feature(objc_arc)
    UIImageView* zoominIconView = [[[UIImageView alloc]initWithFrame:CGRectMake(20, 15, zoominIconImg.size.width, zoominIconImg.size.height)] autorelease];
# else
    UIImageView* zoominIconView = [[UIImageView alloc]initWithFrame:CGRectMake(20, 15, zoominIconImg.size.width, zoominIconImg.size.height)];
# endif
    [zoominIconView setImage:zoominIconImg];

    
    _searchField = [[UITextField alloc]initWithFrame:CGRectMake(34, 5, UI_IOS_WINDOW_WIDTH-50, 34.5)];
    _searchField.backgroundColor = [UIColor clearColor];
    _searchField.font = [UIFont systemFontOfSize:16.0];
    _searchField.delegate = self;
    _searchField.layer.cornerRadius = 2.0;
    _searchField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;

    _searchField.returnKeyType = UIReturnKeySearch;
    _searchField.placeholder = I(@"关键字");
    [inputBack addSubview:_searchField];
    
    [inputBack addSubview:zoominIconView];

    

	_blankView=[[UIScrollView alloc]initWithFrame:CGRectMake(0, rc.size.height, self.view.frame.size.width, UI_IOS_WINDOW_HEIGHT-20-44-rc.size.height)];
	[_blankView setBackgroundColor:kColorBackground];
    _blankView.clipsToBounds = YES;
    _blankView.pagingEnabled = YES;
    [_blankView setAutoresizesSubviews:YES];
    _blankView.showsHorizontalScrollIndicator = NO;
    _blankView.showsVerticalScrollIndicator = NO;
    _blankView.delegate = self;
    _blankView.canCancelContentTouches = YES;
	[self.view addSubview:_blankView];
    [self.view insertSubview:inputBack aboveSubview:_blankView];
    CMRELEASE(inputBack);
    
    
    //热词搜索UI布局
    rc = f;
	rc.origin.y = 48;
	rc.size.height = 282;
	curView = [[UIView alloc] initWithFrame:rc];
    curView.hidden = YES;
	curView.backgroundColor = kColorBackground;

    UISwipeGestureRecognizer *recognizer;
	recognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeFrom:)];
	[recognizer setDirection:(UISwipeGestureRecognizerDirectionRight)];
	[curView addGestureRecognizer:recognizer];
    CMRELEASE(recognizer);
    
	
	recognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(handleSwipeFrom:)];
	[recognizer setDirection:(UISwipeGestureRecognizerDirectionLeft)];
	[curView addGestureRecognizer:recognizer];
    CMRELEASE(recognizer);
	
	pagecontrol = [[UIPageControl alloc] init];
	pagecontrol.numberOfPages = 0;
	pagecontrol.currentPage = 0;
	pagecontrol.userInteractionEnabled = NO;
    pagecontrol.hidden = YES;
	pagecontrol.backgroundColor = [UIColor clearColor];
	
	rc.size.width = pagecontrol.numberOfPages*15;
	rc.origin.x = (f.size.width - rc.size.width)/2;
	rc.origin.y = UI_IOS_WINDOW_HEIGHT - 64 - 48 - 50;
	rc.size.height = 30;
	pagecontrol.frame = rc;
	[self.blankView addSubview:pagecontrol];
    [self.view addSubview:curView];
    CMRELEASE(pagecontrol);

    //添加历史搜索下拉菜单
    [self getHistoryList];
    suggList = [[SuggestionsList alloc]init];
    suggList.view.backgroundColor = [UIColor whiteColor];
	suggList.view.frame = CGRectMake(28.0, 48.0, 260.0, 0);
	suggList.delegate = self;
//	[self.view addSubview:suggList.view];


}

- (void)refreshData{
    [tool ShowActivityIndicator:self.view];
    
    if ([flag isEqualToString:@"course"]) {
        if(!m_pSearchCourse)
        {
            m_pSearchCourse = new CMSearchCourse();
        }
        m_pSearchCourse->SetListener(m_pListener);
        m_pSearchCourse->SetUserData((__bridge void*)self);
        m_pSearchCourse->GetCourseKey();
    }
    else{
        CMSearchHotKey::GetInstance()->SetListener(m_pListener);
        CMSearchHotKey::GetInstance()->SetUserData((__bridge void*)self);
        if(!CMSearchHotKey::GetInstance()->GetHotKey())
        {
            [tool DisimissActivityIndicator];
        }
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
	[_searchField resignFirstResponder];
}

#pragma mark - UI Init Method

- (UIView *)getCateGoryTitleViewWithTitle:(NSString*)titleStr
{
    UIView *titleView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 28)];
    
    titleView.backgroundColor = [UIColor clearColor];
    
    CGSize titleSize = [titleStr sizeWithFont:[UIFont systemFontOfSize:kTextSizeSml] constrainedToSize:CGSizeMake(MAXFLOAT, 28)];
    UILabel *labelTitle = [[UILabel alloc]initWithFrame:CGRectMake(14, 0, titleSize.width + 10, 28)];
    labelTitle.textColor = kColorButtonTitle;
    labelTitle.font = [UIFont systemFontOfSize:kTextSizeSml];
    labelTitle.text = titleStr;
    labelTitle.backgroundColor = [UIColor clearColor];
    [titleView addSubview:labelTitle];
    
    UIView *separatorView = [[UIView alloc]initWithFrame:CGRectMake(labelTitle.frame.origin.x + labelTitle.frame.size.width, 15, titleView.bounds.size.width - labelTitle.frame.origin.x - labelTitle.frame.size.width - 23, 1)];
    separatorView.backgroundColor = UIColorRGB(0xc4c4c4);
    [titleView addSubview:separatorView];
    
    return titleView;
}

#pragma mark search history
- (void)getHistoryList{
	suggList.stringsArray = [self GetAutoList];
}

- (void)passValue:(NSString *)value{
	if (value)
	{
		_searchField.text = value;
		[self setSugestListHidden:YES];
        isCategorySearch = NO;
        [self gotosearchKey:value title:value];
	}
}

- (void)setSugestListHidden:(BOOL)hidden
{
	NSInteger height = hidden ? 0 : suggList.matchedStrings.count*30;
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:.2];
	[suggList.view setFrame:CGRectMake(30.0, 35.5, 265.0, MIN(height,150))];
	[UIView commitAnimations];
}

-(NSMutableArray*)GetAutoList   //获取历史搜索数据
{
	if(!autoarray)
		autoarray = [[NSMutableArray alloc] init];
	[autoarray removeAllObjects];
    CMSearch* pSearch = new CMSearch(m_pHistoryListener);
    pSearch->SetUserData((__bridge void*)self);
	if(pSearch)
	{
		for(int i=0; i<pSearch->GetRecentKeyCount();i++)
		{
			const char* pkey = pSearch->GetRecentKeyItem(i);
			if(pkey)
				[autoarray addObject:[NSString stringWithUTF8String:pkey]];
		}
	}
    SAFEDELETE(pSearch);
    return autoarray;
}

- (void)loadhotkey
{
	if(!hotkeyarray)
		hotkeyarray = [[NSMutableArray alloc] init];
	[hotkeyarray removeAllObjects];
    
	if([flag isEqualToString:@"course"])
	{
        if (m_pSearchCateItem == nil)
        {
            m_pSearchCateItem = new TSearchItem;
        }
        NSInteger count = m_pSearchCourse->GetItemCount();
		for (int i = 0; i < count; i ++) {
           m_pSearchCourse->GetItem(i, m_pSearchCateItem);
            NSString *title = NSStringFrom(m_pSearchCateItem->sTitle);//[NSString stringWithUTF8String:searchItem.sTitle];
            NSString *sid = NSStringFrom(m_pSearchCateItem->sID);//[NSString stringWithUTF8String:searchItem.sID];
            NSDictionary *sDic = [NSDictionary dictionaryWithObjectsAndKeys:title,@"sTitle",sid,@"sID", nil];
            [hotkeyarray addObject:sDic];
        }
        [self showCategoryKey];
	}
	else if([flag isEqualToString:@"news"])
	{
        for(int i=0; i<CMSearchHotKey::GetInstance()->GetNewsHotKeyItemCount();i++)
		{
			const char* skey = CMSearchHotKey::GetInstance()->GetNewsHotKeyItem(i);
			if(!skey)
				break;
			[hotkeyarray addObject:[NSString stringWithUTF8String:skey]];
		}
        [self showhotkey];
	}
    else if([flag isEqualToString:@"qa"])
	{
        for(int i=0; i<CMSearchHotKey::GetInstance()->GetQaHotKeyItemCount();i++)
		{
			const char* skey = CMSearchHotKey::GetInstance()->GetQaHotKeyItem(i);
			if(!skey)
				break;
			[hotkeyarray addObject:[NSString stringWithUTF8String:skey]];
		}
        [self showhotkey];
	}
}

- (void)selectHighSearchKey:(id)sender
{
    TSearchItem *highSearchItem = m_pSearchCourse->GetHighSearch();
    
    TSearchItem *item = highSearchItem->GetChildItem(((UIButton*)sender).tag);
    
    item->SetSearchCountSign();
    m_pSearchCourse->Update(item);
    
    [_searchField resignFirstResponder];
    NSString* skey = NSStringFrom(item->sID);
    NSString* title = NSStringFrom(item->sTitle);
    if(!skey)
        return;
    isCategorySearch = YES;
    [self gotosearchKey:skey title:title];
}

-(void)seletCategoryKey:(id)sender
{
    [self setSugestListHidden:YES];
    
    NSInteger cateGoryIndex = (((UIButton*)sender).tag) / 1000;//分类标记
    NSInteger itemIndex = (((UIButton*)sender).tag) % 1000;//按钮标记
    
    
    m_pSearchCourse->GetItem(cateGoryIndex, m_pSearchCateItem);
    
    TSearchItem *item = m_pSearchCateItem->GetChildItem(itemIndex);
    
    item->SetSearchCountSign();
    m_pSearchCourse->Update(item);
    
    [_searchField resignFirstResponder];
	NSString* skey = NSStringFrom(item->sID);
    NSString* title = NSStringFrom(item->sTitle);
	if(!skey)
		return;
    isCategorySearch = YES;
	[self gotosearchKey:skey title:title];
}

-(void)selethotkey:(id)sender
{
    [self setSugestListHidden:YES];
    NSString* skey = (NSString*)[hotkeyarray objectAtIndex:((UIButton*)sender).tag];
	if(!skey)
		return;
    isCategorySearch = NO;
	[self gotosearchKey:skey title:skey];
}

- (double)getNextBtnWidth:(int)length{
    double width = 0.0;
    switch (length) {
        case 0:
        {
            width = 0;
        }
            break;
		case 2:
        {
            width = BUTTON_WIDTH_TWO;
        }
			break;
		case 3:
        {
            width = BUTTON_WIDTH_THREE;
        }
			break;
		case 4:
        {
            width = BUTTON_WIDTH_FOUR;
        }
			break;
		default:
            width = BUTTON_WIDTH_DEFAULTE;
			break;
	}
	return width;
}

- (UIButton*)getbtn:(NSString*)txt tag:(int)tag length:(int)length type:(SearchItemType)type
{
	UIButton* btn = [UIButton buttonWithType:UIButtonTypeCustom];
	btn.tag = tag;
    
    if (type == SearchItemTypeCageGory)
    {
        [btn addTarget:self action:@selector(seletCategoryKey:) forControlEvents:UIControlEventTouchUpInside];
    }
    else
    {
        [btn addTarget:self action:@selector(selectHighSearchKey:) forControlEvents:UIControlEventTouchUpInside];
    }
	btn.titleLabel.font = [UIFont systemFontOfSize:kTextSizeSml];
	btn.titleLabel.text = txt;
    [btn setTitleColor:UIColorRGB(0x5c5c5c) forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateHighlighted];
    [btn setBackgroundImage:[UIImage imageNamed:@"search_markbtn_normal"] forState:UIControlStateNormal];
    [btn setBackgroundImage:[UIImage imageNamed:@"search_markbtn_select"] forState:UIControlStateHighlighted];
	[btn setTitle:txt forState:UIControlStateNormal];
	switch (length) {
		case 2:
			{
				btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_TWO, BUTTON_HEIGHT);
			}
			break;
		case 3:
			{
				btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_THREE, BUTTON_HEIGHT);
			}
			break;
		case 4:
			{
				btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_FOUR, BUTTON_HEIGHT);
			}
			break;
		default:
            btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_DEFAULTE, BUTTON_HEIGHT);
			break;
	}
	return btn;
}


#pragma mark - search quickly
-(void)Search:(const char*)stype value:(const char*)stxt
{
    if(!stype || !stxt)
        return;

    if(m_pSearch->QuickSearch(stype,stxt))
        ;
    
}

- (void)getQuickSearchList{
    
 //   suggList.stringsArray = [self GetAutoList];
    int count = m_pSearch->GetItemCount();
    NSMutableArray *searchArr = [[NSMutableArray alloc] initWithCapacity:count];
    for (int i = 0; i < count; i++) {
        
        TBrowserItem* browserItem = NULL;
        
        if(m_pSearch->GetItemModel(i)==0)
        {
            
            browserItem = new TClassItem();
            
        }
        else
        {
            browserItem = new TCoursewareItem();
        }
        
        m_pSearch->GetItem(i, browserItem);

        NSString *title = [NSString stringWithUTF8String:browserItem->sTitle];
        
        [searchArr addObject:title];
        
    }
    suggList.matchedStrings = searchArr;

    [suggList updateView];

    [self setSugestListHidden:NO];
}


#pragma mark - hot key or category key
- (void)showCategoryKey{
    if([hotkeyarray count] > 0)
	{
		;
	}
	else
	{
        [tool DisimissActivityIndicator];
        return;
	}
    
    [_blankView.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    
    CGRect visibleBounds = [self.view bounds];
    int visibleWidth = visibleBounds.size.width;
    double spaceHeight = (UI_IOS_WINDOW_WIDTH - 4 * BUTTON_WIDTH_FOUR ) / 5;//10.0;
    double spaceWidth  = (UI_IOS_WINDOW_WIDTH - 4 * BUTTON_WIDTH_FOUR ) / 5;//10.0;
    
    int count  = [hotkeyarray count];
    CGFloat yoff = spaceHeight;
    
    int x = spaceWidth;
    int y = spaceHeight;
    
    TSearchItem *highSearchItem = m_pSearchCourse->GetHighSearch();
    if (highSearchItem->ChildItemCount() > 0)
    {
        UIView *titleView = [self getCateGoryTitleViewWithTitle:I(@"常用搜索")];
        CGRect f = titleView.frame;
        f.origin.y = y;
        [titleView setFrame:f];
        [_blankView addSubview:titleView];
        
        y += titleView.frame.size.height;
        
        for (int j = (highSearchItem->ChildItemCount() - 1); j >= 0; j--)
        {
            TSearchItem *currItem = highSearchItem->GetChildItem(j);
            TSearchItem *nextItem;
            NSString *title = NSStringFrom(currItem->sTitle);
            NSString *nexttile = nil;
            if (j + 1 < highSearchItem->ChildItemCount()) {
                nextItem = highSearchItem->GetChildItem(j+1);
                nexttile = NSStringFrom(nextItem->sTitle);
            }
            
            int length = [title length];
            int nextlength = [nexttile length];
            
            NSInteger buttonTag = j;
            
            UIButton* btn = [self getbtn:title tag:buttonTag length:length type:SearchItemTypeHighUse];
            
            CGRect newFrame = CGRectMake(x, y, BUTTON_WIDTH_FOUR, btn.frame.size.height);
            [btn setFrame:newFrame];
            
            [_blankView addSubview:btn];
            
            if (highSearchItem->ChildItemCount() - j >= 8)
            {
                break;
            }
            
            // Adjust the position.
            double lastSpace = visibleWidth - CGRectGetMaxX(btn.frame) - spaceWidth * 2;
            double nextBtnWidth = [self getNextBtnWidth:nextlength];
            if ( lastSpace - nextBtnWidth < 0.0 && j > 0) {
                // Start new row.
                x = spaceWidth;
                y += CGRectGetHeight(btn.frame) + spaceHeight;
            } else {
                x += CGRectGetWidth(btn.frame) + spaceWidth;
            }
        }
        y += BUTTON_HEIGHT + spaceHeight;
    }
    
    for (int i = 0; i < count; i++)
    {
        m_pSearchCourse->GetItem(i, m_pSearchCateItem);
        UIView *titleView = [self getCateGoryTitleViewWithTitle:[hotkeyarray[i]objectForKey:@"sTitle"]];
        CGRect f = titleView.frame;
        f.origin.y = y;
        [titleView setFrame:f];
        [_blankView addSubview:titleView];
        
        y += titleView.frame.size.height;
        x = spaceWidth;
        
        for (int j = 0; j < m_pSearchCateItem->ChildItemCount(); j++)
        {
            TSearchItem *currItem = m_pSearchCateItem->GetChildItem(j);
            TSearchItem *nextItem;
            NSString *title = NSStringFrom(currItem->sTitle);
            NSString *nexttile = nil;
            if (j + 1 < m_pSearchCateItem->ChildItemCount()) {
                nextItem = m_pSearchCateItem->GetChildItem(j+1);
                nexttile = NSStringFrom(nextItem->sTitle);
            }
            
            int length = [title length];
            int nextlength = [nexttile length];
            
            NSInteger buttonTag = i * 1000 + j;
            
            UIButton* btn = [self getbtn:title tag:buttonTag length:length type:SearchItemTypeCageGory];
            
            CGRect newFrame = CGRectMake(x, y, BUTTON_WIDTH_FOUR, btn.frame.size.height);
            [btn setFrame:newFrame];
            
            [_blankView addSubview:btn];
            
            // Adjust the position.
            double lastSpace = visibleWidth - CGRectGetMaxX(btn.frame) - spaceWidth * 2;
            double nextBtnWidth = [self getNextBtnWidth:nextlength];
            if ( lastSpace - nextBtnWidth < 0.0&& j + 1 < m_pSearchCateItem->ChildItemCount()) {
                // Start new row.
                x = spaceWidth;
                y += CGRectGetHeight(btn.frame) + spaceHeight;
            } else {
                x += CGRectGetWidth(btn.frame) + spaceWidth;
            }
        }
        y += BUTTON_HEIGHT + spaceHeight;
    }
    
    // Set our initial origin.
//    int x = spaceWidth;
//    int y = spaceHeight;
//    
//    for (int i = 0; i < count; i ++) {
//        NSString *title = [[hotkeyarray objectAtIndex:i] objectForKey:@"sTitle"];
//        NSString *nexttile = nil;
//        if (i + 1 < count) {
//            nexttile = [[hotkeyarray objectAtIndex:i + 1] objectForKey:@"sTitle"];
//        }
//        
//        int length = [title length];
//        int nextlength = [nexttile length];
//        
//        UIButton* btn = [self getbtn:title tag:i length:length];
//        
//        CGRect newFrame = CGRectMake(x, y, btn.frame.size.width, btn.frame.size.height);
//        [btn setFrame:newFrame];
//        
//		[_blankView addSubview:btn];
//        
//        // Adjust the position.
//        double lastSpace = visibleWidth - CGRectGetMaxX(btn.frame) - spaceWidth * 2;
//        double nextBtnWidth = [self getNextBtnWidth:nextlength];
//        if ( lastSpace - nextBtnWidth < 0.0) {
//            // Start new row.
//            x = spaceWidth;
//            y += CGRectGetHeight(btn.frame) + spaceHeight;
//        } else {
//            x += CGRectGetWidth(btn.frame) + spaceWidth;
//        }
//    }
    if (y < UI_IOS_WINDOW_HEIGHT-20-44-48-BUTTON_HEIGHT) {
        y = _blankView.frame.size.height + 1.0;
    }
    else{
        y += spaceHeight + BUTTON_HEIGHT + 48;
    }
    
    [_blankView setContentSize:CGSizeMake(UI_IOS_WINDOW_WIDTH, y)];
    [tool DisimissActivityIndicator];
}

- (void)showhotkey
{
    if([hotkeyarray count] > 0)
	{
		pagecontrol.hidden = NO;
		curView.hidden = NO;
		int count  = [hotkeyarray count]/pagecount;
		if([hotkeyarray count]%pagecount > 0)
			count++;
		
		pagecontrol.numberOfPages = count;
	}
	else
	{
		pagecontrol.hidden = YES;
		curView.hidden = YES;
        [tool DisimissActivityIndicator];
        return;
	}
    
    [curView.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
	for(int i = pagecontrol.currentPage*pagecount;i<(pagecontrol.currentPage+1)*pagecount && i< [hotkeyarray count]; i++)
	{
		UIButton* btn = [self getbtn:[hotkeyarray objectAtIndex:i] tag:i];
		[curView addSubview:btn];
	}
    
	if([pagecontrol numberOfPages] > 0)
	{
		
		curView.alpha = 0;
		curView.transform = CGAffineTransformMakeScale(0.1, 0.1);
		[UIView animateWithDuration:0.5
						 animations:^{
							 curView.alpha = 1;
							 curView.transform = CGAffineTransformMakeScale(1,1);
							 
						 }];
		//[self updateDots];
	}
    [tool DisimissActivityIndicator];

}

-(void)gotosearchKey:(NSString*)skey title:(NSString *)title
{
	if([flag isEqualToString:@"course"] || [flag isEqualToString:@"news"])
	{
		CMSearchControl* searchControl = [[CMSearchControl alloc] init];
		searchControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;	
		searchControl.navigationController.navigationBarHidden = NO;
		searchControl.tabBarController.tabBar.hidden = YES;
		searchControl.hidesBottomBarWhenPushed = YES;
		[searchControl.navigationItem setTitle:title];
		searchControl.type = flag;
		searchControl.key = skey;
        searchControl.title = title;
        searchControl.isCategorySearch = isCategorySearch;
		[[self navigationController] pushViewController:searchControl animated:YES];
        CMRELEASE(searchControl);
	}
	else if([flag isEqualToString:@"qa"])
	{
		CMQaSearchControl* searchControl = [[CMQaSearchControl alloc] init];
		searchControl.key = skey;
		searchControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;	
		searchControl.navigationController.navigationBarHidden = NO;
		searchControl.tabBarController.tabBar.hidden = YES;
		searchControl.hidesBottomBarWhenPushed = YES;
		[searchControl.navigationItem setTitle:skey];
		[[self navigationController] pushViewController:searchControl animated:YES];
        CMRELEASE(searchControl);
	}
    suggList.stringsArray = [self GetAutoList];

}

- (void)searchButtonClicked{
    [self setSugestListHidden:YES];
    [_searchField resignFirstResponder];
    if ([[_searchField.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] isEqualToString:@""] || [_searchField.text length] < 1)
    {
        _searchField.text = @"";
        [tool ShowAlert:I(@"请输入搜索内容!")];
    }
    else
    {
        isCategorySearch = NO;
        [self gotosearchKey:_searchField.text title:_searchField.text];
    }
}

- (void)handleSwipeFrom:(UISwipeGestureRecognizer*)tap
{
    [_searchField resignFirstResponder];
	if([pagecontrol numberOfPages] <= 1)
		return;
	if(tap.direction == UISwipeGestureRecognizerDirectionLeft || tap.direction == UISwipeGestureRecognizerDirectionRight)
	{
		int cur = pagecontrol.currentPage;
		if(tap.direction == UISwipeGestureRecognizerDirectionRight)
			cur = [self validPageValue:cur-1];
		else
			cur = [self validPageValue:cur+1];
		[UIView animateWithDuration:0.5
						 animations:^{
							 curView.alpha = 0;
                             if(__iOS8){
                                 curView.transform = CGAffineTransformMakeScale(1.1, 1.1);
                             }
                             else{
                                 curView.transform = CGAffineTransformMakeScale(0.1, 0.1);
                             }
                         }
						 completion:^(BOOL finished){ }];//curView.hidden = YES;
		pagecontrol.currentPage = cur;
		[self showhotkey];
	}
	
}

-(void)handleTap:(UITapGestureRecognizer *)tap{
    [_searchField resignFirstResponder];
}

- (int)validPageValue:(int)value
{
	
	if(value == -1) value = pagecontrol.numberOfPages - 1;
	if(value == pagecontrol.numberOfPages) value = 0;
	
	return value;
	
}

- (UIButton*)getbtn:(NSString*)txt tag: (int)tag;
{
	UIButton* btn = [UIButton buttonWithType:UIButtonTypeCustom];
	btn.tag = tag;
	[btn addTarget:self action:@selector(selethotkey:) forControlEvents:UIControlEventTouchUpInside];
	btn.titleLabel.font = [UIFont systemFontOfSize:kTextSizeSml];
	btn.titleLabel.text = txt;
	//btn.backgroundColor = [UIColor clearColor];
	[btn setTitle:txt forState:UIControlStateNormal];
	switch (tag%7) {
		case 2:
        {
            [btn setTitleColor: [UIColor magentaColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(110, 52, 100, 20);
        }
			break;
		case 1:
        {
            [btn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(10, 102, 100, 20);
        }
			break;
		case 0:
        {
            [btn setTitleColor:[UIColor brownColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(110, 152, 100, 20);
        }
			break;
		case 3:
        {
            [btn setTitleColor:[UIColor greenColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(210, 102, 100, 20);
        }
			break;
		case 4:
        {
            [btn setTitleColor:[UIColor cyanColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(10, 202, 100, 20);
        }
			break;
		case 5:
        {
            [btn setTitleColor:[UIColor orangeColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(210, 202, 100, 20);
        }
			break;
		case 6:
        {
            [btn setTitleColor:[UIColor purpleColor] forState:UIControlStateNormal];
            btn.frame = CGRectMake(100, 252, 100, 20);
        }
			break;
		default:
			break;
	}
	return btn;
}


#pragma mark - UITextfield 
- (void)textFieldDidBeginEditing:(UITextField *)textField           // became first responder
{
}
- (void)textFieldDidEndEditing:(UITextField *)textField             // may be called if forced even if shouldEndEditing returns NO (e.g. view removed from window) or endEditing:YES called
{
 //   [self setSugestListHidden:YES];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField              // called when 'return' key pressed. return NO to ignore.
{
    [self searchButtonClicked];

    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string  // return NO to not change text
{
    //得到输入结束后的内容
    NSString* content ;
    if([string isEqualToString:@""])
        content = [textField.text substringToIndex:[textField.text length]-1];
    else
        content = [NSString stringWithFormat:@"%@%@",textField.text,string];
    
    
    
    if ([content length] == 0 && ([content isEqualToString:@""] || !content)) { //判断搜索框 内容是否为nil，当删除textfield。text内容时，textField保留当前textField。text的值，string为@“”替代即将删除的text
        [self setSugestListHidden:YES];
    }
    else{
//        if ([flag isEqualToString:@"qa"]) {
            [self setSugestListHidden:![suggList ChangeText:content]];
//        }
//        else
//             [self Search:[flag UTF8String] value:[content UTF8String]];
    }
    
	return YES;
}

-(void)gotoSweep:(id)sender
{
    
    CMSearchQRCode *QRcodeControl = [[CMSearchQRCode alloc]init];
    //[QRcodeControl setSignViewControl:self];  
    [self.navigationController pushViewController:QRcodeControl animated:YES];
    
    
}


- (void)scrollViewDidScroll:(UIScrollView *)scrollView{
    [_searchField resignFirstResponder];
    [self setSugestListHidden:YES];
}

@end
