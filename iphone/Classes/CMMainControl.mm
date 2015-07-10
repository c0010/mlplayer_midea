	//
	//  CMMainControl.m
	//  iphone_Learning
	//

//  tabbar 


	//  Created by sunjj on 11-4-15.
	//  Copyright 2011 __MyCompanyName__. All rights reserved.
	//
#include "stdafx.h"
#import "CMMainControl.h"
#import "CMBrowserControl.h"
#import "CMApplicationControl.h"
#import "CMQaControl.h"
#import "CMExamControl.h"
#import "cmcategory.h"
#import "CMPersonController.h"
#import "CMGetNewControl.h"
#import "cmmyinfo.h"
//#import "JPushSDK/APService.h"
#import "CMMsgManager.h"
#import  "CMInteractViewController.h"
#import "CMCoreDataUtils.h"
#include "cmundone.h"
#import "CMLeftView.h"
#import <sys/utsname.h>
#import "CMSliderBrowseController.h"
#import "CMConfig.h"

typedef NS_ENUM(NSInteger, RMoveDirection) {
    RMoveDirectionLeft = 0,
    RMoveDirectionRight
};  //手势左右滑动方向

#define SETTAGESDELAY    5*60
#define kEnableDoubleTapTapBarToScrollingToTop  TRUE     //是否启用双击tabbar让列表滚动到最顶端的功能，若不用则置为FALSE

@implementation CustomTabBarItem
@synthesize HighlightedImage;

-(void)dealloc
{	
    CMRELEASE(HighlightedImage);
# if !__has_feature(objc_arc)
	[super dealloc];
#endif
}

- (id)initWithTitle:(NSString *)title image:(UIImage *)image tag:(NSInteger)tag{
    self = [super initWithTitle:title image:image tag:tag];
    if (self) {
        [self setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:
                                            UIColorRGB(0x8a8a8a), UITextAttributeTextColor,
                                            nil] forState:UIControlStateNormal];
        [self setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:
                                            kColorForeground, UITextAttributeTextColor,
                                            nil] forState:UIControlStateSelected];
        
    }
    return self;
}

-(UIImage *)selectedImage{
	return self.HighlightedImage;
}

@end

class CMUpdateCategoryListener:public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        ;
    };
    
    void OnUpdateDataFinish(void* UserData, int Result)
    {
        
        //刷新栏目信息
        [[NSNotificationCenter defaultCenter] postNotificationName:CM_NotificationCenter_ReloadCategory object:nil];
        
    };
    
};

@interface CMMainControl ()
{
    CMUpdateCategoryListener *m_pListener;
}

@end

@implementation CMMainControl
@synthesize bIsPush,learnNavigationController;
@synthesize moreTips;
-(void)gotoPlay:(id)sender
{	

}


