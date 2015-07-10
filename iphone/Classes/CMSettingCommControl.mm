//
//  CMBufferTimeControl.m
//  MLPlayer
//
//  Created by sunjj on 11-7-12.
//  Copyright 2011 w. All rights reserved.
//

#include "stdafx.h"
#import "CMSettingCommControl.h"

#define kCellIdentifier @"com.apple.CMSettingCommControl.CellIdentifier"


@implementation CMSettingCommControl
@synthesize tableViews;

-(void)setSettingType:(NSString*)type
{
	m_type =  type;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
	self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
	//self.tableViews = nil;
	return self;
}

-(void)viewDidLoad
{	
	[super viewDidLoad];
		
	CGRect f = [[self view] bounds];	
	
	[self setTableViews:[[UITableView alloc] initWithFrame:f style:UITableViewStyleGrouped]];
	[[self tableViews] setDelegate:self];
	[[self tableViews] setDataSource:self];
    [[self tableViews] setBackgroundColor:kColorBackground];
	[[self tableViews] setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	[self tableViews].sectionHeaderHeight = 40;
	[self tableViews].sectionFooterHeight = 0;
	
	[self.view addSubview:[self tableViews]];		
			
}

#pragma mark UIViewController delegate

- (void)viewWillAppear:(BOOL)animated
{

}

#pragma mark UITableView delegate methods

	// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	if(indexPath.section == 0)
	{
		if ([m_type isEqualToString:@"buffertime"]) {
			int buftime = 90;
			switch(indexPath.row)
			{
				case 0:
					buftime = 30;				
					break;
				case 1:
					buftime = 60;
					break;
				case 2:
					buftime = 90;
					break;
				case 3:
					buftime = 120;
					break;
				case 4:
					buftime = 180;
					break;
			}
			SETTING.SetBufTime(buftime);
		}else if ([m_type isEqualToString:@"playmode"]) {
			
			// 播放模式：1"全屏"、2"普通"，Symbian/Windows Mobile默认为普通，iPhone/Android（Ophone）默认为全屏
			int value = 1;
			switch(indexPath.row)
			{
				case 0:
					value = 1;				
					break;
				case 1:
					value = 2;
					break;
			}
			SETTING.SetPlayMode(value);
			
		}else if ([m_type isEqualToString:@"fullscreenmode"]) {
				// 全屏模式：1"保持宽高比例"、2"填满屏幕"，默认为"保持宽高比例"
			int value = 1;
			switch(indexPath.row)
			{
				case 0:
					value = 1;				
					break;
				case 1:
					value = 2;
					break;
			}
			SETTING.SetFullScreenMode(value);
		
		}else if ([m_type isEqualToString:@"autoloadmore"]) {
			// 自动加载"更多"：0不自动加载，1自动加载，默认1
			int value = 1;
			switch(indexPath.row)
			{
				case 0:
					value = 0;				
					break;
				case 1:
					value = 1;
					break;
			}
			SETTING.SetAutoLoadMore(value);			
		}		
		
		SETTING.Save();
		[self.tableViews reloadData];
	}
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];

	
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
	if(section == 0)
	{
		if ([m_type isEqualToString:@"buffertime"]) {
			return 5;
			
		}else if ([m_type isEqualToString:@"playmode"]) {
			return 2;
			
		}else if ([m_type isEqualToString:@"fullscreenmode"]) {
			return 2;
			
		}else if ([m_type isEqualToString:@"autoloadmore"]) {
			return 2;
			
		}		
	}
	return 0;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil)
	{
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
		cell.textLabel.textAlignment = UITextAlignmentLeft;
		cell.textLabel.textColor = [UIColor blackColor];
		cell.textLabel.highlightedTextColor = [UIColor blackColor];
		cell.textLabel.font = [UIFont systemFontOfSize:15.0];
	}
	if(indexPath.section == 0)
	{
		if ([m_type isEqualToString:@"buffertime"]) {
			
			int buftime = SETTING.GetBufTime();
			
			cell.accessoryType = UITableViewCellAccessoryNone;
			NSString *pstr = I(@"秒");
			switch(indexPath.row)
			{
				case 0:
					if(buftime == 30)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = [NSString stringWithFormat:@"30%@",pstr];
					break;
				case 1:
					if(buftime == 60)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = [NSString stringWithFormat:@"60%@",pstr];
					break;
				case 2:
					if(buftime == 90)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = [NSString stringWithFormat:@"90%@",pstr];
					break;
				case 3:
					if(buftime == 120)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = [NSString stringWithFormat:@"120%@",pstr];
					break;
				case 4:
					if(buftime == 180)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = [NSString stringWithFormat:@"180%@",pstr];
					break;
					
			}		
			
		}else if ([m_type isEqualToString:@"playmode"]) {
			
			int value = SETTING.GetPlayMode();
			
			cell.accessoryType = UITableViewCellAccessoryNone;
			
			switch(indexPath.row)
			{
				case 0:
					if(value == 1)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = I(@"全屏");
					break;
				case 1:
					if(value == 2)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = I(@"普通");
					break;
			}
			
		}else if ([m_type isEqualToString:@"fullscreenmode"]) {
			int value = SETTING.GetFullScreenMode();
			
			cell.accessoryType = UITableViewCellAccessoryNone;
			
			switch(indexPath.row)
			{
				case 0:
					if(value == 1)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = I(@"保持宽高比例");
					break;
				case 1:
					if(value == 2)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = I(@"填满屏幕");
					break;
			}			
			
		}else if ([m_type isEqualToString:@"autoloadmore"]) {
			int value = SETTING.GetAutoLoadMore();
			
			cell.accessoryType = UITableViewCellAccessoryNone;
			
			switch(indexPath.row)
			{
				case 0:
					if(value == 0)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = I(@"不自动加载");
					break;
				case 1:
					if(value == 1)
						cell.accessoryType = UITableViewCellAccessoryCheckmark;
					cell.textLabel.text = I(@"自动加载");
					break;
			}
			
		}	
		
	}
	
	[cell setSelectionStyle:UITableViewCellSelectionStyleNone];
	
	return cell;
}



@end
