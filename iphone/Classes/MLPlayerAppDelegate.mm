//
//  MLPlayerAppDelegate.m
//  MLPlayer
//
//  Created by sunjj on 11-5-3.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "stdafx.h"
#import "MLPlayerAppDelegate.h"
#import "CMLoginControl.h"
#import "CMPushMessage.h"
#import "CMGetNewControl.h"
//#import "MobClick.h"
#include "cmsettings.h"
#import "CMExamControl.h"
#include "CMMainControl.h"
//debug
//#import "JPushSDK/APService.h"
#import "YunBaService.h"
//debug//
#import "CMInteractViewController.h"
#include <SDL.h>
#import "CMPlayerControl.h"
#import "CMConfig.h"
#import "cmmyinfo.h"




@implementation MLPlayerAppDelegate
#define isNotIos7 (DeviceSystemMajorVersion() < 7)

@synthesize window;
@synthesize guideWindow;
@synthesize navigationController = _navigationController;
@synthesize jumpedTag;
-(void)DelayHandleRemoteNotification{
	
	downTime0 = [NSTimer scheduledTimerWithTimeInterval:3
												  target:self
												selector:@selector(startJob_0:)
												userInfo:nil
												 repeats:NO];
}

- (void)startJob_0:(NSTimer *)theTimer
{	 
	[self HandleRemoteNotification];
	CMRELEASE(downTime0);
}

NSUInteger DeviceSystemMajorVersion() {
    static NSUInteger _deviceSystemMajorVersion = -1;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _deviceSystemMajorVersion = [[[[[UIDevice currentDevice] systemVersion] componentsSeparatedByString:@"."] objectAtIndex:0] intValue];
    });
    return _deviceSystemMajorVersion;
}


- (instancetype)init
{
    self = [super init];
    if (self) {

    }
    return self;
}

void uncaughtExceptionHandler(NSException *exception) {
    NSLog(@"CRASH: %@", exception);
    NSLog(@"Stack Trace: %@", [exception callStackSymbols]);
    // Internal error reporting
}


#pragma mark -
#pragma mark XMPP

// 通知网络状态
- (void)reachabilityChanged:(NSNotification *)note {
    Reachability * reach = [note object];
    
    NSParameterAssert([reach isKindOfClass:[Reachability class]]);
    
   // NetworkStatus netStatus = [reach currentReachabilityStatus];
    
    if(![reach isReachable])
    {
        CMGlobal::TheOne().SetOffline(TRUE);
        [tool DisimissActivityIndicator];
    }
    else
    {
        CMGlobal::TheOne().SetOffline(FALSE);
    }
}


#pragma mark -
#pragma mark Application lifecycle

//- (void)umengTrack {
//	[MobClick setCrashReportEnabled:YES]; // 如果不需要捕捉异常，注释掉此行
////    [MobClick setLogEnabled:YES];  // 打开友盟sdk调试，注意Release发布时需要注释掉此行,减少io消耗
//    [MobClick setAppVersion:XcodeAppVersion]; //参数为NSString * 类型,自定义app版本信息，如果不设置，默认从CFBundleVersion里取
//	//
//    [MobClick startWithAppkey:UMENG_APPKEY reportPolicy:(ReportPolicy) SEND_ON_EXIT channelId:nil];
//    
//   // [MobClick checkUpdate];
//
//}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    
    [self handleOpenUrl:url];
    
    [self loginFromMidea];
    
    return YES;
    
//    return [self jumpToWeTool];
}

- (void)handleOpenUrl:(NSURL*)url
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSArray *schemaApartArr = [url.absoluteString componentsSeparatedByString:@"://"];
    NSString *schema = schemaApartArr[0];
    if ([schema isEqualToString:@"com.wunding.wetool"])
    {
        self.jumpedTag = TAGJumpFromWetool;
    }
    NSString *othauStr = [url.absoluteString substringFromIndex:[schema stringByAppendingString:@"://"].length];
    
    NSArray *allTags = [othauStr componentsSeparatedByString:@"&"];
    for (NSString *unitStr in allTags)
    {
        NSArray *unitArr = [unitStr componentsSeparatedByString:@"="];
        NSString *key;
        NSString *value;
        if (unitArr.count == 2)
        {
            key = unitArr[0];
            value = unitArr[1];
        }
        else
        {
            key = unitArr[0];
            value = [unitStr substringFromIndex:key.length + 1];
        }
        [ud setValue:value forKey:key];
    }
    [ud synchronize];
}

