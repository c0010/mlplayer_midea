//
//  CMTrainSignTableViewCell.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainSignTableViewCell.h"

@implementation CMTrainSignTableViewCell

- (void)awakeFromNib {
    // Initialization code
}

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        titleLab = [self GetLabel:[UIColor clearColor] textcolor:UIColorRGB(0x333333) fontsize:15];
        [titleLab setFrame:CGRectMake(12, 14, UI_IOS_WINDOW_WIDTH-24, 15)];
        
        dateLab = [self GetLabel:[UIColor clearColor] textcolor:UIColorRGB(0x999999) fontsize:11];
        [dateLab setFrame:CGRectMake(12, 39, UI_IOS_WINDOW_WIDTH-24, 14)];
        
        addressLab = [self GetLabel:[UIColor clearColor] textcolor:UIColorRGB(0x8a8a8a) fontsize:12];
        [addressLab setFrame:CGRectMake(28, 57, UI_IOS_WINDOW_WIDTH-24, 12)];
        
        stateBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [stateBtn setFrame:CGRectMake(275, 10, 25, 13)];
        [stateBtn setBackgroundImage:[UIImage imageNamed:@"signstate"]forState:UIControlStateNormal];
        [stateBtn setTitle:I(@"已签") forState:UIControlStateNormal];
        [stateBtn.titleLabel setFont:[UIFont systemFontOfSize:9]];
       [stateBtn setTitleColor:UIColorRGB(0xf99200) forState:UIControlStateNormal];
        stateBtn.hidden = YES;
        
        UIImageView *dateImageView = [[UIImageView alloc]initWithFrame:CGRectMake(11, 39, 12, 12)];
        [dateImageView setImage:[UIImage imageNamed:@"signtime"]];
        //[self.contentView addSubview:dateImageView];
        CMRELEASE(dateImageView);
        
        UIImageView *addressImageView = [[UIImageView alloc]initWithFrame:CGRectMake(11, 57, 12, 12)];
        addressImageView.tag = 1000;
        [addressImageView setImage:[UIImage imageNamed:@"signaddress"]];
        //[self.contentView addSubview:addressImageView];
        CMRELEASE(addressImageView);
        
        separatorLine = [[UIImageView alloc]init];
        [separatorLine setImage:[UIImage imageNamed:@"learn_cell_sep"]];
        separatorLine.contentMode = UIViewContentModeScaleAspectFit;
        separatorLine.frame = CGRectMake(10, 66, UI_IOS_WINDOW_WIDTH-20, 1);
        
        
        [self.contentView addSubview:titleLab];
        [self.contentView addSubview:dateLab];
        //[self.contentView addSubview:addressLab];
        [self.contentView addSubview:stateBtn];
        [self.contentView addSubview:separatorLine];
        
        
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

-(void)setCellInfo:(TTrainSignInItem &)item
{
    if ([[NSString stringWithUTF8String:item.sFlag.c_str()] isEqualToString:@"nosignin"]) {
        stateBtn.hidden = YES;
        addressLab.hidden = NO;

        [titleLab setFrame:CGRectMake(12, 14, UI_IOS_WINDOW_WIDTH-24, 15)];
        
        [dateLab setText:[NSString stringWithUTF8String:item.sTime.c_str()]];
        
    }else{
        stateBtn.hidden = NO;
        addressLab.hidden = YES;
        [titleLab setFrame:CGRectMake(12, 14, UI_IOS_WINDOW_WIDTH-65, 15)];

        
        [dateLab setText:[NSString  stringWithUTF8String:item.sSignInTime.c_str()]];
    }
    
    [titleLab setText:[NSString  stringWithUTF8String:item.sTitle.c_str()]];
    
    //[addressLab setText:[NSString stringWithUTF8String:item.sAddress.c_str()]];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
