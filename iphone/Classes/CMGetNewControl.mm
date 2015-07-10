    //
//  CMBrowserControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import "stdafx.h"
#import "cmcommon.h"
#import "cmsettings.h"
#import "CMGetNewControl.h"
#import "CMNavgateItem.h"
#import "CMCourseDetailControl.h"
#import "CMExamInfoControl.h"
#import "CMSurveyControl.h"
#import "CMMainControl.h"
#import "CMBrowserControl.h"
#import "CMIntrodocutionViewController.h"
#import "CMQuestionDetailControl.h"
#import "CMTrainApplyDetailController.h"
#import "CMTrainDetailSignController.h"
#import "CMTrainInfoViewController.h"
#import "CMPositionCourseControl.h"

#define kNewContentCell @"newcontenttableviewcell"
#define ANIMATEWITHPUSHDURATION 0.1

@implementation UINavigationBar(CustomImage)


-(void)viewDidLoad
{
    
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    
    if (version >= 5.0)
    {
        if (version >= 7.0)
        {
            [self setBackgroundImage:[UIImage imageNamed:@"background"] forBarPosition:UIBarPositionTopAttached barMetrics:UIBarMetricsDefault];
        }
        else
        {
            [self setBackgroundImage:[UIImage imageNamed:@"NaviBg"] forBarMetrics:UIBarMetricsDefault];
        }
        
    }else{
        
        self.layer.contents=(id)[UIImage imageNamed:@"NaviBg"].CGImage;
    }
    
}


@end

@implementation CMGetNewControl

@synthesize model;
@synthesize bAppStateIsBackground;
@synthesize titleLabel;
@synthesize sId = _sId;
@synthesize sType = _sType;



-(void)clickLeftButton
{
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"0" forKey:kUDOpenPush];
    
//    [self PushLoadCancel];

    [self.navigationController popViewControllerAnimated:YES];
    
}


-(void)viewWillAppear:(BOOL)animated
{
    self.navigationController.navigationBarHidden = NO;
    self.navigationItem.leftBarButtonItem.enabled = NO;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        self.navigationItem.leftBarButtonItem.enabled = YES;
    });
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

- (void)viewDidAppear:(BOOL)animated{
    
    [super viewDidAppear:animated];
    
    //关闭推送，防止跳转错误
    [[NSUserDefaults standardUserDefaults] setObject:@"0" forKey:kUDOpenPush];
    
    if (bShouldPush)
    {
        
        if ([self.sType isEqualToString:@"apply"] || [self.sType isEqualToString:@"signin"] || [self.sType isEqualToString:@"trainclass"] || [self.sType isEqualToString:@"position_course"])
        {
            [self gotoPush : self.sType];
        }else
            //        [self LoadData];
            [self gotoPush];
    }
    else
    {
        [self.navigationController popViewControllerAnimated:NO];
    }
    bShouldPush = NO;
    
    
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    bIsPush = YES;
    bShouldPush = YES;
    
    self.view.backgroundColor = [UIColor whiteColor];
	
	appDelegate = [UIApplication sharedApplication].delegate;

    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
	backBtn.frame = CGRectMake(0, 0, 40, 44);
    if (__iOS7)
    {
        backBtn.imageEdgeInsets = UIEdgeInsetsMake(0, -20, 0, 0);
    }
    else
    {
        backBtn.imageEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 0);
    }

	[backBtn setImage:[UIImage imageNamed:@"back"] forState:UIControlStateNormal];
	[backBtn addTarget:self action:@selector(clickLeftButton) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem *backBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
	self.navigationItem.leftBarButtonItem = backBarButtonItem;
    

#if !__has_feature(obj_arc)
 
    self.titleLabel = [[UILabel alloc] init];
#else
    self.titleLabel = [[UILabel alloc] init];

#endif

    self.titleLabel.frame = CGRectMake(0, 0, 200, 44);
    self.titleLabel.textAlignment = NSTextAlignmentCenter;
    self.titleLabel.backgroundColor = [UIColor clearColor];
    self.titleLabel.textColor = [UIColor blackColor];
    self.titleLabel.font = [UIFont boldSystemFontOfSize:20];;
    
    self.titleLabel.text = self.navigationItem.title;
    self.navigationItem.titleView = self.titleLabel;

//    UIActivityIndicatorView *activiyview = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
//    activiyview.center = self.view.center;
//    [activiyview startAnimating];
//    [self.view addSubview:activiyview];
    

}

