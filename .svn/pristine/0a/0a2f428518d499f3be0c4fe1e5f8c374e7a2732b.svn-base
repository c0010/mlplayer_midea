//
//  CMTrainDetailSignController.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainDetailSignController.h"
#import "CMLabel.h"
#import "CMSearchQRCode.h"
#import "NSDate+Helper.h"



@implementation CMTrainDetailSignController


-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.titleLabel.text = I(@"签到详情");
    
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    scrollView = [[UIScrollView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-64)];
    [self.view addSubview:scrollView];
    
    if (!self.isSweepPush && !self.bIsPush) {
        [self initView];

    }else
        [self callBack];
    
}

-(void)initView
{
    
    for (UIView *subview in scrollView.subviews) {
        [subview removeFromSuperview];
    }
    for (UIView *button in self.view.subviews) {
        if (button.tag == 5000) {
            [button removeFromSuperview];
        }
    }
    
    
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setFrame:CGRectMake(0, 0, 44, 40)];
    btn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
    [btn setImage:[UIImage imageNamed:@"code"] forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(gotoSweep:) forControlEvents:UIControlEventTouchUpInside];
    
    
    UIBarButtonItem *rightitem = [[UIBarButtonItem alloc]initWithCustomView:btn];
    self.navigationItem.rightBarButtonItem = rightitem;

    
    //画界面
    
    UILabel *titleLab=[[UILabel alloc]initWithFrame:CGRectMake(10, 24, UI_IOS_WINDOW_WIDTH-20, 20)];
    [titleLab setFont:[UIFont systemFontOfSize:20]];
    [titleLab setTextAlignment:NSTextAlignmentCenter];
    [titleLab setTextColor:UIColorRGB(0x333333)];
    [titleLab setText:NSStringFrom(curItem->sTitle)];
    [scrollView addSubview:titleLab];
    CMRELEASE(titleLab);
    
    UILabel *dateLab = [[UILabel alloc]initWithFrame:CGRectMake(10, 68, 150, 13)];
    [dateLab setFont:[UIFont systemFontOfSize:14]];
    [dateLab setTextColor:UIColorRGB(0x999999)];
    [dateLab setText:@"签到时间:"];
    [scrollView addSubview:dateLab];
    CMRELEASE(dateLab);
    
    UILabel *dateInfoLab = [self GetLabel:[NSString stringWithUTF8String:curItem->sTime.c_str()]  textcolor:UIColorRGB(0x333333) fontsize:15];
    [dateInfoLab setFrame:CGRectMake(10, 91, UI_IOS_WINDOW_WIDTH-20, 30)];
    [dateInfoLab setNumberOfLines:2];
    
    [dateInfoLab setText:NSStringFrom(curItem->sTime)];
    [dateInfoLab sizeToFit];

    [scrollView addSubview:dateInfoLab];
    
    UILabel *addressLab = [self GetLabel:@"签到地点:" textcolor:UIColorRGB(0x999999) fontsize:14];
    [addressLab setFrame:CGRectMake(10, 124, 150, 13)];
    [scrollView addSubview:addressLab];
    
    UILabel *addressInfoLab = [self GetLabel:[NSString stringWithUTF8String:curItem->sAddress.c_str()] textcolor:UIColorRGB(0x333333) fontsize:15];
    [addressInfoLab  setNumberOfLines:0];
    [addressInfoLab setFrame:CGRectMake(10, 147, UI_IOS_WINDOW_WIDTH-20, 50)];
    [addressInfoLab sizeToFit];
    [scrollView addSubview:addressInfoLab];

    
    UIButton *signButton = [UIButton buttonWithType:UIButtonTypeCustom];
    signButton.frame = CGRectMake(10, UI_IOS_WINDOW_HEIGHT-10-44-64, UI_IOS_WINDOW_WIDTH-20, 44);

    
    [signButton.titleLabel setFont:[UIFont systemFontOfSize:15]];
    [signButton setBackgroundImage:[UIImage imageNamed:@"apply_n"] forState:UIControlStateNormal];
    [signButton setBackgroundImage:[UIImage imageNamed:@"apply_p"] forState:UIControlStateHighlighted];
    [signButton setBackgroundImage:[UIImage imageNamed:@"apply_d"] forState:UIControlStateDisabled];
    [signButton setTag:5000];
    
    [signButton addTarget:self action:@selector(signBtnPressed:) forControlEvents:UIControlEventTouchUpInside];

    
    if ([[NSString stringWithUTF8String:curItem->sFlag.c_str()] isEqualToString:@"nosignin"]) {
        
        if (curItem->nMode == 1) {
            UILabel *lab = [self GetLabel:@"注: 只允许扫描二维码签到" textcolor:UIColorRGB(0x999999) fontsize:14];
            [lab setBackgroundColor:[UIColor clearColor]];
            [lab setFrame:CGRectMake(10, 200, UI_IOS_WINDOW_WIDTH-20, 20)];
            [lab setTextAlignment:NSTextAlignmentLeft];
            [scrollView addSubview:lab];
            
            UIImageView *sweepImageView = [[UIImageView alloc]initWithFrame:CGRectMake(62, 14, 16, 16)];
            [sweepImageView setImage:[UIImage imageNamed:@"code"]];
            [signButton addSubview:sweepImageView];
            CMRELEASE(sweepImageView);
            
            CMLabel *tipLab = [[CMLabel alloc]initWithFrame:CGRectMake(88, 14, UI_IOS_WINDOW_WIDTH-100 , 16)];
            [tipLab setBackgroundColor:[UIColor clearColor]];
            
            NSRange range;
            range = NSMakeRange(8, [[NSString stringWithFormat:@"(%d人已签到)",curItem->nSignInNum] length]);
            
            [tipLab setText:[NSString stringWithFormat:@"扫一扫,来签到 (%d人已签到)",curItem->nSignInNum] WithFont:[UIFont systemFontOfSize:15] AndColor:UIColorRGB(0xffffff)];
            [tipLab setKeyWordRange:range WithFont:[UIFont systemFontOfSize:10] AndColor:UIColorRGB(0xffffff)];
            
            [tipLab setTextAlignment:NSTextAlignmentLeft];
            
            [signButton addSubview:tipLab];
            CMRELEASE(tipLab);

            
            
            
        }else if(curItem->nMode == 0)
        {
            CMLabel *titleLabel = [[CMLabel alloc]initWithFrame:CGRectMake(10, 10, UI_IOS_WINDOW_WIDTH-40, 24)];
            [titleLab setBackgroundColor:[UIColor clearColor]];
            
            NSRange range;
            range = NSMakeRange(3, [[NSString stringWithFormat:I(@"(%d人已签到)"),curItem->nSignInNum] length]);
            
            [titleLabel setText:[NSString stringWithFormat:I(@"签到 (%d人已签到)"),curItem->nSignInNum] WithFont:[UIFont systemFontOfSize:15] AndColor:UIColorRGB(0xffffff)];
            [titleLabel setKeyWordRange:range WithFont:[UIFont systemFontOfSize:10] AndColor:UIColorRGB(0xffffff)];
            
            [titleLabel setTextAlignment:NSTextAlignmentCenter];
            
            [signButton addSubview:titleLabel];
            
        }
        
        
    }else if([[NSString stringWithUTF8String:curItem->sFlag.c_str()] isEqualToString:@"signin"]){
        
        UILabel *lab = [self GetLabel:[NSString stringWithFormat:I(@"签到时间:%@"),NSStringFrom(curItem->sSignInTime)] textcolor:UIColorRGB(0x999999) fontsize:12];
        [lab setFrame:CGRectMake(10, UI_IOS_WINDOW_HEIGHT-64-55-15-12, UI_IOS_WINDOW_WIDTH-20, 12)];
        [lab setTextAlignment:NSTextAlignmentCenter];
        [self.view insertSubview:lab aboveSubview:scrollView];
        
        signButton.enabled = NO;
        [signButton setTitle:I(@"签到成功") forState:UIControlStateNormal];
        [signButton setTitleColor:UIColorRGB(0x22a000) forState:UIControlStateNormal];
        [signButton setImage:[UIImage imageNamed:@"applysuccess"] forState:UIControlStateNormal];
        [signButton setImageEdgeInsets: UIEdgeInsetsMake(0, -4, 0, 0)];

        
    }else // 其他特殊情况 也让按钮可点击
    {
        signButton.enabled = NO;
        [signButton setTitle:I(@"签到时间已过期") forState:UIControlStateNormal];
        [signButton setTitleColor:UIColorRGB(0x22a000) forState:UIControlStateNormal];
        //[signButton setImage:[UIImage imageNamed:@"applysuccess"] forState:UIControlStateNormal];
        [signButton setImageEdgeInsets: UIEdgeInsetsMake(0, -4, 0, 0)];
    }

    //[scrollView addSubview:signButton];
    [self.view insertSubview:signButton aboveSubview:scrollView];
    
}


