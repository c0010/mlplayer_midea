 //
//  CMGroupManagementViewController.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#define kGroupManageCell @"com.ulp.groupmanagecell"

#import "CMGroupManagementViewController.h"
#import "CMGroupMembersCell.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "CMChatViewController.h"
#import "UITableViewCell+Helpper.h"
#import "CMContactManager.h"
#import "CMGroupManager.h"
#import "CMGroupInfoExitViewController.h"
#import "CMCoreDataUtils.h"
#import "CMSearchModel.h"
#import "CMInteractConfig.h"
#import "CMPersonDetailyViewController.h"
#import "UIScrollView+SVPullToRefresh.h"

@interface CMGroupManagementViewController ()
@end

@implementation CMGroupManagementViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        
        m_pGroupInfoItem = new TGroupInfoItem();

        self.members = [NSMutableArray array];
    }
    return self;
}

-(void)setItem:(TGroupInfoItem&)item
{
    *m_pGroupInfoItem = item;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.searchBar=[[CMSearchBar alloc]initWithFrame:CGRectMake(0, 0, 320, 44)];
    self.searchBar.delegate=self;
    [self.searchBar setPlaceholder:I(@"搜索")];
    
    self.occupantTableView = [[UITableView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-44-20) style:UITableViewStylePlain];
    [self.occupantTableView setDelegate:self];
    [self.occupantTableView setDataSource:self];
	self.occupantTableView.tableHeaderView = self.searchBar;
    
    [self.occupantTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    self.occupantTableView.backgroundColor = [UIColor clearColor];

    if (self.editType == CMGroupMemberEditTypeRemove && m_pGroupInfoItem->nIsOccupant != 0 ) {
        self.commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.commitBtn setTitle:I(@"编辑") forState:UIControlStateNormal];
        [self.commitBtn setFrame:CGRectMake(0, 0, 40, 40)];
        [self.commitBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        self.commitBtn.titleLabel.font = [UIFont boldSystemFontOfSize:18.f];
        [self.commitBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateHighlighted];
        [self.commitBtn addTarget:self action:@selector(commitButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem * commitBarItem = [[UIBarButtonItem alloc]initWithCustomView:self.commitBtn];
        
        self.navigationItem.rightBarButtonItem = commitBarItem;
    }
    
    [self.view addSubview:self.occupantTableView];
    
    WEAKSELF;
    [self.occupantTableView addPullToRefreshWithActionHandler:^{
        STRONGSELF;
        [sself reloadTableViewDataSource];
    }];
    
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"roomID == %@", [NSString stringWithUTF8String:m_pGroupInfoItem->sID.c_str()]];

    NSArray *memberscache = [CMCoreDataUtils fetchManagedObjects:NSStringFromClass([CMMemberItem class]) withPredicate:predicate];
    
    for (CMMemberItem *member in memberscache) {
        
        [self.members addObject:[[CMSearchModel model] toMModel:member index:0]];
    }
    
    //在结果中权限降序排序
    [self.members sortUsingComparator:^NSComparisonResult(CMSearchModel* obj1, CMSearchModel* obj2) {
        
        if (obj1.manager > obj2.manager) {
            return NSOrderedAscending;
        }else if (obj1.manager < obj2.manager){
            return NSOrderedDescending;
        }
        else
            return NSOrderedSame;
    }];
    
    self.originalMembers = self.members;
    
    [tool ShowActivityIndicator:self.view];
    //请求群成员列表
    if (self.editType == CMGroupMemberEditTypeTrain) {
        [self doRequestTrainMembers];
    }else
        [self doRequestGroupMembers];
}


//请求群成员列表
- (void)doRequestGroupMembers{
    
    NSString *roomID = [NSString stringWithUTF8String:m_pGroupInfoItem->sID.c_str()];
    
    [[CMContactManager manager] doRequestOccupantsList: roomID success:^(CMContacts* contacts) {
        
        //请求群成员列表成功，清空历史成员列表缓存
        {
            NSPredicate *predicate = [NSPredicate predicateWithFormat:@"roomID == %@", roomID];
            [CMCoreDataUtils clearManagedObjects:NSStringFromClass([CMMemberItem class]) withPredicate:predicate];
            [self.members removeAllObjects];
        }
        
        for (int i= 0; i < contacts->GetItemCount(); i++) {
            TContactsItem item;
            if(contacts && contacts->GetItem(i, item)){
                
                [self.members addObject:[[CMSearchModel model] toCModel:item index:i]];
                
                //在结果中权限降序排序
                [self.members sortUsingComparator:^NSComparisonResult(CMSearchModel* obj1, CMSearchModel* obj2) {
                    
                    if (obj1.manager > obj2.manager) {
                        return NSOrderedAscending;
                    }else if (obj1.manager < obj2.manager){
                        return NSOrderedDescending;
                    }
                    else
                        return NSOrderedSame;
                }];
                
                //保存群成员到缓存
                [CMCoreDataUtils saveGroupMembersWithTContactsItem:item roomID:roomID];
            }
        }
        
        self.originalMembers = self.members;
        
        [self.occupantTableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
        
        //群信息界面更新群成员数量
        [[NSNotificationCenter defaultCenter] postNotificationName:RefreshGroupInfoNSNotification object:nil];
        
        [self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.3];
        
    } failure:^(int errorCode) {
        
        [tool ShowError:errorCode];
        
        [self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.3];
    }];
}

//获取培训班成员
-(void)doRequestTrainMembers
{
    
    
    [[CMContactManager manager] doRequestTrainOccupantsList: self.trainID success:^(CMContacts* contacts) {
        
        //请求群成员列表成功，清空历史成员列表缓存
        {
            NSPredicate *predicate = [NSPredicate predicateWithFormat:@"roomID == %@", self.trainID];
            [CMCoreDataUtils clearManagedObjects:NSStringFromClass([CMMemberItem class]) withPredicate:predicate];
            [self.members removeAllObjects];
        }
        
        for (int i= 0; i < contacts->GetItemCount(); i++) {
            TContactsItem item;
            if(contacts && contacts->GetItem(i, item)){
                
                [self.members addObject:[[CMSearchModel model] toCModel:item index:i]];
                
                //在结果中权限降序排序
                [self.members sortUsingComparator:^NSComparisonResult(CMSearchModel* obj1, CMSearchModel* obj2) {
                    
                    if (obj1.manager > obj2.manager) {
                        return NSOrderedAscending;
                    }else if (obj1.manager < obj2.manager){
                        return NSOrderedDescending;
                    }
                    else
                        return NSOrderedSame;
                }];
                
                //保存群成员到缓存
                [CMCoreDataUtils saveGroupMembersWithTContactsItem:item roomID:self.trainID];
            }
        }
        
        self.originalMembers = self.members;
        
        [self.occupantTableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
        
        [self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.3];
        
    } failure:^(int errorCode) {
        
        [tool ShowError:errorCode];
        
        [self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.3];
    }];
}

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText{
    
    if([searchText isEqualToString:@""]){
        self.members = self.originalMembers;

    }else{
        self.members = [CMCoreDataUtils filterContacts:self.originalMembers keyword:searchText];
    }
    
    [self.occupantTableView reloadData];
}

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    [self.searchBar resignFirstResponder];
}

- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar
{
    searchBar.placeholder = I(@"想搜“张三”输入“zs”试试");

    [self.searchBar setShowsCancelButton:YES animated:YES];
}

- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar{
    
    searchBar.placeholder = I(@"搜索");

    [self.searchBar setShowsCancelButton:NO animated:YES];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar
{
    self.searchBar.text = @"";
    [self.searchBar resignFirstResponder];
    [self searchBar:searchBar textDidChange:self.searchBar.text];
}

-(void)commitButtonPressed:(UIButton *)sender
{
    if (self.editType == CMGroupMemberEditTypeRemove) {
        sender.selected= !sender.selected;
        [self.commitBtn setTitle:sender.selected ? I(@"完成") : I(@"编辑") forState:UIControlStateNormal];
        [self.occupantTableView reloadData];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)viewWillDisappear:(BOOL)animated
{
    [self.searchBar resignFirstResponder];
    [super viewWillDisappear:animated];
}

#pragma mark -
#pragma mark UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.members.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMGroupMembersCell *cell = [self.occupantTableView dequeueReusableCellWithIdentifier:kGroupManageCell];
    if (cell == nil) {
        cell = [[CMGroupMembersCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kGroupManageCell] ;
        
        cell.accessoryType = UITableViewCellAccessoryNone;
    }

    cell.optionButton.titleLabel.font = [UIFont systemFontOfSize:15.f];
    [cell.optionButton setBackgroundImage:[UIImage imageNamed:@"interact_remove_btn_normal"] forState:UIControlStateNormal];
    [cell.optionButton setBackgroundImage:[UIImage imageNamed:@"interact_remove_btn_highlight"] forState:UIControlStateHighlighted];
    [cell.optionButton setTitle:I(@"移除") forState:UIControlStateNormal];
    cell.optionButton.tag = indexPath.row;
    cell.headButton.tag = indexPath.row;


    CMSearchModel *model = [self.members objectAtIndex:indexPath.row];
    
    if ([model.jid isEqualToString:kXMPPJid]) {
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }else{
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
    
    if(self.editType == CMGroupMemberEditTypeRemove)
    {
        if(model.manager == CMGroupMemberStateCreater)
        {
            cell.cellType = CMGroupMembersCellTypeMain;
            cell.accessoryLabel.text = I(@"群主");
        }else if (model.manager == CMGroupMemberStateManager){
            if (m_pGroupInfoItem->nIsOccupant == CMGroupMemberStateCreater) {
                if (self.commitBtn.selected) {
                    cell.cellType = CMGroupMembersCellTypeMemberEdit;
                }else{
                    cell.cellType = CMGroupMembersCellTypeManager;
                    cell.accessoryLabel.text = I(@"管理员");
                }
            }else{
                cell.cellType = CMGroupMembersCellTypeManager;
                cell.accessoryLabel.text = I(@"管理员");
            }
        }else{
            if (self.commitBtn.selected) {
                cell.cellType = CMGroupMembersCellTypeMemberEdit;
            }else{
                cell.cellType = CMGroupMembersCellTypeMemberDefault;
            }
        }
    }
    else if(self.editType == CMGroupMemberEditTypeManager)
    {
        //设置管理员
        {
            CGRect rect = cell.optionButton.frame;
            rect.size.width = 70;
            rect.origin.x = 240;
            cell.optionButton.frame = rect;
        }
        cell.optionButton.titleLabel.font = [UIFont systemFontOfSize:12.f];
        
        if(model.manager == CMGroupMemberStateCreater)
        {
            cell.cellType = CMGroupMembersCellTypeMain;
            cell.accessoryLabel.text = I(@"群主");
        }else if (model.manager == CMGroupMemberStateManager){
            cell.cellType = CMGroupMembersCellTypeMemberEdit;
            [cell.optionButton setTitle:I(@"取消管理员") forState:UIControlStateNormal];
            [cell.optionButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
            [cell.optionButton setBackgroundImage:[UIImage imageNamed:@"interact_canclemanager_btn_highlight"] forState:UIControlStateHighlighted];
            [cell.optionButton setBackgroundImage:[UIImage imageNamed:@"interact_canclemanager_btn_normal"] forState:UIControlStateNormal];
        }else{
            cell.cellType = CMGroupMembersCellTypeMemberEdit;
            [cell.optionButton setTitle:I(@"设为管理员") forState:UIControlStateNormal];
            [cell.optionButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [cell.optionButton setBackgroundImage:[UIImage imageNamed:@"interact_setmanager_btn_highlight"] forState:UIControlStateHighlighted];
            [cell.optionButton setBackgroundImage:[UIImage imageNamed:@"interact_setmanager_btn_normal"] forState:UIControlStateNormal];
        }
        [cell.optionButton setTitleEdgeInsets:UIEdgeInsetsMake(0, 5, 0, 5)];
    }else if(self.editType == CMGroupMemberEditTypeTrain)
    {
        cell.cellType = CMGroupMembersCellTypeMain;
        //cell.accessoryLabel.text = @"";
    }
    
    [cell.headButton sd_setImageWithURL:[NSURL URLWithString:model.icon] forState:UIControlStateNormal placeholderImage:DefaultHeaderImage];
    [cell.headButton setOnClickListener:^(UIButton *sender){
        
        CMPersonDetailyViewController * controller = [[CMPersonDetailyViewController alloc]init];
        controller.jid = model.jid;
        controller.title = model.name;
        [self.navigationController pushViewController:controller animated:YES];

    }];
    cell.titlelabel.text = model.name;
    
    //事件处理
    [cell.optionButton setOnClickListener:^(UIButton *sender){
        
        CMSearchModel *model = [self.members objectAtIndex:sender.tag];

        NSString *sID = model.uid;
        NSString *roomID = [NSString stringWithUTF8String:m_pGroupInfoItem->sID.c_str()];

        if (self.editType == CMGroupMemberEditTypeRemove) {
            //踢出成员
            [tool ShowActivityIndicator:self.view];
            [[CMGroupManager manager] doKickGroupOccupant:roomID sid:sID success:^{
                [tool ShowAlert:I(@"移除成功！")];
                [self performSelector:@selector(refreshListA) withObject:nil afterDelay:0.3];
            }];
        }else if(self.editType == CMGroupMemberEditTypeManager){
            //设置/取消 管理员
            [tool ShowActivityIndicator:self.view];
            if (model.manager == CMGroupMemberStateManager) {
                [[CMGroupManager manager] doRemoveGroupAdmin:roomID sid:sID success:^() {
                    [tool ShowAlert:I(@"取消管理员成功！")];
                    [self performSelector:@selector(refreshListA) withObject:nil afterDelay:0.3];
                }];
            }else{
                [[CMGroupManager manager] doSetGroupAdmin:roomID sid:sID success:^() {
                    [tool ShowAlert:I(@"设置管理员成功！")];
                    [self performSelector:@selector(refreshListA) withObject:nil afterDelay:0.3];
                }];
            }
        }
        
    }];
    
    [cell setSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:CMGroupMembersCellHeight];
	return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [self.occupantTableView deselectRowAtIndexPath:indexPath animated:YES];
   
    CMSearchModel *model = [self.members objectAtIndex:indexPath.row];

    NSString *jid = model.jid;
    if (![jid isEqualToString:kXMPPJid]) {
        CMChatViewController * controller = [[CMChatViewController alloc]init];
        
        [controller setHidesBottomBarWhenPushed:YES];
        
        controller.chatType = CMSingleChatType;
        controller.toName = model.name;
        
        controller.toJid = model.jid;
        controller.toUid = model.uid;
        controller.icon = model.icon;
        
        [self.navigationController pushViewController:controller animated:YES];
    }
   
}

- (void)refreshListA{
    //[self doRequestGroupMembers];
    
    //请求群成员列表
    if (self.editType == CMGroupMemberEditTypeTrain) {
        [self doRequestTrainMembers];
    }else
        [self doRequestGroupMembers];
}

//- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
//{
//    return 10.0 ;
//}
//
//- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
//    return [[UIView alloc]initWithFrame:CGRectZero];
//}

#pragma mark -
#pragma mark UITableViewDataDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return CMGroupMembersCellHeight;
}

#pragma mark -
#pragma mark refresh

#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
	
	//  should be calling your tableviews data source model to reload
	//  put here just for demo
	
    //[self doRequestGroupMembers];
    //请求群成员列表
    if (self.editType == CMGroupMemberEditTypeTrain) {
        [self doRequestTrainMembers];
    }else
        [self doRequestGroupMembers];
    
}

- (void)doneLoadingTableViewData{
	
	//  model should call this when its done loading
    [self.occupantTableView.pullToRefreshView refreshLastUpdatedDate];
    [self.occupantTableView.pullToRefreshView stopAnimating];
}

@end
