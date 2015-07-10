//
//  CMAddressSearchControl.h
//  MLPlayer
//
//  互动首页
//  Created by sunjj on 11-5-12.
//  Copyright 2011 w. All rights reserved.
//
#import <CoreData/CoreData.h>

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmcontacts.h"
#import "CustomBGAlert.h"
#include "cmwebimage.h"
#import "CMChatViewController.h"
#import "CMNewGroupViewController.h"
#import "CMSysMessageViewController.h"
#import "CMGroupViewController.h"
#import "CMInteractModel.h"
#import "CMSearchBar.h"
#import "cmqalist.h"

@class CMContactManager;

enum CMInteractState{
    CMInteractStateMessage = 0,
    CMInteractStateGroup = 1,
};

@interface CMInteractViewController : CMViewController <UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate,UIScrollViewDelegate,NSFetchedResultsControllerDelegate,UISearchBarDelegate,UISearchDisplayDelegate,CMSearchDisplayDelegate>
{

	CMContacts *m_pContacts;

	UITableView* theTableView;

    UIView* bgview;     //无数据logo
    
    UIImageView *placeholder;

    CMGroup *m_pGroups;
    
    UIButton* btnMore;
    
    NSString *searchKey;
    
    CMContactManager *contactManager;   //搜索句柄


@public
    TBrowserItem* currItem;
    
    TQAItem* currQaItem;

}
@property(nonatomic,strong)NSFetchedResultsController* fetchedResultsController;

@property(nonatomic,strong) UITableView *theTableView;
@property (nonatomic,strong) CMSearchBar *searchBar;
@property (nonatomic,strong) CMSearchDisplayController *strongSearchDisplayController;

@property(nonatomic,assign)BOOL isShowChat;

@property (nonatomic,assign) enum CMInteractState interactState;//标记最近联系人，群组

@property(nonatomic,strong) NSMutableArray *searchResults,*searchGroups;

@property(nonatomic,assign) BOOL isPlayAndNewsPush;

- (id)initWithTBrowserItem:(TBrowserItem *)startitem;
- (id)initWithTQaItem:(TQAItem *)startitem;

- (void)scrollToTop;
//- (void)stopScrolling;


@end

