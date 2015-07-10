//
//  CMTrainListTableViewCell.m
//  MLPlayer
//
//  Created by 张永兵 on 14-12-19.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainListTableViewCell.h"
#import "SDWebImage/UIImageView+WebCache.h"


@implementation CMTrainListTableViewCell

- (void)awakeFromNib {
    // Initialization code
}

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        titleLabel = [self GetLabel:[UIColor clearColor] textcolor:UIColorRGB(0x333333) fontsize:15];
        titleLabel.frame = CGRectMake(70,(65 - 20)/2,UI_IOS_WINDOW_WIDTH-84,20);

        
        trainDateLabel = [self GetLabel:[UIColor clearColor]textcolor:[UIColor blackColor] fontsize:12];
        
        addressLabel = [self GetLabel:[UIColor clearColor] textcolor:[UIColor blackColor] fontsize:12];
        
        separatorLine = [[UIImageView alloc]init];
        [separatorLine setImage:[UIImage imageNamed:@"learn_cell_sep"]];
        separatorLine.frame = CGRectMake(0, 64, UI_IOS_WINDOW_WIDTH, 1);
        
        iconImage = [[UIImageView alloc]initWithFrame:CGRectMake(10, 7.5, 50, 50)];
        
        [self.contentView addSubview:titleLabel];
        [self.contentView addSubview:separatorLine];
        [self.contentView addSubview:iconImage];
        //[self.contentView addSubview:trainDateLabel];
        //[self.contentView addSubview:addressLabel];
        
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.backgroundColor=UIColorRGB(0xffffff);
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

-(void)setcellinfo:(TMyTrainItem &)trainlistItem
{
    
    titleLabel.text = [NSString stringWithUTF8String:trainlistItem.sTitle.c_str()];
    [iconImage  sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:trainlistItem.sIcon.c_str()]] placeholderImage:[UIImage imageNamed:@"default_img_mytrain"]];
    
    //trainDateLabel.text = [NSString stringWithFormat:@"时间: %@",[NSString stringWithUTF8String:trainlistItem.sTrainTime.c_str()]];
    
    // CGSize size=[self.trainDateLabel.text sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(CGFLOAT_MAX, 10) lineBreakMode:NSLineBreakByWordWrapping];
    
    //trainDateLabel.frame = CGRectMake(12, 40, UI_IOS_WINDOW_WIDTH-24, 10);
    
    //addressLabel.text = [NSString stringWithFormat:@"地点: %@",[NSString stringWithUTF8String:trainlistItem.sTrainTime.c_str()]];
    //addressLabel.frame = CGRectMake(170, 60, UI_IOS_WINDOW_WIDTH-24, 10);
    
    //
    //    self.desLineLabel.text = [NSString stringWithUTF8String:trainlistItem.sTitle.c_str()];
    
    
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
