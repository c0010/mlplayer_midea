    //
	//  CMDownLoadControl.m
	//  MLPlayer
	//
	//  Created by sunjj on 11-9-19.
	//  Copyright 2011 w. All rights reserved.
	//

#import "CMDownLoadControl.h"
#import "CMNavgateItem.h"
#import "cmsettings.h"
@implementation CMDownLoadControl
#define kCellIdentifier @"com.apple.CMDownLoadControl.CellIdentifier"
#define kCellSubIdentifier @"com.apple.CMDownLoadControl.CellSubIdentifier"

@synthesize itemArray ;
@synthesize openItemArray,RepeatItemArray;

-(CMContenthandler*)GetContenthandler
{
    return Nil;
    
}

-(void)loadTableList
{
	[TableViewList reloadData];
}
-(void)btn_Error:(id)sender
{
	
}

-(void)btn_InDownList:(id)sender
{

}


-(void)gotoplay_list:(id)sender
{
	UIButton* btnplay = (UIButton*)sender;
	
	CMCourseInfo item;

	CMCourseDownload::GetInstance()->GetItem(btnplay.titleLabel.tag,item);

	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
	   
    TCoursewareItem courseItem;
    item.GetCourseware(btnplay.tag, courseItem);
    
	[nav NavgateItem:self item:courseItem];
	
}

-(void)btn_Start:(id)sender
{
	UIButton *btntag = (UIButton*)sender;
	
	CMCourseDownload::GetInstance()->Start(btntag.tag);
	
    CMCourseDownload::GetInstance()->SetUserData(BridgeObjectToC(self));

	[self readPlistToArray];
	
	[TableViewList reloadData];
	
}

-(void)btn_Stop:(id)sender
{	
	CMCourseDownload::GetInstance()->Stop();
	[self readPlistToArray] ;
	[TableViewList reloadData] ;
	
}

#pragma mark startJob_0

-(void)getdown_value_0{

//		downTime0 = [[NSTimer scheduledTimerWithTimeInterval:3
//										 target:self
//									   selector:@selector(startJob_0:)
//									   userInfo:nil
//										repeats:YES] retain];
}

- (void)startJob_0:(NSTimer *)theTimer
 {	 

//	[TableViewList reloadData];
 }


#pragma mark reload data



-(void)clearitemArray
{	
	for (int i=0; i<[self.itemArray count]; i++) {
        [self.itemArray removeObjectAtIndex:i];
	}	
	
	//[self.itemArray removeAllObjects];
	
}