- (void)loginFromMidea
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    CMLoadingControl *loadingCtrl = [[CMLoadingControl alloc]init];
    loadingCtrl.userid = [ud objectForKey:@"uid"];
    loadingCtrl.passwd = [ud objectForKey:@"password"];
    loadingCtrl.loginType = TAGLoginTypeFromMidea;
    [self.navigationController pushViewController:loadingCtrl animated:NO];
}

- (BOOL)jumpToWeTool
{
    if (self.jumpedTag == TAGJumpFromWetool)
    {
        [tool ShowActivityIndicator:self.navigationController.view];
        
        CMString sSID ;
        
        if ( CMGlobal::TheOne().GetSessionID(sSID) ) {
            
            NSString *sid  = [NSString stringWithUTF8String:(const char *)sSID];
            
            NSString *loginname = [NSString stringWithUTF8String:SETTING.GetUserName()];
            NSString *pwd  = [NSString stringWithUTF8String:SETTING.GetUserPass()];
            NSString *server  = [NSString stringWithUTF8String:SETTING.GetServerUrl()];
            NSString *companyId = [NSString stringWithUTF8String:SETTING.GetDefautlEnterpriseID()];
            //    NSString *userName  = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetFullName()];
            
            
            NSString *oauthStr = [NSString stringWithFormat:@"%@://uid=%s&loginname=%@&sid=%@&server=%@&userName=%@&companyId=%@",WEToolSchema,defaultEid,loginname,sid,server,loginname,companyId];
            NSURL * we_appurl = [NSURL URLWithString:oauthStr];
            
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [tool DisimissActivityIndicator];
                
                [tool ShowAlert:@"授权成功，即将返回WE微课件工具"];
                
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    if ([[UIApplication sharedApplication] canOpenURL:we_appurl]) {
                        [[UIApplication sharedApplication] openURL:we_appurl];
                    }
                    else{
                        
                        //打开app store的we页面
                        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:kWetoolsDownloadUrl]];
                    }
                });
                
            });
            
            
            return YES;
        }
        else
        {
            [tool DisimissActivityIndicator];
            return NO;
        }
    }
    return NO;
}

	//用该判断程序是否用PUSH消息启动
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    //打开调试
	CMLogger::GetLogger()->SetType(CM_LOGT_CONSOLE);
#ifndef __OPTIMIZE__
    CMLogger::GetLogger()->SetLevel(CM_LOGL_DEBUG);
    kYBLogLevel = kYBLogLevelInfo;
#else
    CMLogger::GetLogger()->SetLevel(CM_LOGL_ERR);
    kYBLogLevel = kYBLogLevelNoLog;
