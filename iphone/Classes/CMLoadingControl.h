//
//  CMLoadingControl.h
//  iphone_Learning
//
//  Created by sunjj on 11-4-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmlogin.h"
#import "cmcommon.h"
#include "cmcategory.h"
#import "tool.h"
#import "cmgroup.h"
#import "CMViewController.h"
#import "CMVersionVerifyAgent.h"

typedef enum {
    TAGLoginTypeDefault = 1,
    TAGLoginTypeFromMidea = 2
}TAGLoginType;

class CMloginListener;
class CMCategoryLister;
class CMMyInfoListener;

@class CMPushMessage;

#define kBigSloganWidth 300
#define kBigSloganHeight 50

#define kSmallSloganWidth 200
#define kSmallSloganHeight 30

class CMGroupUpdateDataListener;
@interface CMLoadingControl : CMViewController
<UIAlertViewDelegate,UITabBarControllerDelegate>
{

	UIActivityIndicatorView * activity;
	NSString *eid;
	NSString *usernames;
	NSString *passwd;
    NSString *userid;

    CMPushMessage* device;
	CMLogin* m_pLogin;
	CMloginListener* m_pListener;
	
	CMCategory* m_pCategory;
	CMCategoryItem* m_pCategoryItem;
	CMCategoryLister* m_pCategoryLister;
	CMMyInfoListener* m_pMyinfoListener;
    
//    UILabel* bigSlogan;
//    UILabel* smallSlogan;
    
    UIImageView *imageViewLogo_1;
    UIImageView *imageViewLogo_2;
    UIImageView *imageViewLogo_3;
	
	BOOL checkAuto;
	BOOL checkpass;
	BOOL firstlogin;
    
    BOOL bIsPush;
    
	CMGroup *m_pGroups;
    
    int tabSelectIndex;
}
-(void) GotoMain;
-(void) OnLoginResult : (int)Result HasNewVersion:(BOOL)HasNewVersion;
-(IBAction)cancelBack;
-(void)GetMyinfo;
-(void)GetCategory;
- (void)sendDeviceToken;
-(void)DoCategory;

@property(nonatomic,strong) UILabel* loadingStatelbl;
@property (nonatomic,strong)UIActivityIndicatorView *activity;
@property(nonatomic,copy)NSString *eid;
@property(nonatomic,copy)NSString *username;
@property(nonatomic,copy)NSString *passwd; 
@property(nonatomic,copy)NSString *userid;
@property (nonatomic) BOOL checkAuto;
@property (nonatomic) BOOL checkpass;
@property (nonatomic) BOOL bIsPush;
@property (nonatomic, assign) TAGLoginType loginType;

@end
class CMloginListener : public IMLoginListener
{
public:
	CMloginListener(){};
	~CMloginListener(){};
	
	void OnLogin(void* UserData, int Result, int HasNewVersion){
		
		NSLog(@"CMloginListener OnLogin result = %d", Result);
		
		CMLoadingControl* Loading= (__bridge CMLoadingControl*)UserData;
				
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{			
            if (![tool GetIsBack]) {
                [Loading OnLoginResult:Result HasNewVersion : HasNewVersion];
            }
            
		}else {
			[Loading.activity stopAnimating];
			[tool ShowError:Result];
			[Loading cancelBack];
		}
	};
};

class CMCategoryLister : public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{

		if (![tool GetIsBack]) {
			
			CMLoadingControl* Loading= (__bridge CMLoadingControl*)UserData;
							
            if (Result == TResult::ESuccess || Result == TResult::ENotSupportOffline)
            {
               
                
                //应用登陆后，自动检测升级   #廖宏兴
                double delayInSeconds = 1.0;
                dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
                dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                    [[CMVersionVerifyAgent sharedVersionVerifyAgent] checkUpdateWhenApplicationStart];
                });
                //登录不再拿个人信息
                [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:0.5]];
                [Loading performSelectorOnMainThread:@selector(GotoMain) withObject:nil waitUntilDone:NO];

			}
            else
            {
				[Loading.activity stopAnimating];
				[tool ShowError:Result];
                [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:1]];

                [Loading cancelBack];

			}
		}
	}
};
class CMMyInfoListener : public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		NSLog(@"OnUpdateDataProgress login");
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		
        CMLoadingControl* Loading= (__bridge CMLoadingControl*)UserData;
//        [Loading sendDeviceToken];
        [Loading GotoMain];

        if (Result == TResult::ESuccess)
        {
            //[Loading GetCategory];
        }
        else
        {
            //[Loading GetMyinfo];
        }
        
	}
};
