//
//  CMPositionCourseView.m
//  MLPlayer
//
//  Created by sunjj on 13-7-15.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMPositionCourseView.h"
#import "CMNavgateItem.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "CMMarkViewController.h"
#define kCellIdentifier @"com.apple.CMItemView.CellIdentifier"


@implementation CMPositionCourseView

- (id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh
{
    self = [super initWithFrame:frame refresh:brefresh];
    if (self) {
        // Initialization code
        
        memset(m_sFlag,0,16);

        m_pUpdataDataListerner = NULL;

    }
    return self;
}

-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh  useCache:(BOOL)isUseCache
{
	if(!sFlag)
		return;
    
	if(!self.Contenthandler || bRefresh)
	{
        utf8ncpy(m_sFlag, sFlag, 15);
        
		if(!m_pUpdataDataListerner)
			m_pUpdataDataListerner = new CMPositionCourseUpdateDataListener();
		if(!self.Contenthandler)
		{
			CMBrowser* pBrowser = new CMBrowser(m_pUpdataDataListerner);
			pBrowser->SetUserData((__bridge void*)self);
			self.Contenthandler = pBrowser;
		}
        
       	CMBrowser* pBrowser = (CMBrowser*) self.Contenthandler;
        pBrowser->SetListener(m_pUpdataDataListerner, NULL);
        
        pBrowser->SetUserData((__bridge void*)self);
        
        if (pBrowser->IsRunning())
            pBrowser->Cancel();

        if(isUseCache)
        {
            pBrowser->SetRequestType(1);
        }
        else
        {
            pBrowser->SetRequestType(0);
            
        }

        
        if(pBrowser->RequestPisitionCourse())
		{
            
		}
	}
	self.HasMore = false;
}


-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh
{
    [self LoadData:sFlag refresh:bRefresh useCache:NO];
}

-(void)RefreshList
{
    if(self.isUseCache)
        [self LoadData:m_sFlag refresh:true useCache:YES];
    else
        [self LoadData:m_sFlag refresh:true];
    
    self.isUseCache = NO;
}


-(BOOL)RefreshMore
{
	if([self HasMore])
	{
        
        if(!m_pUpdataDataListerner)
			m_pUpdataDataListerner = new CMPositionCourseUpdateDataListener();
        
       	CMBrowser* pBrowser = (CMBrowser*) self.Contenthandler;
        pBrowser->SetListener(m_pUpdataDataListerner, NULL);
        
		return pBrowser->RequestMore();
	}
    
    return NO;
}




- (void)dealloc {
    if (self.Contenthandler) {
        self.Contenthandler->Cancel();
    }
	SAFEDELETE(m_pUpdataDataListerner);
    SAFEDELETE(m_pGetImageListener);
    SAFEDELETE(m_pWebImage);
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}



@end
