//
//  CMPushMessageBoxViewController.h
//  MLPlayer
//
//  Created by wangjianbin on 15/6/17.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMViewController.h"
#import "cmpushmsg.h"
#import "CMTableView.h"
#import "CMGetNewControl.h"

class CMPushMessageBoxListener;
@interface CMPushMessageBoxViewController : CMViewController<UITableViewDataSource,UITableViewDelegate>
{
    CMPushMsg *m_PushMsgInfo;
    CMPushMessageBoxListener *m_pListener;
    
    CMGetNewControl *m_pNewControl;
    CMTableView *tableViewList;
}

- (void)loadTableViewList;

@end

class CMPushMessageBoxListener : public IMUpdateDataListener
{
public:
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMPushMessageBoxViewController *pushMsgVC = (CMPushMessageBoxViewController*)BridgeObjectToOC(UserData);
        {
            [pushMsgVC loadTableViewList];
            if (Result == TResult::ESuccess || Result == TResult::ENothing)
            {
                ;
            }
            else
            {
                [tool ShowError:Result];
            }
        }
    }
};