//
//  CMPersonDetailyViewController.m
//  MLPlayer
//
//  Created by water on 14-9-29.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMPersonDetailyViewController.h"
#import "CMTableView.h"
#import "CMLabel.h"
#import "SDWebImage/SDImageCache.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "CMGroupNameViewController.h"
#import "CMGroupManagementViewController.h"
#import "CMGroupManagementMenuViewController.h"
#import "CMGroupManager.h"
#import "UITableViewCell+Helpper.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "CMButton.h"
#import "CMAlertView.h"
#import "CMCoreDataUtils.h"
#import "CMContactManager.h"
#import "CMChatViewController.h"

#define PictureCellHeight 80
#define TextCellHieght 55


#define TitleCoclor UIColorRGB(0x333333)
#define DescColor UIColorRGB(0x999999)


#define kCMGroupInfoExitCellIdentifier @"com.apple.CMGroupInfoExitViewController.CellIdentifier"

@interface CMPersonDetailyViewController ()

@end

@implementation CMPersonDetailyViewController
@synthesize thetableView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    thetableView = [[CMTableView alloc] initWithFrame:CGRectMake(10,0,UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT-20-44) style:UITableViewStylePlain];
    thetableView.delegate = self;
    thetableView.dataSource = self;
    [thetableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    thetableView.showsVerticalScrollIndicator = NO;
    thetableView.backgroundColor = [UIColor clearColor];
    
    [self.view addSubview:thetableView];
    
    m_pContacts = new CMContacts(NULL);
    
    if ( self.jid ) {
        
        isOwner = [self.jid isEqualToString:kXMPPJid];
        
        
        tContactsItem = *new TContactsItem();
        
        CMUserItem  *userCache = (CMUserItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMUserItem class]) withPredicate:Pre_UserJid(self.jid)];
        
        if ( userCache ) {
            
            tContactsItem.sJid = userCache.jid ? [userCache.jid UTF8String] : "";
            tContactsItem.sID = userCache.uid ? [userCache.uid UTF8String] : "";
            tContactsItem.sIcon = userCache.icon ? [userCache.icon UTF8String] : "";
            tContactsItem.sName = userCache.name ? [userCache.name UTF8String] : "";
            tContactsItem.sDep = userCache.sDep ? [userCache.sDep UTF8String] : "";
            tContactsItem.sPosition = userCache.sPosition ? [userCache.sPosition UTF8String] : "";
            tContactsItem.sMobilenumber = userCache.sMobilenumber ? [userCache.sMobilenumber UTF8String] : "";
            tContactsItem.sPhonenumber = userCache.sPhonenumber ? [userCache.sPhonenumber UTF8String] : "";
            tContactsItem.sEmail = userCache.sEmail ? [userCache.sEmail UTF8String] : "";
            
            [thetableView reloadData];
        }
        
        //获取个人信息
        [[CMContactManager manager]doRequestUserInfoWithJid:self.jid listener:^(CMContacts *contact) {
            TContactsItem item;
            
            m_pContacts = contact;
            
            if(contact && contact->GetItem(0, item)){
                tContactsItem = item;
                
                CMUserItem  *currUser = [NSEntityDescription insertNewObjectForEntityForName:NSStringFromClass([CMUserItem class]) inManagedObjectContext:MessageObjectContext];
                currUser.jid = [NSString stringWithUTF8String:item.sJid.c_str()];
                currUser.uid = [NSString stringWithUTF8String:item.sID.c_str()];
                currUser.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
                currUser.name = [NSString stringWithUTF8String:item.sName.c_str()];
                currUser.sDep = [NSString stringWithUTF8String:item.sDep.c_str()];
                currUser.sPosition = [NSString stringWithUTF8String:item.sPosition.c_str()];
                currUser.sMobilenumber = [NSString stringWithUTF8String:item.sMobilenumber.c_str()];
                currUser.sPhonenumber = [NSString stringWithUTF8String:item.sPhonenumber.c_str()];
                currUser.sEmail = [NSString stringWithUTF8String:item.sEmail.c_str()];
                
                [MessageObjectContext save:NULL];
                
            }
            
            [thetableView reloadData];
            
            self.navigationItem.rightBarButtonItem = nil;
        }];
    }
}


