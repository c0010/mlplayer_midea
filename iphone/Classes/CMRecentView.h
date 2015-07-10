//
//  CMBrowserView.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMItemView.h"
#include "cmrecentcontent.h"

class CMRecentUpdateDataListener;
class CMRecentGetImageListener;
@interface CMRecentView : CMRefreshMoreView {
	CMRecentUpdateDataListener* m_pUpdataDataListerner;
	
	CMRecentGetImageListener *m_pGetImageListener;
	CMWebImage * m_pWebImage;
	CMContenthandler * m_pContenthandler;
}
@property(nonatomic,assign)CMContenthandler* Contenthandler;

-(void)LoadData;

-(id)initWithFrame:(CGRect)frame;
-(void)RefreshList;
-(BOOL)RefreshMore;
@end

class CMRecentGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMRecentView* recentview = (__bridge CMRecentView*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
			[recentview GetBrowserList];
		}else {
			//[tool ShowError:Result];			
		}
	}
};
class CMRecentUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		CMRecentView* recentview = (__bridge CMRecentView*)UserData;
		CMRecentContent* pRecentContent = (CMRecentContent*)recentview.Contenthandler;
		[recentview setHasMore:!pRecentContent->IsEnd()];
        [tool DisimissActivityIndicator];
        [recentview GetBrowserList];
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
           // recentview.tableviewlist.separatorStyle = UITableViewCellSeparatorStyleNone;
            //recentview.tableviewlist.backgroundColor = [UIColor clearColor];//UIColorRGB(0xf7f7f7);
		}else {
			[tool ShowError:Result];			
		}
		
	}	
};