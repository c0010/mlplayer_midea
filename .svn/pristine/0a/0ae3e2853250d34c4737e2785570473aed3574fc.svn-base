//
//  CMTableViewCell.h
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "stdafx.h"
#include "cmqalist.h"
#include "cmwebimage.h"
#import "SDWebImage/SDWebImageManager.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "SDWebImage/SDImageCache.h"
#import "CMLabel.h"

@interface CMQuestionTableViewCell : UITableViewCell  {
	UIImageView *LeftImageView;//图像
	UIImageView *valueImageView; //悬赏图像
    UIImageView *userImageView; //默认用户头像
    UIImageView *questionImageView; //问题logo
    UIButton *showImageView; //用户分享图片
	CMLabel* lbquestion; //问题
	UILabel* lbpv;//关注数
	UILabel* lbanswercount;//回答次数                    //在此处加一个UILabel  问题分类
	UILabel* lbvalue;//悬赏积分	
	UILabel* lbpubdate;//提问时间
	UILabel* lbname;//名字
    UILabel* lbsolve;//是否已解决
    CMLabel* lbqcategory;                                //问题分类
    BOOL hideimage;//用户头像hide，判断是否进入问题详情
    BOOL isUserSelf;//是否用户本身
    NSUInteger pv_length;
    NSUInteger answer_length;
    
    UIImage *shareImage;
    NSString *imgpath;
    double img_width;
    double img_height;
    
}
@property (nonatomic,strong) UIImage     * shareImage;
@property (nonatomic,strong) UIButton    * showImageView;
@property (nonatomic,strong) UIImageView * questionImageView;
@property (nonatomic,strong) UIImageView * LeftImageView;
@property (nonatomic,strong) UIImageView * valueImageView;
@property (nonatomic,strong) UIImageView * userImageView;
@property (nonatomic,strong) CMLabel     * lbquestion;
@property (nonatomic,strong) UILabel     * lbpv;
@property (nonatomic,strong) UILabel     * lbanswercount;
@property (nonatomic,strong) UILabel     * lbvalue;
@property (nonatomic,strong) UILabel     * lbpubdate;
@property (nonatomic,strong) UILabel     * lbname;
@property (nonatomic,strong) UILabel     * lbsolve;
@property (nonatomic,strong) CMLabel     * lbqcategory;
@property (nonatomic,assign) BOOL          hideimage;
@property (nonatomic,assign) BOOL          isUserSelf;
@property(nonatomic, strong) UIImageView *separatorLine;

-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size;
-(void)setcellinfo:(TQAItem&)qaItem webimage:(CMWebImage*)pWebImage shareimage:(CMWebImage*)pShareImage index:(NSInteger)index;
+(CGFloat)GetCellHeight:(TQAItem&)qaItem webimage:(CMWebImage*)pWebImage shareimage:(CMWebImage *)shareImage width:(int)width hideimage:(BOOL)hideimage;
@end
