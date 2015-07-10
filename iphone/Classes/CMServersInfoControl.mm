    //
//  CMServersInfoControl.m
//  MLPlayer
//
//  Created by sunjj on 11-8-26.
//  Copyright 2011 w. All rights reserved.
//

#import "CMServersInfoControl.h"

#define kCellIdentifier @"com.apple.CMServersInfoControl.CellIdentifier"
@implementation CMServersInfoControl
@synthesize m_pTableView,sServerName;;


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
int currentIndex = -1;

	// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	self.navigationController.navigationBarHidden = NO;
		
	CGRect f = [[self view] bounds];

	m_pTableView = [[UITableView alloc] initWithFrame:f style:UITableViewStylePlain];
	[[self m_pTableView] setDelegate:self];
	[[self m_pTableView] setDataSource:self];
	[[self m_pTableView] setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	[[self view] addSubview:[self m_pTableView]];
	
	//[tool WaitView];

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
	if(m_pListener)
		delete m_pListener;
	if(m_pCustomerts)
		delete m_pCustomerts;
	
}

#pragma mark UIViewController delegate

- (void)viewWillAppear:(BOOL)animated
{
	if(m_pCustomerts == nil)
	{
		m_pListener=new CMServersInfoListener();
		m_pCustomerts =new CMCustomerList(m_pListener);
		m_pCustomerts->SetUserData( (__bridge void *)self);
	}
	if(m_pCustomerts->GetItemCount() <= 0)
		m_pCustomerts->GetList();
}

#pragma mark UITableView delegate methods

	// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableViews didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	
	[tableViews deselectRowAtIndexPath:indexPath animated:NO];
	if(indexPath.row==currentIndex){
		return;
	}
	NSIndexPath *oldIndexPath = [NSIndexPath indexPathForRow:currentIndex
                                                   inSection:0];
	UITableViewCell *newCell = [tableViews cellForRowAtIndexPath:indexPath];
	if (newCell.accessoryType == UITableViewCellAccessoryNone) {
		newCell.accessoryType = UITableViewCellAccessoryCheckmark;
			//newCell.textColor=[UIColor blueColor];
	}
	UITableViewCell *oldCell = [tableViews cellForRowAtIndexPath:oldIndexPath];
	if (oldCell.accessoryType == UITableViewCellAccessoryCheckmark) {
		oldCell.accessoryType = UITableViewCellAccessoryNone;
			//oldCell.textColor=[UIColor blackColor];
	}
	currentIndex=indexPath.row;
	
	
	
	//UITableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath]; 
	TCustomerListItem item = {0};
	if(m_pCustomerts && m_pCustomerts->GetItem(indexPath.row, item))
	{
		NSLog(@"sServerName=%@",[NSString stringWithUTF8String:item.sName]);
		
		[[NSNotificationCenter defaultCenter] postNotificationName:@"clickBtn" 
															object:nil
														  userInfo:[NSDictionary dictionaryWithObject:[NSString stringWithUTF8String:item.sName]
																							   forKey:@"name"]];
		m_pCustomerts->SetServerUrl((char*)item.sName, (char*)item.sServer);
	}
	
}

#pragma mark UITableView data source methods

	// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

	// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	int rows = 0;
	
	if(m_pCustomerts)
	{
		rows = m_pCustomerts->GetItemCount();
		//if(rows > 0 )
		//	rows++;
	}
	return rows;
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
	return @"";
}

- (UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath
{
	if(indexPath.row==currentIndex){
		return UITableViewCellAccessoryCheckmark;
	}
	else{
		TCustomerListItem item = {0};

		if(m_pCustomerts && m_pCustomerts->GetItem(indexPath.row, item))
		{
			NSString * strName = [NSString stringWithUTF8String:item.sName];
			
			if ([strName isEqualToString:sServerName]) {
				
				currentIndex=indexPath.row;

				return UITableViewCellAccessoryCheckmark;
				
			}else {
				return UITableViewCellAccessoryNone;
			}				
		}		
		return UITableViewCellAccessoryNone;
	}
}



	// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	
	if(cell == nil)
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];

	TCustomerListItem item = {0};

	NSLog(@"indexpath row=%d,items=%d sServerName=%@",[indexPath row],m_pCustomerts->GetItemCount(),sServerName);

	if(m_pCustomerts && m_pCustomerts->GetItem(indexPath.row, item))
	{
		cell.textLabel.text = [NSString stringWithFormat:@"%@",[NSString stringWithUTF8String:item.sName]];
	//cell..text = [NSString stringWithFormat:@"%@",[NSString stringWithUTF8String:item.sServer]];
	}
		
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
	
	return cell;
}



@end