-(id)init
{

 
     if (self = [super init]) {
         
         self.LeftSContentOffset=270;
         self.LeftSContentScale=0.75;
         self.LeftSJudgeOffset=100;
         self.LeftSOpenDuration=0.4;
         self.LeftSCloseDuration=0.3;
         self.minAlphaLeftView = 0.01f;
         self.minScaleLeftView = .8f;
         self.canShowLeft=YES;
    
//	//应用 系统设置按钮
//	UIButton* modalViewButton = [UIButton buttonWithType:UIButtonTypeInfoLight];
//	[modalViewButton addTarget:self action:@selector(gotoSettings) forControlEvents:UIControlEventTouchUpInside];	
//	UIBarButtonItem *appBarButtonItem = [[UIBarButtonItem alloc]initWithCustomView:modalViewButton];
//
# if ! __has_feature(objc_arc)
    NSMutableArray *localControllersArray =	[[[NSMutableArray alloc] initWithCapacity:6] autorelease];
#else
      NSMutableArray *localControllersArray =	[[NSMutableArray alloc] initWithCapacity:6];
#endif
         
	for(int i=0;i<CMCategory::GetInstance()->TopItemCount();i++) {
		
		CMCategoryItem* pCategoryItem = CMCategory::GetInstance()->GetTopItem(i);
		assert(pCategoryItem);
		
		NSString* strType	= [NSString stringWithUTF8String:pCategoryItem->sType];
		NSInteger m_sID		= i;//atoi(m_pCategoryItem->sID);
		NSString* m_sTitle	= [NSString stringWithUTF8String:pCategoryItem->sTitle];
		CustomTabBarItem* tabbaritem =  [[CustomTabBarItem alloc] initWithTitle:m_sTitle  image:nil  tag:i];
		if([strType caseInsensitiveCompare:@"course"] == 0|| [strType caseInsensitiveCompare:@"news"] == 0 || [strType caseInsensitiveCompare:@"kb"] == 0) {
			//CMBrowserControl* learnController = [[CMBrowserControl alloc] init];
            CMSliderBrowseController* learnController = [[CMSliderBrowseController alloc] init];
            learnController.bIsShowTabbar = YES;
            learnController.bIsShowTagbar = YES;
			UINavigationController* pNavigationController = nil;
			if([strType caseInsensitiveCompare:@"course"] == 0)
			{
				tabbaritem.image = [UIImage imageNamed:@"TabLearning_n"];
				tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabLearning_p"];
                tabbaritem.selectedImage = [UIImage imageNamed:@"TabLearning_p"];
                learnController.openShake = YES;

				learnNavigationController = [[UINavigationController alloc] init];
				pNavigationController = learnNavigationController;
			}
			else if([strType caseInsensitiveCompare:@"news"] == 0)
			{
				tabbaritem.image = [UIImage imageNamed:@"TabNews_n"];
				tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabNews_p"];
                tabbaritem.selectedImage = [UIImage imageNamed:@"TabNews_p"];
				newsNavigationController = [[UINavigationController alloc] init];
				pNavigationController = newsNavigationController;
			}
			else if([strType caseInsensitiveCompare:@"kb"] == 0)
			{
				tabbaritem.image = [UIImage imageNamed:@"TabNews_n"];
				tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabNews_p"];
                tabbaritem.selectedImage = [UIImage imageNamed:@"TabNews_p"];
				knowledgeNavigationController = [[UINavigationController alloc] init];
				pNavigationController = knowledgeNavigationController;
			}

			learnController.tabBarItem = tabbaritem;
			learnController.navigationController.navigationBarHidden = NO;
			[learnController.navigationItem setTitle:m_sTitle];

			[learnController setFlag:pCategoryItem->sType];
			
			[pNavigationController pushViewController:learnController animated:NO];			
 			[localControllersArray addObject:pNavigationController];	
            CMRELEASE(learnController);

        }
        else if([strType caseInsensitiveCompare:@"qa"] == 0)
        {
            //CMExamControl * examControl = [[CMExamControl alloc] init];
            
            CMQaControl* qaControl = [[CMQaControl alloc] init];
           // qaControl.title = I(@"全部");//全部问答
            qaControl.bIsShowTabbar = YES;
            qaControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
            qaControl.navigationController.navigationBarHidden = YES;
            qaControl.tabBarController.tabBar.hidden = NO;
            qaControl.hidesBottomBarWhenPushed = NO;
            
            qaControl.tabBarItem = tabbaritem;
            
            
            tabbaritem.image = [UIImage imageNamed:@"TabQa_n"];
            tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabQa_p"];
            tabbaritem.selectedImage = [UIImage imageNamed:@"TabQa_p"];
            qaControl.title = m_sTitle;
            qaNavController = [[UINavigationController alloc] init];
            qaNavController.navigationController.navigationBarHidden=NO;
            [qaNavController pushViewController:qaControl animated:NO];
            [localControllersArray addObject:qaNavController];
            CMRELEASE(qaControl);
        }
        else if ([strType caseInsensitiveCompare:@"interaction"] == 0) {
				//互动

            CMInteractViewController *interactController = [[CMInteractViewController alloc]init];
        	interactController.tabBarItem =  tabbaritem;
            interactController.bIsShowTabbar = YES;

            tabbaritem.image = [UIImage imageNamed:@"TabInteract_n"];
            tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabInteract_p"];
            tabbaritem.selectedImage = [UIImage imageNamed:@"TabInteract_p"];
            tabbaritem.tag = InteractItemTag;
			tabbaritem.title = m_sTitle;
    
            [CMCoreDataUtils updateBadgeValueWithTabBar:interactController.tabBarItem];//设置互动未读消息

			interactNavigationController = [[UINavigationController alloc] init];
			interactNavigationController.navigationController.navigationBarHidden=NO;
			[interactController.navigationItem setTitle:m_sTitle];

            XmppHandler.interactNavigationController = interactNavigationController;
            
			 [interactNavigationController pushViewController:interactController animated:NO];
			[localControllersArray addObject:interactNavigationController];
            CMRELEASE(interactController);
		}
		else if([strType caseInsensitiveCompare:@"exam"] == 0)
		{
			//CMExamControl * examControl = [[CMExamControl alloc] init];
            
            CMExamControl * examControl = [[CMExamControl alloc] init];
            examControl.bIsShowTabbar = YES;

			examControl.tabBarItem = tabbaritem;

            //缺少判断 当前是否有未完成的测验
            if (CMMyInfo::GetInstance()->GetUndoExam() > 0)
            {
                examTips = [[UIImageView alloc] initWithFrame:CGRectMake(i*(UI_IOS_WINDOW_WIDTH/ CMCategory::GetInstance()->TopItemCount()) + 40, 2, 10, 10)];
                examTips.backgroundColor = [UIColor clearColor];
                examTips.image = [UIImage imageNamed:@"newTips"];
                [self.tabBar addSubview:examTips];
                strExam = m_sTitle;
            }
            
			tabbaritem.image = [UIImage imageNamed:@"TabExam_n"];
			tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabExam_p"];
            tabbaritem.selectedImage = [UIImage imageNamed:@"TabExam_p"];
			examControl.title = m_sTitle;
			examNavController = [[UINavigationController alloc] init];    
			examNavController.navigationController.navigationBarHidden=NO;
			[examNavController pushViewController:examControl animated:NO];
			[localControllersArray addObject:examNavController];
            CMRELEASE(examControl);
		}
		else if([strType caseInsensitiveCompare:@"mycenter"] == 0)
		{
//            CMPersonController* personControl = [[CMPersonController alloc] init];
//            personControl.tabBarItem = tabbaritem;
//            tabbaritem.image = [UIImage imageNamed:@"TabMycenter_n"];
//            tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabMycenter_p"];
//            tabbaritem.selectedImage = [UIImage imageNamed:@"TabMycenter_p"];
//			personControl.title = m_sTitle;
//            mycenterController = [[UINavigationController alloc] init];
//            mycenterController.navigationController.navigationBarHidden=NO;
//            [mycenterController pushViewController:personControl animated:NO];
//            [localControllersArray addObject:mycenterController];
//            CMRELEASE(personControl);
		}
        else if ([strType caseInsensitiveCompare:@"apply"] == 0) {
            
            CMApplicationControl* appController = [[CMApplicationControl alloc] init];
            appController.bIsShowTabbar = YES;

            //当前有未完成的调研时提示
//            for (int j = 0; j < pCategoryItem->ChildItemCount(); j++)
//            {
//                CMCategoryItem *item = pCategoryItem->GetChildItem(j);
//                
//                if ((strcmp(item->sType,"survey") == 0 && item->nItemcount > 0) || ![tool hasClickedWE] || CMMyInfo::GetInstance()->GetNoSigninCount()>0)
//                {
                    moreTips = [[UIImageView alloc] initWithFrame:CGRectMake(i*(UI_IOS_WINDOW_WIDTH/ CMCategory::GetInstance()->TopItemCount()) + 40, 2, 10, 10)];
                    moreTips.backgroundColor = [UIColor clearColor];
                    moreTips.image = [UIImage imageNamed:@"newTips"];
                    [self.tabBar addSubview:moreTips];
                    strMore = m_sTitle;
                    moreTips.hidden = YES;
//                    break;
//                }
//            }
        
			appController.tabBarItem =  tabbaritem;
			tabbaritem.image = [UIImage imageNamed:@"TabApp_n"];
			tabbaritem.HighlightedImage = [UIImage imageNamed:@"TabApp_p"];
            tabbaritem.selectedImage = [UIImage imageNamed:@"TabApp_p"];
			appNavigationController = [[UINavigationController alloc] init];
			//appNavigationController.navigationController.navigationBarHidden=NO;
			//appController.navigationItem.rightBarButtonItem =appBarButtonItem;
			[appController.navigationItem setTitle:m_sTitle];
			appController.Parentid = m_sID;
			appController.strTitle = m_sTitle;
			
			[appNavigationController pushViewController:appController animated:NO];
			[localControllersArray addObject:appNavigationController];
            CMRELEASE(appController);
			
		} 
        CMRELEASE(tabbaritem);
	} 
	self.viewControllers = localControllersArray;
     }
	
    return self;
}

