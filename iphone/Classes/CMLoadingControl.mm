 //  CMLoadingControl.m
//  iphone_Learning
//
//  Created by sunjj on 11-4-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "stdafx.h"
#import "CMLoadingControl.h"
#import "CMMainControl.h"
#import "CMImage.h"
//#import "MobClick.h"
#include "cmsettings.h"
#include "cmmyinfo.h"
#include "MLPlayerAppDelegate.h"
#include "CMPushMessage.h"
#import "CMGroupManager.h"
#import "CMContactManager.h"
#import "CMCoreDataUtils.h"
#import "CMInteractViewController.h"
#import "CMBrowserControl.h"
#import "CMCoreDataUpdate.h"

@implementation CMLoadingControl
@synthesize activity;
@synthesize eid;
@synthesize username;
@synthesize passwd;
@synthesize checkAuto;
@synthesize checkpass;
@synthesize bIsPush;
@synthesize userid;

#define kActivityViewCenterY  270

-(IBAction) cancelBack
{
	[[NSNotificationCenter defaultCenter] postNotificationName:@"loginstate"
                      object:nil
                    userInfo:[NSDictionary dictionaryWithObject:[NSString stringWithFormat:@"%d",3]
                      forKey:@"name"]];
	[tool SetIsBack:YES];
	[self.navigationController popViewControllerAnimated:YES];   //移除栈顶页面
    
}

-(void) connectXmppAndJoinRoom
{
    //登录xmpp服务器
    [ XmppHandler connect ];

}

-(void) GotoMain
{
    
    //切换用户数据库
    [[XMPPChatMessageCoreDataStorage sharedInstance] resetStorePath];
    
    //获取用户详细信息
    [[CMContactManager manager] doRequestOwnerUserInfo];
    
//    [[CMCoreDataUpdate create] doUpdate];
    
    //获取我的群列表
    [[CMGroupManager manager] doRequestMyGroup:^(CMGroup *group) {
        
        m_pGroups = group;
        
        for (int i = 0; i < m_pGroups->GetItemCount(); i ++) {
            
            TGroupInfoItem item;
            if (m_pGroups && m_pGroups->GetItem(i,  item)) {
                [CMCoreDataUtils saveGruopCacheFromTGroupInfoItem:item resetJoined:YES];
            }
        }
        
        [CMCoreDataUtils removeNotExistGroupCache:m_pGroups];
        
        [self performSelectorInBackground:@selector(connectXmppAndJoinRoom) withObject:nil];
        
        
    } failure:^(int errorCode) {
                
        [self performSelectorInBackground:@selector(connectXmppAndJoinRoom) withObject:nil];
        
    }];
   
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];         //跳转到主页面
    NSString *type = [ud objectForKey:kUDPushType];
    if(bIsPush)
	{
        CMMainControl* mainController = [[CMMainControl alloc] init];
        mainController.bIsPush = bIsPush;
        mainController.canShowLeft = YES;

        [ud setObject:@"1" forKey:kUDOpenPush];//1 打开push 0 关闭
        
        int selectRow = 0;
        
        if ([type isEqualToString:@"course"] || [type isEqualToString:@"position_course"]) {
            selectRow = 0;
        }
        else if ([type isEqualToString:@"news"]){
            selectRow = 1;
        }
        else if ([type isEqualToString:@"exam"] || [type isEqualToString:@"exercise"]){
            selectRow = 4;
        }
        else if ([type isEqualToString:@"survey"]){
            selectRow = 4;
        }
        [mainController setSelectedIndex:selectRow];
        
		[self.navigationController pushViewController:mainController animated:NO];
        
	}
	else
	{
		CMMainControl* mainController = [[CMMainControl alloc] init];
//        mainController.delegate = self;
        mainController.canShowLeft = YES;
        
		[self.navigationController pushViewController:mainController animated:YES];
	}
}

//- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController{
//    
//
//    if (tabSelectIndex == tabBarController.selectedIndex) {
//        
//        CMViewController *selectViewController = [((UINavigationController *)viewController).viewControllers objectAtIndex:0];
//
//        if ([selectViewController respondsToSelector:@selector(gotoTop)]) {
//            
//            [selectViewController gotoTop];
//        }
//    }
//}
//
//- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController{
//
//    tabSelectIndex = tabBarController.selectedIndex;
//    
//    return YES;
//}

