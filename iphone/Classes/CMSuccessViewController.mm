//
//  CMSuccessViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-12-5.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMSuccessViewController.h"
#import "CMLoginControl.h"

@interface CMSuccessViewController ()

@end

@implementation CMSuccessViewController

@synthesize strMail;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    self.titleLabel.text = self.navigationItem.title;
    self.view.backgroundColor = [UIColor whiteColor];
    
    UILabel *topLabel = [[UILabel alloc] init];
    topLabel.frame = CGRectMake(20, 40, UI_IOS_WINDOW_WIDTH - 40, 20);
    topLabel.backgroundColor = [UIColor clearColor];
    topLabel.text = I(@"重置密码的激活邮件已发送到您的邮箱");
    topLabel.font = [UIFont systemFontOfSize:15];
    topLabel.textColor = UIColorRGB(0x000000);
    topLabel.textAlignment = UITextAlignmentCenter;
    [self.view addSubview:topLabel];
    CMRELEASE(topLabel);
    
    
    UILabel *timeLabel = [[UILabel alloc] init];
    timeLabel.frame = CGRectMake(20, 70, UI_IOS_WINDOW_WIDTH - 40, 20);
    timeLabel.backgroundColor = [UIColor clearColor];
    timeLabel.text = I(@"(2小时内有效)");
    timeLabel.font = [UIFont systemFontOfSize:14];
    timeLabel.textColor = UIColorRGB(0x747474);
    timeLabel.textAlignment = UITextAlignmentCenter;
    [self.view addSubview:timeLabel];
    CMRELEASE(timeLabel);
    
    
    UIButton *successBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    successBtn.frame = CGRectMake(20, 120, UI_IOS_WINDOW_WIDTH - 40, 40);
    successBtn.backgroundColor = [UIColor clearColor];
    [successBtn setBackgroundImage:[UIImage imageNamed:@"introductionstart_n@2x"] forState:UIControlStateNormal];
    [successBtn setBackgroundImage:[UIImage imageNamed:@"introductionstart_p@2x"] forState:UIControlStateHighlighted];
    [successBtn setTitle:I(@"登录邮箱激活") forState:UIControlStateNormal];
    [successBtn addTarget:self action:@selector(goToMail:) forControlEvents:UIControlEventTouchUpInside];
    [successBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.view addSubview:successBtn];
    
    
    UILabel *mailLabel = [[UILabel alloc] init];
    mailLabel.frame = CGRectMake(20, 170, UI_IOS_WINDOW_WIDTH - 40, 20);
    mailLabel.backgroundColor = [UIColor clearColor];
    mailLabel.text = self.strMail;
    mailLabel.font = [UIFont systemFontOfSize:14];
    mailLabel.textColor = UIColorRGB(0x747474);
    [self.view addSubview:mailLabel];
    CMRELEASE(mailLabel);
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)goToMail:(id)sender
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:self.strMail]];
    
    NSArray *viewArr = self.navigationController.viewControllers;
    
    int nIndex = -1;
    for (int i = 0; i < [viewArr count]; i++)
    {
        if ([[viewArr objectAtIndex:i] isKindOfClass:[CMLoginControl class]])
        {
            nIndex = i;
            break;
        }
    }
   
    if (nIndex >= 0 && nIndex < [viewArr count])
    {
        [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:nIndex] animated:YES];
    }
    else
    {
        [self.navigationController popViewControllerAnimated:YES];
    }
}

@end