//更新栏目分类
- (void)UpdateCategoryList{
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    
    NSString *everyDayFirstlaunch = [ud objectForKey:@"EveryDayFirstLaunch"];
    
    NSDate *  senddate=[NSDate date];
    
    NSDateFormatter  *dateformatter=[[NSDateFormatter alloc] init];
    
    [dateformatter setDateFormat:@"YYYYMMdd"];
    
    NSString *  locationString=[dateformatter stringFromDate:senddate];
    
    
    if(!everyDayFirstlaunch || ![everyDayFirstlaunch isEqualToString:locationString]){
        CMString sid;
        if (CMGlobal::TheOne().GetSessionID(sid)) {
            if (!m_pListener) {
                m_pListener = new CMUpdateCategoryListener();
            }
            
            CMCategory::GetInstance()->SetUserData(BridgeObjectToC(self));
            CMCategory::GetInstance()->SetListener(m_pListener);
            CMCategory::GetInstance()->UpdateCategoryList();
            
            [self requestUnDone];

        }
        [ud setObject:locationString forKey:@"EveryDayFirstLaunch"];
    }
    
    [ud synchronize];
}

- (void)requestUnDone{
    CMUnDone *m_pUnDone = CMUnDone::GetInstance();
    m_pUnDone->SetUserData(BridgeObjectToC([GlobalAlertCenter sharedAlertCenter]));
    m_pUnDone->SetListener([[GlobalAlertCenter sharedAlertCenter] GetUpdateDataCallBack]);
    [[GlobalAlertCenter sharedAlertCenter] setType:CM_NotificationCenter_ReloadView];
    
    CMUnDone::GetInstance()->GetUnDone();
}

