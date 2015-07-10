//
//  CMTableViewCell.m
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMQuestionTableViewCell.h"
#import "CMImage.h"
#import "tool.h"
#include "cmwebimage.h"
#define SPINNER_HEIGHT 5.0   //布局间隙
#define SPACING_HEIGHT 55.0
#define SHARE_IMAGE_WIDTH 220.0
#define SHARE_IMAGE_HEIGHT 75.0

@implementation CMQuestionTableViewCell
@synthesize valueImageView,LeftImageView,lbquestion,lbpv,lbanswercount,lbvalue,lbpubdate,lbname,hideimage,lbqcategory;
@synthesize userImageView,questionImageView,showImageView,isUserSelf;
@synthesize lbsolve;
@synthesize shareImage;
@synthesize separatorLine;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier             //在该函数中，将UILabel添加到cell
{
		if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier])
		{
			self.backgroundColor = [UIColor clearColor];
            
			LeftImageView = [[UIImageView alloc]init];
			LeftImageView.clipsToBounds = YES;
			[LeftImageView setBackgroundColor:[UIColor clearColor]];
            
            questionImageView = [[UIImageView alloc]init];
			questionImageView.clipsToBounds = YES;
			[questionImageView setBackgroundColor:[UIColor clearColor]];
            
            
			valueImageView = [[UIImageView alloc]init];
			valueImageView.image = [UIImage imageNamed:@"gold"];
			
            userImageView = [[UIImageView alloc]init];
            userImageView.image = [UIImage imageNamed:@"user_image"];
            
            showImageView = [[UIButton alloc]initWithFrame:CGRectZero];
            showImageView.backgroundColor = [UIColor clearColor];
            
			lbquestion = [[CMLabel alloc]init];
			lbquestion.textAlignment = UITextAlignmentLeft;
			lbquestion.font = [UIFont systemFontOfSize:kTextSizeMid];
			lbquestion.textColor = kTextColorDark;
			lbquestion.numberOfLines = 0;
            lbquestion.lineBreakMode=UILineBreakModeWordWrap;
			[lbquestion setBackgroundColor:[UIColor clearColor]];

			lbpv = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];
			lbpv.textAlignment = UITextAlignmentCenter;
            
			lbanswercount = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];
            lbanswercount.textAlignment = UITextAlignmentCenter;

			lbvalue = [self GetLabel:@"" textcolor:UIColorRGB(0x8d8d8d) fontsize:15];
			
			lbpubdate = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];
            lbpubdate.textAlignment = UITextAlignmentRight;
			
			lbname = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13];
            lbsolve = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13.0];
            
           // lbqcategory=[[self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:13] retain];     //新增，问题类别label
            lbqcategory=[[CMLabel alloc]init];

            self.separatorLine = [[UIImageView alloc] init];
            self.separatorLine.contentMode = UIViewContentModeScaleAspectFit;
            [self.separatorLine setImage:[UIImage imageNamed:@"learn_cell_sep"]];
            
			[self.contentView addSubview:valueImageView];
			[self.contentView addSubview:LeftImageView];
            [self.contentView addSubview:userImageView];
            [self.contentView addSubview:questionImageView];
            [self.contentView addSubview:showImageView];
     

			[self.contentView addSubview:lbquestion];
			[self.contentView addSubview:lbpv];
			[self.contentView addSubview:lbanswercount];
			[self.contentView addSubview:lbvalue];
			[self.contentView addSubview:lbpubdate];
			[self.contentView addSubview:lbname];
            [self.contentView addSubview:lbsolve];
            
            [self.contentView addSubview:lbqcategory];           //新增，问题类别label
            [self.contentView addSubview:separatorLine];
            
			[self setSelectionStyle:UITableViewCellSelectionStyleGray];
			self.accessoryType = UITableViewCellAccessoryNone;
		}
	return self;
}

-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size
{

    UILabel* lb = [[UILabel alloc] init];
	lb.backgroundColor = [UIColor clearColor];
	lb.textAlignment = UITextAlignmentLeft;
	lb.font = [UIFont systemFontOfSize:size];
	lb.textColor = textcolor;
	lb.text = title;
	return lb;
}
- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
	 [super setSelected:selected animated:animated];
}

