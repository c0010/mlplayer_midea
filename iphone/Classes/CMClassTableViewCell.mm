//
//  CMTableViewCell.m
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMClassTableViewCell.h"
#import "tool.h"
#import "CMImage.h"

#define SHOWIMAGEVIEW_WIDTH   290
#define SHOWIMAGEVIEW_HEIGHT  145
#define CELL_WIDTH            310 //假cell宽度
#define CELL_ADD_LABEL        290 //cell上label宽度
static const CGSize imageSize = {307, 300};
@implementation CMClassTableViewCell
@synthesize lbltitle,viewImageView,likeImageView, LeftImageView,lblplay,lbllike,lbltime,Specialtopic;
@synthesize seriesView,lbseries,lbsubtitle,pointImageView,showImageView,btnproject,titleView,btnplay,subtitleView;
@synthesize blankImageView;
@synthesize isShowMark;
@synthesize separatorLine;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
	if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        //cell backgroundColor
		//cell section title
        //title
		lbltitle = [[CMLabel alloc]init];
		lbltitle.textAlignment = UITextAlignmentLeft;
        [lbltitle setBackgroundColor:[UIColor clearColor]];
		lbltitle.font = [UIFont systemFontOfSize:17];
		lbltitle.textColor = UIColorRGB(0x333333);
        
        //project button
        btnproject = [[UIButton alloc] init];
        btnproject.backgroundColor = [UIColor clearColor];
        [btnproject setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, -10)];
        [btnproject.titleLabel setFont:[UIFont systemFontOfSize:15.0]];
        //cell section subtitle
        //subtitle
        lbsubtitle = [[CMLabel alloc]init];
        lbsubtitle.font = [UIFont systemFontOfSize:14];
        lbsubtitle.textColor = UIColorRGB(0x999999);
        lbsubtitle.numberOfLines = 3;
        lbsubtitle.backgroundColor = [UIColor clearColor];
        
        // background View
        subtitleView = [[UIButton alloc]init];
       // subtitleView.backgroundColor = UIColorRGB(0xffffff);

        UIImage *image1 = [UIImage imageNamed:@"class_normal"];
        UIImage *image2 = [UIImage imageNamed:@"class_select"];
        UIEdgeInsets insets = UIEdgeInsetsMake(10, 10, 10, 10);
        image1 = [image1 resizableImageWithCapInsets:insets];
        image2 = [image2 resizableImageWithCapInsets:insets];
      //  [subtitleView setBackgroundImage:image1 forState:UIControlStateNormal];
      //  [subtitleView setBackgroundImage:image2 forState:UIControlStateHighlighted];
        
        //追加在subtitle后面的 分割image
     //   blankImageView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"classCource_normal2"]];
        self.separatorLine = [[UIImageView alloc] init];
        self.separatorLine.contentMode = UIViewContentModeScaleAspectFit;
        [self.separatorLine setImage:[UIImage imageNamed:@"learn_cell_sep"]];

        
        //showImageView
        showImageView = [[UIImageView alloc]init];
        showImageView.contentMode = UIViewContentModeScaleAspectFit;

        //play button
        btnplay = [[UIButton alloc]init];

		LeftImageView = [[UIImageView alloc]init];
		LeftImageView.clipsToBounds = YES;
		LeftImageView.contentMode = UIViewContentModeScaleAspectFit; 
		
		[LeftImageView setBackgroundColor:UIColorRGB(0xffffff)];
		
		viewImageView = [[UIImageView alloc]init];
		viewImageView.image = [UIImage imageNamed:@"view"];
		
		likeImageView = [[UIImageView alloc]init];
		likeImageView.image = [UIImage imageNamed:@"reply"];
		
		lblplay = [[UILabel alloc]init];
		lblplay.font = [UIFont systemFontOfSize:12];
		lblplay.textColor=UIColorRGB(0x999999);
		[lblplay setBackgroundColor:[UIColor clearColor]];
		
		lbllike = [[UILabel alloc]init];
		lbllike.font = [UIFont systemFontOfSize:12];
		lbllike.textColor=UIColorRGB(0x999999);
		[lbllike setBackgroundColor:[UIColor clearColor]];
		
		lbltime = [[UILabel alloc]init];			
		lbltime.font = [UIFont systemFontOfSize:12];
		lbltime.textColor= UIColorRGB(0x999999);
		[lbltime setBackgroundColor:[UIColor clearColor]];
		lbltime.textAlignment = UITextAlignmentRight;
		
		Specialtopic = [[UIImageView alloc]init];
		Specialtopic.clipsToBounds = YES;
		Specialtopic.contentMode = UIViewContentModeCenter; 		
		[Specialtopic setBackgroundColor:[UIColor clearColor]];
		Specialtopic.image = [UIImage imageNamed:@"specialtopic.png"];
		Specialtopic.hidden = YES;
        
        //cell section series
        lbseries = [[CMLabel alloc]init];
        lbseries.backgroundColor = [UIColor clearColor];
        lbseries.font = [UIFont systemFontOfSize:16];
        lbseries.textColor = UIColorRGB(0x6f6f6f);
        
        //series background image
        seriesView = [[UIButton alloc]init];
        [seriesView setBackgroundImage:[UIImage imageNamed:@"serier_bg_normal"] forState:UIControlStateNormal];
        [seriesView setBackgroundImage:[UIImage imageNamed:@"serier_bg_select"] forState:UIControlStateHighlighted];
        
        //right point image
        pointImageView = [[UIImageView alloc]init];
        pointImageView.image = [UIImage imageNamed:@"point_right"];
        [self.contentView addSubview:seriesView];

        [self.contentView addSubview:subtitleView];
        [self.contentView addSubview:lbltitle];
        [self.contentView addSubview:btnproject];
        
        [self.contentView addSubview:blankImageView];
        [self.contentView addSubview:showImageView];
        [self.contentView addSubview:btnplay];
        [self.contentView addSubview:lbsubtitle];
        
        [self.contentView addSubview:lbseries];
        [self.contentView addSubview:pointImageView];
        
		[self.contentView addSubview:viewImageView];
		[self.contentView addSubview:likeImageView];
		[self.contentView addSubview:LeftImageView];	
		
		[self.contentView addSubview:lblplay];
		[self.contentView addSubview:lbllike];			
		
		[self.contentView addSubview:lbltime];
		[self.contentView addSubview:Specialtopic];
        [self.contentView addSubview:separatorLine];
		//[self.contentView addSubview:lblclass];
		
		[self setSelectionStyle:UITableViewCellSelectionStyleGray];
		self.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
		//self.detailTextLabel.adjustsFontSizeToFitWidth = YES;
        self.backgroundColor = [UIColor clearColor];
        

		
	}
	return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
	
	[super setSelected:selected animated:animated];
}

