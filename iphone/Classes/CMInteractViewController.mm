//  互动首页

#import "CMInteractViewController.h"
#import "cmsettings.h"
#import "CMImage.h"
#import "CMTableViewCell.h"
#import "tool.h"
#import "cmglobal.h"
#include "cmmyinfo.h"
#import "CMGroupInfoExitViewController.h"
#import "CMInteractCell.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "NSDate+Helper.h"
#import "CMGroupManager.h"
#import "CMMsgManager.h"
#import "UITableViewCell+Helpper.h"
#import "CMSegmentedControl.h"
#import "CMSysMessageDetailyViewController.h"
#import "qa_ChoiceList.h"
#import "CMContactManager.h"
#import "CMParseXmppMessage.h"
#import "CMSearchModel.h"
#import "CMCoreDataUtils.h"
#import "CMTrainInfoViewController.h"
#import "UIScrollView+SVPullToRefresh.h"

#define kCellIdentifier @"com.apple.CMAddressControl.CellIdentifier"

@implementation CMInteractViewController
@synthesize theTableView;
@synthesize interactState;

- (instancetype)init
{
    self = [super init]; 
    if (self) {
        
    }
    return self;
}

- (id)initWithTBrowserItem:(TBrowserItem *)startitem{
    self = [super init];
    if (self) {
        currItem = startitem;
    }
    return self;
}

- (id)initWithTQaItem:(TQAItem *)startitem{
    self = [super init];
    if (self) {
        currQaItem = new TQAItem();
        currQaItem = startitem;
    }
    return self;
}

-(void)loadTableList
{
    [tool DisimissActivityIndicator];
    [self.searchDisplayController.searchResultsTableView reloadData];
}

- (void)loadGroupList{
	
    if (self.interactState == CMInteractStateMessage) {
        return;
    }
   
    [tool DisimissActivityIndicator];
    [self.searchDisplayController.searchResultsTableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationNone];
}

- (void)segmentedTempPressed:(NSInteger )segmentedControlIndex{
    
    _fetchedResultsController = nil;
    
    [self.theTableView setContentOffset:CGPointMake(0, 0)];
    
    switch (segmentedControlIndex) {
        case 0:
        {
            placeholder.image = [UIImage imageNamed:@"interact_bg_single"];
            
            [self removePullRefreshView];
            
           //消息
            self.interactState = CMInteractStateMessage;
            [self.theTableView reloadData];
            //[self.theTableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
        }
            break;
        case 1:
        {
            placeholder.image = [UIImage imageNamed:@"interact_bg_group"];

            [self addPullRefreshView];
            
           //群组
            self.interactState = CMInteractStateGroup;
            [self.theTableView reloadData];
            //[self.theTableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
        }
            break;
        default:
            break;
    }
}

-(void)gotoBack
{
    if (currItem || currQaItem) {
        if (_isPlayAndNewsPush) {
            [self.navigationController popViewControllerAnimated:YES];
        }
        else
            [self.navigationController dismissModalViewControllerAnimated:YES];
    }
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)gotoTop{

    [self.theTableView setContentOffset:CGPointMake(0, 0) animated:YES];

}