-(void)updateView
{
    if (curItem->nMode == 0) {
        UIButton *signButton = [UIButton buttonWithType:UIButtonTypeCustom];
        signButton.frame = CGRectMake(10, 280, UI_IOS_WINDOW_WIDTH - 20, 46);
        [signButton setBackgroundImage:[UIImage imageNamed:@"sign_p"] forState:UIControlStateNormal];
        [signButton setBackgroundImage:[UIImage imageNamed:@"sign_n@2x"] forState:UIControlStateHighlighted];
        signButton.tag = 2013;
        [signButton setTitle:I(@"签到") forState:UIControlStateNormal];
        [signButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [signButton setTitleColor:UIColorRGB(0xa2f192) forState:UIControlStateDisabled];
        [signButton.titleLabel setFont:[UIFont boldSystemFontOfSize:20]];
        [signButton addTarget:self action:@selector(signBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
        
        [scrollView addSubview:signButton];
        
        CMLabel *tipLab = [[CMLabel alloc]initWithFrame:CGRectMake(50, 280+46+10, UI_IOS_WINDOW_WIDTH-100, 15)];
        [tipLab setFont:[UIFont systemFontOfSize:14]];
        [tipLab setText:[NSString stringWithFormat:I(@"已有%d人签到"),curItem->nSignInNum]];
        
        NSRange range;
        range = NSMakeRange(2, [[NSString stringWithFormat:@"%d",curItem->nSignInNum] length]);
        
        [tipLab setText:[NSString stringWithFormat:I(@"已有%d人签到"),curItem->nSignInNum] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0x7f7f7f)];
        [tipLab setKeyWordRange:range WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0xfe883f)];
        
        [tipLab setTextAlignment:NSTextAlignmentCenter];
        
        [scrollView addSubview:tipLab];
        CMRELEASE(tipLab);

    }else if (curItem->nMode == 1){
        
        UILabel *lab = [self GetLabel:I(@"此签到只允许二维码签到!") textcolor:[UIColor grayColor] fontsize:18];
        [lab setFrame:CGRectMake(20, 300, UI_IOS_WINDOW_WIDTH-40, 20)];
        [lab setTextAlignment:NSTextAlignmentCenter];
        [scrollView addSubview:lab];
        
        UIButton *sweepBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [sweepBtn setFrame:CGRectMake(90, 335, 140, 20)];
        [sweepBtn setImage:[UIImage imageNamed:@"sweepsign"] forState:UIControlStateNormal];
        [sweepBtn setTitle:I(@"点击此处开始扫一扫") forState:UIControlStateNormal];
        [sweepBtn addTarget:self action:@selector(gotoSweep:) forControlEvents:UIControlEventTouchUpInside];
        [sweepBtn setFont:[UIFont systemFontOfSize:12]];
        [sweepBtn setTitleColor:[UIColor colorWithRed:9/255.0 green:76/255.0 blue:161/255.0 alpha:1] forState:UIControlStateNormal];
        [scrollView addSubview:sweepBtn];
    }
    
    
}

-(UILabel*)GetLabel:(NSString*)text textcolor: (UIColor*)textcolor fontsize:(int)size
{
    UILabel* lb = [[UILabel alloc] init];
    lb.backgroundColor = [UIColor clearColor];
    lb.textAlignment = NSTextAlignmentLeft;
    lb.font = [UIFont systemFontOfSize:size];
    lb.textColor = textcolor;
    lb.text = text;
    return lb;
}

//扫一扫

-(void)gotoSweep:(id)sender
{
    CMSearchQRCode *QRcodeControl = [[CMSearchQRCode alloc]init];
    [QRcodeControl setInfo:*curItem];
    [QRcodeControl setTrainSignView:self.TrainSignView];
    [QRcodeControl setSignControl:self];
    [self.navigationController pushViewController:QRcodeControl animated:YES];
}

//普通签到
-(void)signBtnPressed: (id)sender
{
    if (curItem->nMode == 0) {
        if (!m_pUpdataDataListerner) {
            m_pUpdataDataListerner = new CMTrainSignUpdateDataListener();
        }
        curItem->SetListener(NULL, m_pUpdataDataListerner);
        curItem->SetUserData((__bridge void*)self);
        
        curItem->Cancel();
        
        [tool ShowActivityIndicator:self.view];

        curItem->SignInTrain();
        
    }else if (curItem->nMode == 1)
    {
        CMSearchQRCode *QRcodeControl = [[CMSearchQRCode alloc]init];
        [QRcodeControl setInfo:*curItem];
        [QRcodeControl setTrainSignView:self.TrainSignView];
        [QRcodeControl setSignControl:self];
        [self.navigationController pushViewController:QRcodeControl animated:YES];
    }
}

-(void)callBack
{
    if (!self.isSweepPush) {
        [self.TrainSignView refreshTableView];
    }else
        [self.TrainSignView automaticRefresh];
    
    if (!m_prefreshViewListerner) {
        m_prefreshViewListerner = new CMTrainSigninViewUpdateDataListener();
    }
    curItem->SetListener(m_prefreshViewListerner, NULL);
    curItem->SetUserData((__bridge void*)self);
    
    curItem->Cancel();
    
    [tool ShowActivityIndicator:self.view];
    
    curItem->RequestInfo();

    
}

-(void)setInfo:(TTrainSignInItem &)item
{
    if (!curItem) {
        curItem = new TTrainSignInItem();
    }
    *curItem = item;
}

-(void)setInfoWithString:(NSString *)sid
{
    if (!curItem) {
        curItem = new TTrainSignInItem();
    }
    curItem->sID = [sid UTF8String];
}


- (void)gotoBack
{
    //首先 判断是否是推送消息
    if (self.bIsPush) {
        //      MLPlayerAppDelegate *appdelegate = [UIApplication sharedApplication].delegate;
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud setObject:@"0" forKey:kUDOpenPush];
        //  appdelegate.navigationController.navigationBarHidden = YES;
        //判断 推送消息的app 状态
    }

    if (!self.isSweepPush) {
        [self.navigationController popViewControllerAnimated:YES];
        
    }else//不返回到扫描而二维码的界面
        [self.navigationController popToViewController:[[self.navigationController viewControllers] objectAtIndex:self.navigationController.viewControllers.count-3] animated:YES];
    
}

-(void)dealloc
{
    if (curItem) {
        curItem->Cancel();
        curItem->SetListener(NULL, NULL);
        curItem->SetUserData(NULL);
    }
    SAFEDELETE(curItem);
    
    if (self.TrainSignView!=nil) {
        self.TrainSignView;
    }
    
}

@end
