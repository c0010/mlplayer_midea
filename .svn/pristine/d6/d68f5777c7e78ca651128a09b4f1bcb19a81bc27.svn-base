    //
//  CMWrongControl.m
//  MLPlayer
//
//  Created by sunjj on 11-10-9.
//  Copyright 2011 w. All rights reserved.
//
#import "stdafx.h"
#import "CMWrongControl.h"
#import "CMLabel.h"
#import "cmmyinfo.h"
#import "UIScrollView+SVPullToRefresh.h"

@implementation CMWrongControl

@synthesize navigationControllerDelegates,nWrongPractice;

-(void)GetListTable
{
    TableViewList.delegate = self;
    TableViewList.dataSource = self;
	[self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.5];
	[TableViewList reloadData] ;
}

- (void)gotoNav_repeat:(int)row
{
    CMQuestionCategoryItem* item = m_pQuestionCategory->GetTopItem(row);
    
    if (item->nWrongcount <= 0) {
        [tool ShowAlert:I(@"无题目")];
        return;
    }
    
    CMExamInfoControl* examControl = [[CMExamInfoControl alloc] init];
    
    examControl.title = [NSString stringWithUTF8String:item->sTitle];
    examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    examControl.navigationController.navigationBarHidden = NO;
    examControl.tabBarController.tabBar.hidden = YES;
    examControl.hidesBottomBarWhenPushed = YES;
    examControl.navigationController.delegate =self;
    examControl.delegate= self;
    
    [examControl setbtn:FALSE];
    [examControl OpenSurvey:@"wrong" surveyid:item->sID oper:@"start"];
    [[((UIViewController*)[self superview].nextResponder) navigationController] pushViewController:examControl animated:YES];
}

#pragma mark Table view data source

	// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    int count = 0;
	for (int i = 0; i < m_pQuestionCategory->TopItemCount(); i++) {
		CMQuestionCategoryItem* item = m_pQuestionCategory->GetTopItem(i);
		if (item->nWrongcount>0) {
			count ++;
		}
	}
    self.nWrongPractice = count;
    
    if (count>0) {
        tableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;

        bgview.hidden=YES;
    }else
    {
        tableView.separatorStyle=UITableViewCellSeparatorStyleNone;

        bgview.hidden=NO;
    }
    
	NSLog(@"CMQuestionCategoryItem count=%d",count);
	return count;
}

- (CGFloat)tableView:(UITableView *)atableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	return 60;
} 

	// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
	
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
# if ! __has_feature(objc_arc)
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
# else
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
# endif
        
        UIImageView *imageView = [[UIImageView alloc] init];
        imageView.frame = CGRectMake(10, 8.5, 43, 43);
        imageView.backgroundColor = [UIColor clearColor];
        imageView.tag = 1000;
        [cell.contentView addSubview:imageView];
        CMRELEASE(imageView);
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.frame = CGRectMake(60, 9, 230, 23);
        titleLabel.font = [UIFont systemFontOfSize:17];
        titleLabel.tag = 2000;
        [cell.contentView addSubview:titleLabel];
        CMRELEASE(titleLabel);
        
        CMLabel *detailLabel = [[CMLabel alloc] init];
        detailLabel.frame = CGRectMake(60, 32, 230, 19);
        detailLabel.tag = 3000;
        [cell.contentView addSubview:detailLabel];
        CMRELEASE(detailLabel);
        
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
    
    UIImageView *imgView = (UIImageView *)[cell.contentView viewWithTag:1000];
    UILabel *titleLbl = (UILabel *)[cell.contentView viewWithTag:2000];
    CMLabel *detailLbl = (CMLabel *)[cell.contentView viewWithTag:3000];
    
    imgView.image = nil;
    titleLbl.text = @"";
    detailLbl.text = @"";
		
	CMQuestionCategoryItem* item=NULL;
	int i = 0;
	int pos = 0;
	for (i = 0; i < m_pQuestionCategory->TopItemCount(); i++)
	{
		item = m_pQuestionCategory->GetTopItem(i);
		if(item == nil)
			return cell;
		
		if (item->nWrongcount>0)
		{
			if(pos == indexPath.row)
				break;
			pos++;
		}
	}
    
    imgView.image = [UIImage imageNamed:@"wrongexam"];
    titleLbl.text = [NSString stringWithUTF8String:item->sTitle];
    [detailLbl setText:[NSString stringWithFormat:I(@"错题数%d"), item->nWrongcount] WithFont:[UIFont systemFontOfSize:12] AndColor:UIColorRGB(0x7f7f7f)];
    [detailLbl setKeyWordRange:NSMakeRange(3, [[NSString stringWithFormat:@"%d",item->nWrongcount] length]) WithFont:[UIFont systemFontOfSize:12] AndColor:UIColorRGB(0xfe883f)];

    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	[self gotoNav_repeat:indexPath.row];
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
}

#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
	
	//  should be calling your tableviews data source model to reload
	//  put here just for demo
	
	//refreshView.HasMore = false;
	
	m_pQuestionCategory->Update();
	
	//[TableViewList reloadData];
}

- (void)doneLoadingTableViewData{
	
	//  model should call this when its done loading
    [TableViewList.pullToRefreshView refreshLastUpdatedDate];
    [TableViewList.pullToRefreshView stopAnimating];
}

-(void)willRershTableListView
{
	m_pQuestionCategory->Update();	
	[TableViewList reloadData];	
}
-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	if(self != nil)
	{	
		CGRect f = self.bounds;
# if ! __has_feature(objc_arc)
		TableViewList = [[[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain] autorelease];
# else
        TableViewList = [[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain];
# endif
        
		[TableViewList setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	
        
        //添加无内容时底图
           bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.bounds.size.width, self.bounds.size.height)];
        [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
        [TableViewList addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        
        bgview.userInteractionEnabled=NO;
        bgview.hidden = YES;
        

        
		[self addSubview:TableViewList];	
		
        WEAKSELF;
        [TableViewList addPullToRefreshWithActionHandler:^{
            STRONGSELF;
            [sself reloadTableViewDataSource];
        }];
		
		m_pUpdateDataListener = new CMWrongListUpdateDataListener();
		m_pQuestionCategory = new CMQuestionCategory(m_pUpdateDataListener);
		
        m_pQuestionCategory->SetUserData(BridgeObjectToC(self));
		//m_pQuestionCategory->Update();
		[self startFlash];
		//[tool Wait];
	}
	return self;
	
}

- (void)startFlash
{
    if (TableViewList.pullToRefreshView.state != SVPullToRefreshStateLoading) {
        [TableViewList triggerPullToRefresh];
    }
}

- (void)clickRefresh{
    if (CMGlobal::TheOne().IsExistNetwork()) {
        [self startFlash];
    }
}

- (void)dealloc {
	
    CMRELEASE(bgview);
	SAFEDELETE(m_pUpdateDataListener);		
	SAFEDELETE(m_pQuestionCategory);
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}


@end