//- (void)PushLoadCancel{
//    NSLog(@"PushLoadCancel");
//    if (m_pGetNewContent->IsRunning())
//        m_pGetNewContent->Cancel();
//}

-(void)LoadData
{
	if(!m_pUpdataDataListerner)
    {
		m_pUpdataDataListerner = new CMGetNewUpdateDataListener();
    }
    
    m_pGetNewContent= CMGetNewContent::GetInstance();
    m_pGetNewContent->SetListener(m_pUpdataDataListerner);
    m_pGetNewContent->SetUserData(BridgeObjectToC(self));
	m_pGetNewContent->GetNewContent([_sId UTF8String], [_sType UTF8String]);
}

//等待Push load后，再remove该视图
- (void)removeLoadingPushView{
    int nRow = -1;
    
    for (int i = 0; i < [self.navigationController.viewControllers count]; i++)
    {
        if ([[self.navigationController.viewControllers objectAtIndex:i] isKindOfClass:[CMGetNewControl class]])
        {
            nRow = i;
            break;
        }
    }
    NSMutableArray *pMtbArray = [[NSMutableArray alloc] initWithArray:self.navigationController.viewControllers];
    if ([pMtbArray count] > nRow) {
        [pMtbArray removeObjectAtIndex:nRow];
    }
    
    
    [self.navigationController setViewControllers:pMtbArray animated:NO];

}


-(void)gotoPush:(NSString *)type
{
    if ([type isEqualToString:@"position_course"])
    {
        CMPositionCourseControl* coursecontrol=[[CMPositionCourseControl alloc]init];
        [coursecontrol setBIsPush:bIsPush];
        [self.navigationController pushViewController:coursecontrol animated:NO];
    }
    else if ([type isEqualToString:@"signin"]) {
        CMTrainDetailSignController *signControl = [[CMTrainDetailSignController alloc]init];
        [signControl setTitle:I(@"签到详情")];
        [signControl setBIsPush:bIsPush];
        [signControl setInfoWithString:self.sId];
        
        [self.navigationController pushViewController:signControl animated:NO];
        
    }
    else if ([type isEqualToString:@"apply"]) {
        CMTrainApplyDetailController *applyControl = [[CMTrainApplyDetailController alloc]init];
        [applyControl setTitle:I(@"报名详情")];
        [applyControl setBIsPush:bIsPush];
        [applyControl setInfoWithString:self.sId];
        [self.navigationController pushViewController:applyControl animated:NO];
    }
    else if ([type isEqualToString:@"trainclass"]) {
        
        CMTrainInfoViewController *infoControl = [[CMTrainInfoViewController alloc]init];
        [infoControl setTrainID:self.sId];
        [infoControl setBIsPush:bIsPush];
        [infoControl setIsChatEnter:YES];
        [self.navigationController pushViewController:infoControl animated:NO];
    }
    else if ([type isEqualToString:@"item_category"]) {
        
    }
    
    [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];
}


