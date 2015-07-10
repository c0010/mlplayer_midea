    //
//  CMApplicationControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-16.
//  Copyright 2011 w. All rights reserved.
//

#import "CMApplicationControl.h"
#import "CMAddressControl.h"
#import "CMDownLoadControl.h"
#import "CMExamControl.h"
#import "CMRecentControl.h"
#import "CMFavoriteControl.h"
#import "CMSurveyListControl.h"
#import "CMPersonController.h"
#import "CMSettingControl.h"
#import "CMTableView.h"
#import "CMQaControl.h"
#import "CMShakeController.h"
#import "CMShakeListController.h"
#import "CMFindgroupViewController.h"
#import "CMGroupNameViewController.h"
#import "CMChatViewController.h"
#import "cmmyinfo.h"
#import "cmundone.h"
#import "CMTrainApplyController.h"
#import "CMTrainSignController.h"
#import "CMAppVCTableViewCell.h"
#import "cmmyinfo.h"
#import "CMConfig.h"
#import "CMAppVCCollectionViewCell.h"
#import "CMCoreDataUtils.h"
#import "CMSearchQRCode.h"
#import "CMPushMessageBoxViewController.h"

@implementation CMApplicationControl
@synthesize Parentid,strTitle;


#define kCellIdentifier @"com.apple.CMApplicationControl.CellIdentifier"



