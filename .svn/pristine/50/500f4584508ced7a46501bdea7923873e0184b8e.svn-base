//
//  CMAddressSearchControl.mm
//  MLPlayer
//
//  Created by sunjj on 11-5-12.
//  Copyright 2011 w. All rights reserved.
//

#import "CMAddressControl.h"
#import "cmsettings.h"
#import "CMImage.h"
#import "CMAddressInfoControl.h"
#import "CMTableViewCell.h"
#import "tool.h"
#import "cmglobal.h"
#import "UITableViewCell+Helpper.h"
#import "CMPersonDetailyViewController.h"

#define kCellIdentifier @"com.apple.CMAddressControl.CellIdentifier"

@implementation CMAddressControl
@synthesize searchBar;
@synthesize activity;
@synthesize tableView;
@synthesize TalkImage;
@synthesize btnTalk;
@synthesize searchField = _searchField;
@synthesize backBtn = _backBtn;

-(void)loadTableList
{
    [tool DisimissActivityIndicator];
    [self.tableView reloadData];
    
}

-(void)RershTableList:(UITableViewCell*)mycell
{
    
    if(!m_pContacts || m_pContacts->IsEnd())
        return;
    
	if (!SETTING.GetAutoLoadMore()) {
		[btnMore setHidden:YES];
	}
	
	dwActiveView.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2, (44-20)/2, 20, 20);
	
	UILabel * lblview = [[UILabel alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2+25, (44-20)/2, 150, 20)];
    lblview.backgroundColor = [UIColor clearColor];
	lblview.text = I(@"加载更多...");// @"加载更多...";
	
	[mycell.contentView addSubview:dwActiveView];			
	[mycell.contentView addSubview:lblview];
	
	mycell.selectionStyle = UITableViewCellSelectionStyleNone;
	mycell.accessoryType = UITableViewCellAccessoryNone;
	
//	[dwActiveView startAnimating];
//	
//	m_pContacts->SearchMore();
    m_pContacts->RequestMore();
    

}

-(void)RershTableList
{
//	if(m_pContacts)
//		m_pContacts->SearchMore();
    if (m_pContacts) {
        m_pContacts->RequestMore();
    }
}



-(void)PhoneAction
{
	if (phoneNum ==nil || [phoneNum length] ==0 ) {
		[tool ShowAlert:I(@"没有找到手机号码！")];//@"没有找到手机号码！"
	}
	
	NSString* pNs = [NSString stringWithFormat:@"tel://%@",phoneNum];
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:pNs]];
}


-(void)MsgAction
{
	if (phoneNum ==nil || [phoneNum length] ==0 ) {
		[tool ShowAlert:I(@"没有找到手机号码！")];//@"没有找到手机号码！"
	}
		
	NSString* pNs = [NSString stringWithFormat:@"sms://%@",phoneNum];
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:pNs]];
}