- (void)gotoPush{
    
    
    
//    if([self.sType isEqualToString:@""])
//    {
//        
//        if(m_pGotoCoursewareListener == NULL)
//            m_pGotoCoursewareListener = new CMGotoCoursewareListener();
//        
//        if(tempBrowser == NULL)
//            tempBrowser = new CMBrowser(m_pGotoCoursewareListener);
//        
//        tempBrowser->SetUserData((__bridge void*)self);
//        
//        if(tempBrowser->RequestCoursewareById([sid UTF8String]))
//            [tool ShowActivityIndicator:self.view];
//        else
//            [tool DisimissActivityIndicator];
//        
//        return NO;
//    }
    
    if([self.sType isEqualToString:@"course"])
    {
        TClassItem item;
        item.nModel = 0;
        strcpy(item.sID, [self.sId UTF8String]);
        strcpy(item.sFlag, "course");
        
        CMCourseDetailControl* coursedetailControl = [[CMCourseDetailControl alloc] init];
        [coursedetailControl setInfo:item];
        [self.navigationController pushViewController:coursedetailControl animated:NO];
        CMRELEASE(coursedetailControl);
        [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];
        
    }
    
    if([self.sType isEqualToString:@"news"])
    {
        
        if(m_pCMGotoNewsListener == NULL)
            m_pCMGotoNewsListener = new CMPushGotoNewsListener();
        
        if(tempBrowser == NULL)
            tempBrowser = new CMBrowser(m_pCMGotoNewsListener);
        
        tempBrowser->SetUserData((__bridge void*)self);
        
        if(tempBrowser->RequestNewsById([self.sId UTF8String]))
            [tool ShowActivityIndicator:self.view];
        else
            [tool DisimissActivityIndicator];
    }
    
    
//    if([self.sType isEqualToString:@"exercise"])
//    {
//        
//        if(m_pCMGotoExerciseListener == NULL)
//            m_pCMGotoExerciseListener = new CMGotoExerciseListener();
//        
//        if(m_pExerciselist == NULL)
//            m_pExerciselist = new CMExerciseList();
//        
//        m_pExerciselist->SetListener(m_pCMGotoExerciseListener);
//        
//        m_pExerciselist->SetUserData((__bridge void*)self);
//        
//        if (m_pExerciselist->GetExerciseById([sid UTF8String]))
//        {
//            [tool ShowActivityIndicator:self.view];
//        }
//        else
//            [tool DisimissActivityIndicator];
//        
//        return NO;
//        
//    }
    
    if([self.sType isEqualToString:@"exam"])
    {
        if(m_pCMGotoExamListener == NULL)
            m_pCMGotoExamListener = new CMPushGotoExamListener();
        
        if(m_pExamlist == NULL)
            m_pExamlist = new CMExamList();
        
        m_pExamlist->SetListener(m_pCMGotoExamListener);
        
        m_pExamlist->SetUserData((__bridge void*)self);
        
        if (m_pExamlist->GetExamById([self.sId UTF8String])) {
            [tool ShowActivityIndicator:self.view];
        }
        else
            [tool DisimissActivityIndicator];
    }
    
    if([self.sType isEqualToString:@"survey"])
    {
        if(m_pCMGotoSurveyListener == NULL)
            m_pCMGotoSurveyListener = new CMPushGotoSurveyListener();
        
        if(m_pSurveylist == NULL)
            m_pSurveylist = new CMSurveyList(m_pCMGotoSurveyListener);
        
        m_pSurveylist->SetUserData((__bridge void*)self);
        
        if (m_pSurveylist->GetSurveyById([self.sId UTF8String])) {
            [tool ShowActivityIndicator:self.view];
        }
        else
            [tool DisimissActivityIndicator];
    }
    
    if([self.sType isEqualToString:@"qa"])
    {
        
        if(m_pCMGotoQAListener == NULL)
            m_pCMGotoQAListener = new CMPushGotoQAListener();
        
        if(m_pQalist == NULL)
            m_pQalist = new CMQAList();
        
        m_pQalist->SetListener(m_pCMGotoQAListener,NULL,NULL);
        
        m_pQalist->SetUserData((__bridge void*)self);
        
        if (m_pQalist->GetQuestionbyId([self.sId UTF8String])) {
            [tool ShowActivityIndicator:self.view];
        }
        else
            [tool DisimissActivityIndicator];
        
    }
    
//    int row = 0;
//    int nType = m_pGetNewContent->GetItemType(row);
//    
//    if (m_pGetNewContent->GetItemCount() == 0) {
//        UIAlertView *alert = [[UIAlertView alloc]initWithTitle:nil message:I(@"此推送已不可用") delegate:self cancelButtonTitle:I(@"确定") otherButtonTitles:nil];
//        [alert show];
//        return;
//    }
//    
//    switch (nType)
//    {
//        case 1:
//        {
//            TBrowserItem* bItem = NULL;
//            
//            if(m_pGetNewContent->GetBrowserItemModel(row) == 0)
//            {
//                TClassItem temp;
//                bItem = &temp;
//            }
//            else
//            {
//                TCoursewareItem temp;
//                bItem=&temp;
//            }
//            
//            if (m_pGetNewContent->GetBrowserItem(row, *bItem))
//            {
//                CMNavgateItem* nav = [[CMNavgateItem alloc] init];
//                nav->bIsPush = bIsPush;
//                [nav NavgateItem:self item:*bItem];
//            }
//            break;
//        }
//        case 2:
//        {
//            TBrowserItem bItem;
//            
//            
//            if (m_pGetNewContent->GetBrowserItem(row, bItem))
//            {
//                CMNavgateItem* nav = [[CMNavgateItem alloc] init];
//                nav->bIsPush = bIsPush;
//                [nav NavgateItem:self item:bItem];
//            }
//            break;
//        }
//        case 3:
//        {
//            TExamListItem examItem;
//            
//            if (m_pGetNewContent->GetExamItem(row, examItem))
//            {
//                if (examItem.nRequirecount<=0)
//                {
//                    [tool ShowAlert:I(@"无题目")];
//                    return;
//                }
//                
//                NSString * strValue;
////                if (examItem.bIsComplete)
////                {
////                    strValue = @"view";//测验已完成
////                }else {
//                    strValue = @"start";//测验未完成，开始测验
//                //   }
//                //如果是菜单项处理相关操作
//                CMIntrodocutionViewController* examControl = [[CMIntrodocutionViewController alloc] init];
//                examControl.title = [NSString stringWithUTF8String:examItem.sTitle.c_str()
//                                     ];
//                examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//                examControl.navigationController.navigationBarHidden = NO;
//                examControl.tabBarController.tabBar.hidden = YES;
//                examControl.hidesBottomBarWhenPushed = YES;
//                examControl.bIsPush = bIsPush;
//                examControl.bAppStateIsBackground = bAppStateIsBackground;
//                NSString *strTitle = [NSString stringWithUTF8String:examItem.sTitle.c_str()];
//                NSString *strID = [NSString stringWithUTF8String:examItem.sID.c_str()];
//                NSString *strDesc = [NSString stringWithUTF8String:examItem.sDesc.c_str()];
//                NSString *strCategory = [NSString stringWithUTF8String:examItem.sCategory.c_str()];
//                NSString *strPubdate = [NSString stringWithUTF8String:examItem.sPubdate.c_str()];
//                NSString *strRequireCount = [NSString stringWithFormat:@"%d",examItem.nRequirecount];
//                NSString *strCompleteCount = [NSString stringWithFormat:@"%d",examItem.nRequirecount - examItem.nUncompletecount];
//                NSString *strQuestionCount = [NSString stringWithFormat:@"%d",examItem.nQuestioncount];
//                NSString *sortes = [NSString stringWithFormat:@"%@",NSStringFrom(examItem.sTestscores)];
//                NSString *strDuration = [NSString stringWithFormat:@"%d",examItem.nDuration];
//                NSString *strRemainTime = [NSString stringWithFormat:@"%d",examItem.nRemainTime];
//                NSString *strFullMark = [NSString stringWithFormat:@"%d",examItem.nFullmark];
//                NSString *strPassMark = [NSString stringWithFormat:@"%d",examItem.nPassmark];
//                NSString *strRankUrl = [NSString stringWithUTF8String:examItem.sRankurl.c_str()];
//                //NSString *strComplete = [NSString stringWithFormat:@"%i",examItem.bIsComplete];
//                NSString *strViewAnswer = [NSString stringWithFormat:@"%i",examItem.bViewAnswer];
//
//                
//                NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"exam",@"type",strTitle,@"title",sortes,@"sortes",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strRequireCount,@"requirecount",strCompleteCount,@"completecount",strQuestionCount,@"questioncount",strDuration,@"duration",strRemainTime,@"remaintime",strFullMark,@"fullmark",strPassMark,@"passmark",strRankUrl,@"rank",/*strComplete,@"complete",*/strViewAnswer,@"viewanswer", nil];
//                examControl.itemDic = dic;
//                
//                [self.navigationController pushViewController:examControl animated:NO];
//            }
//            
//            break;
//        }
//        case 4:
//        {
//            TExerciseListItem exerciseItem;
//            
//            if (m_pGetNewContent->GetExerciseItem(row, exerciseItem))
//            {
//                if (exerciseItem.nQuestioncount<=0)
//                {
//                    [tool ShowAlert:I(@"无题目")];
//                    return;
//                }
//                
//                //如果是菜单项处理相关操作
//                CMIntrodocutionViewController* examControl = [[CMIntrodocutionViewController alloc] init];
//                examControl.title = [NSString stringWithUTF8String:exerciseItem.GetExerciseListItemTitle()];
//                examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//                examControl.navigationController.navigationBarHidden = NO;
//                examControl.tabBarController.tabBar.hidden = YES;
//                examControl.hidesBottomBarWhenPushed = YES;
//                examControl.bIsPush = bIsPush;
//                examControl.bAppStateIsBackground = bAppStateIsBackground;
//
//                NSString *strTitle = [NSString stringWithUTF8String:exerciseItem.GetExerciseListItemTitle()];
//                NSString *strID = [NSString stringWithUTF8String:exerciseItem.GetExerciseListItemID()];
//                NSString *strDesc = [NSString stringWithUTF8String:exerciseItem.GetExerciseListItemDesc()];
//                NSString *strCategory = [NSString stringWithUTF8String:exerciseItem.GetExerciseListItemCategory()];
//                NSString *strPubdate = [NSString stringWithUTF8String:exerciseItem.GetExerciseListItemPubdate()];
//                NSString *strTotalCount = [NSString stringWithFormat:@"%d",exerciseItem.nQuestioncount];
//                NSString *strCompleteCount = [NSString stringWithFormat:@"%d",exerciseItem.nCompleteCount];
//                NSString *strCompleteUser = [NSString stringWithFormat:@"%d",exerciseItem.nUsercompletecount];
//                NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"practice",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strTotalCount,@"totalcount",strCompleteCount,@"completecount",strCompleteUser,@"completeuser", nil];
//                examControl.itemDic = dic;
//               // examControl->m_pExerciseList = m_pExerciseList;
//                examControl.nRow = 0;
//                [self.navigationController pushViewController:examControl animated:NO];
//            }
//            
//            break;
//        }
//        case 5:
//        {
//            TSurveyListItem surveyItem;
//            if (m_pGetNewContent->GetSurveyItem(row, surveyItem))
//            {
//                CMIntrodocutionViewController *SurveyView = [[CMIntrodocutionViewController alloc] init];
//                SurveyView.bIsPush = bIsPush;
//                SurveyView.bAppStateIsBackground = bAppStateIsBackground;
//
//                NSString *strTitle = [NSString stringWithUTF8String:surveyItem.sTitle];
//                NSString *strID = [NSString stringWithUTF8String:surveyItem.sID];
//                NSString *strDesc = [NSString stringWithUTF8String:surveyItem.sDesc];
//                NSString *strRequireCount = [NSString stringWithFormat:@"%d",surveyItem.nInvitecount];
//                NSString *strCompleteCount = [NSString stringWithFormat:@"%d",surveyItem.nCompletecount];
//                NSString *strExpiredate = [NSString stringWithUTF8String:surveyItem.sExpiredate];
//                NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"survey",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strExpiredate,@"expiredate",strRequireCount,@"requirecount",strCompleteCount,@"completecount", nil];
//                SurveyView.itemDic = dic;
//
//                [self.navigationController pushViewController:SurveyView animated:NO];
//            }
//            
//            break;
//        }
//        case 6:
//            
//        {
//            
//            TQAItem qaItem;
//            if (m_pGetNewContent->GetQuestionItem(row, qaItem))
//            {
//                CMQuestionDetailControl* questiondetailcontrol = [[CMQuestionDetailControl alloc] init];               //问题的详细界面
//                
//                [questiondetailcontrol SetQuestionItem:qaItem];
//                questiondetailcontrol->m_pQalist=m_pQalist;
//                if(_stricmp(qaItem.sQuestioner_username.c_str(),SETTING.GetUserName()) != 0){
//                    questiondetailcontrol.title = [NSString stringWithFormat:I(@"%@的问题"),[NSString stringWithUTF8String:qaItem.sQuestioner_fullname.c_str() ]];
//                }
//                else{
//                    questiondetailcontrol.title = [NSString stringWithFormat:I(@"我的问题")];
//                }
//                questiondetailcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//                questiondetailcontrol.navigationController.navigationBarHidden = NO;
//                questiondetailcontrol.tabBarController.tabBar.hidden = YES;
//                questiondetailcontrol.hidesBottomBarWhenPushed = YES;
//                [self.navigationController pushViewController:questiondetailcontrol animated:NO];
//                CMRELEASE(questiondetailcontrol);
//                
//                
//            }
//        }
//            break;
//        default:
//        {
//            break;
//        }
//    }
//    
//    [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];

}

