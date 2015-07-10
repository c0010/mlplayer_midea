//
//  CMTrainContentViewController.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainContentViewController.h"
#import "CMTrainContentCell.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "CMLabel.h"
#import "UITableViewCell+Helpper.h"
#import "CMGroupManagementViewController.h"
#import "CMButton.h"


@implementation CMTrainContentViewController


-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.titleLabel.text = self.title;

    tableviewlist = [[CMTableView alloc] initWithFrame:CGRectMake(10,0,UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT-20-44) style:UITableViewStylePlain];
    tableviewlist.delegate=self;
    tableviewlist.dataSource=self;
    tableviewlist.backgroundColor = [UIColor clearColor];
    tableviewlist.separatorStyle = UITableViewCellSeparatorStyleNone;
    
    [self.view addSubview:tableviewlist];
    
}


-(void)setInfoItem:(TMyTrainItem &)item
{
    curItem = item ;
}

#pragma mark TableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return 6;
    
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (indexPath.row == 2) {
        
        CMGroupManagementViewController *controller = [[CMGroupManagementViewController alloc]init];
        controller.title = I(@"培训班成员");
        //[controller setItem:m_TGroupInfoItem];
        [controller setTrainID:NSStringFrom(curItem.sID)];
        controller.editType = CMGroupMemberEditTypeTrain;
        [self.navigationController pushViewController:controller animated:YES];
        
    }
    
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    
    return 10.0 ;

}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    if (indexPath.section == 0) {
        if (indexPath.row == 0) {
            return 80;
        }else if (indexPath.row == 3){
            NSString* str = NSStringFrom(curItem.sTrainTime);
            CGSize labelSize=[str sizeWithFont:[UIFont systemFontOfSize:kTextSizeMid] constrainedToSize:CGSizeMake(260, 80) lineBreakMode:UILineBreakModeWordWrap];
            return 44 + labelSize.height;
        }else if (indexPath.row == 4){
            NSString* str = NSStringFrom(curItem.sAddress);
            CGSize labelSize=[str sizeWithFont:[UIFont systemFontOfSize:kTextSizeMid] constrainedToSize:CGSizeMake(260, 80) lineBreakMode:UILineBreakModeWordWrap];
            return 44 + labelSize.height;
        }
        else if (indexPath.row == 5){
            NSString* str = NSStringFrom(curItem.sDesc);
            CGSize labelSize=[str sizeWithFont:[UIFont systemFontOfSize:kTextSizeMid] constrainedToSize:CGSizeMake(260, 80) lineBreakMode:UILineBreakModeWordWrap];
            return 44 + labelSize.height;
        }
    }
    return 44;
    
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:@"ContentCell"];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:((indexPath.section == 0 && indexPath.row == 2)  || (indexPath.section == 0 && indexPath.row == 1) )? UITableViewCellStyleValue1 : UITableViewCellStyleDefault reuseIdentifier:@"ContentCell"];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    for (UIView *subView in cell.contentView.subviews) {
        [subView removeFromSuperview];
    }
    
    switch (indexPath.section) {
        case 0:
        {
            switch (indexPath.row) {
                case 0:
                {
                    CMButton *imageView = [[CMButton alloc]initWithFrame:CGRectMake(10, 10, 60, 60)];
                    imageView.isRound = YES;
                    //WEAKSELF;
                    [imageView setOnClickListener:^(CMButton * sender){
//                        if ([self.currGroupItem.occupant intValue] == CMGroupMemberStateManager || [self.currGroupItem.occupant intValue] == CMGroupMemberStateCreater) {
//                            [weakSelf showActionSheet];
//                        }
                    }];
                    [imageView sd_setBackgroundImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:curItem.sIcon.c_str()]]  forState:UIControlStateNormal placeholderImage:[UIImage imageNamed:@"default_img_mytrain"]];
    
                    [cell.contentView addSubview:imageView];
                    
                    
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(85, 25, 175, 23);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.numberOfLines = 1;
                    titleLabel.font = [UIFont systemFontOfSize:17];
                    [cell.contentView addSubview:titleLabel];
                    titleLabel.text = [NSString stringWithUTF8String:curItem.sTitle.c_str()];
                    
                    
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
       
                    cell.accessoryType = UITableViewCellAccessoryNone;
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                }
                    break;
                case 1:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 0, 100, 44);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:17];
                    titleLabel.textColor = [UIColor blackColor];
                    titleLabel.text = I(@"班级编号");
                    [cell.contentView addSubview:titleLabel];
                    
                    cell.detailTextLabel.text = NSStringFrom(curItem.sTrainNumber);
                    cell.detailTextLabel.textColor = [UIColor lightGrayColor];
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                    cell.accessoryType = UITableViewCellAccessoryNone;
                    break;
                }
                    
                case 2:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 0, 100, 44);
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:17];
                    titleLabel.textColor = [UIColor blackColor];
                    titleLabel.text = I(@"培训班成员");
                    [cell.contentView addSubview:titleLabel];
                    
                    cell.detailTextLabel.text =[NSString stringWithFormat:@"%d",curItem.nUserCount];
                    cell.detailTextLabel.textColor = [UIColor lightGrayColor];
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    break;
                }
                
                case 3:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 10, 180, 23);
                    titleLabel.font = [UIFont systemFontOfSize:17];
                    titleLabel.textColor = [UIColor blackColor];
                    titleLabel.backgroundColor = [UIColor clearColor];
                    [cell.contentView addSubview:titleLabel];
                    titleLabel.text=I(@"培训时间安排");
                    
                    CMLabel *detailLabel=[[CMLabel alloc]init];
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.textColor = [UIColor lightGrayColor];
                    NSString* str = NSStringFrom(curItem.sTrainTime);
                    
                    UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
                    CGSize constraintSize = CGSizeMake(260, 80);
                    
                    CGSize labelSize=[str sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
                    detailLabel.frame = CGRectMake(10, 33, labelSize.width, labelSize.height + 5);
                    
                    detailLabel.numberOfLines=0;
                    detailLabel.font = cellFont;
                    detailLabel.lineBreakMode=UILineBreakModeWordWrap | UILineBreakModeTailTruncation;
                    
                    [detailLabel setText:str  WithFont:[UIFont systemFontOfSize:kTextSizeMid] AndColor:UIColorRGB(0X333333)];
                    [cell.contentView addSubview:detailLabel];
                    
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                    

                    cell.accessoryType = UITableViewCellAccessoryNone;
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                }
                    break;
                    
                case 4:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 10, 180, 23);
                    titleLabel.font = [UIFont systemFontOfSize:17];
                    titleLabel.textColor = [UIColor blackColor];
                    titleLabel.backgroundColor = [UIColor clearColor];
                    [cell.contentView addSubview:titleLabel];
                    titleLabel.text=I(@"培训地点");
                    
                    CMLabel *detailLabel=[[CMLabel alloc]init];
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.textColor = [UIColor lightGrayColor];
                    NSString* str = NSStringFrom(curItem.sAddress);
                    
                    UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
                    CGSize constraintSize = CGSizeMake(260, 80);
                    
                    CGSize labelSize=[str sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
                    detailLabel.frame = CGRectMake(10, 33, labelSize.width, labelSize.height + 5);
                    
                    detailLabel.numberOfLines=0;
                    detailLabel.font = cellFont;
                    detailLabel.lineBreakMode=UILineBreakModeWordWrap | UILineBreakModeTailTruncation;
                    
                    [detailLabel setText:str  WithFont:[UIFont systemFontOfSize:kTextSizeMid] AndColor:UIColorRGB(0X333333)];
                    [cell.contentView addSubview:detailLabel];
                    
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                    
                    
                    cell.accessoryType = UITableViewCellAccessoryNone;
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                }
                    break;
                    
                case 5:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(10, 10, 180, 23);
                    titleLabel.font = [UIFont systemFontOfSize:17];
                    titleLabel.textColor = [UIColor blackColor];
                    titleLabel.backgroundColor = [UIColor clearColor];
                    [cell.contentView addSubview:titleLabel];
                    titleLabel.text=I(@"培训内容");
                    
                    CMLabel *detailLabel=[[CMLabel alloc]init];
                    detailLabel.backgroundColor = [UIColor clearColor];
                    detailLabel.textColor = [UIColor lightGrayColor];
                    NSString* str = [NSStringFrom(curItem.sDesc) isEqualToString:@""]?I(@"无"):NSStringFrom(curItem.sDesc);
                    
                    UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
                    CGSize constraintSize = CGSizeMake(260, 80);
                    
                    CGSize labelSize=[str sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
                    detailLabel.frame = CGRectMake(10, 33, labelSize.width, labelSize.height + 5);
                    
                    detailLabel.numberOfLines=0;
                    detailLabel.font = cellFont;
                    detailLabel.lineBreakMode=UILineBreakModeWordWrap | UILineBreakModeTailTruncation;
                    
                    [detailLabel setText:str  WithFont:[UIFont systemFontOfSize:kTextSizeMid] AndColor:UIColorRGB(0X333333)];
                    [cell.contentView addSubview:detailLabel];
                    
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                    
                    
                    cell.accessoryType = UITableViewCellAccessoryNone;
                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
                }
                    break;
                    
                    
                default:
                    break;
            }
        }
            
            
                default:
            break;
    }
    [cell setRoundSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[self tableView:tableView heightForRowAtIndexPath:indexPath]];
    
    return cell;
    
}


@end
