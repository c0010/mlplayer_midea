    //
//  CMBrowserControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import "CMCreditControl.h"

@implementation CMCreditControl
@synthesize alert;

#define kCellIdentifier @"com.apple.CMCreditControl.CellIdentifier"

-(void) viewWillDisappear:(BOOL)animated    
{   
    if (checkpos >= 0 && [self.navigationController.viewControllers indexOfObject:self]==NSNotFound)    
    {  

		[[NSNotificationCenter defaultCenter] postNotificationName:@"choosevalue" 
															object:nil
														  userInfo:[NSDictionary dictionaryWithObject:[NSString stringWithFormat:@"%d",[self getSelCredit:checkpos]] forKey:@"value"]];
	}   
    [super viewWillDisappear:animated];   
}  
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	CGRect f = self.view.bounds;
	txtcredit = [[UILabel alloc]init];
	txtcredit.textAlignment = UITextAlignmentLeft;
	txtcredit.font = [UIFont systemFontOfSize:kTextSizeMid];
	txtcredit.textColor = kTextColorDark;
	[txtcredit setBackgroundColor:[UIColor clearColor]];
	txtcredit.frame = CGRectMake(20.0, 10.0, f.size.width-40, 20);
	[self.view addSubview:txtcredit];
	
	tableviewlist = [[CMTableView alloc] initWithFrame:CGRectMake(20.0,35.0,f.size.width-40, 320) style:UITableViewStyleGrouped];
	[tableviewlist setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	tableviewlist.backgroundColor = [UIColor clearColor];
	tableviewlist.scrollEnabled = NO;
	[self.view addSubview:tableviewlist];
	
	alert = [[CustomBGAlert alloc] initWithTitle:@" " message:@" " delegate:self cancelButtonTitle:nil otherButtonTitles:nil];
	alert.tag = 200; 
	alert.delegate = self;
	
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMCreditUpdateDataListener();
	CMMyInfo::GetInstance()->SetListener(m_pUpdataDataListerner, NULL);
	CMMyInfo::GetInstance()->SetUserData(BridgeObjectToC(self));
	CMMyInfo::GetInstance()->UpdateData();
	[alert show];
	[alert.indicatorView startAnimating]; 
	checkpos = -1;
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
#pragma mark -
#pragma mark Table view 

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	
	return 8;
}
// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
	UITableViewCell *cell =  [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
	
	int nCredit = [self getSelCredit:indexPath.row];
	cell.textLabel.text = [NSString stringWithFormat:@"%d",nCredit];
	cell.textLabel.textAlignment = UITextAlignmentLeft;
	//cell.textLabel.highlightedTextColor = [UIColor clearColor];
	cell.textLabel.font = [UIFont systemFontOfSize:15.0];
	cell.textLabel.textColor = kTextColorDark;
	cell.textLabel.backgroundColor = [UIColor clearColor];

	if(nCredit > CMMyInfo::GetInstance()->GetCredit())
	{
		cell.selected = YES;
		cell.backgroundColor = [UIColor grayColor];
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
	else
	{
		if(checkpos == [indexPath row])
			cell.accessoryType = UITableViewCellAccessoryCheckmark;	
		else
			cell.accessoryType = UITableViewCellAccessoryNone;	
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
	}
	return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	return 30;
} 
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	if([self getSelCredit:indexPath.row] > CMMyInfo::GetInstance()->GetCredit())
		return;
	checkpos = indexPath.row;
	[tableView reloadData];
}

-(int)getSelCredit:(int)row
{
	int ncredit = 0;
	row++;
	switch (row) 
	{
		case 5:
			ncredit = 30;
			break;
		case 6:
			ncredit = 50;
			break;
		case 7:
			ncredit = 80;
			break;
		case 8:
			ncredit = 100;
			break;
		default:
		{
			if(row < 5)
				ncredit = row*5;
		}
	}
	return ncredit;
}
-(void)setCredit
{
	txtcredit.text = [NSString stringWithFormat:@"当前可用积分为:%d",CMMyInfo::GetInstance()->GetCredit()];
	[tableviewlist setDelegate:self];
	[tableviewlist setDataSource:self];
	[tableviewlist reloadData];
}
#pragma mark -
#pragma mark alert
- (void)willPresentAlertView:(CustomBGAlert *)alertView {  
	if (alertView.tag == 200) {       
		[alertView setBGAlertViewX:110 alertFrameY:200 alertFrameWidth:100 alertFrameHeight:100];   
		alert.titleLabel.text = @"加载中...";      
	}
}

- (void)dealloc 
{
	SAFEDELETE(m_pUpdataDataListerner);
}


@end

