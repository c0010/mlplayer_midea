//
//  CMTrainListView.m
//  MLPlayer
//
//  Created by hushengwu on 14/11/5.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainListView.h"
#import "CMTrainListTableViewCell.h"
#import "CMTrainInfoViewController.h"
#import "CMTrainContentViewController.h"
#import "CMTrainApplyController.h"
#import "CMBrowserControl.h"


#define kCellIdentifier @"com.apple.CMTRAINVIEW.CellIdentifier"

@implementation CMTrainListView

- (id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:true];
    if (self) {
        // Initialization code
        
        memset(m_sFlag,0,16);

        if(!m_pUpdataDataListerner)
			m_pUpdataDataListerner = new CMTrainListViewUpdateDataListener();
        
        if(!m_pTrainList)
			m_pTrainList = new CMMyTrainList();
        
        m_pTrainList->SetListener(m_pUpdataDataListerner);
        m_pTrainList->SetUserData((__bridge void*)self);
        
        bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.bounds.size.width, self.bounds.size.height)];
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(50, 70, UI_IOS_WINDOW_WIDTH-100, 20)];
        [label setFont:[UIFont systemFontOfSize:16]];
        [label setText:I(@"您还没有加入任何培训班")];
        [label setTextAlignment:NSTextAlignmentCenter];
        [label setTextColor:[UIColor grayColor]];
        [label setBackgroundColor:[UIColor clearColor]];
        [bgview addSubview:label];
        CMRELEASE(label);
        
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        [btn setFrame:CGRectMake(110, 95, 100, 20)];
        [btn setTitle:I(@"现在就去报名") forState: UIControlStateNormal];
        [btn setTitleColor:kColorForeground forState:UIControlStateNormal];
        [btn.titleLabel setFont:[UIFont systemFontOfSize:16]];
        [btn addTarget:self action:@selector(gotoApply:) forControlEvents:UIControlEventTouchUpInside];
        [bgview addSubview:btn];
        
        [tableviewlist addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        CMRELEASE(bgview);
        
        bgview.userInteractionEnabled=YES;
        bgview.hidden = YES;
        
        
    }
    return self;
}

-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh{
    if (m_pTrainList && m_pUpdataDataListerner) {
        m_pTrainList->Cancel();
        m_pTrainList->RequestTrainApplyList();
    }
}



-(void)gotoApply:(id)sender
{
    CMTrainApplyController *applyControl = [[CMTrainApplyController alloc]init];
    applyControl.title = I(@"培训报名");
    [[self viewController].navigationController pushViewController:applyControl animated:YES];
    CMRELEASE(applyControl);
    
}

-(void) refreshTableView{
//    if (m_pTrainList) {
//        //m_pTrainList->RemoveSignUpSuccessTrain(selectRow);
//        [tableviewlist reloadData];
//    }
}



-(BOOL)RefreshMore
{
	if([self HasMore])
	{
        return m_pTrainList->RequestMore();
	}
    return NO;
}

-(void)RefreshList
{
    [self LoadData:m_sFlag refresh:true];
    
    self.isUseCache = NO;
    
}

#pragma mark TableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (m_pTrainList) {
        if (![self HasMore] || SETTING.GetAutoLoadMore()) {
            return m_pTrainList->GetItemCount();
        }
        return m_pTrainList->GetItemCount()+1;
    }
    
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
	int row = indexPath.row;
    
    selectRow = row;
    
    TMyTrainItem item;
    m_pTrainList->GetItem(row, item);
    
    CMTrainInfoViewController *traininfo=[[CMTrainInfoViewController alloc]init];
    traininfo.title = [NSString stringWithUTF8String:item.sTitle.c_str()];
    [traininfo setItem:item];
    [[self viewController].navigationController pushViewController:traininfo animated:YES ];
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (!m_pTrainList) {
        return 0;
    }
    return 65;
    
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int row = indexPath.row;
    
    TMyTrainItem item;
    m_pTrainList->GetItem(row, item);
    
    //更多
	if (row == m_pTrainList->GetItemCount() &&  m_pTrainList->GetItemCount()!= 0)
		return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    CMTrainListTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"mytraincell"];
    if (cell == nil) {
        cell = [[CMTrainListTableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"mytraincell"];
    }
    [cell setcellinfo:item];
    return cell;

}

- (void)dealloc{
    if (m_pTrainList) {
        m_pTrainList->Cancel();
        m_pTrainList->SetUserData(NULL);
        m_pTrainList->SetListener(NULL);
    }
    
    SAFEDELETE(m_pTrainList);

    SAFEDELETE(m_pUpdataDataListerner);
    
}


/**
 *	获取当前view的 viewController
 *
 *	@param	sender
 *	@param	event
 */

- (UIViewController*)viewController {
    for (UIView* next = [self superview]; next; next =
         next.superview) {
        UIResponder* nextResponder = [next nextResponder];
        if ([nextResponder isKindOfClass:[UIViewController
                                          class]] && ![nextResponder isKindOfClass:[CMBrowserControl class]]) {
            return (UIViewController*)nextResponder;
        }
    }
    return nil;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
