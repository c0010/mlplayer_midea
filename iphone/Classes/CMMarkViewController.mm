//
//  CMMarkViewController.m
//  MLPlayer
//
//  Created by hushengwu on 13-10-8.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMMarkViewController.h"

@interface CMMarkViewController ()

@end

@implementation CMMarkViewController
@synthesize markview,MarkID;


-(CMContenthandler*)GetContenthandler
{
    if(self.markview!=NULL)
        return markview.Contenthandler;
    else
        return NULL;
    
}

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
    
    self.titleLabel.text = self.navigationItem.title;
    
	// Do any additional setup after loading the view.

    markview = [[CMMarkView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH,UI_IOS_WINDOW_HEIGHT-44-20) refresh:YES];
    markview.MarkID = MarkID;

    [self.view addSubview:markview];
    
    [markview automaticRefresh];
}

//iOS8上 cell分割线置顶
-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    if ([markview.tableviewlist respondsToSelector:@selector(setSeparatorInset:)]) {
        [markview.tableviewlist setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([markview.tableviewlist respondsToSelector:@selector(setLayoutMargins:)]) {
        [markview.tableviewlist setLayoutMargins:UIEdgeInsetsZero];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (void)dealloc{
    CMRELEASE(markview);
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}
@end
