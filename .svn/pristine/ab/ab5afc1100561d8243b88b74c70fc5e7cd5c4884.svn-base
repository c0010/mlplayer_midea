//
//  CMMyExamControl.h
//  MLPlayer
//
//  Created by sunjj on 11-10-9.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMCourseTableViewCell.h"
#import "CMTableViewCell.h"
#import "CMTableView.h"
#import "CMExamInfoControl.h"
#import "cmexamlist.h"
#import "cmcommon.h"

class CMMyExamUpdateDataListener;

@interface CMMyExamControl : UIView<CMExamControlDelegate,UITableViewDelegate,UITableViewDataSource,UINavigationControllerDelegate> {

	CMTableView * TableViewList;
	CMExamList *m_pCMExamList;
	
	CMMyExamUpdateDataListener *m_UpdateDataListener;
	
	NSIndexPath * selectedCellIndexPath;
    
    UIView* bgview;
    
    NSInteger selectRow;
}
@property (nonatomic, weak) UINavigationController* navigationControllerDelegates;
@property (nonatomic, strong) NSString* TrainID;

-(void)GetListTable;
- (void)startFlash;//第一次进入页面刷新
@end

class CMMyExamUpdateDataListener:public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent) 
	{
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		
		CMMyExamControl* examControl = (__bridge CMMyExamControl*)UserData;
		
		[tool CancelWait];
		
		[examControl GetListTable];
		
		if(Result == TResult::ESuccess)
		{			
		}
		else if(Result == TResult::ENotSupportOffline)
		{
            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
			[tool ShowAlert:str];
		}
		else if(Result == TResult::ENothing)
		{
			//[tool ShowAlert:I(@"无题目")];
		}
		else {
			[tool ShowError:Result];
		}
	}
};

