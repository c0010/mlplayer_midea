//
//  CMGroupAndMsgViewController.m
//  MLPlayer
//
//  Created by kyp on 14-6-17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupAndMsgViewController.h"
#import "CMLabel.h"
@interface CMGroupAndMsgViewController ()

@end

@implementation CMGroupAndMsgViewController
@synthesize searchBar;
@synthesize tableView;
@synthesize segCtrl;
#define kCellIdentifier @"com.apple.CMGroupAndMsgViewController.CellIdentifier"
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
    UIView *newBak=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20)];
    
    [newBak setBackgroundColor:kColorBackground];
    [self.view addSubview:newBak];
    CMRELEASE(newBak);
    
    
    searchBar=[[UISearchBar alloc]initWithFrame:CGRectMake(0, 0, 320, 40)];
    searchBar.delegate=self;
    [searchBar setPlaceholder:I(@"搜素")];
    
    searchDisplayController = [[UISearchDisplayController alloc]initWithSearchBar:searchBar contentsController:self];
    searchDisplayController.active = NO;
    searchDisplayController.searchResultsDataSource = self;
    searchDisplayController.searchResultsDelegate = self;

    CGRect f = [[self view] bounds];
    //f.origin.y += (48-10);
	f.size.height = UI_IOS_WINDOW_HEIGHT - 64 - (48-10)+38;
    tableView=[[UITableView alloc]initWithFrame:f];
    
    tableView.delegate = self;
	tableView.dataSource = self;
	[tableView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
    
    tableView.scrollEnabled = YES;
    
    tableView.tableHeaderView=searchBar;
    
    [self.view addSubview:tableView];
    
    NSArray *buttons = [NSArray arrayWithObjects:@" 消息 ", @" 群组 ", nil];
    segCtrl = [[UISegmentedControl alloc] initWithItems:buttons];
    //设置横向按钮风格
    segCtrl.segmentedControlStyle = UISegmentedControlStyleBar;
    segCtrl.tintColor=[UIColor whiteColor];
   // [segCtrl addTarget:self action:@selector(switchtableview:) forControlEvents:UIControlEventValueChanged];
    self.navigationItem.titleView=segCtrl;
}


#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 50;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil) {
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] ;
        
        UIImageView *imageView = [[UIImageView alloc] init];
        imageView.frame = CGRectMake(10, 8.5, 43, 43);
        imageView.backgroundColor = [UIColor clearColor];
        imageView.tag = 1000;
        [cell.contentView addSubview:imageView];
        
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.frame = CGRectMake(60, 9, 230, 23);
        titleLabel.font = [UIFont systemFontOfSize:17];
        titleLabel.tag = 2000;
        [cell.contentView addSubview:titleLabel];
        
        
        CMLabel *detailLabel = [[CMLabel alloc] init];
        detailLabel.frame = CGRectMake(60, 32, 230, 19);
        detailLabel.tag = 3000;
        [cell.contentView addSubview:detailLabel];
        
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
	}
    
    UIImageView *imgView = (UIImageView *)[cell.contentView viewWithTag:1000];
    UILabel *titleLbl = (UILabel *)[cell.contentView viewWithTag:2000];
    CMLabel *detailLbl = (CMLabel *)[cell.contentView viewWithTag:3000];
    
    imgView.image = nil;
    imgView.image = [UIImage imageNamed:@"surveyicon"];
    titleLbl.text = @"123232";
    detailLbl.text = @"12312675675";
    
    
	return cell;
    
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 50;
}


- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    
    // Request table view to reload
    [tableView reloadData];
}

#pragma UISearchDisplayDelegate

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    NSLog(@"1234");
 }


- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar
{
    searchBar.showsCancelButton = YES;  //关键语句
    UIView *topView = searchBar.subviews[0];
    for(id cc in topView.subviews)
    {
        if([cc isKindOfClass:NSClassFromString(@"UINavigationButton")])
        {
            UIButton *btn = (UIButton *)cc;
            [btn setTitle:I(@"取消")  forState:UIControlStateNormal];
        }
    }
    
    NSLog(@"123");
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
