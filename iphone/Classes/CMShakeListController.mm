//
//  CMShakeListControllerViewController.m
//  MLPlayer
//
//  Created by sunjj on 13-10-8.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMShakeListController.h"
#import "CMMarkViewController.h"
#import "SDWebImage/UIImageView+WebCache.h"
@implementation CMShakeListController
@synthesize tableviewlist;

#define kCellIdentifier @"com.apple.CMItemView.CellIdentifier"

#pragma mark -
#pragma mark CMNavgateItem delegate methods
-(CMContenthandler*)GetContenthandler
{
    return  m_pShake;
}

#pragma mark -
#pragma mark LifeCycle
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(BOOL)canBecomeFirstResponder
{
    return YES;
    
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [self becomeFirstResponder];
}

- (void)viewWillDisappear:(BOOL)animated {
    [self resignFirstResponder];
    [super viewWillDisappear:animated];
}

- (void)refreshTitle{
    self.title = I(@"您摇到的课程");
    self.titleLabel.text = I(@"您摇到的课程");
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //加入声音效果
    
    NSString *strAudio = [[NSBundle mainBundle] pathForResource:@"glass" ofType:@"wav"];
    
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)[NSURL URLWithString:strAudio], &sysSoundID);
    
    self.view.backgroundColor=[UIColor whiteColor];
    
    
    appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
    
        
    self.titleLabel.text = self.navigationItem.title;
    
    UIImage *shakeImg=[UIImage imageNamed:@"shake_center"];
    

    
    tableviewlist=[[UITableView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH,UI_IOS_WINDOW_HEIGHT-44-20)];
    tableviewlist.separatorStyle = UITableViewCellSeparatorStyleNone;
    [tableviewlist setDelegate:self];
    [tableviewlist setDataSource:self];

    
    bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, tableviewlist.bounds.size.width, tableviewlist.bounds.size.height)];
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
    [tableviewlist addSubview:bgview];
    [bgview setBackgroundColor:[UIColor whiteColor]];
    
    bgview.userInteractionEnabled=NO;
    bgview.hidden = YES;
    [tableviewlist addSubview:bgview];
    
    [self.view addSubview:tableviewlist];
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


//iOS8上 cell分割线置顶
-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    if ([self.tableviewlist respondsToSelector:@selector(setSeparatorInset:)]) {
        [self.tableviewlist setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([self.tableviewlist respondsToSelector:@selector(setLayoutMargins:)]) {
        [self.tableviewlist setLayoutMargins:UIEdgeInsetsZero];
    }
}



#pragma mark -
#pragma mark UITableView delegate methods

-(void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
}


- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return  I(@"删除");
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
	if(!m_pShake)
    {
        bgview.hidden=YES;
        
        //tableviewlist.separatorStyle =UITableViewCellSeparatorStyleNone;
		return 0;
    }
	int head = 0;
    
    if(m_pShake->GetItemCount()>0)
    {
    //    tableviewlist.separatorStyle =     UITableViewCellSeparatorStyleSingleLine;
        bgview.hidden=YES;
    }else
    {
        bgview.hidden=NO;
        tableviewlist.separatorStyle =UITableViewCellSeparatorStyleNone;
    }
    
	if (!bHasMore) {
		return m_pShake->GetItemCount()+head;
	}
	return m_pShake->GetItemCount()+head+1;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
	int row = indexPath.row;
    
    //需要判断
    TBrowserItem* item=NULL;
    
    if(m_pShake->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }
        
	if (row == m_pShake->GetItemCount())
    {
        SAFEDELETE(item);
		return;
    }

	m_pShake->GetItem(row, item);
  //  NSString * strFlag = [NSString stringWithUTF8String:item->sFlag];
   // if([strFlag isEqualToString:@"news"]){
    [self selItem:*item];
  //  }
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    SAFEDELETE(item);
}

