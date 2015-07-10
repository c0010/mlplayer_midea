//
//  CMMarkView.m
//  MLPlayer
//
//  Created by hushengwu on 13-10-8.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMMarkView.h"
#import "CMNavgateItem.h"
#import "SDWebImage/UIImageView+WebCache.h"
#define kCellIdentifier @"com.apple.CMMarkView.CellIdentifier"

@implementation CMMarkView
@synthesize MarkID;
- (id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh
{
    self = [super initWithFrame:frame refresh:brefresh];
    if (self) {
        // Initialization code
        memset(m_sFlag,0,16);
        
        m_pUpdataDataListener = NULL;
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

-(void)searchByMarkid:(id)sender event:(id)event
{
    ;
}

-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh
{
	if(!sFlag)
		return;
    
    //[self automaticRefresh];
    
	if(!self.Contenthandler || bRefresh)
	{
        utf8ncpy(m_sFlag, sFlag, 15);
                
		if(!m_pUpdataDataListener)
			m_pUpdataDataListener = new CMMarkViewUpdateDataListener();
		if(!self.Contenthandler)
		{
			CMBrowser* pBrowser = new CMBrowser(m_pUpdataDataListener);
			pBrowser->SetUserData((__bridge void*)self);
			self.Contenthandler = pBrowser;
		}
        CMBrowser* pBrowser = (CMBrowser*) self.Contenthandler;
        self.Contenthandler->SetUserData((__bridge void*)self);
        self.Contenthandler->SetListener(m_pUpdataDataListener, NULL);
        
        if(pBrowser->RequestMarkClass([MarkID UTF8String]))
		{
            //	[tool Wait];
            //  [self automaticRefresh];
		}
	}
	self.HasMore = false;
	//[self GetBrowserList];
}

-(void)RefreshList
{
	[self LoadData:m_sFlag refresh:true];
	
}


-(BOOL)RefreshMore
{
	if([self HasMore])
	{
        
        if(!m_pUpdataDataListener)
			m_pUpdataDataListener = new CMMarkViewUpdateDataListener();
        CMBrowser* pBrowser = (CMBrowser*) self.Contenthandler;
        pBrowser->SetListener(m_pUpdataDataListener, NULL);

		return pBrowser->RequestMore();
	}
    return NO;
}




- (void)dealloc {
    if (self.Contenthandler) {
        self.Contenthandler->Cancel();
    }
	SAFEDELETE(m_pUpdataDataListener);
    CMRELEASE(MarkID);
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
    
}

@end
