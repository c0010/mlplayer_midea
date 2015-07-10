//
//  tool.m
//  iphone_Learning
//
//  Created by sunjj on 11-4-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "tool.h"
#include "cmcommon.h"
#import "CustomBGAlert.h"
#import <QuartzCore/QuartzCore.h> 
#import "MLPlayerAppDelegate.h"
#import "CMViewController.h"

#import "ATMHud/ATMHud.h"
#import "ATMHud/ATMHudQueueItem.h"


@interface CMViewController(addLoading)<UIWebViewDelegate>
@end


@implementation CMViewController(addLoading)

static UIActivityIndicatorView* activityView;

static 	ATMHud *hud;

-(void)webViewDidStartLoad:(UIWebView *)webView
{
    

    [tool ShowActivityIndicator:webView];
}

-(void)webViewDidFinishLoad:(UIWebView *)webView
{
    [tool DisimissActivityIndicator];
}

-(void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [tool DisimissActivityIndicator];
 
    
        
//    UIImage *reloadImg=[UIImage imageNamed:@"reloadHandImg"];
//    
//    UIImageView *reloadView=[[UIImageView alloc]initWithFrame:CGRectMake((webView.frame.size.width-reloadImg.size.width)/2, (webView.frame.size.height-reloadImg.size.height)/2, reloadImg.size.width, reloadImg.size.height)];
//    [reloadView setImage:reloadImg];
//    
//    UIButton* reloadBtn=[[UIButton alloc]initWithFrame:CGRectMake(0,0,webView.frame.size.width,webView.frame.size.height)];
//    
//    [reloadBtn addSubview:reloadView];
//    [reloadView release];
//
//    [reloadBtn addTarget:self action:@selector(reloadPage:) forControlEvents:UIControlEventTouchUpInside];
//
//    [webView addSubview:reloadBtn];
//    webView.scrollView.scrollEnabled=NO;
    
//    [tool ShowAlert:@"网络不给力，读取失败"];
//    [reloadBtn release];
    
}

-(void)reloadPage:(id)sender
{
    UIButton *refreshButton = (UIButton *)sender;

    UIWebView *webview= (UIWebView*)refreshButton.superview;
    
    [refreshButton removeFromSuperview];
    webview.scrollView.scrollEnabled=YES;

    
    [webview loadRequest:webview.request];
    
    
}


@end


//@implementation WaitingView
//
//UIView *m_pBackView;
//
//+ (void)WaitingStart
//{
//    if (m_pBackView)
//    {
//        m_pBackView.hidden = YES;
//        [m_pBackView release];
//        m_pBackView = nil;
//    }
//    
//    m_pBackView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
//    m_pBackView.center = CGPointMake(UI_IOS_WINDOW_HEIGHT/2, UI_IOS_WINDOW_WIDTH/2);
//    m_pBackView.backgroundColor = [UIColor blackColor];
//    m_pBackView.alpha = 0.6;
//    m_pBackView.layer.cornerRadius = 3.0f;
//    
//    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
//    
//    if (orientation == UIInterfaceOrientationLandscapeLeft)
//    {
//        m_pBackView.transform = CGAffineTransformMakeRotation(-M_PI_2);
//    }
//    else if (orientation == UIInterfaceOrientationLandscapeRight)
//    {
//        
//        m_pBackView.transform = CGAffineTransformMakeRotation(M_PI_2);
//    }
//    
//    UIActivityIndicatorView *pActivityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
//    pActivityView.frame = CGRectMake(0, 0, 30, 30);
//    pActivityView.center = CGPointMake(50, 40);
//    [pActivityView startAnimating];
//    [m_pBackView addSubview:pActivityView];
//    [pActivityView release];
//    
//    UILabel *pTitle = [[UILabel alloc] initWithFrame:CGRectMake(10, 70, 80, 25)];
//    pTitle.backgroundColor = [UIColor clearColor];
//    pTitle.font = [UIFont systemFontOfSize:15];
//    
//    if ([UIDevice currentDevice].systemVersion.floatValue < 6.0)
//    {
//        pTitle.textAlignment = UITextAlignmentCenter;
//    }
//    else
//    {
//        pTitle.textAlignment = NSTextAlignmentCenter;
//    }
//    pTitle.textColor = [UIColor whiteColor];
//    pTitle.text = I(@"加载中…");
//    [m_pBackView addSubview:pTitle];
//    [pTitle release];
//    
//    MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
//    
//    [appDelegate.window addSubview:m_pBackView];
//    
//    [NSTimer timerWithTimeInterval:20 target:self selector:@selector(WaitingFail) userInfo:nil repeats:NO];
//}
//
//
//+ (void)WaitingStop
//{
//    if (m_pBackView)
//    {
//        m_pBackView.hidden = YES;
//        [m_pBackView release];
//        m_pBackView = nil;
//    }
//}
//
//
//+ (void)WaitingFail
//{
//    if (!m_pBackView.hidden)
//    {
//        [self WaitingStop];
//    }
//}
//@end
@implementation tool