#endif

    NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
    // 设置网络状态变化时的通知函数
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reachabilityChanged:)
                                                 name:kReachabilityChangedNotification
                                               object:nil];
    // 设置网络检测的站点
    pReachability = [Reachability reachabilityWithHostName:@"www.wdlearning.com"];
    [pReachability startNotifier];

    
    //注册webview缓存
    [NSURLProtocol registerClass:[RNCachingURLProtocol class]];
    

    
    //打开友盟
   // [self umengTrack];
    
    mGlobalListener = new CMGlobalListener_ios();
 	CMGlobalListener_ios::SetListener(mGlobalListener);

    //引导页
    self.guideWindow=[[UIWindow alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
    self.guideWindow.windowLevel=UIWindowLevelStatusBar+1;
    
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0)
    {
        //设置tabbar选中时图片图片和文字颜色
        self.window.tintColor = UIColorRGB(0x1a6cc3);
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault animated:YES];
    }
    else
    {
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault animated:YES];
    }
    
    [UIApplication sharedApplication].applicationSupportsShakeToEdit = YES;
	[[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
    self.window.rootViewController.view.layer.cornerRadius = 5;
    self.window.rootViewController.view.layer.masksToBounds = YES;
    
    
	CMLoginControl * loginControl = [[CMLoginControl alloc] init];

	_navigationController = [[UINavigationController alloc] initWithRootViewController:loginControl];
	loginControl.navigationController.navigationBarHidden = YES;
    
	CMRELEASE(loginControl);
	
    
    if ([window respondsToSelector:@selector(setRootViewController:)]) {
        [self.window setRootViewController:_navigationController];
    } else {
        [self.window addSubview:_navigationController.view];
    }

    [self.window makeKeyAndVisible];
    
    //注册对http的缓存处理

	_isActive = NO;
	_hasNotification = NO;
	_bShowAlert = NO;
	
	//注册启动PUSH
    [application setApplicationIconBadgeNumber:0];


	//看是否有push notification到达
    // Required
    //debug
    //#if __IPHONE_OS_VERSION_MAX_ALLOWED > __IPHONE_7_1
    //    if ([[UIDevice currentDevice].systemVersion floatValue] >= 8.0) {
    //        //可以添加自定义categories
    //        [APService registerForRemoteNotificationTypes:(UIUserNotificationTypeBadge |
    //                                                       UIUserNotificationTypeSound |
    //                                                       UIUserNotificationTypeAlert)
    //                                           categories:nil];
    //    } else {
    //        //categories 必须为nil
    //        [APService registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge |
    //                                                       UIRemoteNotificationTypeSound |
    //                                                       UIRemoteNotificationTypeAlert)
    //                                           categories:nil];
    //    }
    //#else
    //    //categories 必须为nil
    //    [APService registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge |
    //                                                   UIRemoteNotificationTypeSound |
    //                                                   UIRemoteNotificationTypeAlert)
    //                                       categories:nil];
    //#endif
    //    // Required
    //
    //    [APService setupWithOption:launchOptions];
    
    
    
    //YunBa push service
    NSString *subKey = @"";
    NSString *pubKey = @"";
    NSString *secKey = @"";
    NSString *authKey = nil;
    NSString *appKey = @"";

    
#ifdef __MLPlayer__
    subKey = @"sub-01635e37-3032-461a-bd15-c416099fdddf";
    pubKey = @"pub-295fc887-53a9-44f6-9ef4-75366cb888b9";
    secKey = @"sec-b5GiDpcgm1gUCbk8GfhjBqSlKEi9e5EmDZOWNTPwAYx7Iggx";
    authKey = nil;
    appKey = @"557f8f6127302bb315894835";
#endif

#ifdef __MideaCourse_test__
    subKey = @"sub-8eff4ec5-4085-4d4e-9a0b-5884a0b0a970";
    pubKey = @"pub-fddbb51a-4dca-4682-b9fd-3a988ab063fd";
    secKey = @"sec-2pQNVs2akQW9OuvVHVVSwcYUbJUDT7eBf57nr8EuCtKRLy6Q";
    authKey = nil;
    appKey = @"555a994c27302bb315893592";
#endif
    
#ifdef __MideaCourse_in_uat__
    subKey = @"sub-0c5a8586-2f42-4e73-ad2c-08beb0efadcd";
    pubKey = @"pub-4f70b664-9c47-4d0d-b182-4900be381017";
    secKey = @"sec-3ZdBaO9yvdcpYOt69vVeqtOAiFdiTQqAkGzhPJKHWm3PiS51";
    authKey = nil;
    appKey = @"559240460914236151255b32";
#endif
    
    YBSetupOption *option = [YBSetupOption optionWithSubKey:subKey
                                                     pubKey:pubKey
                                                     secKey:secKey
                                                    authKey:authKey];
//    [YunBaService setup];
    
    BOOL btest = [YunBaService setupWithAppkey:appKey];
    BOOL bIsSetUpSuccess = [YunBaService setupWithAppkey:appKey option:option];
    
    
    // uncomment to register for remote notification(APNs)     //注册APNs，申请获取device token
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings
                                                                             settingsForTypes:(UIUserNotificationTypeSound | UIUserNotificationTypeAlert | UIUserNotificationTypeBadge) categories:nil]];
        [[UIApplication sharedApplication] registerForRemoteNotifications];
    }
    else
    {
        [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
    }
    
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onMessageReceived:) name:kYBDidReceiveMessageNotification object:nil];
    
    
    //debug//

    
	if(launchOptions) {
		NSDictionary* remoteNotification = [launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
		if (remoteNotification) {
			[self application:application didReceiveRemoteNotification:remoteNotification];
		}
	}
    
    SDL_SetMainReady();
    
    
    self.faceBoard = [[FaceBoard alloc]init];
    self.faceBoard.backgroundColor = [UIColor clearColor];
    
    {
        //添加摇一摇视图
        UIImageView *pImgUp = [[UIImageView alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-125)/2, UI_IOS_WINDOW_HEIGHT/2-100, 125, 100)];
        pImgUp.backgroundColor = [UIColor clearColor];
        pImgUp.image = [UIImage imageNamed:@"shakeup"];
        
        self.m_pImgUp = [[UIView alloc] initWithFrame:CGRectMake(0, -UI_IOS_WINDOW_HEIGHT/2, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT/2)];
        self.m_pImgUp.backgroundColor = [UIColor colorWithRed:38/255.0 green:38/255.0 blue:38/255.0 alpha:1.0];
        self.m_pImgUp.hidden=YES;
        [self.m_pImgUp addSubview:pImgUp];
        [self.window addSubview:self.m_pImgUp];
        
        UIImageView *pImgDown = [[UIImageView alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-125)/2, 0, 125, 100)];
        pImgDown.backgroundColor = [UIColor clearColor];
        pImgDown.image = [UIImage imageNamed:@"shakedown"];
        
        self.m_pImgDown = [[UIView alloc] initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT/2)];
        self.m_pImgDown.backgroundColor = [UIColor colorWithRed:38/255.0 green:38/255.0 blue:38/255.0 alpha:1.0];
        self.m_pImgDown.hidden=YES;
        [self.m_pImgDown addSubview:pImgDown];
        [self.window addSubview:self.m_pImgDown];
    }

    
	return YES;
}

