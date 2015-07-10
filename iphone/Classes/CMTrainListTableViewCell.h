//
//  CMTrainListTableViewCell.h
//  MLPlayer
//
//  Created by 张永兵 on 14-12-19.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmmytrainlist.h"

@interface CMTrainListTableViewCell : UITableViewCell
{
    UILabel *titleLabel;
    
    UILabel *trainDateLabel;
    
    UILabel *addressLabel;
    
    UIButton *stateBtn;
    
    UIImageView *separatorLine;
    
    UIImageView *iconImage;

}

-(void)setcellinfo:(TMyTrainItem &)trainlistItem;

@end
