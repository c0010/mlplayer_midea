//
//  MLPlayer
//  FileName：CMQListView.mm
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMQListView.h"
#import "cmsettings.h"
#import "CMQuestionTableViewCell.h"
#import "CMQuestionDetailControl.h"
#import "CMImageDetailViewControl.h"
#import "cmmyinfo.h"

@implementation CMQListView

@synthesize curpos,flag,category,key;
@synthesize qalist = m_pQalist;
@synthesize selectedIndex;
@synthesize isSearchMode;

#define kCellIdentifier @"com.apple.CMQListView.CellIdentifier"

#pragma mark -
#pragma mark View init



-(id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh
{
	self = [super initWithFrame:frame refresh:brefresh];
	if(self != nil)
	{
		//init
		m_pUpdataDataListerner = nil;
		m_pSimpleResultListener = nil;
		m_pQalist = nil;
		if (!m_pGetImageListener) 
			m_pGetImageListener = new CMQListGetImageListener();
   
    
		if (!m_pWebImage)
		{
			m_pWebImage=new CMWebImage(m_pGetImageListener);      //设置回调的类
			m_pWebImage->SetUserData(BridgeObjectToC(self));
		}
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadTableview:) name:@"reloadTableview" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SubmitSuccess) name:@"submit_success" object:nil];
        
        //添加无内容时底图
        bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, tableviewlist.bounds.size.width, tableviewlist.bounds.size.height)];
        [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
//        if(brefresh){
//            [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:(UIViewController *)[self.superview nextResponder] action:@selector(clickRefresh) on:bgview];
//        }
//        else{
//            [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:(UIViewController *)[self.superview nextResponder] action:@selector(clickNoPullDownRefresh) on:bgview];
//        }
        [tableviewlist addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        
        bgview.userInteractionEnabled=YES;
        bgview.hidden = YES;
        
        
        
    }
	return self;
}

- (void)clickNoPullDownRefresh{
    if (CMGlobal::TheOne().IsExistNetwork()) {
        [self RefreshList];
    }
}

- (void)SubmitSuccess{
    self.curpos=3;
    [self automaticRefresh];
    
    //刷新个人积分
    CMMyInfo::GetInstance()->UpdateData();
    
}
#pragma mark -
#pragma mark UITableView delegate methods