-(void)OpenUpdate:(id)data
{
	NSDictionary* dic = (NSDictionary*)data;
	NSString* aValue = (NSString*)[dic objectForKey:@"update"];
//	if([aValue caseInsensitiveCompare:@"YES"] == NSOrderedSame && [MessageBox DoModalWithTitle:I(@"完成提示") message:I(@"确定交卷？") mode:MODE_YESNO])
//	{
//		//itms-apps
//		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://itunes.apple.com/cn/app/id589274023?mt=8"]];
//		exit(0);
//	}
//	else
//		[self GetMyinfo];
    
    
    
    if ([aValue caseInsensitiveCompare:@"YES"] == NSOrderedSame){
        WEAKSELF;
        CMAlertView *alert = [[CMAlertView alloc] initWithTitle:I(@"完成提示") message:I(@"确定交卷？") cancelButtonTitle:I(@"取消") otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
            STRONGSELF;
            if (buttonIndex == BUTTON_CONFIRM_TAG) {
                //itms-apps
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://itunes.apple.com/cn/app/id589274023?mt=8"]];
                exit(0);
                
            }
            else if (buttonIndex == BUTTON_CANCEL_TAG){
                [sself GetMyinfo];
            }
        }];
        [alert setDisabledOutSide:YES];
        [alert show];
    }
    else {
        [self GetMyinfo];
    }
}

-(void) OnLoginResult : (int)Result HasNewVersion:(BOOL)HasNewVersion;
{
    m_pLogin->LoadFromDbs();
    
    NSString *testStr = [NSString stringWithUTF8String:CMGlobal::TheOne().GetUpdateUrl()];
    
    if (HasNewVersion)
    {
        CMAlertView * alert = [[CMAlertView alloc]initWithTitle:I(@"发现新版本") message:I(@"是否升级？") cancelButtonTitle:I(@"取消") otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
            if (buttonIndex == BUTTON_CONFIRM_TAG)
            {
                [[UIApplication sharedApplication]openURL:[NSURL URLWithString:[NSString stringWithUTF8String:CMGlobal::TheOne().GetUpdateUrl()]]];
                [self cancelBack];
            }
            if (buttonIndex == BUTTON_CANCEL_TAG)
            {
                if (!__iOS7 && !CMGlobal::TheOne().IsExistNetwork()) {
                    [self performSelector:@selector(GetCategory) withObject:nil afterDelay:2];
                }
                else{
                    [self GetCategory];
                }
            }
        }];
        alert.disabledOutSide = YES;
        [alert show];
    }
    else if (!__iOS7 && !CMGlobal::TheOne().IsExistNetwork()) {
        [self performSelector:@selector(GetCategory) withObject:nil afterDelay:2];
    }
    else{
        [self GetCategory];
    }
    
    //TODO: 更新label
}

-(void)GetMyinfo
{
	if(!m_pMyinfoListener)
		m_pMyinfoListener = new CMMyInfoListener();
	CMMyInfo::GetInstance()->SetListener(m_pMyinfoListener, NULL);
	CMMyInfo::GetInstance()->SetUserData(BridgeObjectToC(self));
    
}


-(void)GetCategory
{
    self.loadingStatelbl.text=I(@"获取栏目信息...");
	m_pLogin->SetUserData(NULL);
	
	if (!m_pCategoryLister) {
		m_pCategoryLister = new CMCategoryLister();
	}
	
	if (!m_pCategory) {
		m_pCategory = CMCategory::GetInstance();
	}
	
	assert(m_pCategory);
	m_pCategory->SetUserData(BridgeObjectToC(self));
	m_pCategory->SetListener(m_pCategoryLister);
    
    m_pCategory->UpdateCategoryList();
   
    
    //CMMyInfo::GetInstance()->RefereshCache();
    
    
}

