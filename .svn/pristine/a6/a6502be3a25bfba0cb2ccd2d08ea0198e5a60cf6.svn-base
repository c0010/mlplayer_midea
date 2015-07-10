//
//  CMTrainApplyView.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMRefreshMoreView.h"
#import "CMTrainApplyTableViewCell.h"

class CMTrainApplyViewUpdateDataListener;

@interface CMTrainApplyView : CMRefreshMoreView<UITableViewDataSource, UITableViewDelegate>
{
    CMTrainApplyViewUpdateDataListener *m_pUpdataDataListerner;
    
    NSInteger selectRow; //cell当前点击行
    
    @public
    CMTrainApplyList *m_pTrainApplyList;
    
    CMTrainApplyList *m_pTrainNotApplyList;
    
    CMTrainApplyList *m_pTrainOverList;
    
    char m_sFlag[16];
}

@property(assign,nonatomic)int flag;
-(void) refreshTableView;
@end


class CMTrainApplyViewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMTrainApplyView* trainview = (__bridge CMTrainApplyView*)UserData;
        
        if (trainview.flag == 1) {
            [trainview setHasMore:!trainview->m_pTrainApplyList->IsEnd()];
        }
        if (trainview.flag == 0) {
            [trainview setHasMore:!trainview->m_pTrainNotApplyList->IsEnd()];
        }
        if (trainview.flag == 2) {
            [trainview setHasMore:!trainview->m_pTrainOverList->IsEnd()];
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