- (void)updateView{
    
    for(int i=0;i<CMCategory::GetInstance()->TopItemCount();i++) {
        
        CMCategoryItem* pCategoryItem = CMCategory::GetInstance()->GetTopItem(i);
        assert(pCategoryItem);
        
        NSString* strType	= [NSString stringWithUTF8String:pCategoryItem->sType];
        if ([strType caseInsensitiveCompare:@"app"] == 0){
            for (int j = 0; j < pCategoryItem->ChildItemCount(); j++)
            {
                CMCategoryItem *item = pCategoryItem->GetChildItem(j);
                
                if (((strcmp(item->sType,"survey") == 0 && item->nItemcount > 0) || (strcmp(item->sType,"train_signin") == 0 && item->nItemcount > 0) || ![tool hasClickedWE] ) && self.selectedIndex != i)
                {
                    moreTips.hidden = NO;
                }
            }
        }
    }
}

- (void)viewDidLoad
{
	[super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateView) name:CM_NotificationCenter_ReloadView object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(UpdateCategoryList) name:UIApplicationDidBecomeActiveNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(requestUnDone) name:CM_NotificationCenter_ItemCategory object:nil];

    
    self.canShowLeft = YES;
    if(self.canShowLeft){

        MLPlayerAppDelegate* appdelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];

        //寻找view的superview
        for(UIView *v in appdelegate.window.subviews)
        {
            if([[[v class] description] isEqualToString:@"UILayoutContainerView"])
                _mainContentView=v;
        }
    
        bgView = (UIImageView*)[appdelegate.window viewWithTag:199999];
        //加入左视图
        _leftSideView = [[CMLeftView alloc] initWithFrame:self.view.bounds];
        if (bgView) {
            [bgView removeFromSuperview];
        }

        bgView = [[UIImageView alloc] initWithFrame:self.view.bounds];
        bgView.hidden = NO;
        //UIImage *image = (UI_IOS_WINDOW_HEIGHT > 480) ? [UIImage imageNamed:@"personcenter_widen"] : [UIImage imageNamed:@"personcenter_widen"];
        UIImage *image = [UIImage imageNamed:@"personcenter_widen"];
        
        bgView.tag = 199999;
        [bgView setImage:image];
        bgView.userInteractionEnabled = YES;
        [bgView addSubview:_leftSideView];
        _leftSideView.backgroundColor = [UIColor clearColor];
        [_leftSideView refreshMyInfo:NO];
        _leftSideView.navigationcontrollerdelegate = self;
        
        [appdelegate.window insertSubview:bgView atIndex:0];
     
        _leftSideView.alpha = self.minAlphaLeftView;
        
        _leftSideView.transform = CGAffineTransformMakeScale(self.minScaleLeftView, self.minScaleLeftView);
    
        //点击手势
        _tapGestureRec = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(closeSideBar)];
        _tapGestureRec.delegate=self;
        _tapGestureRec.enabled=NO;
        [self.view addGestureRecognizer:_tapGestureRec];
        
        _centerButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_centerButton setBackgroundColor:[UIColor clearColor]];
        _centerButton.frame = self.view.bounds;
        [self.view addSubview:_centerButton];
        [_centerButton addTarget:self action:@selector(closeSideBar) forControlEvents:UIControlEventTouchUpInside];
        _centerButton.hidden = YES;
        
        //滑动手势
        _panGestureRec = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(moveViewWithGesture:)];
        _panGestureRec.delegate=self;
        _panGestureRec.enabled = NO;
        [_mainContentView addGestureRecognizer:_panGestureRec];
        
        
        if (kEnableDoubleTapTapBarToScrollingToTop) {
            //添加单击手势识别器
            UITapGestureRecognizer *singleTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleSingleTap:)];
            singleTapGestureRecognizer.numberOfTapsRequired = 1;
            [self.tabBar addGestureRecognizer:singleTapGestureRecognizer];
            
            //添加双击手势识别器
            UITapGestureRecognizer *doubleTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleDoubleTap:)];
            doubleTapGestureRecognizer.numberOfTapsRequired = 2;
            [self.tabBar addGestureRecognizer:doubleTapGestureRecognizer];
        }
    }
    
    [[UITabBar appearance] setSelectedImageTintColor: kColorForeground];

    if ([self.tabBar respondsToSelector:@selector(setBarTintColor:)]) {
        [self.tabBar setBarTintColor:UIColorRGB(0xf7f7f7)];
    }else{
        UIView *back = [[UIView alloc]initWithFrame:self.tabBar.bounds];
        back.backgroundColor = UIColorRGB(0xf7f7f7);
        UIView *seqView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 320, 0.5)];
        seqView.backgroundColor = UIColorRGB(0xafafaf);
        [back addSubview:seqView];
        [self.tabBar addSubview:back];
        
        for (UIView *subView in self.tabBar.subviews) {
            if ([subView isKindOfClass:NSClassFromString(@"UIImageView")]) {
                [subView removeFromSuperview];               
            }
            if ([subView isKindOfClass:NSClassFromString(@"_UITabBarBackgroundView")]) {
                [subView removeFromSuperview];
            }
        }
        CMRELEASE(back);
        CMRELEASE(seqView);
    }
    
    [self requestUnDone];
    
    [AppDelegate jumpToWeTool];
}

