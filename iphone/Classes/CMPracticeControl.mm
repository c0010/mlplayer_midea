    //
//  CMPracticeControl.m
//  MLPlayer
//
//  Created by sunjj on 11-10-9.
//  Copyright 2011 w. All rights reserved.
//
#import "stdafx.h"
#import "CMPracticeControl.h"
#import "CMIntrodocutionViewController.h"
#import "CMLabel.h"
#import "UIScrollView+SVPullToRefresh.h"

@implementation CMPracticeControl
@synthesize navigationControllerDelegates;

-(void)GetListTable
{
    TableViewList.delegate = self;
    TableViewList.dataSource = self;
	[self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.5];
	[TableViewList reloadData] ;
}

-(void)gotoNav_start:(int)row
{
//	UIButton *btntag = (UIButton*)sender;
//	if (btntag) {
		TExerciseListItem item;
		m_pExerciseList->GetItem(row,item);
		
		if (item.nQuestioncount<=0) {
			[tool ShowAlert:I(@"无题目")];
			return;
		}
		
			//UIBarButtonItem *endexamBarButtonItem = [[UIBarButtonItem alloc] initWithTitle: I(@"结束测试") style:UIBarButtonItemStyleBordered target:self action:nil]; 
		
			//如果是菜单项处理相关操作
		CMExamInfoControl* examControl = [[CMExamInfoControl alloc] init];
		
		examControl.title = [NSString stringWithUTF8String:item.GetExerciseListItemTitle()];
			//examControl.navigationItem.rightBarButtonItem = endexamBarButtonItem;
		examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
		examControl.navigationController.navigationBarHidden = NO;
		examControl.tabBarController.tabBar.hidden = YES;
		examControl.hidesBottomBarWhenPushed = YES;
		examControl.navigationController.delegate =self;
		examControl.delegate =self;
		
		[examControl setbtn:FALSE];
		[examControl OpenSurvey:@"practice" surveyid:item.GetExerciseListItemID() oper:@"start"];
		[[((UIViewController*)[self superview].nextResponder) navigationController] pushViewController:examControl animated:YES];
         CMRELEASE(examControl);
//	}
	
}

#pragma mark Table view data source

	// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