-(void)DoCategory
{
    if(m_pCategory)
    {
        for(int i=0;i<m_pCategory->TopItemCount();i++) {
            CMCategoryItem* pCategoryItem = CMCategory::GetInstance()->GetTopItem(i);
            assert(pCategoryItem);
            
            NSString* strType	= [NSString stringWithUTF8String:pCategoryItem->sType];
            
            //找到"更多"目录
            if ([strType caseInsensitiveCompare:@"app"] == 0)
            {
                CMCategoryItem* tempCategoryItem = CMCategory::GetInstance()->GetTopItem(i);
                
                
                for (int q=0; q<tempCategoryItem->FrontChildItemCount(); q++) {
                    
                    CMCategoryItem* m_pCategoryChildItem = tempCategoryItem->GetChildItem(q);
                    assert(m_pCategoryChildItem);
                    
                    NSString* temp = [NSString stringWithUTF8String:m_pCategoryChildItem->sType];
                    if ([temp caseInsensitiveCompare:@"coursewetools"] == 0)
                    {
                        tempCategoryItem->RemoveChildItem(q);
                        //干掉we工具
                        
                    }
                }
                
            }
            
        }
        

    }
    
}

-(void)loginStart
{
	//bool ret;
	
	//NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
	
}

- (void)sendDeviceToken
{
    device = [[CMPushMessage alloc]init];
	
	[device inits];
	
    MLPlayerAppDelegate *app = [[UIApplication sharedApplication] delegate];
    
    if (app->g_strDeviceToken && ![app->g_strDeviceToken isEqualToString:@""])
    {
        [device SendDeviceTokey:app->g_strDeviceToken];
    }
}


// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
 - (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
 self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
 if (self) {
 // Custom initialization.
 }
 return self;
 }
 */


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
	UIImage *myImage = [UIImage imageNamed:@"sysbackground.png"];
	
	CGSize sizes = CGSizeMake(UI_IOS_WINDOW_WIDTH,UI_IOS_WINDOW_HEIGHT);
	
	CMImage *image = [[CMImage alloc] init];
	
	myImage = [image imageWithImage:myImage scaledToSize:sizes];
	
	[self.view setBackgroundColor:[UIColor colorWithPatternImage:myImage]];
	
    
	//self.view.frame.size.height -=20;
    self.view.frame.size = CGSizeMake(self.view.frame.size.width, self.view.frame.size.height - 20);
    
//	UIImage *sysimage = [UIImage imageNamed:@"syslog_2.png"];
	
    //去掉字符
//	UIImageView* imageViewlog = [[UIImageView alloc] initWithImage:sysimage];
//	imageViewlog.frame=CGRectMake((UI_IOS_WINDOW_WIDTH-sysimage.size.width)/2, 80, sysimage.size.width, sysimage.size.height);
////	[self.view addSubview:imageViewlog];
//    //[image release];
//	[imageViewlog release];
//	
//    
    //去掉字符
