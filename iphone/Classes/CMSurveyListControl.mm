//
//  CMSurveyListUI.m
//  OCplusplus
//
//  Created by sunjj on 11-4-27.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMSurveyListControl.h"
#import "CMSurveyControl.h"
#import "CMIntrodocutionViewController.h"
#import "cmsettings.h"
#import "CMLabel.h"
#import "UIScrollView+SVPullToRefresh.h"

#define kCellIdentifier @"com.apple.samplecode.QuartzDemo.CellIdentifier"

@implementation CMSurveyListControl

@synthesize TableViewList;

-(void)GetTableList
{
    [[self TableViewList] setDelegate:self];
	[[self TableViewList] setDataSource:self];
	[self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.5];

	[TableViewList reloadData];
}

-(void)reloadTableViewDataSource
{
    if (!self.trainID) {
        m_surveylist->GetList();

    }else
        m_surveylist->GetTrainSurveyList([self.trainID UTF8String]);
}
- (void)doneLoadingTableViewData{
	
	//  model should call this when its done loading
    [TableViewList.pullToRefreshView refreshLastUpdatedDate];
    [TableViewList.pullToRefreshView stopAnimating];
}




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


//- (void)viewWillAppear:(BOOL)animated {
//	
//	[super viewWillAppear:animated];
//    [self startRefresh];
//	
//}

- (void)clickRefresh{
    if (CMGlobal::TheOne().IsExistNetwork()) {
        [self startRefresh];
    }
}

-(void)startRefresh
{
    if (TableViewList.pullToRefreshView.state != SVPullToRefreshStateLoading) {
        [TableViewList triggerPullToRefresh];
    }
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	if(m_surveylist == nil)
	{
		m_pListener=new CMSurveyListListener();
		m_surveylist =new CMSurveyList(m_pListener);
		m_surveylist->SetUserData(BridgeObjectToC(self));
		//m_surveylist->GetList();
	}
	
	CGRect f = [[self view] bounds];
    f.size.height -=64;
	TableViewList = [[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain];
	//[TableViewList setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];

    
    //添加无内容时底图
     bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, TableViewList.bounds.size.width, TableViewList.bounds.size.height)];
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
   // [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(clickRefresh) on:bgview];
    [TableViewList addSubview:bgview];
    [bgview setBackgroundColor:[UIColor whiteColor]];
    
    bgview.userInteractionEnabled=YES;
    bgview.hidden = YES;
    
	[[self view] addSubview:TableViewList];		
		
    WEAKSELF;
    [TableViewList addPullToRefreshWithActionHandler:^{
        STRONGSELF;
        [sself reloadTableViewDataSource];
    }];
    
    [self startRefresh];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(finishsurvey:) name:@"finishsurvey" object:nil];
}

-(void) refreshTableView
{
    if (m_surveylist) {
        m_surveylist->RemoveItem(selectRow);
    }
    [TableViewList reloadData];
    
}
    

//完成一个调研后调研数-1
- (void)finishsurvey:(id)sender
{
    surveyDone = YES;
    [[bgview subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoSurveyText on:bgview]];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"surveycountchange" object:nil];

}

- (void)gotoBack
{
    if (surveyDone)
    {
        surveyDone = NO;
    }
    
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark UITableView delegate methods

// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

//	TSurveyListItem item = {0};
//	if(m_surveylist && m_surveylist->GetItem(indexPath.row, item))
//	{
//		CMSurveyControl *SurveyView = [[CMSurveyControl alloc] init];
//		[self.navigationController pushViewController:SurveyView animated:YES];
//		
//		[SurveyView OpenSurvey:[NSString stringWithUTF8String:item.sTitle] surveyid:item.sID];
//		[SurveyView release];		
//	}
    
    selectRow = indexPath.row;
    
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
	TSurveyListItem item;
	m_surveylist->GetItem(indexPath.row,item);
    NSString *strTitle = [NSString stringWithUTF8String:item.sTitle];
    NSString *strID = [NSString stringWithUTF8String:item.sID];
    NSString *strDesc = [NSString stringWithUTF8String:item.sDesc];
    NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nInvitecount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nCompletecount];
    NSString *strExpiredate = [NSString stringWithUTF8String:item.sExpiredate];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"survey",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strExpiredate,@"expiredate",strRequireCount,@"requirecount",strCompleteCount,@"completecount", nil];
    intro.itemDic = dic;
    intro.surveyListControl = self;
    [self.navigationController pushViewController:intro animated:YES];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	if(m_surveylist)
    {
        if(m_surveylist->GetItemCount()>0)
        {
            tableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;
            bgview.hidden=YES;
        }else
        {
            bgview.hidden=NO;
            tableView.separatorStyle=UITableViewCellSeparatorStyleNone;
        }
        
        
        
		return m_surveylist->GetItemCount();
    }
	else
    {
        
        bgview.hidden=NO;
        tableView.separatorStyle=UITableViewCellSeparatorStyleNone;
		return 0;
    }
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
	return @"";
}

- (CGFloat)tableView:(UITableView *)atableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	//return 40;
  	return 67;
} 
// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil) {
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
        
        UIImageView *imageView = [[UIImageView alloc] init];
        imageView.frame = CGRectMake(10, 12, 43, 43);
        imageView.backgroundColor = [UIColor clearColor];
        imageView.tag = 1000;
        [cell.contentView addSubview:imageView];
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.frame = CGRectMake(60, 14, 230, 15);
        titleLabel.font = [UIFont systemFontOfSize:15];
        titleLabel.textColor = UIColorRGB(0x333333);
        titleLabel.tag = 2000;
        [cell.contentView addSubview:titleLabel];
        
        CMLabel *detailLabel = [[CMLabel alloc] init];
        detailLabel.frame = CGRectMake(60, 39, 230, 14);
        detailLabel.tag = 3000;
        [cell.contentView addSubview:detailLabel];
        
        //cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
	}
    
    UIImageView *imgView = (UIImageView *)[cell.contentView viewWithTag:1000];
    UILabel *titleLbl = (UILabel *)[cell.contentView viewWithTag:2000];
    CMLabel *detailLbl = (CMLabel *)[cell.contentView viewWithTag:3000];
    
    imgView.image = nil;
    titleLbl.text = @"";
    detailLbl.text = @"";

	TSurveyListItem item = {0};
	if(m_surveylist && m_surveylist->GetItem(indexPath.row, item))
	{
        imgView.image = [UIImage imageNamed:@"surveyicon_n"];
        titleLbl.text = [NSString stringWithUTF8String:item.sTitle];
        
        NSRange range;
        range = NSMakeRange([[NSString stringWithFormat:@"%d",item.nInvitecount] length] + 3, [[NSString stringWithFormat:@"%d",item.nCompletecount] length]);
        
        [detailLbl setText:[NSString stringWithFormat:I(@"共%d人，%d人已完成"),item.nInvitecount,item.nCompletecount] WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0x999999)];
        [detailLbl setKeyWordRange:range WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0xfe883f)];
        
        NSRange range2 = NSMakeRange(1, [[NSString stringWithFormat:@"%d",item.nInvitecount] length]);
        [detailLbl setKeyWordRange:range2 WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0xfe883f)];
    }
	
	return cell;
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
	
	SAFEDELETE(m_surveylist);
	SAFEDELETE(m_pListener);
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"finishsurvey" object:nil];
	
}


@end
