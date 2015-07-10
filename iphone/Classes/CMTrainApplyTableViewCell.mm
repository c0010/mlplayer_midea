//
//  CMTrainApplyTableViewCell.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainApplyTableViewCell.h"

@implementation CMTrainApplyTableViewCell

- (void)awakeFromNib {
    // Initialization code
}

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        titleLabel = [self GetLabel:[UIColor clearColor] textcolor:UIColorRGB(0x333333) fontsize:15];
        
        trainDateLabel = [self GetLabel:[UIColor clearColor]textcolor:UIColorRGB(0x999999) fontsize:11];
        trainDateLabel.frame = CGRectMake(12, 39, UI_IOS_WINDOW_WIDTH-24, 14);
        
        
        addressLabel = [self GetLabel:[UIColor clearColor] textcolor:UIColorRGB(0x8a8a8a) fontsize:12];
        addressLabel.frame = CGRectMake(28, 57, UI_IOS_WINDOW_WIDTH-24, 14);

        
        dateImageView = [[UIImageView alloc]initWithFrame:CGRectMake(11, 40, 12, 12)];
        [dateImageView setImage:[UIImage imageNamed:@"traintime"]];
        
        addressImageView = [[UIImageView alloc]initWithFrame:CGRectMake(11, 58, 12, 12)];
        [addressImageView setImage:[UIImage imageNamed:@"trainaddress"]];
        
        stateBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [stateBtn setFrame:CGRectMake(275, 14, 36, 13)];
        [stateBtn setTitleColor:UIColorRGB(0xf99200) forState:UIControlStateNormal];
        [stateBtn.titleLabel setFont:[UIFont systemFontOfSize:9]];
        [stateBtn setBackgroundImage:[UIImage imageNamed:@"trainstate"] forState:UIControlStateNormal];
        
        separatorLine = [[UIImageView alloc]init];
        [separatorLine setImage:[UIImage imageNamed:@"learn_cell_sep"]];
        separatorLine.contentMode = UIViewContentModeScaleAspectFit;
        separatorLine.frame = CGRectMake(10, 66, UI_IOS_WINDOW_WIDTH-20, 1);
        
        [self.contentView addSubview:titleLabel];
        [self.contentView addSubview:trainDateLabel];
        //[self.contentView addSubview:addressLabel];
        //[self.contentView addSubview:dateImageView];
        //[self.contentView addSubview:addressImageView];
        [self.contentView addSubview:stateBtn];
        [self.contentView addSubview:separatorLine];
        
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.backgroundColor=UIColorRGB(0xf7f7f7);
        self.accessoryType = UITableViewCellAccessoryNone;
        
        [self setSelectionStyle:UITableViewCellSelectionStyleGray];
    }
    return self;
}

-(UILabel*)GetLabel:(UIColor*)backgroundcolor textcolor: (UIColor*)textcolor fontsize:(int)size
{
    UILabel* lb = [[UILabel alloc] init];
    lb.backgroundColor = [UIColor clearColor];
    lb.textAlignment = NSTextAlignmentLeft;
    lb.font = [UIFont systemFontOfSize:size];
    lb.textColor = textcolor;
    return lb;
}

-(void)setcellinfo:(TTrainApplyItem &)trainlistItem
{
    if ([[NSString stringWithUTF8String:trainlistItem.sFlag.c_str()] isEqualToString:@"applied"]) {
        //addressImageView.hidden = YES;
        //addressLabel.hidden = YES;
        stateBtn.hidden = NO;
        
        //[dateImageView setImage:[UIImage imageNamed:@"applytime"]];
        
        int flag = trainlistItem.nIsPass;
        if (flag == 1) {
            [stateBtn setTitle:I(@"成功") forState:UIControlStateNormal];
        }else if (flag == 0){
            [stateBtn setTitle:I(@"审核中") forState:UIControlStateNormal];
        }else if (flag == 2){
            [stateBtn setTitle:I(@"未通过") forState:UIControlStateNormal];
        }
        
        [titleLabel setFrame:CGRectMake(12,14,UI_IOS_WINDOW_WIDTH-66,15)];
        
        trainDateLabel.text = [NSString stringWithUTF8String:trainlistItem.sAppliedTime.c_str()];
        
    }else if ([[NSString stringWithUTF8String:trainlistItem.sFlag.c_str()] isEqualToString:@"over"]) {
        //addressImageView.hidden = NO;
        //addressLabel.hidden = NO;
        stateBtn.hidden = NO;
        
        [stateBtn setTitle:I(@"已结束") forState:UIControlStateNormal];
        [titleLabel setFrame:CGRectMake(12,14,UI_IOS_WINDOW_WIDTH-66,15)];
        //[dateImageView setImage:[UIImage imageNamed:@"traintime"]];
        
        trainDateLabel.text = [NSString stringWithUTF8String:trainlistItem.sTrainTime.c_str()];
        
    }else
    {
        stateBtn.hidden = YES;
        //addressImageView.hidden = NO;
        //addressLabel.hidden = NO;
        [titleLabel setFrame:CGRectMake(12,14,UI_IOS_WINDOW_WIDTH-24,15)];
        
        //[dateImageView setImage:[UIImage imageNamed:@"traintime"]];
        
        trainDateLabel.text = [NSString stringWithUTF8String:trainlistItem.sTrainTime.c_str()];
    }
    
    
    titleLabel.text = [NSString stringWithUTF8String:trainlistItem.sTitle.c_str()];
    addressLabel.text = [NSString stringWithFormat:@"%@",[NSString stringWithUTF8String:trainlistItem.sAddress.c_str()]];
    
    
    
    
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
