//
//  CMTrainApplyTableViewCell.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmtrainapplylist.h"

@interface CMTrainApplyTableViewCell : UITableViewCell
{
    UILabel *titleLabel;
    
    UILabel *trainDateLabel;
    
    UILabel *addressLabel;
    
    UIButton *stateBtn;
    
    UIImageView *dateImageView;
    
    UIImageView *addressImageView;
    
    UIImageView *separatorLine;//分割线
    
}
-(void)setcellinfo:(TTrainApplyItem &)trainlistItem;
@end