#pragma mark UITableView data source methods

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

	CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(indexPath.row);
	assert(m_pCategoryChildItem);

	NSString* strType = [NSString stringWithUTF8String:m_pCategoryChildItem->sType];
	NSString* strtitle = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
	
    nSelectRow = 0;
    
    if ([strType caseInsensitiveCompare:@"down"] == 0) {
        CMDownLoadControl * downLoadControl = [[CMDownLoadControl alloc] init];
        
        downLoadControl.title = strtitle;//I(@"下载管理");
        downLoadControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        downLoadControl.navigationController.navigationBarHidden = NO;
        downLoadControl.tabBarController.tabBar.hidden = YES;
        downLoadControl.hidesBottomBarWhenPushed = YES;
        downLoadControl.navigationController.delegate = self;		
        [self.navigationController pushViewController:downLoadControl animated:YES];
        
    }
    else if ([strType caseInsensitiveCompare:@"contacts"] == 0) {
        
//        if(CMGlobal::TheOne().IsOffline())
//        {
//            
//            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];;
//            [tool ShowAlert:str];
//            return ;
//        }
        
        
        CMAddressControl * addressControl = [[CMAddressControl alloc] init];
        
        addressControl.title = strtitle;//I(@"通讯录");
        addressControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        addressControl.navigationController.navigationBarHidden = NO;
        addressControl.tabBarController.tabBar.hidden = YES;
        addressControl.hidesBottomBarWhenPushed = YES;
        addressControl.navigationController.delegate = self;	
        [self.navigationController pushViewController:addressControl animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"learnfile"] == 0) {
        CMRecentControl* recentcontrol = [[CMRecentControl alloc] init];
        
        recentcontrol.title = strtitle;//I(@"最近访问");
        recentcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        recentcontrol.navigationController.navigationBarHidden = NO;
        recentcontrol.tabBarController.tabBar.hidden = YES;
        recentcontrol.hidesBottomBarWhenPushed = YES;
        recentcontrol.navigationController.delegate = self;
        recentcontrol.view.backgroundColor = [UIColor clearColor];
        [self.navigationController pushViewController:recentcontrol animated:YES];
    
    }else if ([strType caseInsensitiveCompare:@"favorites"] == 0) {
        CMFavoriteControl* favoriteControl = [[CMFavoriteControl alloc] init];
        
        favoriteControl.title = strtitle;//I(@"我的收藏");
        favoriteControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        favoriteControl.navigationController.navigationBarHidden = NO;
        favoriteControl.tabBarController.tabBar.hidden = YES;
        favoriteControl.hidesBottomBarWhenPushed = YES;
        favoriteControl.navigationController.delegate = self;
        favoriteControl.view.backgroundColor = [UIColor clearColor];		
        [self.navigationController pushViewController:favoriteControl animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"survey"] == 0) {
        
        nSelectRow = indexPath.row;

//        if(CMGlobal::TheOne().IsOffline())
//        {
//            
//            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
//            [tool ShowAlert:str];
//            return ;
//        }
        CMSurveyListControl* favoriteControl = [[CMSurveyListControl alloc] init];
        favoriteControl.title = strtitle;//I(@"在线调研");
                                         //[favoriteControl OpenSurvey:strTitle :m_pCategoryChildItem->sID];
        favoriteControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        favoriteControl.navigationController.navigationBarHidden = NO;
        favoriteControl.tabBarController.tabBar.hidden = YES;
        favoriteControl.hidesBottomBarWhenPushed = YES;
        favoriteControl.navigationController.delegate = self;
        favoriteControl.view.backgroundColor = [UIColor clearColor];		
        [self.navigationController pushViewController:favoriteControl animated:YES];
    }
    else if ([strType caseInsensitiveCompare:@"qa"] == 0) {
        CMQaControl* qaControl = [[CMQaControl alloc] init];
        qaControl.title = I(@"全部");//全部问答
        qaControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;	
        qaControl.navigationController.navigationBarHidden = NO;
        qaControl.tabBarController.tabBar.hidden = YES;
        qaControl.hidesBottomBarWhenPushed = YES;
        
        //添加判断qa 是否刷新的标记
//        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
//        [ud setObject:@"1" forKey:@"isRefresh"];
        
        [[self navigationController] pushViewController:qaControl animated:YES];
    
    }else if ([strType caseInsensitiveCompare:@"setting"] == 0) {
            CMSettingControl* settingControl = [[CMSettingControl alloc] init];
            settingControl.title = strtitle;
            settingControl.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
            settingControl.navigationController.navigationBarHidden = NO;
            settingControl.tabBarController.tabBar.hidden = YES;
            settingControl.hidesBottomBarWhenPushed = YES;
            [self.navigationController pushViewController:settingControl animated:YES];
        //	
    }else if ([strType caseInsensitiveCompare:@"feedback"] == 0) {
//        if (CMGlobal::TheOne().IsOffline())
//        {
//            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
//            [tool ShowAlert:str];
//            return ;
//        }
        CMFeedbackControl* feedbackControl = [[CMFeedbackControl alloc] init];
        feedbackControl.title = strtitle;
        feedbackControl.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
        feedbackControl.navigationController.navigationBarHidden = NO;
        feedbackControl.tabBarController.tabBar.hidden = YES;
        feedbackControl.hidesBottomBarWhenPushed = YES;
        [self.navigationController pushViewController:feedbackControl animated:YES];
        //	
    }else if ([strType caseInsensitiveCompare:@"courseshake"] == 0) {
        
        CMShakeListController* shakeControl=[[CMShakeListController alloc]init];
        shakeControl.title=I(@"摇一摇");
        shakeControl.openShake = YES;
        shakeControl.hidesBottomBarWhenPushed=YES;

        [self.navigationController pushViewController:shakeControl animated:YES];
        
        
    }else if ([strType caseInsensitiveCompare:@"coursewetools"] == 0) {
        
        [tool clickedWE];
        
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
            
            if ([[UIApplication sharedApplication] canOpenURL:we_appurl]) {
                [[UIApplication sharedApplication] openURL:we_appurl];
            }
            else{
                
                //打开app store的we页面
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:kWetoolsDownloadUrl]];
            }
            
        }
        
    }else if ([strType caseInsensitiveCompare:@"exam"] == 0) {
        
        nSelectRow = indexPath.row;

		CMExamControl * examControl = [[CMExamControl alloc] init];
        examControl.bIsShowTagbar = YES;
        examControl.title=I(@"exam");
        examControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:examControl animated:YES];
        
		
    }else if ([strType caseInsensitiveCompare:@"train_apply"] == 0) {
        
        nSelectRow = indexPath.row;
        
        CMTrainApplyController * applyControl = [[CMTrainApplyController alloc] init];
        
        applyControl.title=I(@"培训报名");
        applyControl.view.backgroundColor = [UIColor clearColor];
        applyControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:applyControl animated:YES];
        
        
    }
    else if ([strType caseInsensitiveCompare:@"train_signin"] == 0) {
        
        nSelectRow = indexPath.row;
        
        CMTrainSignController * signControl = [[CMTrainSignController alloc] init];
        
        signControl.title=I(@"培训签到");
        signControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:signControl animated:YES];
        
        
    }
    else {
    
//        [tool ShowAlert:I(@"系统配置出错，请与管理员联系!")];

    }

    [tableView deselectRowAtIndexPath:indexPath animated:NO];


}

-(void)viewWillAppear:(BOOL)animated 
{ 
    [super viewWillAppear:animated];
}



