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
#include "cmcomment.h"


#define kBtnLikeTag  8
#define kBtnCommentTag 9
#define kLblPvTag 10

@interface CMCommentTableViewCell : UITableViewCell  {
	UIImageView *LeftImageView;
	UILabel *lblauthor;
	UILabel *lblcomment;
	UIImageView* imgpv;
	UILabel *lblpv;
	UIImageView* imgreplycount;
	UILabel *lblreplycount;
	UILabel* lbltime;
	UIView*  lblsepview;
    
    UIButton *btnLike;
    
    UIButton *btnComment;
    
    UIImageView *replyBriefView;
    
    UIImageView* sep;
    
}

@property(nonatomic,strong)UIImageView* sep;
@property(nonatomic,strong)    UIImageView *replyBriefView;

@property(nonatomic,strong)UIButton *btnLike;
@property(nonatomic,strong)UIButton *btnComment;


@property(nonatomic,strong)UIImageView *LeftImageView;
@property(nonatomic,strong)UILabel *lblauthor;
@property(nonatomic,strong)UILabel *lblcomment;
@property(nonatomic,strong)UIImageView* imgpv;
@property(nonatomic,strong)UILabel* lblpv;
@property(nonatomic,strong)UIImageView* imgreplycount;
@property(nonatomic,strong)UILabel *lblreplycount;
@property(nonatomic,strong)UILabel* lbltime;
@property(nonatomic,strong)UIView* lblsepview;
+(CGFloat)GetCellHeight:(TCommentItem&)item webimage:(CMWebImage*)pWebImage width:(int)width;
-(void)setcellinfo:(TCommentItem&)item webimage:(CMWebImage*)pWebImage;
@end
