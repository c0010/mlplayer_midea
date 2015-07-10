//
//  CMPushMessageBoxViewController.m
//  MLPlayer
//
//  Created by wangjianbin on 15/6/17.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMPushMessageBoxViewController.h"
#import "CMPushMessageVCTableViewCell.h"
#import "UIScrollView+SVPullToRefresh.h"

#define nPushMessageBoxCellHeight 75

@interface CMPushMessageBoxViewController ()

@end

@implementation CMPushMessageBoxViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = kColorBackground;
    
    UIButton *clearBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [clearBtn setFrame:CGRectMake(0, 0, 44, 44)];
    [clearBtn setTitle:I(@"清空") forState:UIControlStateNormal];
    [clearBtn setTitleColor:kColorButtonTitle forState:UIControlStateNormal];
    [clearBtn setTitleColor:kColorGrayText forState:UIControlStateHighlighted];
    [clearBtn addTarget:self action:@selector(clearUpPushMessage) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *rightBarBtn = [[UIBarButtonItem alloc]initWithCustomView:clearBtn];
    
    self.navigationItem.rightBarButtonItem = rightBarBtn;
    
    if (m_pListener == nil)
    {
        m_pListener = new CMPushMessageBoxListener;
    }
    m_PushMsgInfo = CMPushMsg::GetInstance();
    m_PushMsgInfo->SetListener(m_pListener);
    m_PushMsgInfo->SetUserData(BridgeObjectToC(self));
    
    m_PushMsgInfo->LoadFromDB();
//    int nMsgCount = m_PushMsgInfo->GetItemCount();
    
//    if (nMsgCount * nPushMessageBoxCellHeight < UI_IOS_VC_HEIGHT)
//    {
//        tableViewList = [[CMTableView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, nMsgCount * nPushMessageBoxCellHeight)];
//    }
//    else
//    {
        tableViewList = [[CMTableView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_VC_HEIGHT)];
//    }
    tableViewList.delegate = self;
    tableViewList.dataSource = self;
    tableViewList.backgroundColor = [UIColor whiteColor];
    tableViewList.separatorStyle = UITableViewCellSeparatorStyleNone;
    
    [self.view addSubview:tableViewList];
    
    WEAKSELF;
    [tableViewList addPullToRefreshWithActionHandler:^{
        STRONGSELF;
        [sself reloadTableViewDataSource];
    }];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)clearUpPushMessage
{
    m_PushMsgInfo->SetListener(m_pListener);
    m_PushMsgInfo->SetUserData(BridgeObjectToC(self));
    m_PushMsgInfo->ClearCache();
}

- (void)loadTableViewList
{
    m_PushMsgInfo->SetListener(m_pListener);
    m_PushMsgInfo->SetUserData(BridgeObjectToC(self));
    [tableViewList reloadData];
    [self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.5];
}

- (void)reloadTableViewDataSource
{
    m_PushMsgInfo->SetListener(m_pListener);
    m_PushMsgInfo->SetUserData(BridgeObjectToC(self));
    m_PushMsgInfo->LoadFromDB();
}

- (void)doneLoadingTableViewData{
    
    //  model should call this when its done loading
    [tableViewList.pullToRefreshView refreshLastUpdatedDate];
    [tableViewList.pullToRefreshView stopAnimating];
}

#pragma mark - Table View Delegate And Datasource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return m_PushMsgInfo->GetItemCount();
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return nPushMessageBoxCellHeight;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    return YES;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return UITableViewCellEditingStyleDelete;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
//        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationLeft];
        m_PushMsgInfo->SetListener(m_pListener);
        m_PushMsgInfo->SetUserData(BridgeObjectToC(self));
        m_PushMsgInfo->RemoveItem(indexPath.row);
    }
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMPushMessageVCTableViewCell *cell = (CMPushMessageVCTableViewCell*)[tableView dequeueReusableCellWithIdentifier:@"PushMessageCell"];
    if (cell == nil)
    {
        cell = [[CMPushMessageVCTableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"PushMessageCell"];
        cell.backgroundColor = [UIColor clearColor];
    }
    TPushItem *pushItem = new TPushItem;
    if (m_PushMsgInfo->GetItem(indexPath.row, *pushItem))
    {
        cell.labelTitle.text = NSStringFrom(pushItem->sMsg);
        cell.labelTime.text = NSStringFrom(pushItem->sPubDate);
        if (pushItem->bIsRead)
        {
            cell.imageViewLeftIcon.image = [UIImage imageNamed:@"pushMessage_old"];
            cell.labelTitle.textColor = kColorGrayText;
            cell.labelTime.textColor = kColorGrayText;
        }
        else
        {
            cell.imageViewLeftIcon.image = [UIImage imageNamed:@"pushMessage_new"];
            cell.labelTitle.textColor = [UIColor blackColor];
            cell.labelTime.textColor = [UIColor blackColor];
        }
        
    }
    
    
    
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    TPushItem *pushItem = new TPushItem;
    if (m_PushMsgInfo->GetItem(indexPath.row, *pushItem))
    {
        pushItem->bIsRead = YES;
        m_PushMsgInfo->Update(*pushItem);
        
        m_pNewControl = [[CMGetNewControl alloc] init];
        m_pNewControl.title = I(@"最新推送");
        m_pNewControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        m_pNewControl.navigationController.navigationBarHidden = NO;
        m_pNewControl.tabBarController.tabBar.hidden = YES;
        m_pNewControl.hidesBottomBarWhenPushed = YES;
        m_pNewControl.sType = NSStringFrom(pushItem->sType);
        m_pNewControl.sId   = NSStringFrom(pushItem->sKey);
//        m_pNewControl.bAppStateIsBackground = AppDelegate->_isActive;
        m_pNewControl.view.backgroundColor = [UIColor whiteColor];
        [self.navigationController pushViewController:m_pNewControl animated:YES];
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [tableView reloadData];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
