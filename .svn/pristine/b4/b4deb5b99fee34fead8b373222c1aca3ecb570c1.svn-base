//
//  CMBrowserControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CustomBGAlert.h"
#import "CMTableView.h"
#include "stdafx.h"
#include "cmmyinfo.h"

class CMCreditUpdateDataListener;
@interface CMCreditControl:UIViewController<UITableViewDelegate,UITableViewDataSource>{
	CustomBGAlert* alert;
	CMCreditUpdateDataListener* m_pUpdataDataListerner;
	CMTableView* tableviewlist;
	UILabel* txtcredit;
	NSInteger checkpos;
}
@property(nonatomic,strong)CustomBGAlert* alert;
-(void)setCredit;
-(int)getSelCredit:(int)row;
@end
class CMCreditUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		CMCreditControl* creditcontrol = (__bridge CMCreditControl*)UserData;
		[tool CancelWait];
		if (Result == TResult::ESuccess || Result == TResult::ENothing)
			[creditcontrol setCredit];
		else 
		{
			[tool ShowError:Result];
			[creditcontrol.navigationController popViewControllerAnimated:YES];
		}
		
	}	
};