//
//  CMClassInfoCell.h
//  MLPlayer
//
//  Created by sunjj on 13-4-10.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmcomment.h"
@interface CMClassInfoCell : UITableViewCell
{
    UILabel *_className;
    UILabel *_isLearned;
    UIImageView *_typeImage;
    
    
}


@property(nonatomic,strong) IBOutlet UILabel *className;
@property(nonatomic,strong) IBOutlet UILabel *isLearned;
@property(nonatomic,strong)  IBOutlet  UIImageView *typeImage;

-(void)setcellinfo:(TCoursewareItem&)citem;

@end