// set marktitle
- (void)setMarkTitle:(NSString *)marktitle markId:(NSInteger)markid withTableViewCell:(CMClassTableViewCell *)cell{
    if (!markid) {
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateHighlighted];
    }
    else if([marktitle isEqualToString:@"精品"]){
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_Boutique_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_Boutique_select"] forState:UIControlStateHighlighted];
    }
    else if ([marktitle isEqualToString:@"热点"]){
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_hot_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_hot_select"] forState:UIControlStateHighlighted];
    }
    else if (markid == 500){//500 mark id
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_teacher_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_teacher_select"] forState:UIControlStateHighlighted];
    }
    else if([marktitle isEqualToString:@"默认"]){
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_project_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_project_select"] forState:UIControlStateHighlighted];
    }
    if (marktitle == nil || [marktitle length] <= 0) {
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateHighlighted];
        
        
        cell.isShowMark = NO;

    }
    else{
        cell.isShowMark = YES;
    }
    cell.btnproject.tag = markid;
    [cell.btnproject setTitle:marktitle forState:UIControlStateNormal];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int row = indexPath.row;
    
    
    TBrowserItem* browserItem = NULL;
    
    if(m_pShake->GetItemModel(row)==0)
    {
        browserItem = new TClassItem();
    }
    else
    {
        browserItem = new TCoursewareItem();
    }
    
    
    if(row == m_pShake->GetItemCount())
    {
        SAFEDELETE(browserItem);
		return 44;
    }

	m_pShake->GetItem(row, browserItem);
    
    NSString * strFlag = [NSString stringWithUTF8String:browserItem->sFlag];
    
    if([strFlag isEqualToString:@"news"])
    {
        SAFEDELETE(browserItem);
        return 90;
    }
    else
    {
         CGFloat tempf= [CMClassTableViewCell GetCellHeight:*browserItem webimage:m_pWebImage width:self.view.frame.size.width];
        
        SAFEDELETE(browserItem);
        
        return tempf;
    }
}

// Customize the appearance of table view cells.

