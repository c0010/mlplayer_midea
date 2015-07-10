//
//  CMTableViewCell.h
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


#define kBtnSetBestTag  8

//#define kBtnLikeTag 9


@interface CMAnswerTableViewCell : UITableViewCell  {
	UIImageView *LeftImageView;//图像

	UILabel *lbanswer; //回答
	UILabel* lbpubdate;//提问时间

	UILabel* lbname;
	UILabel* lblike;
	
	UIImageView* sepImageView;
	UIImageView* likeImageView;
    UIView *separetor;
    UIView *separetor2;
    
    UIButton *showImageView; //用户分享图片

	int  sepstatus; //0 没有 1 btnlike高亮 2 btnlike正常
    
    UIButton *btnLike;
    UIButton *btnSetBest;
    
    UIView *bg;
    
    UIImage *shareImage;
    NSString *imgpath;
    double img_width;
    double img_height;
}
@property(nonatomic,strong)UIButton *btnLike;
@property(nonatomic,strong)UIButton *btnSetBest;
@property(nonatomic,strong)UIButton *showImageView;
@property(nonatomic,strong)UIView *separetor2;
@property(nonatomic,strong)UIView *separetor;
@property(nonatomic,strong)UIView *bg;

@property(nonatomic,strong)UIImageView *LeftImageView;
@property(nonatomic,strong)UILabel* lbanswer;
@property(nonatomic,strong)UILabel* lbpubdate;
@property(nonatomic,strong)UILabel* lbname;
@property(nonatomic,strong)UILabel* lblike;
@property(nonatomic,strong)UIImageView* sepImageView;
@property(nonatomic,strong)UIImageView* likeImageView;
@property(nonatomic,assign)int sepstatus;
-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size;
- (void)setBtnLikeHighlighted:(BOOL)hight;
@end
