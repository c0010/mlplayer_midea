//
//  CMBrowserView.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMItemView.h"
#import "cmcategory.h"
#import "cmbrowser.h"
#import "CMRefreshMoreView.h"
#import "cmshake.h"
#import "CMNavgateItem.h"

#import "CMShakeListController.h"


class CMBrowserUpdateDataListener;
class CMShakeUpdateListener;

@interface CMBrowserView : CMItemView
{
    CMBrowserUpdateDataListener * m_pUpdataDataListerner;
    CMShakeUpdateListener       * m_pShakeListener;
    CMShake                     * m_pShake;
    
    @public
    id   m_pSender;
    char m_sFlag[16];
}


@property(nonatomic,assign)NSInteger CurrentPos; //tab
@property(nonatomic,strong)NSString * TrainID;//培训班ID

-(id)initWithFrame:(CGRect)frame;
-(void) LoadData:(const char*)sFlag refresh:(BOOL)bRefresh;
-(CMCategoryItem*)GetCategory:(const char*)stype;
- (void)loadShakeDate:(id)sender;
- (void)shakeToDetail;

@end

class CMBrowserUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		CMBrowserView* browserview = (__bridge CMBrowserView*)UserData;
		CMBrowser* pBrowser = (CMBrowser*)browserview.Contenthandler;
        

		[browserview setHasMore:!pBrowser->IsEnd()];
        
        [browserview GetBrowserList];
        
        NSLog(@"result = %d",Result);

		[tool DisimissActivityIndicator];
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            ;
        }
        else if(Result == TResult::ENetDisconnect){
			[tool ShowError:Result];
            [browserview stopRefreshingMore];
		}
        else{
            [tool ShowError:Result];
            [browserview stopRefreshingMore];
        }
		
	}	
};

class CMShakeUpdateListener: public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMBrowserView *browser = (__bridge CMBrowserView*)UserData;
//        CMShake* pShake = (CMShake*)browser.Contenthandler;
//        [browser setHasMore:!pShake->IsEnd()];
        if (Result == TResult::ESuccess||Result == TResult::ENothing)
        {
            [browser shakeToDetail];
        }else
        {
            [browser->m_pSender performSelector:@selector(shakeDown)];

            
        }
    }
};
