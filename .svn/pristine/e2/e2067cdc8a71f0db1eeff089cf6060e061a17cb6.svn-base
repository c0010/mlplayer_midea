//
//  CMInviteNewViewController.m
//  MLPlayer
//
//  Created by kyp on 14-6-18.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMInviteNewViewController.h"
#import "CMGroupMembersCell.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "cmsettings.h"
#import "UITableViewCell+Helpper.h"
#import "CMButton.h"
#import "CMContactManager.h"
#import "CMSearchModel.h"
#import "CMCoreDataUtils.h"
#import "CMGroupManager.h"

#define KInviteCellIdentifier @"com.invite.cell"
#define KInviteBottomCellIdentifier @"com.invite.bottom.cell"

#define kXMPPManager [NSString stringWithUTF8String:SETTING.GetXMPPManager()]

@interface CMInviteNewViewController ()

@end

@implementation CMInviteNewViewController

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

        m_pContacts = new CMContacts(NULL);
        m_pGroupInfoItem = new TGroupInfoItem();

        self.selectedArray = [[NSMutableArray alloc]init];
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.openAutoKeyboard = YES;
    
    UIView *newBak=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20)];
    
    [newBak setBackgroundColor:UIColorRGB(0xe7e7e7)];
    [self.view addSubview:newBak];
    CMRELEASE(newBak);
    
    _isChecked=NO;
    
    self.searchBar=[[CMSearchBar alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-20-44, 320, 40)];
    self.searchBar.delegate=self;
    [self.searchBar setPlaceholder:I(@"搜索")];

    CGRect f = [[self view] bounds];
    //f.origin.y += (48-10);
	f.size.height = UI_IOS_WINDOW_HEIGHT-44-20;
    self.tableView=[[UITableView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-44-20)style:UITableViewStylePlain];
    
    self.tableView.delegate = self;
	self.tableView.dataSource = self;
    [self.tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    self.tableView.backgroundColor = [UIColor clearColor];
    [self.tableView setTableHeaderView:self.searchBar];
    self.tableView.scrollEnabled = YES;
    [self.view addSubview:self.tableView];

    self.bottomView = [[UIView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-20-44-44, UI_IOS_WINDOW_WIDTH, 44)];
    self.bottomView.backgroundColor = UIColorMakeRGBA(238, 238, 238, 0.9);
    self.bottomView.layer.shadowColor=[UIColor grayColor].CGColor;
	self.bottomView.layer.shadowOffset=CGSizeMake(0,-1);
    
    UIView *seqView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 0.5)];
    seqView.backgroundColor = UIColorRGB(0xbbbbbb);
    [self.bottomView addSubview:seqView];
    [self.view addSubview:self.bottomView];

    self.bottomTableView = [[UITableView alloc]initWithFrame:CGRectMake(0, 0, 44, UI_IOS_WINDOW_WIDTH-70)];
    self.bottomTableView.transform = CGAffineTransformMakeRotation(-M_PI / 2);
    self.bottomTableView.delegate = self;
    self.bottomTableView.dataSource = self;
    self.bottomTableView.backgroundColor = [UIColor clearColor];
    self.bottomTableView.showsVerticalScrollIndicator = NO;
    self.bottomTableView.center = CGPointMake((self.bottomView.frame.size.width - 70) / 2, self.bottomView.frame.size.height / 2);
    [self.bottomView addSubview:self.bottomTableView];
    self.bottomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        
    self.commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.commitBtn setTitle:I(@"完成") forState:UIControlStateNormal];
    [self.commitBtn setTitle:I(@"完成") forState:UIControlStateHighlighted];
    [self.commitBtn setFrame:CGRectMake(260, 7, 50, 30)];
    [self.commitBtn setCenterY:CGRectGetHeight(self.bottomView.frame)/2];
    [self.commitBtn setBackgroundImage:[UIImage imageNamed:@"interact_setmanager_btn_normal"] forState:UIControlStateNormal];
    [self.commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_dis"] forState:UIControlStateDisabled];
    [self.commitBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.commitBtn setTitleColor:[UIColor darkGrayColor] forState:UIControlStateDisabled];
    self.commitBtn.titleLabel.font = [UIFont systemFontOfSize:15.f];
    self.commitBtn.enabled = NO;
    [self.commitBtn addTarget:self action:@selector(commitBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.bottomView addSubview:self.commitBtn];
    
    bgview = [[UIView alloc] initWithFrame:self.view.bounds];
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
    [bgview setBackgroundColor:[UIColor clearColor]];
    bgview.userInteractionEnabled=NO;
    bgview.hidden = YES;
    [self.view addSubview:bgview];
    

    [self setRecentContacts];
}


- (void) setRecentContacts{
    
    //一进来显示最近联系人
    m_pContacts->getRecentContacts();

    self.searchResults = [NSMutableArray array];
    
    for (int i= 0; i < m_pContacts->GetItemCount(); i++) {
        TContactsItem item;
        if(m_pContacts && m_pContacts->GetItem(i, item)){

            CMSearchModel *model = [[CMSearchModel model] toCModel:item index:i];

            [self.searchResults addObject:model];
        }
    }
    
    [self refreshView];
    
    //获取群成员，并与最近联系人合并
    if ( !self.occupantsList ) {
        
        self.occupantsList = [NSMutableArray array];

        WEAKSELF;
        //获取群成员
        [[CMContactManager manager] doRequestOccupantsList:[NSString stringWithUTF8String:m_pGroupInfoItem->sID.c_str()] success:^(CMContacts *contact) {
            STRONGSELF;
            for (int i= 0; i < contact->GetItemCount(); i++) {
                TContactsItem item;
                if(m_pContacts && contact->GetItem(i, item)){
                    [sself.occupantsList addObject:[NSString stringWithUTF8String:item.sID.c_str()]];
                }
            }
            
            for (int i= 0; i < sself.searchResults.count; i++) {
                
                CMSearchModel *model = [sself.searchResults objectAtIndex:i];
                if ([sself.occupantsList containsObject:model.uid]) {
                    model.type = -1;
                    
                    [sself.searchResults replaceObjectAtIndex:i withObject:model];
                }
            }
            
            mergeredRecentContacts = sself.searchResults;
            
            [sself refreshView];
        }failure:^(int errorCode) {
            
        }];
        
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    

}

-(void)viewWillDisappear:(BOOL)animated
{
    [self.searchBar resignFirstResponder];
    [super viewWillDisappear:animated];
}

-(void)keyboardWillShow:(NSNotification*)notification{
    NSDictionary* info=[notification userInfo];
    CGSize kbSize=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
    
    [UIView animateWithDuration:0.3 animations:^{
        CGRect navframe = self.bottomView.frame;
        navframe.origin.y = UI_IOS_WINDOW_HEIGHT-20-44-44-kbSize.height;
        self.bottomView.frame = navframe;
    }];
    
}

-(void)keyboardWillHide:(NSNotification *)aNotification
{
    [UIView animateWithDuration:0.3 animations:^{
        CGRect navframe=self.bottomView.frame;
        navframe.origin.y = UI_IOS_WINDOW_HEIGHT-20-44-44;
        self.bottomView.frame=navframe;
    }];
}

-(void)setItem:(TGroupInfoItem&)item
{
    *m_pGroupInfoItem = item;
    
}

- (void)commitBtnPressed:(UIButton *)button{
    
    NSString * tempStr = @"";
    
    //快速枚举遍历所有KEY的值
    for (CMSearchModel *model in self.selectedArray) {
        NSString *str = model.uid;
        tempStr = [tempStr stringByAppendingString:[NSString stringWithFormat:@",%@",str]];
    }
    
    [tool ShowActivityIndicator:self.view];
    
    WEAKSELF;
    [[CMGroupManager manager] doInviteToGroup:[NSString stringWithUTF8String:m_pGroupInfoItem->sID.c_str()] sidarray:tempStr success:^{
        STRONGSELF;
        [tool ShowAlert:I(@"发送成功")];

        [sself.selectedArray removeAllObjects];
         sself.commitBtn.enabled = NO;
        
        [sself.tableView reloadData];

        [sself.bottomTableView reloadData];

    }];
    
}

#pragma mark - UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(tableView==self.tableView){
        
        bgview.hidden = (self.searchResults.count != 0);

        return self.searchResults.count;
    }
    else{
        return self.selectedArray.count;
    }
    
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{

    if(tableView == self.tableView)
    {

        CMGroupMembersCell *cell = [tableView dequeueReusableCellWithIdentifier:KInviteCellIdentifier];
        if (cell == nil) {
            cell = [[CMGroupMembersCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:KInviteCellIdentifier] ;
            
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
        }
        
        CMSearchModel *model = [self.searchResults objectAtIndex:indexPath.row];
        
        BOOL exist = (model.type == -1);
        
        cell.titlelabel.text = model.name;
        cell.cellType = CMGroupMembersCellTypeMemberMark;
        cell.markButton.selected = [self existSelectedWithUid:model.uid];
        cell.markButton.enabled = !exist;
        cell.markButton.tag = indexPath.row;
        [cell.headButton sd_setImageWithURL:[NSURL URLWithString:model.icon] forState:UIControlStateNormal placeholderImage:DefaultHeaderImage];
        [cell.markButton setOnClickListener:^(UIButton *sender){
            sender.selected = ! sender.selected;
            [self ButtonPressed:sender];
        }];
        
        [cell setSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:CMGroupMembersCellHeight];
        return cell;
    }

    else if(tableView == self.bottomTableView)
    {
        UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:KInviteBottomCellIdentifier];

        if (cell == nil) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:KInviteBottomCellIdentifier];
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
        }

        CMButton *btnimgView = [CMButton buttonWithType:UIButtonTypeCustom];
        btnimgView.frame = CGRectMake(7, 10, 30, 30);
        btnimgView.tag = indexPath.row;
        btnimgView.isRound = YES;
        
        WEAKSELF;
        [btnimgView setOnClickListener:^(UIButton *sender){
            STRONGSELF;
            [sself.selectedArray removeObjectAtIndex:sender.tag];
            [sself.bottomTableView reloadData];
            [sself.tableView reloadData];
            
            sself.commitBtn.enabled = (self.selectedArray.count > 0);
        }];

        CMSearchModel *model = [self.selectedArray objectAtIndex:indexPath.row];
        [btnimgView sd_setBackgroundImageWithURL:[NSURL URLWithString:model.icon] forState:UIControlStateNormal placeholderImage:DefaultHeaderImage];
        btnimgView.transform = CGAffineTransformMakeRotation(M_PI / 2);
        [cell.contentView addSubview:btnimgView];
        cell.backgroundColor = [UIColor clearColor];
        return cell;
    }
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMSearchModel *model = [self.searchResults objectAtIndex:indexPath.row];

    if(tableView == self.tableView && model.type != -1){
        CMGroupMembersCell *cell = (CMGroupMembersCell *)[self tableView:tableView cellForRowAtIndexPath:indexPath];
        
        cell.markButton.onClickListener(cell.markButton);
        [tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
    }
}

