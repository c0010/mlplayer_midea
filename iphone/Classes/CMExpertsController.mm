//
//  CMExpertsController.m
//  MLPlayer
//
//  Created by kyp on 14-3-26.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMExpertsController.h"
#import "CMAddressControl.h"
#import "cmsettings.h"
#import "CMImage.h"
#import "CMAddressInfoControl.h"
#import "CMTableViewCell.h"
#import "tool.h"
#import "cmglobal.h"
#import "CMQuestionControl.h"
#define kCellIdentifier @"com.apple.CMAddressControl.CellIdentifier"

@interface CMExpertsController ()

@end

@implementation CMExpertsController
@synthesize searchBar;
@synthesize activity;
@synthesize tableView;
@synthesize TalkImage;
@synthesize btnTalk;
@synthesize searchField = _searchField;
@synthesize backBtn = _backBtn;
@synthesize questionctrl;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
    }
    return self;
}

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
	
	mycell.selectionStyle = UITableViewCellSelectionStyleNone;
	mycell.accessoryType = UITableViewCellAccessoryNone;
	
	[dwActiveView startAnimating];
    m_pContacts->RequestMore();

}

-(void)RershTableList
{
    if (m_pContacts) {
        m_pContacts->RequestMore();
    }
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.openAutoKeyboard = YES;
    
    self.titleLabel.text=I(@"@专家");

    
    showRecent=YES;
   
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
    
    _searchField = [[UITextField alloc]initWithFrame:CGRectMake(34, 5, UI_IOS_WINDOW_WIDTH-50, 30)];
    _searchField.backgroundColor = [UIColor clearColor];
    _searchField.font = [UIFont systemFontOfSize:14.0];
    _searchField.delegate = self;
    _searchField.layer.cornerRadius = 2.0;
    _searchField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    _searchField.returnKeyType = UIReturnKeyDone;
    _searchField.placeholder = I(@"请输入姓名或帐号查找");//I(@"想搜“张三”输入“zs”试试");
    [inputBack addSubview:_searchField];
    
    [inputBack addSubview:zoominIconView];
    
	f.origin.y += (48-10);
	f.size.height = UI_IOS_WINDOW_HEIGHT - 64 - (48-10);
	tableView=[[UITableView alloc] initWithFrame:f style:UITableViewStylePlain];
	   
    [self.view addSubview:tableView];
    [tableView addSubview:bgview];
    
    
	[self setActivity:[[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray]];
	
    
    m_pImageListener = new CMExpertsGetImageListener();
	m_pWebImage = new CMWebImage(m_pImageListener);
	m_pWebImage->SetUserData(BridgeObjectToC(self));
    
    
    if(m_pListener == NULL)
        m_pListener = new CMExpertsUpdateDataListener();
    
    if(m_pContacts == nil)
	{
		m_pListener=new CMExpertsUpdateDataListener();
		m_pContacts =new CMContacts(m_pListener);
		m_pContacts->SetUserData(BridgeObjectToC(self));
	}
    
   // m_pContacts->getRecentContacts();
    m_pContacts->SearchByQaCategory(_categoryID.UTF8String);
    
    [tableView setDelegate:self];
	[tableView setDataSource:self];
    
    if(tableView)
       [tableView reloadData];
   
    self.backBtn = [[UIButton alloc]initWithFrame:tableView.frame];
    [self.backBtn setBackgroundColor:[UIColor clearColor]];
    [self.backBtn addTarget:self action:@selector(hidKeyBoard) forControlEvents:UIControlEventTouchUpInside];
    [self.backBtn setHidden:YES];
    [self.view addSubview:self.backBtn];
    
//    //UINavigationItem *navigationItem = [[UINavigationItem alloc] initWithTitle:nil];
//    //向导航栏集合中添加横向按钮列表
//    NSArray *buttons = [NSArray arrayWithObjects:I(@"最近联系人"), I(@"通讯录"), nil];
//    UISegmentedControl* segmentedControl = [[UISegmentedControl alloc] initWithItems:buttons];
//    //设置横向按钮风格
//    segmentedControl.segmentedControlStyle = UISegmentedControlStyleBar;
//    segmentedControl.tintColor=[UIColor whiteColor];
//    [segmentedControl addTarget:self action:@selector(switchtableview:) forControlEvents:UIControlEventValueChanged];
    
}

//-(void )switchtableview:(id)sender
//{
//    UISegmentedControl* control = (UISegmentedControl*)sender;
//    switch (control.selectedSegmentIndex)
//    {
//       case 0:
//            if(!recentorcontact)
//                recentorcontact=YES;
//            [self.tableView reloadData];
//            break;
//            
//       case 1:
//            if(recentorcontact)
//                recentorcontact=NO;
//           // m_pExperts->getexperts();
//
//            [self.tableView reloadData];
//            break;
//            
//    }
//}



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
    SAFEDELETE(m_pContacts);
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

#pragma mark - Request Data

-(void)SearchContacts:(NSString*)keyword
{
    //设置是否显示“最近联系人”
    if([keyword isEqualToString:@""])
        showRecent = YES;
    else
        showRecent = NO;
    
    if(m_pListener == NULL)
        m_pListener = new CMExpertsUpdateDataListener();
    
    if(m_pContacts == nil)
	{
		m_pListener=new CMExpertsUpdateDataListener();
		m_pContacts =new CMContacts(m_pListener);
		m_pContacts->SetUserData(BridgeObjectToC(self));
	}
    
    m_pContacts->Cancel();
    
    [tableView reloadData];
    
    [tool DisimissActivityIndicator];
    
    [tool ShowActivityIndicator:tableView at:CGPointMake((UI_IOS_WINDOW_WIDTH-20)/2,80)];

	if(m_pContacts->QuickSearch([keyword UTF8String]))
        ;
    else
    {
        [tool DisimissActivityIndicator];

         m_pContacts->getRecentContacts();
    }
    [tableView reloadData];
    
}


#pragma mark - UITextfield

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if(!isSearchfieldOnFirstRespond)
        return FALSE;
    
    //得到输入结束后的内容
    NSString* content ;
    if([string isEqualToString:@""])
        content = [textField.text substringToIndex:[textField.text length]-1];
    else
        content = [NSString stringWithFormat:@"%@%@",textField.text,string];
    
    [self SearchContacts:content];
    
    return YES;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField;
{
    
    return YES;
    
}// return NO to disallow editing.
- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    return ;

    
}// became first responder
- (BOOL)textFieldShouldEndEditing:(UITextField *)textField
{
    
    return YES;
}// return YES to allow editing to stop and to resign first responder status. NO to disallow the editing session to end
- (void)textFieldDidEndEditing:(UITextField *)textField
{
    
    return ;

    
}// may be called if forced even if