#pragma mark - 下架时自动跳回
- (void)popWhenNoNermission
{
    [self.navigationController popViewControllerAnimated:YES];
}


#pragma mark - 跳转到app
//-(void)gotoCourseware
//{
//    
//    [tool DisimissActivityIndicator];
//    
//    TBrowserItem* item = new TCoursewareItem();
//    
//    if(!tempBrowser->GetItem(0, item))
//        return;
//    
//    CMNavgateItem* nav = [[CMNavgateItem alloc] init];
//    
//    
//    [nav NavgateItem:(UIViewController*)self item:*item];
//    
//    SAFEDELETE(item);
//    
//    CMRELEASE(nav);
//    
//}

-(void)gotoNews
{
    [tool DisimissActivityIndicator];
    
    TBrowserItem *item = new TBrowserItem();
    
    if(!tempBrowser->GetItem(0, item))
    {
        SAFEDELETE(item);
        return;
    }
    
    CMNavgateItem* nav = [[CMNavgateItem alloc] init];
    
    [nav NavgateItem:(UIViewController*)self item:*item];
    
    SAFEDELETE(item);
    
    CMRELEASE(nav);
    [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];
    
}

-(void)gotoExam
{
    
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
    TExamListItem item;
    m_pExamlist->GetItem(0,item);
    
    NSString *strTitle = [NSString stringWithUTF8String:item.sTitle.c_str()];
    NSString *sortes = [NSString stringWithFormat:@"%@",NSStringFrom(item.sTestscores)];
    NSString *strID = [NSString stringWithUTF8String:item.sID.c_str()];
    NSString *strDesc = [NSString stringWithUTF8String:item.sDesc.c_str()];
    NSString *strCategory = [NSString stringWithUTF8String:item.sDesc.c_str()];
    NSString *strPubdate = [NSString stringWithUTF8String:item.sPubdate.c_str()];
    NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nRequirecount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nRequirecount - item.nUncompletecount];
    NSString *strQuestionCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
    NSString *strDuration = [NSString stringWithFormat:@"%d",item.nDuration];
    NSString *strRemainTime = [NSString stringWithFormat:@"%d",item.nRemainTime];
    NSString *strFullMark = [NSString stringWithFormat:@"%d",item.nFullmark];
    NSString *strPassMark = [NSString stringWithFormat:@"%d",item.nPassmark];
    NSString *strRankUrl = [NSString stringWithUTF8String:item.sRankurl.c_str()];
    // NSString *strComplete = [NSString stringWithFormat:@"%i",item.bIsComplete];
    NSString *strViewAnswer = [NSString stringWithFormat:@"%i",item.bViewAnswer];
    NSString *strCurrNumber = [NSString stringWithFormat:@"%i", item.nCurrNumber];
    NSString *strTotalNumber = [NSString stringWithFormat:@"%i", item.nTotalNumber];
    NSString *strCompleteTime = NSStringFrom(item.sCompletetime);
    
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"exam",@"type",strTitle,@"title",sortes,@"scores",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strRequireCount,@"requirecount",strCompleteCount,@"completecount",strQuestionCount,@"questioncount",strDuration,@"duration",strRemainTime,@"remaintime",strFullMark,@"fullmark",strPassMark,@"passmark",strRankUrl,@"rank",/*strComplete,@"complete",*/ strViewAnswer,@"viewanswer", strCurrNumber, @"currnumber", strTotalNumber, @"totalnumber", strCompleteTime, @"completetime", nil];
    intro.itemDic = dic;
    CMRELEASE(dic);
    [intro setHanlder:m_pExamlist row:0];
    [self.navigationController pushViewController:intro animated:NO];
    CMRELEASE(intro);
    [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];
    
}


