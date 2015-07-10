//
//  cmitemcontroller.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMRefreshMoreView.h"
#include "cmqalist.h"
#import "cmcommon.h"
#import "CMImage.h"
#import "CMQuestionTableViewCell.h"
//#import "CMMediaFocusManager.h"

class CMQListGetImageListener;
class CMQListUpdateDataListener;
class CMQListSimpleResultListener;
@interface CMQListView : CMRefreshMoreView
{
	CMQListGetImageListener *m_pGetImageListener;
	CMQListUpdateDataListener* m_pUpdataDataListerner;
	CMQListSimpleResultListener* m_pSimpleResultListener;
	CMWebImage * m_pWebImage;
	CMQAList* m_pQalist;
    
    NSInteger selectedIndex;
}


@property(nonatomic,assign)NSInteger curpos; //0我的提问 1我的回答 2 我的关注 3最新
@property(nonatomic,strong)NSString* flag;
@property(nonatomic,strong)NSString* key;
@property(nonatomic,copy)NSString* category;
@property(nonatomic)CMQAList* qalist;
@property(nonatomic,assign)     NSInteger selectedIndex;
@property (nonatomic,assign) BOOL          isSearchMode;

//提问列表的分类
@property  (nonatomic,copy) NSString* categoryId;


-(id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh;
-(void)RefreshList;
-(BOOL)RefreshMore;
-(void)LoadData;
-(void)Search;
-(void)GetCategory;
@end

class CMQListGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMQListView* qlistview = (__bridge CMQListView*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
			[qlistview GetBrowserList];
		}else {
			//[tool ShowError:Result];			
		}
	}
};
class CMQListUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
        
       // dispatch_async(dispatch_get_main_queue(), ^{
            
            //NSLog(@"%d",Result);
            CMQListView* qlistview = (__bridge CMQListView*)UserData;
            CMQAList* qalist = (CMQAList*)qlistview.qalist;
            [qlistview setHasMore:!qalist->IsEnd()];
            [tool DisimissActivityIndicator];
            [qlistview GetBrowserList];

            if (Result == TResult::ESuccess || Result == TResult::ENothing) {
                ;
                if(Result == TResult::ENothing && qlistview.key != nil)
                {
                    //[[(UIViewController*)[searchview.superview nextResponder] navigationController] popViewControllerAnimated:YES];
                 //   [tool ShowAlert:I(@"没有搜索到内容!")];
                }
            }else {
                [tool ShowError:Result];			
            }
            
        //});
        
        
			}	
};
class CMQListSimpleResultListener : public IMSimpleResultListener
{
	void OnRequestFinish(void* UserData, int Result)
	{
//		NSLog(@"CMCommentSimpleResultListener OnRequestFinish Result=%d",Result);
//		
//		CMInfoCommentControl * infoCommentControl= (CMInfoCommentControl*)UserData;
//		
//		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
//			[infoCommentControl LoadComment];
//		}else {
//			[tool ShowError:Result];
//		}		
	}
};
