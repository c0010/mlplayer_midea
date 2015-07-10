//
//  CMSysMessageViewController.m
//  MLPlayer
//系统消息界面

//  Created by 王浩沣 on 14-6-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMSysMessageViewController.h"
#import "CMSysMessageDetailyViewController.h"
#import "CMGroupManager.h"
#import "CMAlertView.h"
#import "UITableViewCell+Helpper.h"
#import "CMInteractViewController.h"
#import "CMCoreDataUtils.h"

@implementation CMSysMessageViewController
@synthesize theTableView;

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.titleLabel.text = I(@"系统信息");
    
    removeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    removeButton.frame = CGRectMake(0, 0, 40, 44);
    [removeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [removeButton setTitleColor:[UIColor blackColor] forState:UIControlStateHighlighted];
    [removeButton setTitleColor:[UIColor colorWithWhite:0.8 alpha:1.0] forState:UIControlStateDisabled];
    removeButton.titleLabel.font = [UIFont boldSystemFontOfSize:18.f];
    [removeButton setTitle:I(@"清空") forState:UIControlStateNormal];
    [removeButton addTarget:self action:@selector(removeButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:removeButton];
    self.navigationItem.rightBarButtonItem = rightItem;
    
    self.theTableView.backgroundColor= UIColorRGB(0xf5f5f5);
	self.view.backgroundColor=UIColorRGB(0xf5f5f5);
	
	theTableView = [[UITableView alloc] initWithFrame:CGRectMake(10, 0, UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT - 64) style:UITableViewStylePlain];
	theTableView.backgroundColor=UIColorRGB(0xf5f5f5);
	[theTableView setDelegate:self];
	[theTableView setDataSource:self];
    theTableView.showsVerticalScrollIndicator = NO;
    [theTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    theTableView.backgroundColor = [UIColor clearColor];
    
    bgview = [[UIView alloc] initWithFrame:self.view.bounds];
    [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
    [bgview setBackgroundColor:[UIColor clearColor]];
    bgview.userInteractionEnabled=NO;
    bgview.hidden = YES;
    
	[self.view addSubview:theTableView];
    [self.view  addSubview:bgview];

    // Uncomment the following line to preserve selection between presentations.
    
    if (self.sysDialogueItem.unread > 0) {
        self.sysDialogueItem.unread = 0;
        NSError *error = NULL;
        [MessageObjectContext save:&error];
    }
    
    m_TGroupInfoItem = new TGroupInfoItem();
    
    if(!m_pEnterListener)
        m_pEnterListener=new CMEnterGroupSysMessageListener();
    
    m_TGroupInfoItem->SetUserData((__bridge void *)self);
    m_TGroupInfoItem->SetListener(m_pEnterListener, NULL);
}

- (void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
}

- (void) removeButtonPressed:(UIButton *)button{
   
    id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:0];
    for (CMMessageItem *item in [sectionInfo objects]) {
        [MessageObjectContext deleteObject:item];
    }
    [MessageObjectContext deleteObject:self.sysDialogueItem];
    [MessageObjectContext save:NULL];
    
    [self.theTableView reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section{
    return 60;
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMMessageItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];

    CMSysMessageCell *cell = (CMSysMessageCell *)[self tableView:tableView cellForRowAtIndexPath:indexPath];

	return [cell getCellHeight:item];
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    return 10 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:section];

	NSInteger count = [sectionInfo numberOfObjects];
    bgview.hidden = (count != 0);
    return count;

}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMSysMessageCell *cell = (CMSysMessageCell*)[tableView dequeueReusableCellWithIdentifier:kSysMessageCell];
    
	if (cell == nil) {
        cell = [[CMSysMessageCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kSysMessageCell];
    }

    CMMessageItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
    
    cell.agreeButton.tag = indexPath.row;
    cell.cellDelegate=self;
    
    [cell setItem:item];
    
    [cell setSubViewsFrame:item.content];
    
    [cell setRoundSection:[self tableView:self.theTableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[cell getCellHeight:item]];

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    CMMessageItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
    m_TGroupInfoItem->sID = [item.sysmessage.roomID UTF8String];

    if (item.type == CMInteractSystemMessageTypeApply || item.type == CMInteractSystemMessageTypeInvite) {
        
        //没有处理的交互消息
        if (item.sysmessage.state == 0) {
            
            CMSysMessageDetailyViewController *controller = [[CMSysMessageDetailyViewController alloc]init];
            controller.currMessageItem = item;
            [controller setButtonListener:^(UIButton *sender){
                switch (sender.tag) {
                    case 1:
                    {
                        //同意
                        if (item.type == CMInteractSystemMessageTypeApply) {
                            //需要验证加群
                            
                            [[CMGroupManager manager] doAcceptUserApply:item.sysmessage.roomID sid:item.sysmessage.rawSenderID success:^{
                                
                                questIndex = indexPath.row;
                                [self updateSysState:item state:CMSysMessageStateAgree];
                            } failure:^(int errorCode) {
                                ;
                            }];
                            
                            
                        }else{
                            //被邀请加群
                            [[CMGroupManager manager] doRequestEnterGroup:item.sysmessage.roomID key:item.sysmessage.key success:^{
                                
                                questIndex = indexPath.row;
                                [self updateSysState:item state:CMSysMessageStateAgree];
                                
                                //管理员邀请，同意入群，刷新list列表
                                [[NSNotificationCenter defaultCenter] postNotificationName:RefreshGroupListNSNotification object:nil];
                            } failure:^(int errorCode) {
                                
                                if (errorCode  == TResult::EGroupInexistence) {
                                    
                                    [tool ShowAlert:I(@"该群组已解散")];
                                }else{
                                    
                                    [tool ShowError:errorCode];
                                }
                            }];
                        }
                    }
                        break;
                    case 2:
                    {
                        
                        
                        if (item.type == CMInteractSystemMessageTypeApply) {
                            
                            //需要验证 加群拒绝
                            [[CMGroupManager manager] doRefuseUserApply:item.sysmessage.roomID sid:item.sysmessage.rawSenderID success:^{
                                
                                questIndex = indexPath.row;
                                [self updateSysState:item state:CMSysMessageStateRefuse];
                            }];
                        }else{
                            //被邀请加群，拒绝不作处理
                            [self updateSysState:item state:CMSysMessageStateRefuse];
                        }
                    }
                        break;
                    default:
                        break;
                }
            }];
            [self.navigationController pushViewController:controller animated:YES];
            
        }
    }
}

//更新操作状态，1同意/2拒绝
- (void)updateSysState:(CMMessageItem *)item state:(enum CMSysMessageState)state{
    NSError *error = NULL;
    
    CMSysMessageItem *sys = item.sysmessage;
    sys.state = state;
    item.sysmessage = sys;
    [MessageObjectContext save:&error];
}

#pragma CMSysMessageCellDelegate

- (void) CMSysMessageCell:(CMSysMessageCell *)sysMessageCell didSelectedAtIndex:(NSInteger)row{
    CMMessageItem* item = [self.fetchedResultsController objectAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0]];
    
    m_TGroupInfoItem->sID = [item.sysmessage.roomID UTF8String];
    
    switch (item.type) {
        case CMInteractSystemMessageTypeInvite:
        {
            
            sysMessageCell.agreeButton.enabled = NO;

            [[CMGroupManager manager] doRequestEnterGroup:item.sysmessage.roomID key:nil success:^{
                
                questIndex = row;
                [self updateSysState:item state:CMSysMessageStateAgree];
                
                [CMCoreDataUtils saveGruopCacheFromSystemMessage:item.sysmessage];
                [[CMGroupManager managerDelegate] joinWithJid:item.sysmessage.roomJID withPassword:item.sysmessage.password isNewAdd:YES];
            } failure:^(int errorCode) {
                
                sysMessageCell.agreeButton.enabled = YES;

                if (errorCode  == TResult::EGroupInexistence) {
                    
                    [tool ShowAlert:I(@"该群组已解散")];
                }else{
                    
                    [tool ShowError:errorCode];
                }
            }];

        }
            break;
        case CMInteractSystemMessageTypeApply:
        {
            
            sysMessageCell.agreeButton.enabled = NO;

            [[CMGroupManager manager] doAcceptUserApply:item.sysmessage.roomID sid:item.sysmessage.rawSenderID success:^{
                
                questIndex = row;
                [self updateSysState:item state:CMSysMessageStateAgree];
            } failure:^(int errorCode) {
                
                sysMessageCell.agreeButton.enabled = YES;
                
            }];

        }
            break;
        default:
            break;
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
    NSEntityDescription *entity = [NSEntityDescription entityForName:@"CMMessageItem" inManagedObjectContext:MessageObjectContext];
    [fetchRequest setEntity:entity];

    //设定以时间排序
    NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:NO];
    [fetchRequest setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];

    //过滤数据
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@" (fromJID == %@ ) AND (SELF.sysmessage.skip == 0)",kXMPPManager];
    [fetchRequest setPredicate:predicate];
    [fetchRequest setFetchBatchSize:CacheMaxForSystemChatCount];

    _fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:MessageObjectContext sectionNameKeyPath:nil cacheName:nil];

    _fetchedResultsController.delegate = self;

    NSError *error = NULL;
    if (![_fetchedResultsController performFetch:&error]) {
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }

    return _fetchedResultsController;
}

