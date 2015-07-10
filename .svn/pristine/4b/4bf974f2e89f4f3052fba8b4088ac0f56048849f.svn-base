//
//  CMWrongViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-10-30.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMWrongViewController.h"
#import "CMWrongControl.h"
#import "cmmyinfo.h"

@interface CMWrongViewController ()

@end

@implementation CMWrongViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)gotoBack
{
    //退出页面时保存当前错误练习数
    CMMyInfo::GetInstance()->SetWrongQa(mWongControl.nWrongPractice);
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"refreshwrongcount" object:nil];
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    self.titleLabel.text = self.navigationItem.title;
    
    mWongControl = [[CMWrongControl alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-64)];
    [mWongControl startFlash];
    [self.view addSubview:mWongControl];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    CMRELEASE(mWongControl);
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

@end