- (void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(setTagsAlias) object:nil];
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSString *openpush = [ud objectForKey:kUDOpenPush];
    if ([openpush isEqualToString:@"1"]) {
        NSString *type = [ud objectForKey:kUDPushType];
        NSString *sid = [ud objectForKey:kUDPushID];
        if ([type isEqualToString:@"position_course"]) {
            return;
        }
        else{
            CMGetNewControl*  browserControl=[[CMGetNewControl alloc] init];
            browserControl.title = I(@"最新推送");
            browserControl.tabBarController.tabBar.hidden = YES;

            browserControl.bAppStateIsBackground = bIsPush;
            browserControl.sType = type;
            browserControl.sId = sid;
            [self.navigationController pushViewController:browserControl animated:NO];
            CMRELEASE(browserControl);
        }
    }
    [ud removeObjectForKey:kUDOpenPush]; //即时关闭判断，避免页面跳转错乱
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    
//    [self setTagsAlias];
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSString *openpush = [ud objectForKey:kUDOpenPush];
    
    if ([openpush isEqualToString:@"1"]) {
        self.navigationController.navigationBarHidden = NO;
    }
    else{
        self.navigationController.navigationBarHidden = YES;
    }
    
    [ud setBool:YES forKey:@"isLoginSuccess"];  //记录登陆状态，避免多次弹框
    
}

//#pragma mark -----------------------绑定极光推送tags alias--------------------------------
//- (void)setTagsAlias{
//    if (!CMMyInfo::GetInstance()->CompareAlias() || !CMMyInfo::GetInstance()->CompareTags()) {
//        NSString *alias = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetUid()];
//        NSString *tags  = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetTags()];
//        NSArray  *alltags = [tags componentsSeparatedByString:@"|"];
//        
//        if([alias length]>0 || [tags length]>0)
//            [APService setTags:[NSSet setWithArray:alltags] alias:alias callbackSelector:@selector(tagsAliasCallback:tags:alias:) target:self];
//    }
//}
//
//- (void)tagsAliasCallback:(int)iResCode tags:(NSSet*)tags alias:(NSString*)alias {
//    if (iResCode == 0) {
//        return;
//    }
//    else{
//        [self performSelector:@selector(setTagsAlias) withObject:nil afterDelay:SETTAGESDELAY];
//        CM_ERRP("tagsAliasCallback rescode: %d,\ntags: %s, \nalias: %s\n", iResCode,[[[tags allObjects] componentsJoinedByString:@"|"] UTF8String],[alias UTF8String]);
//    }
//}

#pragma mark －－－－－－－－－－－－－－左滑视图实现方法－－－－－－－－－－－－－－－－－－－－－－－－－
- (void)isForbidGesture:(BOOL)isForbid{
    if (_panGestureRec) {
        _panGestureRec.enabled = !isForbid;
    }
}


- (void)closeSideBar{
    CGAffineTransform oriT = CGAffineTransformIdentity;
    [UIView animateWithDuration:_LeftSCloseDuration
                     animations:^{
                         _mainContentView.transform = oriT;
                         _leftSideView.alpha = self.minAlphaLeftView;
                         
                         _leftSideView.transform = CGAffineTransformMakeScale(self.minScaleLeftView, self.minScaleLeftView);
          
                         [self setBrowserLeftAlpha:1];
                     }
                     completion:^(BOOL finished) {
                         _tapGestureRec.enabled = NO;
                         _showingLeft=NO;
                         _centerButton.hidden = YES;
                         
                         bgView.hidden = YES;

                         [[NSNotificationCenter defaultCenter]postNotificationName:LeftVcFinishMove object:nil];

                     }];
}

