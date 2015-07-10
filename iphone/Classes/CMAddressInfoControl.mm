//
//  CMAddressInfoControl.m
//  MLPlayer
//
//  Created by sunjj on 12-2-21.
//  Copyright 2012 w. All rights reserved.
//
#include "cmwebimage.h"
#import "CMAddressInfoControl.h"
#import "CMTableView.h"
#import "CMImage.h"
#import "CMChatViewController.h"
#include "cmmyinfo.h"
#import "UITableViewCell+Helpper.h"

#define kCellHeight  58

@implementation CMAddressInfoControl
@synthesize ListTableView;
@synthesize isFromChat;
@synthesize isOwner;

#define kCellIdentifier @"com.apple.CMAddressInfoControl.CellIdentifier"

-(void)getAddItem:(TContactsItem)item
{
    
    m_TContactsItem.sID = item.sID;
    m_TContactsItem.sName = item.sName;
    m_TContactsItem.sIcon = item.sIcon;
    m_TContactsItem.sSex = item.sSex;
    m_TContactsItem.sOrg = item.sOrg;
    m_TContactsItem.sPosition = item.sPosition;
    m_TContactsItem.sMobilenumber = item.sMobilenumber;
    m_TContactsItem.sShortnumber = item.sShortnumber;
    m_TContactsItem.sPhonenumber = item.sPhonenumber;
    m_TContactsItem.sEmail = item.sEmail;
    m_TContactsItem.sFax = item.sFax;
    m_TContactsItem.sJid = item.sJid;
    m_TContactsItem.nIsManager = item.nIsManager;


    isOwner = [[NSString stringWithUTF8String:SETTING.GetXMPPJid()] isEqualToString:[NSString stringWithUTF8String:m_TContactsItem.sJid.c_str()]];
}


-(void)MobileAction:(id)sender
{	
	UIButton* btn = (UIButton*)sender;
	const char* sNo = nil;
    
    if(m_pContacts)
        m_pContacts->addRecentContact(m_TContactsItem);
    
	if(btn.tag == 1)
		sNo = m_TContactsItem.sMobilenumber.c_str();
	else
		sNo = m_TContactsItem.sShortnumber.c_str();
    
	if (strlen(sNo) <= 0) {
		[tool ShowAlert:I(@"没有找到手机号码！")];
	}else {
		NSString* pNs = [NSString stringWithFormat:@"tel://%@",[NSString stringWithUTF8String:sNo]];
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:pNs]];
	}
}
-(void)MsgAction:(id)sender
{
	UIButton* btn = (UIButton*)sender;
	const char* sNo = nil;
    
    if(m_pContacts)
        m_pContacts->addRecentContact(m_TContactsItem);
    
	if(btn.tag == 1)
		sNo = m_TContactsItem.sMobilenumber.c_str();
	else
		sNo = m_TContactsItem.sShortnumber.c_str();
	if (strlen(sNo) <= 0) {	
		[tool ShowAlert:I(@"没有找到手机号码！")];
	}else {
        
		NSString* pNs = [NSString stringWithFormat:@"sms://%@",[NSString stringWithUTF8String:sNo]];
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:pNs]];
	}
}


-(void)PhoneAction
{
    
    if(m_pContacts)
        m_pContacts->addRecentContact(m_TContactsItem);
    
	if (m_TContactsItem.sPhonenumber.size() <= 0 ) {
		[tool ShowAlert:I(@"没有找到固定号码！")];//@"没有找到固定号码！"
	}else {
		NSString* pNs = [NSString stringWithFormat:@"tel://%@",[NSString stringWithUTF8String:m_TContactsItem.sPhonenumber.c_str()]];
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:pNs]];
	}
}

-(void)MailAction
{
    if(m_pContacts)
        m_pContacts->addRecentContact(m_TContactsItem);

	if (m_TContactsItem.sMobilenumber.size() <= 0 ) {
		[tool ShowAlert:I(@"没有找到邮件地址！")];//@"没有找到邮件地址！"
	}else {
		NSString* pNs = [NSString stringWithFormat:@"mail://%@",[NSString stringWithUTF8String:m_TContactsItem.sMobilenumber.c_str()]];
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:pNs]];
	}
}

