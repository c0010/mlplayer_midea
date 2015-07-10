//
//  CMLearnRecordCell.h
//  MLPlayer
//
//  Created by hushengwu on 13-9-25.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "cmbrowser.h"

//学习纪录Cell
@interface CMLearnRecordCell : UITableViewCell{
    UILabel *_lbltitle; //标题
    UILabel *_lbltime;  //时间
  //  UIImageView *_typeImageView;
    BOOL isShowTimeItem;   //是否显示时间节点
}
@property (nonatomic, strong) UILabel *lbltitle;
@property (nonatomic, strong) UILabel *lbltime;
//@property (nonatomic, strong) UIImageView *typeImageView;
@property (nonatomic, strong) UIImageView *popBackgroundView;
@property (nonatomic, strong) UIView *titleView;
@property (nonatomic, strong) UIImageView *leftLineImageView;

+(CGFloat)GetCellHeight:(TBrowserItem&)browserItem  width:(int)width withPreString:(NSString*)pretimestr;
-(void)setcellinfo:(TBrowserItem&)browserItem perTimeString:(NSString*)pertimestr;

@end