- (void)viewDidLoad {
    [super viewDidLoad];
    

    
    CGRect f = [self.view bounds];

	f.size.height = UI_IOS_WINDOW_HEIGHT - 64 - 49;
    
    if (!currItem && !currQaItem) {
//        self.navigationItem.leftBarButtonItem = nil;
        
        UIButton *rightBtn = [[UIButton alloc]initWithFrame:CGRectMake(0, 10, kBarItemWidth, 24)];
        [rightBtn setImageEdgeInsets:UIEdgeInsetsMake(0, 15, 0, 0)];
        [rightBtn setImage:[UIImage imageNamed:@"interact_add_group"] forState:UIControlStateNormal];
        [rightBtn addTarget:self action:@selector(gotoAddGroupPage) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem * rightBtnItem = [[UIBarButtonItem alloc]initWithCustomView:rightBtn];
        
        self.navigationItem.rightBarButtonItem=rightBtnItem;
    }else{
        f.size.height = UI_IOS_WINDOW_HEIGHT - 64;
    }
    
    WEAKSELF;
    self.navigationItem.titleView = [[CMSegmentedControl alloc]initWithFrame:CGRectMake(0, 0, 140, 30)
                                                                   leftTitle:I(@"消息")
                                                                  rightTitle:I(@"群组")
                                                            didSelectedIndex:^(NSInteger index) {
                                                                STRONGSELF;
                                                                [sself segmentedTempPressed:index];
                                                            }];;

    if(m_pContacts == nil)
	{
		m_pContacts =new CMContacts(NULL);
		m_pContacts->SetUserData(NULL);
	}
    
    if (!contactManager) {
        contactManager = [CMContactManager manager];
    }
    
    self.interactState = CMInteractStateMessage;
    
    self.searchBar = [[CMSearchBar alloc] initWithFrame:CGRectZero];
    self.searchBar.delegate = self;
    
    self.strongSearchDisplayController = [[CMSearchDisplayController alloc] initWithSearchBar:self.searchBar contentsController:self];
    self.strongSearchDisplayController.cmDelegate = self;
    self.strongSearchDisplayController.searchResultsDataSource = self;
    self.strongSearchDisplayController.searchResultsDelegate = self;
    self.strongSearchDisplayController.navigationController = self.navigationController;

    self.theTableView = [[UITableView alloc] initWithFrame:f style:UITableViewStylePlain];
    self.theTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.theTableView.backgroundColor = [UIColor clearColor];
    self.theTableView.showsHorizontalScrollIndicator = NO;
    self.theTableView.showsVerticalScrollIndicator = NO;
	self.theTableView.tableHeaderView = self.searchBar;
    self.theTableView.dataSource = self;
    self.theTableView.delegate = self;

    [self.view addSubview:self.theTableView];
    
    //添加下拉刷新
//    [self addPullRefreshView];
    
    bgview = [[UIView alloc] initWithFrame:self.view.bounds];
    placeholder = [[UIImageView alloc] initWithFrame:CGRectMake(40, 104, 240, 152)];
    placeholder.image = [UIImage imageNamed:@"interact_bg_single"];
    [bgview addSubview:placeholder];//[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
    [bgview setBackgroundColor:[UIColor clearColor]];
    bgview.userInteractionEnabled=NO;
    bgview.hidden = YES;
    [self.theTableView addSubview:bgview];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshGroupList) name:RefreshGroupListNSNotification object:nil];

}

- (void)addPullRefreshView{

    WEAKSELF;
    [self.theTableView addPullToRefreshWithActionHandler:^{
        STRONGSELF;
        [sself reloadTableViewDataSource];
    }];
    self.theTableView.showsPullToRefresh = YES;
}

- (void)removePullRefreshView{
    [self doneLoadingTableViewData];
    self.theTableView.showsPullToRefresh = NO;
}

- (void)CMSearchDisplayControllerWillBeginSearch:(UISearchDisplayController *)controller
{
    self.isShowChat = YES;
    self.searchBar.placeholder = I(@"想搜“张三”输入“zs”试试");
    
    self.tabBarController.tabBar.hidden = YES;
}

- (void)CMSearchDisplayControllerWillEndSearch:(UISearchDisplayController *)controller
{
    self.tabBarController.tabBar.hidden = NO;

    self.isShowChat = NO;
    self.searchBar.placeholder = I(@"搜索");
}

-(void)gotoAddGroupPage
{
    NSArray *menuItems=
    @[
      [qa_ChoiceListItem menuItem:I(@"创建群组")
                            image:nil
                           target:self
                           action:@selector(gotoCreateGroupVC)],
      
      [qa_ChoiceListItem menuItem:I(@"查找群组")
                            image:nil
                           target:self
                           action:@selector(gotoAddGroupVC)],
      ];
    
    CGRect frame = CGRectMake(280.0, 0.0, 30, 62.0);
    [qa_ChoiceList showMenuInView:self.navigationController.view
                         fromRect:frame
                        menuItems:menuItems
                        transform:self.view.transform];
}