-(void)viewDidLoad
{
	[super viewDidLoad];
	
    m_pContacts = new CMContacts(NULL);
    
	ListTableView = [[UITableView alloc] initWithFrame:CGRectMake(10,0,UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT-20-44) style:UITableViewStylePlain];
	//[ListTableView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];

	[ListTableView setDelegate:self];
	[ListTableView setDataSource:self];
    ListTableView.showsVerticalScrollIndicator = NO;
    [ListTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
	[self.view addSubview:ListTableView];

    if ([ListTableView respondsToSelector:@selector(setSeparatorInset:)]) {
        [ListTableView setSeparatorInset:UIEdgeInsetsZero];
    }
    ListTableView.backgroundColor = [UIColor clearColor];
	
	m_pImageListener = new CMAddressInfoGetImageListener();
	m_pWebImage = new CMWebImage(m_pImageListener);
	m_pWebImage->SetUserData(BridgeObjectToC(self));
	
}

#pragma mark UITableView delegate methods


// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 1) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
        [self sendMessageButtonPressed:nil];
    }
	
}

#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	if (! isOwner) {
        return 2;
    }
    return 1;
}



// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0) {
        return 5;
    }
	return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	if (indexPath.section == 0) {
        if(indexPath.row == 0)
        {
            CGFloat hg = 0;
            
            if(m_pWebImage->GetFromUrl(0,m_TContactsItem.sIcon.c_str()))
            {
                //UIImage* loadImage  =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(m_TContactsItem.sIcon)]];// m_image;
                hg = 40;
                //[loadImage release];
            }
            else
            {
                //UIImage* lImage = [UIImage imageNamed:@"headbig"];
                hg = 40;
            }
            return MAX(hg+40,kCellHeight);
        }
        return kCellHeight;
    }
    return 44;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil)
	{
        cell = [[UITableViewCell alloc] initWithStyle:(indexPath.section == 1) ? UITableViewCellStyleDefault : UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
	}
    
    [cell setRoundSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[self tableView:tableView heightForRowAtIndexPath:indexPath]];

	cell.accessoryType = UITableViewCellAccessoryNone;
	[cell setSelectionStyle:UITableViewCellSelectionStyleNone];
	
	CGRect f = CGRectMake(15, 10, 260, 15);
	UILabel * lbltitle = [[UILabel alloc] initWithFrame:f];
	[lbltitle setBackgroundColor:[UIColor clearColor]];
	
	lbltitle.textColor = kTextColorDark ;
	lbltitle.font = [UIFont systemFontOfSize:kTextSizeMid ];
	
	f.origin.y += 25;
	UILabel * lblview = [[UILabel alloc]initWithFrame:f];
	[lblview setBackgroundColor:[UIColor clearColor]];
	lblview.textColor = kTextColorNormal;
	lblview.font = [UIFont systemFontOfSize:kTextSizeSml];
	
	[cell.contentView addSubview:lbltitle];
	[cell.contentView addSubview:lblview];	
	
	NSString *strTitle=@"";
	NSString *strValue=@"";

	switch (indexPath.section) {
        case 0:
        {
            switch (indexPath.row)
            {
                case 0:
                {
                    UIImage* loadImage = nil;
                    if(m_pWebImage->GetFromUrl(0,m_TContactsItem.sIcon.c_str()))
                        loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(m_TContactsItem.sIcon.c_str())]];// m_image;
                    
                    if(!loadImage)
                        loadImage = [UIImage imageNamed:@"headbig"];
                    
                    UIImageView *headview = [[UIImageView alloc] init];
                    headview.layer.cornerRadius = 2.f;
                    headview.layer.masksToBounds = YES;
                    headview.image = loadImage;
                    CGFloat xoff = 10;
                    CGFloat yoff = 10;
                    headview.frame = CGRectMake(xoff, yoff, 60, 60);
                    xoff += 60;
                    xoff += 10;
                    lblview.text = I(@"部门:");// @"部门：";
                    lblview.frame = CGRectMake(xoff, yoff, 200, 20);
                    lblview.font = [UIFont systemFontOfSize:kTextSizeMid ];

                    if([[NSString stringWithUTF8String:m_TContactsItem.sPosition.c_str()] isEqualToString:@""])
                        lblview.text = [NSString stringWithFormat:@"%@  %@",I(@"部门:"),I(@"无")];
                    else
                        lblview.text = [NSString stringWithFormat:@"%@  %@",I(@"部门:"),[NSString stringWithUTF8String:m_TContactsItem.sDep.c_str()]];
                    
                    
                    
                    lbltitle.frame = CGRectMake(xoff, yoff + 40, 200, 20);
                    lbltitle.textColor = kTextColorDark;
                    lbltitle.font = [UIFont systemFontOfSize:kTextSizeSml ];

                    if([[NSString stringWithUTF8String:m_TContactsItem.sPosition.c_str()] isEqualToString:@""])
                        lbltitle.text = [NSString stringWithFormat:@"%@  %@",I(@"岗位:"),I(@"无")];
                    else
                        lbltitle.text = [NSString stringWithFormat:@"%@  %@",I(@"岗位:"),[NSString stringWithUTF8String:m_TContactsItem.sPosition.c_str()]];
                    
                    [cell.contentView addSubview:headview];
                    return cell;
                    break;
                }
                    //		case 1:
                    //			strTitle= I(@"岗位:");
                    //			strValue = [NSString stringWithUTF8String:m_TContactsItem.sPosition];
                    //			break;
                case 1:{
                    strTitle=   I(@"手机");
                    strValue = [NSString stringWithUTF8String:m_TContactsItem.sMobilenumber.c_str()];
                    if([strValue length] > 0)
                    {
                        UIImage* image = [UIImage imageNamed:@"phone_n"];
                        UIButton* btnPhone=[UIButton buttonWithType:UIButtonTypeCustom];
                        btnPhone.frame=CGRectMake(UI_IOS_WINDOW_WIDTH-150,5,image.size.width,image.size.height);
                        [btnPhone setBackgroundImage:[UIImage imageNamed:@"phone_n"] forState:UIControlStateNormal];
                        [btnPhone setBackgroundImage:[UIImage imageNamed:@"phone_p"] forState:UIControlStateHighlighted];
                        [btnPhone addTarget:self action:@selector(MobileAction:) forControlEvents:UIControlEventTouchUpInside];
                        btnPhone.tag = 1;
                        [btnPhone setCenterY:kCellHeight/2];
                        
                        UIButton* btnMsg=[UIButton buttonWithType:UIButtonTypeCustom];
                        btnMsg.frame=CGRectMake(UI_IOS_WINDOW_WIDTH-85, 5,image.size.width,image.size.height);
                        
                        [btnMsg setBackgroundImage:[UIImage imageNamed:@"sms_n"] forState:UIControlStateNormal];
                        [btnMsg setBackgroundImage:[UIImage imageNamed:@"sms_p"] forState:UIControlStateHighlighted];
                        [btnMsg addTarget:self action:@selector(MsgAction:) forControlEvents:UIControlEventTouchUpInside];
                        [btnMsg setCenterY:kCellHeight/2];

                        btnMsg.tag = 1;
                        [cell.contentView addSubview:btnMsg];
                        [cell.contentView addSubview:btnPhone];
                    }
                    
                    break;
                }
                case 2:{
                    strTitle=  I(@"固定电话");
                    strValue = [NSString stringWithUTF8String:m_TContactsItem.sPhonenumber.c_str()];
                    if([strValue length] > 0)
                    {
                        UIImage* image = [UIImage imageNamed:@"phone_n"];
                        UIButton* btnPhone=[UIButton buttonWithType:UIButtonTypeCustom];
                        btnPhone.frame=CGRectMake(UI_IOS_WINDOW_WIDTH-150,5,image.size.width,image.size.height);
                        [btnPhone setBackgroundImage:[UIImage imageNamed:@"phone_n"] forState:UIControlStateNormal];
                        [btnPhone setBackgroundImage:[UIImage imageNamed:@"phone_p"] forState:UIControlStateHighlighted];
                        [btnPhone addTarget:self action:@selector(PhoneAction) forControlEvents:UIControlEventTouchUpInside];
                        [btnPhone setCenterY:kCellHeight/2];

                        [cell.contentView addSubview:btnPhone];
                    }
                    break;
                }
                case 3:
                {
                    strTitle=  I(@"短号");
                    strValue = [NSString stringWithUTF8String:m_TContactsItem.sShortnumber.c_str()];
                    if([strValue length] > 0)
                    {
                        UIImage* image = [UIImage imageNamed:@"phone_n"];
                        UIButton* btnPhone=[UIButton buttonWithType:UIButtonTypeCustom]; 
                        btnPhone.frame=CGRectMake(UI_IOS_WINDOW_WIDTH-150,5,image.size.width,image.size.height); 
                        [btnPhone setBackgroundImage:[UIImage imageNamed:@"phone_n"] forState:UIControlStateNormal]; 
                        [btnPhone setBackgroundImage:[UIImage imageNamed:@"phone_p"] forState:UIControlStateHighlighted]; 
                        [btnPhone addTarget:self action:@selector(MobileAction:) forControlEvents:UIControlEventTouchUpInside];
                        [btnPhone setCenterY:kCellHeight/2];
                        btnPhone.tag = 2;
                        
                        UIButton* btnMsg=[UIButton buttonWithType:UIButtonTypeCustom]; 
                        btnMsg.frame=CGRectMake(UI_IOS_WINDOW_WIDTH-85, 5,image.size.width,image.size.height); 
                        
                        [btnMsg setBackgroundImage:[UIImage imageNamed:@"sms_n"] forState:UIControlStateNormal]; 
                        [btnMsg setBackgroundImage:[UIImage imageNamed:@"sms_p"] forState:UIControlStateHighlighted];
                        [btnMsg addTarget:self action:@selector(MsgAction:) forControlEvents:UIControlEventTouchUpInside];
                        [btnMsg setCenterY:kCellHeight/2];
                        btnMsg.tag = 2;
                        
                        [cell.contentView addSubview:btnMsg];
                        [cell.contentView addSubview:btnPhone];
                    }
                    break;
                }
                case 4:	
                    strTitle=  I(@"邮箱");
                    strValue =[NSString stringWithUTF8String:m_TContactsItem.sEmail.c_str()];
                    
                    break;		
                default:
                    break;
            }
            
            lbltitle.text = strTitle;
            if([strValue length] <= 0)
                strValue = I(@"暂无");
            lblview.text =strValue;
        }
            break;
        case 1:
        {
            [cell setSelectionStyle:UITableViewCellSelectionStyleGray];
            cell.textLabel.text = I(@"发送消息");
            cell.textLabel.textColor = [UIColor colorWithRed:27.0/255.0 green:109.0/255.0 blue:179.0/255.0 alpha:1.0f];
            cell.textLabel.textAlignment= UITextAlignmentCenter;
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.textLabel.font = [UIFont systemFontOfSize:18.0];
        }
            break;
        default:
            break;
    }
	
	return cell;
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    
    if (section == 0) {
        return 10.0 ;
    }
    return 24.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- ( CGFloat )tableView:( UITableView *)tableView heightForFooterInSection:(NSInteger )section
{
    
    if (section == 1) {
        return 30.0 ;
    }
    return 0.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

//聊天界面
- (void) sendMessageButtonPressed:(UIButton *)button{
    if (self.isFromChat) {
        [self.navigationController popViewControllerAnimated:YES];
    }else{
        CMChatViewController * controller = [[CMChatViewController alloc]init];
        [controller setHidesBottomBarWhenPushed:YES];
        controller.chatType = CMSingleChatType;

        controller.toJid = [NSString stringWithUTF8String:m_TContactsItem.sJid.c_str()];
        controller.icon = [NSString stringWithUTF8String:m_TContactsItem.sIcon.c_str()];
        controller.toUid = [NSString stringWithUTF8String:m_TContactsItem.sID.c_str()];
        controller.toName = [NSString stringWithUTF8String:m_TContactsItem.sName.c_str()];
        
        [self.navigationController pushViewController:controller animated:YES];
    }
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
    m_pImageListener = nil;
    SAFEDELETE(m_pContacts);
}
@end