BOOL b_isBack;

UIView *customView;

UIAlertView *alert;
CustomBGAlert*customalert;

//- (void) performDismiss: (NSTimer *)timer
//{
//	[alert dismissWithClickedButtonIndex:0 animated:NO];
//	[alert release];
//	alert = NULL;	
//}

+(UIView*)generatePlaceholderView:(PlaceholderInfo)info on:(UIView*)targetView
{
    
    UIView* tempview =  [tool generatePlaceholderView:info];
    [tempview setCenter:CGPointMake(targetView.frame.size.width/2, targetView.frame.size.height/2-50)];
    
    return tempview;
    
}

+(void)addGeneratePlaceholderView: (PlaceholderActionType)actiontype
                           target:(id)target
                           action:(SEL) action
                               on:(UIView*)targetView
{
    switch (actiontype) {
        case PlaceholderActionClickRefresh:
        {
            UIView *bgview;
            bgview = [targetView viewWithTag:500001];
            if (bgview) {
                [bgview removeFromSuperview];
            }
            
            CGRect targetRect = targetView.bounds;
            bgview = [[UIView alloc] initWithFrame:targetRect];
            bgview.tag = 500001;
            bgview.backgroundColor = [UIColor clearColor];
            
            UIImageView *imgview = [[UIImageView alloc] initWithFrame:CGRectMake((targetRect.size.width - 120)/2, (targetRect.size.height - 220)/2, 120, 120)];
            imgview.image = [UIImage imageNamed:@"placeholder_clickrefresh"];
            imgview.userInteractionEnabled = YES;
            [bgview addSubview:imgview];
            
            UILabel * lbl_NoData = [[UILabel alloc]init];
            lbl_NoData.backgroundColor = [UIColor clearColor];
            
            [lbl_NoData setFrame:CGRectMake(0, CGRectGetMaxY(imgview.frame), targetRect.size.width, 32)];
            
            [lbl_NoData setFont:[UIFont systemFontOfSize:15]];
            
            [lbl_NoData setTextAlignment:NSTextAlignmentCenter];
            
            [lbl_NoData setText:I(@"点击屏幕刷新")];
            
            [lbl_NoData setTextColor:UIColorRGB(0x999999)];
            
            [bgview addSubview:lbl_NoData];
            
            UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
            
            [btn setBackgroundColor:[UIColor clearColor]];
            
            [btn addTarget:target action:action forControlEvents:UIControlEventTouchUpInside];
            
            [btn setFrame:bgview.frame];
            
            [bgview addSubview:btn];
            
            [targetView addSubview:bgview];
            
        }
            break;
            
        default:
            break;
    }
}



+(UIView*)generatePlaceholderView:(PlaceholderInfo)info
{
    switch (info)
    {
        case Placeholder_NoDataText:
        {
            UILabel * lbl_NoData = [[UILabel alloc]init];
            lbl_NoData.backgroundColor = [UIColor clearColor];
            CGSize size_NoData = [I(@"暂无数据") sizeWithFont:[UIFont systemFontOfSize:15] constrainedToSize:CGSizeMake(UI_IOS_WINDOW_WIDTH, MAXFLOAT)];
            
            [lbl_NoData setFrame:CGRectMake(0, 0, size_NoData.width, size_NoData.height)];
            
            [lbl_NoData setFont:[UIFont systemFontOfSize:15]];
            
            [lbl_NoData setText:I(@"暂无数据")];
            
            [lbl_NoData setTextColor:[UIColor grayColor]];
            
            return lbl_NoData;
           
            break;
        }
        case Placeholder_NoSurveyText:{
            
            UILabel * lbl_NoData = [[UILabel alloc]init];
            lbl_NoData.backgroundColor = [UIColor clearColor];
            CGSize size_NoData = [I(@"调研已全部提交") sizeWithFont:[UIFont systemFontOfSize:15] constrainedToSize:CGSizeMake(UI_IOS_WINDOW_WIDTH, MAXFLOAT)];
            
            [lbl_NoData setFrame:CGRectMake(0, 0, size_NoData.width, size_NoData.height)];
            
            [lbl_NoData setFont:[UIFont systemFontOfSize:15]];
            
            [lbl_NoData setText:I(@"调研已全部提交")];
            
            [lbl_NoData setTextColor:[UIColor grayColor]];
            
            return lbl_NoData;
            
            break;

        }
        default:
            return nil;
            break;
            
    }
    return nil;

}