-(void)readPlistToArray
{
	if ([self.itemArray count]) {		
		[self.itemArray removeAllObjects];
	}
    
    
    //一级菜单
	for (int i = 0 ; i < CMCourseDownload::GetInstance()->GetItemCount(); i++) {
		
		CMCourseInfo item;		
		CMCourseDownload::GetInstance()->GetItem(i,item);
        TClassItem titem;
        item.GetClassItem(titem);
		        
        const char* nStatusText = "";

		int mStatus = CMCourseDownload::GetInstance()->Status(i);
				
		NSMutableDictionary * menuDic_1 = [NSMutableDictionary dictionary];
	
		[menuDic_1 setObject:@"0" forKey:@"level"] ;
		[menuDic_1 setObject:[NSString stringWithUTF8String:titem.sID] forKey:@"id"];
		[menuDic_1 setObject:[NSString stringWithUTF8String:titem.sTitle] forKey:@"title"];
		[menuDic_1 setObject:[NSString stringWithUTF8String:titem.sImage] forKey:@"image"];
		[menuDic_1 setObject:[NSString stringWithUTF8String:nStatusText] forKey:@"StatusText"];
		[menuDic_1 setObject:[NSString stringWithFormat:@"%d",i] forKey:@"indexid"];
		[menuDic_1 setObject:[NSString stringWithFormat:@"%d",mStatus] forKey:@"mStatus"];

		
		[self.itemArray addObject:menuDic_1];
		
		//[menuDic_1 release];
		
		if (![self.openItemArray count]) {
			continue;
		}
			//判断打开的菜单
		for (int j = 0 ; j < [self.openItemArray count] ; j++) {
			
				//NSLog(@"openid = %@,item.id = %@",[[self.openItemArray objectAtIndex:j] objectForKey:@"id"],[NSString stringWithUTF8String:item.sID]);
				
			if ([[[self.openItemArray objectAtIndex:j] objectForKey:@"id"] isEqualToString:[NSString stringWithUTF8String:titem.sID]]) {
					//二级菜单				
				for (int k = 0 ; k < item.GetItemCount(); k++) {
					TCoursewareItem childitem;
					if(item.GetCourseware(k,childitem)){		
					//	const char* nChileStatusText = CMCourseDownload::GetInstance()->GetStatusText(i,k);
                        
                        const char* nChileStatusText="";
						BOOL iscomplete = CMCourseDownload::GetInstance()->isComplete(i,k);
						int currentid = CMCourseDownload::GetInstance()->GetCurrent();
						
						NSMutableDictionary * menuDic_2 = [NSMutableDictionary dictionary] ;
						[menuDic_2 setObject:@"1" forKey:@"level"] ;
                        
                        //判断 当下载列表为第一个 和最后一个时 cell 分割线的不同
                        if (k == 0) {
                            [menuDic_2 setObject:@"1" forKey:@"first"];
                        }
                        else
                            [menuDic_2 setObject:@"2" forKey:@"first"];
                        
                        if (k == item.GetItemCount() - 1) {
                            [menuDic_2 setObject:@"1" forKey:@"last"];
                        }
                        else
                            [menuDic_2 setObject:@"2" forKey:@"last"];

						[menuDic_2 setObject:[NSString stringWithUTF8String:childitem.sID] forKey:@"id"];
						[menuDic_2 setObject:[NSString stringWithUTF8String:childitem.sTitle] forKey:@"title"];	
						[menuDic_2 setObject:[NSString stringWithUTF8String:nChileStatusText] forKey:@"StatusText"];
						[menuDic_2 setObject:[NSString stringWithFormat:@"%d",k] forKey:@"indexid"];
						[menuDic_2 setObject:[NSString stringWithFormat:@"%d",i] forKey:@"parentid"];
						[menuDic_2 setObject:[NSString stringWithFormat:@"%d",childitem.nCheckStatus] forKey:@"nflag"];
						[menuDic_2 setObject:[NSString stringWithFormat:@"%d",iscomplete] forKey:@"iscomplete"];
						[menuDic_2 setObject:[NSString stringWithUTF8String:childitem.sUrl] forKey:@"url"];
						[menuDic_2 setObject:[NSString stringWithUTF8String:childitem.sType] forKey:@"stype"];
						[menuDic_2 setObject:[NSString stringWithFormat:@"%d",currentid] forKey:@"currentid"];
						[menuDic_2 setObject:[NSString stringWithFormat:@"%d",mStatus] forKey:@"mStatus"];
						
						[self.itemArray addObject:menuDic_2];
					//	[menuDic_2 release];
					}
				}
			}
		}
	}
}

#pragma mark Table view data source

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{    
	NSMutableDictionary *dic = [self.itemArray objectAtIndex:indexPath.row] ;
    
	if( [[dic objectForKey:@"level"] intValue] == 0)
	{
//		UITableViewCell *cell = [self tableView:tableView cellForRowAtIndexPath:indexPath];
//		return cell.frame.size.height+6;
        NSString *title = [[self.itemArray objectAtIndex:indexPath.row] objectForKey:@"title"];
        return [CMDownLoadTableViewCell GetCellHeight:title width:260.0];
	}
	return 65.0;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{	
	NSDictionary *dic = [self.itemArray objectAtIndex:[indexPath row]] ;
	
	if(![[dic objectForKey:@"level"] intValue])
	{
		return UITableViewCellEditingStyleDelete;
	}else
		return	UITableViewCellEditingStyleNone;
}

- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return  I(@"删除");
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle 
forRowAtIndexPath:(NSIndexPath *)indexPath 
{
    
    NSDictionary *dic = [self.itemArray objectAtIndex:[indexPath row]] ;
    
		// If row is deleted, remove it from the list.
	if (editingStyle == UITableViewCellEditingStyleDelete) 
	{
		CMCourseDownload::GetInstance()->Delete([[dic objectForKey:@"indexid"] integerValue]);
		[self readPlistToArray];
        
        //在重新刷新tableView的时候延迟一下
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self->TableViewList reloadData];
        });

	}
	else if(editingStyle == UITableViewCellEditingStyleInsert)
	{
   
	}
}

	// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    
    if([self.itemArray count]==0)
    {
        bgview.hidden=NO;
        tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        
    }else
    {
        tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        
        bgview.hidden=YES;
    }
    

    return [self.itemArray count];
	
}

- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return [[[self.itemArray objectAtIndex:[indexPath row]] objectForKey:@"level"] intValue];	
}


	// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    
   	NSMutableDictionary *dic = [self.itemArray objectAtIndex:[indexPath row]] ;

	CMDownLoadTableViewCell* cell = [[CMDownLoadTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
    
    cell.lblvalue.text=@"";
    
	if([[dic objectForKey:@"level"] isEqualToString:@"0"])
	{
        CMCourseInfo item;
        
        NSInteger rownumber =[[dic objectForKey:@"indexid"] integerValue] ;
        
		CMCourseDownload::GetInstance()->GetItem(rownumber,item);

		NSString* strValue= [NSString stringWithFormat:I(@"共%d个课件"),item.GetItemCount()];
		
        cell.lblvalue.text = strValue;
		      
		if([[dic objectForKey:@"mStatus"] intValue] == CMCourseDownload::EStatusDownloading)
		{
			[cell.btnstatus setImage:[UIImage imageNamed:@"down_pause.png"] forState:UIControlStateNormal];
			[cell.btnstatus addTarget:self action:@selector(btn_Stop:) forControlEvents:UIControlEventTouchUpInside];
				//StatusText
		//[self getdown_value_0:cell.lblvalue :[[dic objectForKey:@"indexid"] intValue]];

		}else if([[dic objectForKey:@"mStatus"] intValue] == CMCourseDownload::EStatusPauseDownload)
		{
				//[cell.btnstatus setTitle:I(@"开始") forState:UIControlStateNormal];
			[cell.btnstatus setImage:[UIImage imageNamed:@"down_start.png"] forState:UIControlStateNormal];
            
            [cell.btnstatus addTarget:self action:@selector(btn_Start:) forControlEvents:UIControlEventTouchUpInside];
		}else if([[dic objectForKey:@"mStatus"] intValue] == CMCourseDownload::EStatusInDownloadList)
		{
			[cell.btnstatus setImage:[UIImage imageNamed:@"down_start.png"] forState:UIControlStateNormal];
			[cell.btnstatus addTarget:self action:@selector(btn_Start:) forControlEvents:UIControlEventTouchUpInside];

		}else if([[dic objectForKey:@"mStatus"] intValue] == CMCourseDownload::EStatusPauseDownload)
		{
			[cell.btnstatus setImage:[UIImage imageNamed:@"down_start.png"] forState:UIControlStateNormal];
			[cell.btnstatus addTarget:self action:@selector(btn_Start:) forControlEvents:UIControlEventTouchUpInside];

		}else if ([[dic objectForKey:@"mStatus"] intValue] == CMCourseDownload::EStatusComplete) {
            
			[cell.btnstatus setHidden:YES];
			//cell.lblvalue.frame.origin.x=cell.btnstatus.frame.origin.x;
		}
		cell.btnstatus.tag = [[dic objectForKey:@"indexid"] intValue];
		cell.btnstatus.titleLabel.tag = [[dic objectForKey:@"indexid"] intValue];
		//cell.btnstatus.hidden = YES;
		if ([RepeatItemArray count]<=0) {
			cell.tagImg.image = [UIImage imageNamed:@"list_ico.png"];
		}else {
			
			for (int i = 0 ; i < [RepeatItemArray count]; i++) {
				if ([[[self.RepeatItemArray objectAtIndex:i] objectForKey:@"id"] isEqualToString:[dic objectForKey:@"id"]]) {
					cell.tagImg.image = [UIImage imageNamed:@"list_ico_d.png"];
					break;
				}else {
					cell.tagImg.image = [UIImage imageNamed:@"list_ico.png"];
				}
				
			}	
		}
		

		
		//如果为0则为主菜单
		cell.selectionStyle = UITableViewCellSelectionStyleNone ;
			//cell.LeftImageView.image = homeView.image;
		cell.lbltitle.text = [dic objectForKey:@"title"];
		
		return cell;
		
	}// Configure the cell.
	else if([[dic objectForKey:@"level"] isEqualToString:@"1"]) {
		
        UITableViewCell* cell_list = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellSubIdentifier];

		UILabel *lbltitle = [[UILabel alloc] init];		
		UILabel *lblvalue = [[UILabel alloc] init];	
		//NSLog(@"status = %d",[[dic objectForKey:@"indexid"] intValue]);
		
		CGFloat boundsX ;
		CGFloat boundsY ;
		int X = 10;
		int Y = 13;
		
		CGRect frame;
		
		boundsX = X;	
		boundsY = Y;	
		
		X = UI_IOS_WINDOW_WIDTH - boundsX;
		Y = 18;	
		
			//标题
		frame= CGRectMake(boundsX ,boundsY, X-40, Y);
		lbltitle.frame = frame;
		
		boundsX = boundsX;
		boundsY = boundsY + Y + 3;
		Y = 14;
		X = 250;
		
			//内容
		frame= CGRectMake(boundsX ,CGRectGetMaxY(lbltitle.frame) + 5.0, X, Y);
		lblvalue.frame = frame;
		
		frame= CGRectMake(UI_IOS_WINDOW_WIDTH-40 ,(65.0-25)/2, 25, 25);
        UIImageView* typeImg = [[UIImageView alloc]init];
        
        NSString *sType = [dic objectForKey:@"stype"];
        
        if([sType isEqualToString:@"text/html"] || [sType isEqualToString:@"text/vnd.wap.wml"])
        {
            [typeImg setImage:[UIImage imageNamed:@"txt_icon"]];
            
        }
        else if([sType isEqualToString:@"video/3mv"])
        {
            [typeImg setImage:[UIImage imageNamed:@"video_icon"]];
        }
        else
        {
            [typeImg setImage:[UIImage imageNamed:@"audio_icon"]];
        }


		typeImg.frame = frame;
        
        
        
        UIButton* btnplay = [UIButton buttonWithType:UIButtonTypeCustom];
        [btnplay setBackgroundColor:[UIColor clearColor]];
        
        [btnplay setFrame:CGRectMake(0, 0, cell_list.frame.size.width, cell_list.contentView.frame.size.height+20)];
        
		btnplay.tag = [[dic objectForKey:@"indexid"] intValue];
		
		lbltitle.text = [dic objectForKey:@"title"];
        lbltitle.font = [UIFont systemFontOfSize:kTextSizeMid];
        lbltitle.textColor = UIColorRGB(0x2e2e2e);
		lbltitle.backgroundColor = [UIColor clearColor];
		
		lblvalue.font = [UIFont systemFontOfSize:kTextSizeSml];
		lblvalue.textColor=kTextColorNormal;
		lblvalue.backgroundColor = [UIColor clearColor];
			
		cell_list.selectionStyle = UITableViewCellSelectionStyleNone ;
	
		NSString* strValue2= [NSString stringWithUTF8String:CMCourseDownload::GetInstance()->GetStatusText([[dic objectForKey:@"parentid"] intValue],[[dic objectForKey:@"indexid"] intValue])];

        lblvalue.text = strValue2;
        
        [btnplay setHidden:YES];
        [btnplay addTarget:self action:@selector(gotoplay_list:) forControlEvents:UIControlEventTouchUpInside];

		if ([[dic objectForKey:@"iscomplete"] isEqualToString:@"1"]) {
            [btnplay setHidden:NO];
            
			[btnplay addTarget:self action:@selector(gotoplay_list:) forControlEvents:UIControlEventTouchUpInside];
			[cell_list.contentView addSubview:typeImg];
		}else {
			if([[dic objectForKey:@"nflag"] isEqualToString:@"1"])
			{
				//cell.accessoryType = UITableViewCellAccessoryCheckmark;
			}else {
				cell_list.accessoryType = UITableViewCellAccessoryNone;
			}
		}
		
		btnplay.titleLabel.tag = [[dic objectForKey:@"parentid"] intValue];
		
        UIView *selView = [[UIView alloc]initWithFrame:CGRectMake(8.0, 64.5, UI_IOS_WINDOW_WIDTH - 16.0, 0.5)];
        
        selView.backgroundColor = UIColorRGB(0xcbcbcb);
        UIView *selViewTop = [[UIView alloc]initWithFrame:CGRectMake(8.0, 0.0, 304.0, 0.5)];
        selViewTop.backgroundColor = UIColorRGB(0xf8f8f8);
        if ([[dic objectForKey:@"first"] isEqualToString:@"1"]) { //当显示下载列表第一个时 top cell 加上阴影分割线
            selViewTop.hidden = YES;
            UIImageView *imgview = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"down_list_cell_bg"]];
            imgview.frame = CGRectMake(0.0, 0.0, UI_IOS_WINDOW_WIDTH, 5.0);
            [cell_list.contentView addSubview:imgview];
        }
        if ([[dic objectForKey:@"last"] isEqualToString:@"1"]) { //当显示下载列表最后一个时 last cell 分割线width要与主菜单分割线长度一致
            selView.frame = CGRectMake(0.0, 64.5, UI_IOS_WINDOW_WIDTH, 0.5);
        }
        
        

		[cell_list.contentView addSubview:lbltitle];
		[cell_list.contentView addSubview:lblvalue];
        [cell_list.contentView addSubview:selView];
        [cell_list.contentView addSubview:selViewTop];
        [cell_list.contentView addSubview:btnplay];

		cell_list.contentView.backgroundColor = UIColorRGB(0xedeeee);
        return cell_list;
	}
	
   return cell;
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	NSDictionary *dic = [[NSDictionary alloc] initWithDictionary:[self.itemArray objectAtIndex:indexPath.row]];
		
	//NSLog(@"level =%@",[dic objectForKey:@"level"]);
	
	if(![[dic objectForKey:@"level"] intValue])
	{
		BOOL istrue = false;
						
		for (int i=0; i<[self.RepeatItemArray count]; i++) {
			if ([[[self.RepeatItemArray objectAtIndex:i] objectForKey:@"id"] isEqualToString:[dic objectForKey:@"id"]]) {				

				//[self clearRepeatItemArray];
				[self.RepeatItemArray removeObjectAtIndex:i];
				istrue = true;
				break;
			}
		}
		if (!istrue) {
			[self.RepeatItemArray addObject:dic];
		} 
		
		//如果为0则为主菜单
		for (int i = 0 ; i < [self.openItemArray count]; i++) {
			if ([[[self.openItemArray objectAtIndex:i] objectForKey:@"id"] isEqualToString:[dic objectForKey:@"id"]]) {
				
				[self.openItemArray removeObjectAtIndex:i] ;				
				
				[self readPlistToArray] ;
				[TableViewList reloadData];
				
				return ;
			}
		}	
	}	
	else 
	{
		if([[dic objectForKey:@"nflag"] isEqualToString:@"1"])
		{
			CMCourseDownload::GetInstance()->UnCheckCourseware([[dic objectForKey:@"parentid"] intValue], [[dic objectForKey:@"indexid"] intValue]);
		}else {
			CMCourseDownload::GetInstance()->CheckCourseware([[dic objectForKey:@"parentid"] intValue], [[dic objectForKey:@"indexid"] intValue]);
		}
	}

	
	[self.openItemArray addObject:dic] ;
	[self readPlistToArray] ;
	[TableViewList reloadData] ;
}


