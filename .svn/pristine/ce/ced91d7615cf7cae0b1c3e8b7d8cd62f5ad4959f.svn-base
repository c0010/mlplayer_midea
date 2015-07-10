//
//  CMTrainApplyView.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainApplyView.h"
#import "CMTrainApplyDetailController.h"
@implementation CMTrainApplyView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame refresh:true];
    if (self) {
        // Initialization code
        
        memset(m_sFlag,0,16);
        
        if (!m_pUpdataDataListerner) {
            m_pUpdataDataListerner = new CMTrainApplyViewUpdateDataListener();
        }
        
        if (!m_pTrainApplyList) {
            m_pTrainApplyList = new CMTrainApplyList();
        }
        if (!m_pTrainNotApplyList) {
            m_pTrainNotApplyList = new CMTrainApplyList();
        }
        if (!m_pTrainOverList) {
            m_pTrainOverList = new CMTrainApplyList();
        }
        
        m_pTrainApplyList->SetListener(m_pUpdataDataListerner);
        m_pTrainApplyList->SetUserData((__bridge void*)self);
        
        m_pTrainNotApplyList->SetListener(m_pUpdataDataListerner);
        m_pTrainNotApplyList->SetUserData((__bridge void*)self);
        
        m_pTrainOverList->SetListener(m_pUpdataDataListerner);
        m_pTrainOverList->SetUserData((__bridge void*)self);
        
    }
    return self;
}

-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh{
    if (self.flag == 1) {
        if (m_pTrainApplyList && m_pUpdataDataListerner) {
            m_pTrainApplyList->Cancel();
            if (m_pTrainApplyList->RequestTrainApplyList(m_sFlag)) {
                
            }else
                [tableviewlist reloadData];
            
        }
    }
    if (self.flag == 0) {
        if (m_pTrainNotApplyList && m_pUpdataDataListerner) {
            m_pTrainNotApplyList->Cancel();
            m_pTrainNotApplyList->RequestTrainApplyList(m_sFlag);
        }
    }
    if (self.flag == 2) {
        if (m_pTrainOverList && m_pUpdataDataListerner) {
            m_pTrainOverList->Cancel();
            m_pTrainOverList->RequestTrainApplyList(m_sFlag);
        }
    }
}

-(void) refreshTableView{
    if (self.flag == 1) {
        if (m_pTrainApplyList) {
            m_pTrainApplyList->RemoveSuccessItem(selectRow);
            [tableviewlist reloadData];
        }
    }
    if (self.flag == 0) {
        if (m_pTrainNotApplyList) {
            m_pTrainNotApplyList->RemoveSuccessItem(selectRow);
            [tableviewlist reloadData];
        }
    }
    if (self.flag == 2) {
        if (m_pTrainOverList) {
            m_pTrainOverList->RemoveSuccessItem(selectRow);
            [tableviewlist reloadData];
        }
    }
}




-(BOOL)RefreshMore
{
    if(self.flag == 1)
    {
        if([self HasMore])
        {
            return m_pTrainApplyList->RequestMore();
        }
    }
    if(self.flag == 0)
    {
        if([self HasMore])
        {
            return m_pTrainNotApplyList->RequestMore();
        }
    }
    if(self.flag == 2)
    {
        if([self HasMore])
        {
            return m_pTrainOverList->RequestMore();
        }
    }
    return NO;
}

-(void)RefreshList
{
    [self LoadData:m_sFlag refresh:true];
    
    self.isUseCache = NO;
    
}

- (void)dealloc{
    if (m_pTrainApplyList) {
        m_pTrainApplyList->Cancel();
        m_pTrainApplyList->SetUserData(NULL);
        m_pTrainApplyList->SetListener(NULL);
        SAFEDELETE(m_pTrainApplyList);
    }
    
    if (m_pTrainNotApplyList) {
        m_pTrainNotApplyList->Cancel();
        m_pTrainNotApplyList->SetUserData(NULL);
        m_pTrainNotApplyList->SetListener(NULL);
        SAFEDELETE(m_pTrainNotApplyList);
    }
    
    if (m_pTrainOverList) {
        m_pTrainOverList->Cancel();
        m_pTrainOverList->SetUserData(NULL);
        m_pTrainOverList->SetListener(NULL);
        SAFEDELETE(m_pTrainOverList);
    }
    
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
                                          class]]) {
            return (UIViewController*)nextResponder;
        }
    }
    return nil;
}


#pragma mark TableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (self.flag == 1) {
        if (m_pTrainApplyList) {
            if (![self HasMore] || SETTING.GetAutoLoadMore()) {
                return m_pTrainApplyList->GetItemCount();
            }
            return m_pTrainApplyList->GetItemCount()+1;
        }
    }
    if (self.flag == 0) {
        if (m_pTrainNotApplyList || SETTING.GetAutoLoadMore()) {
            if (![self HasMore]) {
                return m_pTrainNotApplyList->GetItemCount();
            }
            return m_pTrainNotApplyList->GetItemCount()+1;
        }
    }
    if (self.flag == 2) {
        if (m_pTrainOverList) {
            if (![self HasMore] || SETTING.GetAutoLoadMore()) {
                return m_pTrainOverList->GetItemCount();
            }
            return m_pTrainOverList->GetItemCount()+1;
        }
    }
    
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    int row = indexPath.row;
    
    selectRow = row;
    
    TTrainApplyItem item ;
    if (self.flag == 1) {
        m_pTrainApplyList->GetItem(row, item);
    }
    if (self.flag == 0) {
        m_pTrainNotApplyList->GetItem(row, item);
    }
    if (self.flag == 2) {
        m_pTrainOverList->GetItem(row, item);
    }
    
    CMTrainApplyDetailController *detailController = [[CMTrainApplyDetailController alloc]init];
    
    [detailController setInfo:item];
    [detailController setTrainApplyView:self];
    
    [[self viewController].navigationController pushViewController:detailController animated:YES];
    CMRELEASE(detailController);
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    return 67;
//    if (!m_pTrainApplyList) {
//        return 0;
//    }
//    if ([[NSString stringWithUTF8String:m_sFlag] isEqualToString:@"applied"]) {
//        return 57;
//    }
//    return 77;
    
//    if (self.flag == 0 || self.flag == 2) {
//        return 77;
//    }
//    else if (self.flag == 1)
//    {
//        return 57;
//    }
//    return 0;
    
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int row = indexPath.row;
    
    //更多
    TTrainApplyItem item ;
    
    if (self.flag == 1) {
        m_pTrainApplyList->GetItem(row, item);
        
        if (row == m_pTrainApplyList->GetItemCount() &&  m_pTrainApplyList->GetItemCount()!= 0)
            return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    }
    if (self.flag == 0) {
        m_pTrainNotApplyList->GetItem(row, item);
        
        if (row == m_pTrainNotApplyList->GetItemCount() &&  m_pTrainNotApplyList->GetItemCount()!= 0)
            return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    }
    if (self.flag == 2) {
        m_pTrainOverList->GetItem(row, item);
        
        if (row == m_pTrainOverList->GetItemCount() &&  m_pTrainOverList->GetItemCount()!= 0)
            return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    }
    
    CMTrainApplyTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"mytraincell"];
    if (cell == nil) {
        cell = [[CMTrainApplyTableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"mytraincell"];
    }
    [cell setcellinfo: item];
    return cell;
    
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
