//
//  CMExamRankViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-11-13.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMExamRankViewController.h"
#import "cmgeneral.h"

@interface CMExamRankViewController ()

@end

@implementation CMExamRankViewController

@synthesize strURL;

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
    
    m_pWebView = [[CMWebView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-44-20)];
    m_pWebView.dataDetectorTypes = UIDataDetectorTypeNone;
    
    [m_pWebView setBackgroundColor:[UIColor whiteColor]];
    m_pWebView.delegate = self;
    
    [self.view addSubview:m_pWebView];
    
    bgview = [[UIView alloc] initWithFrame:m_pWebView.bounds];
    [m_pWebView addSubview:bgview];
    [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(loadWebviewData) on:bgview];
    bgview.hidden = YES;
    
    const char* sUrl = NULL;
    CMGeneral gengral;
    sUrl = gengral.FormatUrlBySID([strURL UTF8String]);
    
    
    if ( sUrl != NULL ) {
        NSString *strSIDURL = [NSString stringWithUTF8String:sUrl];
        [m_pWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:strSIDURL]]];
    }else{
        
        bgview.hidden = NO;
    }
}

- (void)loadWebviewData{
    
    const char* sUrl = NULL;
    CMGeneral gengral;
    sUrl = gengral.FormatUrlBySID([strURL UTF8String]);
    
    
    if ( sUrl != NULL ) {
        NSString *strSIDURL = [NSString stringWithUTF8String:sUrl];
        [m_pWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:strSIDURL]]];
    }else{
        
        bgview.hidden = NO;
    }
    
}

- (void)webViewDidFinishLoad:(UIWebView *)awebView{
    [tool DisimissActivityIndicator];
    
    [bgview setHidden:YES];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error{
    [bgview setHidden:NO];
    [tool DisimissActivityIndicator];
}




- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc{
    CMRELEASE(m_pWebView);
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

@end
