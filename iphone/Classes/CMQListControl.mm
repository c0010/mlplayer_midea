    //
//  CMHomeControl.m
//  MLPlayer
//
//学习的二级菜单
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import "CMQListControl.h"
#import "CMSearchHotControl.h"
#import "CMQaCategoryControl.h"
#import "CMQuestionControl.h"


@implementation CMQListControl

-(void)gotoBack
{
	if(qlistview.tag)
	{
		int count = [self.navigationController.viewControllers count];
		[[NSNotificationCenter defaultCenter] postNotificationName:@"qarefresh" object:[self.navigationController.viewControllers objectAtIndex:count-2]  userInfo:nil];
	}
	[[self navigationController] popViewControllerAnimated:	YES];
}

#pragma mark system function
-(void)viewWillAppear:(BOOL)animated 
{ 
		// 显示外部NavBar，隐藏内部NavBar
	
    self.navigationController.navigationBarHidden = NO;
    
    CGRect rect = qlistview.frame;
    rect.size.height = UI_IOS_VC_HEIGHT;
    qlistview.frame = rect;
	[super viewWillAppear:animated];
	
}

- (void) viewWillDisappear:(BOOL)animated {

}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {	
	
	[super viewDidLoad];	
	self.title = I(@"我的问答");
    
    self.titleLabel.text = self.title;
    
	//搜索
	UIButton *searchbtn = [UIButton buttonWithType:UIButtonTypeCustom];
	searchbtn.frame = CGRectMake(0, 0, 40, 44);
    searchbtn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
	[searchbtn setImage:[UIImage imageNamed:@"NavSearch"] forState:UIControlStateNormal];
	[searchbtn addTarget:self action:@selector(gotosearch) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem *searchBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:searchbtn];
    
 
    self.navigationItem.rightBarButtonItem = searchBarButtonItem;
    CMRELEASE(searchBarButtonItem);

	CGRect f = [[self view] bounds];
	CGRect rc = f;
	UIImage* bkimage = [UIImage imageNamed:@"catnavbk"];
	UIView* catview = [[UIView alloc] init];
	catview.backgroundColor = [UIColor colorWithPatternImage:bkimage];
	rc.size.height = bkimage.size.height;
	catview.frame = rc;
	
	selview = [[UIImageView alloc] init];
	selview.image = [UIImage imageNamed:@"catnavselect"];
	selview.frame = CGRectMake(0, 0, rc.size.width/3, bkimage.size.height);
	
	firbtn = [UIButton buttonWithType:UIButtonTypeCustom];
	firbtn.tag = 0;
	[firbtn setTitle:I(@"提问")
            forState:UIControlStateNormal];
	[firbtn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateNormal];
	[firbtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
	firbtn.frame = CGRectMake(0, 0, rc.size.width/3, bkimage.size.height);
	[firbtn addTarget:self action:@selector(gotoselect:) forControlEvents:UIControlEventTouchUpInside];
	
	secbtn = [UIButton buttonWithType:UIButtonTypeCustom];
	secbtn.tag = 1;
	[secbtn setTitle:I(@"回答")
            forState:UIControlStateNormal];
	[secbtn setTitleColor:UIColorRGB(0x777777) forState:UIControlStateNormal];
	[secbtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
	secbtn.frame = CGRectMake(f.size.width/3, 0, rc.size.width/3, bkimage.size.height);
	[secbtn addTarget:self action:@selector(gotoselect:) forControlEvents:UIControlEventTouchUpInside];
	
	thrbtn = [UIButton buttonWithType:UIButtonTypeCustom];
	thrbtn.tag = 2;
	[thrbtn setTitle:I(@"关注")
            forState:UIControlStateNormal];
//    [thrbtn setTitleColor:[UIColor greenColor] forState:UIControlStateNormal];
    
	[thrbtn setTitleColor:UIColorRGB(0x777777) forState:UIControlStateNormal];
	thrbtn.frame = CGRectMake(f.size.width*2/3, 0, rc.size.width/3, bkimage.size.height);
	[thrbtn addTarget:self action:@selector(gotoselect:) forControlEvents:UIControlEventTouchUpInside];
	
	selview.tag = 0;
	[catview addSubview:selview];
	[catview addSubview:firbtn];
	[catview addSubview:secbtn];
	[catview addSubview:thrbtn];
	[self.view addSubview:catview];
    
    CMRELEASE(catview);
    CMRELEASE(selview);
    
    self.tagbarHeight = bkimage.size.height;
	//数据列表
    rc = CGRectMake(0,bkimage.size.height,f.size.width,UI_IOS_VC_HEIGHT) ;

    NSLog(@"%f,%f,%f,%f" , UI_IOS_NAVIBAR_HEIGHT,UI_IOS_STATUSBAR_HEIGHT,UI_IOS_TABBAR_HEIGHT,UI_IOS_TAGBAR_HEIGHT);
	qlistview = [[CMQListView alloc] initWithFrame:rc refresh:TRUE];
	qlistview.tag = 0;
	[[self view] addSubview:qlistview];

	qlistview.userInteractionEnabled = YES;
	UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];  
	horizontal.direction = UISwipeGestureRecognizerDirectionLeft;  
	[qlistview addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);
	
	horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];  
	horizontal.direction = UISwipeGestureRecognizerDirectionRight;  
	[qlistview addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);

	[self onselect:selview.tag];
//	[qlistview LoadData:selview.tag];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshfunc) name:@"qarefresh" object:self];
}
- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap {
    
	if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
	{
		[self onselect:(selview.tag+1)];
	}
	else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
	{
		[self onselect:(selview.tag-1)];
	}
	
}
-(void)onselect:(int)pos
{
	if(pos < 0 || pos > 2)
		return;
	UIButton* btn = nil;
	if(pos == 0)
		btn = firbtn;
	else if(pos == 1)
		btn = secbtn;
	else
		btn = thrbtn;
	self.title = [NSString stringWithFormat:@"%@%@",I(@"我的"), btn.titleLabel.text];
    self.titleLabel.text = self.title;
    
	[firbtn setTitleColor:UIColorRGB(0x777777) forState:UIControlStateNormal];
	[secbtn setTitleColor:UIColorRGB(0x777777) forState:UIControlStateNormal];
	[thrbtn setTitleColor:UIColorRGB(0x777777) forState:UIControlStateNormal];
	
	//UIColorRGB(0x065cc6)
	selview.tag = btn.tag;
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDidStopSelector:@selector(AnimationDidStop)];
	[UIView setAnimationDuration:0.3];
	[btn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateNormal];
	CGRect f = [[self view] bounds];
	CGFloat xoff =  f.size.width*btn.tag/3;
	f = selview.frame;
	f.origin.x = xoff;
	selview.frame = f;
	[UIView commitAnimations]; 		
}
-(void)gotoselect:(id)sender
{
	UIButton* btn = ((UIButton*)sender);
	if(btn.tag == selview.tag)
		return;
	[self onselect:btn.tag];
 
}
-(void)AnimationDidStop
{
    qlistview.curpos=selview.tag;
  //  qlistview->_reloading=NO;
    [qlistview automaticRefresh];
}
-(void)refreshfunc
{
	qlistview.tag = 1;
	[qlistview RefreshList];
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
-(void)gotocategory
{
	CMQaCategoryControl* qacategorycontrol = [[CMQaCategoryControl alloc] init];
	qacategorycontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	qacategorycontrol.navigationController.navigationBarHidden = NO;
	qacategorycontrol.tabBarController.tabBar.hidden = YES;
	qacategorycontrol.hidesBottomBarWhenPushed = YES;
	//qasearchcontrol.navigationController.delegate = self;
	qacategorycontrol.view.backgroundColor = [UIColor clearColor];
	qacategorycontrol.type = 1;
	[self.navigationController pushViewController:qacategorycontrol animated:YES];
    CMRELEASE(qacategorycontrol);
	
}
-(void)gotorespond:(id)sender
{
//	UIBarButtonItem*bar = (UIBarButtonItem*)sender;
//	if(bar.tag == 2)//我要提问
//	{
//		CMQuestionControl*	questioncontrol = [[CMQuestionControl alloc] init];
//		questioncontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//		questioncontrol.navigationController.navigationBarHidden = NO;
//		questioncontrol.tabBarController.tabBar.hidden = YES;
//		questioncontrol.hidesBottomBarWhenPushed = YES;
//		questioncontrol.view.backgroundColor = [UIColor clearColor];
//		[self.navigationController pushViewController:questioncontrol animated:YES];
//		[questioncontrol release];
//	}
//	else
//	{
//		CMQaSearchControl*	qasearchcontrol = [[CMQaSearchControl alloc] init];
//		qasearchcontrol.type = bar.tag;
//		qasearchcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//		qasearchcontrol.navigationController.navigationBarHidden = NO;
//		qasearchcontrol.tabBarController.tabBar.hidden = YES;
//		qasearchcontrol.hidesBottomBarWhenPushed = YES;
//		//qasearchcontrol.navigationController.delegate = self;
//		qasearchcontrol.view.backgroundColor = [UIColor clearColor];
//		[self.navigationController pushViewController:qasearchcontrol animated:YES];
//		[qasearchcontrol release];
//	}
}
/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/


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

- (void)dealloc {
    CMRELEASE(qlistview);
    
#if !__has_feature(obj_arc)
#endif
}
@end