//-(void)gotoExercise
//{
//    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
//    intro.hidesBottomBarWhenPushed = YES;
//    
//    TExerciseListItem item;
//    if(m_pExerciselist == NULL)
//    {
//        CMRELEASE(intro);
//        return;
//    }
//    
//    m_pExerciselist->GetItem(0,item);
//    
//    NSString *strTitle = [NSString stringWithUTF8String:item.GetExerciseListItemTitle()];
//    NSString *strID = [NSString stringWithUTF8String:item.GetExerciseListItemID()];
//    NSString *strDesc = [NSString stringWithUTF8String:item.GetExerciseListItemDesc()];
//    NSString *strCategory = [NSString stringWithUTF8String:item.GetExerciseListItemCategory()];
//    NSString *strPubdate = [NSString stringWithUTF8String:item.GetExerciseListItemPubdate()];
//    NSString *strTotalCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
//    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nUsercompletecount];
//    NSString *strCompleteUser = [NSString stringWithFormat:@"%d",item.nUsercompletecount];
//    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"practice",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strTotalCount,@"totalcount",strCompleteCount,@"completecount",strCompleteUser,@"completeuser", nil];
//    intro.itemDic = dic;
//    intro->m_pExerciseList = m_pExerciselist;
//    intro.nRow = 0;
//    CMRELEASE(dic);
//    [self.navigationController pushViewController:intro animated:YES];
//    //[self gotoNav_start:indexPath.row];
//    CMRELEASE(intro);
//    
//    
//}