- (void)bindPushTagsAndAlias
{
    if (!CMMyInfo::GetInstance()->CompareTags()) {
        NSString *tags  = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetTags()];
        NSArray  *alltags = [tags componentsSeparatedByString:@"|"];
        
        if([tags length]>0)
        {
            
            for (NSString *tag in alltags)
            {
                [YunBaService subscribe:tag resultBlock:^(BOOL succ, NSError *error) {
                    if (!succ)
                    {
                        CM_ERRP("set alias failed due to : %@, recovery suggestion: %@", error, [error localizedRecoverySuggestion]);
                    }
                }];
            }
            
        }
    }
    
    NSString *alias = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetUid()];
    if ([alias length]>0)
    {
        [YunBaService setAlias:alias resultBlock:^(BOOL succ, NSError *error) {
            if (!succ)
            {
                CM_ERRP("set alias failed due to : %@, recovery suggestion: %@", error, [error localizedRecoverySuggestion]);
            }
        }];
    }
    

    
}


- (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    //debug
    //[APService registerDeviceToken:deviceToken];
    
    NSLog(@"get Device Token: %@", [NSString stringWithFormat:@"Device Token: %@", deviceToken]);
    // uncomment to store device token to YunBa
    [YunBaService storeDeviceToken:deviceToken resultBlock:^(BOOL succ, NSError *error) {
        if (succ) {
            NSLog(@"store device token to YunBa succ");
        } else {
            NSLog(@"store device token to YunBa failed due to : %@, recovery suggestion: %@", error, [error localizedRecoverySuggestion]);
        }
    }];
    
    //debug//
}


