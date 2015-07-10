//
//  CMPositionCourseView.h
//  MLPlayer
//
//  Created by sunjj on 13-7-15.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMItemView.h"
#import "cmcommon.h"
#import "cmbrowser.h"
#import "CMQuestionDetailControl.h"


class CMPositionCourseUpdateDataListener;

@interface CMPositionCourseView : CMItemView{
    
    CMPositionCourseUpdateDataListener* m_pUpdataDataListerner;

    char	m_sFlag[16];
    
}

- (id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh;
- (void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh;

@end


class CMPositionCourseUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result)
	{
		CMPositionCourseView* browserview = (__bridge CMPositionCourseView*)UserData;
		CMBrowser* pBrowser = (CMBrowser*)browserview.Contenthandler;
		[browserview setHasMore:!pBrowser->IsEnd()];
	//	[tool DisimissActivityIndicator];
        [browserview GetBrowserList];
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
           // browserview.tableviewlist.separatorColor = UIColorRGB(0xd8dbdc);
          //  browserview.tableviewlist.backgroundColor = UIColorRGB(0xd8dbdc);
		}else {
			[tool ShowError:Result];
		}
		
	}
};