-(void)setcellinfo:(TBrowserItem&)browserItem webimage:(CMWebImage*)pWebImage{
    NSString * strFlag = [NSString stringWithUTF8String:browserItem.sFlag];
    if ([strFlag isEqualToString:@"course"] || [strFlag isEqualToString:@"news"])
    {
        NSString *url = [NSString stringWithUTF8String:browserItem.sThumbs];
        if(browserItem.sThumbs && browserItem.sThumbs != '\0' && ![url isEqualToString:@""])
        {
            UIImage*lImage = [UIImage imageNamed:@"ulp"];
            [self.LeftImageView sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:lImage];
        }
        else
            self.LeftImageView.image = [UIImage imageNamed:@"ulp"];
    }
    
    self.lblplay.text=[NSString stringWithFormat:@"%@ %d  ｜",I(@"观看"),browserItem.nVC];
    if([strFlag isEqualToString:@"news"])
    {
        self.lbllike.text = [NSString stringWithFormat:@"%d",browserItem.nCommentcount];
        self.tag = 1;
    }
    else
    {
        self.lbllike.text = [NSString stringWithFormat:@"%@ %d",I(@"评论"),browserItem.nCommentcount];
        self.tag = 2;
    }
    
    NSString *markTitle = [NSString stringWithUTF8String:browserItem.sMarkTitle]; //标签
    NSInteger markid = [[NSString stringWithUTF8String:browserItem.sMarkID] integerValue];
    
    //标题
    [self.lbltitle setText:[NSString stringWithUTF8String:browserItem.sTitle] WithFont:[UIFont systemFontOfSize:17] AndColor:UIColorRGB(0x333333)];
    self.lbltitle.isLineFeed = NO;
    
    if (!markid) {
        self.btnproject.hidden = YES;
        [self.btnproject setBackgroundImage:nil forState:UIControlStateNormal];
        [self.btnproject setBackgroundImage:nil forState:UIControlStateHighlighted];
        self.isShowMark = NO;
        
    }
    else{
        //要显示标签
        UIImage *markImage = nil;
        
        //从缓存(内存和硬盘)中查找图片
        markImage =  [[SDImageCache sharedImageCache] imageFromDiskCacheForKey:[NSString stringWithUTF8String:browserItem.sMarkPicUrl]];
        
        if(markImage == nil)
        {
            //本地缓存没图片，去下载
            __block typeof(self) weakSelf = self;
//            [[SDWebImageManager sharedManager] downloadWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:browserItem.sMarkPicUrl]]  delegate:self options:SDWebImageRetryFailed success:^(UIImage* image, BOOL cached)
//             {
//                 
//                 weakSelf.btnproject.hidden = NO;
//                 [weakSelf.btnproject setBackgroundImage:image forState:UIControlStateNormal];
//                 [weakSelf.btnproject setBackgroundImage:image forState:UIControlStateHighlighted];
//                 
//                 
//             }  failure:nil];
            [[SDWebImageManager sharedManager] downloadImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:browserItem.sMarkPicUrl]] options:SDWebImageRetryFailed progress:nil completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, BOOL finished, NSURL *imageURL) {
                dispatch_main_sync_safe(^{

                    if (image) {
                        weakSelf.btnproject.hidden = NO;
                        [weakSelf.btnproject setBackgroundImage:image forState:UIControlStateNormal];
                        [weakSelf.btnproject setBackgroundImage:image forState:UIControlStateHighlighted];
                    }
                });
               
            }];
        }
        else
        {
            //本地缓存有图片
            
            self.btnproject.hidden = NO;
            [self.btnproject setBackgroundImage:markImage forState:UIControlStateNormal];
            [self.btnproject setBackgroundImage:markImage forState:UIControlStateHighlighted];
            
        }
        self.isShowMark = YES;
        self.btnproject.tag = markid;
        [self.btnproject setTitle:markTitle forState:UIControlStateNormal];
        
    }
    
    //描述
    [self.lbsubtitle setText:[NSString stringWithUTF8String:browserItem.sDescription] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0x999999)];

}