- (void)viewDidLoad {
    [super viewDidLoad];

	dwActiveView = [[UIActivityIndicatorView alloc]init];
	[dwActiveView setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleGray];
	[dwActiveView  stopAnimating];
    
	CGRect f = [[self view] bounds];
	
    bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, f.size.width, f.size.height)];
    
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
    [bgview setBackgroundColor:[UIColor clearColor]];
    
    bgview.userInteractionEnabled=NO;
    
    bgview.hidden = YES;

	CGRect rc = f;
	rc.size.height = 48;
    
    //底
    UIImageView* inputBack=[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 42)];
    
    [inputBack setImage:[UIImage imageNamed:@"searchbar"]];
    [inputBack setUserInteractionEnabled:YES];
    
    //放大镜
    UIImage* zoominIconImg = [UIImage imageNamed:@"search_icon"];

    
    UIImageView* zoominIconView = [[UIImageView alloc]initWithFrame:CGRectMake(20, 15, zoominIconImg.size.width, zoominIconImg.size.height)];
    
    [zoominIconView setImage:zoominIconImg];
    
    [self.view addSubview:inputBack];
    
    _searchField = [[UITextField alloc]initWithFrame:CGRectMake(34, 6, UI_IOS_WINDOW_WIDTH-50, 30)];
    _searchField.backgroundColor = [UIColor clearColor];
    _searchField.font = [UIFont systemFontOfSize:14.0];
    _searchField.delegate = self;
    _searchField.layer.cornerRadius = 2.0;
    _searchField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    _searchField.returnKeyType = UIReturnKeyDone;
    _searchField.placeholder = I(@"想搜“张三”输入“zs”试试");
    [_searchField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    

    [inputBack addSubview:_searchField];
    
    [inputBack addSubview:zoominIconView];
    
    
    CMRELEASE(inputBack);
    

	f.origin.y += (48-10);
	f.size.height = UI_IOS_WINDOW_HEIGHT - 64 - (48-10);
	[self setTableView:[[UITableView alloc] initWithFrame:f style:UITableViewStylePlain]];
    self.tableView.backgroundColor = [UIColor clearColor];
    self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
	[[self view] addSubview:[self tableView]];
    
    [tableView addSubview:bgview];


	[self setActivity:[[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray]];
	
	UIImage * image = [UIImage imageNamed:@"addressTalk.png"];
	TalkImage = [[UIImageView alloc] initWithImage:image];
	
	TalkImage.frame = CGRectMake(f.size.width-150, f.origin.y-80 ,120, 48);
	
	if(btnPhone == nil)
	{
		btnPhone=[UIButton buttonWithType:UIButtonTypeCustom]; 
		btnPhone.frame=CGRectMake(f.size.width-35,5,32, 32); 
		UIImage *phoneImage=[UIImage imageNamed:@"menu_call.png"]; 
		[btnPhone setBackgroundImage:phoneImage forState:UIControlStateNormal]; 
		[btnPhone addTarget:self action:@selector(PhoneAction) forControlEvents:UIControlEventTouchUpInside]; 
		
    }
		
  	if(btnMsg == nil)
	{
		btnMsg=[UIButton buttonWithType:UIButtonTypeCustom]; 
		btnMsg.frame=CGRectMake(f.size.width-75, 5,32, 32); 
		UIImage *phoneImage=[UIImage imageNamed:@"menu_sms.png"]; 
		
		[btnMsg setBackgroundImage:phoneImage forState:UIControlStateNormal]; 
		[btnMsg addTarget:self action:@selector(MsgAction) forControlEvents:UIControlEventTouchUpInside];
		
		//[TalkImage addSubview:btnMsg];
	}
	
	if (btnTalk == nil) {
		btnTalk=[UIButton buttonWithType:UIButtonTypeCustom]; 
		btnTalk.frame=CGRectMake(f.size.width-60, 0 ,48, 48); 
		UIImage *image = [UIImage imageNamed:@"menu_click_off.png"];
		[btnTalk setBackgroundImage:image forState:UIControlStateNormal]; 
		[btnTalk addTarget:self action:@selector(PhoneAction) forControlEvents:UIControlEventTouchUpInside]; 
	}
	
	m_pImageListener = new CMAddressGetImageListener();
	m_pWebImage = new CMWebImage(m_pImageListener);
	m_pWebImage->SetUserData(BridgeObjectToC(self));
    
    
    if(m_pListener == NULL)
        m_pListener = new CMAddressUpdateDataListener();
    
    if(m_pContacts == nil)
	{
		m_pListener=new CMAddressUpdateDataListener();
		m_pContacts =new CMContacts(m_pListener);
		m_pContacts->SetUserData(BridgeObjectToC(self));
	}
    
    //一进来就显示最近联系人
    showRecent = YES;
    m_pContacts->getRecentContacts();
    [tableView setDelegate:self];
	[tableView setDataSource:self];
    if(tableView)
        [tableView reloadData];

    self.backBtn = [[UIButton alloc]initWithFrame:tableView.frame];
    
    [self.backBtn setBackgroundColor:[UIColor clearColor]];
    
    [self.backBtn addTarget:self action:@selector(hidKeyBoard) forControlEvents:UIControlEventTouchUpInside];
    
    [self.backBtn setHidden:YES];
    
    [self.view addSubview:self.backBtn];
    

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
    
//    [_searchBtn   release];
	SAFEDELETE(m_pWebImage);
	SAFEDELETE(m_pImageListener);
	
}

#pragma mark - Lifecycle

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
	NSIndexPath *tableSelection = [self.tableView indexPathForSelectedRow];
	[self.tableView deselectRowAtIndexPath:tableSelection animated:NO];
	// Set the navbar style to its default color for the list view.
	self.navigationController.navigationBar.barStyle = UIBarStyleDefault;
}


-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];

}


