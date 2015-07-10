//
//  CMShakeListControllerViewController.h
//  MLPlayer
//
//  Created by sunjj on 13-10-8.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import "cmcommon.h"
#import "tool.h"

#import "CMItemView.h"
#import "cmcategory.h"
#import "cmbrowser.h"
#import "CMRefreshMoreView.h"
#import "cmshake.h"
#import "CMNavgateItem.h"
#import "CMClassTableViewCell.h"

class CMShakeListUpdateListener;
class CMShakeListItemGetImageListener;
@interface CMShakeListController : CMViewController<UITableViewDelegate,UITableViewDataSource,CMNavgateItemDelegate>
{
    
    MLPlayerAppDelegate *appDelegate;


    CMShakeListItemGetImageListener *m_pGetImageListener;

    
    CMWebImage* m_pWebImage;
    CMShakeListUpdateListener *m_pShakeListener;
    
    UITableView * tableviewlist;
    
    
    UIView* bgview;
    
    BOOL bHasMore;
    
@public
    CMShake *m_pShake;

}
@property(nonatomic,strong)     UITableView * tableviewlist;

- (void)refreshTitle;

@end
class CMShakeListItemGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
        CMShakeListController *browser = (__bridge CMShakeListController*)UserData;

		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
			[browser.tableviewlist reloadData];
		}else {
			//[tool ShowError:Result];
		}
	}
};

class CMShakeListUpdateListener: public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMShakeListController *browser = (__bridge CMShakeListController*)UserData;
        
        [tool DisimissActivityIndicator];

        //        CMShake* pShake = (CMShake*)browser.Contenthandler;
        //        [browser setHasMore:!pShake->IsEnd()];
        if (Result == TResult::ESuccess || Result == TResult::ENothing)
        {
            [browser refreshTitle];
            [browser.tableviewlist reloadData];

        }else
        {
            
            
        }
    }
};