#pragma mark -
#pragma mark UITableViewDataDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
     if(tableView == self.bottomTableView)
    {
        return 44;

    }
    return CMGroupMembersCellHeight;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section{
    if(tableView == self.tableView)
    {
        return 44;
        
    }
    return 0;
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    if (self.tableView == tableView && self.searchBar.text.length == 0) {
        return 25;
    }
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    
    if (self.tableView == tableView && self.searchBar.text.length == 0) {
        UIView *headView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 25)];
        headView.backgroundColor = UIColorRGB(0xeeeeee);
        
        UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 0, UI_IOS_WINDOW_WIDTH, 25)];
        titleLabel.backgroundColor = [UIColor clearColor];
        titleLabel.font = [UIFont systemFontOfSize:15.f];
        titleLabel.textColor = [UIColor blackColor];
        titleLabel.text = I(@"最近联系人");
        [headView addSubview:titleLabel];
        return headView;
    }
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)refreshView
{
    [self.tableView reloadData];

    [self.bottomTableView reloadData];

    [self.searchDisplayController.searchResultsTableView reloadData];
}


#pragma mark - UITableView data source methods

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{
    //设置是否显示“最近联系人”
    if([searchText isEqualToString:@""]){
        
        
       self.searchResults = mergeredRecentContacts;

        
    }else{

        WEAKSELF;
        [[CMContactManager manager] doQuickSearch:searchText success:^(CMContacts *contacts) {
            STRONGSELF;
            m_pContacts = contacts;
            
            sself.searchResults = [NSMutableArray array];
            
            for (int i= 0; i < m_pContacts->GetItemCount(); i++) {
                TContactsItem item;
                if(m_pContacts && m_pContacts->GetItem(i, item)){
                    
                    CMSearchModel *model = [[CMSearchModel model] toCModel:item index:i];
                    
                    if ([sself.occupantsList containsObject:model.uid]) {
                        model.type = -1;
                    }
                    [sself.searchResults addObject:model];
                }
            }
            
            //在结果中按名称长度升序排序
            [sself.searchResults sortUsingComparator:^NSComparisonResult(CMSearchModel* obj1, CMSearchModel* obj2) {
                
                if (obj1.name.length > obj2.name.length) {
                    return NSOrderedDescending;
                }else if (obj1.name.length < obj2.name.length){
                    return NSOrderedAscending;
                }
                else
                    return NSOrderedSame;
            }];
            
            [sself refreshView];
        }];
    }
    
    [self.tableView reloadData];
    
}
- (void)searchBarCancelButtonClicked:(UISearchBar *) searchBar
{
    [searchBar resignFirstResponder];
}
// called when cancel button pressed
- (void)searchBarResultsListButtonClicked:(UISearchBar *)searchBar
{
    [searchBar resignFirstResponder];
}
- (BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBar
{
    return YES;
}

- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar
{
    searchBar.placeholder = I(@"想搜“张三”输入“zs”试试");

    [searchBar setShowsCancelButton:YES animated:YES];
}

- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar{
    
    searchBar.placeholder = I(@"搜索");

    [searchBar setShowsCancelButton:NO animated:YES];
}

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    [searchBar resignFirstResponder];
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    [self.searchBar resignFirstResponder];
}

