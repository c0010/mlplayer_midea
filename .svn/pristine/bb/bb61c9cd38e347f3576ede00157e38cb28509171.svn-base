//
//  CMNewsCell.h
//  MLPlayer
//
//  Created by sunjj on 13-7-29.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdafx.h"
#include "cmbrowser.h"
#import "CMLabel.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "SDWebImage/SDWebImageDownloader.h"
#import "SDWebImage/SDImageCache.h"

@interface CMNewsCell : UITableViewCell
{
    UIImageView * LeftImageView;
                
    CMLabel     * lbltitle;
    CMLabel     * contentLabel;
                
    UILabel     * viewCountLabel;
                
    UILabel     * lbltime;
}
@property (nonatomic,strong) IBOutlet UIImageView *LeftImageView;

@property (nonatomic,strong) IBOutlet CMLabel     * lbltitle;

@property (nonatomic,strong) IBOutlet CMLabel     * contentLabel;

@property (nonatomic,strong) IBOutlet UILabel     * viewCountLabel;

@property (nonatomic,strong) IBOutlet UILabel     * lbltime;

@property(nonatomic,strong) UIImageView *separatorLine;


-(void)setcellinfo:(TBrowserItem&)browserItem;

@end
