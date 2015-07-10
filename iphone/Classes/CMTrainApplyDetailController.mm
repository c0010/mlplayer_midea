//
//  CMTrainApplyDetailController.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainApplyDetailController.h"
#import "CMLabel.h"
#import "CMTrainApplyView.h"


@implementation CMTrainApplyDetailController


-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.titleLabel.text = I(@"报名详情") ;
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    if (self.bIsPush) {
        [self CallBackSuccess];
    }else
        [self initView];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    //flag状态改变时移除上一层tableview的某一行
    if (![stateStr isEqualToString:NSStringFrom(curItem->sFlag)]) {
        [self.TrainApplyView refreshTableView];
    }
}

-(void)initView
{
    for (UIView *subview in self.view.subviews) {
        [subview removeFromSuperview];
    }
    
    if (stateStr == nil || [stateStr isEqualToString:@""]) {
        stateStr = [[NSString alloc]initWithUTF8String:curItem->sFlag.c_str()];
    }
    
    
    UIButton *cancelApply = [UIButton buttonWithType:UIButtonTypeCustom];
    [cancelApply setFrame:CGRectMake(0, 0, 60, 40)];
    [cancelApply setTitle:I(@"取消报名") forState:UIControlStateNormal];
    [cancelApply.titleLabel setFont:[UIFont systemFontOfSize:14]];
    [cancelApply setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [cancelApply addTarget:self action:@selector(cancelApply:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem *rightbaritem = [[UIBarButtonItem alloc]initWithCustomView:cancelApply];
    if (curItem->nEnableCancelApply && [NSStringFrom(curItem->sFlag) isEqualToString:@"applied"]) {
        self.navigationItem.rightBarButtonItem = rightbaritem;
    }else
        self.navigationItem.rightBarButtonItem = nil;
    
    
    
    //画出界面
    UIScrollView *scrollView = [[UIScrollView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-64)];
    [self.view addSubview:scrollView];
    
    UILabel *titleLab=[[UILabel alloc]initWithFrame:CGRectMake(10, 24, UI_IOS_WINDOW_WIDTH-20, 20)];
    [titleLab setFont:[UIFont systemFontOfSize:20]];
    [titleLab setTextAlignment:NSTextAlignmentCenter];
    [titleLab setBackgroundColor:[UIColor clearColor]];
    [titleLab setTextColor:UIColorRGB(0x333333)];
    [titleLab setText:NSStringFrom(curItem->sTitle)];
    [scrollView addSubview:titleLab];
    CMRELEASE(titleLab);
    
    UILabel *desLab = [[UILabel alloc]initWithFrame:CGRectMake(10, 68, UI_IOS_WINDOW_WIDTH-20, 50)];
    [desLab setFont:[UIFont systemFontOfSize:14]];
    [desLab setTextColor:UIColorRGB(0x333333)];
    [desLab setBackgroundColor:[UIColor clearColor]];
    [desLab setText:NSStringFrom(curItem->sDesc)];
    [desLab setNumberOfLines:0];
    CGSize size = [desLab.text sizeWithFont:[UIFont systemFontOfSize:14] constrainedToSize:CGSizeMake(UI_IOS_WINDOW_WIDTH-26, MAXFLOAT) lineBreakMode:NSLineBreakByCharWrapping];
    [desLab setFrame: CGRectMake(10, 68, UI_IOS_WINDOW_WIDTH-20, size.height)];
    [scrollView addSubview:desLab];
    CMRELEASE(desLab);
    
    int originY=68+24+size.height;
    
    UIImageView *lineImage = [[UIImageView alloc]initWithFrame:CGRectMake(10, originY, UI_IOS_WINDOW_WIDTH-20, 1)];
    originY += 19;
    [lineImage setImage:[UIImage imageNamed:@"learn_cell_sep"]];
    lineImage.contentMode = UIViewContentModeScaleAspectFit;
    [scrollView addSubview:lineImage];
    CMRELEASE(lineImage);
    
    
    
    UILabel *dateLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, 100, 13)];
    originY += 23;
    [dateLab setFont:[UIFont systemFontOfSize:14]];
    [dateLab setTextColor:UIColorRGB(0x999999)];
    [dateLab setText:@"培训时间:"];
    [scrollView addSubview:dateLab];
    CMRELEASE(dateLab);
    
    UILabel *dateInfoLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, UI_IOS_WINDOW_WIDTH-20, 17)];
    originY += 37;
    [dateInfoLab setFont:[UIFont systemFontOfSize:15]];
    [dateInfoLab setTextColor:UIColorRGB(0x333333)];
    [dateInfoLab setBackgroundColor:[UIColor clearColor]];
    
    
    [dateInfoLab setText:NSStringFrom(curItem->sTrainTime)];
    [scrollView addSubview:dateInfoLab];
    CMRELEASE(dateInfoLab);
    
    UILabel *addressLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, 100, 13)];
    originY += 23;
    [addressLab setFont:[UIFont systemFontOfSize:14]];
    [addressLab setTextColor:UIColorRGB(0x999999)];
    [addressLab setBackgroundColor:[UIColor clearColor]];
    [addressLab setText:@"培训地点:"];
    [scrollView addSubview:addressLab];
    CMRELEASE(addressLab);
    
    UILabel *addressInfoLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, UI_IOS_WINDOW_WIDTH-20, 17)];
    originY += 37;
    [addressInfoLab setFont:[UIFont systemFontOfSize:15]];
    [addressInfoLab setTextColor:UIColorRGB(0x333333)];
    [addressInfoLab setBackgroundColor:[UIColor clearColor]];
    [addressInfoLab setText:NSStringFrom(curItem->sAddress)];
    [scrollView addSubview:addressInfoLab];
    CMRELEASE(addressInfoLab);
    
    UILabel *planPersonLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, 100, 13)];
    originY += 23;
    [planPersonLab setFont:[UIFont systemFontOfSize:14]];
    [planPersonLab setTextColor:UIColorRGB(0x999999)];
    [planPersonLab setBackgroundColor:[UIColor clearColor]];
    [planPersonLab setText:@"计划人数:"];
    [scrollView addSubview:planPersonLab];
    CMRELEASE(planPersonLab);
    
    UILabel *planpersonInfoLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, UI_IOS_WINDOW_WIDTH-20, 17)];
    originY += 37;
    [planpersonInfoLab setFont:[UIFont systemFontOfSize:15]];
    [planpersonInfoLab setTextColor:UIColorRGB(0x333333)];
    [planpersonInfoLab setText:NSStringFrom(curItem->sPlanPerson)];
    [scrollView addSubview:planpersonInfoLab];
    CMRELEASE(planpersonInfoLab);
    
    UILabel *signLab = [[UILabel alloc]initWithFrame:CGRectMake(10, originY, 100, 13)];
    originY += 23;
    [signLab setFont:[UIFont systemFontOfSize:14]];
    [signLab setTextColor:UIColorRGB(0x999999)];
    [signLab setBackgroundColor:[UIColor clearColor]];
    [signLab setText:@"报名时间:"];
    [scrollView addSubview:signLab];
    CMRELEASE(signLab);
    
    UILabel *signInfoLab = [[UILabel alloc]initWithFrame:CGRectMake(13, originY, UI_IOS_WINDOW_WIDTH-26, 17)];
    originY += 37;
    [signInfoLab setFont:[UIFont systemFontOfSize:15]];
    [signInfoLab setTextColor:UIColorRGB(0x333333)];
    [signInfoLab setBackgroundColor:[UIColor clearColor]];
    
    [signInfoLab setText:NSStringFrom(curItem->sApplyTime)];
    
    [scrollView addSubview:signInfoLab];
    CMRELEASE(signInfoLab);
    
    UIButton *applyButton = [UIButton buttonWithType:UIButtonTypeCustom];
    applyButton.frame = CGRectMake(10, UI_IOS_WINDOW_HEIGHT-10-44-64, UI_IOS_WINDOW_WIDTH-20, 44);

    [applyButton.titleLabel setFont:[UIFont systemFontOfSize:15]];
    [applyButton setBackgroundImage:[UIImage imageNamed:@"apply_n"] forState:UIControlStateNormal];
    [applyButton setBackgroundImage:[UIImage imageNamed:@"apply_p"] forState:UIControlStateHighlighted];
    [applyButton setBackgroundImage:[UIImage imageNamed:@"apply_d"] forState:UIControlStateDisabled];
    [applyButton setTag:5000];
    [applyButton addTarget:self action:@selector(signBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    if ([NSStringFrom(curItem->sFlag) isEqualToString:@"noapply"]) {
        if (curItem->nEnableApply == 0) {
            applyButton.tag = 2013;
            //[applyButton setTitle:I(@"我要报名") forState:UIControlStateNormal];
            //[applyButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            
            CMLabel *titleLabel = [[CMLabel alloc]initWithFrame:CGRectMake(10, 10, UI_IOS_WINDOW_WIDTH-40, 24)];
            [titleLab setBackgroundColor:[UIColor clearColor]];
            
            NSRange range;
            range = NSMakeRange(5, [[NSString stringWithFormat:I(@"(%d人已报名)"),curItem->nAppliedNum] length]);
            
            [titleLabel setText:[NSString stringWithFormat:I(@"我要报名 (%d人已报名)"),curItem->nAppliedNum] WithFont:[UIFont systemFontOfSize:15] AndColor:UIColorRGB(0xffffff)];
            [titleLabel setKeyWordRange:range WithFont:[UIFont systemFontOfSize:10] AndColor:UIColorRGB(0xffffff)];
            
            [titleLabel setTextAlignment:NSTextAlignmentCenter];
            
            [applyButton addSubview:titleLabel];
        }

        
        else if (curItem->nEnableApply == 1) {
            applyButton.enabled = NO;
            [applyButton setTitle:I(@"报名人数已满") forState:UIControlStateNormal];
            [applyButton setTitleColor:UIColorRGB(0x999999) forState:UIControlStateNormal];
        }
        
        
    }else if ([NSStringFrom(curItem->sFlag) isEqualToString:@"applied"])
    {
        if (curItem->nIsPass == 0) {
            applyButton.enabled = NO;
            [applyButton setTitle:I(@"提交成功,审核中") forState:UIControlStateNormal];
            [applyButton setTitleColor:UIColorRGB(0x999999) forState:UIControlStateNormal];
        }else if(curItem->nIsPass == 1)
        {
            applyButton.enabled = NO;
            [applyButton setTitle:I(@"报名成功") forState:UIControlStateNormal];
            [applyButton setTitleColor:UIColorRGB(0x22a000) forState:UIControlStateNormal];
            [applyButton setImage:[UIImage imageNamed:@"applysuccess"] forState:UIControlStateNormal];
            [applyButton setImageEdgeInsets: UIEdgeInsetsMake(0, -4, 0, 0)];

        }else if(curItem->nIsPass == 2)
        {
            applyButton.enabled = NO;
            [applyButton setTitle:I(@"审核不通过") forState:UIControlStateNormal];
            [applyButton setTitleColor:UIColorRGB(0x999999) forState:UIControlStateNormal];
            [applyButton setImage:[UIImage imageNamed:@"applyover"] forState:UIControlStateNormal];
            [applyButton setImageEdgeInsets: UIEdgeInsetsMake(0, -4, 0, 0)];
            
        }
        
        
    }else if ([NSStringFrom(curItem->sFlag) isEqualToString:@"over"])
    {
        applyButton.enabled = NO;
        [applyButton setTitle:I(@"报名已结束") forState:UIControlStateNormal];
        [applyButton setTitleColor:UIColorRGB(0xff4200) forState:UIControlStateNormal];
        [applyButton setImage:[UIImage imageNamed:@"applyover"] forState:UIControlStateNormal];
        [applyButton setImageEdgeInsets: UIEdgeInsetsMake(0, -4, 0, 0)];

    }
    
    [self.view insertSubview:applyButton aboveSubview:scrollView];
    //[scrollView addSubview:applyButton];
    
    CMLabel *tipLab = [[CMLabel alloc]initWithFrame:CGRectMake(50, originY, UI_IOS_WINDOW_WIDTH-100, 12)];
    [tipLab setBackgroundColor:[UIColor clearColor]];
    [tipLab setFont:[UIFont systemFontOfSize:12]];
    [tipLab setText:[NSString stringWithFormat:I(@"已有%d人报名"),curItem->nAppliedNum]];
    
    NSRange range;
    range = NSMakeRange(2, [[NSString stringWithFormat:@"%d",curItem->nAppliedNum] length]);
    
    [tipLab setText:[NSString stringWithFormat:I(@"已有%d人报名"),curItem->nAppliedNum] WithFont:[UIFont systemFontOfSize:12] AndColor:UIColorRGB(0x999999)];
    [tipLab setKeyWordRange:range WithFont:[UIFont systemFontOfSize:12] AndColor:UIColorRGB(0xf89a07)];
    
    [tipLab setTextAlignment:NSTextAlignmentCenter];
    
    //[scrollView addSubview:tipLab];
    CMRELEASE(tipLab);
    
    scrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, originY + 80 );
    
    CMRELEASE(scrollView);

    
}