+(void)ShowActivityIndicator:(UIView*)view
{
    if(view == nil)
        return;
    
    [activityView stopAnimating];
    activityView=nil;

    if(!activityView)
    {
        activityView = [[UIActivityIndicatorView alloc]
                        initWithFrame:CGRectMake(0,
                                                 0.0f,
                                                 20,
                                                 20)];
    
        activityView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        activityView.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin
        | UIViewAutoresizingFlexibleRightMargin
        | UIViewAutoresizingFlexibleTopMargin
        | UIViewAutoresizingFlexibleBottomMargin;
            activityView.hidesWhenStopped = YES;
        
        [activityView startAnimating];//开启动画
    }

    [activityView setFrame:CGRectMake((view.frame.size.width-20)/2, (view.frame.size.height-20)/2, 20, 20)];

    [view addSubview:activityView];
    
//    if ( !hud ) {
//        
//        hud = [[ATMHud alloc] initWithDelegate:self];
//        
//        MLPlayerAppDelegate* appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
//        [appDelegate.window addSubview:hud.view];
//    }
//    
//    
//    [hud setCaption:@"加载中..."];
//    [hud setActivity:YES];
//    [hud setActivityStyle:UIActivityIndicatorViewStyleWhiteLarge];
//    [hud setAccessoryPosition:ATMHudAccessoryPositionTop];
//    [hud show];
    
}

+(void)ShowActivityIndicator:(UIView*)view at:(CGPoint)pos
{
    
    [activityView stopAnimating];
    activityView=nil;
    
    if(!activityView)
    {
        activityView = [[UIActivityIndicatorView alloc]
                        initWithFrame:CGRectMake(0,
                                                 0.0f,
                                                 20,
                                                 20)];
        
        activityView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        activityView.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin
        | UIViewAutoresizingFlexibleRightMargin
        | UIViewAutoresizingFlexibleTopMargin
        | UIViewAutoresizingFlexibleBottomMargin;
        activityView.hidesWhenStopped = YES;
        
        [activityView startAnimating];//开启动画
    }
    
    [activityView setFrame:CGRectMake(pos.x, pos.y, 20, 20)];
    
    [view addSubview:activityView];
    
//    if ( !hud ) {
//        
//        hud = [[ATMHud alloc] initWithDelegate:self];
//        
//        MLPlayerAppDelegate* appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
//        [appDelegate.window addSubview:hud.view];
//    }
//    
//    
//    [hud setCaption:@"加载中..."];
//    [hud setActivity:YES];
//    [hud setActivityStyle:UIActivityIndicatorViewStyleWhiteLarge];
//    [hud setAccessoryPosition:ATMHudAccessoryPositionTop];
//    [hud show];
}


+(void)DisimissActivityIndicator
{


    [activityView stopAnimating];
    activityView=nil;
    
//    if ( hud ) {
//        
//        [hud hide];
//        
//        [hud.view removeFromSuperview];
//        [hud release];
//        hud= nil;
//    }
}


