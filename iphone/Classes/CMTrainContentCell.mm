//
//  CMTrainContentCell.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainContentCell.h"

@implementation CMTrainContentCell


-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
  
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        
        trainContentBackgroundView = [[UIView alloc] init];
        trainContentBackgroundView.backgroundColor = [UIColor whiteColor];
        
        cutOffLine = [[UIImageView alloc] init];
        [cutOffLine setImage:[UIImage imageNamed:@"train_cell_sep"]];
        
        modeLab = [[UILabel alloc]init];
        [modeLab setTextColor:[UIColor blackColor]];
        [modeLab setFont:[UIFont systemFontOfSize:14]];
        [modeLab setBackgroundColor:[UIColor clearColor]];
        
        infoLab = [[UILabel alloc]init];
        [infoLab setTextColor:[UIColor grayColor]];
        [infoLab setFont:[UIFont systemFontOfSize:14]];
        [infoLab setBackgroundColor: [UIColor clearColor]];
        
        
        [trainContentBackgroundView addSubview:modeLab];
        [trainContentBackgroundView addSubview:infoLab];
        [trainContentBackgroundView addSubview:cutOffLine];
        
        [self.contentView addSubview:trainContentBackgroundView];
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.backgroundColor = [UIColor clearColor];
    }
    
    return self;
}

-(void)setCellInfo:(TMyTrainItem &)item index:(int)index
{
    int height;
    
    switch (index) {
        case 0:
            [modeLab setFrame:CGRectMake(80, 10, UI_IOS_WINDOW_WIDTH-20-80-10, 15)];
            [infoLab setFrame:CGRectMake(80, 50, UI_IOS_WINDOW_WIDTH-20-80-10, 15)];
            [modeLab setText:[NSString stringWithUTF8String:item.sTitle.c_str()]];
            height = 80;
            
            
            break;
        case 1:
        {
            [modeLab setFrame:CGRectMake(8, 8, 100, 20)];
            [infoLab setFrame:CGRectMake(170, 8, 115, 20)];
            [infoLab setTextAlignment:NSTextAlignmentRight];
            [infoLab setText:[NSString stringWithUTF8String:item.sTitle.c_str()]];
            [modeLab setText:I(@"班级编号")];
            height = 35;
            
            break;
        }
            
        case 2:
        {
            [modeLab setFrame:CGRectMake(8, 8, 100, 20)];
            [infoLab setFrame:CGRectMake(170, 8, 115, 20)];
            [infoLab setTextAlignment:NSTextAlignmentRight];
            [infoLab setText:[NSString stringWithUTF8String:item.sTitle.c_str()]];
            [modeLab setText:I(@"培训班成员")];
            self.accessoryType=UITableViewCellAccessoryDisclosureIndicator;
            height = 35;
            break;
        }
            
        case 3:
        {
            [modeLab setFrame:CGRectMake(8, 8, 100, 20)];
            [infoLab setFrame:CGRectMake(8, 30, UI_IOS_WINDOW_WIDTH-20-16  , 20)];
            [infoLab setTextAlignment:NSTextAlignmentLeft];
            [infoLab setText:[NSString stringWithUTF8String:item.sTitle.c_str()]];
            [modeLab setText:I(@"培训时间")];
            height = 55;
            
            break;
        }
            
        case 4:
        {
            [modeLab setFrame:CGRectMake(8, 8, 100, 20)];
            
            [infoLab setTextAlignment:NSTextAlignmentLeft];
            [infoLab setText:[NSString stringWithUTF8String:item.sDesc.c_str()]];
            [modeLab setText:I(@"培训地点")];
            CGSize size = [infoLab.text sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(300-16, MAXFLOAT) lineBreakMode:NSLineBreakByCharWrapping];
            [infoLab setFrame:CGRectMake(8, 30, UI_IOS_WINDOW_WIDTH-20-16  , size.height)];
            height = 40+size.height;
            
            
            break;
        }
            
        case 5:
        {
            [modeLab setFrame:CGRectMake(8, 8, 100, 20)];
            [infoLab setTextAlignment:NSTextAlignmentLeft];
            [infoLab setText:[NSString stringWithUTF8String:item.sTitle.c_str()]];
            [modeLab setText:I(@"培训内容")];
            CGSize Size = [infoLab.text sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(300-16, MAXFLOAT) lineBreakMode:NSLineBreakByCharWrapping];
            [infoLab setFrame:CGRectMake(8, 30, UI_IOS_WINDOW_WIDTH-20-16  , Size.height)];
            height = 40+Size.height;
            
            
            break;
            
        }
        default:
            break;
    
    }
    trainContentBackgroundView.frame = CGRectMake(10, 0, UI_IOS_WINDOW_WIDTH - 20,  height);
    cutOffLine.frame = CGRectMake(0, height - 1, UI_IOS_WINDOW_WIDTH - 20, 1);
}

@end
