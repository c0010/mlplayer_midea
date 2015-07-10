//
//  CMGroupManagementMenuViewController.m
//  MLPlayer
//
//  Created by water on 14-7-10.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupManagementMenuViewController.h"
#import "CMTableView.h"
#import "CMGroupManagementViewController.h"
#import "CMInviteNewViewController.h"
#import "UITableViewCell+Helpper.h"
#import "CMGroupManager.h"
#import "CMGroupInfoExitViewController.h"

@interface CMGroupManagementMenuViewController ()

@end

@implementation CMGroupManagementMenuViewController

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
    
    self.verArray = @[I(@"不允许加入"),I(@"不需要身份验证"),I(@"需要身份验证")];
    
    thetableView = [[CMTableView alloc] initWithFrame:CGRectMake(10,0,UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT-20) style:UITableViewStylePlain];
	thetableView.delegate = self;
	thetableView.dataSource = self;
    [thetableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    thetableView.backgroundColor = [UIColor clearColor];
    
	[self.view addSubview:thetableView];
}

-(void)setItem:(TGroupInfoItem &)item
{
    
    m_pGroupInfoItem =item;
    
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	if (m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateManager) {
        return 2;
    }else if (m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateCreater){
        return 3;
    }
    return 0;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
    
	if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:kCellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    if (m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateManager) {
        switch (indexPath.row) {
            case 0:
            {
                cell.textLabel.text = I(@"邀请新成员");
            }
                break;
            case 1:
            {
                cell.textLabel.text = I(@"身份验证");
                cell.detailTextLabel.text = [self.verArray objectAtIndex:m_pGroupInfoItem.nFlag];
                cell.detailTextLabel.textColor = [UIColor lightGrayColor];
            }
                break;
            default:
                break;
        }
    }else if (m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateCreater){
        switch (indexPath.row) {
            case 0:
            {
                cell.textLabel.text = I(@"邀请新成员");
            }
                break;
            case 1:
            {
                cell.textLabel.text = I(@"设置管理员");
            }
                break;
            case 2:
            {
                cell.textLabel.text = I(@"身份验证");
                cell.detailTextLabel.text = [self.verArray objectAtIndex:m_pGroupInfoItem.nFlag];
                cell.detailTextLabel.textColor = [UIColor lightGrayColor];
            }
                break;
            default:
                break;
        }
    }
    
    cell.textLabel.font = [UIFont systemFontOfSize:18.0];
    [cell setRoundSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:44];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateManager) {
        switch (indexPath.row) {
            case 0:
            {
                CMInviteNewViewController *controller = [[CMInviteNewViewController alloc]init];
                controller.title = I(@"邀请新成员");
                [controller setItem:m_pGroupInfoItem];
                [self.navigationController pushViewController:controller animated:YES];
            }
                break;
            case 1:
            {
                UIActionSheet *action = [[UIActionSheet alloc]initWithTitle:nil delegate:self cancelButtonTitle:I(@"取消") destructiveButtonTitle:nil otherButtonTitles:I(@"不允许加入"),I(@"不需要身份验证"),I(@"需要身份验证"), nil];
                [action showInView:self.view];
            }
                break;
            default:
                break;
        }
    }else if (m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateCreater){
        switch (indexPath.row) {
            case 0:
            {
                CMInviteNewViewController *controller = [[CMInviteNewViewController alloc]init];
                controller.title = I(@"邀请新成员");
                [controller setItem:m_pGroupInfoItem];
                [self.navigationController pushViewController:controller animated:YES];
            }
                break;
            case 1:
            {
                CMGroupManagementViewController *controller = [[CMGroupManagementViewController alloc]init];
                controller.title = I(@"设置管理员");
                [controller setItem:m_pGroupInfoItem];
                controller.editType = CMGroupMemberEditTypeManager;
                [self.navigationController pushViewController:controller animated:YES];
            }
                break;
            case 2:
            {
                UIActionSheet *action = [[UIActionSheet alloc]initWithTitle:nil delegate:self cancelButtonTitle:I(@"取消") destructiveButtonTitle:nil otherButtonTitles:I(@"不允许加入"),I(@"不需要身份验证"),I(@"需要身份验证"), nil];
                [action showInView:self.view];
            }
                break;
            default:
                break;
        }
    }
    
    
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex != actionSheet.cancelButtonIndex) {
        [tool ShowActivityIndicator:self.view];

        NSString *roomId = [NSString stringWithUTF8String:m_pGroupInfoItem.sID.c_str()];
        [[CMGroupManager manager] doUpdateFlagWithroomID:roomId flag:buttonIndex success:^{
            m_pGroupInfoItem.nFlag = buttonIndex;
            [thetableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:m_pGroupInfoItem.nIsOccupant == CMGroupMemberStateCreater ? 2 : 1 inSection:0]] withRowAnimation:UITableViewRowAnimationNone];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:RefreshGroupInfoNSNotification object:nil];
        }];
    }
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    return 10.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
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