+(void)ShowError:(int)Result
{
	if (Result == TResult::ENetTimeout) {
		
		[self ShowAlert:I(@"网络连接超时")];

	}else if (Result == TResult::EUserdisabled) {
		
		[self ShowAlert:I(@"该用户己被禁用")];

	}else if (Result == TResult::EUserusing) {
		
		[self ShowAlert:I(@"该用户己登录")];

	}else if (Result == TResult::ENetDisconnect) {
		
		[self ShowAlert:I(@"网络不给力")];

	}else if (Result == TResult::EVersionError) {
		
		[self ShowAlert:I(@"版本不被服务器支持")];

	}else if(Result == TResult::EDuplicaterating) {
		
		[self ShowAlert:I(@"每门课程只能顶一次，您已经顶过了")];
		
	}else if(Result == TResult::EProtocolFormatError) {
		
		[self ShowAlert:I(@"协议格式错误")];
		
	}else if(Result == TResult::EUnknownFormat) {
		
		[self ShowAlert:I(@"未知格式")];
		
	}else if(Result == TResult::ENotSupportFormat) {
		
		[self ShowAlert:I(@"不支持格式")];
		
	}else if(Result == TResult::EPartialContent) {
		
		[self ShowAlert:I(@"只返回了请求数据中的一部分")];
		
	}else if(Result == TResult::EUserOrPassError) {
		
		[self ShowAlert:I(@"员工帐号或密码错误")];
		
	}else if(Result == TResult::EUnknownError) {
        
		[self ShowAlert:I(@"服务器未知错误")];
		
	}
    else if(Result == TResult::ENoPowerCourse) {
        
        [self ShowAlert:I(@"您无权限访问此课程")];
        
    }
    else if(Result == TResult::ENotMideaUid){
        [self ShowAlert:I(@"非美的帐号不能登陆")];
    }
    
#ifndef __OPTIMIZE__
    else if(Result == TResult::ENotSupportOffline){
        [self ShowAlert:I(@"不支持离线")];
    }
    else if(Result == TResult::ENothing){
        [self ShowAlert:I(@"没有符合条件的结果")];
    }
    else if(Result == TResult::ESuccess){
        [self ShowAlert:I(@"成功")];
    }
    else if(Result == TResult::ESuccessCache){
        [self ShowAlert:I(@"成功从缓存读取出来")];
    }
    else if(Result == TResult::EKicked){
        [self ShowAlert:I(@"被迫下线")];
    }
    else if(Result == TResult::ESmscode){
        [self ShowAlert:I(@"短信授权码不正确")];
    }
    else if(Result == TResult::ECer){
        [self ShowAlert:I(@"登陆签证不正确")];
    }
    else if(Result == TResult::EAlreadyDone){
        [self ShowAlert:I(@"已完成")];
    }
    else if(Result == TResult::EParams){
        [self ShowAlert:I(@"参数错误")];
    }
    else if(Result == TResult::EIsGone){
        [self ShowAlert:I(@"状态已改变")];
    }
    else if(Result == TResult::EBound){
        [self ShowAlert:I(@"帐号已绑定其他设备")];
    }
    else if(Result == TResult::EJoinGroupError){
        [self ShowAlert:I(@"加入群失败")];
    }
    else if(Result == TResult::ECreateGroupError){
        [self ShowAlert:I(@"创建群失败")];
    }
    else if(Result == TResult::EGetGroupListError){
        [self ShowAlert:I(@"获取群列表失败")];
    }
    else if(Result == TResult::EGetGroupInfoError){
        [self ShowAlert:I(@"获取群详细信息失败")];
    }
    else if(Result == TResult::EApplyGroupError){
        [self ShowAlert:I(@"申请加入群失败")];
    }
    else if(Result == TResult::EGroupManagementError){
        [self ShowAlert:I(@"群管理操作失败")];
    }
    else if(Result == TResult::EGroupInexistence){
        [self ShowAlert:I(@"群组已解散或不存在")];
    }
    else if(Result == TResult::ETimeNotStart){
        [self ShowAlert:I(@"未开始")];
    }
    else if(Result == TResult::ETimeEnd){
        [self ShowAlert:I(@"已结束")];
    }
    else if(Result == TResult::EBeCancel){
        [self ShowAlert:I(@"已经取消")];
    }
    else if(Result == TResult::ENotBelong){
        [self ShowAlert:I(@"不属于")];
    }
    else if(Result == TResult::EOutNum){
        [self ShowAlert:I(@"超出人数")];
    }
    else if(Result == TResult::EExamTimeOut){
        [self ShowAlert:I(@"考试超时")];
    }
    else if(Result == TResult::ESameData){
        [self ShowAlert:I(@"本地数据与服务器相同,不返回")];
    }
    else if(Result == TResult::ECantExam){
        [self ShowAlert:I(@"不能考试")];
    }
#endif
    
    else {
        
		[self ShowAlert:I(@"网络不给力")];
		
	}
	
	/*
	 
	 const static int EProtocolFormatError = 7;//协议格式错误
	 
	 const static int EUnknownFormat = 6;//未知格式
	 
	 const static int ENotSupportFormat = 5;//不支持格式
	 
	 const static int ENothing = 4;//对获取数据的请求处理正确，但没有符合条件的结果返回
	 
	 const static int EPartialContent = 3;//只返回了请求数据中的一部分
	 
	 const static int ENetTimeout = 2;//请求超时
	 
	 const static int ENetDisconnect = 1;//网络连接异常
	 
	 const static int ESuccess = 0;//成功
	 
	 const static int EUnknownError = -1;//服务器发生未定义的错误
	 
	 const static int EUserOrPassError = -10;//用户名或密码错误
	 
	 const static int EVersionError = -3;//版本不被服务器支持
	 
	 const static int EUserusing = -12;//用户已经登录，不允许重复登录
	 
	 const static int EUserdisabled = -13;//用户已被禁用
	 
	 const static int EDuplicaterating = -14;//不允许重复评价课程
	 */
}

