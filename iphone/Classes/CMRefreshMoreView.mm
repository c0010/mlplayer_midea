//
//  cmitemcontroller.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMRefreshMoreView.h"
#import "cmsettings.h"
#import "CMNavgateItem.h"
#import "UIScrollView+SVPullToRefresh.h"
#import "UIScrollView+SVInfiniteScrolling.h"


@implementation CMRefreshMoreView

@synthesize HasMore = m_bHasMore;
@synthesize tableviewlist;

#define kCellIdentifier @"com.apple.CMRefreshMoreView.CellIdentifier"

#pragma mark -

-(void)automaticRefresh
{
    [self automaticRefreshUseCache:NO];
}

-(void)clickRefresh{
    if (CMGlobal::TheOne().IsExistNetwork()) {
        [self automaticRefreshUseCache:NO];
    }
}


-(void)automaticRefreshUseCache:(BOOL)useCache
{
    self.isUseCache = useCache;
    
    if (tableviewlist.pullToRefreshView.state != SVPullToRefreshStateLoading) {
        [tableviewlist triggerPullToRefresh];
    }
}

-(void)GetBrowserList
{
    
    [activityView stopAnimating];
    [tableviewlist reloadData];
    [tableviewlist.infiniteScrollingView stopAnimating];
    if(SETTING.GetAutoLoadMore()){
        if (self.HasMore) {
            tableviewlist.showsInfiniteScrolling = YES;
        }
        else {
            tableviewlist.showsInfiniteScrolling = NO;
        }
    }
    if([tableviewlist numberOfRowsInSection:0]==0)
    {
        bgview.hidden=NO;
        
        tableviewlist.separatorStyle =UITableViewCellSeparatorStyleNone;
        
    }
    else
    {
        
        bgview.hidden=YES;
        
    }

    [self doneLoadingTableViewData];
    if ([self HasMore]){
        self.tableviewlist.showsInfiniteScrolling = YES;
    }
}

- (void)stopRefreshingMore{
    if (tableviewlist.showsInfiniteScrolling) {
        tableviewlist.showsInfiniteScrolling = NO;
    }
}

#pragma mark -
#pragma mark View init
-(id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh
{
	self = [super initWithFrame:frame];
	if(self != nil) 
	{
		//init
		m_bHasMore = false;
		btnMore = nil;
		tableviewlist = [[CMTableView alloc] initWithFrame:self.bounds style:UITableViewStylePlain];
		[tableviewlist setDelegate:self];
		[tableviewlist setDataSource:self];
		[tableviewlist setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        tableviewlist.separatorStyle =UITableViewCellSeparatorStyleNone;
		if(brefresh)
		{
            WEAKSELF;
            [tableviewlist addPullToRefreshWithActionHandler:^{
                STRONGSELF;
                sself.isUseCache = NO;
                [sself reloadTableViewDataSource];
                
            }];
		}
   
        bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.bounds.size.width, self.bounds.size.height)];

        [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];


        [tableviewlist addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        CMRELEASE(bgview);
        
        bgview.userInteractionEnabled=YES;
        bgview.hidden = YES;
        [self addSubview:tableviewlist];
        if(SETTING.GetAutoLoadMore()){
            WEAKSELF;
            [tableviewlist addInfiniteScrollingWithActionHandler:^{
                STRONGSELF;
                
                if ([sself RefreshMore] == NO){
                    [sself->tableviewlist.infiniteScrollingView stopAnimating];
                }
            }];
            
            [tableviewlist.infiniteScrollingView setCustomView: [self customViewForRequestMore] forState:SVInfiniteScrollingStateAll];
        }
    }
	return self;
}

- (UIView *)customViewForRequestMore{
    CGRect frame = tableviewlist.infiniteScrollingView.frame;
    UIView *customInfiniteScrollingView = [[UIView alloc] initWithFrame:frame];
    
    UIActivityIndicatorView *activityIndicator= [[UIActivityIndicatorView alloc]init];
    [activityIndicator setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleGray];
    
    activityIndicator.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2, (44-20)/2, 20, 20);
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2+25, (44-20)/2, 150, 20)];
    label.text = I(@"加载更多...");// @"加载更多...";
    label.backgroundColor = [UIColor clearColor];
    customInfiniteScrollingView.backgroundColor = [UIColor clearColor];
    [customInfiniteScrollingView addSubview:activityIndicator];
    [customInfiniteScrollingView addSubview:label];
    
    [activityIndicator startAnimating];
    
    return customInfiniteScrollingView;
}


#pragma mark -
#pragma mark Table view 

-(void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {

	return 0;
}
// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
	UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	
	if (cell == nil) {
# if ! __has_feature(objc_arc)
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] autorelease];
# else
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
# endif
	}

    if(!SETTING.GetAutoLoadMore()){
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
        UILabel *lbl_LoadMore = [[UILabel alloc]init];
        
        CGSize size_LoadMore =[I(@"加载更多...") sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(NSIntegerMax, cell.contentView.frame.size.height) lineBreakMode:NSLineBreakByTruncatingTail];
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

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	return 30;
} 

#pragma mark -
#pragma mark refresh

#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
	
	//  should be calling your tableviews data source model to reload
	//  put here just for demo
    self.tableviewlist.showsInfiniteScrolling = NO;
	self.HasMore = false;
	//[tableviewlist reloadData];
	[self performSelectorOnMainThread:@selector(RefreshList) withObject:self waitUntilDone:NO];
}

- (void)doneLoadingTableViewData{
	
	//  model should call this when its done loading
    [tableviewlist.pullToRefreshView refreshLastUpdatedDate];
    [tableviewlist.pullToRefreshView stopAnimating];
}


-(void)RershTableList
{
    activityView = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    activityView.frame = CGRectMake(80.0, 15.0, 10.0, 10.0);
    [btnMore addSubview:activityView];
    [activityView startAnimating];
	[self RefreshMore];	
}
-(void)RefreshList
{

}
-(BOOL)RefreshMore
{
}

- (void)dealloc {
	
	CMRELEASE(tableviewlist);
    CMRELEASE(activityView);
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

@end