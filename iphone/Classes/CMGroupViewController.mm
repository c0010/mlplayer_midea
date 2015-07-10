//
//  CMGroupViewController.m
//  MLPlayer
//
//  Created by kyp on 14-6-10.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupViewController.h"
#import "CMTableView.h"
#import "UITableViewCell+Helpper.h"

@interface CMGroupViewController ()

@end

@implementation CMGroupViewController
@synthesize tableView;
#define kCellIdentifier @"com.apple.CMGroupControl.CellIdentifier"
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
    
	tableView = [[CMTableView alloc] initWithFrame:CGRectMake(10,0,UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT-20) style:UITableViewStylePlain];
	
	tableView.delegate = self;
	tableView.dataSource = self;
    
    [tableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    tableView.backgroundColor = [UIColor clearColor];

	[self.view addSubview:tableView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Lifecycle

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
	NSIndexPath *tableSelection = [self.tableView indexPathForSelectedRow];
	[self.tableView deselectRowAtIndexPath:tableSelection animated:NO];
	// Set the navbar style to its default color for the list view.
	self.navigationController.navigationBar.barStyle = UIBarStyleDefault;
}


-(void)viewWillDisappear:(BOOL)animated
{
    
    [super viewWillDisappear:animated];
    
}



#pragma mark UITableView delegate methods

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.row) {
        case 0://搜索群
        {
            CMFindgroupViewController * controller = [[CMFindgroupViewController alloc]init];

            controller.title = I(@"加入群");
            [self.navigationController pushViewController:controller animated:YES];
        }

            break;


        case 1:
        {

            CMNewGroupViewController *controller = [[CMNewGroupViewController alloc]init];
            controller.title = I(@"创建群");

            [self.navigationController pushViewController:controller animated:YES];
        }

            break;
            
        default:
            break;
    }
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    return 10.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 44;
}
// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	
    
	return 2;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	[cell setSelectionStyle:UITableViewCellSelectionStyleGray];
    cell.textLabel.font = [UIFont systemFontOfSize:18];
    [cell setRoundSection:2 atIndex:indexPath.row height:44];
    
    if(indexPath.row==0)
        cell.textLabel.text=I(@"加入群");
    else
        cell.textLabel.text=I(@"创建群");
    
    return cell;
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
