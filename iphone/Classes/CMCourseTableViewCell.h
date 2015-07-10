//
//  CMCourseTableViewCell.h
//  MLPlayer
//
//  Created by sunjj on 11-9-21.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdafx.h"
#include "cmwebimage.h"

@interface CMCourseTableViewCell : UITableViewCell  {
	UILabel *lblauthor;
	UILabel *lbldesc;
	UIImageView *LeftImageView;
	UILabel* lbltime;
}

@property(nonatomic,strong)UILabel *lblauthor;
@property(nonatomic,strong)UILabel *lbldesc;
@property(nonatomic,strong)UILabel* lbltime;
@property(nonatomic,strong)UIImageView *LeftImageView;
+(CGFloat)GetCellHeight:(const char*)sMsg url:(const char*)sUrl webimage:(CMWebImage*)pWebImage width:(int)width;
-(void)setcellinfo:(const char*)sUrl webimage:(CMWebImage*)pWebImage;
@end
