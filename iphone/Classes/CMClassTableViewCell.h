//
//  CMTableViewCell.h
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdafx.h"
#include "cmbrowser.h"
#include "cmwebimage.h"
#import "CMLabel.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "SDWebImage/SDWebImageDownloader.h"
#import "SDWebImage/SDImageCache.h"

@interface CMClassTableViewCell : UITableViewCell<SDWebImageManagerDelegate>  {
	CMLabel *lbltitle;//课程名称
    UIButton *titleView; //课程title 背景
    
    CMLabel *lbsubtitle; //课程详情
    UIButton *subtitleView; //课程描述 背景
    UIImageView *blankImageView;   //是否有同系列时分割线
    
    UIButton *seriesView; //同系列相关
    CMLabel *lbseries; //同系列数
    
    UIImageView *pointImageView; //系列右边指示图标
	//学分、章节数
	UIImageView *LeftImageView;//课程图标（打上播放时长的水印）
	UIImageView *viewImageView;
	UIImageView *likeImageView;
	
	UILabel* lblplay;//播放次数
	UILabel* lbllike;//评论数	
	
	UILabel* lbltime;//发布时间
	UIImageView* Specialtopic;//专题
    
    UIImageView *showImageView; //课件展示图片
    
    UIButton *btnproject; //专题标签
    UIButton *btnplay; //播放显示
	
	//课程图标（打上播放时长的水印）、课程名称、发布时间、学分、章节数（如果有章节则显示章节数）、
	//评价（顶的人数）、播放次数、评论数。课程类别,课程简介,标签（关键字）
}
@property(nonatomic,retain)UIButton *subtitleView;
@property(nonatomic,retain)UIButton *btnplay;
@property(nonatomic,retain)UIButton *titleView;
@property(nonatomic,retain)UIButton *btnproject;
@property(nonatomic,retain)UIButton *seriesView;
@property(nonatomic,retain)CMLabel *lbseries;
@property(nonatomic,retain)UIImageView *pointImageView;
@property(nonatomic,retain)CMLabel *lbsubtitle;
@property(nonatomic,retain)UIImageView *showImageView;
@property(nonatomic,retain)UIImageView *blankImageView;
@property(nonatomic,retain)CMLabel *lbltitle;
@property(nonatomic,retain)UIImageView *viewImageView;
@property(nonatomic,retain)UIImageView *likeImageView;
@property(nonatomic,retain)UIImageView *LeftImageView;
@property(nonatomic,retain)UILabel* lblplay;
@property(nonatomic,retain)UILabel* lbllike;
@property(nonatomic,retain)UILabel* lbltime;
@property(nonatomic,retain)UIImageView *Specialtopic;
@property(nonatomic,assign)BOOL isShowMark;
@property(nonatomic,retain)UIImageView *separatorLine;

-(void)setcellinfo:(TBrowserItem&)browserItem webimage:(CMWebImage*)pWebImage;

+(CGFloat)GetCellHeight:(TBrowserItem&)browserItem webimage:(CMWebImage*)pWebImage width:(int)width;

@end
