    //
//  CMInteractTableViewCell.m
//  MLPlayer
//
//  Created by sunjj on 11-11-7.
//  Copyright 2011 w. All rights reserved.
//

#import "CMInteractMyInfoTableViewCell.h"


@implementation CMInteractMyInfoTableViewCell
@synthesize lblauthor,lbldesc,LeftImageView;
@synthesize lblfrom,lblcomment,lbltime;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
	if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
		
		lblauthor = [[UILabel alloc]init];
		lblauthor.textAlignment = UITextAlignmentLeft;
		lblauthor.font = [UIFont systemFontOfSize:LEARN_TITLE_FONT15];
		lblauthor.textColor = LEARN_TITLE_COLOR;
		
		lbldesc = [[UILabel alloc]init];
		lbldesc.textAlignment = UITextAlignmentLeft;
		lbldesc.font = [UIFont systemFontOfSize:LEARN_ATTRIBUTE_FONT];
						
		lblfrom = [[UILabel alloc]init];
		lblfrom.textAlignment = UITextAlignmentLeft;
		lblfrom.font = [UIFont systemFontOfSize:LEARN_TITLE_FONT10];
		lblfrom.textColor=LEARN_DESC_COLOR;
		
		lblcomment = [[UILabel alloc]init];
		lblcomment.textAlignment = UITextAlignmentLeft;
		lblcomment.font = [UIFont systemFontOfSize:LEARN_TITLE_FONT10];
		lblcomment.textColor=LEARN_DESC_COLOR;
		
		lbltime = [[UILabel alloc]init];			
		lbltime.font = [UIFont systemFontOfSize:LEARN_TITLE_FONT10];
		lbltime.textColor=LEARN_DESC_COLOR;
		
		[self.contentView addSubview:lblauthor];
		[self.contentView addSubview:lbldesc];
		[self.contentView addSubview:lblfrom];
		[self.contentView addSubview:lblcomment];			
		[self.contentView addSubview:lbltime];
		
		[self setSelectionStyle:UITableViewCellSelectionStyleGray];
		self.accessoryType = UITableViewCellAccessoryNone;
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
	CGRect contentRect = self.contentView.bounds;
	CGFloat boundsX = contentRect.origin.x;
	CGFloat boundsY = contentRect.origin.y;
	int X = 5;
	int Y = 5;
	
	CGRect frame;
	
	boundsX = boundsX + X + 5;	
	boundsY = 5;	
	
	X = UI_IOS_WINDOW_WIDTH - boundsX;
	Y = 15;	
	
		//标题
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lblauthor.frame = frame;
	
	boundsX = boundsX;
	boundsY = boundsY + Y + 5;
	Y = 12;
	X = 250 - boundsX;
	
		//内容
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lbldesc.frame = frame;
	
	boundsX = boundsX;
	boundsY = boundsY + Y + 5;
	X = 60 ;
	Y = 18 ;
	
		//信息来源	
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lblfrom.frame = frame;
	
	boundsX = boundsX + X + 5;
	X = 70 ;
		//评论		
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lblcomment.frame = frame;
	
	boundsX = boundsX + X + 5;	
	X = 110 ;
		//时间
	frame= CGRectMake(boundsX ,boundsY, X, Y);
	lbltime.frame = frame;
	
}

- (void)dealloc {
	
	CMRELEASE(lblauthor);
	CMRELEASE(lbldesc);
	CMRELEASE(LeftImageView);
	CMRELEASE(lblfrom);
	CMRELEASE(lblcomment);
	CMRELEASE(lbltime);
	[super dealloc];
}

@end