-(void)gotoSurvey
{
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
    TSurveyListItem item;
    m_pSurveylist->GetItem(0,item);
    NSString *strTitle = [NSString stringWithUTF8String:item.sTitle];
    NSString *strID = [NSString stringWithUTF8String:item.sID];
    NSString *strDesc = [NSString stringWithUTF8String:item.sDesc];
    NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nInvitecount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nCompletecount];
    NSString *strExpiredate = [NSString stringWithUTF8String:item.sExpiredate];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"survey",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strExpiredate,@"expiredate",strRequireCount,@"requirecount",strCompleteCount,@"completecount", nil];
    intro.itemDic = dic;
    [self.navigationController pushViewController:intro animated:NO];
    [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];
    
    
}


-(void)gotoQA
{
    
    TQAItem qaitem;
    if(!m_pQalist->GetItem(0, qaitem))
        return;
    
    
    CMQuestionDetailControl* questiondetailcontrol = [[CMQuestionDetailControl alloc] init];
    
    [questiondetailcontrol SetQuestionItem:qaitem];
    questiondetailcontrol->m_pQalist=m_pQalist;
    if(_stricmp(qaitem.sQuestioner_username.c_str(),SETTING.GetUserName()) != 0){
        questiondetailcontrol.title = [NSString stringWithFormat:I(@"%@的问题"),[NSString stringWithUTF8String:qaitem.sQuestioner_fullname.c_str()]];
    }
    else{
        questiondetailcontrol.title = [NSString stringWithFormat:I(@"我的提问")];
    }
    questiondetailcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    questiondetailcontrol.navigationController.navigationBarHidden = NO;
    questiondetailcontrol.tabBarController.tabBar.hidden = YES;
    questiondetailcontrol.hidesBottomBarWhenPushed = YES;
    //qasearchcontrol.navigationController.delegate = self;
    //添加判断textanswer 是否第一响应标记
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"isFirstResponder"];
    
   	questiondetailcontrol.view.backgroundColor = [UIColor clearColor];
    [self.navigationController pushViewController:questiondetailcontrol animated:NO];
    CMRELEASE(questiondetailcontrol);
    [self performSelector:@selector(removeLoadingPushView) withObject:self afterDelay:.3];
    
    
    
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    [self clickLeftButton];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
	
}