- (void)openSideBar{
    
    if (_showingLeft) {
        [self closeSideBar];
        return;
    }
    
    bgView.hidden = NO;

    if (!_canShowLeft) {
        return;
    }
    CGAffineTransform conT = [self transformWithDirection:RMoveDirectionRight];
    
    [self configureViewShadowWithDirection:RMoveDirectionRight];
    
    _showingLeft=YES;
    
    [UIView animateWithDuration:_LeftSOpenDuration
                     animations:^{
                         _mainContentView.transform = conT;
                         
                         _leftSideView.alpha = 1.f;
                         
                         _leftSideView.transform = CGAffineTransformMakeScale(1.f, 1.f);
                         
                         [self setBrowserLeftAlpha:0];

                     }
                     completion:^(BOOL finished) {
                         [self openAnimateSuccess];
                      //   [[NSNotificationCenter defaultCenter]postNotificationName:LeftVcFinishMove object:nil];
                         
                     }];


}

- (void)closeAnimateSuccess{
    bgView.hidden = YES;
}

- (void)openAnimateSuccess{
    _tapGestureRec.enabled = YES;
    _centerButton.hidden = NO;
    _showingLeft=YES;
    bgView.hidden = NO;
    _panGestureRec.enabled = YES;
    [_leftSideView refreshHeadImageView];
    [_leftSideView refreshMyInfo:YES];
}

- (void)moveViewWithGesture:(UIPanGestureRecognizer *)panGes{
    
    bgView.hidden = NO;
    
    static CGFloat currentTranslateX;
    if (panGes.state == UIGestureRecognizerStateBegan)
    {
        currentTranslateX = _mainContentView.transform.tx;
    }
    if (panGes.state == UIGestureRecognizerStateChanged)
    {
        CGFloat transX = [panGes translationInView:_mainContentView].x;
        transX = transX + currentTranslateX;
        
        CGFloat sca=0;
        CGFloat sleftca=0;
        CGFloat aleftca=0;
        CGFloat aNavLeft=0;
        
        if (transX > 0 && transX < self.LeftSContentOffset)
        {
            if (!_canShowLeft) {
                return;
            }
            
            [self configureViewShadowWithDirection:RMoveDirectionRight];
            
            if (_mainContentView.frame.origin.x < _LeftSContentOffset)
            {
                sca = 1 - (_mainContentView.frame.origin.x/_LeftSContentOffset) * (1-_LeftSContentScale);
                sleftca = 1 - ((1 - self.minScaleLeftView) + ((_mainContentView.frame.origin.x/_LeftSContentOffset) * (-1+self.minScaleLeftView)));
                aleftca = 1 - ((1 - self.minAlphaLeftView) + ((_mainContentView.frame.origin.x/_LeftSContentOffset) * (-1+self.minAlphaLeftView)));
                aNavLeft = 1 - (_mainContentView.frame.origin.x/_LeftSContentOffset);

            }
            else
            {
                sca = _LeftSContentScale;
                sleftca = 1.0;
                aleftca = 1.0;
                aNavLeft = 0;
            }
        }
        else
        {
            return;
        }
        
        if (sleftca < self.minScaleLeftView)
            sleftca = self.minScaleLeftView;
        
        if (sca > 1.f)
            sca = 1.f;
        
        CGAffineTransform transS = CGAffineTransformMakeScale(sca, sca);
        CGAffineTransform transT = CGAffineTransformMakeTranslation(transX, 0);
        
        CGAffineTransform conT = CGAffineTransformConcat(transT, transS);
        
        _mainContentView.transform = conT;
        
        _leftSideView.alpha = aleftca;
        
        _leftSideView.transform =  CGAffineTransformMakeScale(sleftca, sleftca);
        
        [self setBrowserLeftAlpha:aNavLeft];
        
    }
    else if (panGes.state == UIGestureRecognizerStateEnded)
    {
        CGFloat panX = [panGes translationInView:_mainContentView].x;
        CGFloat finalX = currentTranslateX + panX;
        if (finalX > _LeftSJudgeOffset)
        {
            
            if (!_canShowLeft) {
                return;
            }
            UIView *view = self.view;
            CGRect frame = self.view.bounds;
            view.frame = frame;
            
            CGAffineTransform conT = [self transformWithDirection:RMoveDirectionRight];
            [UIView beginAnimations:nil context:nil];
            
            _mainContentView.transform = conT;
            _leftSideView.alpha = 1.f;
            _leftSideView.transform = CGAffineTransformMakeScale(1.f, 1.f);
 
            [self setBrowserLeftAlpha:0];

            [UIView commitAnimations];
            
            [self openAnimateSuccess];
            
            return;
        }
        else
        {
            CGAffineTransform oriT = CGAffineTransformIdentity;
            [UIView beginAnimations:nil context:nil];
            _mainContentView.transform = oriT;
            _leftSideView.alpha = self.minAlphaLeftView;
            _leftSideView.transform = CGAffineTransformMakeScale(self.minScaleLeftView, self.minScaleLeftView);
            
            [self setBrowserLeftAlpha:1];
            [UIView commitAnimations];
            
            [self performSelector:@selector(closeAnimateSuccess) withObject:nil afterDelay:.2f];
            
            _showingLeft=NO;
            _tapGestureRec.enabled = NO;
            _centerButton.hidden = YES;
        }
        [[NSNotificationCenter defaultCenter]postNotificationName:LeftVcFinishMove object:nil];

    }

}