-(void)viewWillAppear:(BOOL)animated 
{ 
    [super viewWillAppear:animated];
	
	MLPlayerAppDelegate *appDelegate = [UIApplication sharedApplication].delegate;
	appDelegate.navigationController.navigationBarHidden = YES;
	self.navigationController.navigationBarHidden = NO;
}

- (void) viewWillDisappear:(BOOL)animated {
	[super viewWillAppear:animated];
}

	// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.titleLabel.text = self.navigationItem.title;
    
	CGRect f = [[self view] bounds];
	//f.size.height -= 44;
		//数据列表	
	TableViewList = [[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain] ;
	[TableViewList setDelegate:self];
	[TableViewList setDataSource:self];
	[TableViewList setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
    TableViewList.separatorStyle = UITableViewCellSeparatorStyleNone;

    bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, TableViewList.bounds.size.width, TableViewList.bounds.size.height)];
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
    [TableViewList addSubview:bgview];
    [bgview setBackgroundColor:[UIColor whiteColor]];
    
    bgview.userInteractionEnabled=NO;
    bgview.hidden = YES;
    
    
	[self.view addSubview:TableViewList];
	

	self.itemArray = [[NSMutableArray alloc] init];
	self.openItemArray = [[NSMutableArray alloc] init];
	self.RepeatItemArray = [[NSMutableArray alloc]init];
	if (!m_pGetImageListener) {
		m_pGetImageListener = new CMNDownLoadGetImageListener();
	}
    
    if(!m_pProgressListener)
    {
        m_pProgressListener= new CMDownLoadProgressListener();
    }
    
    CMCourseDownload::GetInstance()->SetListener(m_pProgressListener);
    CMCourseDownload::GetInstance()->SetUserData(BridgeObjectToC(self));
    
	if (!m_pWebImage) {
		m_pWebImage=new CMWebImage(m_pGetImageListener);
		m_pWebImage->SetUserData(BridgeObjectToC(self));
	}
	
	[self readPlistToArray] ;
	
	[self getdown_value_0];
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


- (void)dealloc {
    
    CMCourseDownload::GetInstance()->SetListener(NULL);
    
    CMCourseDownload::GetInstance()->SetUserData(NULL);

	CMRELEASE(itemArray);
	CMRELEASE(openItemArray);
	CMRELEASE(RepeatItemArray);
	
	CMRELEASE(scrollView);
	CMRELEASE(selectedCellIndexPath);

	SAFEDELETE(m_pGetImageListener);
	SAFEDELETE(m_pWebImage);
}


@end
