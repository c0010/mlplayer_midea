    //
//  CMHomeControl.m
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import "CMQaControl.h"
#import "CMSearchHotControl.h"
#import "CMQuestionControl.h"
#import "CMQListControl.h"
//#import "MobClick.h"
#import "qa_ChoiceList.h"

#define  kCategoryListWidth 130
#define  kCategoryListHeight 220

@implementation CMQaControl

#pragma mark segment function

- (id)init
{    self = [super init];
    if (self) {
        self.categoryList = [[UITableView alloc]initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-kCategoryListWidth)/2, 6 , kCategoryListWidth, kCategoryListHeight)];
        self.categoryList.backgroundColor = [UIColor whiteColor];
//        self.categoryList.backgroundColor = [UIColor clearColor];

        [self.categoryList setIndicatorStyle:UIScrollViewIndicatorStyleWhite];
        self.categoryList.delegate = self;
        self.categoryList.dataSource=self;
        self.categoryList.hidden=YES;
        [self.categoryList setSeparatorStyle:UITableViewCellSeparatorStyleNone];
//        self.categoryList.separatorColor =[UIColor blackColor];
        
        //添加阴影
//        self.categoryList.layer.shadowColor=[UIColor blackColor].CGColor;
//        self.categoryList.layer.shadowOffset=CGSizeMake(1,5);
//        self.categoryList.layer.shadowOpacity=1;
//        self.categoryList.layer.shadowRadius=1;
        
        self.categoryList.layer.borderColor = kColorBackground.CGColor;
        self.categoryList.layer.borderWidth = 1;
        
        if ([self.categoryList respondsToSelector:@selector(setSeparatorInset:)]) {
            [self.categoryList setSeparatorInset:UIEdgeInsetsZero];
        }
        
        self.lblCategoryList=[[UIButton alloc]initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2-50, 12, 100, 26)];
        [self.lblCategoryList setBackgroundColor:[UIColor clearColor]];
        [self.lblCategoryList addTarget:self action:@selector(UpdateCategoryList) forControlEvents:UIControlEventTouchUpInside];
        
        
        self.downListIndicator = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"qalistArrow_down"]];
        [self.downListIndicator setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2+22, 16, 12, 12)];
        
        
        self.lblBack = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
        [self.lblBack setOpaque:NO];
        [self.lblBack addTarget:self action:@selector(UpdateCategoryList) forControlEvents:UIControlEventTouchUpInside];
        self.lblBack.hidden = YES;
        
        
        m_pQcategory =CMQACategory::GetInstance();

    }
    return self;
}

- (void)showChoiceList:(UIButton *)sender{
    NSArray *menuItems =
    @[
      [qa_ChoiceListItem menuItem:I(@"提问")
                     image:[UIImage imageNamed:@"pop_qa"]
                    target:self
                    action:@selector(gotoquestion)],
      
      [qa_ChoiceListItem menuItem:I(@"我的问答")
                     image:[UIImage imageNamed:@"pop_answer"]
                    target:self
                    action:@selector(gotomy)],
      
      [qa_ChoiceListItem menuItem:I(@"搜索")
                     image:[UIImage imageNamed:@"pop_search"]
                    target:self
                    action:@selector(gotosearch)],
    ];
    CGRect frame = CGRectMake(280.0, 0.0, 30, 62.0);
    [qa_ChoiceList showMenuInView:self.navigationController.view
                  fromRect:frame
                 menuItems:menuItems
                 transform:self.view.transform];
}


-(void)gotoquestion
{
	CMQuestionControl*	questioncontrol = [[CMQuestionControl alloc] init];
	questioncontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	questioncontrol.navigationController.navigationBarHidden = NO;
	questioncontrol.tabBarController.tabBar.hidden = YES;
	questioncontrol.hidesBottomBarWhenPushed = YES;
	questioncontrol.view.backgroundColor = [UIColor clearColor];
	[self.navigationController pushViewController:questioncontrol animated:YES];
    CMRELEASE(questioncontrol);
}

-(void)gotomy
{
	CMQListControl*	qlistcontrol = [[CMQListControl alloc] init];
    qlistcontrol.bIsShowTagbar = YES;
    qlistcontrol.bIsShowTabbar = NO;
	qlistcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	qlistcontrol.navigationController.navigationBarHidden = NO;
	qlistcontrol.tabBarController.tabBar.hidden = YES;
	qlistcontrol.hidesBottomBarWhenPushed = YES;
	qlistcontrol.view.backgroundColor = [UIColor clearColor];		
	[self.navigationController pushViewController:qlistcontrol animated:YES];
    CMRELEASE(qlistcontrol);
}
-(void)gotosearch
{
	CMSearchHotControl* searchControl = [[CMSearchHotControl alloc] init];
	
	searchControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;	
	searchControl.navigationController.navigationBarHidden = NO;
	searchControl.tabBarController.tabBar.hidden = YES;
	searchControl.hidesBottomBarWhenPushed = YES;
	[searchControl.navigationItem setTitle:I(@"搜索")];
	searchControl.flag = @"qa";
	[[self navigationController] pushViewController:searchControl animated:YES];
	CMRELEASE(searchControl);
}