- (void)setTContactsItem:(TContactsItem &)item{
    
    tContactsItem = item;
    
    self.jid = [NSString stringWithUTF8String:tContactsItem.sJid.c_str()];
    
}
#pragma mark - Lifecycle

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}


-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
}



#pragma mark UITableView delegate methods

#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    TContactsItem item;
    
    if( !m_pContacts->GetItem(0, item) || isOwner){
        
        return  1;
    }
    
    return  2;

}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0) {
        if (indexPath.row == 0) {
            return PictureCellHeight;
        }else {
            return TextCellHieght;
        }
    }
    return 44;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    switch (section) {
        case 0:
            return 4;
        case 1:
            return 1;
        default:
            break;
    }
    
    return 0;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = (UITableViewCell*)[thetableView dequeueReusableCellWithIdentifier:kCMGroupInfoExitCellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:kCMGroupInfoExitCellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    for (UIView *subView in cell.contentView.subviews) {
        [subView removeFromSuperview];
    }
    
    switch (indexPath.section) {
        case 0:
        {
            switch (indexPath.row) {
                case 0:
                {
                    CMButton *imageView = [[CMButton alloc]initWithFrame:CGRectMake(10, 10, 60, 60)];
                    [imageView sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:tContactsItem.sIcon.c_str()]] forState:UIControlStateNormal placeholderImage:DefaultBigHeaderImage];
                    [cell.contentView addSubview:imageView];
                    
                    
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(85, 10, 175, 23);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:16];
                    titleLabel.textColor = TitleCoclor;
                    
                    NSString *sDep = [NSString stringWithUTF8String:tContactsItem.sDep.c_str()];
                    
                    if (sDep.length > 0) {
                        titleLabel.text = sDep;
                    }else{
                        titleLabel.text =  I(@"无");
                    }
                    [cell.contentView addSubview:titleLabel];
                    
                    
                    CMLabel *detailLabel = [[CMLabel alloc] init];
                    detailLabel.frame = CGRectMake(85, 50, 175, 19);
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.font =[UIFont systemFontOfSize:13];
                    detailLabel.textColor = DescColor;
                    
                    NSString *sPosition = [NSString stringWithUTF8String:tContactsItem.sPosition.c_str()];
                    
                    if (sPosition.length > 0) {
                        detailLabel.text = sPosition;
                    }else{
                        detailLabel.text =  I(@"无");
                    }
                    [cell.contentView addSubview:detailLabel];
                }
                    break;
                case 1:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 10, 250, 16);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:16];
                    titleLabel.textColor = TitleCoclor;
                    titleLabel.text = I(@"邮箱");
                    [cell.contentView addSubview:titleLabel];
                    
                    
                    CMLabel *detailLabel = [[CMLabel alloc] init];
                    detailLabel.frame = CGRectMake(10, 32, 250, 14);
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.font =[UIFont systemFontOfSize:13];
                    detailLabel.textColor = DescColor;
                    detailLabel.textColor = [UIColor lightGrayColor];
                    
                    NSString *sEmail = [NSString stringWithUTF8String:tContactsItem.sEmail.c_str()];
                    
                    if (sEmail.length > 0) {
                        detailLabel.text = sEmail;
                    }else{
                        detailLabel.text =  I(@"无");
                    }
                    [cell.contentView addSubview:detailLabel];
                    break;
                }
                case 2:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 10, 250, 18);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:16];
                    titleLabel.textColor = TitleCoclor;
                    titleLabel.text = I(@"手机");
                    [cell.contentView addSubview:titleLabel];
                    
                    
                    CMLabel *detailLabel = [[CMLabel alloc] init];
                    detailLabel.frame = CGRectMake(10, 36, 250, 10);
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.font =[UIFont systemFontOfSize:13];
                    detailLabel.textColor = DescColor;
                    detailLabel.textColor = [UIColor lightGrayColor];
                    
                    NSString *phoneNo = [NSString stringWithUTF8String:tContactsItem.sMobilenumber.c_str()];
                    if (phoneNo.length > 0) {
                        detailLabel.text = phoneNo;
                        
                        CGFloat buttonWidth = 36;
                        
                        CMButton *sbutton = [[CMButton alloc]initWithFrame:CGRectMake(250 , 0, buttonWidth, buttonWidth)];
                        [sbutton setCenterY:TextCellHieght/2];
                        sbutton.image = [UIImage imageNamed:@"sms_n"];
                        sbutton.hightlightImage = [UIImage imageNamed:@"sms_p"];
                        [cell.contentView addSubview:sbutton];
                        
                        [sbutton setOnClickListener:^(UIButton *sender){
                            
                            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"sms://%@",phoneNo]]];
                            
                        }];
                        [cell.contentView addSubview:sbutton];
                        
                        CMButton *pbutton = [[CMButton alloc]initWithFrame:CGRectMake(190 ,0, buttonWidth, buttonWidth)];
                        [pbutton setCenterY:TextCellHieght/2];
                        pbutton.image = [UIImage imageNamed:@"phone_n"];
                        pbutton.hightlightImage = [UIImage imageNamed:@"phone_p"];
                        [pbutton setOnClickListener:^(UIButton *sender){
                            
                            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"tel://%@",phoneNo]]];
                            
                        }];
                        [cell.contentView addSubview:pbutton];
                    }else{
                        detailLabel.text = I(@"无");
                        
                    }
                    [cell.contentView addSubview:detailLabel];
                }
                    break;
                case 3:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 10, 250, 18);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:16];
                    titleLabel.textColor = TitleCoclor;
                    titleLabel.text = I(@"固定电话");
                    [cell.contentView addSubview:titleLabel];
                    
                    
                    CMLabel *detailLabel = [[CMLabel alloc] init];
                    detailLabel.frame = CGRectMake(10, 36, 250, 10);
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.font =[UIFont systemFontOfSize:13];
                    detailLabel.textColor = DescColor;
                    detailLabel.textColor = [UIColor lightGrayColor];
                    
                    NSString *phoneNo = [NSString stringWithUTF8String:tContactsItem.sPhonenumber.c_str()];
                    if (phoneNo.length > 0) {
                        
                        detailLabel.text = phoneNo;
                        
                        CGFloat buttonWidth = 36;
                        
                        CMButton *pbutton = [[CMButton alloc]initWithFrame:CGRectMake(250 ,0, buttonWidth, buttonWidth)];
                        [pbutton setCenterY:TextCellHieght/2];
                        pbutton.image = [UIImage imageNamed:@"phone_n"];
                        pbutton.hightlightImage = [UIImage imageNamed:@"phone_p"];
                        [pbutton setOnClickListener:^(UIButton *sender){
                            
                            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"tel://%@",phoneNo]]];
                            
                        }];
                        [cell.contentView addSubview:pbutton];
                        
                    }else{
                        detailLabel.text = I(@"无");
                        
                    }
                    [cell.contentView addSubview:detailLabel];
                }
                    break;
                default:
                    break;
            }
        }
            
            break;
        case 1:
        {
            UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(100, 0, 100, 44)];
            titleLabel.backgroundColor = [UIColor clearColor];
            titleLabel.textAlignment= UITextAlignmentCenter;
            titleLabel.font = [UIFont systemFontOfSize:18];
            titleLabel.textColor = kColorForeground;
            titleLabel.text = I(@"发送消息");
            [cell.contentView addSubview:titleLabel];
            
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.selectionStyle = UITableViewCellSelectionStyleGray;
        }
            break;
        default:
            break;
    }
    [cell setRoundSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[self tableView:tableView heightForRowAtIndexPath:indexPath]];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (indexPath.section == 1) {
        if (self.isFromChat && !self.isFromGroupChat) {
            [self.navigationController popViewControllerAnimated:YES];
        }else{
            CMChatViewController * controller = [[CMChatViewController alloc]init];
            [controller setHidesBottomBarWhenPushed:YES];
            controller.chatType = CMSingleChatType;
            
            controller.toJid = [NSString stringWithUTF8String:tContactsItem.sJid.c_str()];
            controller.icon = [NSString stringWithUTF8String:tContactsItem.sIcon.c_str()];
            controller.toUid = [NSString stringWithUTF8String:tContactsItem.sID.c_str()];
            controller.toName = [NSString stringWithUTF8String:tContactsItem.sName.c_str()];
            
            [self.navigationController pushViewController:controller animated:YES];
        }
    }
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
    
    if (section == 2) {
        return 24.0 ;
    }
    return 0.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
 {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

@end