-(void)selItem:(TBrowserItem&)item
{
//	UIResponder* nextResponder = nil;
//	for (UIView* next = [self superview]; next; next = next.superview) {
//		nextResponder = [next nextResponder];
//		if ([nextResponder isKindOfClass:[UIViewController class]]) {
//			break;
//		}
//	}
//	if(!nextResponder)
//		return;
	
	int selrow = 0;
	if(_stricmp(item.sFlag,"course") == 0)
		selrow = -1;
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
	[nav NavgateItem:(UIViewController*)self item:item];
    
    CMRELEASE(nav);
	
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
	int row = indexPath.row;
    
//	if (row == m_pShake->GetItemCount() &&  m_pShake->GetItemCount()!= 0)
//		return [tableView:tableView cellForRowAtIndexPath:indexPath];
    
    
    
    TBrowserItem* browserItem = NULL;
    
    if(m_pShake->GetItemModel(row)==0)
    {
        browserItem = new TClassItem();
    }
    else
    {
        browserItem = new TCoursewareItem();
    }
    
    
    //    memset((void*)&browserItem,0,sizeof(TBrowserItem));
    
	m_pShake->GetItem(row, browserItem);
	
	NSString * strFlag = [NSString stringWithUTF8String:browserItem->sFlag];
    
    UITableViewCell* basecell;
    
    if([strFlag isEqualToString:@"news"])
    {
        CMNewsCell* cell;
        basecell = (CMNewsCell*)[tableviewlist dequeueReusableCellWithIdentifier:kCellIdentifier];
        
        if (basecell == nil) {
# if ! __has_feature(objc_arc)
            basecell = [[[CMNewsCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] autorelease];
# else
            basecell = [[CMNewsCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
# endif
        }
        
        cell=(CMNewsCell*)basecell;
        
        NSString *url = [NSString stringWithUTF8String:browserItem->sImage];
        if(browserItem->sImage && browserItem->sImage != '\0' && ![url isEqualToString:@""])
        {
            UIImage*lImage = [UIImage imageNamed:@"ulp"];
            
            [cell.LeftImageView sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:lImage];
        }
        
        else
            cell.LeftImageView.image = nil;
        
        //标题
        [cell.lbltitle setText:[NSString stringWithUTF8String:browserItem->sTitle] WithFont:[UIFont systemFontOfSize:17.0] AndColor:UIColorRGB(0x000000)];
        cell.lbltitle.isLineFeed = NO;
        
        [cell.contentLabel setText:[NSString stringWithUTF8String:browserItem->sBrief] WithFont:[UIFont systemFontOfSize:14] AndColor:[UIColor colorWithRed:102/255.0 green:102/255.0 blue:102/255.0 alpha:1.0]];
        cell.viewCountLabel.text=[NSString stringWithFormat:@"%d浏览",browserItem->nVC];
        
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        basecell=cell;
        
    }
    else
    {
        browserItem->Refresh();
        
        CMClassTableViewCell* cell;
        
        basecell = (CMClassTableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
        
        cell=(CMClassTableViewCell*)basecell;
        
        
        if (cell == nil) {
# if ! __has_feature(objc_arc)
            cell = [[[CMClassTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] autorelease];
# else
            cell = [[CMClassTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
# endif
        }
      //  self.tableviewlist.backgroundColor = UIColorRGB(0xd8dbdc);
      //  self.tableviewlist.separatorStyle = UITableViewCellSelectionStyleNone;
   
        [cell setcellinfo:*browserItem webimage:nil];
        
//        NSString *markTitle = [NSString stringWithUTF8String:browserItem->sMarkTitle]; //标签
//        NSInteger markid = [[NSString stringWithUTF8String:browserItem->sMarkID] integerValue];
//        
//        [self setMarkTitle:markTitle markId:markid withTableViewCell:cell];
        
        
        [cell.subtitleView addTarget:self action:@selector(gotoDetail:) forControlEvents:UIControlEventTouchUpInside];
        
        [cell.seriesView addTarget:self action:@selector(gotoClassdetail:event:) forControlEvents:UIControlEventTouchUpInside];
        [cell.btnproject addTarget:self action:@selector(searchByMarkid:event:) forControlEvents:UIControlEventTouchUpInside];
        

     
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        
        basecell=cell;
    }
    SAFEDELETE(browserItem);
	return basecell;
}

- (void)gotoDetail:(UIButton *)button{
    UITableViewCell *cell = nil;
    for (UIView* next = [button superview]; next; next = next.superview) {
        if ([next isKindOfClass:[UITableViewCell class]]) {
            cell = (UITableViewCell*)next;
            break;
        }
    }
    NSIndexPath *indexPath = [self.tableviewlist indexPathForCell:cell];
	int row = indexPath.row;
    //需要判断
    
    TBrowserItem* item = NULL;
    
    if(m_pShake->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }
	
    if (row == m_pShake->GetItemCount())
    {
        SAFEDELETE(item);
		return;
    }
	m_pShake->GetItem(row, item);
	[self selItem:*item];
    SAFEDELETE(item);
}




-(void)searchByMarkid:(id)sender event:(id)event
{
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:tableviewlist];
    
    int row =[tableviewlist indexPathForRowAtPoint:touchPoint].row;
    
    TBrowserItem* item = NULL;
    
    if(m_pShake->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }

    
	if (row == m_pShake->GetItemCount())
    {
        SAFEDELETE(item);
		return;
    }
	m_pShake->GetItem(row, item);
    
    UIViewController *viewControl = (UIViewController *)self;
    
    CMMarkViewController* markviewControl=[[CMMarkViewController alloc]init];
    markviewControl.hidesBottomBarWhenPushed=YES;
    UIButton *btn = (UIButton *)sender;
    markviewControl.title = btn.titleLabel.text;
    markviewControl.MarkID = [NSString stringWithUTF8String:item->sMarkID];
    [viewControl.navigationController pushViewController:markviewControl animated:YES];
    CMRELEASE(markviewControl);
    
    SAFEDELETE(item);
    //......
    
    
}

-(void)gotoClassdetail:(id)sender event:(id)event
{
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:tableviewlist];
    
    int row =[tableviewlist indexPathForRowAtPoint:touchPoint].row;
    //	[tableviewlist reloadData];
    
    
    //需要判断
    TBrowserItem* item = NULL;
    
    if(m_pShake->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }
    

    
	if (row == m_pShake->GetItemCount())
    {

        SAFEDELETE(item);
		return;

    }
	m_pShake->GetItem(row, item);
    //	[self selItem:*item];
    
    
	
	int selrow = 0;
	if(_stricmp(item->sFlag,"course") == 0 && item->nModel==1)
		selrow = -2;
    else
        return;
    
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
	[nav NavgateItem:(UIViewController*)self item:*item];
    
    CMRELEASE(nav);
    
    [tableviewlist deselectRowAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0] animated:NO];
    
    SAFEDELETE(item);
    
    
}

-(void)gotoShake
{
    if(m_pShakeListener==NULL)
        m_pShakeListener=new CMShakeListUpdateListener();
    
//    if(m_pShake==NULL)
//    {
        m_pShake=new CMShake(m_pShakeListener);
        m_pShake->SetUserData((__bridge void*)self);
//    }
    
    m_pShake->Request();
}

-(void)dealloc
{
    SAFEDELETE(m_pShakeListener);
    
    if (m_pShake) {
        m_pShake->SetListener(NULL, NULL);
        m_pShake->SetUserData(NULL);
        m_pShake->Cancel();
        m_pShake = NULL;
    }
    
//    SAFEDELETE(m_pShake);

    
    CMRELEASE(m_pImgUp);
    CMRELEASE(m_pImgDown);
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

@end