#pragma mark - UICollectionView Delegate

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return m_pCategoryItem->FrontChildItemCount();
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath
{
    CGFloat collCellWidth = collectionViewList.bounds.size.width / 3;
    return CGSizeMake(collCellWidth, collCellWidth);
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section
{
    return 0;
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section
{
    return 0;
}


- (UICollectionViewCell*)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    CMAppVCCollectionViewCell *collCell = [collectionView dequeueReusableCellWithReuseIdentifier:@"collCell" forIndexPath:indexPath];
    if (collCell != nil)
    {
        CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(indexPath.row);
        assert(m_pCategoryChildItem);
        NSString* strID = [NSString stringWithUTF8String:m_pCategoryChildItem->sID];
        UIImage*image = nil;
        if ([strID caseInsensitiveCompare:@"survey"] == 0) {
            image = [UIImage imageNamed:@"more_survey"];//调研
            
            nSurveyCount = m_pCategoryChildItem->nItemcount;
            
            if (nSurveyCount == -1)
            {
                collCell.badgeIcon.hidden = YES;
            }
            if (nSurveyCount == 0) {
                collCell.badgeIcon.hidden = YES;
            }
            else{
                collCell.badgeIcon.hidden = NO;
                if (nSurveyCount>99) {
                    nSurveyCount = 99;
                }
                
                NSString *num = [NSString stringWithFormat:@"%d",nSurveyCount];
                [collCell.badgeIcon setTitle:num forState:UIControlStateNormal];
            }
            
        }else if ([strID caseInsensitiveCompare:@"exam"] == 0) {
            image = [UIImage imageNamed:@"more_exam"];//测验
            
            nExamCount = m_pCategoryChildItem->nItemcount;
            
            if (nExamCount == -1)
            {
                collCell.badgeIcon.hidden = YES;
            }
            if (nExamCount == 0) {
                collCell.badgeIcon.hidden = YES;
            }
            else{
                collCell.badgeIcon.hidden = NO;
                if (nExamCount>99) {
                    nExamCount = 99;
                }
                NSString *numStr = [NSString stringWithFormat:@"%d",nExamCount];
                [collCell.badgeIcon setTitle:numStr forState:UIControlStateNormal];
            }
            
            
        }else if ([strID caseInsensitiveCompare:@"interaction"] == 0) {
            image = [UIImage imageNamed:@"more_interaction"];//互动
            int messageCount = [CMCoreDataUtils fetchUnreadAmount];
            if (messageCount == 0)
            {
                collCell.badgeIcon.hidden = YES;
            }
            else
            {
                collCell.badgeIcon.hidden = NO;
                if (messageCount > 99)
                {
                    messageCount = 99;
                }
                NSString *numStr = [NSString stringWithFormat:@"%d",messageCount];
                [collCell.badgeIcon setTitle:numStr forState:UIControlStateNormal];
            }
            
        }else if ([strID caseInsensitiveCompare:@"courseshake"] == 0) {
            image = [UIImage imageNamed:@"more_shake"];//摇一摇
        }else if ([strID caseInsensitiveCompare:@"coursesweep"] == 0) {
            image = [UIImage imageNamed:@"more_sweep"];//扫一扫
        }else if ([strID caseInsensitiveCompare:@"coursewetools"] == 0) {
            image = [UIImage imageNamed:@"more_wetool"];//we课件
            
        }else if ([strID caseInsensitiveCompare:@"messages"] == 0) {
            image = [UIImage imageNamed:@"more_messagebox"];//消息盒子
            
        }
        
        
//        else if ([strID caseInsensitiveCompare:@"setting"] == 0) {
//            image = [UIImage imageNamed:@"setting"];
//            
//        }else if ([strID caseInsensitiveCompare:@"qa"] == 0) {
//            image = [UIImage imageNamed:@"qa"];//问答
//            
//        }else if ([strID caseInsensitiveCompare:@"feedback"] == 0) {
//            image = [UIImage imageNamed:@"feedback"];
//            
//        }else if ([strID caseInsensitiveCompare:@"favorites"] == 0) {
//            
//            image = [UIImage imageNamed:@"favorite"];
//        }else if ([strID caseInsensitiveCompare:@"down"] == 0)
//        {
//            image = [UIImage imageNamed:@"down"];//下载
//            
//        }else if ([strID caseInsensitiveCompare:@"contacts"] == 0) {
//            image = [UIImage imageNamed:@"contacts"];
//            
//        }else if ([strID caseInsensitiveCompare:@"train_signin"] == 0) {
//            image = [UIImage imageNamed:@"more_trainsign"];//培训签到
//            
//            nNoSignCount = m_pCategoryChildItem->nItemcount;
//            
//            if (nNoSignCount <= 0) {
//                collCell.badgeIcon.hidden = YES;
//            }
//            else{
//                collCell.badgeIcon.hidden = NO;
//                if (nNoSignCount>99) {
//                    nNoSignCount = 99;
//                }
//                NSString *numStr = [NSString stringWithFormat:@"%d",nNoSignCount];
//                [collCell.badgeIcon setTitle:numStr forState:UIControlStateNormal];
//            }
//            
//        }else if ([strID caseInsensitiveCompare:@"train_apply"] == 0) {
//            image = [UIImage imageNamed:@"more_trainapply"];//培训报名
//        }else if([strID caseInsensitiveCompare:@"learnfile"] == 0) {
//            image = [UIImage imageNamed:@"studyrecord"];
//            
//        }
        
        collCell.imaView.image = image;
        
        collCell.titleLab.text = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
    }
    return collCell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    
    CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(indexPath.row);
    assert(m_pCategoryChildItem);
    
    NSString* strType = [NSString stringWithUTF8String:m_pCategoryChildItem->sID];
    NSString* strtitle = [NSString stringWithUTF8String:m_pCategoryChildItem->sTitle];
    
    nSelectRow = 0;
    
    if  ([strType caseInsensitiveCompare:@"survey"] == 0) {
        
        nSelectRow = indexPath.row;
        
        //        if(CMGlobal::TheOne().IsOffline())
        //        {
        //
        //            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
        //            [tool ShowAlert:str];
        //            return ;
        //        }
        CMSurveyListControl* favoriteControl = [[CMSurveyListControl alloc] init];
        favoriteControl.title = strtitle;//I(@"在线调研");
        //[favoriteControl OpenSurvey:strTitle :m_pCategoryChildItem->sID];
        favoriteControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        favoriteControl.navigationController.navigationBarHidden = NO;
        favoriteControl.tabBarController.tabBar.hidden = YES;
        favoriteControl.hidesBottomBarWhenPushed = YES;
        favoriteControl.navigationController.delegate = self;
        favoriteControl.view.backgroundColor = [UIColor clearColor];
        [self.navigationController pushViewController:favoriteControl animated:YES];
    }
    else if  ([strType caseInsensitiveCompare:@"exam"] == 0) {
        
        nSelectRow = indexPath.row;
        
        CMExamControl * examControl = [[CMExamControl alloc] init];
        examControl.bIsShowTagbar = YES;
        examControl.title=strtitle;
        examControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:examControl animated:YES];
        
        
    }else if ([strType caseInsensitiveCompare:@"interaction"] == 0) {
        
        
        [tool ShowAlert:I(@"开发中，敬请期待")];
        //以下互动模块暂未实现
        /*
        CMInteractViewController *interactController = [[CMInteractViewController alloc]init];
        interactController.hidesBottomBarWhenPushed=YES;
        
        XmppHandler.interactNavigationController = interactController.navigationController;
        
        [self.navigationController pushViewController:interactController animated:YES];
         */
    }else if ([strType caseInsensitiveCompare:@"courseshake"] == 0) {
        
        CMShakeListController* shakeControl=[[CMShakeListController alloc]init];
        shakeControl.openShake = YES;
        shakeControl.title=strtitle;
        shakeControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:shakeControl animated:YES];
        
        
    }else if ([strType caseInsensitiveCompare:@"coursesweep"] == 0) {
        CMSearchQRCode *QRcodeControl = [[CMSearchQRCode alloc]init];
        QRcodeControl.title = strtitle;
        [self.navigationController pushViewController:QRcodeControl animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"coursewetools"] == 0) {
        
        [tool ShowAlert:I(@"开发中，敬请期待")];
        //以下点击we工具的方法暂时不实现
        
        /*
        [tool clickedWE];
        
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
            
            if ([[UIApplication sharedApplication] canOpenURL:we_appurl]) {
                [[UIApplication sharedApplication] openURL:we_appurl];
            }
            else{
                
                //打开app store的we页面
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:kWetoolsDownloadUrl]];
            }
            
        }
         */
        
    }else if ([strType caseInsensitiveCompare:@"messages"] == 0) {
        
        CMPushMessageBoxViewController *pushMsgController = [[CMPushMessageBoxViewController alloc]init];
        pushMsgController.title = strtitle;
        [self.navigationController pushViewController:pushMsgController animated:YES];
    }
    
    
    else if ([strType caseInsensitiveCompare:@"learnfile"] == 0) {
        CMRecentControl* recentcontrol = [[CMRecentControl alloc] init];
        
        recentcontrol.title = strtitle;//I(@"最近访问");
        recentcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        recentcontrol.navigationController.navigationBarHidden = NO;
        recentcontrol.tabBarController.tabBar.hidden = YES;
        recentcontrol.hidesBottomBarWhenPushed = YES;
        recentcontrol.navigationController.delegate = self;
        recentcontrol.view.backgroundColor = [UIColor clearColor];
        [self.navigationController pushViewController:recentcontrol animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"favorites"] == 0) {
        CMFavoriteControl* favoriteControl = [[CMFavoriteControl alloc] init];
        
        favoriteControl.title = strtitle;//I(@"我的收藏");
        favoriteControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        favoriteControl.navigationController.navigationBarHidden = NO;
        favoriteControl.tabBarController.tabBar.hidden = YES;
        favoriteControl.hidesBottomBarWhenPushed = YES;
        favoriteControl.navigationController.delegate = self;
        favoriteControl.view.backgroundColor = [UIColor clearColor];
        [self.navigationController pushViewController:favoriteControl animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"down"] == 0) {
        CMDownLoadControl * downLoadControl = [[CMDownLoadControl alloc] init];
        
        downLoadControl.title = strtitle;//I(@"下载管理");
        downLoadControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        downLoadControl.navigationController.navigationBarHidden = NO;
        downLoadControl.tabBarController.tabBar.hidden = YES;
        downLoadControl.hidesBottomBarWhenPushed = YES;
        downLoadControl.navigationController.delegate = self;
        [self.navigationController pushViewController:downLoadControl animated:YES];
        
    }
    else if ([strType caseInsensitiveCompare:@"qa"] == 0) {
        CMQaControl* qaControl = [[CMQaControl alloc] init];
        qaControl.title = I(@"全部");//全部问答
        qaControl.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
        qaControl.navigationController.navigationBarHidden = NO;
        qaControl.tabBarController.tabBar.hidden = YES;
        qaControl.hidesBottomBarWhenPushed = YES;
        
        //添加判断qa 是否刷新的标记
        //        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        //        [ud setObject:@"1" forKey:@"isRefresh"];
        
        [[self navigationController] pushViewController:qaControl animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"setting"] == 0) {
        CMSettingControl* settingControl = [[CMSettingControl alloc] init];
        settingControl.title = strtitle;
        settingControl.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
        settingControl.navigationController.navigationBarHidden = NO;
        settingControl.tabBarController.tabBar.hidden = YES;
        settingControl.hidesBottomBarWhenPushed = YES;
        [self.navigationController pushViewController:settingControl animated:YES];
        //
    }else if ([strType caseInsensitiveCompare:@"feedback"] == 0) {
        //        if (CMGlobal::TheOne().IsOffline())
        //        {
        //            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
        //            [tool ShowAlert:str];
        //            return ;
        //        }
        CMFeedbackControl* feedbackControl = [[CMFeedbackControl alloc] init];
        feedbackControl.title = strtitle;
        feedbackControl.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
        feedbackControl.navigationController.navigationBarHidden = NO;
        feedbackControl.tabBarController.tabBar.hidden = YES;
        feedbackControl.hidesBottomBarWhenPushed = YES;
        [self.navigationController pushViewController:feedbackControl animated:YES];
        //
    }else if([strType caseInsensitiveCompare:@"contacts"] == 0) {
        
        //        if(CMGlobal::TheOne().IsOffline())
        //        {
        //
        //            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];;
        //            [tool ShowAlert:str];
        //            return ;
        //        }
        
        
        CMAddressControl * addressControl = [[CMAddressControl alloc] init];
        
        addressControl.title = strtitle;//I(@"通讯录");
        addressControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        addressControl.navigationController.navigationBarHidden = NO;
        addressControl.tabBarController.tabBar.hidden = YES;
        addressControl.hidesBottomBarWhenPushed = YES;
        addressControl.navigationController.delegate = self;
        addressControl.openAutoKeyboard = YES;
        [self.navigationController pushViewController:addressControl animated:YES];
        
    }else if ([strType caseInsensitiveCompare:@"train_apply"] == 0) {
        
        nSelectRow = indexPath.row;
        
        CMTrainApplyController * applyControl = [[CMTrainApplyController alloc] init];
        
        applyControl.title=I(@"培训报名");
        applyControl.view.backgroundColor = [UIColor clearColor];
        applyControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:applyControl animated:YES];
        
        
    }
    else if ([strType caseInsensitiveCompare:@"train_signin"] == 0) {
        
        nSelectRow = indexPath.row;
        
        CMTrainSignController * signControl = [[CMTrainSignController alloc] init];
        
        signControl.title=I(@"培训签到");
        signControl.hidesBottomBarWhenPushed=YES;
        
        [self.navigationController pushViewController:signControl animated:YES];
        
        
    }
    else {
        
        //        [tool ShowAlert:I(@"系统配置出错，请与管理员联系!")];
        
    }
    
    [collectionView deselectItemAtIndexPath:indexPath animated:YES];
    
    
}