- (void)keyboardWillShow:(NSNotification *)notification
{
    isSearchfieldOnFirstRespond = YES;
    
    [self.backBtn setHidden:NO];
    
}


#pragma mark - UITextfield

- (void) textFieldDidChange:(UITextField *) textField{
    
    if(!isSearchfieldOnFirstRespond)
        return ;
    if (m_pContacts != nil) {
        if (m_pListener != nil) {
            SAFEDELETE(m_pListener);
        }
        SAFEDELETE(m_pContacts);
    }
    //得到输入结束后的内容
    NSString* content = textField.text;
    
    //设置是否显示“最近联系人”
    if([content isEqualToString:@""])
        showRecent = YES;
    else
        showRecent = NO;
    
    if(m_pListener == NULL)
        m_pListener = new CMAddressUpdateDataListener();
    
    if(m_pContacts == nil)
    {
        m_pListener=new CMAddressUpdateDataListener();
        m_pContacts =new CMContacts(m_pListener);
        m_pContacts->SetUserData(BridgeObjectToC(self));
    }
    
    m_pContacts->Cancel();
    
    [tableView reloadData];
    [tool DisimissActivityIndicator];
    
    [tool ShowActivityIndicator:tableView at:CGPointMake((UI_IOS_WINDOW_WIDTH-20)/2,80)];
    
    if(m_pContacts->QuickSearch([content UTF8String]))
        ;
    else
    {
        m_pContacts->getRecentContacts();
    }

    [tableView reloadData];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
// called when 'return' key pressed. return NO to ignore.
{
    [self hidKeyBoard];
    return YES;
}


//goto search
-(void)gotoSearch:(NSString *)value
{
	if(m_pContacts == nil)
	{
		m_pListener=new CMAddressUpdateDataListener();
		m_pContacts =new CMContacts(m_pListener);
		m_pContacts->SetUserData(BridgeObjectToC(self));
	}
	m_pContacts->Search([value UTF8String]);
   [self.tableView reloadData];
	
}

#pragma mark other operator
//hide keyBoard
-(void)hidKeyBoard
{
	//[self hidSearchCancleBtn];
    
    
    
    [self.backBtn setHidden:YES];
    
    
    isSearchfieldOnFirstRespond = NO;


	[_searchField resignFirstResponder];


}

#pragma mark UITableView delegate methods

// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
	TContactsItem item ;
	
	if(m_pContacts && m_pContacts->GetItem(indexPath.row, item))
	{
        CMPersonDetailyViewController * controller = [[CMPersonDetailyViewController alloc]init];
        controller.jid = [NSString stringWithUTF8String:item.sJid.c_str()];
        controller.title = [NSString stringWithUTF8String:item.sName.c_str()];
        [self.navigationController pushViewController:controller animated:YES];
	}
    
    [self hidKeyBoard];

    
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
    
    int count = m_pContacts->GetItemCount();
    if (count == 0) {
        bgview.hidden = NO;
        [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];

    }
    else{
        bgview.hidden = YES;
        [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];

    }
    
    
	if (m_pContacts->IsEnd()) {
		return count;
	}
    
    if (showRecent) {
        return count;
    }
    
	return count+1;
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{

    if (showRecent) {
        return 25;
    }
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    
    
    if (showRecent) {
        UIView *headView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 25)];
        headView.backgroundColor = UIColorRGB(0xeeeeee);
        
        UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 0, UI_IOS_WINDOW_WIDTH, 25)];
        titleLabel.backgroundColor = [UIColor clearColor];
        titleLabel.font = [UIFont systemFontOfSize:14.0f];
        titleLabel.textColor = [UIColor blackColor];
        titleLabel.text = I(@"最近联系人");
        [headView addSubview:titleLabel];

        return headView;
    }
    return nil;
}

