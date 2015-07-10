//
//  CMSysMessageDetailyViewController.m
//  MLPlayer
//
//  Created by water on 14-6-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMSysMessageDetailyViewController.h"
#import "CMLabel.h"
#import "NSDate+Helper.h"
#import "CMAlertView.h"
#import "UITableViewCell+Helpper.h"
#import "CMInteractViewController.h"
#import "tool.h"

@interface CMSysMessageDetailyViewController ()

@end

@implementation CMSysMessageDetailyViewController
@synthesize theTableView;

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
    self.titleLabel.text = I(@"系统信息");

	theTableView = [[UITableView alloc] initWithFrame:CGRectMake(10, 0, UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT - 64) style:UITableViewStylePlain];
	[theTableView setDelegate:self];
	[theTableView setDataSource:self];
    theTableView.showsVerticalScrollIndicator = NO;
    theTableView.separatorStyle =UITableViewCellSeparatorStyleNone;
    self.theTableView.backgroundColor= [UIColor clearColor];
    
	[self.view addSubview:theTableView];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 3;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.section) {
        case 0:
        {
            UITableViewCell *cell = [self tableView:tableView cellForRowAtIndexPath:indexPath];
            
           UILabel *descLabel = (UILabel *)[cell.contentView viewWithTag:100];
            if (descLabel) {
                return CGRectGetMaxY(descLabel.frame) + 10;
            }
            return 60;
        }
            break;
        case 1:
            return 40;
            break;
        case 2:
            return 40;
            break;
        default:
            break;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    
    if (section == 1) {
        return 100.0 ;
    }else if (section == 2) {
        return 20.0 ;
    }
    return 10.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kSysMessageDetailyCell];
    
	if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kSysMessageDetailyCell];
    }
    
    for (UIView *subView in cell.contentView.subviews) {
        [subView removeFromSuperview];
    }
    
    switch (indexPath.section) {
        case 0:
        {
            CMLabel *titleLabel = [[CMLabel alloc]initWithFrame:CGRectMake(10, 10, 240, 20)];
            titleLabel.textColor = [UIColor blackColor];
            titleLabel.font = [UIFont systemFontOfSize:13.f];
            titleLabel.numberOfLines = 0;
            titleLabel.lineBreakMode = NSLineBreakByWordWrapping | NSLineBreakByTruncatingTail;
            titleLabel.backgroundColor = [UIColor clearColor];
            
            UILabel *descLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 35, 280, 20)];
            descLabel.textColor = [UIColor lightGrayColor];
            descLabel.font = [UIFont systemFontOfSize:13.f];
            descLabel.numberOfLines = 0;
            descLabel.tag = 100;
            descLabel.lineBreakMode = NSLineBreakByWordWrapping | NSLineBreakByTruncatingTail;
            descLabel.backgroundColor = [UIColor clearColor];
            
            UILabel *timeLabel = [[UILabel alloc]initWithFrame:CGRectMake(250, 10, 40, 20)];
            timeLabel.textColor = [UIColor lightGrayColor];
            timeLabel.font = [UIFont systemFontOfSize:10.f];
            timeLabel.backgroundColor = [UIColor clearColor];
            timeLabel.text = [NSDate stringForDisplayFromDate:self.currMessageItem.sendTime ];
            timeLabel.textAlignment = UITextAlignmentRight;
            
            
            [cell.contentView addSubview:titleLabel];
            [cell.contentView addSubview:descLabel];
            [cell.contentView addSubview:timeLabel];
            
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            
            NSString *content = self.currMessageItem.content;

            NSString *roomName = self.currMessageItem.sysmessage.roomName;
            titleLabel.text = self.currMessageItem.content;

            CGSize tsize = [content sizeWithFont:descLabel.font constrainedToSize:CGSizeMake(CGRectGetWidth(titleLabel.frame), 60) lineBreakMode:NSLineBreakByWordWrapping];
            
            [titleLabel setFrameHeight: tsize.height];
            
            NSString *desc = @"";
            
            if (self.currMessageItem.type == CMInteractSystemMessageTypeApply) {
                self.titleLabel.text = self.currMessageItem.content;
                [titleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:titleLabel.font AndColor:UIColorRGB(0x083E73)];
                [titleLabel setKeyWordRange:NSMakeRange(0, self.currMessageItem.sysmessage.rawSenderName.length) WithFont:titleLabel.font AndColor:UIColorRGB(0x083E73)];
                
                
                desc = [NSString stringWithFormat:I(@"验证信息：%@"),self.currMessageItem.sysmessage.key.length > 0 ? self.currMessageItem.sysmessage.key : I(@"无")];
    
            }else if (self.currMessageItem.type == CMInteractSystemMessageTypeInvite){
                [titleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:titleLabel.font AndColor:UIColorRGB(0x083E73)];
                [titleLabel setKeyWordRange:NSMakeRange(0, self.currMessageItem.sysmessage.rawSenderName.length) WithFont:titleLabel.font AndColor:UIColorRGB(0x083E73)];
            }
            
            descLabel.text = desc;
            
            CGSize size = [desc sizeWithFont:descLabel.font constrainedToSize:CGSizeMake(CGRectGetWidth(descLabel.frame), 100) lineBreakMode:NSLineBreakByWordWrapping];
            
            [descLabel setFrameY:CGRectGetMaxY(titleLabel.frame) + 10 Height:size.height];
            
            [cell setRoundSection:[self tableView:self.theTableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:CGRectGetMaxY(descLabel.frame) + 10];

        }
            break;
        case 1:
        {
            UIButton *agreeButton= [UIButton buttonWithType:UIButtonTypeCustom];
            agreeButton.tag = 1;
            agreeButton.frame = CGRectMake(0, 0, 300, 40);
            [agreeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [agreeButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0x085ba1)] forState:UIControlStateNormal];
            [agreeButton setTitle:I(@"同意") forState:UIControlStateNormal];
            [agreeButton addTarget:(id)self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
            [agreeButton setAccessibilityLabel:I(@"提交")];
            [cell.contentView addSubview:agreeButton];
        }
            break;
        case 2:
        {
            UIButton *refusalButton= [UIButton buttonWithType:UIButtonTypeCustom];
            refusalButton.tag = 2;
            refusalButton.frame = CGRectMake(0, 0, 300, 40);
            [refusalButton setTitleColor:UIColorRGB(0x085ba1) forState:UIControlStateNormal];
            [refusalButton setBackgroundImage:[CMImage imageWithColor:[UIColor whiteColor]] forState:UIControlStateNormal];
            [refusalButton setTitle:I(@"拒绝") forState:UIControlStateNormal];
            [refusalButton addTarget:(id)self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
            [cell.contentView addSubview:refusalButton];
        }
            break;
        default:
            break;
    }
    
    
    return cell;
}

- (void) buttonPressed:(UIButton *)button{
    if (self.buttonListener) {
        self.buttonListener(button);
        self.buttonListener = nil;
        
        [self.navigationController popViewControllerAnimated:YES];
    }
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
