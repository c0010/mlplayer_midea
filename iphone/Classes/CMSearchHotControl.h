//
//  CMNavControl.h
//  MLPlayer
//
//  Created by Tim on 12-12-26.
//  Copyright 2013 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#include "cmsearchhotkey.h"
#import "cmsearchcourse.h"
#import "SuggestionsList.h"
#import "tool.h"
#include "cmsearch.h"
#import "CMTableView.h"

class CMSearchHotUpdateDataListener;
class CMSearchHistoryListener;
class CMSearchQuicklyUpdateDataListener;
@interface CMSearchHotControl : CMViewController<UIScrollViewDelegate,UITextFieldDelegate,PassValueDelegate>{
	NSString* flag;
	UISearchBar *searchbar;
	NSMutableArray* hotkeyarray;
	UIView* curView;
	UIPageControl* pagecontrol;
	
	CMSearchHotUpdateDataListener* m_pListener;
    CMSearchHistoryListener* m_pHistoryListener;
    CMSearchQuicklyUpdateDataListener* m_pQuicklyListener;
    
	UIScrollView* _blankView;
    UIActivityIndicatorView *m_pActivityView;
    
    UITextField *_searchField;   //搜索框
    UIButton    *_searchBtn;     //搜索按钮
    SuggestionsList *suggList;   //历史搜索列表
	NSMutableArray* autoarray;   //装载 历史数据
    BOOL isCategorySearch;       //判断是否分类搜索
    
    CMSearchCourse *m_pSearchCourse;
    
    TSearchItem *m_pSearchCateItem;
    CMSearch* m_pSearch;
}
@property(nonatomic,strong)NSMutableArray* autoarray;
@property(nonatomic,strong)NSString* flag;
@property(nonatomic,strong) UIScrollView * blankView;
@property(nonatomic,strong) UIActivityIndicatorView *m_pActivityView;
@property(nonatomic, strong) UITextField *searchField;
@property(nonatomic, strong) UIButton    *searchBtn; 
@property(nonatomic) CMSearchCourse* searchCourse;

- (int)validPageValue:(int)value;
-(void)selethotkey:(id)sender;
- (void)showhotkey;
//- (void)updateDots;
- (void)loadhotkey;
-(void)gotosearchKey:(NSString*)skey title:(NSString *)title;
-(void)setSugestListHidden:(BOOL)hidden;
-(NSMutableArray*)GetAutoList;
- (void)getHistoryList;
- (void)getQuickSearchList;
-(void)Search:(const char*)stype value:(const char*)stxt;


@end

class CMSearchHotUpdateDataListener:public IMUpdateDataListener
{
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{

	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
        CMSearchHotControl * searchhot = (__bridge CMSearchHotControl*)UserData;
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            
             [searchhot loadhotkey];

        }
        else if (Result == TResult::ENotSupportOffline)
        {
        }
        else
        {
            [tool ShowError:Result];
        }
	}
};

class CMSearchHistoryListener:public IMUpdateDataListener
{
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		NSLog(@"CMSearchUpdateDataListener OnUpdateDataProgress");
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result)
	{
        CMSearchHotControl * searchhot = (__bridge CMSearchHotControl*)UserData;
		if (Result == TResult::ESuccess) {
			[searchhot getHistoryList];
		}
		else if(Result == TResult::ENothing)
		{
			[tool ShowAlert:I(@"没有搜索到内容!")];
		}
		else
		{
			[tool ShowError:Result];
		}
	}
	
};


class CMSearchQuicklyUpdateDataListener:public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        NSLog(@"CMSearchQuicklyUpdateDataListener OnUpdateDataProgress");
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMSearchHotControl* searchview = (__bridge CMSearchHotControl*)UserData;
        [tool DisimissActivityIndicator];
        if (Result == TResult::ESuccess) {
            [searchview getQuickSearchList];
        }
        else if(Result == TResult::ENothing)
        {
            ;
        }
        else if (Result == TResult::ENotSupportOffline)
        {
            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
            [tool ShowAlert:str];
        }
        else
        {
            [tool ShowError:Result];			
        }
    }
};

