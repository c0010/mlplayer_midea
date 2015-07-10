//
//  CMClassTopView.m
//  MLPlayer
//
//  Created by wangjianbin on 15/6/25.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMClassTopView.h"

@implementation CMClassTopView

-(id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame refresh:NO];
    if (self)
    {
        m_pListener = NULL;
        if (!m_pListener)
        {
            m_pListener = new CMUpdateTopDataListener;
        }
        if (!self.Contenthandler)
        {
            CMBrowser *browser = new CMBrowser(m_pListener);
            browser->SetUserData(BridgeObjectToC(self));
            self.Contenthandler = browser;
        }
    }
    return self;
}

- (void)loadData
{
    CMBrowser *browser = (CMBrowser*)self.Contenthandler;
    if (!m_pListener)
    {
        m_pListener = new CMUpdateTopDataListener;
    }
    browser->SetUserData(BridgeObjectToC(self));
    browser->SetListener(m_pListener, nil);
    [tool ShowActivityIndicator:self];
    if (!browser->RequestTop([m_type UTF8String], m_courseid))
    {
        [tool ShowAlert:I(@"获取Top失败")];
        return;
    }
}

- (void)setCourseID:(const char*)courseid type:(NSString*)type
{
    m_type = [type copy];
    
    utf8ncpy(m_courseid, courseid, 63);
}

- (void)dealloc
{
    SAFEDELETE(m_pListener);
    SAFEDELETE(self.Contenthandler);
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
