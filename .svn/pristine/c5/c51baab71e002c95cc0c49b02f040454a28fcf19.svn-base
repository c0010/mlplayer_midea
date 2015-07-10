//
//  CMTableViewCell.m
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMGroupTableViewCell.h"


@implementation CMGroupTableViewCell
@synthesize lbltitle,lbldesc,LeftImageView,lblplay,lblcomment,lblevaluate,lbltime;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
		if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
			
			lbltitle = [[UILabel alloc]init];
			lbltitle.textAlignment = UITextAlignmentLeft;
			lbltitle.font = [UIFont systemFontOfSize:kTextSizeMid];
			lbltitle.textColor = kTextColorDark;
			lbltitle.numberOfLines = 0; 
			
			//lbldesc = [[UILabel alloc]init];
//			lbldesc.textAlignment = UITextAlignmentLeft;
//			lbldesc.font = [UIFont systemFontOfSize:12];
//			
			LeftImageView = [[UIImageView alloc]init];
			LeftImageView.clipsToBounds = YES;
			LeftImageView.contentMode = UIViewContentModeScaleAspectFill; 
			[LeftImageView setBackgroundColor:[UIColor clearColor]];

			lblplay = [[UILabel alloc]init];
			lblplay.font = [UIFont systemFontOfSize:kTextSizeSml];
			lblplay.textColor=kTextColorNormal;
			[lblplay setBackgroundColor:[UIColor clearColor]];
			
			lblcomment = [[UILabel alloc]init];
			lblcomment.font = [UIFont systemFontOfSize:kTextSizeSml];
			lblcomment.textColor=kTextColorNormal;
			[lblcomment setBackgroundColor:[UIColor clearColor]];
			
			lblevaluate = [[UILabel alloc]init];
			lblevaluate.font = [UIFont systemFontOfSize:kTextSizeSml];
			lblevaluate.textColor=kTextColorNormal;
			[lblevaluate setBackgroundColor:[UIColor clearColor]];
			
			lbltime = [[UILabel alloc]init];			
			lbltime.font = [UIFont systemFontOfSize:kTextSizeSml];
			lbltime.textColor=kTextColorNormal;//[UIColor colorWithRed:136.0f/255.0f green:136.0f/255.0f blue:136.0f/255.0f alpha:1.0f];
			[lbltime setBackgroundColor:[UIColor clearColor]];
			
			//lblclass = [[UILabel alloc]init];
//			lblclass.font = [UIFont systemFontOfSize:kTextSizeSml];
//			lblclass.textColor=kTextColorNormal;//[UIColor colorWithRed:136.0f/255.0f green:136.0f/255.0f blue:136.0f/255.0f alpha:1.0f];
//			
			[self.contentView addSubview:lbltitle];
				//[self.contentView addSubview:lbldesc];
			[self.contentView addSubview:LeftImageView];	

			[self.contentView addSubview:lblplay];
			[self.contentView addSubview:lblcomment];			
			
			[self.contentView addSubview:lblevaluate];
			
			[self.contentView addSubview:lbltime];
				//[self.contentView addSubview:lblclass];
			
			[self setSelectionStyle:UITableViewCellSelectionStyleGray];
			self.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
			self.detailTextLabel.adjustsFontSizeToFitWidth = YES;
			
		}
	return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
	
	 [super setSelected:selected animated:animated];
	
}


-(void)layoutSubviews
{
	[super layoutSubviews];
	//CGRect contentRect = self.contentView.bounds;
	//CGFloat boundsX = contentRect.origin.x;
	//CGFloat boundsY = contentRect.origin.y;
    
    CGFloat boundsX ;
	CGFloat boundsY ;
	CGFloat X = 5;
	CGFloat Y = 5;
	
	CGRect frame;
	
	
	boundsX = 5 ;
	//boundsY = 2 ;

	X = LeftImageView.frame.size.width;//78/2 ;
	//Y = LeftImageView.frame.size.height;//60/2 ;

		//左图
		//frame= CGRectMake(boundsX ,boundsY, X, Y);
		//LeftImageView.frame = frame;
	
	boundsX = boundsX + X + 5;	
	boundsY = 5;	
	
	X = UI_IOS_WINDOW_WIDTH - boundsX;
	Y = 15;	
	
		//CGRect rect = [lbltitle textRectForBounds:lbltitle.frame limitedToNumberOfLines:0];
		//标题
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	
	//lbltitle.frame = frame;	
	
	[lbltitle setNumberOfLines:0];
	//NSString *s = @"string......";
	//UIFont *font = [UIFont fontWithName:@"Arial" size:12];
	CGSize size = CGSizeMake(X,UI_IOS_WINDOW_HEIGHT);
	CGSize labelsize = [lbltitle.text sizeWithFont:lbltitle.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
	
	[lbltitle setFrame:CGRectMake(boundsX, boundsY, labelsize.width, labelsize.height)];
	//[self.view addSubView:label];
	
	
	boundsX = boundsX;
		//boundsY = boundsY + Y + 5;
	Y = boundsY + labelsize.height - 10;
//	X = 250 - boundsX;
//	
	//	//分类
//	frame= CGRectMake(boundsX ,boundsY, X, Y);
//	lblclass.frame = frame;
//		//内容
//	//frame= CGRectMake(boundsX+60 ,25, 200, 15);
//	//lbldesc.frame = frame;	
//	
	boundsX = boundsX;
	boundsY = boundsY + Y + 5;
	X = 95 ;
	Y = 18 ;
	
		//播放
	
	boundsX = boundsX;

	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lblplay.frame = frame;
	
	boundsX = boundsX + X + 5-10;

		//评论		
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lblcomment.frame = frame;
	
	boundsX = boundsX + X + 5-20;

		//评价	
	
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lblevaluate.frame = frame;
	
	boundsX = 250 ;
	
	X = 70;
	
		//时间
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lbltime.frame = frame;
	
	
	
}


- (void)dealloc {
	
	CMRELEASE(lbltitle);//课程名称
	CMRELEASE(lbldesc);//课程简介
	CMRELEASE(lbltag);//标签（关键字）
	//学分、章节数
	CMRELEASE(LeftImageView);//课程图标（打上播放时长的水印）	
	CMRELEASE(lblplay);//播放次数
	CMRELEASE(lblcomment);//评论数	
	CMRELEASE(lblevaluate);//评价（顶的人数）	
	CMRELEASE(lbltime);//发布时间
}


@end