- (void)application:(UIApplication *)app didFailToRegisterForRemoteNotificationsWithError:(NSError *)err {
    //debug
    if ([[[UIDevice currentDevice] model] rangeOfString:@"Simulator"].location != NSNotFound) {
        NSLog(@"apns is NOT supported on simulator, run your Application on a REAL device to get device token");
    }
    
    NSLog(@"didFailToRegisterForRemoteNotificationsWithError Error: %@", err);
    //debug//
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    //debug
    //[APService handleRemoteNotification:userInfo];
    //debug//

    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    
    //作用：考试时不提示推送。先关闭，因为如果考试时程序崩掉或者杀后台，就再也无法处理推送了
    
//    if ([[ud objectForKey:@"exam"] isEqualToString:@"exam"]) {
//        return;
//    }
    
    NSDictionary *dataDic = [userInfo objectForKey:@"aps"];
    
    if (dataDic.count != 6)
    {
        [tool ShowAlert:I(@"推送消息格式错误")];
        return;
    }
	
	_hasNotification = YES;
	_bShowAlert = _isActive;
	_sNotificationText = [[NSString alloc] initWithString:[dataDic objectForKey:@"alert"]];
    NSString *pushMsg = _sNotificationText;
    NSString *pushId = [[NSString alloc] initWithString:[dataDic objectForKey:@"id"]];
    NSString *cmdtype = [[NSString alloc] initWithString:[dataDic objectForKey:@"cmdtype"]];
    NSString *cmdkeys = [[NSString alloc] initWithString:[dataDic objectForKey:@"cmdkeys"]];
    
    if (m_pushItem == nil)
    {
        m_pushItem = new TPushItem;;
    }
    
    if (pushMsg) {
        m_pushItem->sMsg = [pushMsg UTF8String];
    }
    
    if (pushId) {
        m_pushItem->sID = [pushId UTF8String];
    }
    
    if (cmdtype) {
        _sType = [[NSString alloc]initWithString:cmdtype];
        m_pushItem->sType = [cmdtype UTF8String];
    }
    if (cmdkeys) {
        _sID = [[NSString alloc]initWithString:cmdkeys];
        m_pushItem->sKey = [cmdkeys UTF8String];
    }
    m_pushItem->bIsRead = NO;
    NSDate *currTime = [NSDate date];
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"yyyy-MM-dd HH:mm"];
    NSString *strTime = [formatter stringFromDate:currTime];
    m_pushItem->sPubDate = [strTime UTF8String];
    
    CMPushMsg::GetInstance()->SetUserData(nil);
    CMPushMsg::GetInstance()->SetListener(nil);
    if (!CMPushMsg::GetInstance()->AddPushMsg(*m_pushItem))
    {
        [tool ShowAlert:I(@"推送消息存入失败")];
    }
    
    [ud setObject:_sType forKey:kUDPushType];
    [ud setObject:_sID forKey:kUDPushID];
    
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:1];
	[[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
    

    if (application.applicationState == UIApplicationStateActive) {
        // Nothing to do if applicationState is Inactive, the iOS already displayed an alert view.
        _isActive = YES;
        [self ShowNotification];
    }
    else{
        _isActive = NO;
        [self ShowNewContent];
    }
}



//debug
- (void)onMessageReceived:(NSNotification *)notification{
    YBMessage *message = [notification object];
    NSString *payloadString = [[NSString alloc] initWithData:[message data] encoding:NSUTF8StringEncoding];
    NSLog(@"[Message] %@ => %@", [message topic], payloadString);
}
//debug//

-(void)HandleRemoteNotification
{
    ;
}

-(void)ShowNotification
{
	UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:I(@"美课")
		message:_sNotificationText delegate:self cancelButtonTitle: I(@"关闭") otherButtonTitles: I(@"显示"),nil];
	if(alertView)
	{
		alertView.tag = 1;
		[alertView show];
	}
}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView.tag == 10) {
        return;
    }
	if(buttonIndex == 1 && alertView.tag == 1)
    {
        CMPushMsg::GetInstance()->Refresh(*m_pushItem);
        m_pushItem->bIsRead = YES;
        CMPushMsg::GetInstance()->Update(*m_pushItem);
        [self ShowNewContent];
    }
    else if (buttonIndex == 0 && alertView.tag == 1){
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud removeObjectForKey:kUDOpenPush];
        [ud removeObjectForKey:kUDPushID];
        [ud removeObjectForKey:kUDPushType];
    }
	else if(alertView.tag == 2)
	{
       
        
		[self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:0] animated:NO];
		
		[[NSNotificationCenter defaultCenter] postNotificationName:@"loginstate" 
															object:nil
														  userInfo:[NSDictionary dictionaryWithObject:[NSString stringWithFormat:@"%d",2]
																				   forKey:@"name"]];
	}
	CMRELEASE(alertView);
}

