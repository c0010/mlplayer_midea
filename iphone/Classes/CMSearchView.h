//
//  CMBrowserView.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMItemView.h"
#include "cmcategory.h"
#include "cmsearch.h"

class CMSearchUpdateDataListener;
@interface CMSearchView : CMItemView {
	CMSearchUpdateDataListener* m_pUpdataDataListerner;
//    NSString *type;
//    NSString *value;
//    NSString *title;
}
-(id)initWithFrame:(CGRect)frame;
-(void)setGeneratePlaceholderView:(BOOL)isCategory type:(NSString*)stype value:(NSString*)svalue title:(NSString*)stitle;
-(void)Search:(const char*)stype value:(const char*)stxt;
-(void)Search:(const char*)stype value:(const char*)categoryid title:(const char*)title;//分类搜索

@end

class CMSearchUpdateDataListener:public IMUpdateDataListener
{
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		NSLog(@"CMSearchUpdateDataListener OnUpdateDataProgress");
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		CMSearchView* searchview = (__bridge CMSearchView*)UserData;
		CMSearch* pSearch = (CMSearch*)searchview.Contenthandler;
		[searchview setHasMore:!pSearch->IsEnd()];
		[tool DisimissActivityIndicator];
        [searchview GetBrowserList];
		if (Result == TResult::ESuccess) {
         //   searchview.tableviewlist.separatorColor = UIColorRGB(0xdbdbdb);
		//	searchview.tableviewlist.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
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
