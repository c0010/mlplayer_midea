//
//  CMAboutController.m
//  MLPlayer
//
//  Created by sunjj on 13-6-20.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMAboutController.h"

@interface CMAboutController ()

@end

@implementation CMAboutController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)gotoBack
{
	[[self navigationController] popViewControllerAnimated:	YES];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
	backBtn.frame = CGRectMake(0, 0, 40, 44);
	[backBtn setImage:[UIImage imageNamed:@"back"] forState:UIControlStateNormal];
	[backBtn addTarget:self action:@selector(gotoBack) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem *backBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
	self.navigationItem.leftBarButtonItem = backBarButtonItem;
    
	// Do any additional setup after loading the view.
    
    self.title=I(@"关于");
    self.titleLabel.text = self.title;
    
    [self.view setBackgroundColor:[UIColor whiteColor]];
    
    //logo图
#ifdef __MideaCourse_in_uat__
    UIImage *logoImg=[UIImage imageNamed:@"iconLogo.png"];
#else
    UIImage *logoImg=[UIImage imageNamed:@"icon_test.png"];
#endif
    
    UIImageView *logoView=[[UIImageView alloc]initWithImage:logoImg];
    
    
    CGFloat logowidth=100;
    CGFloat logoheight=105;
    

    [logoView setFrame:CGRectMake(self.view.center.x-logowidth/2, (self.view.center.y-170)-logoheight/2, logowidth, logoheight)];
    
    [self.view addSubview:logoView];
    
    
    //App名
    UILabel *lbAppName=[[UILabel alloc]initWithFrame:CGRectMake(60, logoView.frame.origin.y+logoheight+10, 200, 30)];
    lbAppName.textAlignment=NSTextAlignmentCenter;
    lbAppName.text=I(@"美课");
    
    [lbAppName setTextColor:[UIColor blackColor]];
    [lbAppName setFont:[UIFont boldSystemFontOfSize:27]];
    
    [self.view addSubview:lbAppName];
    
    
    //版本号
    UILabel *lbVer=[[UILabel alloc]init ];
                    
    
    lbVer.text = [NSString stringWithFormat:@"V%@",AppVersion];
    


    [lbVer setTextColor:[UIColor whiteColor]];
    [lbVer setFont:[UIFont boldSystemFontOfSize:16]];
    
    [lbVer setBackgroundColor:[UIColor clearColor]];
    [lbVer setTextAlignment:NSTextAlignmentCenter];
    
    CGSize labelSize=[lbVer.text sizeWithFont:[UIFont boldSystemFontOfSize:16] constrainedToSize:CGSizeMake(MAXFLOAT,20)];
    
    [lbVer setFrame:CGRectMake(18,3, labelSize.width, 20)];


    
    UIImage *left=[UIImage imageNamed:@"ver_back_left.png"];
    UIImage *right=[UIImage imageNamed:@"ver_back_right.png"];
    UIImage *mid=[UIImage imageNamed:@"ver_back_mid.png"];

    
    labelSize.width=labelSize.width+40;
    //拼接图片
    UIGraphicsBeginImageContextWithOptions(CGSizeMake(labelSize.width,25), NO, 2) ;
    
    // Draw left
    [left drawInRect:CGRectMake(0, 0, 13, 25)];
    
    // Draw mid
    [mid drawAsPatternInRect:CGRectMake(13, 0, labelSize.width-13*2, 25)];
    
    // Draw right
    [right drawInRect:CGRectMake(labelSize.width-13-1, 0, 13 , 25)];
    
    UIImage *resultingImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    UIImageView* verBackView=[[UIImageView alloc]initWithImage:resultingImage];
    
    [verBackView setFrame:CGRectMake(126, logoView.frame.origin.y+logoheight+100, labelSize.width, 25)];
    
    //[lbVer setFrame:CGRectMake(110, logoView.frame.origin.y+logoheight+103, labelSize.width, 20)];
    [verBackView addSubview:lbVer];
    [self.view addSubview:verBackView];
    
//    //文字1
//    UILabel *lbTEXT_ONE=[[UILabel alloc]initWithFrame:CGRectMake(35,logoView.frame.origin.y+logoheight+150, 400, 20)];
//    
//    lbTEXT_ONE.text=I(@" Copyright© 2012-2015 问鼎资讯");
//    
//    [lbTEXT_ONE setTextColor:[UIColor grayColor]];
//    [lbTEXT_ONE setFont:[UIFont boldSystemFontOfSize:16]];
//    
//    [self.view addSubview:lbTEXT_ONE];
//    
//    
//    
//    //文字2
//    
//    UILabel *lbTEXT_TWO=[[UILabel alloc]initWithFrame:CGRectMake(60, logoView.frame.origin.y+logoheight+180, 400, 20)];
//    
//    lbTEXT_TWO.text=I(@"全国免费咨询电话:0755-26505694");
//    
//    [lbTEXT_TWO setTextColor:[UIColor grayColor]];
//    [lbTEXT_TWO setFont:[UIFont boldSystemFontOfSize:14]];
//    
//    [self.view addSubview:lbTEXT_TWO];
    
    
   // UIImage *ver_back=[UIImage imageNamed:@"ver_back.png"];
    
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
