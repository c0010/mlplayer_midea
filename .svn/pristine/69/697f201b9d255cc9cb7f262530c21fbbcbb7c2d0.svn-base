//
//  test.h
//  MLPlayer
//
//  Created by sunjj on 11-12-31.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableView.h"
#import "CustomBGAlert.h"
#include "cmqacategory.h"
#import "tool.h"

class CMQaCategoryUpdateDataListener;
@interface CMQaCategoryControl: CMViewController  <UITableViewDelegate,UITableViewDataSource>{
	NSMutableArray *itemArray ;
	CMQACategory* m_pQaCategory;
	CMQaCategoryUpdateDataListener* m_pQaCategoryUpdateDataListener;
	CMTableView *TableViewList;
	CustomBGAlert* alert;
	NSInteger checkpos;
}

@property(nonatomic,strong)CustomBGAlert* alert;
@property(nonatomic,assign) NSInteger type; //1分类可打开，2选择

@property(nonatomic,strong) NSMutableArray* itemArray ;
-(void)GetBrowserList;
@end

class CMQaCategoryUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		CMQaCategoryControl* qacategorycontrol = (__bridge CMQaCategoryControl*)UserData;
		[tool CancelWait];
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {			
			[qacategorycontrol GetBrowserList];
		}else {
			[tool ShowError:Result];			
		}
		
	}	
};