+(void)ShowAlert:(NSString*) text
{
    
//    [alert dismissWithClickedButtonIndex:0 animated:YES];
//    
//    [alert release];
//
//    alert = nil;
//   // if (__iOS8) text = [@"\n" stringByAppendingString:text];
//	alert = [[UIAlertView alloc] 
//				 initWithTitle:nil message:text
//				 delegate:self cancelButtonTitle:nil
//				 otherButtonTitles: nil];
////	[alert setBackgroundColor:[UIColor clearColor]];
////	alert.frame = CGRectMake(50, 150, 220, 20);
//	//alert = [[[UIAlertView alloc] initWithTitle:text
////										message:nil delegate:self cancelButtonTitle: @"ok" otherButtonTitles: nil] autorelease];
////		
////	UIActivityIndicatorView *indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
////	indicator.center = CGPointMake(alert.bounds.size.width + 150, alert.bounds.size.height + 70);
////	
////	[indicator startAnimating];
////	
////    [alert addSubview:indicator];
////	[indicator release];
//	[alert performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];
//	
//	[NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(dimissAlertView) userInfo:nil repeats:NO];
	
    
    if ( hud ) {
        [hud hide];
        [hud.view removeFromSuperview];
        CMRELEASE(hud);
        hud =nil;
    }
    hud = [[ATMHud alloc] initWithDelegate:self];
    
    MLPlayerAppDelegate* appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
    [appDelegate.window addSubview:hud.view];
    [hud setAllowSuperviewInteraction:TRUE];     //允许用户与界面交互
    [hud setCaption:text];
    [hud show];
    [hud hideAfter:1.0];
}

+(void)willPresentAlertView:(UIAlertView *)alertView;  // before animation and showing view
{
	alertView.frame = CGRectMake(50, 200, 220, 40);
    if([[UIApplication sharedApplication] statusBarOrientation] == UIInterfaceOrientationLandscapeRight){
        alertView.frame = CGRectMake((UI_IOS_WINDOW_HEIGHT - 220)/2.0, (UI_IOS_WINDOW_WIDTH - 40)/2.0, 220, 40);
    }

    [[UIApplication sharedApplication] statusBarOrientation];
	for( UIView * view in alertView.subviews )
	{
		if([view isKindOfClass:[UILabel class]])
		{
			UILabel* label = (UILabel*) view;
			label.textAlignment=UITextAlignmentCenter;
			label.frame = CGRectMake(5, 10, 210, 20);
		}else if ([view isKindOfClass:[UIImageView class]])
		{
            UIImage *theImage = [UIImage imageNamed:@"textHintBG.png"];  
			theImage = [theImage stretchableImageWithLeftCapWidth:theImage.size.width/2 topCapHeight:theImage.size.height/2];
			//((UIImageView *)view).image = [theImage resizableImageWithCapInsets:UIEdgeInsetsMake(0, 0, 0, 0)];
            ((UIImageView *)view).image = theImage;
        }
	}	
}
+(void)Wait
{
    [customalert dismissWithClickedButtonIndex:0 animated:YES];
	customalert = nil;
	
    customalert = [[CustomBGAlert alloc] init];
	[customalert show];
}
+(void)CancelWait
{
	[customalert dismissWithClickedButtonIndex:0 animated:YES];
	customalert = nil;
}


+(void)dimissAlertView{
	
    [alert dismissWithClickedButtonIndex:0 animated:YES];
		
    alert = nil;
	
}

+(BOOL)GetIsBack
{
	return b_isBack;
}

+(void)SetIsBack:(BOOL)istrue
{

	b_isBack = istrue;
}

#pragma mark - we工具


+(BOOL)hasClickedWE
{
    BOOL hasClicked= [[NSUserDefaults standardUserDefaults] boolForKey:@"wetool"];
    return hasClicked;
}

+(void)clickedWE
{
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"wetool"];
}

+(void)revertWE
{
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"wetool"];
}


#pragma mark - 引导页
+(NSString*)NeedGuideViewToString:(NeedGuideView)name
{
    NSString *viewname;
    switch (name) {
        case NeedGuideViewMoviePlayer:
            viewname=@"MoivePlayer";
            break;
            
        case NeedGuideViewExam:
            viewname=@"Exam";
            break;
            
        case NeedGuideViewSearch:
            viewname=@"Search";
            break;
            
        case NeedGuideViewComment:
            viewname=@"Comment";
            break;
            
            
        case NeedGuideViewCourse:
            viewname=@"Course";
            break;
            
        case NeedGuideViewLearn:
            viewname=@"Learn";
            break;
            
        case NeedGuideViewPerson:
            viewname=@"Person";
            break;
            
        case NeedGuideViewPush:
            viewname=@"Push";
        
        default:
            break;
    }
    
    return viewname;
    
}

+(BOOL)isFirstTimeToDisplay:(NeedGuideView)name
{
    BOOL first= [[NSUserDefaults standardUserDefaults] boolForKey:[tool NeedGuideViewToString:name]];
    return first;
}

+(void)SetDisplayed:(NeedGuideView )name
{
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:[tool NeedGuideViewToString:name]];
}

