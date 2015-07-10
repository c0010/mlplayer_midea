//
//  CMWrongControl.h
//  MLPlayer
//
//  Created by sunjj on 11-10-9.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMTableView.h"
#import "CMTableViewCell.h"
#import "CMViewController.h"
#import "CMExamInfoControl.h"
#import "cmquestioncategory.h"
#import "cmcommon.h"

class CMWrongListUpdateDataListener;

@interface CMWrongControl : UIView<CMExamControlDelegate,UITableViewDelegate,UITableViewDataSource,UINavigationControllerDelegate>
{
	CMTableView *TableViewList;			
	CMWrongListUpdateDataListener* m_pUpdateDataListener;	
	
	CMQuestionCategory * m_pQuestionCategory;

    
    UIView* bgview;
}
@property (nonatomic, weak) UINavigationController* navigationControllerDelegates;
@property (nonatomic, assign) int nWrongPractice; //错题库中错误练习数

-(void)GetListTable;
- (void)startFlash;//第一次进入页面刷新
- (void)gotoNav_repeat:(int)row;
@end

class CMWrongListUpdateDataListener:public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent) 
	{
		NSLog(@"CMExameUpdateDataListener OnUpdateDataProgress");
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMExameUpdateDataListener OnUpdateDataFinish Result= %d",Result);
		
		CMWrongControl* examControl = (__bridge CMWrongControl*)UserData;
		
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
