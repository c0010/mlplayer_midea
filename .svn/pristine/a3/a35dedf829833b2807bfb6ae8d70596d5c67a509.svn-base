//
//  CMShakeController.m
//  MLPlayer
//
//  Created by 王 浩沣 on 13-7-13.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "stdafx.h"
#import "cmcommon.h"
#import "CMShakeController.h"
#import "cmsettings.h"

@interface CMShakeController (custom)

@end

@implementation CMShakeController

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
    
    self.title=I(@"摇一摇");

    NSString *strAudio = [[NSBundle mainBundle] pathForResource:@"glass" ofType:@"wav"];

    AudioServicesCreateSystemSoundID((__bridge CFURLRef)[NSURL URLWithString:strAudio], &sysSoundID);

    self.view.backgroundColor=[UIColor whiteColor];
    
    
    appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(BOOL)canBecomeFirstResponder
{
    return YES;
    
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}


- (void)shakeToDetail
{
    
    TBrowserItem* item=NULL;
    
    if(m_pShake->GetItemModel(0)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }

    m_pShake->GetItem(0, item);
    
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
    nav->bIsShake = YES;
	[nav NavgateItem:self item:*item];
    
    SAFEDELETE(item);
}

-(void)gotoShake
{
    if (!m_pShakeListener)
    {
        m_pShakeListener = new  CMShakeUpdateListener();
    }
    
    if (!m_pShake)
    {
        m_pShake = new CMShake(m_pShakeListener);
        m_pShake->SetUserData(BridgeObjectToC(self));
    }
    m_pShake->SetUserData(BridgeObjectToC(self));

    m_pShake->SetListener(m_pShakeListener, NULL);
    m_pShake->Request();
}


-(void)dealloc
{
    SAFEDELETE(m_pShakeListener);

    SAFEDELETE(m_pShake);
    


}

@end