//	UIImage *myimage = [UIImage imageNamed:@"loadingSlogan.png"];
//	UIImageView* imageViewSlogan = [[UIImageView alloc] initWithImage:myimage];
//	imageViewSlogan.frame=CGRectMake(UI_IOS_WINDOW_WIDTH/2-432/4, 152, 432/2, 36/2);
//	//[self.view addSubview:imageViewSlogan];
//    //[myimage release];
//	[imageViewSlogan release];

    
//    bigSlogan = [[UILabel alloc]init] ;
//    
//    [bigSlogan setFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-kBigSloganWidth)/2, 80, kBigSloganWidth, kBigSloganHeight)];
//    
//    [bigSlogan setTextAlignment:NSTextAlignmentCenter];
//    
//    [bigSlogan setFont:[UIFont systemFontOfSize:40]];
//    
//    [bigSlogan setTextColor:[UIColor whiteColor]];
//    
//    [bigSlogan setBackgroundColor:[UIColor clearColor]];
//    
//    [self.view addSubview:bigSlogan];
//    
//    
//    
//   smallSlogan = [[UILabel alloc]init] ;
//    CGRect smallCg= bigSlogan.frame;
//    smallCg.origin.y += 20;
//    
//    
//    [smallSlogan setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2-432/4, 152, 432/2, 36/2)];
//    
//    [smallSlogan setTextAlignment:NSTextAlignmentCenter];
//
//    [smallSlogan setFont:[UIFont systemFontOfSize:20]];
//    
//    [smallSlogan setTextColor:[UIColor whiteColor]];
//    
//    [smallSlogan setBackgroundColor:[UIColor clearColor]];
//    
//    [self.view addSubview:smallSlogan];
//    
//    
//	UIButton *BackButton= [UIButton buttonWithType:UIButtonTypeCustom];
//	
//	BackButton.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-274/2)/2, 276/2+21+136, 274/2, 91.0/2);
//	[BackButton addTarget:(id)self action:@selector(cancelBack) forControlEvents:UIControlEventTouchUpInside];
//	BackButton.tag=1000;
//    
//	[BackButton setBackgroundImage:[UIImage imageNamed:@"logoutbtn.png"] forState:UIControlStateNormal];
    
	//[self.view addSubview:BackButton];
    
    CGFloat yoff = 0;
    
    yoff = yoff + 100;
    UIImage *imaLogo_1 = [UIImage imageNamed:@"loading_logo_1"];
    imageViewLogo_1 = [[UIImageView alloc]initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH - imaLogo_1.size.width)/2, yoff, imaLogo_1.size.width, imaLogo_1.size.height)];
    imageViewLogo_1.image = imaLogo_1;
    [self.view addSubview:imageViewLogo_1];
    
    yoff = yoff + imaLogo_1.size.height + 10;
    UIImage *imaLogo_2 = [UIImage imageNamed:@"loading_logo_2"];
    imageViewLogo_2 = [[UIImageView alloc]initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH - imaLogo_2.size.width)/2, yoff, imaLogo_2.size.width, imaLogo_2.size.height)];
    imageViewLogo_2.image = imaLogo_2;
    [self.view addSubview:imageViewLogo_2];
    
    yoff = yoff + imaLogo_2.size.height + 73;
    UIImage *imaLogo_3 = [UIImage imageNamed:@"loading_logo_3"];
    imageViewLogo_3 = [[UIImageView alloc]initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH - imaLogo_3.size.width)/2, yoff, imaLogo_3.size.width, imaLogo_3.size.height)];
    imageViewLogo_3.image = imaLogo_3;
    [self.view addSubview:imageViewLogo_3];
    
    yoff = yoff + imaLogo_3.size.height + 95;
    //加入登录状态显示
#if !__has_feature(obj_arc)
    
    self.loadingStatelbl = [[UILabel alloc]initWithFrame:CGRectMake(0, yoff, UI_IOS_WINDOW_WIDTH, 20)];
#else
    self.loadingStatelbl = [[UILabel alloc]initWithFrame:CGRectMake(0, yoff, UI_IOS_WINDOW_WIDTH, 20)];
    
#endif
    self.loadingStatelbl.text=I(@"登录中...");
    
    [self.loadingStatelbl setFont:[UIFont systemFontOfSize:14]];
    
    [self.loadingStatelbl setBackgroundColor:[UIColor clearColor]];
    
    [self.loadingStatelbl setTextAlignment:NSTextAlignmentCenter];
    
    [self.loadingStatelbl setTextColor:[UIColor whiteColor]];
    
    [self.view addSubview:self.loadingStatelbl];
    
	activity = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
	activity.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2,kActivityViewCenterY);
    //CGRectMake(320/2, 276/2+21+40,10, 10);
    
	activity.backgroundColor = [UIColor clearColor];
	[self.view addSubview:activity];
	
	firstlogin = strlen(SETTING.GetServerUrl()) == 0;
	
	//[self loginStart];
	
	[tool SetIsBack:NO];
    
	m_pListener = new CMloginListener();
	m_pLogin = new CMLogin(m_pListener);
    