#pragma mark - UITableView data source methods
-(void)ButtonPressed:(UIButton *)sender
{
    NSString *icon;
    NSString *currUid;
    NSInteger index= sender.tag;
    
    
    CMSearchModel *model = [self.searchResults objectAtIndex:index];
    icon = model.icon;
    currUid = model.uid;
    
    if(!sender.selected){
        for (int i= 0; i < self.selectedArray.count; i++) {
            CMSearchModel *model = [self.selectedArray objectAtIndex:i];
            if ([currUid isEqualToString:model.uid]) {
                [self.selectedArray removeObject:model];
            }
        }
    }
    else{
        [self.selectedArray addObject:model];
    }
    
    [self.bottomTableView reloadData];
    [self scrollToBottomAnimated:YES];
    
    self.commitBtn.enabled = (self.selectedArray.count > 0);
}

- (BOOL)existSelectedWithUid:(NSString *)uid{
    
    for (CMSearchModel *model in self.selectedArray) {
        if ([model.uid isEqualToString:uid]) {
            return YES;
        }
    }
    return NO;
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.searchBar resignFirstResponder];
}

- (void)scrollToBottomAnimated:(BOOL)animated
{
    NSInteger rows = [self.bottomTableView numberOfRowsInSection:0];
    
    if(rows > 0) {
        [self.bottomTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:rows - 1 inSection:0]
                                      atScrollPosition:UITableViewScrollPositionBottom
                                              animated:animated];
    }
}

@end