- (void)gotoAddGroupVC{
    CMFindgroupViewController * controller = [[CMFindgroupViewController alloc]init];
    [controller setHidesBottomBarWhenPushed:YES];

    controller.title = I(@"查找群组");
    [self.navigationController pushViewController:controller animated:YES];
}

- (void)gotoCreateGroupVC{
    CMNewGroupViewController *controller = [[CMNewGroupViewController alloc]init];
    controller.title = I(@"创建群组");
    [controller setHidesBottomBarWhenPushed:YES];

    [self.navigationController pushViewController:controller animated:YES];
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
    SAFEDELETE(m_pContacts);
    SAFEDELETE(currQaItem);
}

#pragma mark - Lifecycle

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

	// Set the navbar style to its default color for the list view.
	self.navigationController.navigationBar.barStyle = UIBarStyleDefault;
   
    [CMCoreDataUtils updateBadgeValueWithTabBar:self.navigationController.tabBarItem];
    
    if (self.isShowChat) {
        self.tabBarController.tabBar.hidden = YES;
       // if(__iOS7)[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault];
    }else{
       // if(__iOS7)[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
        self.tabBarController.tabBar.hidden = NO;
    }
}

-(void)viewWillDisappear:(BOOL)animated
{
    
//    if (self.isShowChat) {
//        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
//    }
    
    [self.searchBar resignFirstResponder];
    
    [super viewWillDisappear:animated];
}

-(void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
}

#pragma mark - UISearchBar
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    
    searchKey = searchText;
    
    WEAKSELF;
    [contactManager doQuickSearch:searchText success:^(CMContacts *contacts) {
        STRONGSELF;
        [sself doSearchList:contacts searchText:searchText];
    }];
}

- (void)doSearchList:(CMContacts *)contacts searchText:searchtext
{
    m_pContacts = contacts;
    
    self.searchResults = [NSMutableArray array];
    
    for (int i= 0; i < m_pContacts->GetItemCount(); i++) {
        TContactsItem item;
        if(m_pContacts && m_pContacts->GetItem(i, item)){
            
            [self.searchResults addObject:[[CMSearchModel model] toCModel:item index:i]];
        }
    }
    
    self.searchGroups = [CMCoreDataUtils filterGroupCacheWithKeyword:searchtext];
    //添加群组搜索结果
    [self.searchResults addObjectsFromArray:[CMCoreDataUtils packageSearchModel:self.searchGroups]];
    
    //在结果中按名称长度升序排序
    [self.searchResults sortUsingComparator:^NSComparisonResult(CMSearchModel* obj1, CMSearchModel* obj2) {
        
        if (obj1.name.length > obj2.name.length) {
            return NSOrderedDescending;
        }else if (obj1.name.length < obj2.name.length){
            return NSOrderedAscending;
        }
        else
            return NSOrderedSame;
    }];
    
    [self loadTableList];

}

-(void)RershTableList
{
    WEAKSELF;
    [contactManager doQuickSearchMore:searchKey success:^(CMContacts *contacts) {
        STRONGSELF;
        [sself doSearchList:contacts searchText:searchKey];
        
    }];
}

//加载更多
-(void)RershTableList:(UITableViewCell*)cell
{
    
    if(!m_pContacts || m_pContacts->IsEnd())
        return;
    
    if (!SETTING.GetAutoLoadMore()) {
        [btnMore setHidden:YES];
    }
    
    UIActivityIndicatorView* dwActiveView = (UIActivityIndicatorView*)[cell viewWithTag:80001];
    UILabel * lblview = (UILabel*)[cell viewWithTag:80002];
    if(dwActiveView){
        [dwActiveView removeFromSuperview];
    }
    if (lblview) {
        [lblview removeFromSuperview];
    }
    
    dwActiveView = [[UIActivityIndicatorView alloc]init];
    [dwActiveView setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleGray];
    
    dwActiveView.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2, (44-20)/2, 20, 20);
    
    lblview = [[UILabel alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-145)/2+25, (44-20)/2, 150, 20)];
    lblview.text = I(@"加载更多...");// @"加载更多...";
    lblview.backgroundColor = [UIColor clearColor];
    cell.backgroundColor = [UIColor clearColor];
    [dwActiveView setTag:80001];
    [lblview setTag:80002];
    [cell.contentView addSubview:dwActiveView];
    [cell.contentView addSubview:lblview];
    CMRELEASE(lblview);
    CMRELEASE(dwActiveView);
    
    [dwActiveView startAnimating];

    WEAKSELF;
    [contactManager doQuickSearchMore:searchKey success:^(CMContacts *contacts) {
        STRONGSELF;
        [sself doSearchList:contacts searchText:searchKey];
        
    }];
    
}


