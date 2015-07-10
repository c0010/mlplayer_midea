//
//  CMTrainListView.h
//  MLPlayer
//
//  Created by hushengwu on 14/11/5.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMRefreshMoreView.h"
#include "cmmytrainlist.h"
#import "tool.h"

class CMTrainListViewUpdateDataListener;

@interface CMTrainListView : CMRefreshMoreView{
    CMTrainListViewUpdateDataListener *m_pUpdataDataListerner;
    
    NSInteger selectRow; //cell当前点击行
    
@public
    CMMyTrainList *m_pTrainList;
    char m_sFlag[16];

}
@property(nonatomic,assign)BOOL isUseCache;

-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh;

-(void) refreshTableView;

@end


class CMTrainListViewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result)
	{
		CMTrainListView* trainview = (__bridge CMTrainListView*)UserData;
        
		[trainview setHasMore:!trainview->m_pTrainList->IsEnd()];
        
        [trainview GetBrowserList];
        
		[tool DisimissActivityIndicator];
        
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
		}
        else{
            [tool ShowError:Result];
        }
		
	}	
};
