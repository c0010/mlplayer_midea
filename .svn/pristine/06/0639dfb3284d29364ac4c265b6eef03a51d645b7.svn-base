//
//  CMBrowserView.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMSearchView.h"


@implementation CMSearchView

-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:false];
	if(self != nil)
	{
		m_pUpdataDataListerner = NULL;

		if(!m_pUpdataDataListerner)
			m_pUpdataDataListerner = new CMSearchUpdateDataListener();
		if(!self.Contenthandler)
		{
			CMSearch* pSearch = new CMSearch(m_pUpdataDataListerner);
			pSearch->SetUserData((__bridge void*)self);
			self.Contenthandler = pSearch;
		}
        
	}
	return self;
}

-(void)setGeneratePlaceholderView:(BOOL)isCategory type:(NSString*)stype value:(NSString*)svalue title:(NSString*)stitle;
{
//    type  = stype;
//    value = svalue;
//    title = stitle;
    if (isCategory) {
       // [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(searchCategory) on:bgview];
    }
    else
        ; //[tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(searchCustomer) on:bgview];

}

//- (void)searchCustomer{
//    [self Search:[type UTF8String] value:[value UTF8String]];
//}
//
//- (void)searchCategory{
//    [self Search:[type UTF8String] value:[value UTF8String] title:[title UTF8String]];
//}


-(void)Search:(const char*)stype value:(const char*)stxt
{
	if(!stype || !stxt)
		return;
	CMSearch* pSearch = (CMSearch*) self.Contenthandler;
    
    
    if(!m_pUpdataDataListerner)
        m_pUpdataDataListerner = new CMSearchUpdateDataListener();

    
    pSearch->SetUserData((__bridge void*)self);
    pSearch->SetListener(m_pUpdataDataListerner, NULL);
    [tool ShowActivityIndicator:self];
	if(pSearch->Search(stype,stxt))
        ;
	
}
-(void)Search:(const char*)stype value:(const char*)categoryid title:(const char*)title{
    if(!stype || !categoryid)
		return;
	CMSearch* pSearch = (CMSearch*) self.Contenthandler;
    
    
    if(!m_pUpdataDataListerner)
        m_pUpdataDataListerner = new CMSearchUpdateDataListener();
    
    
    pSearch->SetUserData((__bridge void*)self);
    pSearch->SetListener(m_pUpdataDataListerner, NULL);
    [tool ShowActivityIndicator:self];
	if(pSearch->CategorySearch(stype, categoryid, title))
        ;
//	[self GetBrowserList];
}


-(BOOL)RefreshMore
{
	if([self HasMore])
	{
		CMSearch* pSearch = (CMSearch*) self.Contenthandler;
        
        if(!m_pUpdataDataListerner)
            m_pUpdataDataListerner = new CMSearchUpdateDataListener();
        
        
        pSearch->SetUserData((__bridge void*)self);
        pSearch->SetListener(m_pUpdataDataListerner, NULL);
        return pSearch->RequestMore();
	}
    else
        return NO;
}
- (void)dealloc {
	
	SAFEDELETE(m_pUpdataDataListerner);
	SAFEDELETE(self->m_pContenthandler);
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}


@end

