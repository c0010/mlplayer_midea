//
//  CMSysMessageCell.h
//  MLPlayer
//
//  Created by water on 14-6-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMLabel.h"
#import "CMInteractModel.h"

#define SINGLE_HEIGHT 50
#define DOUBLE_HEIGHT 60

#define Single_Cell_titleHight 280

#define MidFrameY(h,view) (h - CGRectGetHeight(view.frame))/2

#define UP 10


@protocol CMSysMessageCellDelegate;

enum CMSysMessageCellType{
    CMSysMessageCellSingleType = 0,//单行不可交互
    CMSysMessageCellDoubleType = 1,//双行不可交互
    CMSysMessageCellSingleTypeEdit = 2,//单行可交互
    CMSysMessageCellDoubleTypeEdit = 3//双行可交互
};

@interface CMSysMessageCell : UITableViewCell
{
    NSObject<CMSysMessageCellDelegate> *cellDelegate;
}
@property(nonatomic,strong) CMLabel* titleLabel;
@property(nonatomic,strong) CMLabel* middleLabel;
@property(nonatomic,strong) UILabel* descrLabel;
@property(nonatomic,strong) UIButton* agreeButton;
@property(nonatomic,strong) UILabel* agreeLabel;

@property (nonatomic, strong) NSObject<CMSysMessageCellDelegate> *cellDelegate;
@property (nonatomic, assign) enum CMSysMessageCellType cellType;

- (IBAction)agreeButtonPressed:(UIButton *)sender;
- (void)setItem:(CMMessageItem *)item;
- (void)setSubViewsFrame:(NSString *)content;
- (CGFloat)getCellHeight:(CMMessageItem *)item;
@end

@protocol CMSysMessageCellDelegate <NSObject>

@optional
- (void)CMSysMessageCell:(CMSysMessageCell *)sysMessageCell didSelectedAtIndex:(NSInteger)row;

@end