-(void)layoutSubviews                    //在该函数中调整UILabel的位置
{
	[super layoutSubviews];
	//CGRect contentRect = self.bounds;
	CGFloat boundsX = 5.0;
	CGFloat boundsY = 5.0;
	CGFloat X = 0;
	
    if(!hideimage)
	{
        LeftImageView.frame = CGRectMake(boundsX, boundsY, 40 , 40);
        
		X = LeftImageView.frame.size.width;
		boundsX = boundsX + X + 5;
	}
    else{
        questionImageView.frame = CGRectMake(2 * boundsX, boundsY, 17.0, 17.0);
        boundsX = CGRectGetMaxX(questionImageView.frame) + 2 *SPINNER_HEIGHT;
    }
	lbname.frame = CGRectMake(boundsX, boundsY, 3 *SPACING_HEIGHT, 20);
    
    
    lbqcategory.frame=CGRectMake(boundsX, boundsY+23, 3 *SPACING_HEIGHT, 14);
	
	lbpubdate.frame = CGRectMake(boundsX+154, boundsY, SPACING_HEIGHT + 50.0, 20);
    [lbpubdate setTextAlignment:NSTextAlignmentRight];
	
	if (hideimage) {
       // lbsolve.hidden = YES;
    }
    else{
       boundsY += 25;
    }

	//问题
    if (!hideimage) {
        X = 260;
    }
    else{
        X = 280;
    }
	CGSize size = CGSizeMake(X,MAXFLOAT);
    
    
	CGSize labelsize = [lbquestion.text sizeWithFont:lbquestion.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
	
	[lbquestion setFrame:CGRectMake(boundsX, boundsY+15, labelsize.width, labelsize.height)];

  
    img_width = self.showImageView.imageView.image.size.width;
    img_height = self.showImageView.imageView.image.size.height;
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
 
    showImageView.frame = CGRectMake(CGRectGetMinX(lbquestion.frame), boundsY+15+labelsize.height, img_width, img_height);
    boundsY += img_height;
    
    CGSize n_Size = CGSizeMake(SPACING_HEIGHT + 20, 10.0);
    CGSize lbpv_Size = [lbpv.text sizeWithFont:[UIFont systemFontOfSize:13.0] constrainedToSize:n_Size lineBreakMode:UILineBreakModeWordWrap];
    lbpv.frame = CGRectMake(boundsX, boundsY+2*SPINNER_HEIGHT+labelsize.height+10, lbpv_Size.width, 20);
    
    CGSize lbanswer_Size = [lbanswercount.text sizeWithFont:[UIFont systemFontOfSize:13.0] constrainedToSize:n_Size lineBreakMode:UILineBreakModeWordWrap];
    lbanswercount.frame = CGRectMake(CGRectGetMaxX(lbpv.frame) + 7.0, boundsY+2*SPINNER_HEIGHT+labelsize.height+10, lbanswer_Size.width, 20);
    
    lbsolve.frame = CGRectMake(CGRectGetMaxX(lbanswercount.frame) + 5.0, CGRectGetMinY(lbanswercount.frame), SPACING_HEIGHT, 20.0);

    //问答详情隐藏分割线
    self.separatorLine.frame = CGRectMake(0, CGRectGetMaxY(lbanswercount.frame) - 1, UI_IOS_WINDOW_WIDTH, 1);
    self.separatorLine.hidden = NO;
    
	if(hideimage)//二级目录的显示
	{
        self.separatorLine.hidden = YES;
        userImageView.frame = CGRectMake(CGRectGetMinX(questionImageView.frame) + 2.0, boundsY + 2 * SPINNER_HEIGHT + 2.0 + labelsize.height + 5, 14.0, 14.0);

		CGRect rc;
    //    double myself_X;    //用户本身，和非本身，关注，回答的frame位置变化
        userImageView.hidden = YES;
        lbname.hidden = YES;
        lbqcategory.hidden=YES;    //新加
        CGSize size = CGSizeMake(SPACING_HEIGHT + 20, 10.0);
        
		rc = lbpv.frame;
		rc.origin.y = userImageView.frame.origin.y;
        rc.origin.x = CGRectGetMaxX(userImageView.frame) + 7.0;
        CGSize labelSize_pv=[lbpv.text sizeWithFont:[UIFont systemFontOfSize:13.0] constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
        rc.size.width = labelSize_pv.width;
		lbpv.frame = rc;
		
		rc = lbanswercount.frame;
		rc.origin.y = lbpv.frame.origin.y;
        rc.origin.x = CGRectGetMaxX(lbpv.frame) + 7.0;
        CGSize labelSize_answer=[lbanswercount.text sizeWithFont:[UIFont systemFontOfSize:13.0] constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
        rc.size.width = labelSize_answer.width;
		lbanswercount.frame = rc;
        
        rc = lbpubdate.frame;
		rc.origin.y = lbpv.frame.origin.y;
        rc.origin.x = CGRectGetMaxX(lbanswercount.frame) + 7.0;
		lbpubdate.frame = rc;
        [lbpubdate setTextAlignment:NSTextAlignmentLeft];
	}
    if([lbvalue.text intValue] > 0)
	{
		valueImageView.frame = CGRectMake(278.0, CGRectGetMinY(lbanswercount.frame) + SPINNER_HEIGHT, valueImageView.image.size.width, valueImageView.image.size.height);
		lbvalue.frame =  CGRectMake(CGRectGetMaxX(valueImageView.frame) + 2.0, CGRectGetMinY(lbanswercount.frame)+ SPINNER_HEIGHT, 30.0, valueImageView.image.size.height + 1.0);
        
	}
    
}

- (CGSize)getCGSizeWithLabel:(UILabel *)label{
    CGSize size = CGSizeMake(60.0, 25.0);
	CGSize labelsize = [lbquestion.text sizeWithFont:lbquestion.font constrainedToSize:size lineBreakMode:UILineBreakModeCharacterWrap];
    return labelsize;
}

-(void)setcellinfo:(TQAItem&)qaItem webimage:(CMWebImage*)pWebImage shareimage:(CMWebImage*)pShareImage index:(NSInteger)index
{
	CGRect cellFrame = self.frame;
	if(!hideimage)
	{
		if(pWebImage->GetFromUrl(0,qaItem.sQuestioner_icon.c_str()))
		{	
			UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:pWebImage->GetFilePath(qaItem.sQuestioner_icon.c_str())]];// m_image;
			self.LeftImageView.image = loadImage;
		}
		else
		{
			UIImage* lImage = [UIImage imageNamed:@"head.png"];
			self.LeftImageView.image = lImage;
		}
	}
    
    NSString *sep_str1 = @"";
    NSString *sep_str2 = @"|  ";
    NSString *sep_str3 = @"";

    if (hideimage) {
        sep_str3 = [NSString stringWithFormat:@"|  "];
    }
    else{
        sep_str3 = [NSString stringWithFormat:@""];
    }
    
    self.lbname.text = [NSString stringWithUTF8String:qaItem.sQuestioner_fullname.c_str()];

    //self.lbqcategory.text=[NSString stringWithUTF8String:qaItem.GetQAItemCategoryTitle()];       //新增
    NSString* sqcategory=[NSString stringWithUTF8String:qaItem.sQcategorytitle.c_str()];
    [self.lbqcategory setText:sqcategory WithFont:[UIFont systemFontOfSize:kTextSizeSmlLess] AndColor:UIColorRGB(0X1b6fb3)];
    
	NSString* squestion = [NSString stringWithUTF8String:qaItem.sQuestion.c_str()];

    [self.lbquestion setText:squestion WithFont:[UIFont systemFontOfSize:kTextSizeMid] AndColor:UIColorRGB(0X333333)];
    
        
    UIImage *loadImage = nil;
    UIImage *placeholderImg = [UIImage imageNamed:@"placeholder_loading"];
    NSString *url = [NSString stringWithUTF8String:qaItem.sThumburl.c_str()];
    if(qaItem.sThumburl.c_str() && qaItem.sThumburl.c_str() != '\0' && ![url isEqualToString:@""])
    {
        SDWebImageManager *manager = [SDWebImageManager sharedManager];
        UIImage *cachedImage =[[SDImageCache sharedImageCache] imageFromMemoryCacheForKey:url];// 将需要缓存的图片加载进来
        if (cachedImage) {
            // 如果Cache命中，则直接利用缓存的图片进行有关操作
            img_width = cachedImage.size.width;
            img_height = cachedImage.size.height;
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
            
            [self.showImageView setImage:cachedImage forState:UIControlStateNormal];
            
        } else {
            // 如果Cache没有命中，则去下载指定网络位置的图片，并且给出一个委托方法
            // Start an async download
            manager.imageDownloader.executionOrder = SDWebImageDownloaderLIFOExecutionOrder;

            __weak CMQuestionTableViewCell* blockSelf = self;
            [manager downloadImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:qaItem.sThumburl.c_str()]] options:0 progress:nil completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, BOOL finished, NSURL *imageURL) {
                
                if (!blockSelf || ![blockSelf isKindOfClass:[CMQuestionTableViewCell class]]) return ;
                NSDictionary *dic = [[NSDictionary alloc]initWithObjectsAndKeys:[NSString stringWithFormat:@"%ld",index],@"index", nil];
                dispatch_main_sync_safe(^{
                    
                    if (image) {
                        [blockSelf.showImageView setImage:image forState:UIControlStateNormal];
                        [[NSNotificationCenter defaultCenter] postNotificationName:@"reloadTableview" object:nil userInfo:dic];

                    }
                });
            }];
            [self.showImageView setImage:placeholderImg forState:UIControlStateNormal];
        }
        loadImage = showImageView.imageView.image;
        img_height = placeholderImg.size.height;
        if (loadImage.size.width > SHARE_IMAGE_WIDTH || loadImage.size.height > SHARE_IMAGE_HEIGHT) {
            img_height = SHARE_IMAGE_HEIGHT;
        }
    }
    else
    {
        self.showImageView.frame = CGRectZero;
    }
	self.lbpv.text =[NSString stringWithFormat:@"%@%@ %d",sep_str1,I(@"关注"), qaItem.nPV];
	self.lbanswercount.text = [NSString stringWithFormat:@"%@%@ %d",sep_str2,I(@"回答"),qaItem.nAnswercount];
	self.lbvalue.text = [NSString stringWithFormat:@"%d",qaItem.nValue];
    
    
	self.lbpubdate.text=[NSString stringWithFormat:@"%@%@",sep_str3,[NSString stringWithUTF8String:qaItem.sPubdate.c_str()]];
    
    ///////////////////////////////////////////////////
    pv_length = qaItem.nPV;
    answer_length = qaItem.nValue;
    
    self.lbsolve.text = [NSString stringWithFormat:@"|  已解决"];
    if (hideimage) {
        lbsolve.hidden = YES;
    }
    else{
        if (qaItem.bIsresolved) {
            lbsolve.hidden = NO;
        }
        else{
            lbsolve.hidden = YES;
        }
    }
	
	[self setFrame:cellFrame];
	self.accessoryType = UITableViewCellAccessoryNone;	
}



