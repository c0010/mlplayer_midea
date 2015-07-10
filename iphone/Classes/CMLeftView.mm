//
//  CMLeftView.m
//  MLPlayer
//
//  Created by hushengwu on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMLeftView.h"
#include "stdafx.h"
#import "CMApplicationControl.h"
#import "CMQaControl.h"
#import "CMExamControl.h"
#import "cmcategory.h"
#import "CMPersonController.h"
#import "CMGetNewControl.h"
#import "cmmyinfo.h"
//#import "JPushSDK/APService.h"
#import "CMLeftVCTableViewCell.h"
#import "CMMainControl.h"
#import "SDWebImage/UIImageView+WebCache.h"
#include "cmsettings.h"
#import "CMDownLoadControl.h"
#import "CMFavoriteControl.h"
#import "CMPersonController.h"
#import "CMRecentControl.h"
#import "CMPositionCourseControl.h"
#import "CMQListControl.h"
#import "CMSettingControl.h"
#import "CMTrainListViewController.h"
#import "CMTrainSignController.h"
#import "CMTitleController.h"
#define SETTAGESDELAY    5*60

@implementation CMLeftView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor clearColor];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshHeadImageView) name:CM_NotificationCenter_HeadImageUpdate object:nil];

        [self updateView];
    }
    return self;
}


/**
 *  不要多次使用，会重复创建label
 *
 *  @param title
 *  @param textcolor
 *  @param size
 *
 *  @return
 */
-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size
{
    UILabel* lb = [[UILabel alloc] init];
    lb.backgroundColor = [UIColor clearColor];
    lb.textAlignment = NSTextAlignmentLeft;
    lb.font = [UIFont systemFontOfSize:size];
    lb.textColor = textcolor;
    lb.text = title;
    return lb;
}