- (void)reloadTableview:(NSNotification *)notification{
    NSDictionary *dic = [notification userInfo];
    NSInteger index = [[dic objectForKey:@"index"] integerValue];
    [self.tableviewlist reloadRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:index inSection:0]] withRowAnimation:UITableViewRowAnimationNone];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if(!m_pQalist)
		return 0;
	if (m_pQalist->IsEnd() || SETTING.GetAutoLoadMore()) {
//        if (m_pQalist->GetItemCount()>0)
//        {
//            tableviewlist.separatorStyle=UITableViewCellSeparatorStyleNone;
//            
//            bgview.hidden=YES;
//        }
//        else
//        {
//            tableviewlist.separatorStyle=UITableViewCellSeparatorStyleNone;
//            
//            bgview.hidden=NO;
//        }
		return m_pQalist->GetItemCount();
	}
	return m_pQalist->GetItemCount()+1;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	if (indexPath.row == m_pQalist->GetItemCount()) {
		return;
	}
	
	TQAItem qaitem;
	m_pQalist->GetItem(indexPath.row, qaitem);      //和数据源关联的代码
	
	UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {     
		nextResponder = [next nextResponder];      
		if ([nextResponder isKindOfClass:[UIViewController class]]) {       
			break; 
		}    
	}
	if(!nextResponder)
		return;

    
	CMQuestionDetailControl* questiondetailcontrol = [[CMQuestionDetailControl alloc] init];               //问题的详细界面
    
	[questiondetailcontrol SetQuestionItem:qaitem];
    questiondetailcontrol->m_pQalist=m_pQalist;
    if(_stricmp(qaitem.sQuestioner_username.c_str(),SETTING.GetUserName()) != 0){
        questiondetailcontrol.title = [NSString stringWithFormat:I(@"%@的问题"),[NSString stringWithUTF8String:qaitem.sQuestioner_fullname.c_str()]];
    }
    else{
        questiondetailcontrol.title = [NSString stringWithFormat:I(@"我的提问")];
    }
	questiondetailcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	questiondetailcontrol.navigationController.navigationBarHidden = NO;
	questiondetailcontrol.tabBarController.tabBar.hidden = YES;
	questiondetailcontrol.hidesBottomBarWhenPushed = YES;
	//qasearchcontrol.navigationController.delegate = self;
    //添加判断textanswer 是否第一响应标记
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"isFirstResponder"];
    
   	questiondetailcontrol.view.backgroundColor = [UIColor clearColor];
	[((UIViewController*)nextResponder).navigationController pushViewController:questiondetailcontrol animated:YES];
    CMRELEASE(questiondetailcontrol);
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];

}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{       
	if(indexPath.row == m_pQalist->GetItemCount())
		return 44;
	TQAItem qaitem;
	m_pQalist->GetItem(indexPath.row,qaitem);
    
	return [CMQuestionTableViewCell GetCellHeight:qaitem webimage:m_pWebImage shareimage:nil width:self.frame.size.width hideimage:false ];
} 

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {         
	
	if (indexPath.row == m_pQalist->GetItemCount() &&  m_pQalist->GetItemCount()!= 0)
		return [super tableView:tableView cellForRowAtIndexPath:indexPath];

#if ! __has_feature(obj_arc)
    CMQuestionTableViewCell *cell = [[CMQuestionTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
#else
    CMQuestionTableViewCell *cell = [[CMQuestionTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
#endif

	TQAItem qaItem;
	m_pQalist->GetItem(indexPath.row, qaItem);        //数据源与视图关联的代码
    cell.hideimage = FALSE;
	[cell setcellinfo:qaItem webimage:m_pWebImage shareimage:nil index:indexPath.row];        //设置cell内容
    
    if (isSearchMode) {
        [cell.lbquestion setAllKeyWordTextArray:[NSArray arrayWithObject:key] WithFont:[UIFont systemFontOfSize:kTextSizeMid] AndColor:UIColorRGB(0xff7800)];
    }

    [cell.showImageView addTarget:self action:@selector(pressImg:event:) forControlEvents:UIControlEventTouchUpInside];


	return cell;
}


-(void)pressImg:(id)sender event:(id)event                //点击图片放大图片 ,[cell.showImageView addTarget:self action:@selector(pressImg:event:)
{
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:self.tableviewlist];
    
    NSInteger selected=[self.tableviewlist indexPathForRowAtPoint:touchPoint].row;
    

	TQAItem qaItem;
    if(m_pQalist)
    {
        if(m_pQalist->GetItem(selected, qaItem))
        {
            NSString *url = [NSString stringWithUTF8String:qaItem.sPic_url.c_str()];
            if(qaItem.sPic_url.c_str() && qaItem.sPic_url.c_str() != '\0' && ![url isEqualToString:@""])
            {
                [self ShowImageView:url thumbView:[NSString stringWithUTF8String:qaItem.sThumburl.c_str()]];    //call  ShowImageView:
            }
        }
    }
    
}

- (void)ShowImageView:(NSString*)url thumbView:(NSString *)thumburl{            //显示放大的图片
    //获取当前view的响应接受者
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];  //显示大图的viewcontroller
    //  [cmimageController setImage:[UIImage imageNamed:@"test_image"]];
    cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    //    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];
    cmimageController.isURL = YES;
    [cmimageController setCMImageURL:url thumbURL:thumburl];
    [((UIViewController*)nextResponder) presentModalViewController:cmimageController animated:YES];
    CMRELEASE(cmimageController);
    
}


-(void)LoadDataUseCache:(BOOL)useCache Category:(NSString*)categoryid
{
    
    NSInteger pos= self.curpos ;
    
    
	if(pos >3 || pos < 0)
		return;
	self.curpos = pos;
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMQListUpdateDataListener();           //设置回调的类
	if(!m_pSimpleResultListener)
		m_pSimpleResultListener = new CMQListSimpleResultListener();        //设置回调的类
	if(!m_pQalist)
	{
		m_pQalist = new CMQAList();
        
	}
    
    m_pQalist->SetListener(m_pUpdataDataListerner,m_pSimpleResultListener,nil);
    m_pQalist->SetUserData(BridgeObjectToC(self));
    
    
	BOOL ret = FALSE;
    if(useCache)
        m_pQalist->SetRequestType(1);
    else
        m_pQalist->SetRequestType(0);
        
	if(pos == 0)
		ret = m_pQalist->GetMyQuestion();
	else if(pos == 1)
		ret = m_pQalist->GetMyAnswer();
	else if(pos == 2)
		ret = m_pQalist->GetMyAttention();
	else if(pos == 3)
    {
        if(categoryid == nil)
            ret = m_pQalist->GetNew();
        else
            ret = m_pQalist->GetAllQAByCategoryId([categoryid UTF8String]);
    }
	if(ret)
	{
		//[tool Wait];
        //[self GetBrowserList];
        [self.tableviewlist reloadData];
	}

}




-(void) LoadData:(NSString*)categoryid
                          //RefreshList  call Loadata
{
    [self LoadDataUseCache:YES Category:categoryid];
  }
-(void)Search
{
	if(self.key == nil || [self.key length] == 0)
		return;
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMQListUpdateDataListener();
	if(!m_pSimpleResultListener)
		m_pSimpleResultListener = new CMQListSimpleResultListener();
	if(!m_pQalist)
	{
		m_pQalist = new CMQAList();
	
	}
    m_pQalist->SetListener(m_pUpdataDataListerner,m_pSimpleResultListener,nil);
    m_pQalist->SetUserData(BridgeObjectToC(self));
	
    [tool ShowActivityIndicator:self];
	if(m_pQalist->Search([self.flag UTF8String], [self.category length] > 0 ? [self.category UTF8String]:"", [self.key UTF8String]))
	{
        
	}
}
-(void)GetCategory
{
	if(self.category == nil || [self.category length] == 0)
		return;
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMQListUpdateDataListener();
	if(!m_pSimpleResultListener)
		m_pSimpleResultListener = new CMQListSimpleResultListener();
	if(!m_pQalist)
	{
		m_pQalist = new CMQAList();
	
	}
    m_pQalist->SetListener(m_pUpdataDataListerner,m_pSimpleResultListener,nil);
    m_pQalist->SetUserData(BridgeObjectToC(self));
	
	if(m_pQalist->GetByCategory([category UTF8String]))
	{
		[tool Wait]; 
		[self GetBrowserList];
	}
	
}
-(void)RefreshList
{
	if(self.category == nil || [self.category length] == 0)
    {
        if (self.curpos >= 0)
        {
            if(self.isUseCache)
                [self LoadDataUseCache:YES Category:self.categoryId];
            else
                [self LoadData:self.categoryId];
            
            self.isUseCache = NO;
        }
    }
	else
    {
		//[self GetCategory];
    }
}

-(BOOL)RefreshMore
{
	if([self HasMore])
    {
		return  m_pQalist->RequestMore();
    }
    
    return  NO;
}

- (void)dealloc
{
    CMRELEASE(flag);
    CMRELEASE(category);
    CMRELEASE(key);
	
	SAFEDELETE(m_pGetImageListener);
	SAFEDELETE(m_pUpdataDataListerner);
	SAFEDELETE(m_pSimpleResultListener);
    SAFEDELETE(m_pWebImage);

	SAFEDELETE(m_pQalist);
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"reloadTableview" object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"submit_success" object:nil];
#if !__has_feature(obj_arc)
#endif
}

@end