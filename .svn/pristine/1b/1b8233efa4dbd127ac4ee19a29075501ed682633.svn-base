//
//  CMInteractCell.h
//  MLPlayer
//
//  Created by water on 14-7-18.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMInteractModel.h"
#import "cmsettings.h"
#import "CMButton.h"
#import "CMLabel.h"

#define CMInteractCellHeight 65
#define CMInteractCell_Title_Y 12

@interface CMInteractCell : UITableViewCell

@property(nonatomic,strong) CMButton *headButton;
@property(nonatomic,strong) UILabel *titleLabel,*timeLabel,*phoneLabel;
@property(nonatomic,strong) UIButton *badgeView;
@property(nonatomic,strong) CMLabel *DescLabel;
@property(nonatomic,strong) UIImageView *draftImgView;
@property(nonatomic,assign) NSInteger badgeValue;

- (void)bindDialogueItem:(CMDialogueItem *)item;
- (void) setSingleCell;
- (void) setDoubleCell;
@end