//-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
//{
//    if(showRecent)
//        return I(@"最近联系人");
//    else
//        return @"";
//}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{       
	
	if (indexPath.row == m_pContacts->GetItemCount()) {
		return 44;
	}
    
	TContactsItem item ;
	
	if(m_pContacts && m_pContacts->GetItem(indexPath.row, item))
	{
		CGFloat hg = 0;
		if(m_pWebImage->GetFromUrl(0,item.sIcon.c_str()))
		{	
			UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(item.sIcon.c_str())]];// m_image;
			hg = loadImage.size.height;
		}
		else
		{
			UIImage* lImage = [UIImage imageNamed:@"head"];
			hg = lImage.size.height;
		}
		return 60;
        
	}
	return 50;
}
// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	CMTableViewCell *cell = (CMTableViewCell*)[self.tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil) {
        cell = [[CMTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
    }
    
    [cell setSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[self tableView:tableView heightForRowAtIndexPath:indexPath]];

    if (indexPath.row == m_pContacts->GetItemCount() &&  m_pContacts->GetItemCount()!= 0) {
        cell = (CMTableViewCell*)[self.tableView dequeueReusableCellWithIdentifier:@"addressmore"];
        if (cell == nil) {
            cell = [[CMTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"addressmore"];
        }
        
        if(SETTING.GetAutoLoadMore())
        {
            [self RershTableList:cell];
            
        }else {
            btnMore = [UIButton buttonWithType:UIButtonTypeCustom];
            
            [btnMore setImage:[UIImage imageNamed:@"Load_More_nor"] forState:UIControlStateNormal];
            
            [btnMore setImage:[UIImage imageNamed:@"Load_More_sel"] forState:UIControlStateHighlighted];
            
            [btnMore addTarget:self action:@selector(RershTableList) forControlEvents:UIControlEventTouchUpInside];
            
            [btnMore setHidden:NO];
            
            UIImage * loadMorePic = [UIImage imageNamed:@"Load_More_sel"];
            
            [btnMore setFrame:CGRectMake(0, 0, loadMorePic.size.width, loadMorePic.size.height)];
            
            [btnMore setCenter:CGPointMake(UI_IOS_WINDOW_WIDTH/2, cell.contentView.frame.size.height/2)];
            
            [cell.contentView addSubview:btnMore];
            
            //加上"加载更多..."文字说明
            UILabel *lbl_LoadMore = [[UILabel alloc]init] ;
            
            CGSize size_LoadMore =[I(@"加载更多...") sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(NSIntegerMax, cell.contentView.frame.size.height) lineBreakMode:NSLineBreakByCharWrapping];
            [lbl_LoadMore setText:I(@"加载更多...")];
            [lbl_LoadMore setFont:[UIFont systemFontOfSize:16]];
            
            [lbl_LoadMore setFrame:CGRectMake(0, 0, size_LoadMore.width, size_LoadMore.height)];
            [lbl_LoadMore setCenter:CGPointMake(UI_IOS_WINDOW_WIDTH/2-20, cell.contentView.frame.size.height/2)];
            [btnMore addSubview:lbl_LoadMore];
            
            
            
            
            [cell.contentView setBackgroundColor: UIColorRGB(0xd8dbdc)];
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
        
        return cell;		
    }
        
    TContactsItem item ;

    if(m_pContacts && m_pContacts->GetItem(indexPath.row, item))
    {
        cell.TitelLabel.text = [NSString stringWithUTF8String:item.sName.c_str()];
        cell.PhoneLabel.text = [NSString stringWithUTF8String:item.sMobilenumber.c_str()];
        cell.DescLabel.text = [NSString stringWithFormat:@"%@ %@",[NSString stringWithUTF8String:item.sOrg.c_str()],[NSString stringWithUTF8String:item.sDep.c_str()]];
        if(m_pWebImage->GetFromUrl(0,item.sIcon.c_str()))
        {	
            UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(item.sIcon.c_str())]];// m_image;
            cell.LeftImageView.image = loadImage;
            //[loadImage release];
        }
        else
            cell.LeftImageView.image = [UIImage imageNamed:@"head.png"];
    }
    cell.LeftImageView.bounds.size=CGSizeMake(40.0, 40.0);
    //cell.LeftImageView.frame.size=CGSizeMake(40.0, 40.0);
    cell.accessoryType = UITableViewCellAccessoryNone;
	return cell;
}

-(void)talkFun:(id)sender
{
	UIButton *rowButton = (UIButton *)sender;
	
	int rowValue =[rowButton.titleLabel.text intValue];
	NSIndexPath *path = [NSIndexPath indexPathForRow:rowValue inSection:0];
    
	UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:path];
	[[cell contentView] addSubview:btnMsg];
	[[cell contentView] addSubview:btnPhone];

    
}

/*
 // Override to allow orientations other than the default portrait orientation.
 - (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
 // Return YES for supported orientations.
 return (interfaceOrientation == UIInterfaceOrientationPortrait);
 }
 */
@end