#pragma mark Request Data
-(void)updateQalist
{
    
    
    
}


-(void)refreshQalist
{
    
}

#pragma mark UI Control
-(void)UpdateCategoryList
{
    
    if (CMGlobal::TheOne().IsOffline()) {
        [tool ShowError:-1];
        return;
    }
    
    if(self.categoryList.hidden == NO)
    {
        [self.categoryList flashScrollIndicators];
        if(m_pQcategory)
            m_pQcategory->CancelUpdate();
        self.categoryList.hidden = YES;
        
        self.lblBack.hidden=YES;
        
        [self.downListIndicator setImage:[UIImage imageNamed:@"qalistArrow_down"]];
        
        NSInteger titleLength = [self.titleLabel.text length];
        
        if(titleLength <6)
            [self.downListIndicator setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2+10+titleLength*8, 16, 12, 12)];
        else
            [self.downListIndicator setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2+10+titleLength*8, 16, 12, 12)];
        
        return;
    }
    self.lblBack.hidden=NO;
    
    [self.downListIndicator setImage:[UIImage imageNamed:@"qalistArrow_up"]];
    
    self.categoryList.hidden = NO;
    
    //清空数据
    if(m_pQcategory == NULL)
        m_pQcategory =CMQACategory::GetInstance();
    
    [tool ShowActivityIndicator:self.categoryList];
    
    if(m_pUpdataDataListerner == NULL)
        m_pUpdataDataListerner = new CMQAListCategoryUpdateDataListener();
    
    
    m_pQcategory->SetListener(m_pUpdataDataListerner);
    m_pQcategory->SetUserData(BridgeObjectToC(self));

    if(!m_pQcategory->UpdateData())
    {
        [tool DisimissActivityIndicator];
    }
    
    [self.categoryList reloadData];
    
}


-(void)refreshCategoryLit
{
    [tool DisimissActivityIndicator];
    
    //确定tableview高度
    NSInteger itemCount = 0;
    
    if(m_pQcategory==nil || m_pQcategory->TopItemCount()==0)
        itemCount = 1;
    else
    {
        if(m_pQcategory->TopItemCount() <= 5)
            itemCount = m_pQcategory->TopItemCount() > 1 ? m_pQcategory->TopItemCount() : 2;
        else
            itemCount = 5;
        
    }
    
    [self.categoryList setFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-kCategoryListWidth)/2, 6 , kCategoryListWidth, itemCount*44)];

    [self.categoryList reloadData];
    [self.categoryList flashScrollIndicators];
}



#pragma mark TableView

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
//    int height;
//    if(m_pQcategory==nil || m_pQcategory->TopItemCount()==0)
//        height=44;
//    else
//        height=44*m_pQcategory->TopItemCount()>UI_IOS_WINDOW_HEIGHT-70?UI_IOS_WINDOW_HEIGHT-70:44*m_pQcategory->TopItemCount();
//    self.categoryList.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-kCategoryListWidth)/2, 6 , kCategoryListWidth, height);
//    //[self.categoryList flashScrollIndicators];
//    [self.categoryList setIndicatorStyle:UIScrollViewIndicatorStyleWhite];
    //多的一个为“全部”
    if(m_pQcategory==nil || m_pQcategory->TopItemCount()==0)
        return 1;
    
    return (m_pQcategory->TopItemCount()+1);
    
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
#if !__has_feature(obj_arc)
	UITableViewCell *cell =  [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"qcategory"];
#else
    UITableViewCell *cell =  [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"qcategory"];
#endif
    if(indexPath.row == 0)
    {
        cell.textLabel.text = I(@"全部");

    }
    else
    {
        
        CMQACategoryItem* qcategoryItem = NULL;
        
        if(m_pQcategory->GetTopItem(indexPath.row-1))
        {
            
            qcategoryItem=m_pQcategory->GetTopItem(indexPath.row-1);
            NSString * str=[NSString  stringWithUTF8String:qcategoryItem->sCategoryTitle];
        
            cell.textLabel.text = [NSString stringWithFormat:@"%@",str];

        }
    }
    
   

    cell.textLabel.textAlignment = UITextAlignmentCenter;
    cell.textLabel.backgroundColor = [UIColor clearColor];
	
	cell.textLabel.font = [UIFont systemFontOfSize:14.0];
	cell.textLabel.textColor = [UIColor blackColor];
    cell.backgroundColor = [UIColor whiteColor];
    
    UIView *separator = [[UIView alloc]initWithFrame:CGRectMake(10, cell.bounds.size.height - 1, tableView.bounds.size.width - 20, 1)];
    separator.backgroundColor = kColorBackground;
    [cell.contentView addSubview:separator];
    
    cell.selectionStyle = UITableViewCellSelectionStyleGray;
    