- (void)dealloc {
    CMRELEASE(_sId);
    CMRELEASE(_sType);
    

}

@end

////////////////////////////////////////////////////
@implementation CMGetNewView

@synthesize alert;

-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:false];
	if(self != nil)
	{
		alert = NULL;
		m_pUpdataDataListerner = NULL;
		alert = [[CustomBGAlert alloc] initWithTitle:@" " message:@" " delegate:self cancelButtonTitle:nil otherButtonTitles:nil];
		alert.tag = 200; 
		alert.delegate = self;
	}
	return self;
}
-(void)LoadData
{
    
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMGetNewUpdateDataListener();
	if(!self.Contenthandler)
	{
		CMGetNewContent* pGetNewContent= CMGetNewContent::GetInstance();
		pGetNewContent->SetListener(m_pUpdataDataListerner);
		pGetNewContent->SetUserData(BridgeObjectToC(self));
		//self.Contenthandler = pGetNewContent;
	}
	CMGetNewContent* pGetNewContent = (CMGetNewContent*)self.Contenthandler;
	pGetNewContent->Update();
	[alert show];
	[alert.indicatorView startAnimating]; 
	[self GetBrowserList];
}
#pragma mark -
#pragma mark alert
- (void)willPresentAlertView:(CustomBGAlert *)alertView {  
	if (alertView.tag == 200) {       
		[alertView setBGAlertViewX:110 alertFrameY:200 alertFrameWidth:100 alertFrameHeight:100];   
		alert.titleLabel.text = I(@"加载中…");
	}
}

- (void)dealloc {
	
	CMGetNewContent::GetInstance()->SetListener(NULL);
	self.Contenthandler = nil;
	CMRELEASE(alert);
	SAFEDELETE(m_pUpdataDataListerner);
}


@end

