//
//  CMDownLoadTableViewCell.h
//  MLPlayer
//
//  Created by sunjj on 11-12-14.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "tool.h"
@interface CMDownLoadTableViewCell : UITableViewCell {
	UIImageView *LeftImageView;
	UILabel *lbltitle;
	UILabel* lblvalue;//下载完
	UIButton* btnstatus;
	UIImageView * tagImg;
    UIView *selView; //分割线
    UIView *selViewTop; //分割线阴影
}
@property (nonatomic,strong) UIView *selViewTop;
@property (nonatomic,strong) UIImageView *LeftImageView;
@property (nonatomic,strong) UILabel *lbltitle;

@property (nonatomic,strong) UILabel* lblvalue;//下载完成百分比
@property (nonatomic,strong) UIButton* btnstatus;
@property (nonatomic,strong) UIImageView * tagImg;
@property (nonatomic,strong) UIView *selView;
+(CGFloat)GetCellHeight:(NSString *)title  width:(int)width;

@end
