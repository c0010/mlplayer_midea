//
//  CMMarkView.h
//  MLPlayer
//
//  Created by hushengwu on 13-10-8.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMRefreshMoreView.h"
#import "CMItemView.h"
#import "cmcommon.h"
#import "cmbrowser.h"

class CMMarkViewUpdateDataListener;
@interface CMMarkView : CMItemView{
    CMMarkViewUpdateDataListener *m_pUpdataDataListener;
    
    char	m_sFlag[16];
    
    NSString    *MarkID;
    
}

@property (nonatomic, strong) NSString *MarkID;
- (id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh;
-(void)searchByMarkid:(id)sender event:(id)event;

@end

class CMMarkViewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result)
	{
		CMMarkView* markview = (__bridge CMMarkView*)UserData;
        CMBrowser* pBrowser = (CMBrowser*)markview.Contenthandler;
		[markview setHasMore:!pBrowser->IsEnd()];
        [markview GetBrowserList];
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
         //   markview.tableviewlist.backgroundColor = UIColorRGB(0xd8dbdc);

		}else {
			[tool ShowError:Result];
		}
		
	}
};