- (void)updateView
{

    double h = 0;
    if (__iOS7) {
        h += 20;
    }
    
    _headView=[[UIView alloc] init];
    
    [_headView setFrame:CGRectMake(0, h, UI_IOS_WINDOW_WIDTH, 171-h)];
    
    [self createHeadView];
    
    _tableviewlist=[[UITableView alloc] init];
    _tableviewlist.backgroundColor=[UIColor clearColor];
    _tableviewlist.delegate=self;
    _tableviewlist.dataSource=self;
    _tableviewlist.showsVerticalScrollIndicator = NO;
    [_tableviewlist setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    
    
    UIImageView *sepV = [[UIImageView alloc] init];
    [sepV setImage:[UIImage imageNamed:@"dark_sep"]];
    
    
    scrollView=[[UIScrollView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
    
    scrollView.scrollEnabled=NO;
    
    [scrollView addSubview:_headView];
    [scrollView addSubview:_tableviewlist];
    [scrollView addSubview:sepV];
    [self addSubview:scrollView];
    
    lbdict=[[NSMutableDictionary alloc]init];
    
    [_tableviewlist setFrame:CGRectMake(0, h + _headView.frame.size.height + 23, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-50- (h + _headView.frame.size.height + 23))];
    sepV.frame = CGRectMake(20, _tableviewlist.frame.origin.y - 1, 205, 1);
  
    [self initToolBar];

}

- (void)createHeadView{
    if(!_headView)
        return;
    
    [_headView.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    
    //当前用户没有更换头像时 显示提示
    
    _headimageview = [[UIImageView alloc] init];
    

    //[_headimageview setUserInteractionEnabled:YES];
    
    //
    //[_headView setUserInteractionEnabled:YES];
    
    //作为头像的mask
    [_headimageview sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetHeadimage()]] placeholderImage:[UIImage imageNamed:@"user_img_big"]];
    

    CGFloat xoff = 10;
    CGFloat yoff = 10+20;
    
    _headimageview.frame = CGRectMake(35 , yoff, 70, 70);
    
    _headimageview.layer.cornerRadius = 35;
    
    _headimageview.layer.masksToBounds = YES;

    CGPoint tempCenter = _headimageview.center;
    
    _headimageview.center = tempCenter;
    
  
    self.lblName = [self GetLabel:[NSString stringWithUTF8String: CMMyInfo::GetInstance()->GetFullName()] textcolor:[UIColor redColor] fontsize:18];
    
    self.lblName.frame = CGRectMake(CGRectGetMaxX(_headimageview.frame) + 22,yoff + 13, 100,17);
    
    [self.lblName setAdjustsFontSizeToFitWidth:YES];
    

    credit = [self GetLabel:[NSString stringWithFormat:@"%@: %d",I(@"学分"), CMMyInfo::GetInstance()->GetCredit()] textcolor:UIColorRGB(0x707c85) fontsize:14];
    credit.frame = CGRectMake(self.lblName.frame.origin.x, CGRectGetMaxY(self.lblName.frame) + 14, 140, 14);
    
    
    UIView *tapView1 = [[UIView alloc ] initWithFrame:CGRectMake(12, 24, 220, 87)];
    tapView1.backgroundColor = [UIColor clearColor];
    UITapGestureRecognizer *_tapGes = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(gotoPersonInfo)];
    [tapView1 addGestureRecognizer:_tapGes];
    
    
    UIView *tapView2 = [[UIView alloc ] initWithFrame:CGRectMake(12, 125, 220, 32)];
    tapView2.backgroundColor = [UIColor clearColor];
    UITapGestureRecognizer *_tapGes2 = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(gotoCreditInfo)];
    [tapView2 addGestureRecognizer:_tapGes2];
    
    
    rankPorgress=[[UIProgressBar alloc]initWithFrame:CGRectMake(20, CGRectGetMaxY(_headimageview.frame) + 34, 170, 15)];      //进度条
    rankPorgress.maxValue=1;
    rankPorgress.minValue=0;
    
    float temp= (float)(CMMyInfo::GetInstance()->GetValue()-CMMyInfo::GetInstance()->GetCurrentminvalue())/(float)(CMMyInfo::GetInstance()->GetNextvalue());
    
    rankPorgress.currentValue=temp;
    
    [rankPorgress setLineColor:[UIColor clearColor]];
    
    [rankPorgress setProgressColor:UIColorRGB(0xFFA200)];
    
    [rankPorgress setProgressRemainingColor:UIColorRGB(0xB7C7D3)];
    
    value = [self GetLabel:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetTitle()]  textcolor:UIColorRGB(0x707c85) fontsize:14];

    value.frame = CGRectMake(CGRectGetMaxX(rankPorgress.frame) - 2, rankPorgress.frame.origin.y-2.5, 50, 20);
    
    [value setAdjustsFontSizeToFitWidth:YES];
    [value setMinimumFontSize:12];
    value.lineBreakMode=NSLineBreakByTruncatingTail;
    value.textAlignment=NSTextAlignmentCenter;
    
    //进度条上的数字
    rankPoint=[self GetLabel:[NSString stringWithFormat:@"%d/%d",CMMyInfo::GetInstance()->GetValue(),(CMMyInfo::GetInstance()->GetNextvalue() - 1)] textcolor:UIColorRGB(0x444444) fontsize:11];
    [rankPoint setFrame:CGRectMake(0, 0, rankPorgress.frame.size.width, 15)];
    [rankPoint setTextAlignment:NSTextAlignmentCenter];
    
    [rankPorgress addSubview:rankPoint];
    
    
    UIImageView *headimageviewBg = [[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 72, 72)];
    
    headimageviewBg.center = _headimageview.center;
    
    [headimageviewBg setImage:[UIImage imageNamed:@"user_image_bg"]];
    [_headView addSubview:headimageviewBg];
    
//    UIImageView *sepV = [[UIImageView alloc] init];
//    [sepV setImage:[UIImage imageNamed:@"course_sep"]];
//    sepV.frame = CGRectMake(20, _headView.frame.size.height - 1, 205, 1);
    
    [_headView addSubview:_headimageview];
    [_headView addSubview:self.lblName];
    [_headView addSubview:jobnumber];
    
    [_headView addSubview:credit];
    [_headView addSubview:value];
    [_headView addSubview:rankPorgress];
//    [_headView addSubview:sepV];
    [scrollView addSubview:rankBtn];
    
    [_headView addSubview:tapView1];
    [_headView addSubview:tapView2];
}

