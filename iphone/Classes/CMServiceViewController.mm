//
//  CMServiceViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-12-6.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMServiceViewController.h"

#define SERVICE_CELL @"servicecell"

@interface CMServiceViewController ()
- (IBAction)phoneBtnPressed:(id)sender;
@end

@implementation CMServiceViewController

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
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    UITableView *tableView = [[UITableView alloc] init];
    tableView.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64);
    tableView.backgroundColor = [UIColor clearColor];
    tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    tableView.separatorColor = UIColorRGB(0x757575);
    tableView.delegate = self;
    tableView.dataSource = self;
    [self.view addSubview:tableView];
    
    UIView *footView = [[UIView alloc] init];
    footView.frame = CGRectMake(0,10, UI_IOS_WINDOW_WIDTH, 200);
    footView.backgroundColor = [UIColor clearColor];
    
    UIImageView *imgView = [[UIImageView alloc] init];
    imgView.frame = CGRectMake(0, 0, 200, 200);
    imgView.center = footView.center;
    imgView.image = [UIImage imageNamed:@"ulpweixin@2x"];
    [footView addSubview:imgView];
    CMRELEASE(imgView);
    
    //tableView.tableFooterView = footView;
    tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    CMRELEASE(footView);
    CMRELEASE(tableView);
}

- (IBAction)phoneBtnPressed:(id)sender
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"tel://4001007350"]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - TableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 3;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 55;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:SERVICE_CELL];
    
    if (cell == nil)
    {
# if ! __has_feature(objc_arc)
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SERVICE_CELL] autorelease];
#else
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SERVICE_CELL];
#endif
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    
    if (indexPath.row == 0)
    {
        cell.textLabel.text =I(@"客服电话：400-100-7350");
        
        UIButton *phoneBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        phoneBtn.frame = CGRectMake(240, 7.5, 54, 40);
        phoneBtn.backgroundColor = [UIColor clearColor];
        [phoneBtn setImage:[UIImage imageNamed:@"servicephone_n@2x"] forState:UIControlStateNormal];
        [phoneBtn setImage:[UIImage imageNamed:@"servicephone_p@2x"] forState:UIControlStateHighlighted];
        [phoneBtn addTarget:self action:@selector(phoneBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
        [cell.contentView addSubview:phoneBtn];
    }
    else if (indexPath.row == 1)
    {
        cell.textLabel.text = I(@"QQ：2561269605");
    }
    else if (indexPath.row == 2)
    {
        cell.textLabel.text = I(@"邮箱：wdxuexi@wunding.com");
    }
    else if (indexPath.row == 3)
    {
        cell.textLabel.text = I(@"官方微博：@美课");
    }
    else
    {
        cell.textLabel.text = I(@"公众微信号：wdxuexi");
    }
    
    cell.textLabel.textColor = UIColorRGB(0x757575);
    return cell;
}

@end