-(void)ShowNewContent
{
    
    CMString sID;
	if(CMGlobal::TheOne().GetSessionID(sID))
    {
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        NSString *openpush = [ud objectForKey:kUDOpenPush];
        /**
         *	判断是否连续收到推送，1，是，这时移除掉当前navigationController.viewControllers 控制器里的最后一个
         */
        if ([openpush isEqualToString:@"1"]) {
            int nRow = -1;

            for (int i = 0; i < [self.navigationController.viewControllers count]; i++)
            {
                if ([[self.navigationController.viewControllers objectAtIndex:i] isKindOfClass:[CMGetNewControl class]])
                {
                    nRow = i;
                    break;
                }
      
            }
            
            if (nRow >= 0 && nRow < [self.navigationController.viewControllers count])
            {
                NSMutableArray *pMtbArray = [[NSMutableArray alloc] initWithArray:self.navigationController.viewControllers];
                [pMtbArray removeObjectsInRange:NSMakeRange(nRow, [self.navigationController.viewControllers count] - nRow)];
                self.navigationController.viewControllers = pMtbArray;
            }
        }
        [ud setObject:@"1" forKey:kUDOpenPush];//1 打开push 0 关闭
        [ud setObject:_sType forKey:kUDPushType];
        [ud setObject:_sID forKey:kUDPushID];
        
        if ([_sType isEqualToString:@"item_category"]) {
            //do something
            [[NSNotificationCenter defaultCenter] postNotificationName:CM_NotificationCenter_ItemCategory object:nil];
        }
        else{
            
            m_pNewControl = [[CMGetNewControl alloc] init];
            m_pNewControl.title = I(@"最新推送");
            m_pNewControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            m_pNewControl.navigationController.navigationBarHidden = NO;
            m_pNewControl.tabBarController.tabBar.hidden = YES;
            m_pNewControl.hidesBottomBarWhenPushed = YES;
            m_pNewControl.sType = _sType;
            m_pNewControl.sId   = _sID;
            m_pNewControl.bAppStateIsBackground = _isActive;
            m_pNewControl.view.backgroundColor = [UIColor whiteColor];
            
            CMMainControl *mainCtrl;
            for (int i = 0; i < [self.navigationController.viewControllers count]; i++)
            {
                
                if ([[self.navigationController.viewControllers objectAtIndex:i] isKindOfClass:[CMMainControl class]])
                {
                    mainCtrl = (CMMainControl*)[self.navigationController.viewControllers objectAtIndex:i];
                    BOOL  isShowLeft = [(CMMainControl*)[self.navigationController.viewControllers objectAtIndex:i] showingLeft];
                    
                    if (isShowLeft) {
                        
                        [(CMMainControl*)[self.navigationController.viewControllers objectAtIndex:i] closeSideBar];
                        
//                        [self.navigationController pushViewController:m_pNewControl animated:NO];
                        
                        [mainCtrl.navigationController pushViewController:m_pNewControl animated:NO];
                        return;
                    }
                    
                    break;
                }
            }

//            [self.navigationController pushViewController:m_pNewControl animated:YES];
            [mainCtrl.navigationController pushViewController:m_pNewControl animated:YES];
            
        }
        
    }
    else
    {
        CMLoginControl *ctrl = (CMLoginControl*)[self.navigationController.viewControllers objectAtIndex:0];
        
        //通知登录页 在登录后跳转到推送消息界面
        ctrl.bIsPush = YES;
		
//		[[NSNotificationCenter defaultCenter] postNotificationName:@"loginstate"
//															object:nil
//														  userInfo:[NSDictionary dictionaryWithObject:@"2" forKey:@"name"]];
    }
}


