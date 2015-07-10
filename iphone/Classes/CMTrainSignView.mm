//
//  CMTrainSignView.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainSignView.h"
#import "CMTrainSignTableViewCell.h"
#import "CMTrainDetailSignController.h"

@implementation CMTrainSignView

-(id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame refresh:true];
    if (self) {
        // Initialization code
        
        memset(m_sFlag,0,16);

        if (!m_pUpdataDataListerner) {
            m_pUpdataDataListerner = new CMTrainSignViewUpdateDataListener();
        }
        
        if (!m_pTrainSignList) {
            m_pTrainSignList= new CMTrainSignInList();
        }
        if (!m_pTrainNotSignList) {
            m_pTrainNotSignList = new CMTrainSignInList();
        }
        m_pTrainNotSignList->SetListener(m_pUpdataDataListerner);
        m_pTrainNotSignList->SetUserData((__bridge void*)self);
        
        m_pTrainSignList->SetListener(m_pUpdataDataListerner);
        m_pTrainSignList->SetUserData((__bridge void*)self);
    }
    return self;
}

-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh{
    if (self.flag == 1) {
        if (m_pTrainSignList && m_pUpdataDataListerner) {
            m_pTrainSignList->Cancel();
            if (m_pTrainSignList->RequestTrainApplyList(m_sFlag)) {
                
            }else
                [tableviewlist reloadData];
        }
    }
    if (self.flag == 0) {
        if (m_pTrainNotSignList && m_pUpdataDataListerner) {
            m_pTrainNotSignList->Cancel();
            if (m_pTrainNotSignList->RequestTrainApplyList(m_sFlag)) {
                
            }else
                [tableviewlist reloadData];
        }
    }
}

-(void) refreshTableView{
    if (self.flag ==1 ) {
        if (m_pTrainSignList) {
            m_pTrainSignList->RemoveSuccessItem(selectRow);
            [tableviewlist reloadData];
        }
    }
    if (self.flag ==0 ) {
        if (m_pTrainNotSignList) {
            m_pTrainNotSignList->RemoveSuccessItem(selectRow);
            [tableviewlist reloadData];
        }
    }
}



-(BOOL)RefreshMore
{
    if (self.flag == 1) {
        if([self HasMore])
        {
            return m_pTrainSignList->RequestMore();
        }
    }
    if (self.flag == 0) {
        if([self HasMore])
        {
            return m_pTrainNotSignList->RequestMore();
        }
    }
    return NO;
}

-(void)RefreshList
{
    [self LoadData:m_sFlag refresh:true];
    
    self.isUseCache = NO;
    
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
        if (m_pTrainSignList) {
            if (![self HasMore] || SETTING.GetAutoLoadMore()) {
                return m_pTrainSignList->GetItemCount();
            }
            return m_pTrainSignList->GetItemCount()+1;
        }
    }
    if (self.flag == 0) {
        if (m_pTrainNotSignList) {
            if (![self HasMore] || SETTING.GetAutoLoadMore()) {
                return m_pTrainNotSignList->GetItemCount();
            }
            return m_pTrainNotSignList->GetItemCount()+1;
        }
    }
    
    return 0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSInteger row = indexPath.row;
    selectRow = row;
    
    TTrainSignInItem item;
    if (self.flag == 1) {
        m_pTrainSignList->GetItem(row, item);
    }
    if (self.flag == 0) {
        m_pTrainNotSignList->GetItem(row, item);
    }
    
    CMTrainDetailSignController *trainController = [[CMTrainDetailSignController alloc]init];
    [trainController setInfo:item];
    [trainController setTrainSignView:self];
    
    [[self viewController].navigationController pushViewController:trainController animated:YES];
    CMRELEASE(trainController);
    
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
//    if (!m_pTrainSignList) {
//        return 0;
//    }
//    if ([[NSString stringWithUTF8String:m_sFlag] isEqualToString:@"signin"]) {
//        return 60;
//    }
    return 67;
//    if (self.flag == 1) {
//        return 60;
//    }
//    if (self.flag == 0) {
//        return 75;
//    }
//    return 0;
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int row = indexPath.row;
    
    TTrainSignInItem item;
    if (self.flag == 1) {
        m_pTrainSignList->GetItem(row, item);
        
        //更多
        if (row == m_pTrainSignList->GetItemCount() &&  m_pTrainSignList->GetItemCount()!= 0)
            return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    }
    
    if (self.flag == 0) {
        m_pTrainNotSignList->GetItem(row, item);
        
        //更多
        if (row == m_pTrainNotSignList->GetItemCount() &&  m_pTrainNotSignList->GetItemCount()!= 0)
            return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    }
    
    CMTrainSignTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"mytraincell"];
    if (cell == nil) {
        cell = [[CMTrainSignTableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"mytraincell"];
    }
    [cell setCellInfo:item];
    
    return cell;
    
}

- (void)dealloc{
    if (m_pTrainNotSignList) {
        m_pTrainNotSignList->Cancel();
        m_pTrainNotSignList->SetUserData(NULL);
        SAFEDELETE(m_pTrainNotSignList);
    }
    
    SAFEDELETE(m_pUpdataDataListerner);
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
