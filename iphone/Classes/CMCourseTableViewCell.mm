    //
//  CMCourseTableViewCell.m
//  MLPlayer
//
//  Created by sunjj on 11-9-21.
//  Copyright 2011 w. All rights reserved.
//

#import "CMCourseTableViewCell.h"
#import "tool.h"
#import "CMImage.h"

@implementation CMCourseTableViewCell
@synthesize lblauthor,lbldesc,LeftImageView;
@synthesize lbltime;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
	if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
		
		lblauthor = [[UILabel alloc]init];
		lblauthor.textAlignment = UITextAlignmentLeft;
		lblauthor.font = [UIFont systemFontOfSize:kTextSizeSml];
		lblauthor.textColor = kTextColorNormal;
		
		lbldesc = [[UILabel alloc]init];
		lbldesc.textAlignment = UITextAlignmentLeft;
		lbldesc.font = [UIFont systemFontOfSize:kTextSizeMid];
		lbldesc.textColor=kTextColorDark;
		[lbldesc setBackgroundColor:[UIColor clearColor]];
		
		LeftImageView = [[UIImageView alloc]init];
		LeftImageView.clipsToBounds = YES;
		LeftImageView.contentMode = UIViewContentModeScaleAspectFill; 
		
		lbltime = [[UILabel alloc]init];			
		lbltime.font = [UIFont systemFontOfSize:kTextSizeSml];
		lbltime.textColor=kTextColorNormal;
		[lbltime setBackgroundColor:[UIColor clearColor]];
		
		[self addSubview:LeftImageView];
		[self addSubview:lblauthor];
		[self addSubview:lbldesc];
		[self addSubview:lbltime];
		
		[self setSelectionStyle:UITableViewCellSelectionStyleGray];
		self.accessoryType = UITableViewCellAccessoryNone;
		self.detailTextLabel.adjustsFontSizeToFitWidth = YES;
		
	}
	return self;	
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
	
	[super setSelected:selected animated:animated];
}
+(CGFloat)GetCellHeight:(const char*)sMsg url:(const char*)sUrl webimage:(CMWebImage*)pWebImage width:(int)width
{
	CGFloat hg = 0 ;
	CGFloat wd = 0 ;
	CGFloat blank = 5;
	if(pWebImage->GetFromUrl(0,sUrl))
	{	
		UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:pWebImage->GetFilePath(sUrl)]];
		hg = loadImage.size.height;
		wd = loadImage.size.width;
	}
    else
	{
		UIImage* lImage = [UIImage imageNamed:@"head.png"];
		hg = lImage.size.height;
		wd = lImage.size.width;
	}
	blank += 5;
	NSString *cellText = [NSString stringWithUTF8String:sMsg];
	
	//字体高度
	UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
	CGSize constraintSize = CGSizeMake(width-wd-blank, MAXFLOAT);
	CGSize labelSize = [cellText sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
	int fonthg = labelSize.height + kTextSizeMid + 15;	
	
	hg = MAX(hg+10,fonthg);
	return hg;			
}
-(void)setcellinfo:(const char*)sUrl webimage:(CMWebImage*)pWebImage
{
	if(pWebImage->GetFromUrl(0,sUrl))
	{	
		UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:pWebImage->GetFilePath(sUrl)]];
		LeftImageView.image = loadImage;
	}
	else
	{
		UIImage* lImage = [UIImage imageNamed:@"head.png"];
		LeftImageView.image = lImage;
	}
	CGRect cellFrame = self.frame;
	[self setFrame:cellFrame];	
	self.accessoryType = UITableViewCellAccessoryNone;
}
-(void)layoutSubviews
{
	[super layoutSubviews];
	CGRect contentRect = self.bounds;
	CGFloat boundsX = 5;
	CGFloat boundsY = 5;
	CGFloat X = 0;
	CGFloat Y = 0;
	LeftImageView.frame = CGRectMake(boundsX, (contentRect.size.height - LeftImageView.image.size.height)/2, LeftImageView.image.size.width, LeftImageView.image.size.height);
	X = LeftImageView.frame.size.width;
	
	boundsX = boundsX + X + 5;
	
	X = contentRect.size.width-boundsX;
	//Y = 15;
	
	[lbldesc setNumberOfLines:0];
	CGSize size = CGSizeMake(X,UI_IOS_WINDOW_HEIGHT);
	CGSize labelsize = [lbldesc.text sizeWithFont:lbldesc.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
	
	[lbldesc setFrame:CGRectMake(boundsX, boundsY, labelsize.width, labelsize.height)];
	
	boundsY = boundsY +labelsize.height + 5;
	//X = 80 ;
	Y = 15 ;
	
	//用户名
	CGRect frame = CGRectMake(boundsX ,boundsY, X, Y);
	lblauthor.frame = frame;
	
	boundsX = 220;//boundsX + X + 5;
	
	//回复数	
	frame= CGRectMake(boundsX ,boundsY, 100, Y);
	lbltime.frame = frame;
}



@end