+(CGFloat)GetCellHeight:(TQAItem&)qaItem webimage:(CMWebImage*)pWebImage shareimage:(CMWebImage *)shareImage width:(int)width hideimage:(BOOL)hideimage;
{
	CGFloat hg = 0 ;
	CGFloat wd = 0 ;
	CGFloat blank = 5;
    UIImage *img = nil;
    
    CGFloat X = 0;

    double img_height = img.size.height;

    NSString *url = [NSString stringWithUTF8String:qaItem.sThumburl.c_str()];
    if(qaItem.sThumburl.c_str() && qaItem.sThumburl.c_str() != '\0' && ![url isEqualToString:@""])
    {
        img_height = SHARE_IMAGE_HEIGHT;
    }

	if(!hideimage)
	{
        hg = 40;
        wd = 40;
        X = 260;
	}
    else{
        X = 280;
    }
	blank += 5;
	NSString* squestion = [NSString stringWithUTF8String:qaItem.sQuestion.c_str()];
	NSString *cellText = [NSString stringWithFormat:@"%@",squestion];
	
	//字体高度
	UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
	CGSize constraintSize = CGSizeMake(X, MAXFLOAT);

    CGSize labelSize=[cellText sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];


    if (!hideimage) {
        return labelSize.height>50?labelSize.height+70 + img_height:labelSize.height+70+ img_height;
    }
	return labelSize.height>50?labelSize.height+80+ img_height:labelSize.height+80+ img_height;
    
}

- (void)dealloc {
    CMRELEASE(questionImageView);
    CMRELEASE(showImageView);
    CMRELEASE(valueImageView);
    CMRELEASE(LeftImageView);
    CMRELEASE(userImageView);
    CMRELEASE(lbquestion);
    CMRELEASE(lbpv);
    CMRELEASE(lbanswercount);
    CMRELEASE(lbvalue);
    CMRELEASE(lbpubdate);
    CMRELEASE(lbname);
    CMRELEASE(separatorLine);

}


@end
