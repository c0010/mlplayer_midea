//
//  CMRuleViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-12-6.
//  Copyright (c) 2013年 w. All rights reserved.
//

#include "stdafx.h"
#import "CMRuleViewController.h"
#import "CMWebView.h"
#include "cmgeneral.h"
#include "cmmyinfo.h"

@interface CMRuleViewController ()

@end

@implementation CMRuleViewController

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
    
    self.title = I(@"积分规则");
    self.titleLabel.text = self.navigationItem.title;
    self.view.backgroundColor = [UIColor whiteColor];
    
	CGRect f = self.view.bounds;
    f.size.height -= 64;
    
# if ! __has_feature(objc_arc)
	UIWebView* webView = [[[UIWebView alloc] initWithFrame:f] autorelease];
# else
    UIWebView* webView = [[UIWebView alloc] initWithFrame:f];
# endif
    
	CMGeneral general;
	const char*sUrl = general.FormatUrlBySID(CMMyInfo::GetInstance()->GetRankUrl());
	if(!sUrl)
		return;
    
	NSURL *desturl = [NSURL URLWithString:[NSString stringWithUTF8String:sUrl]];
	
	NSURLRequest *requestObj = [NSURLRequest requestWithURL:desturl];
    
    //不对webview里面的数据进行检测 即不显示任何电话号码、URL的样式
    webView.dataDetectorTypes = UIDataDetectorTypeNone;
    
    [webView setDelegate:self];
    [tool ShowActivityIndicator:self.view];
    
	[webView loadRequest:requestObj];
	[self.view addSubview:webView];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView;
{
    [tool DisimissActivityIndicator];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error;
{
    [tool DisimissActivityIndicator];
    NSLog(@"error:%@",error);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