#pragma mark UITableView delegate methods
// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.theTableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if(tableView == self.theTableView){
        
        if (self.interactState == CMInteractStateMessage) {
            CMDialogueItem* dialogueItem = [self.fetchedResultsController objectAtIndexPath:indexPath];
            
            if (dialogueItem.flag == 1) {
                //培训班交流区房间
                if ([dialogueItem.roomJID rangeOfString:@"@train"].location != NSNotFound) {

                    CMTrainInfoViewController *trainControl = [[CMTrainInfoViewController alloc]init];
                    trainControl.trainID=[[dialogueItem.roomJID componentsSeparatedByString:@"@"] objectAtIndex:0];
                    trainControl.isChatEnter = YES;
                    trainControl.draft = dialogueItem.draft;
                    if (currItem || currQaItem) {
                        if(currItem)
                            trainControl->currItem = currItem;
                        else if(currQaItem)
                            trainControl->currQaItem = currQaItem;
                    }
                    [trainControl setHidesBottomBarWhenPushed:YES];

                    [self.navigationController pushViewController:trainControl animated:YES];
                    
                    
                }//普通群房间
                else {
                    
                    //消息 从历史进入群组
                    CMChatViewController * controller;
                    if (currItem || currQaItem) {
                        if(currItem)
                            controller = [[CMChatViewController alloc]initWithTBrowserItem:currItem];
                        else if(currQaItem)
                            controller=[[CMChatViewController alloc]initWithTQaItem:currQaItem];
                    }else{
                        controller = [[CMChatViewController alloc]init];
                    }
                    [controller setHidesBottomBarWhenPushed:YES];
                    controller.chatType = CMGroupChatType;
                    controller.toJid = dialogueItem.roomJID;
                    controller.toUid = dialogueItem.roomID;
                    controller.toName = dialogueItem.roomName;
                    controller.draft = dialogueItem.draft;
                    [self.navigationController pushViewController:controller animated:YES];
                    
                }
    
            }else{
                //系统消息
                if ([dialogueItem.fromJID isEqualToString:kXMPPManager]) {
                    CMSysMessageViewController * controller = [[CMSysMessageViewController alloc]init];
                    [controller setHidesBottomBarWhenPushed:YES];
                    controller.sysDialogueItem = dialogueItem;
                    [self.navigationController pushViewController:controller animated:YES];
                }else{
                    //消息 从历史进入单聊
                    CMChatViewController * controller;
                    if (currItem || currQaItem) {
                        if(currItem)
                            controller = [[CMChatViewController alloc]initWithTBrowserItem:currItem];
                        else if(currQaItem)
                            controller=[[CMChatViewController alloc]initWithTQaItem:currQaItem];
                    }else{
                        controller = [[CMChatViewController alloc]init];
                    }
                    [controller setHidesBottomBarWhenPushed:YES];
                    
                    controller.chatType = CMSingleChatType;
                    controller.toName = dialogueItem.fromName;
                    controller.toJid = dialogueItem.fromJID;
                    controller.toUid = dialogueItem.fromID;
                    controller.icon = dialogueItem.icon;
                    controller.draft = dialogueItem.draft;

                    [self.navigationController pushViewController:controller animated:YES];
                }
            }
        }else if (self.interactState == CMInteractStateGroup){
            //群组，进入群聊
            CMGroupItem* groupItem = [self.fetchedResultsController objectAtIndexPath:indexPath];
            
            CMChatViewController * controller;
            if (currItem || currQaItem) {
                if(currItem)
                    controller = [[CMChatViewController alloc]initWithTBrowserItem:currItem];
                else if(currQaItem)
                    controller=[[CMChatViewController alloc]initWithTQaItem:currQaItem];
            }else{
                controller = [[CMChatViewController alloc]init];
            }
            [controller setHidesBottomBarWhenPushed:YES];
            controller.chatType = CMGroupChatType;
            
            controller.toUid = groupItem.roomID;
            controller.toJid = groupItem.roomJID;
            controller.toName = groupItem.roomName;
            
            CMDialogueItem *dialogueItem = (CMDialogueItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMDialogueItem class]) withPredicate:Pre_RoomJid(groupItem.roomID)];
            
            if ( dialogueItem ) {
                
                controller.draft = dialogueItem.draft;
            }

            self.navigationController.navigationBar.translucent = NO;
            
            [self.navigationController pushViewController:controller animated:YES];
        }
        
    }else if(tableView == self.strongSearchDisplayController.searchResultsTableView){
        
        CMSearchModel *model =(CMSearchModel *) [self.searchResults objectAtIndex:indexPath.row];
        if (model.type == 0) {
            TContactsItem item ;
            
            if(m_pContacts && m_pContacts->GetItem(model.no, item))
            {
                //加入最近联系人
                m_pContacts->addRecentContact(item);

                //消息 从搜索进入单聊
                NSString *jid = [NSString stringWithUTF8String:item.sJid.c_str()];
                NSString *toName = [NSString stringWithUTF8String:item.sName.c_str()];
                NSString *icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
                NSString *uid = [NSString stringWithUTF8String:item.sID.c_str()];
                
                CMChatViewController * controller;
                if (currItem || currQaItem) {
                    if(currItem)
                        controller = [[CMChatViewController alloc]initWithTBrowserItem:currItem];
                    else if(currQaItem)
                        controller=[[CMChatViewController alloc]initWithTQaItem:currQaItem];
                }else{
                    controller = [[CMChatViewController alloc]init];
                }
                [controller setHidesBottomBarWhenPushed:YES];
                
                controller.chatType = CMSingleChatType;
                controller.toJid = jid;
                controller.toUid = uid;
                controller.icon = icon;
                controller.toName = toName;
                
                NSPredicate *predicate = [NSPredicate predicateWithFormat:@"fromJID == %@", jid];
                CMDialogueItem *dialogueItem = (CMDialogueItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMDialogueItem class]) withPredicate:predicate];
                
                if ( dialogueItem ) {
                    
                    controller.draft = dialogueItem.draft;
                }
                
                self.navigationController.navigationBar.translucent = NO;
                [self.navigationController pushViewController:controller animated:YES];
            }
        }else if(model.type == 1){
            //群组，进入群聊
            CMGroupItem* groupItem = [self.searchGroups objectAtIndex:model.no];
            
            CMChatViewController * controller;
            if (currItem || currQaItem) {
                if(currItem)
                    controller = [[CMChatViewController alloc]initWithTBrowserItem:currItem];
                else if(currQaItem)
                    controller=[[CMChatViewController alloc]initWithTQaItem:currQaItem];
            }else{
                controller = [[CMChatViewController alloc]init];
            }
            [controller setHidesBottomBarWhenPushed:YES];
            controller.chatType = CMGroupChatType;
            
            controller.toUid = groupItem.roomID;
            controller.toJid = groupItem.roomJID;
            controller.toName = groupItem.roomName;
            
            CMDialogueItem *dialogueItem = (CMDialogueItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMDialogueItem class]) withPredicate:Pre_RoomJid(groupItem.roomID)];
            
            if ( dialogueItem ) {
                
                controller.draft = dialogueItem.draft;
            }
            
            self.navigationController.navigationBar.translucent = NO;
            
            [self.navigationController pushViewController:controller animated:YES];
        }
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
    if(tableView == self.strongSearchDisplayController.searchResultsTableView)
    {
        int count = self.searchResults.count;
        if (m_pContacts->IsEnd()) {
            return count;
        }

        return  count + 1;

    }else if(tableView == self.theTableView)
    {
        
        id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:section];
        
        NSInteger count = [sectionInfo numberOfObjects];
        
        bgview.hidden = (count != 0);
        
        return count;
    }
    return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(tableView == self.strongSearchDisplayController.searchResultsTableView)
    {
        if (indexPath.row == self.searchResults.count) {
            return 44;
        }
    }
    
	return CMInteractCellHeight;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{

    CMInteractCell *cell = (CMInteractCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
    
	if (cell == nil) {
        cell = [[CMInteractCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
    [cell setSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[self tableView:tableView heightForRowAtIndexPath:indexPath]];
    
    if (tableView == self.strongSearchDisplayController.searchResultsTableView) {
        
        if (indexPath.row == self.searchResults.count &&  [self.searchResults count]!= 0) {
            cell = [tableView dequeueReusableCellWithIdentifier:@"addressmore"];
            if (cell == nil) {
                cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"addressmore"] ;
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

        
        CMSearchModel *model = [self.searchResults objectAtIndex:indexPath.row];
        
        cell.titleLabel.text =  model.name;
        cell.DescLabel.text = model.desc;
        cell.phoneLabel.text = model.phoneNum;

        [cell.headButton sd_setImageWithURL:[NSURL URLWithString:model.icon] forState:UIControlStateNormal placeholderImage:DefaultBigHeaderImage];
        
        [cell setDoubleCell];
        
        cell.badgeValue = 0;
        cell.timeLabel.hidden = YES;
        
    }else if(tableView == self.theTableView ){
        if (self.interactState == CMInteractStateMessage) {
            CMDialogueItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
            [cell bindDialogueItem:item];
            cell.timeLabel.hidden = NO;
        }else if(self.interactState == CMInteractStateGroup){
            cell.timeLabel.hidden = YES;
            cell.badgeValue = 0;
            cell.draftImgView.hidden = YES;
            CMGroupItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
            cell.titleLabel.text =item.roomName;
            
            [cell.headButton sd_setImageWithURL:[NSURL URLWithString:item.icon] forState:UIControlStateNormal placeholderImage:DefaultGroupImage];

            [cell setSingleCell];
        }
    }
    return cell;
}

- (void)singleTapGestureRecognizerPressed:(UITapGestureRecognizer *)gestureRecognizer{
    
}

//删除最近联系人
-(UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath{
    if (tableView == self.theTableView && self.interactState == CMInteractStateMessage) {
        return UITableViewCellEditingStyleDelete;
    }
    return UITableViewCellEditingStyleNone;
}

-(void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath{//请求数据源提交的插入或删除指定行接收者。
    if (editingStyle ==UITableViewCellEditingStyleDelete) {
        if ((tableView == self.theTableView && self.interactState == CMInteractStateMessage)) {
            CMDialogueItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
            
            [MessageObjectContext deleteObject:item];
            [MessageObjectContext save:NULL];
            
            [CMCoreDataUtils updateBadgeValueWithTabBar:self.navigationController.tabBarItem];
        }
    }
}

#pragma mark -
#pragma mark FetchResultsController
- (NSFetchedResultsController *)fetchedResultsController
{
    if (nil != _fetchedResultsController) {
        return _fetchedResultsController;
    }

    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init] ;

    if (self.interactState == CMInteractStateMessage) {
        NSEntityDescription *entity = [NSEntityDescription entityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];
        [fetchRequest setEntity:entity];
        
        //设定以时间排序
        NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:NO];
        [fetchRequest setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    }else if(self.interactState == CMInteractStateGroup){
        
        NSEntityDescription *entity = [NSEntityDescription entityForName:@"CMGroupItem" inManagedObjectContext:MessageObjectContext];
        [fetchRequest setEntity:entity];
        
        //设定roomName排序
        NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"roomName" ascending:YES];
        [fetchRequest setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    }
   
    NSPredicate *predicate;
    predicate = [NSPredicate predicateWithFormat:nil];

    //分享课件时，过滤系统消息
    if ((currQaItem || currItem) && self.interactState == CMInteractStateMessage ) {
        predicate = [NSPredicate predicateWithFormat:@"fromJID != %@",kXMPPManager];
    }
    //过滤数据
    [fetchRequest setPredicate:predicate];

    _fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:MessageObjectContext sectionNameKeyPath:nil cacheName:nil];
    _fetchedResultsController.delegate = self;

    NSError *error = NULL;
    if (![_fetchedResultsController performFetch:&error]) {
//        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }

    return _fetchedResultsController;
}

#pragma mark -
#pragma mark FetchResultsControllerDelegate
- (void)controllerWillChangeContent:(NSFetchedResultsController *)controller {
    // The fetch controller is about to start sending change notifications, so prepare the table view for updates.
    
//    if (self.isShowChat) {
//        [self.tableView beginUpdates];
//    }
}

- (void)controller:(NSFetchedResultsController *)controller didChangeObject:(id)anObject atIndexPath:(NSIndexPath *)indexPath forChangeType:(NSFetchedResultsChangeType)type newIndexPath:(NSIndexPath *)newIndexPath {
//    if (self.isShowChat) {
//        switch(type) {
//                
//            case NSFetchedResultsChangeInsert:
//                [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:newIndexPath] withRowAnimation:UITableViewRowAnimationFade];
//                break;
//                
//            case NSFetchedResultsChangeDelete:
//                [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
//                break;
//            case NSFetchedResultsChangeUpdate:
//                [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
//                break;
//            default:
//                break;
//        }
//    }
}

- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    // The fetch controller has sent all current change notifications, so tell the table view to process all updates.
//    if (self.isShowChat) {
//       [self.tableView endUpdates];
//    }
    [self.theTableView reloadData];
}


#pragma mark -
#pragma mark refresh

#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
	
	//  should be calling your tableviews data source model to reload
	//  put here just for demo
	
	
    if (self.interactState == CMInteractStateGroup) {
        
        [self refreshGroupList];
        
    }
    
}

- (void)doneLoadingTableViewData{
	
	//  model should call this when its done loading
    [self.theTableView.pullToRefreshView refreshLastUpdatedDate];
    [self.theTableView.pullToRefreshView stopAnimating];
}




- (void)refreshGroupList{
    
    WEAKSELF;
    [[CMGroupManager manager] doRequestMyGroup:^(CMGroup *group) {
        STRONGSELF;
        m_pGroups = group;
   
        for (int i = 0; i < m_pGroups->GetItemCount(); i ++) {
            
            TGroupInfoItem item;
            if (m_pGroups && m_pGroups->GetItem(i,  item)) {
                //缓存
                [CMCoreDataUtils saveGruopCacheFromTGroupInfoItem:item resetJoined:NO];
                
                NSString *roomJid = [NSString stringWithUTF8String:item.sJID.c_str()];
                
                //进入房间
                if ( ![CMCoreDataUtils existManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(roomJid)] ) {
                    
                    [[CMGroupManager managerDelegate] joinWithJid:roomJid withPassword:[NSString stringWithUTF8String:item.sPwd.c_str()]];
                }
            }
        }
        
        [CMCoreDataUtils removeNotExistGroupCache:m_pGroups];
        
        [sself performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.3];
        
    }failure:^(int errorCode) {
        STRONGSELF;
        [tool ShowError:errorCode];
        
        [sself performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.3];

    }];
}

- (void)scrollToTop
{
    if (self.theTableView != nil)
    {
        [self.theTableView setContentOffset:CGPointMake(0, 0) animated:YES];
    }
}

//- (void)stopScrolling
//{
//    if (self.theTableView != nil)
//    {
//        [self.theTableView setContentOffset:CGPointMake(0, 0) animated:YES];
//    }
//}

@end