//    if(!m_pExerciseList || m_pExerciseList->GetItemCount())
    
	if(m_pExerciseList)
    {
        if (m_pExerciseList->GetItemCount()>0)
        {
            tableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;

            bgview.hidden=YES;
        }
        else
        {
            tableView.separatorStyle=UITableViewCellSeparatorStyleNone;

            bgview.hidden=NO;
        }
        
		return m_pExerciseList->GetItemCount();
        
    }else
    {
        bgview.hidden=NO;
        return 0;
    }
}
- (CGFloat)tableView:(UITableView *)atableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{       
	return 67;
} 

	// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil)
    {
# if ! __has_feature(objc_arc)
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
# else
         cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
# endif
        
        UIImageView *imageView = [[UIImageView alloc] init];
        imageView.frame = CGRectMake(10, 12, 43, 43);
        imageView.backgroundColor = [UIColor clearColor];
        imageView.tag = 1000;
        [cell.contentView addSubview:imageView];
        CMRELEASE(imageView);
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.frame = CGRectMake(60, 14, 230, 15);
        titleLabel.font = [UIFont systemFontOfSize:kTextSizeSml];
        titleLabel.textColor = UIColorRGB(0x333333);
        titleLabel.tag = 2000;
        [cell.contentView addSubview:titleLabel];
        CMRELEASE(titleLabel);
        
        CMLabel *detailLabel = [[CMLabel alloc] init];
        detailLabel.frame = CGRectMake(60, 39, 230, 14);
        detailLabel.font = [UIFont systemFontOfSize:11];
        detailLabel.tag = 3000;
        [cell.contentView addSubview:detailLabel];
        CMRELEASE(detailLabel);
        
        //cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
	
    UIImageView *imgView = (UIImageView *)[cell.contentView viewWithTag:1000];
    UILabel *titleLbl = (UILabel *)[cell.contentView viewWithTag:2000];
    CMLabel *detailLbl = (CMLabel *)[cell.contentView viewWithTag:3000];
    
    imgView.image = nil;
    titleLbl.text = @"";
    detailLbl.text = @"";
    
	TExerciseListItem item;
	m_pExerciseList->GetItem(indexPath.row,item);

    imgView.image = [UIImage imageNamed:@"praicon"];
    titleLbl.text = [NSString stringWithUTF8String:item.GetExerciseListItemTitle()];
    
    NSRange range;
    range = NSMakeRange(2, [[NSString stringWithFormat:@"%d",item.nCompleteCount] length]);

    
    [detailLbl setText:[NSString stringWithFormat:I(@"已答%d/%d"),item.nCompleteCount,item.nQuestioncount] WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0x999999)];
    [detailLbl setKeyWordRange:range WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0xfe883f)];


    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
	TExerciseListItem item;
	m_pExerciseList->GetItem(indexPath.row,item);
    NSString *strTitle = [NSString stringWithUTF8String:item.GetExerciseListItemTitle()];
    NSString *strID = [NSString stringWithUTF8String:item.GetExerciseListItemID()];
    NSString *strDesc = [NSString stringWithUTF8String:item.GetExerciseListItemDesc()];
    NSString *strCategory = [NSString stringWithUTF8String:item.GetExerciseListItemCategory()];
    NSString *strPubdate = [NSString stringWithUTF8String:item.GetExerciseListItemPubdate()];
    NSString *strTotalCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nCompleteCount];
    NSString *strCompleteUser = [NSString stringWithFormat:@"%d",item.nUsercompletecount];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"practice",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strTotalCount,@"totalcount",strCompleteCount,@"completecount",strCompleteUser,@"completeuser", nil];
    intro.itemDic = dic;
    intro->m_pExerciseList = m_pExerciseList;
    intro.nRow = indexPath.row;
    CMRELEASE(dic);
    [[((UIViewController*)[self superview].nextResponder) navigationController] pushViewController:intro animated:YES];
	//[self gotoNav_start:indexPath.row];
    CMRELEASE(intro);
 
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
}
#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
	
	//  should be calling your tableviews data source model to reload
	//  put here just for demo
    if (!self.trainID) {
        m_pExerciseList->GetList();
    }else
        m_pExerciseList->GetTrainList([self.trainID UTF8String]);
	
}

- (void)doneLoadingTableViewData
{
	//  model should call this when its done loading
    [TableViewList.pullToRefreshView refreshLastUpdatedDate];
    [TableViewList.pullToRefreshView stopAnimating];
}


- (void)startFlash
{
    if (TableViewList.pullToRefreshView.state != SVPullToRefreshStateLoading) {
        [TableViewList triggerPullToRefresh];
    }
}

- (void)willRershTableListView
{
	m_pExerciseList->GetList();
	[TableViewList reloadData];
}
	// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	if(self != nil)
	{	
		CGRect f = self.bounds;
		//数据列表
#if ! __has_feature(objc_arc)
		TableViewList = [[[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain] autorelease];
# else
        TableViewList = [[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain];
# endif
		[TableViewList setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	    
        WEAKSELF;
        [TableViewList addPullToRefreshWithActionHandler:^{
            STRONGSELF;
            [sself reloadTableViewDataSource];
        }];
        
        
        //添加无内容时底图
        
        bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.bounds.size.width, self.bounds.size.height)];
        [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
       // [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(clickRefresh) on:bgview];
        [TableViewList addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        
        bgview.userInteractionEnabled=NO;
        bgview.hidden = YES;

        
        
        
		[self addSubview:TableViewList];
		
		m_pUpdateDataListener = new CMExameListUpdateDataListener();
		m_pExerciseList = new CMExerciseList();
		m_pExerciseList->SetListener(m_pUpdateDataListener);
		m_pExerciseList->SetUserData(BridgeObjectToC(self));	
		//m_pExerciseList->GetList();
        
        //[self startFlash];
		//[tool Wait];
	}
	return self;
}

- (void)dealloc {
    CMRELEASE(bgview);
	SAFEDELETE(m_pUpdateDataListener);	
	SAFEDELETE(m_pExerciseList);
# if ! __has_feature(objc_arc)
	[super dealloc];
# endif

}


@end