- (void)setBrowserLeftAlpha:(CGFloat)alpha{
//    CMBrowserControl *browserCtr1 = [[learnNavigationController viewControllers] objectAtIndex:0];
//    if(browserCtr1){
//        browserCtr1.leftButton.alpha = alpha;
//    }
    
    CMSliderBrowseController *browserCtr2 = [[learnNavigationController viewControllers] objectAtIndex:0];
    if (browserCtr2) {
        browserCtr2.leftButton.alpha = alpha;
    }
    
//    CMBrowserControl *browserCtr2 = [[newsNavigationController viewControllers] objectAtIndex:0];
//    if (browserCtr2) {
//        browserCtr2.leftButton.alpha = alpha;
//    }
}


#pragma mark ------------------CGAffineTransform---------------

- (CGAffineTransform)transformWithDirection:(RMoveDirection)direction
{
    CGFloat translateX = 0;
    CGFloat transcale = 0;
    switch (direction) {
        case RMoveDirectionLeft:
            break;
        case RMoveDirectionRight:
            translateX = _LeftSContentOffset;
            transcale = _LeftSContentScale;
            break;
        default:
            break;
    }
    
    CGAffineTransform transT = CGAffineTransformMakeTranslation(translateX, 0);
    CGAffineTransform scaleT = CGAffineTransformMakeScale(transcale, transcale);
    CGAffineTransform conT = CGAffineTransformConcat(transT, scaleT);
    
    return conT;
}

- (NSString*)deviceWithNumString{
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    
    @try {
        return [deviceString stringByReplacingOccurrencesOfString:@"," withString:@""];
    }
    @catch (NSException *exception) {
        return deviceString;
    }
    @finally {
    }
}

- (void)configureViewShadowWithDirection:(RMoveDirection)direction
{
    if ([[self deviceWithNumString] hasPrefix:@"iPhone"]&&[[[self deviceWithNumString] stringByReplacingOccurrencesOfString:@"iPhone" withString:@""] floatValue]<40) {
        return;
    }
    if ([[self deviceWithNumString] hasPrefix:@"iPod"]&&[[[self deviceWithNumString] stringByReplacingOccurrencesOfString:@"iPod" withString:@""] floatValue]<40) {
        return;
    }
    if ([[self deviceWithNumString] hasPrefix:@"iPad"]&&[[[self deviceWithNumString] stringByReplacingOccurrencesOfString:@"iPad" withString:@""] floatValue]<25) {
        return;
    }
    
    CGFloat shadowW;
    switch (direction)
    {
        case RMoveDirectionLeft:
            shadowW = 2.0f;
            break;
        case RMoveDirectionRight:
            shadowW = -2.0f;
            break;
        default:
            break;
    }
//    _mainContentView.layer.shadowOffset = CGSizeMake(shadowW, 0.5);
//    _mainContentView.layer.shadowColor = [UIColor grayColor].CGColor;
//    _mainContentView.layer.shadowOpacity = 0.3f;
}

- (void)setSelectedIndex:(NSUInteger)index
{
    [super setSelectedIndex:index];
    [self setNoHighlightTabBar];
}

- (void)setSelectedViewController:(UIViewController *)selectedViewController
{
    [super setSelectedViewController:selectedViewController];
    [self setNoHighlightTabBar];
}

- (void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item
{
    CGFloat systemVersion = [[UIDevice currentDevice] systemVersion].floatValue;
    if (systemVersion <= 7.0 && systemVersion >=5.0)
    {
        NSMutableArray *mutableArr = [tabBar.items mutableCopy];
        [mutableArr removeObject:item];
        
        for (UITabBarItem *anItem in mutableArr)
        {
            [anItem setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:[UIColor grayColor],UITextAttributeTextColor,nil] forState:UIControlStateNormal];
        }
        [item setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:UIColorRGB(0xc8142e),UITextAttributeTextColor,nil] forState:UIControlStateNormal];
    }
    
    [self setMarqueelabelRestart];
    
}


