//
//  CMTrainSignView.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMRefreshMoreView.h"
#import "cmtrainsigninlist.h"

class CMTrainSignViewUpdateDataListener;
class CMTrainSignInList;

@interface CMTrainSignView : CMRefreshMoreView<UITableViewDelegate,UITableViewDataSource>
{
    CMTrainSignViewUpdateDataListener *m_pUpdataDataListerner;
    
    NSInteger selectRow; //cell当前点击行
    
    
    
    @public
    CMTrainSignInList *m_pTrainSignList;
    
    CMTrainSignInList *m_pTrainNotSignList;
    
    char m_sFlag[16];
}
@property(assign)int flag;
-(void) refreshTableView;
@end

class CMTrainSignViewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMTrainSignView* trainview = (__bridge CMTrainSignView*)UserData;
        
        if (trainview.flag == 1) {
            [trainview setHasMore:!trainview->m_pTrainSignList->IsEnd()];
        }
        if (trainview.flag == 0) {
            [trainview setHasMore:!trainview->m_pTrainNotSignList->IsEnd()];
        }
        
        
        [trainview GetBrowserList];
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
        }
        else{
            [tool ShowError:Result];
        }
        
    }
};