- (void)joinRoom{
    CMMessageItem* item = [self.fetchedResultsController objectAtIndexPath:[NSIndexPath indexPathForRow:questIndex inSection:0]];

    //管理员邀请入群，缓存
    if (item.type == CMInteractSystemMessageTypeInvite) {
        [CMCoreDataUtils saveGruopCacheFromSystemMessage:item.sysmessage];
    }

}


#pragma mark -
#pragma mark FetchResultsControllerDelegate
- (void)controllerWillChangeContent:(NSFetchedResultsController *)controller {
    // The fetch controller is about to start sending change notifications, so prepare the table view for updates.
    [self.theTableView beginUpdates];
}

- (void)controller:(NSFetchedResultsController *)controller didChangeObject:(id)anObject atIndexPath:(NSIndexPath *)indexPath forChangeType:(NSFetchedResultsChangeType)type newIndexPath:(NSIndexPath *)newIndexPath {
    switch(type) {
            
        case NSFetchedResultsChangeInsert:
            [self.theTableView insertRowsAtIndexPaths:[NSArray arrayWithObject:newIndexPath] withRowAnimation:UITableViewRowAnimationFade];
            break;
        case NSFetchedResultsChangeDelete:
            [self.theTableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
            break;
        case NSFetchedResultsChangeUpdate:
            [self.theTableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
            break;
        default:
            break;
    }
}

- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {

    // The fetch controller has sent all current change notifications, so tell the table view to process all updates.
    [self.theTableView endUpdates];
}

- (void)dealloc{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    _fetchedResultsController.delegate = nil;
}
@end