- (void)initToolBar{
    UIImageView *setImgV = [[UIImageView alloc] initWithFrame:CGRectMake(32.5, UI_IOS_WINDOW_HEIGHT - 32, 16, 16)];
    [setImgV setImage:[UIImage imageNamed:@"setting"]];
    UIButton *settingBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [settingBtn setFrame:CGRectMake(32.5, UI_IOS_WINDOW_HEIGHT - 32, 68, 16)];
    settingBtn.titleLabel.font = [UIFont systemFontOfSize:15];
    [settingBtn setTitle:I(@"设置") forState:UIControlStateNormal];
    [settingBtn setTitleColor:UIColorRGB(0x707c85) forState:UIControlStateNormal];
    [settingBtn setTitleColor:UIColorRGB(0x60707b) forState:UIControlStateHighlighted];
    [settingBtn addTarget:self action:@selector(gotoSetting) forControlEvents:UIControlEventTouchUpInside];
    
    UIImageView *sepImgV = [[UIImageView alloc] initWithFrame:CGRectMake(104, UI_IOS_WINDOW_HEIGHT - 29.5, 1, 11)];
    [sepImgV setImage:[UIImage imageNamed:@"leftbar_sep"]];
    
    UIImageView *feedbackImgV = [[UIImageView alloc] initWithFrame:CGRectMake(130, UI_IOS_WINDOW_HEIGHT - 32, 16, 16)];
    [feedbackImgV setImage:[UIImage imageNamed:@"feedback"]];
    UIButton *feedbackBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [feedbackBtn setFrame:CGRectMake(130, UI_IOS_WINDOW_HEIGHT - 32, 102, 16)];
    feedbackBtn.titleLabel.font = [UIFont systemFontOfSize:15];
    [feedbackBtn setTitleColor:UIColorRGB(0x707c85) forState:UIControlStateNormal];
    [feedbackBtn setTitleColor:UIColorRGB(0x60707b) forState:UIControlStateHighlighted];
    [feedbackBtn setTitle:I(@"建议反馈") forState:UIControlStateNormal];
    [feedbackBtn addTarget:self action:@selector(gotoFeedback) forControlEvents:UIControlEventTouchUpInside];

    [scrollView addSubview:setImgV];
    [scrollView addSubview:feedbackImgV];
    [scrollView addSubview:sepImgV];
    [scrollView addSubview:settingBtn];
    [scrollView addSubview:feedbackBtn];
    
}

- (void)bindPushInfo
{
    //绑定推送数据
    [AppDelegate bindPushTagsAndAlias];
}

- (void)updateData
{
    [[NSNotificationCenter defaultCenter] postNotificationName:CM_NotificationCenter_HeadImageUpdate object:nil];
    
   	[_headimageview sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetHeadimage()]] placeholderImage:[UIImage imageNamed:@"user_img_big"]];
    
    [credit setText:[NSString stringWithFormat:@"%@: %d",I(@"学分"),CMMyInfo::GetInstance()->GetCredit()]];
    
    if([[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetPosition()] isEqualToString:@""])
        [jobnumber setText:[NSString stringWithFormat:@"%@(%@)",I(@"无"),[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetDep()]]];
    else
        [jobnumber setText:[NSString stringWithFormat:@"%@(%@)",[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetPosition()],[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetDep()]]];
    
    if(self.lblName)
        self.lblName.text =[NSString stringWithUTF8String: CMMyInfo::GetInstance()->GetFullName()] ;
    
    [self.lblName setTextColor:[UIColor blackColor]];
    
    [value setText:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetTitle()] ];//头衔
    
    
    
    [rankPoint setText:[NSString stringWithFormat:@"%d/%d",CMMyInfo::GetInstance()->GetValue(),(CMMyInfo::GetInstance()->GetNextvalue() - 1)]];
    
    float temp= (float)(CMMyInfo::GetInstance()->GetValue()-CMMyInfo::GetInstance()->GetCurrentminvalue())/(float)CMMyInfo::GetInstance()->GetNextvalue();
    
    rankPorgress.currentValue=temp;
    [_tableviewlist reloadData];

}

- (void)refreshHeadImageView{
    [_headimageview sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetHeadimage()]] placeholderImage:[UIImage imageNamed:@"user_img_big"]];
}

