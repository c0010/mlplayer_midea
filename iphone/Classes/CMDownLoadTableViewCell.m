//
//  CMDownLoadTableViewCell.m
//  MLPlayer
//
//  Created by sunjj on 11-12-14.
//  Copyright 2011 w. All rights reserved.
//

#import "CMDownLoadTableViewCell.h"


@implementation CMDownLoadTableViewCell
@synthesize LeftImageView,lbltitle,lblvalue,btnstatus,tagImg,selView,selViewTop;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        lbltitle = [[UILabel alloc]init];
		lbltitle.textAlignment = UITextAlignmentLeft;
		lbltitle.font = [UIFont systemFontOfSize:kTextSizeBig];
		lbltitle.textColor = kTextColorDark;
        lbltitle.numberOfLines = 2;
		lbltitle.backgroundColor = [UIColor clearColor];
		
		LeftImageView = [[UIImageView alloc]init];
		LeftImageView.clipsToBounds = YES;
		LeftImageView.contentMode = UIViewContentModeScaleAspectFill; 
		
		tagImg = [[UIImageView alloc] init];
		tagImg.clipsToBounds = YES;
		tagImg.contentMode = UIViewContentModeScaleAspectFill;
				
		lblvalue = [[UILabel alloc]init];
		lblvalue.textAlignment = UITextAlignmentLeft;
		lblvalue.font = [UIFont systemFontOfSize:kTextSizeSml];
		lblvalue.textColor=kTextColorNormal;
		lblvalue.backgroundColor = [UIColor clearColor];
		
		
		btnstatus = [UIButton buttonWithType:UIButtonTypeCustom];

        selView = [[UIView alloc]init];
        selView.backgroundColor = UIColorRGB(0xdbdbdb);
        
        selViewTop = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 0.5)];
        selViewTop.backgroundColor = UIColorRGB(0xfdfdfd);

        [self.contentView addSubview:selView];
        [self.contentView addSubview:selViewTop];
        [self.contentView addSubview:lbltitle];
		[self.contentView addSubview:lblvalue];
		[self.contentView addSubview:tagImg];

        [self.contentView addSubview:btnstatus];

		[self setSelectionStyle:UITableViewCellSelectionStyleGray];
		self.accessoryType = UITableViewCellAccessoryNone;
		self.detailTextLabel.adjustsFontSizeToFitWidth = YES;
		
		
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
    // Configure the view for the selected state.
}

//获取cell高度
+(CGFloat)GetCellHeight:(NSString *)title  width:(int)width{
    CGFloat hg = 5.0; //cell 间距
    
	//字体高度
	CGSize constraintSize = CGSizeMake(UI_IOS_WINDOW_WIDTH - 17, MAXFLOAT);
    
	CGSize labelSize = [title sizeWithFont:[UIFont systemFontOfSize:18] constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
    if (labelSize.height > 44.0) {
        hg += 44.0;
    }
    else
        hg += labelSize.height; // subtitle height
    
    hg += 25; // time height
    //判断同系列
	
	return hg;
}
-(void)layoutSubviews
{
	[super layoutSubviews];
	CGRect contentRect = self.contentView.bounds;
	CGFloat boundsX ;
	CGFloat boundsY ;
	int X = 5;
	int Y = 5;
	
	CGRect frame;
	
	boundsX = 10 ;
	boundsY = 10 ;
	
	X = 10.0;//78/2 ;
	Y = 10.0;//60/2 ;
	
	
	boundsY = 5;	
	
	X = UI_IOS_WINDOW_WIDTH - boundsX;
	Y = 18;	
	
		//标题
    CGSize constraintSize = CGSizeMake(X, MAXFLOAT);
    
	CGSize labelSize = [lbltitle.text sizeWithFont:[UIFont systemFontOfSize:18] constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
    if (labelSize.height > 44.0) {
        labelSize.height = 44.0;
    }
   
	frame= CGRectMake(boundsX ,boundsY, X-50, labelSize.height);
	lbltitle.frame = frame;
	
	boundsX = boundsX;
	boundsY = boundsY + Y + 5;
	Y = 25;
	X = 40;
	
    CGSize labelSize_ = [lblvalue.text sizeWithFont:lblvalue.font forWidth:150 lineBreakMode:UILineBreakModeWordWrap];

	frame= CGRectMake(labelSize_.width + boundsX + 10.0 ,CGRectGetMaxY(lbltitle.frame), X, Y);
	btnstatus.frame = frame;

	boundsY = boundsY - 3;
	//boundsX = boundsX + 50;
	
		//内容
	frame= CGRectMake(boundsX ,CGRectGetMaxY(lbltitle.frame) + 1.0,150, 18);
	lblvalue.frame = frame;
	
	
	frame= CGRectMake(UI_IOS_WINDOW_WIDTH-25 , (self.frame.size.height - 15)/2, 15, 15);
	tagImg.frame = frame;
    
    selView.frame = CGRectMake(0.0, CGRectGetMaxY(contentRect) - 0.5, UI_IOS_WINDOW_WIDTH, 0.5);
    
}

- (void)dealloc {
	
	CMRELEASE(LeftImageView);
	CMRELEASE(lbltitle);
	CMRELEASE(lblvalue);//下载完
	CMRELEASE(tagImg);
    CMRELEASE(selView);
    CMRELEASE(selViewTop);
}

@end
