    //
//  CMMyExamControl.m
//  MLPlayer
//
//  Created by sunjj on 11-10-9.
//  Copyright 2011 w. All rights reserved.
//
#import "stdafx.h"
#import "CMMyExamControl.h"
#import "CMIntrodocutionViewController.h"
#import "CMLabel.h"
#import "UIScrollView+SVPullToRefresh.h"

@implementation CMMyExamControl



@synthesize navigationControllerDelegates;

#define kCellIdentifier @"com.apple.CMMyExamControl.CellIdentifier"

-(void)GetListTable
{
    TableViewList.delegate = self;
    TableViewList.dataSource = self;
	[self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.5];
	[TableViewList reloadData] ;
}


-(void)gotoNav_review:(int)pos
{
//	UIButton *btntag = (UIButton*)sender;
//	if (btntag) {
		TExamListItem item;
		m_pCMExamList->GetItem(pos, item);
		
		if (item.nRequirecount<=0) {
			[tool ShowAlert:I(@"无题目")];
			return;
		}
		NSString * strValue;
//		if (item.bIsComplete) {
//			strValue = @"view";//测验已完成
//		}else {
			strValue = @"start";//测验未完成，开始测验
//		}
		
		
			//如果是菜单项处理相关操作
# if ! __has_feature(objc_arc)
		CMExamInfoControl* examControl = [[[CMExamInfoControl alloc] init] autorelease];
# else
    CMExamInfoControl* examControl = [[CMExamInfoControl alloc] init];
# endif
			//examControl.navigationItem.rightBarButtonItem = endexamBarButtonItem;
		examControl.title = [NSString stringWithUTF8String:item.sTitle.c_str()];
		examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
		examControl.navigationController.navigationBarHidden = NO;
		examControl.tabBarController.tabBar.hidden = YES;
		examControl.hidesBottomBarWhenPushed = YES;
		examControl.navigationController.delegate =self;
		examControl.delegate = self;
		
		[examControl setbtn:TRUE];
		[examControl OpenSurvey:@"exam" surveyid:item.sID.c_str() oper:strValue];
	
		[[((UIViewController*)[self superview].nextResponder) navigationController] pushViewController:examControl animated:YES];
	//}
}
#pragma mark table function

-(void)tableView:(CMTableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    selectRow = indexPath.row;
    
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
    TExamListItem item;
	m_pCMExamList->GetItem(indexPath.row,item);
    NSString *strTitle = [NSString stringWithUTF8String:item.sTitle.c_str()];
    NSString *scores = [NSString stringWithFormat:@"%@",NSStringFrom(item.sTestscores)];
    NSString *strID = [NSString stringWithUTF8String:item.sID.c_str()];
    NSString *strDesc = [NSString stringWithUTF8String:item.sDesc.c_str()];
    NSString *strCategory = [NSString stringWithUTF8String:item.sCategory.c_str()];
    NSString *strPubdate = [NSString stringWithUTF8String:item.sPubdate.c_str()];
    NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nRequirecount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nRequirecount - item.nUncompletecount];
    NSString *strQuestionCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
    NSString *strDuration = [NSString stringWithFormat:@"%d",item.nDuration];
    NSString *strRemainTime = [NSString stringWithFormat:@"%d",item.nRemainTime];
    NSString *strFullMark = [NSString stringWithFormat:@"%d",item.nFullmark];
    NSString *strPassMark = [NSString stringWithFormat:@"%d",item.nPassmark];
    NSString *strRankUrl = [NSString stringWithUTF8String:item.sRankurl.c_str()];
    //NSString *strComplete = [NSString stringWithFormat:@"%i",item.bIsComplete];
    NSString *strViewAnswer = [NSString stringWithFormat:@"%i",item.bViewAnswer];
    NSString *strCurrNumber = [NSString stringWithFormat:@"%i", item.nCurrNumber];
    NSString *strTotalNumber = [NSString stringWithFormat:@"%i", item.nTotalNumber];
    NSString *strCompleteTime = NSStringFrom(item.sCompletetime);
    
    
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"exam",@"type",strTitle,@"title",scores,@"scores",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strRequireCount,@"requirecount",strCompleteCount,@"completecount",strQuestionCount,@"questioncount",strDuration,@"duration",strRemainTime,@"remaintime",strFullMark,@"fullmark",strPassMark,@"passmark",strRankUrl,@"rank",/*strComplete,@"complete",*/ strViewAnswer,@"viewanswer", strCurrNumber, @"currnumber", strTotalNumber, @"totalnumber", strCompleteTime, @"completetime", nil];
    intro.itemDic = dic;
    CMRELEASE(dic);
    [intro setHanlder:m_pCMExamList row:indexPath.row];
    [[((UIViewController*)[self superview].nextResponder) navigationController] pushViewController:intro animated:YES];
	//[self gotoNav_review:indexPath.row];
    CMRELEASE(intro);
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(m_pCMExamList)
    {
        if (m_pCMExamList->GetItemCount()>0)
        {
            tableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;

            bgview.hidden=YES;
        }
        else
        {
            tableView.separatorStyle=UITableViewCellSeparatorStyleNone;

            bgview.hidden=NO;
        }
		return m_pCMExamList->GetItemCount();
    }else
    {
        bgview.hidden=NO;
        return 0;
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	return 67;
} 


