//
//  CMExpertsController.h
//  MLPlayer
//
//  Created by kyp on 14-3-26.
//  Copyright (c) 2014年 w. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmcontacts.h"
#import "CustomBGAlert.h"
#include "cmwebimage.h"
#include "CMQuestionControl.h"
class CMExpertsUpdateDataListener;
class CMExpertsGetImageListener;


@interface CMExpertsController : CMViewController<UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate,UIScrollViewDelegate>
{
    //CMContacts *m_pContacts;
	
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
    UITextField *_searchField;   //搜索框
    UIButton *_backBtn;
    UIView* bgview;     //无数据logo
    UISegmentedControl* seg;
    
    CMContacts *m_pContacts;
    CMWebImage* m_pWebImage;
    CMExpertsUpdateDataListener * m_pListener;
    CMExpertsGetImageListener* m_pImageListener;
    
    BOOL isNothing;
    
    BOOL showRecent;
    
    BOOL isSearchfieldOnFirstRespond;
    
    BOOL recentorcontact;    //联系人界面或通讯录界面
    
    
    
   // CMQuestionControl *questionctrl;

}
@property(nonatomic,strong) UIActivityIndicatorView *activity;
@property(nonatomic,strong) UITableView *tableView;
@property (nonatomic,strong) UISearchBar *searchBar;
@property(nonatomic,strong) UIImageView *TalkImage;
@property(nonatomic,strong) UIButton *btnTalk;
@property(nonatomic, strong) UITextField *searchField;
@property(nonatomic, strong) UIButton *backBtn;
@property(nonatomic,strong) CMQuestionControl *questionctrl;
@property(nonatomic, strong) NSString *categoryID;

-(void)gotoSearch:(NSString *)value;
-(void)hidKeyBoard;
-(void)loadTableList;

@end

class CMExpertsGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMExpertsController* control = (__bridge CMExpertsController*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[control.tableView reloadData];
		}else {
			//[tool ShowError:Result];
		}
	}
};

class CMExpertsUpdateDataListener :public IMUpdateDataListener
{
    
public:
	CMExpertsUpdateDataListener(){};
	~CMExpertsUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        //CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMSurveyUpdateDataListener OnUpdateDataFinish Result=%d",Result);
		
		CMExpertsController* control = (__bridge CMExpertsController*)UserData;
		
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