-(void)setMarqueelabelRestart
{
    //判断是否学习和咨询
    //    if(self.selectedIndex==1 && self.selectedIndex==2)
    //    {
    [[NSNotificationCenter defaultCenter] postNotificationName:@"RestartMarqueelabel" object:nil];
    
    //    }
    
}

- (void)setNoHighlightTabBar
{
    NSArray * tabBarSubview = [self.tabBar subviews];
    
    NSMutableArray *tabBarSubviews = [[NSMutableArray alloc] init];
    
    for (NSInteger i = 0; i < [tabBarSubview count]; i++)
    {
        if ([[tabBarSubview objectAtIndex:i] isKindOfClass:NSClassFromString(@"UITabBarButton")])
        {
            [tabBarSubviews addObject:[tabBarSubview objectAtIndex:i]];
        }
    }
    
# if ! __has_feature(objc_arc)
	UIImageView *selview = [[[UIImageView alloc] init] autorelease];
#else 
    UIImageView *selview = [[UIImageView alloc] init];
#endif
    
	selview.image = [UIImage imageNamed:@"tabselect"];
    for(NSInteger i = [tabBarSubviews count] - 1; i >= 0; i--)
    {
        for(UIView * v in [[tabBarSubviews objectAtIndex:i] subviews])
        {
            if(v && [NSStringFromClass([v class]) isEqualToString:@"UITabBarSelectionIndicatorView"])
            {//the v is the highlight view.
				//[v insertSubview:selview atIndex:i];
				 [[tabBarSubviews objectAtIndex:i] insertSubview:selview belowSubview:v];
                [v removeFromSuperview];
                break;
            }
        }
    }
    
    for(UIView * v in [[tabBarSubviews objectAtIndex:self.selectedIndex] subviews])
    {
        if (v && [NSStringFromClass([v class]) isEqualToString:@"UITabBarButtonLabel"])
        {
            if ([((UILabel *)v).text isEqual:strExam])
            {
                [examTips removeFromSuperview];
                CMRELEASE(examTips);
                examTips = nil;
            }
            else if ([((UILabel *)v).text isEqual:strMore])
            {
                [moreTips removeFromSuperview];
                CMRELEASE(moreTips);
                moreTips = nil;
            }
        }
    }
    CMRELEASE(tabBarSubviews);
}

- (void)dealloc {
	
    [_panGestureRec removeTarget:self action:@selector(moveViewWithGesture:)];
    [_tapGestureRec removeTarget:self action:@selector(closeSideBar)];
    
    CMRELEASE(_panGestureRec);
    CMRELEASE(_tapGestureRec);
    CMRELEASE(_leftSideView);
    CMRELEASE(moreTips);
    CMRELEASE(bgView);

    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    CMRELEASE(learnNavigationController);
    CMRELEASE(newsNavigationController);
    CMRELEASE(interactNavigationController);
    CMRELEASE(appNavigationController);
    CMRELEASE(knowledgeNavigationController);
    CMRELEASE(mycenterController);
    
    SAFEDELETE(m_pListener);

# if ! __has_feature(objc_arc)
	[super dealloc];
#endif
}

#pragma mark Gesture Handle Method
/**
 *参考微信的效果，tabbar切换时原有界面滚动不停止。
 *如果实现切换时原界面滚动停止效果,请去注释掉一系列的 stopScrolling 方法。
 **/
- (void)handleSingleTap:(UIGestureRecognizer *)gestureRecognizer{
    // NSUInteger oldSelectedIndex = self.selectedIndex;
    
    CGPoint touchPoint = [gestureRecognizer locationInView:self.tabBar];
    NSUInteger newSelectedIndex = (touchPoint.x * self.tabBar.items.count) / self.view.bounds.size.width;
//    if (self.selectedViewController != nil) {
//        UIViewController *topViewController = [((UINavigationController *)self.selectedViewController).topViewController retain];
//        if (topViewController != nil && [topViewController respondsToSelector:@selector(stopScrolling)]){
//            [topViewController stopScrolling];
//        }
//        [topViewController release];
//    }
    [self setSelectedIndex:newSelectedIndex];
}

- (void)handleDoubleTap:(UIGestureRecognizer *)gestureRecognizer{
    if (self.selectedViewController != nil){
        CMViewController *topViewController = (CMViewController *)((UINavigationController *)self.selectedViewController).topViewController;
        if (topViewController != nil && [topViewController respondsToSelector:@selector(scrollToTop)]){
            [topViewController scrollToTop];
        }
    }
}


@end