-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
    
	if (cell == nil)
    {
# if ! __has_feature(objc_arc)
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] autorelease];
# else
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
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
        detailLabel.textColor = UIColorRGB(0x999999);
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
    
	TExamListItem item;
	m_pCMExamList->GetItem(indexPath.row, item);
	
	NSString* sdetail = nil;
    
    NSRange range1;
    NSRange range2;

//	if ([NSString stringWithUTF8String:item.sCompletetime.c_str()].length > 0)
    if (item.nCurrNumber == item.nTotalNumber || NSStringFrom(item.sTestscores).floatValue > item.nPassmark)
    {
		//已经完成测验
		NSString *scores = NSStringFrom(item.sTestscores);
		NSString *completetime = [NSString stringWithUTF8String:item.sCompletetime.c_str()];


		imgView.image = [UIImage imageNamed:@"examicon_n"];
        
        if ([scores integerValue] < 0)
        {
            sdetail = [NSString stringWithFormat:I(@"阅卷中, 交卷时间 %@"), completetime];
            range1 = NSMakeRange(0, 3);
            range2 = NSMakeRange([sdetail rangeOfString:I(@"交卷时间")].location + [sdetail rangeOfString:I(@"交卷时间")].length, sdetail.length - [sdetail rangeOfString:I(@"交卷时间")].location - [sdetail rangeOfString:I(@"交卷时间")].length);
            
        }
        else
        {
            sdetail = [NSString stringWithFormat:I(@"得分%@, 交卷时间 %@"), scores,  completetime];
            range1 = NSMakeRange(2, [[NSString stringWithFormat:@"%@",scores] length]);
            range2 = NSMakeRange([sdetail rangeOfString:I(@"交卷时间")].location + [sdetail rangeOfString:I(@"交卷时间")].length, sdetail.length - [sdetail rangeOfString:I(@"交卷时间")].location - [sdetail rangeOfString:I(@"交卷时间")].length);
        }

		
	}							
	else
	{
		//未完成测验
		imgView.image = [UIImage imageNamed:@"examicon_p"];

		sdetail =  [NSString stringWithFormat:I(@"共%d人,%d人已交卷"),item.nRequirecount,item.nUsercompletecount];
        
        int l = [[NSString stringWithFormat:@"%d",item.nRequirecount] length] + 3;
        range1 = NSMakeRange(1, [NSString stringWithFormat:@"%d",item.nRequirecount].length);
        range2 = NSMakeRange(l, [[NSString stringWithFormat:@"%d",item.nUsercompletecount] length]);
	}
    [detailLbl setText:sdetail WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0x999999)];
    [detailLbl setKeyWordRange:range1 WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0xfe883f)];
    [detailLbl setKeyWordRange:range2 WithFont:[UIFont systemFontOfSize:11] AndColor:UIColorRGB(0xfe883f)];
	titleLbl.text = [NSString stringWithUTF8String:item.sTitle.c_str()
                     ];
    
		
	return cell;
}



#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
	
	//  should be calling your tableviews data source model to reload
	//  put here just for demo
	
    if (!self.TrainID) {
        m_pCMExamList->GetList();
    }else
        m_pCMExamList->GetTrainList([self.TrainID UTF8String]);
	
	
	//[TableViewList reloadData];
}

- (void)doneLoadingTableViewData{
	
	//  model should call this when its done loading
    [TableViewList.pullToRefreshView refreshLastUpdatedDate];
    [TableViewList.pullToRefreshView stopAnimating];
}

-(void)willRershTableListView
{
	m_pCMExamList->GetList();	
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
             bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, TableViewList.bounds.size.width, TableViewList.bounds.size.height)];
        [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
        //[tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(clickRefresh) on:bgview];
        [TableViewList addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        
        bgview.userInteractionEnabled=YES;
        bgview.hidden = YES;
        

		[self addSubview:TableViewList];	
		
        
        WEAKSELF;
        [TableViewList addPullToRefreshWithActionHandler:^{
            STRONGSELF;
            [sself reloadTableViewDataSource];
        }];
		
		m_UpdateDataListener = new CMMyExamUpdateDataListener;
		
		m_pCMExamList = new CMExamList();
		m_pCMExamList->SetListener(m_UpdateDataListener);
        m_pCMExamList->SetUserData(BridgeObjectToC(self));
		//m_pCMExamList->GetList();
		//[self startFlash];
		//[tool Wait];
        
        [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(refereshTableView) name:@"completeexam" object:nil];
	}
	return self;
}

-(void)refereshTableView
{
 
    if (m_pCMExamList) {
        TExamListItem item;
        m_pCMExamList->GetItem(selectRow, item);
      //  item.bIsComplete = YES;
        m_pCMExamList->UpdateItem(item);
    }
    [TableViewList reloadData];
    
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
    
    [[NSNotificationCenter defaultCenter]removeObserver:self];
    CMRELEASE(bgview);
	
	SAFEDELETE(m_pCMExamList);
	SAFEDELETE(m_UpdateDataListener);
# if ! __has_feature(objc_arc)
	[super dealloc];
# endif
}


@end
