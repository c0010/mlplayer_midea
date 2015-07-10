//
//  test.m
//  MLPlayer
//
//  Created by sunjj on 11-12-31.
//  Copyright 2011 w. All rights reserved.
//

#import "CMQaCategoryControl.h"
#import "CMQContentControl.h"

@implementation CMQaCategoryControl
@synthesize type,alert;   
@synthesize itemArray ;
#define kCellIdentifier @"com.apple.CMQaCategoryControl.CellIdentifier"

#pragma mark -
#pragma mark Initialization

-(void)GetBrowserList
{
	if(itemArray != nil && [itemArray count] > 0)
		[itemArray removeAllObjects];
	if(!itemArray)
		itemArray = [[NSMutableArray alloc] init];
	if(m_pQaCategory)
	{
		for(int i=0;i<m_pQaCategory->TopItemCount();i++)
		{
			CMQACategoryItem *pItem = m_pQaCategory->GetTopItem(i);
			if(!pItem)
				continue;
			NSMutableDictionary* dc = [NSMutableDictionary dictionary];
			[dc setObject:@"0" forKey:@"level"];
			NSString* st = [NSString stringWithUTF8String:pItem->sCategoryTitle];
			if(self.type == 1)
				[dc setObject: [NSString stringWithFormat:@"%@(%d)",st,pItem->nQuestioncount] forKey:@"title"];
			else
				[dc setObject:st forKey:@"title"];
			[dc setObject:[NSString stringWithFormat:@"%s",pItem->sID] forKey:@"id"];
			if(pItem->ChildItemCount())
				[dc setObject:@"close" forKey:@"status"];
			[itemArray addObject:dc];
		}
	}
	[TableViewList setDelegate:self];
	[TableViewList setDataSource:self];	
	[TableViewList reloadData];
}

-(void)btn_open:(id)sender
{
	UIButton *btnopen = (UIButton*)sender;
	NSLog(@"btn-open tag=%d",btnopen.tag);
	
	NSMutableDictionary *dic = [itemArray objectAtIndex:btnopen.tag] ;
	
	if([[dic objectForKey:@"status"] isEqualToString:@"close"])
	{
		[dic setObject:@"open" forKey:@"status"];
		CMQACategoryItem* pItem = m_pQaCategory->GetTopItem(btnopen.tag);
		if(!pItem)
			return;
		for(int i=0;i<pItem->ChildItemCount();i++)
		{
			CMQACategoryItem* pChild = pItem->GetChildItem(i);
			NSMutableDictionary* dc = [NSMutableDictionary dictionary];
			[dc setObject:@"1" forKey:@"level"];
			NSString* st = [NSString stringWithUTF8String:pChild->sCategoryTitle];
			if(self.type == 1)
				[dc setObject: [NSString stringWithFormat:@"%@(%d)",st,pChild->nQuestioncount] forKey:@"title"];
			else
				[dc setObject: st forKey:@"title"];
			[dc setObject:[NSString stringWithFormat:@"%s",pChild->sID] forKey:@"id"];
			[itemArray insertObject:dc atIndex:btnopen.tag+1];
		}
	}
	else
	{
		[dic setObject:@"close" forKey:@"status"];
		int pos = btnopen.tag + 1;
		while(pos < [itemArray count]-1)
		{
			dic = [itemArray objectAtIndex:pos];
			if(dic && [[dic objectForKey:@"level"] intValue] == 1)
				[itemArray removeObjectAtIndex:pos];
			else 
				break;

		}
	}

	[TableViewList reloadData] ;
}

#pragma mark -
#pragma mark View lifecycle
- (void)willPresentAlertView:(CustomBGAlert *)alertView {  
	if (alertView.tag == 200) {       
		[alertView setBGAlertViewX:110 alertFrameY:200 alertFrameWidth:100 alertFrameHeight:100];   
		alert.titleLabel.text = I(@"加载中…");
	}
}
- (void)viewDidLoad {
    [super viewDidLoad];
	CGRect f = [[self view] bounds];
	self.title = I(@"问题分类");
    //to fix

	TableViewList = [[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain];
    
	[self.view addSubview:TableViewList];	
	
	if(!m_pQaCategoryUpdateDataListener)
		m_pQaCategoryUpdateDataListener = new CMQaCategoryUpdateDataListener();
	if(!m_pQaCategory)
	{
		m_pQaCategory =CMQACategory::GetInstance();
		m_pQaCategory->SetUserData(BridgeObjectToC(self));		
	}
	m_pQaCategory->UpdateData();
	
	if (alert == nil) {
		alert = [[CustomBGAlert alloc] initWithTitle:@" " message:@" " delegate:self cancelButtonTitle:nil otherButtonTitles:nil];
		alert.tag = 200; 
	}
	[alert show];  
	alert.delegate = self;  
	[alert.indicatorView startAnimating]; 
	checkpos = -1;
}
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}


- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}


-(void) viewWillDisappear:(BOOL)animated    
{   
    if (checkpos >= 0 && [self.navigationController.viewControllers indexOfObject:self]==NSNotFound)    
    {  
	
		NSArray *keys = [NSArray arrayWithObjects:@"category", @"title", nil];
		
		NSArray *objects = [NSArray arrayWithObjects:[[itemArray objectAtIndex:checkpos] objectForKey:@"id"],
											  [NSString stringWithFormat:I(@"在%@分类中搜索"),[[itemArray objectAtIndex:checkpos] objectForKey:@"title"]], nil];
		[[NSNotificationCenter defaultCenter] postNotificationName:@"choosecategory" 
															object:nil
														  userInfo:[NSDictionary dictionaryWithObjects:objects forKeys:keys]];
	}   
    [super viewWillDisappear:animated];   
}  


- (void)viewDidDisappear:(BOOL)animated {
	
    [super viewDidDisappear:animated];
}


// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return YES;//(interfaceOrientation == UIInterfaceOrientationPortrait);
}



#pragma mark -
#pragma mark Table view data source

- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return [[[self.itemArray objectAtIndex:[indexPath row]] objectForKey:@"level"] intValue];	
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
    return [self.itemArray count];
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
   
	NSDictionary *dic = [self.itemArray objectAtIndex:[indexPath row]] ;
	
	UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
	if([[dic objectForKey:@"level"] isEqualToString:@"0"])
	{	
		NSString* pstatus = [dic objectForKey:@"status"];
		int left = 10;
		if(pstatus)
		{
			UIButton *btnOperIcon = [[UIButton alloc] initWithFrame:CGRectMake(5, 5, 25, 25)];
			btnOperIcon.tag = indexPath.row;
			[btnOperIcon addTarget:self action:@selector(btn_open:) forControlEvents:UIControlEventTouchUpInside];
			[cell.contentView addSubview:btnOperIcon];
			if([pstatus isEqualToString:@"close"])
				[btnOperIcon setBackgroundImage:[UIImage imageNamed:@"list_ico.png"] forState:UIControlStateNormal];
			else
				[btnOperIcon setBackgroundImage:[UIImage imageNamed:@"list_ico_d.png"] forState:UIControlStateNormal];
			left = 40;
		}
		UILabel* lbltitle = [[UILabel alloc] initWithFrame:CGRectMake(left, 10, UI_IOS_WINDOW_WIDTH-40, 18)];
		lbltitle.textColor = kTextColorDark;
		lbltitle.text = [dic objectForKey:@"title"];
		lbltitle.font = [UIFont systemFontOfSize:18.0];
		[cell.contentView addSubview:lbltitle];
		
	}
	else 
	{
		cell.textLabel.textAlignment = UITextAlignmentLeft;
			//cell.textLabel.highlightedTextColor = [UIColor clearColor];
		cell.textLabel.font = [UIFont systemFontOfSize:18.0];
		cell.textLabel.text =[dic objectForKey:@"title"];
		
		cell.textLabel.textColor = kTextColorDark;//[UIColor blackColor];
		
	}
	if(self.type == 1)
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	else
	{
		if(checkpos == [indexPath row])
			cell.accessoryType = UITableViewCellAccessoryCheckmark;	
		else
			cell.accessoryType = UITableViewCellAccessoryNone;	
	}

	cell.selectionStyle = UITableViewCellSelectionStyleGray;
	return cell;
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}




// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source.
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }   
}




// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}




// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}*/



#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *dic = [self.itemArray objectAtIndex:[indexPath row]] ;	
		
	
	
	NSString* strId = [dic objectForKey:@"id"];
	NSLog(@"sid=%@",strId);

	if(self.type == 1)
	{
		CMQContentControl* qcontentcontrol = [[CMQContentControl alloc] init];
		
		NSString* stitle = [dic objectForKey:@"title"];
		NSRange range = [stitle rangeOfString:@"(" options:NSBackwardsSearch];
		
		// What did we find
		if (range.length > 0)
			stitle = [stitle substringToIndex:range.location];
		
		qcontentcontrol.category = [NSString stringWithString:[dic objectForKey:@"id"]];
		qcontentcontrol.title = stitle;
		
		qcontentcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;		
		self.navigationController.navigationBarHidden=NO;		
		
		[self.navigationController pushViewController:qcontentcontrol animated:YES];
				
	}
	else 
	{
		checkpos = [indexPath row];
		[tableView reloadData];
	}
}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}


- (void)dealloc {
	if(itemArray != nil && [itemArray count] > 0)
		[itemArray removeAllObjects];
	
}


@end

