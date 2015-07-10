//
//  CMServersInfoControl.h
//  MLPlayer
//
//  Created by sunjj on 11-8-26.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableViewCell.h"
#import "cmcustomerlist.h"

class CMServersInfoListener;

@interface CMServersInfoControl : CMViewController <UITableViewDelegate,UITableViewDataSource>
{
	CMServersInfoListener *m_pListener;
	CMCustomerList *m_pCustomerts;	
	
	UINavigationBar *topNavigationBar;
	UITableView* m_pTableView;
	NSString * sServerName;
}
@property(nonatomic,strong) UITableView *m_pTableView;
@property(nonatomic,strong) NSString * sServerName;
@end
class CMServersInfoListener:public IMUpdateDataListener
{
public:
	CMServersInfoListener(){};
	~CMServersInfoListener(){};
	
    void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		
	}
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		CMServersInfoControl* lstSearchControl = (__bridge CMServersInfoControl*)UserData;
		[tool CancelWait];
		if(Result != TResult::ENothing)
			[lstSearchControl.m_pTableView reloadData];
		else
			[tool ShowError:Result];
	}
};