+(UIView*)generateGuideView:(NeedGuideView)name
{
   UIButton * view =[[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
    [view setBackgroundColor:[UIColor blackColor]];
    [view setAlpha:0.7];
    [view addTarget:self action:@selector(dismissGuide:event:) forControlEvents:UIControlEventTouchUpInside];
    
    UIImageView *centerview=[[UIImageView alloc]init];
    [centerview setBackgroundColor:[UIColor clearColor]];

    
    //添加右上角关闭按钮
    UIImageView *closeBtn=[[UIImageView alloc]initWithFrame:CGRectMake(280, 30, 29 ,29 )];
    NSString *btnimagePath = [[NSBundle mainBundle] pathForResource:@"guide_button@2x" ofType:@"png"];
  
    
    [closeBtn setImage:[UIImage imageWithContentsOfFile:btnimagePath]];
    [view addSubview:closeBtn];
    
    
    NSString *imagePath = @"";
    //旋转90度
    CGAffineTransform rotation = CGAffineTransformMakeRotation(3.14/2);
    
   // UIImage *img;

    switch (name) {
        case NeedGuideViewMoviePlayer:
            imagePath = [[NSBundle mainBundle] pathForResource:@"guide_movieplay@2x" ofType:@"png"];
           // img=[UIImage imageWithContentsOfFile:imagePath];
            [centerview setTransform:rotation];
           // CGAffineTransformRotate(centerview, 3.14/2);
            [centerview setFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2-50, UI_IOS_WINDOW_HEIGHT/2-100, 101, 202)];
            
            break;
            
        case NeedGuideViewExam:
            imagePath = [[NSBundle mainBundle] pathForResource:@"guide_exam@2x" ofType:@"png"];
            [centerview setFrame:CGRectMake(80, UI_IOS_WINDOW_HEIGHT/2-100,153, 144)];

            break;
            
            
        case NeedGuideViewSearch:
            imagePath = [[NSBundle mainBundle] pathForResource:@"guide_search@2x" ofType:@"png"];
            [centerview setFrame:CGRectMake(80, UI_IOS_WINDOW_HEIGHT/2-100,173, 92)];

            break;
            
        case NeedGuideViewComment:
            imagePath = [[NSBundle mainBundle] pathForResource:@"guide_comment@2x" ofType:@"png"];
            [centerview setFrame:CGRectMake(100, UI_IOS_WINDOW_HEIGHT/2-100,188, 183)];

            break;
            
            
        case NeedGuideViewCourse:
            imagePath = [[NSBundle mainBundle] pathForResource:@"guide_course@2x" ofType:@"png"];
            [centerview setFrame:CGRectMake(80, UI_IOS_WINDOW_HEIGHT/2-50,179,104)];

            break;
            
        case NeedGuideViewLearn:
            imagePath = [[NSBundle mainBundle] pathForResource:@"guide_learn@2x" ofType:@"png"];
            [centerview setFrame:CGRectMake(-3,0,234, 177)];

            break;
        case NeedGuideViewPush:
        {
            imagePath = nil;
            [self initPushLoadView:view];
        }
            break;
            
        default:
            break;
    }
    [centerview setImage:[UIImage imageWithContentsOfFile:imagePath]];

    [view addSubview:centerview];
    
    
    
    [tool SetDisplayed:name];
    
    return view;
}

+(void)initPushLoadView:(UIView *)view{
    UINavigationBar *bar = [[UINavigationBar alloc]init];
    if (__iOS7)
    {
        bar.frame = CGRectMake(0.0, 0.0, UI_IOS_WINDOW_WIDTH, 64.0);
        [bar setBackgroundImage:[UIImage imageNamed:@"background"] forBarPosition:UIBarPositionTopAttached barMetrics:UIBarMetricsDefault];
    }
    else
    {
        bar.frame = CGRectMake(0.0, 0.0, UI_IOS_WINDOW_WIDTH, 44.0);
        [bar setBackgroundImage:[UIImage imageNamed:@"NaviBg"] forBarMetrics:UIBarMetricsDefault];
    }
    
    UINavigationItem *navitem = [[UINavigationItem alloc] init];
    UILabel *titleLabel = [[UILabel alloc] init];
    titleLabel.frame = CGRectMake(0, 0, 200, 44);
    titleLabel.textAlignment = NSTextAlignmentCenter;
    titleLabel.backgroundColor = [UIColor clearColor];
    titleLabel.textColor = [UIColor whiteColor];
    titleLabel.font = [UIFont boldSystemFontOfSize:20];
    titleLabel.text = I(@"最新推送");
    navitem.titleView = titleLabel;
    
    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    backBtn.frame = CGRectMake(0, 0, kBarItemWidth, kBarItemHeight);
    if (__iOS7)
    {
        backBtn.imageEdgeInsets = UIEdgeInsetsMake(0, -20, 0, 0);
    }
    else
    {
        backBtn.imageEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 0);
    }
    [backBtn setImage:[UIImage imageNamed:@"back"] forState:UIControlStateNormal];
    backBtn.tag = 101;
    [backBtn addTarget:self action:@selector(gotoBack:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem *backBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
    navitem.leftBarButtonItem = backBarButtonItem;
    
    NSArray *itemarr = [NSArray arrayWithObjects:navitem, nil];
    [bar setItems:itemarr];
    
    UIView *bg = [[UIView alloc]initWithFrame:CGRectMake(0.0, 64.0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64.0)];
    bg.backgroundColor = [UIColor whiteColor];
    view.alpha = 1.0;
    UIActivityIndicatorView *activiyview = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    activiyview.center = view.center;
    [activiyview startAnimating];
    
    [view addSubview:bar];
    [view addSubview:bg];
    [view addSubview:activiyview];
    
}

+ (void)gotoBack:(id)sender{
    UIButton *btn = (UIButton *)sender;
    UIView *tempview= [btn superview];
    
    ((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).guideWindow.windowLevel=UIWindowLevelNormal;
    [tempview removeFromSuperview];
    
    
    [((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).window makeKeyAndVisible];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"GuideDismiss"
                                                        object:nil
                                                      userInfo:nil];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"PushLoadCancel"
                                                        object:nil
                                                      userInfo:nil];
}

+(void)dismissGuide:(id)sender event:(id)event
{
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
    UIView *tempview=touch.view;
    
    
    ((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).guideWindow.windowLevel=UIWindowLevelNormal;
    [tempview removeFromSuperview];
    
   

    [((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).window makeKeyAndVisible];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"GuideDismiss"
                                                        object:nil
                                                      userInfo:nil];

}


//文字对齐方式
+ (NSInteger)TextAlignment:(ALIGNMENT)alignment
{
    switch (alignment)
    {
        case 0:
        {
            if (__iOS6)
                return NSTextAlignmentLeft;
            else
                return UITextAlignmentLeft;
            break;
        }
        case 1:
        {
            if (__iOS6)
                return NSTextAlignmentCenter;
            else
                return UITextAlignmentCenter;
            break;
        }
        case 2:
        {
            if (__iOS6)
                return NSTextAlignmentRight;
            else
                return UITextAlignmentRight;
            break;
        }
        default:
        {
            if (__iOS6)
                return NSTextAlignmentLeft;
            else
                return UITextAlignmentLeft;
            break;
        }
    }
}

//文字换行方式
+ (NSInteger)TextBreakMode:(TEXTBREAKMODE)mode
{
    switch (mode)
    {
        case 0:
        {
            if (__iOS6)
                return NSLineBreakByWordWrapping;
            else
                return UILineBreakModeWordWrap;
            break;
        }
        case 1:
        {
            if (__iOS6)
                return NSLineBreakByCharWrapping;
            else
                return UILineBreakModeCharacterWrap;
            break;
        }
        case 2:
        {
            if (__iOS6)
                return NSLineBreakByClipping;
            else
                return UILineBreakModeClip;
            break;
        }
        case 3:
        {
            if (__iOS6)
                return NSLineBreakByTruncatingHead;
            else
                return UILineBreakModeHeadTruncation;
            break;
        }
        case 4:
        {
            if (__iOS6)
                return NSLineBreakByTruncatingTail;
            else
                return UILineBreakModeTailTruncation;
            break;
        }
        case 5:
        {
            if (__iOS6)
                return NSLineBreakByTruncatingMiddle;
            else
                return UILineBreakModeMiddleTruncation;
            break;
        }
        default:
        {
            if (__iOS6)
                return NSLineBreakByWordWrapping;
            else
                return UILineBreakModeWordWrap;
            break;
        }
    }
}

//提交内容不能及时返回时页面添加等待状态
+ (void)ShowBeforeBack
{
    if (customView)
        [tool DismissAtEnd];
    
    customView = [[UIView alloc] init];
    customView.frame =  CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT);
    customView.backgroundColor = [UIColor blackColor];
    customView.alpha = 0.4;
    UIActivityIndicatorView *activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    activityView.tag = 1000;
    activityView.center = customView.center;
    [activityView startAnimating];
    [customView addSubview:activityView];
    
    MLPlayerAppDelegate *appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
    [appDelegate.window addSubview:customView];
    
}

+ (void)DismissAtEnd
{
    UIActivityIndicatorView *activityView = (UIActivityIndicatorView*)[customView viewWithTag:1000];
    [activityView stopAnimating];
    
    [customView removeFromSuperview];
    customView = nil;
}

+ (bool)isExistNetwork
{
    BOOL isExist = NO;
    
    Reachability *reach = [Reachability reachabilityForInternetConnection];
    
    switch ([reach currentReachabilityStatus])
    {
        case NotReachable:
        {
            isExist = NO;
            break;
        }
        case ReachableViaWiFi:
        {
            isExist = YES;
            break;
        }
        case ReachableViaWWAN:
        {
            isExist =YES;
            break;
        }
        default:
            break;
    }
    
    return isExist;
}

+ (BOOL)isExistWifi
{
    Reachability *reach = [Reachability reachabilityForInternetConnection];
    if ([reach currentReachabilityStatus] == ReachableViaWiFi)
    {
        return YES;
    }
    return NO;
}

@end


/** @Deprecated
 * 废弃MessageBox这个类，统一用CMAlertView代替
 * 暂时只是注释掉与MessageBox相关代码，待经长时间考证没问题后，再删掉相关代码
 */
/***********************************
@implementation MessageBox
@synthesize _confirmBlock,_cancelBlock;

static MessageBox *sharedMessageBox;

//support iOS4.0+
+(void)DoModalWithTitle:(NSString*)title message:(NSString*)message mode:(int)mode  confirm:(void (^)())myconfirmBlock cancel:(void (^)())mycancelBlock
{
    MessageBox* box = nil;
    
    if(sharedMessageBox == nil)
        sharedMessageBox = [[MessageBox alloc]init];
    
    box = sharedMessageBox;
    
	box->result = -1;
    box->isUseBlock = YES;
    
    box._cancelBlock = nil;
    box._confirmBlock = nil;
   
    box._confirmBlock = [myconfirmBlock copy];
    box._cancelBlock = [mycancelBlock copy];
    
	NSString* cancelButtonTitle = nil;
	NSString* otherButtonTitles = nil;
    
	switch(mode)
	{
		case MODE_OKCANCEL:
			cancelButtonTitle = I(@"取消");
		case MODE_OK:
			otherButtonTitles = I(@"确定");
			break;
		case MODE_YESNO:
			otherButtonTitles = I(@"确定");
			cancelButtonTitle = I(@"取消");
			break;
	}
    
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:message
                                                   delegate:box
                                          cancelButtonTitle:cancelButtonTitle
                                          otherButtonTitles:otherButtonTitles , nil];
    switch(mode)
    {
        case MODE_OKCANCEL:
            alert.tag = 50;
        case MODE_OK:
            alert.tag = 51;
            break;
        case MODE_YESNO:
            alert.tag = 52;
            break;
    }
    if(alert)
    {
        [alert show];
    }
#if ! __has_feature(objc_arc)
    [alert release];


#else

#endif

}

+(BOOL)DoModalWithTitle:(NSString*)title message:(NSString*)message mode:(int)mode
{
    MessageBox* box = nil;
    
    if(sharedMessageBox == nil)
        sharedMessageBox = [[MessageBox alloc]init];
    
    box = sharedMessageBox;
	box->result = -1;
    box->isUseBlock = NO;
	NSString* cancelButtonTitle = nil;
	NSString* otherButtonTitles = nil;
	switch(mode)
	{
		case MODE_OKCANCEL:
			cancelButtonTitle = I(@"取消");
		case MODE_OK:
			otherButtonTitles = I(@"确定");
			break;
		case MODE_YESNO:
			cancelButtonTitle = I(@"取消") ;
			otherButtonTitles = I(@"确定") ;
			break;
	}
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
			message:message delegate:box cancelButtonTitle: cancelButtonTitle otherButtonTitles: otherButtonTitles, nil];
    switch(mode)
    {
        case MODE_OKCANCEL:
            alert.tag = 50;
        case MODE_OK:
            alert.tag = 51;
            break;
        case MODE_YESNO:
            alert.tag = 52;
            break;
    }
    
	if(alert)
	{
		[alert show];
		while(box->result == -1)
		{
			[[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
		}
	}
	
    BOOL ret;
    if (alert.tag == 52) {
        ret = (box->result == 0 ? NO : YES);
    }else
        ret = (box->result == 0 ? YES : NO);
    
	 
    
	return ret;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	result = buttonIndex;
    
    if(isUseBlock)
    {
        
        if (alertView.tag == 52 ) {
            
            if(buttonIndex == 0 && _cancelBlock)
                _cancelBlock();
            
            if(buttonIndex == 1 && _confirmBlock)
                _confirmBlock();
        }
        else
        {
            if(buttonIndex == 0 && _confirmBlock)
                _confirmBlock();
        }
            
        
                
        
        _cancelBlock = nil;
        _confirmBlock = nil;
    }
}


+(void)dimissAlertView
{
	
}

@end
*******************************************/