- (void)refreshMyInfo:(BOOL)useCache
{

    
    if(!m_pMyinfoListener)
        m_pMyinfoListener = new CMLeftMyInfoUpdateLister();
    
    CMMyInfo::GetInstance()->SetListener(m_pMyinfoListener, NULL);
    CMMyInfo::GetInstance()->SetUserData((__bridge void*)self);
    
    if(useCache)
        CMMyInfo::GetInstance()->SetRequestType(1);
    else
        CMMyInfo::GetInstance()->SetRequestType(0);
    
    CMMyInfo::GetInstance()->UpdateData();
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    CMLeftVCTableViewCell *cell = (CMLeftVCTableViewCell*)[tableView dequeueReusableCellWithIdentifier:@"personcell"];
    if (cell == nil) {
        cell = [[CMLeftVCTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"personcell"];
        cell.backgroundColor = [UIColor clearColor];
        
    }
    NSString* stitle = @"";
    UIImage*image = nil;
    NSString* strvalue = @"";
    

    if (indexPath.row == 0)
    {
        image = [UIImage imageNamed:@"positioncourse_icon"];
        stitle = I(@"职位课程");
        strvalue = [NSString stringWithFormat:@"%d",CMMyInfo::GetInstance()->GetPositionCourseCount()];
        
    }else if (indexPath.row == 1) {
        image = [UIImage imageNamed:@"studyrecord"];
        stitle = I(@"学习旅程");
        strvalue = [NSString stringWithFormat:@"%d",CMMyInfo::GetInstance()->GetStudyrecord()];
//    }else if (indexPath.row == 2) {
//        image = [UIImage imageNamed:@"mysign"];
//        stitle = I(@"我的签到");
//        
//        for(int i=0;i<CMCategory::GetInstance()->TopItemCount();i++) {
//            
//            CMCategoryItem* pCategoryItem = CMCategory::GetInstance()->GetTopItem(i);
//            assert(pCategoryItem);
//            
//            NSString* strType	= [NSString stringWithUTF8String:pCategoryItem->sType];
//            if ([strType caseInsensitiveCompare:@"app"] == 0){
//                for (int j = 0; j < pCategoryItem->ChildItemCount(); j++)
//                {
//                    CMCategoryItem *item = pCategoryItem->GetChildItem(j);
//                    
//                    if (strcmp(item->sType,"train_signin") == 0)
//                    {
//                        strvalue = [NSString stringWithFormat:@"%d",item->nItemcount ];
//                    }
//                }
//            }
//        }
//        
//        
//        //strvalue = [NSString stringWithFormat:@"%d",CMMyInfo::GetInstance()->GetNoSigninCount()];
//    }else if (indexPath.row == 3) {
//        image = [UIImage imageNamed:@"mytrain"];
//        stitle = I(@"我的培训班");
    }else if (indexPath.row == 2) {
        
        image = [UIImage imageNamed:@"myqa"];
        stitle = I(@"我的问答");

    }else if (indexPath.row == 3) {
        
        image = [UIImage imageNamed:@"down"];
        stitle = I(@"我的下载");
        strvalue = [NSString stringWithFormat:@"%d",CMCourseDownload::GetInstance()->GetItemCount()];

    }else if (indexPath.row == 4) {
        
        image = [UIImage imageNamed:@"favorite"];
        stitle = I(@"我的收藏");
        strvalue = [NSString stringWithFormat:@"%d",CMFavorites::GetInstance()->GetItemCount()];

    }

    
//    if(strvalue != nil && [strvalue length] > 0 && [strvalue integerValue]>0)
//    {
//        if ([strvalue integerValue]>99) {
//            strvalue=@"99";
//        }
//        
//        CGSize size = CGSizeMake(100,10);
//        NSString *strbadge = [NSString stringWithFormat:@" %@ ",strvalue];
//        size = [strbadge sizeWithFont:[UIFont systemFontOfSize:11] constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
//        CGFloat badge_w = (size.width > 24) ? size.width : 24;
//        cell.badgeIcon.frame = CGRectMake(133, 16, badge_w, 12);
//        
//        [cell.badgeIcon setTitle:strbadge forState:UIControlStateNormal];
//        
//        cell.badgeIcon.hidden = NO;
//        
//        if([strvalue integerValue]==0)
//            cell.badgeIcon.hidden = YES;
//        
//    }
//    else{
//        cell.badgeIcon.hidden = YES;
//    }
    
    cell.LeftImageView.image = image;
    cell.LeftTitle.text = stitle;
    
//    if (indexPath.row == 0) {
//        cell.selectionStyle = UITableViewCellSelectionStyleNone;
//        cell.accessoryImageView.hidden = YES;
//    }
//    else{
        UIImageView *sv = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 320, 60)];
        sv.image = [UIImage imageNamed:@"leftbar_cell_select_bg"];
        cell.selectedBackgroundView = sv;