//    //设定公司名和标语
//
//    CMEnterpriseInfo info;
//    utf8ncpy(info.sID, [[self eid] UTF8String], 19);
//    
//    if(m_pLogin)
//        m_pLogin->GetEnterpriseInfo(info);
//    
//    if(bigSlogan)
//    {
//        if(!info.sTitle ||  strlen(info.sTitle)==0)
//            [bigSlogan setText:I(@"美课")];
//        else
//            [bigSlogan setText:[NSString stringWithUTF8String:info.sTitle]];
//    }
//
//    if(smallSlogan)
//    {
//        if(!info.sSlogan ||  strlen(info.sSlogan)==0)
//            [smallSlogan setText:I(@"轻松学习 愉悦提升")];
//        else
//            [smallSlogan setText:[NSString stringWithUTF8String:info.sSlogan]];
//    }


    
    
    //监测网络
    if (!CMGlobal::TheOne().IsExistNetwork())
    {
        activity.hidden=NO;
        [activity startAnimating];
        
        if(m_pLogin)
        {
            m_pLogin->SetUserData( BridgeObjectToC(self));
            m_pLogin->LoginOffline([[self eid] UTF8String],[[self username] UTF8String], [[self passwd] UTF8String], checkAuto);
        }
    }
    else if (self.loginType == TAGLoginTypeFromMidea)
    {
        activity.hidden=NO;
        [activity startAnimating];
        if(m_pLogin)
        {
            m_pLogin->SetUserData( BridgeObjectToC(self));
            m_pLogin->LoginByMidea("", [[self userid] UTF8String], [[self passwd] UTF8String]);
        }
    }
    else
    {
	    activity.hidden=NO;
	    [activity startAnimating];
        
	    if(m_pLogin)
	    {
		    m_pLogin->SetUserData( BridgeObjectToC(self));
            if (!userid) {
                userid = @"";
            }
//            CMString sID;
//            if (CMGlobal::TheOne().GetSessionID(sID) && checkAuto) {
//                [self OnLoginResult:0 HasNewVersion:YES];
//            }
//            else
                m_pLogin->Login([[self eid] UTF8String],[[self username] UTF8String], [[self passwd] UTF8String],[[self userid] UTF8String], checkAuto);
	    }
    }
    
    
    
}




- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
	    activity.hidden=NO;
	    [activity startAnimating];
        
	    if(m_pLogin)
	    {
		    m_pLogin->SetUserData(BridgeObjectToC(self));
		    m_pLogin->LoginOffline([[self eid] UTF8String],[[self username] UTF8String], [[self passwd] UTF8String], checkAuto);
	    }
    }
    else
    {
        [self cancelBack];
    }
}


-(void)viewWillDisappear:(BOOL)animated
{
	
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    CMEnterpriseInfo info;
    utf8ncpy(info.sID, [[self eid] UTF8String], 19);
    
    if(m_pLogin)
        m_pLogin->GetEnterpriseInfo( info);
    
//    if(bigSlogan)
//    {
//        
//        if(!info.sTitle ||  strlen(info.sTitle)==0)
//            [bigSlogan setText:I(@"美课")];
//        else
//            [bigSlogan setText:[NSString stringWithUTF8String:info.sTitle]];
//    }
//    
//    if(smallSlogan)
//    {
//        if(!info.sSlogan ||  strlen(info.sSlogan)==0)
//            [smallSlogan setText:I(@"轻松学习 愉悦提升")];
//        else
//            [smallSlogan setText:[NSString stringWithUTF8String:info.sSlogan]];
//    }

}

/*
 // Override to allow orientations other than the default portrait orientation.
 - (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
 // Return YES for supported orientations.
 return (interfaceOrientation == UIInterfaceOrientationPortrait);
 }
 */

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
	
	
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
	
	//thread =nil;
}


- (void)dealloc {
	CMRELEASE(bigSlogan);
    CMRELEASE(smallSlogan);
    
	CMRELEASE(activity);
	CMRELEASE(username);
	CMRELEASE(passwd);
    CMRELEASE(_loadingStatelbl);
	
	SAFEDELETE(m_pLogin);
	SAFEDELETE(m_pListener);
	if(m_pCategory)
	{
		m_pCategory->SetUserData(nil);
		m_pCategory->SetListener(nil);
	}
	SAFEDELETE(m_pCategoryLister);
	CMMyInfo::GetInstance()->SetUserData(nil);
	CMMyInfo::GetInstance()->SetListener(nil, nil);
	
	SAFEDELETE(m_pMyinfoListener);
    
	
}


@end
