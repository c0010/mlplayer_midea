//
//  CMTableViewCell.m
//  OCplusplus
//
//  Created by sunjj on 11-4-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMTableViewCell.h"


@implementation CMTableViewCell
@synthesize TitelLabel,PhoneLabel,DescLabel,LeftImageView;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
		if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
			
			TitelLabel = [[UILabel alloc]init];
			TitelLabel.textAlignment = UITextAlignmentLeft;
			TitelLabel.font = [UIFont systemFontOfSize:15];
            TitelLabel.backgroundColor = [UIColor clearColor];
			
			PhoneLabel = [[UILabel alloc]init];
			PhoneLabel.textAlignment = UITextAlignmentCenter;
			PhoneLabel.font = [UIFont systemFontOfSize:15];
            PhoneLabel.backgroundColor = [UIColor clearColor];

			DescLabel = [[UILabel alloc]init];
			DescLabel.textAlignment = UITextAlignmentLeft;
			DescLabel.font = [UIFont systemFontOfSize:12];
			DescLabel.textColor = UIColorRGB(0xa7a7a7);
            DescLabel.backgroundColor = [UIColor clearColor];

			LeftImageView = [[UIImageView alloc]init];
			LeftImageView.clipsToBounds = YES;
			LeftImageView.contentMode = UIViewContentModeScaleAspectFill;
			
			[self addSubview:TitelLabel];
			[self addSubview:PhoneLabel];
			[self addSubview:DescLabel];
			[self addSubview:LeftImageView];	
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
	CGRect contentRect = self.contentView.bounds;
	CGFloat boundsX = 5;
	CGFloat boundsY = 8;

    LeftImageView.frame= CGRectMake(boundsX,(CGRectGetHeight(self.contentView.frame) - 40)/2,40, 40);

    
	//boundsX += LeftImageView.image.size.width;
    boundsX += 40;
	boundsX += 5;
	TitelLabel.frame = CGRectMake(boundsX ,boundsY, 150, 25);
	PhoneLabel.frame = CGRectMake(contentRect.size.width-150 ,boundsY, 150, 25);
	boundsY += 25;
	DescLabel.frame = CGRectMake(boundsX ,boundsY, contentRect.size.width-boundsX-10, 15);
}


- (void)dealloc {
	CMRELEASE(TitelLabel);
	CMRELEASE(PhoneLabel);
	CMRELEASE(DescLabel);
	CMRELEASE(LeftImageView);
}


@end
