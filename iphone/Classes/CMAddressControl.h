//
//  CMAddressSearchControl.h
//  MLPlayer
//
//通讯录
//
//  Created by sunjj on 11-5-12.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmcontacts.h"
#import "CustomBGAlert.h"
#include "cmwebimage.h"

class CMAddressUpdateDataListener;
class CMAddressGetImageListener;
@interface CMAddressControl : CMViewController <UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate,UIScrollViewDelegate>
{
	CMAddressUpdateDataListener *m_pListener;
	CMContacts *m_pContacts;	
	
	UISearchBar *searchBar;
	UINavigationBar *topNavigationBar;
	
	UIActivityIndicatorView* dwActiveView;
	UITableView* tableView;
	UIButton* btnPhone;
	UIButton* btnMsg;
	NSString* phoneNum;
	UIImageView *TalkImage;
	UIButton *btnTalk;
	
	UIButton* btnMore;
	CMWebImage* m_pWebImage;
	CMAddressGetImageListener* m_pImageListener;
	
    UITextField *_searchField;   //搜索框
    UIButton *_backBtn;
    
    UIView* bgview;     //无数据logo
    
    BOOL isNothing;     
    
    BOOL showRecent;
    
    BOOL isSearchfieldOnFirstRespond;
}

@property(nonatomic,strong) UIActivityIndicatorView *activity;
@property(nonatomic,strong) UITableView *tableView;
@property (nonatomic,strong) UISearchBar *searchBar;
@property(nonatomic,strong) UIImageView *TalkImage;
@property(nonatomic,strong) UIButton *btnTalk;
@property(nonatomic, strong) UITextField *searchField;
@property(nonatomic, strong) UIButton *backBtn;
-(void)gotoSearch:(NSString *)value;
-(void)hidKeyBoard;
-(void)loadTableList;
@end

class CMAddressGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMAddressControl* addresscontrol = (__bridge CMAddressControl*)UserData;
        
        [tool DisimissActivityIndicator];

		if (Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[addresscontrol.tableView reloadData];
		}else {
			//[tool ShowError:Result];			
		}
	}
};

class CMAddressUpdateDataListener :public IMUpdateDataListener
{
    
public:
	CMAddressUpdateDataListener(){};
	~CMAddressUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{

	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{	
		NSLog(@"CMSurveyUpdateDataListener OnUpdateDataFinish Result=%d",Result);
		
		CMAddressControl* control = (__bridge CMAddressControl*)UserData;
		
        [tool DisimissActivityIndicator];

        if(Result == TResult::ESuccess )
		{
			[control loadTableList];
		}else if (Result == TResult::ENothing) {
            
            [control loadTableList];

		}else {
			[tool ShowError:Result];
		}
	}
	
};
