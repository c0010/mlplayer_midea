//
//  CMPracticeControl.h
//  MLPlayer

//  专项练习

//  Created by sunjj on 11-10-9.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableView.h"
#import "CMExamInfoControl.h"
#import "cmexerciselist.h"

class CMExameListUpdateDataListener;

@interface CMPracticeControl : UIView<CMExamControlDelegate,UITableViewDelegate,UITableViewDataSource,UINavigationControllerDelegate> {
	
	CMTableView *TableViewList;			
	CMExameListUpdateDataListener* m_pUpdateDataListener;
    
	@public
	CMExerciseList* m_pExerciseList;
    
    UIView* bgview;
    
    
    }
@property (nonatomic, weak) UINavigationController* navigationControllerDelegates;
@property (nonatomic,strong)NSString *trainID;


-(void)GetListTable;
- (void)startFlash;//第一次进入页面刷新
@end

class CMExameListUpdateDataListener:public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent) 
	{
		NSLog(@"CMExameUpdateDataListener OnUpdateDataProgress");
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMExameUpdateDataListener OnUpdateDataFinish Result= %d",Result);
		
		CMPracticeControl* examControl = (__bridge CMPracticeControl*)UserData;
		
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
		//	[tool ShowAlert:I(@"无题目")];
		}
		else {
			[tool ShowError:Result];
		}
	}
	
};
