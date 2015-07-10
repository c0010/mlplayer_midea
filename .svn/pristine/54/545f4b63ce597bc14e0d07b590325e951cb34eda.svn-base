//
//  CMSysMessageViewController.h
//  MLPlayer
//
//  系统消息界面
//
//  Created by 王浩沣 on 14-6-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMChatMessageCell.h"
#import "XMPPFramework.h"
#import "CMInteractModel.h"
#import "CMSysMessageCell.h"
#import "CMViewController.h"
#import "cmgroup.h"
#import "CMInteractModel.h"


#define kSysMessageCell @"com.ulp.sysmessagecell"

class CMEnterGroupSysMessageListener;
@interface CMSysMessageViewController : CMViewController<NSFetchedResultsControllerDelegate,CMSysMessageCellDelegate,UITableViewDataSource,UITableViewDelegate>
{
    UITableView *theTableView;
    
    TGroupInfoItem *m_TGroupInfoItem;
    CMEnterGroupSysMessageListener* m_pEnterListener;
    
    NSInteger questIndex;
    UIView* bgview;     //无数据logo
    UIButton *removeButton;

}
@property (nonatomic, strong) UITableView *theTableView;
@property(nonatomic,strong)NSFetchedResultsController* fetchedResultsController;
@property (nonatomic, strong) CMDialogueItem *sysDialogueItem;

- (void)joinRoom;

@end

class CMEnterGroupSysMessageListener: public IMUpdateDataListener
{
public:
    CMEnterGroupSysMessageListener(){};
    ~CMEnterGroupSysMessageListener(){};
    void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        //CMMainControl* mainControl = (CMMainControl*)UserData;
	}
    
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMSurveyUpdateDataListener OnUpdateDataFinish Result=%d",Result);
		CMSysMessageViewController* control = (__bridge CMSysMessageViewController*)_Block_H_  UserData;
		if(Result == TResult::ESuccess )
		{
			[control joinRoom];
            
            
		}else if (Result == TResult::ENothing) {
            //[control loadTableList];
            
		}else {
			//[tool ShowError:Result];
            [control joinRoom];
		}
	}
};