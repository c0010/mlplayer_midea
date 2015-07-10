//
//  CMTableViewCell.m
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMAnswerTableViewCell.h"
#import "tool.h"
#define SHARE_IMAGE_WIDTH 220.0
#define SHARE_IMAGE_HEIGHT 75.0

@implementation CMAnswerTableViewCell
@synthesize LeftImageView,lbanswer,lbpubdate,lbname,lblike,likeImageView, sepImageView,sepstatus,btnLike,btnSetBest;
@synthesize bg,showImageView,separetor,separetor2;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
		if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier])
		{
            self.backgroundColor = [UIColor clearColor];
            

            bg = [[UIView alloc]initWithFrame:CGRectMake(10.0, 0.0, 300.0, self.contentView.frame.size.height)];
            bg.backgroundColor = [UIColor whiteColor];
            [self.contentView addSubview:bg];
            
            //喜欢按钮
            btnLike=[[UIButton alloc]init];
            [btnLike setBounds:CGRectMake(0, 0, 55, 23)];
            [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_nor"] forState:UIControlStateNormal];
            [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateHighlighted];
            
            [btnLike setImage:[UIImage imageNamed:@"like_nor"] forState:UIControlStateNormal];
            [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateHighlighted];
            
           // [btnLike setTag:kBtnLikeTag];
            btnLike.imageEdgeInsets=UIEdgeInsetsMake(0, -25, 0, 0);
            
            
            //设为最佳按钮
            
            btnSetBest=[[UIButton alloc]init];
            [btnSetBest setBounds:CGRectMake(0, 0, 55, 23)];
            [btnSetBest setBackgroundImage:[UIImage imageNamed:@"setBestAnswer_nor"] forState:UIControlStateNormal];
            [btnSetBest setBackgroundImage:[UIImage imageNamed:@"setBestAnswer_sel"] forState:UIControlStateHighlighted];
            
           // [btnSetBest setTag:kBtnSetBestTag];
            [btnSetBest setImage:[UIImage imageNamed:@"bestAnswer_icon"] forState:UIControlStateNormal];
            [btnSetBest setTitle:I(@"设为最佳答案") forState:UIControlStateNormal];
            
                  [btnSetBest setTitle:I(@"设为最佳答案") forState:UIControlStateHighlighted];
         
            [btnSetBest.titleLabel setFont:[UIFont systemFontOfSize:13]];
            [btnSetBest setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
            btnSetBest.titleEdgeInsets=UIEdgeInsetsMake(0, 0, 0, 0);
            btnSetBest.imageEdgeInsets=UIEdgeInsetsMake(0, 0, 0, 0);

			
			self.contentView.backgroundColor = [UIColor whiteColor];
			LeftImageView = [[UIImageView alloc]init];
			LeftImageView.clipsToBounds = YES;
			LeftImageView.contentMode = UIViewContentModeScaleAspectFit;
			[LeftImageView setBackgroundColor:[UIColor clearColor]];
			
			lbanswer = [[UILabel alloc]init];
			lbanswer.textAlignment = UITextAlignmentLeft;
			lbanswer.font = [UIFont systemFontOfSize:kTextSizeMid];
			lbanswer.textColor = kTextColorDark;
			lbanswer.numberOfLines = 0; 
			[lbanswer setBackgroundColor:[UIColor clearColor]];

			
			sepImageView = [[UIImageView alloc]init];
			likeImageView = [[UIImageView alloc]init];
			likeImageView.image = [UIImage imageNamed:@"Like"];
            
            showImageView = [[UIButton alloc]init];
            showImageView.backgroundColor = [UIColor clearColor];
            			
			lbname = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];

			//lblike = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];
            lblike = [self GetLabel:@"" textcolor:[UIColor grayColor] fontsize:13];

			lbpubdate = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];
            
            separetor2 = [[UIView alloc]init];
            separetor2.backgroundColor = UIColorRGB(0xe7e7e7);
            
            separetor = [[UIView alloc]init];
            separetor.backgroundColor = UIColorRGB(0xa7a7a7);

            [bg addSubview:btnLike];
            [bg addSubview:btnSetBest];
			[bg addSubview:sepImageView];
			[bg addSubview:LeftImageView];
			[bg addSubview:likeImageView];
			[bg addSubview:lbanswer];
			[bg addSubview:lbpubdate];
			[bg addSubview:lbname];
			[bg addSubview:lblike];
            [bg addSubview:showImageView];
            [self.contentView addSubview:separetor2];
            [self addSubview:separetor];

            
		}
	return self;
}
-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size
{
#if !__has_feature(obj_arc)
	UILabel* lb = [[UILabel alloc] init];
#else
    UILabel* lb = [[UILabel alloc] init];
#endif
    
	lb.backgroundColor = [UIColor clearColor];
	lb.textAlignment = UITextAlignmentLeft;
	lb.font = [UIFont systemFontOfSize:size];
	lb.textColor = textcolor;
	lb.text = title;
	return lb;
}
- (void)setBtnLikeHighlighted:(BOOL)hight{
    if (hight) {
        btnLike.enabled = NO;
        [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateNormal];
        [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateNormal];

    }
    else{
        btnLike.enabled = YES;
        [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_nor"] forState:UIControlStateNormal];
        [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateHighlighted];

        [btnLike setImage:[UIImage imageNamed:@"like_nor"] forState:UIControlStateNormal];
        [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateHighlighted];

    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
	
	 [super setSelected:selected animated:animated];
}


-(void)layoutSubviews
{
	[super layoutSubviews];
	CGRect contentRect = self.bounds;
	CGFloat X = 0;
	CGFloat yoff = 5;
	CGFloat xoff = 5;
	
    CGSize size = CGSizeMake(280.0,MAXFLOAT);
	CGSize labelsize = [lbanswer.text sizeWithFont:lbanswer.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
	
	lbanswer.frame = CGRectMake(xoff + 5.0, yoff, labelsize.width, labelsize.height);
	
	yoff += labelsize.height;
	yoff += 7.0;
    
    img_width = showImageView.imageView.image.size.width;
    img_height = showImageView.imageView.image.size.height;
    if (img_width > SHARE_IMAGE_WIDTH || img_height > SHARE_IMAGE_HEIGHT) {
        
        double wide_per = img_width/SHARE_IMAGE_WIDTH;
        double height_per = img_height/SHARE_IMAGE_HEIGHT;
        if (wide_per >= height_per) {
            img_width = SHARE_IMAGE_WIDTH;
            img_height = img_height / wide_per;
        }
        else{
            img_height = SHARE_IMAGE_HEIGHT;
            img_width = img_width / height_per;
        }
    }
    if (img_height < SHARE_IMAGE_HEIGHT && img_height > 0) {
        img_height = SHARE_IMAGE_HEIGHT;
    }

    showImageView.frame = CGRectMake(CGRectGetMinX(lbanswer.frame), yoff, img_width, img_height);
    yoff += img_height + 5.0;
    
    
	UIImage* image = [UIImage imageNamed:@"user_image"];
	
	LeftImageView.frame = CGRectMake(xoff + 5.0, yoff + 3.0, 14.0, 14.0);
	
	xoff += image.size.width;
	xoff += 10.0;

	lbname.frame = CGRectMake(xoff,yoff, 50.0, 20);
    
    separetor.frame = CGRectMake(CGRectGetMaxX(lbname.frame) + 10.0, yoff + 6.0, 1.0, 9.0);
    separetor.alpha = 0.8;
    
	lbpubdate.frame = CGRectMake(CGRectGetMaxX(separetor.frame) + 7.0, yoff, 100, 20);
	//likeImageView.frame = CGRectMake(260, yoff, likeImageView.image.size.width, likeImageView.image.size.height);
	yoff += 20;
	
	X = contentRect.size.width-xoff;
	

    //23为按钮高度 55为按钮宽度
    [btnLike setFrame:CGRectMake(CGRectGetMaxX(lbpubdate.frame) + 30, yoff - 20.0, 55.0, 23.0)];
    lblike.frame = CGRectMake(CGRectGetMaxX(lbpubdate.frame) + 63.0, yoff - 20.0 + 3.0, 60, 16);

    [btnSetBest setFrame:CGRectMake(CGRectGetMinX(LeftImageView.frame), yoff + 5.0, 100, 23)];
    
    yoff += 23;
    yoff +=5;
    
	if(sepstatus == 1)
	{
		//sepImageView.image = [UIImage imageNamed:@"down_sep"];
		//sepImageView.frame = CGRectMake(xoff, yoff, contentRect.size.width-xoff, 2);
	}
	else if(sepstatus == 2)
	{
		//sepImageView.image = [UIImage imageNamed:@"examsep"];
		//sepImageView.frame = CGRectMake(xoff, yoff, contentRect.size.width-xoff, 2);
	}
    bg.frame = CGRectMake(10.0, 0.0, 300.0, CGRectGetHeight(self.contentView.frame));
    separetor2.frame = CGRectMake(10.0, CGRectGetMaxY(self.contentView.frame) - 1.0, 300.0, 1.0);

}


- (void)dealloc {
    CMRELEASE(separetor);
    CMRELEASE(separetor2);
    CMRELEASE(bg);
    CMRELEASE(btnSetBest);
    CMRELEASE(btnLike);
    CMRELEASE(LeftImageView);
    CMRELEASE(lbanswer);
    CMRELEASE(lbpubdate);
    CMRELEASE(likeImageView);
    CMRELEASE(sepImageView);
    CMRELEASE(lbname);
    CMRELEASE(showImageView);
    CMRELEASE(lblike);
    
#if !__has_feature(obj_arc)
#endif
}
@end