+(CGFloat)GetCellHeight:(TBrowserItem&)browserItem webimage:(CMWebImage*)pWebImage width:(int)width
{
	CGFloat hg = 0; //cell 间距
    hg += 30.0;   //cell title height
    hg += 5.0;   //title 与subtitle间距
    
    hg += Course_News_LeftImageView_Height;
    
    hg += 25; //观看评论 与serierView 的间距(加上本身)
    
    hg += 5.0;

    return hg;
}

-(void)layoutSubviews
{
	[super layoutSubviews];
	//CGRect contentRect = self.bounds;
	CGFloat boundsX = 12;
	CGFloat boundsY = 5;

    //计算 title height
    if (!isShowMark) {
        lbltitle.frame = CGRectMake(boundsX, boundsY, CELL_ADD_LABEL, 28);
    }
    else{
        lbltitle.frame = CGRectMake(boundsX, boundsY, CELL_ADD_LABEL - 40, 28);
    }
    
    btnproject.frame = CGRectMake(UI_IOS_WINDOW_WIDTH - 93/2.0 + 1.5, boundsY, 93/2.0, 53/2.0);
    
    //cell section description
    //boundsY 加上 前面titleView的高度
    boundsY += 30;
    
    //左栏图
    self.LeftImageView.frame = CGRectMake(boundsX, boundsY, Course_News_LeftImageView_Height, Course_News_LeftImageView_Height);
    
    //计算 subtitle height
    CGSize size = CGSizeMake(UI_IOS_WINDOW_WIDTH - 3 * boundsX - self.LeftImageView.frame.size.width,MAXFLOAT);
	CGSize labelsize = [lbsubtitle.text sizeWithFont:lbsubtitle.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
    if (labelsize.height > 55) {
        labelsize.height = 55;
    }
    
    boundsY += 5.0;   //title 与subtitle间距
    lbsubtitle.frame = CGRectMake(CGRectGetMaxX(self.LeftImageView.frame) + boundsX, CGRectGetMinY(self.LeftImageView.frame), UI_IOS_WINDOW_WIDTH - 3 * boundsX - self.LeftImageView.frame.size.width, labelsize.height);
    boundsY += Course_News_LeftImageView_Height;//labelsize.height;
//    //计算 showimageview frame
//    if (showImageView.image != nil) { //判断是否有要显示的imageview
//        boundsY += 10.0; //showimageview 与subtitle 的间距
//        showImageView.frame = CGRectMake(boundsX * 3, boundsY, SHOWIMAGEVIEW_WIDTH, SHOWIMAGEVIEW_HEIGHT);
//        boundsY += SHOWIMAGEVIEW_HEIGHT; //boundsY 更新高度
//    }
//    else{
//        showImageView.frame = CGRectZero;
//    }
 
    //play button
    
    //观看，评论 与showimageview 固定间距 20
  //  boundsY += 20;
    CGSize labelSize_play=[lblplay.text sizeWithFont:lblplay.font forWidth:150 lineBreakMode:UILineBreakModeWordWrap];
    lblplay.frame = CGRectMake(boundsX, boundsY, labelSize_play.width, 20.0);
    
    lbllike.frame = CGRectMake(CGRectGetMaxX(lblplay.frame) + 5.0, boundsY, 150.0, 20.0);
    
    if (lbltime.hidden == YES) {
        lbltime.frame = CGRectZero;
    }
    else
        lbltime.frame = CGRectMake(UI_IOS_WINDOW_WIDTH - boundsX - 150, boundsY, 150.0, 20.0);
    if (Specialtopic.hidden == YES) {
        Specialtopic.frame = CGRectZero;
    }
    else
        Specialtopic.frame = CGRectMake(UI_IOS_WINDOW_WIDTH - boundsX - Specialtopic.image.size.width, boundsY - 2.0, Specialtopic.image.size.width, 25);
    
    boundsY += 25; //评论，观看本身高度 加上间距
    
    self.separatorLine.frame = CGRectMake(0, boundsY - 1, UI_IOS_WINDOW_WIDTH, 1);

}

//预渲染image
- (UIImage *)awakeFromImage:(UIImage *)image {
    if (image) {
        if (NULL != UIGraphicsBeginImageContextWithOptions)
            UIGraphicsBeginImageContextWithOptions(imageSize, YES, 0);
        else
            UIGraphicsBeginImageContext(imageSize);
        [image drawInRect:CGRectMake(0, 0, 307, 300)];
        image = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    return image;
}

- (void)dealloc {
	
	CMRELEASE(lbltitle);//课程名称
	CMRELEASE(viewImageView);
	CMRELEASE(likeImageView);
	CMRELEASE(LeftImageView);//课程图标（打上播放时长的水印）	
	CMRELEASE(lblplay);//播放次数
	CMRELEASE(lbllike);//喜欢数	
	CMRELEASE(lbltime);//发布时间
	CMRELEASE(Specialtopic);
    CMRELEASE(seriesView);
    CMRELEASE(lbseries);
    CMRELEASE(pointImageView);
    CMRELEASE(lbsubtitle);
    CMRELEASE(showImageView);
    CMRELEASE(btnproject);
    CMRELEASE(titleView);
    CMRELEASE(btnplay);
    CMRELEASE(subtitleView);
	CMRELEASE(blankImageView);
    CMRELEASE(self.separatorLine);
}


@end