//取消报名
-(void)cancelApply:(id)sender
{
    UIAlertView *alertview = [[UIAlertView alloc]initWithTitle:@"" message:I(@"取消报名?") delegate:self cancelButtonTitle:I(@"取消") otherButtonTitles:I(@"确定"), nil];
    [alertview show];
    
    
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
{
    if (buttonIndex == 1) {
        if (!m_pCancelApplyListerner) {
            m_pCancelApplyListerner = new CMTrainCancelApplyUpdateDataListener();
        }
        curItem->SetListener( NULL ,m_pCancelApplyListerner);
        curItem->SetUserData((__bridge void*)self);
        curItem->CancelApply();
    }
}


-(void)CallBackSuccess
{
    if (!m_refreshViewListerner) {
        m_refreshViewListerner = new CMTrainInfoUpdateDataListener();
    }
    curItem->SetListener(m_refreshViewListerner, NULL);
    curItem->SetUserData((__bridge void*)self);
    
    [tool ShowActivityIndicator:self.view];
    curItem->RequestInfo();
    
}

//-(void)CancelApplySuccess
//{
//    if (!m_refreshViewListerner) {
//        m_refreshViewListerner = new CMTrainInfoUpdateDataListener();
//    }
//    curItem->SetListener(m_refreshViewListerner, NULL);
//    curItem->SetUserData((__bridge void*)self);
//    
//    curItem->RequestInfo();
//    [tool ShowActivityIndicator:self.view];
//}

-(void)setInfo:(TTrainApplyItem &)item
{
    if (!curItem) {
        curItem = new TTrainApplyItem;
    }
    *curItem = item;
}

-(void)setInfoWithString:(NSString *)sid
{
    if (!curItem) {
        curItem = new TTrainApplyItem;
    }
    curItem->sID = [sid UTF8String];
}

-(void)signBtnPressed:(id)sender
{
    if (!m_pUpdataDataListerner) {
        m_pUpdataDataListerner = new CMTrainApplyUpdateDataListener();
    }
    
    curItem->SetListener( NULL ,m_pUpdataDataListerner);
    curItem->SetUserData((__bridge void*)self);
    
    [tool ShowActivityIndicator:self.view];
    
    curItem->Apply();
    
    
}


-(void)dealloc
{
    curItem->Cancel();
    curItem->SetListener(NULL, NULL);
    
    SAFEDELETE(curItem);
    SAFEDELETE(m_pCancelApplyListerner);
    SAFEDELETE(m_pUpdataDataListerner);
    SAFEDELETE(m_refreshViewListerner);
    CMRELEASE(stateStr);
    
}


@end