-(void)OnKicked
{
    SETTING.Logout();
    SETTING.LogoutWithClearSid();

    //帐号被挤下线 清空推送标记
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    
    if (![ud boolForKey:@"isLoginSuccess"]) {
        [ud setBool:NO forKey:@"isLoginSuccess"];
    }
    else{
        
        [ud setBool:NO forKey:@"isLoginSuccess"];

        [ud removeObjectForKey:kUDOpenPush];
        [ud removeObjectForKey:kUDPushID];
        [ud removeObjectForKey:kUDPushType];
        
        [XmppHandler goOffline];
        
        //当打开左栏个人信息，被踢关闭左栏目
        for (int i = 0; i < [self.navigationController.viewControllers count]; i++)
        {
            
            if ([[self.navigationController.viewControllers objectAtIndex:i] isKindOfClass:[CMMainControl class]])
            {
                CMMainControl *mainVC = (CMMainControl*)[self.navigationController.viewControllers objectAtIndex:i];
                
                BOOL  isShowLeft = [mainVC showingLeft];
                
                if (isShowLeft) {
                    
                    [mainVC closeSideBar];
                    
                }
                break;
            }
        }
        
       	UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:I(@"美课") message:I(@"该帐号已在其他地方登录，请重新登录")                                                            delegate:self cancelButtonTitle: I(@"确定") otherButtonTitles:nil];
        if(alertView)
        {
            alertView.tag = 2;
            [alertView show];
        }
    }
}



-(void)OnRelogin
{
    SETTING.Logout();
    SETTING.LogoutWithClearSid();

    //帐号被挤下线 清空推送标记
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud removeObjectForKey:kUDOpenPush];
    [ud removeObjectForKey:kUDPushID];
    [ud removeObjectForKey:kUDPushType];
    
    
    //回到主界面
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:0] animated:NO];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"loginstate"
                                                        object:nil
                                                      userInfo:[NSDictionary dictionaryWithObject:[NSString stringWithFormat:@"%d",2]
                                                                                           forKey:@"name"]];

}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    if (self.playerController) {
        [self.playerController onPause];
    }
  //  [[NSNotificationCenter defaultCenter] postNotificationName:@"CMPlayPause" object:nil];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ExamTimePause" object:nil];
    
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    [[NSNotificationCenter defaultCenter] postNotificationName:@"CMPlayStartTimer" object:nil];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ExamTimeContinue" object:nil];
    

    
}


- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
    if (SDL_GetEventState(SDL_APP_TERMINATING) == SDL_ENABLE) {
        SDL_Event event;
        event.type = SDL_APP_TERMINATING;
        SDL_PushEvent(&event);
    }
}



#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
	
	NSLog(@"iphone --->  applicationDidReceiveMemoryWarning  内存警告！！");
    
    if (SDL_GetEventState(SDL_APP_LOWMEMORY) == SDL_ENABLE) {
        SDL_Event event;
        event.type = SDL_APP_LOWMEMORY;
        SDL_PushEvent(&event);
    }
}



- (void)dealloc {
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kReachabilityChangedNotification object:nil];
    
    if (pReachability) {
        
        [pReachability stopNotifier]; //关闭网络检测
        
        
    }
    
	CMRELEASE(device);
	CMRELEASE(_sNotificationText);
	CMRELEASE(_sType);
    CMRELEASE(_sID);
	CMGlobalListener_ios::SetListener(NULL);
	SAFEDELETE(mGlobalListener);
}


@end
