//
//  CMBrowserView.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMBrowserView.h"


@implementation CMBrowserView
@synthesize CurrentPos;
@synthesize TrainID;


-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:true];
	if(self != nil)
	{
		memset(m_sFlag,0,16);
		m_pUpdataDataListerner = NULL;
	}
	return self;
}

-(CMCategoryItem*)GetCategory:(const char*)stype
{
	if(!stype)
		return NULL;
	//查找分类
	CMCategory *pCategory = CMCategory::GetInstance();
	CMCategoryItem* pItem = NULL;
	for(int i= 0; i<pCategory->TopItemCount(); i++)
	{
		pItem = pCategory->GetTopItem(i);
        if(pItem!=NULL)
            if( _stricmp(pItem->sType,stype) == 0)
                return pItem;
	}
	return NULL;
}




-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh
{
	[self LoadData:sFlag refresh:bRefresh useCache:NO];
}


-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh  useCache:(BOOL)isUseCache
{
	if(!sFlag)
    {
		return;
    }
    
	if(!self.Contenthandler || bRefresh)
	{
        
        utf8ncpy(m_sFlag, sFlag, 15);
		CMCategoryItem* pItem = [self GetCategory:sFlag];
        
		if(!pItem || CurrentPos >= pItem->FrontChildItemCount())
        {
            [self GetBrowserList];
			return;
        }
        
		if(!m_pUpdataDataListerner)
			m_pUpdataDataListerner = new CMBrowserUpdateDataListener();
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

        self.HasMore = false;
        
        if (!self.TrainID) {//普通课程或资讯
            if(!pBrowser->Request(m_sFlag,pItem->GetSelectedChildItem(CurrentPos)->sID))
            {
                
                [self GetBrowserList];
                
            }
            else
                [tableviewlist reloadData];
            //  [self GetBrowserList];
            
        }else{//培训班课程或资讯
            
            if(!pBrowser->RequestTrain(m_sFlag, [self.TrainID UTF8String]))
            {
                
                [self GetBrowserList];
                
            }
            else
                [tableviewlist reloadData];
            //  [self GetBrowserList];
            
        }
        
		
        

	}
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
		CMBrowser* pBrowser = (CMBrowser*) self.Contenthandler;
        pBrowser->SetListener(m_pUpdataDataListerner, NULL);
        return pBrowser->RequestMore();
        
	}
    return NO;
}

- (void)loadShakeDate:(id)sender
{
    m_pSender = sender;
    
    if (!m_pShakeListener)
    {
        m_pShakeListener = new  CMShakeUpdateListener();
    }
    
    if (m_pShake == NULL)
    {
        m_pShake = new CMShake(m_pShakeListener);
        m_pShake->SetUserData((__bridge void*)self);
    }
    
    m_pShake->SetListener(m_pShakeListener, NULL);
    m_pShake->SetUserData((__bridge void*)self);

    
    m_pShake->Request();
}

- (void)shakeToDetail
{
    [m_pSender performSelector:@selector(shakeDown)];
    
    TBrowserItem* item = NULL;
  
    if(m_pShake->GetItemModel(0)==0)
    {
        item = new TClassItem();
    }
        else
    {
        item = new TCoursewareItem();

    }
    
    
    m_pShake->GetItem(0, item);

    
    CMShakeListController *shakeController=[[CMShakeListController alloc]init];
    shakeController->m_pShake=m_pShake;
    shakeController.openShake = YES;
    shakeController.title = I(@"您摇到的课程");
    
    
    [shakeController setHidesBottomBarWhenPushed:YES];
    [((UIViewController*)[self.superview nextResponder]).navigationController pushViewController:shakeController animated:YES ];
    
    SAFEDELETE(item);
    
    CMRELEASE(shakeController);

}

- (void)dealloc {
    if (self->m_pContenthandler != NULL && self->m_pContenthandler->IsRunning()) {
        self->m_pContenthandler->Cancel();
    }
	
	SAFEDELETE(m_pUpdataDataListerner);
	SAFEDELETE(self->m_pContenthandler);
    SAFEDELETE(m_pShakeListener)
    SAFEDELETE(m_pShake);
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}


@end