//        cell.accessoryImageView.hidden = NO;
//    }
    
    cell.accessoryType = UITableViewCellAccessoryNone;
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 52;
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return 5;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    switch (indexPath.row) {
        case 0:
        {
            
            CMPositionCourseControl* coursecontrol=[[CMPositionCourseControl alloc]init];
            [self closeDrawerAndEnterViewController:coursecontrol ];
            
        }
            break;
        case 1:
        {
            
            if (CMGlobal::TheOne().IsOffline())
            {
                NSString *str = [NSString stringWithFormat:I(@"网络不给力"),I(@"学习旅程")];;
                [tool ShowAlert:str];
                return ;
            }
            CMRecentControl* recentcontrol = [[CMRecentControl alloc] init];
            
            recentcontrol.title = I(@"学习旅程");
            recentcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            
            [self closeDrawerAndEnterViewController:recentcontrol];
            
        }
            break;
//        case 2:
//        {
//            CMTrainSignController * signControl = [[CMTrainSignController alloc] init];
//            
//            signControl.title = I(@"我的签到");
//            signControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//            
//            
//            [self closeDrawerAndEnterViewController:signControl];
//    
//            
//        }
//            break;
//        
//        case 3:
//        {
//            CMTrainListViewController * trainControl = [[CMTrainListViewController alloc] init];
//            
//            trainControl.title = I(@"我的培训班");
//            trainControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
//            
//            
//            [self closeDrawerAndEnterViewController:trainControl];
//            
//        }
//            break;
        
        case 2:
        {
            CMQListControl* qlistcontrol = [[CMQListControl alloc] init];
            qlistcontrol.bIsShowTagbar = YES;
            qlistcontrol.bIsShowTabbar = NO;

            qlistcontrol.title = I(@"我的回答");
            qlistcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            qlistcontrol.hidesBottomBarWhenPushed = YES;
            
            [self closeDrawerAndEnterViewController:qlistcontrol];
            
            
        }
            break;
            
        case 3:
        {
            CMDownLoadControl * downLoadControl = [[CMDownLoadControl alloc] init];
            
            downLoadControl.title = I(@"我的下载");
            downLoadControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            
            
            [self closeDrawerAndEnterViewController:downLoadControl];

            
            
            
        }
            break;
        case 4:
        {
            CMFavoriteControl* favoriteControl = [[CMFavoriteControl alloc] init];
            
            favoriteControl.title = I(@"我的收藏");
            favoriteControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            
            [self closeDrawerAndEnterViewController:favoriteControl];

            
        }
            break;
            
        default:
            break;
    }
    
    //[tableView deselectRowAtIndexPath:indexPath animated:NO];
}

-(void)closeDrawerAndEnterViewController:(UIViewController*)vc
{
    [self.navigationcontrollerdelegate closeSideBar];
    
    [self.navigationcontrollerdelegate.navigationController pushViewController:vc animated:NO];
    
}

- (void)gotoPersonInfo{
    CMPersonController *prsnCtr = [[CMPersonController alloc] init];
    prsnCtr.title = I(@"个人信息");
    [self closeDrawerAndEnterViewController:prsnCtr];
}

- (void)gotoCreditInfo{
    if (CMGlobal::TheOne().IsOffline())
    {
        NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
        [tool ShowAlert:str];
        return ;
    }
    
    CMTitleController* titleControl = [[CMTitleController alloc] init];

    titleControl.hidesBottomBarWhenPushed = NO;
    [self closeDrawerAndEnterViewController:titleControl];
}

- (void)gotoSetting{
    CMSettingControl* settingControl = [[CMSettingControl alloc] init];
    settingControl.title = I(@"设置");
    [self closeDrawerAndEnterViewController:settingControl];
}

- (void)gotoFeedback{
    CMFeedbackControl *feedback = [[CMFeedbackControl alloc] init];
    feedback.title = I(@"建议反馈");
    [self closeDrawerAndEnterViewController:feedback];

}


- (void)dealloc{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    CMMyInfo::GetInstance()->SetListener(NULL, NULL);
    CMMyInfo::GetInstance()->SetUserData(NULL);
    SAFEDELETE(m_pMyinfoListener);
    
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/



@end