#pragma mark system function

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

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

- (void)updateView{
    if(collectionViewList)
        [collectionViewList reloadData];
}

- (void)updateCategory{
    m_pCategoryItem = CMCategory::GetInstance()->GetTopItem(Parentid);
}

- (void)updateLeftHeadImage{
   
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateView) name:CM_NotificationCenter_ReloadView object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateCategory) name:CM_NotificationCenter_ReloadCategory object:nil];

    nSelectRow = 0;

    self.titleLabel.text = self.navigationItem.title;
    self.navigationItem.leftBarButtonItem = nil;
    
    CGRect f     = [[self view] bounds];
	
    f.origin.x   = 0;
    f.origin.y   = 00;
    f.size.width = UI_IOS_WINDOW_WIDTH;
    
    m_pCategoryItem = CMCategory::GetInstance()->GetTopItem(Parentid);
    
    f.size.height   = 44*m_pCategoryItem->FrontChildItemCount();

    CGFloat itemWidth = self.view.bounds.size.height / 3;
    f.size.height = ceil(itemWidth * m_pCategoryItem->FrontChildItemCount() / 3.0);
    UICollectionViewFlowLayout *flowLayout = [[UICollectionViewFlowLayout alloc]init];
    [flowLayout setScrollDirection:UICollectionViewScrollDirectionVertical];
    collectionViewList = [[UICollectionView alloc]initWithFrame:f collectionViewLayout:flowLayout];
    collectionViewList.scrollEnabled = NO;
    collectionViewList.delegate = self;
    collectionViewList.dataSource = self;
    collectionViewList.backgroundColor = [UIColor clearColor];
    collectionViewList.layer.borderWidth = 0;
    [collectionViewList registerClass:[CMAppVCCollectionViewCell class] forCellWithReuseIdentifier:@"collCell"];
    
    [self.view addSubview:collectionViewList];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(surveycountchanged:) name:@"surveycountchange" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(examcountchanged:) name:@"examcountchange" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(signcountchanged:) name:@"signcountchange" object:nil];

}