- (BOOL)textFieldShouldReturn:(UITextField *)textField
// called when 'return' key pressed. return NO to ignore.
{
    
    
    [self hidKeyBoard];
    
    [self SearchContacts:textField.text];

    return YES;
}

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    
    
    return YES;
}




//goto search
-(void)gotoSearch:(NSString *)value
{
	NSLog(@"this searchValue=[%@]",value);
	if(m_pContacts == nil)
	{
		m_pListener=new CMExpertsUpdateDataListener();
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


#pragma mark UITableView data source methods

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    
    if (showRecent) {
        UIView *headView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 25)];
        headView.backgroundColor = UIColorRGB(0xeeeeee);
        
        UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 0, UI_IOS_WINDOW_WIDTH, 25)];
        titleLabel.backgroundColor = [UIColor clearColor];
        titleLabel.font = [UIFont systemFontOfSize:14.0f];
        titleLabel.textColor = [UIColor blackColor];
        titleLabel.text = I(@"推荐专家");
        [headView addSubview:titleLabel];
        
        return headView;
    }
    return nil;
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    
    if (showRecent) {
        return 25;
    }
    return 0;
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
  
    int count = m_pContacts->GetItemCount();
    if (count == 0) {
        bgview.hidden = NO;
        [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
        
    }
    else{
        bgview.hidden = YES;
        [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleSingleLine];
        
    }
    
	if (m_pContacts->IsEnd()) {
		return count;
	}
	return count+1;

}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
		return 55;
    
}


// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    CMTableViewCell *cell = (CMTableViewCell*)[self.tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil) {
        cell = [[CMTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
    }
    
    
    
     if (indexPath.row == m_pContacts->GetItemCount() &&  m_pContacts->GetItemCount()!= 0)
     {
         if(SETTING.GetAutoLoadMore())
         {
             [self RershTableList:cell];
         }else {
             btnMore = [UIButton buttonWithType:UIButtonTypeCustom];
             [btnMore setImage:[UIImage imageNamed:@"Load_More_nor"] forState:UIControlStateNormal];
             [btnMore setImage:[UIImage imageNamed:@"Load_More_sel"] forState:UIControlStateHighlighted];
             [btnMore addTarget:self action:@selector(RershTableList) forControlEvents:UIControlEventTouchUpInside];
             
             [btnMore setHidden:NO];
             btnMore.frame = CGRectMake((320 - 100)/2, (44-30)/2, 100, 30);
             [cell.contentView addSubview:btnMore];
             
             cell.selectionStyle = UITableViewCellSelectionStyleNone;
             cell.accessoryType = UITableViewCellAccessoryNone;
         }
         
         return cell;

     }
    
    
    
   
    
    TContactsItem item ;
    if(m_pContacts && m_pContacts->GetItem(indexPath.row, item))
    {
        
        
        
        
        
        
        cell.TitelLabel.text = [NSString stringWithUTF8String:item.sName.c_str()];
        
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
//    else
//    {
//        TExpertsItem expertitem;
//        if(m_pExperts && m_pExperts->GetItem(indexPath.row, expertitem))
//        {
//            cell.TitelLabel.text=[NSString stringWithUTF8String:expertitem.sName];
//            cell.DescLabel.text=[NSString stringWithUTF8String:expertitem.sPosition];
//        }
//        
//        if(m_pWebImage->GetFromUrl(0,expertitem.sIcon))
//        {
//            UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(expertitem.sIcon)]];// m_image;
//            cell.LeftImageView.image = loadImage;
//            //[loadImage release];
//        }
//        else
//            cell.LeftImageView.image = [UIImage imageNamed:@"head.png"];
//
//        
//    }

    cell.LeftImageView.bounds.size=CGSizeMake(40.0, 40.0);
    cell.accessoryType = UITableViewCellAccessoryNone;
	return cell;

}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    TContactsItem item ;
    m_pContacts->GetItem(indexPath.row, item);
    
    
    //加入最近联系人
    m_pContacts->addRecentContact(item);
    
    
    //选择
    NSString* str;
    NSString* sid;
    
    str=[NSString stringWithUTF8String:item.sName.c_str()];
    
    sid=[NSString stringWithUTF8String:item.sID.c_str()];
    
    
    [questionctrl getExpertsName:str Id:sid];

    
    
    [self.navigationController popViewControllerAnimated:YES];
}


@end
