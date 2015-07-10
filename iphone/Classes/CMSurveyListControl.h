//
//  CMSurveyListControl.h
//  OCplusplus
//
//  Created by sunjj on 11-4-27.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//收藏

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmsurvey.h"
#import "cmsurveylist.h"
#import "CMTableView.h"


class CMSurveyListListener;

@interface CMSurveyListControl : CMViewController <UITableViewDelegate,UITableViewDataSource> {
	
	CMSurveyListListener *m_pListener;
	CMSurveyList *m_surveylist;
	
	CMTableView* TableViewList;	
    
    UIView* bgview;
    
    BOOL surveyDone;
    
    NSInteger selectRow;
    
}
@property(nonatomic,strong) UITableView *TableViewList;
@property(nonatomic,strong)NSString *trainID;

-(void)GetTableList;
-(void) refreshTableView;

@end


class CMSurveyListListener :public IMUpdateDataListener
{
public:
	CMSurveyListListener(){};
	~CMSurveyListListener(){};

	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		//CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{	
		NSLog(@"CMSurveyListListener OnUpdateDataFinish Result=%d",Result);
		
		CMSurveyListControl* listView = (__bridge CMSurveyListControl*)UserData;
		[listView GetTableList];
		if(Result == TResult::ESuccess)
		{
		}
		else if(Result == TResult::ENotSupportOffline)
		{
            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
			[tool ShowAlert:str];
		}
		else if( Result == TResult::ENothing)
		{
			//[tool ShowAlert:I(@"暂无调研")];
		}
		else
		{
			[tool ShowError:Result];
		}
	}
};