//完成一个调研后调研数-1
- (void)surveycountchanged:(id)sender
{
    CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(nSelectRow);
    
    if (!m_pCategoryChildItem) {
        return;
    }
    if(!m_pCategoryItem)
        return;
    
    assert(m_pCategoryChildItem);
    
    if (nSurveyCount > 0) {
        nSurveyCount--;
    }
    m_pCategoryChildItem->nItemcount = nSurveyCount;
    [collectionViewList reloadData];
}

//完成一个测验后调研数-1
- (void)examcountchanged:(id)sender
{
    CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(nSelectRow);
    if (!m_pCategoryChildItem) {
        return;
    }
    
    if(!m_pCategoryItem)
        return;
    
    assert(m_pCategoryChildItem);
    if (nExamCount > 0) {
        nExamCount--;
    }
    m_pCategoryChildItem->nItemcount = nExamCount;

    [collectionViewList reloadData];
}

//完成一个签到后签到数-1
- (void)signcountchanged:(id)sender
{
    CMCategoryItem* m_pCategoryChildItem = m_pCategoryItem->GetChildItem(nSelectRow);
    if (!m_pCategoryChildItem) {
        return;
    }
    
    if(!m_pCategoryItem)
        return;
    
    assert(m_pCategoryChildItem);
    if (nNoSignCount > 0) {
        nNoSignCount--;
    }
    m_pCategoryChildItem->nItemcount = nNoSignCount;
    
    [collectionViewList reloadData];
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
}


- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"surveycountchange" object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"examcountchange" object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:CM_NotificationCenter_ReloadView object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:CM_NotificationCenter_ReloadCategory object:nil];
    
    CMRELEASE(TableViewList);

}


@end