//    CGSize imageSize = CGSizeMake(130, 44);
//    UIGraphicsBeginImageContextWithOptions(imageSize, 0, [UIScreen mainScreen].scale);
//    [[UIColor colorWithRed:0 green:0 blue:0 alpha:0.7] set];
//    UIRectFill(CGRectMake(0, 0, imageSize.width, imageSize.height));
//    UIImage *pressedColorImg = UIGraphicsGetImageFromCurrentImageContext();
//    UIGraphicsEndImageContext();
//    
//    UIImageView* imgViewBack = [[UIImageView alloc]initWithImage:pressedColorImg];
//    cell.selectedBackgroundView = imgViewBack;

	return cell;
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    
    if(indexPath.row == 0)
    {
        qlistview.categoryId  = @"";
        
        
        [qlistview automaticRefresh];
        
        self.titleLabel.text =I(@"全部");

    }
    else
    {
    
        CMQACategoryItem *item = NULL;

        item=m_pQcategory->GetTopItem(indexPath.row-1);
        
        if(item)
        {
            qlistview.categoryId = [NSString stringWithUTF8String:item->sID];
            
            [qlistview automaticRefresh];
            
            self.titleLabel.text =[NSString stringWithUTF8String:item->sCategoryTitle];
            
        }
    }
    
    [self UpdateCategoryList];
    
}




#pragma mark system function
-(void)viewWillAppear:(BOOL)animated 
{
    
    if(self.lblCategoryList)
        self.lblCategoryList.hidden = NO;
    
    if(self.downListIndicator)
        self.downListIndicator.hidden = NO;
    
		// 显示外部NavBar，隐藏内部NavBar
    self.navigationController.navigationBarHidden = NO;
    
   // [MobClick beginEvent:@"QATime"];
    
    qlistview.curpos=3;

    [LPanelTableview sharedLpanel].hidden=YES;
    

	[super viewWillAppear:animated];
	
}


- (void) viewWillDisappear:(BOOL)animated {

    if(self.lblCategoryList)
        self.lblCategoryList.hidden = YES;
    
    if(self.downListIndicator)
        self.downListIndicator.hidden = YES;
    
   // [MobClick endEvent:@"QATime"];
    [super viewWillDisappear:animated];
}
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {	
	
	[super viewDidLoad];
    
	UIButton *questionBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    questionBtn.frame = CGRectMake(0, 0, kBarItemWidth, kBarItemHeight);
    questionBtn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
    [questionBtn setImage:[UIImage imageNamed:@"pull_down"] forState:UIControlStateNormal];
//	[questionBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
//	[questionBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
	[questionBtn addTarget:self action:@selector(showChoiceList:) forControlEvents:UIControlEventTouchUpInside];
    
        
    
	UIBarButtonItem *rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:questionBtn];
	self.navigationItem.rightBarButtonItem = rightBarButtonItem;
    self.navigationItem.leftBarButtonItem = nil;
    CMRELEASE(leftview);
	
	

	//数据列表
	qlistview = [[CMQListView alloc] initWithFrame:CGRectMake(0, 0, 320, UI_IOS_WINDOW_HEIGHT-44-20) refresh:YES];
    [qlistview setIsUseCache:YES];
	[[self view] addSubview:qlistview];
    
    //自动刷新
    [qlistview automaticRefresh];
    

    //加入分类下来列表
    [qlistview addSubview:self.lblBack];

    [qlistview addSubview:self.categoryList];

    
    [self.navigationController.navigationBar addSubview:self.downListIndicator];

    [self.navigationController.navigationBar addSubview:self.lblCategoryList];
    
    

    
}
- (void)reloadTableview{
    [qlistview.tableviewlist reloadData];
}

-(void)refreshfunc
{
	[qlistview RefreshList];
}
-(void)gotorespond:(id)sender
{
    
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

- (UIEdgeInsets)itemFitDifferentVersion:(BOOL)leftItem
{
    if (__iOS7)
    {
        //leftItem YES表示左边item NO表示右边item
        if (leftItem)
        {
            return UIEdgeInsetsMake(0, -20, 0, 0);
        }
        else
        {
            return UIEdgeInsetsMake(0, 0, 0, -20);
        }
    }
    else
    {
        return UIEdgeInsetsMake(0, 0, 0, 0);
    }
}

- (void)dealloc {
    
    if(m_pQcategory)
    {
        m_pQcategory->CancelUpdate();
        
        m_pQcategory->SetListener(NULL);
        
        
        m_pQcategory->SetUserData(NULL);
    }
    
    CMRELEASE(_downListIndicator);
    CMRELEASE(_lblCategoryList);

    CMRELEASE(_categoryList);
    
    CMRELEASE(qlistview);
    
    
    
//    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"reloadTableview" object:nil];
#if !__has_feature(obj_arc)
#endif

}
@end
