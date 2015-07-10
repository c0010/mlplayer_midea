//
//  CMTrainListViewController.m
//  MLPlayer
//
//  Created by hushengwu on 14/11/5.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainListViewController.h"
#import "CMTrainListView.h"
//#import "CMTrainSearchViewController.h"
#import "tool.h"


@interface CMTrainListViewController ()

@property (nonatomic,weak) UISegmentedControl *segment;


@end

@implementation CMTrainListViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)configSearchItem{
//    UIBarButtonItem *barButtonitem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"comm_search_n"] style:UIBarButtonItemStyleBordered target:self action:@selector(baseSearchButton:)];
//    
//    self.navigationItem.rightBarButtonItem = barButtonitem;
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.frame = CGRectMake(0, 0, 40, 44);
    button.imageEdgeInsets = [self itemFitDifferentVersion:NO];
    [button addTarget:self action:@selector(baseSearchButton:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *searchBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = searchBarButtonItem;
}

-(void)baseSearchButton:(id)sender{

}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.titleLabel.text=self.title;
    
    [self configSearchItem];

    self.navigationController.navigationBarHidden = NO;
    //[self setupUI];

    self.trainlistView = [[CMTrainListView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64 )];
    self.trainlistView.backgroundColor = [UIColor whiteColor];
    //self.trainlistView.tableviewlist.backgroundColor = UIColorRGB(0xeeeeee);
    self.trainlistView.tableviewlist.separatorColor = UIColorRGB(0xeeeeee);
    
    [self.view addSubview:self.trainlistView];
    
    //strcpy(self.trainlistView->m_sFlag, [TRAIN_APPLY UTF8String]);
    
    [self.trainlistView automaticRefresh];

}

#pragma mark -- ui
-(void)setupUI{
    int offsetY=0;
    UIView *topBgView = [[UIView alloc] initWithFrame:CGRectMake(0, offsetY, 320, 44)];
    //[topBgView setBackgroundColor: UIColorRGB(0x0161b6)];
    UIImageView *backgroundimg=[[UIImageView alloc]initWithFrame:CGRectMake(0, offsetY, 320, 44)];
    [topBgView addSubview:backgroundimg];
    
    
    [self.view addSubview:topBgView];
    
    NSArray *segmentedArray = [[NSArray alloc] initWithObjects:I(@"未报名"),I(@"已报名"),I(@"已结束"),nil];
    UISegmentedControl *segmentTemp = [[UISegmentedControl alloc] initWithItems:segmentedArray];
    self.segment=segmentTemp;
    [self.segment setSelectedSegmentIndex:1];
    [self.segment setFrame:CGRectMake(50, 7, UI_IOS_WINDOW_WIDTH - 100, 30)];
    [topBgView addSubview:_segment];
    [self.segment setTintColor:[UIColor whiteColor]];
    [self.segment addTarget:self action:@selector(segmentClick:) forControlEvents:UIControlEventValueChanged];
}

-(void)segmentClick:(UISegmentedControl *)_seg{
    int segIndex = _seg.selectedSegmentIndex;
//    if (segIndex == 0) {
//        strcpy(self.trainlistView->m_sFlag, [TRAIN_NOAPPLY UTF8String]);
//    }
//    else if (segIndex == 1){
//        strcpy(self.trainlistView->m_sFlag, [TRAIN_APPLY UTF8String]);
//    }
//    else{
//        strcpy(self.trainlistView->m_sFlag, [TRAIN_OVER UTF8String]);
//    }
//    
//    [self.trainlistView automaticRefresh];

}


- (void)dealloc{
    self.segment = nil;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
