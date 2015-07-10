//
//  CMPersonTableViewCell.m
//  MLPlayer
//
//  Created by hushengwu on 14-6-21.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMPersonTableViewCell.h"
#import "tool.h"
@implementation CMPersonTableViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
        self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(130, 15, 170, 15)];
        self.titleLabel.font = [UIFont systemFontOfSize:kTextSizeMidLess];
        //self.titleLabel.textColor = UIColorRGB(0x2e2e2e);
        self.titleLabel.textAlignment = NSTextAlignmentLeft;
        
        self.desLabel = [[UILabel alloc] initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH - 60, 15, 200, 15)];
        self.desLabel.font = [UIFont systemFontOfSize:kTextSizeMidLess];
        self.desLabel.numberOfLines = 2;
        self.desLabel.textColor = UIColorRGB(0x8a8a8a);
        self.desLabel.textAlignment = NSTextAlignmentRight;
        
        self.rankImageView = [[UIImageView alloc] initWithFrame:CGRectMake(90, 13, 29, 18)];
        self.rankImageView.contentMode = UIViewContentModeScaleAspectFit;
        self.rankImageView.hidden = YES;
        
        self.accessoryImageView = [[UIImageView alloc] initWithFrame:CGRectMake(90, 13, 29, 18)];
        self.accessoryImageView.contentMode = UIViewContentModeScaleAspectFit;
        self.accessoryImageView.image = [UIImage imageNamed:@"point_right"];
        self.accessoryImageView.hidden = YES;
        
        //分割线
        self.sepV = [[UIImageView alloc] initWithFrame:CGRectMake(10, self.contentView.frame.size.height - 1, UI_IOS_WINDOW_WIDTH - 10, 1)];
        //self.sepV.contentMode = UIViewContentModeScaleAspectFit;
        [self.sepV setImage:[UIImage imageNamed:@"course_sep"]];
        
        [self.contentView addSubview:self.titleLabel];
        [self.contentView addSubview:self.desLabel];
        [self.contentView addSubview:self.rankImageView];
        [self.contentView addSubview:self.accessoryImageView];
        [self.contentView addSubview:self.sepV];
    }
    return self;
}

- (void)awakeFromNib
{
    // Initialization code
}

- (void)layoutSubviews{
	[super layoutSubviews];
	CGRect contentRect = self.bounds;
	CGFloat boundsX = 30;
	CGFloat boundsY = 15;
    
//    NSString *strvalue = [NSString stringWithUTF8String:CMMyInfo::GetInstance()->GetDesc()];
//    if ([strvalue isEqualToString:@"null"] || [strvalue length] <= 0 || !strvalue) {
//        strvalue = I(@"暂无签名");
//    }
//    //字体高度
//	UIFont *cellFont = [UIFont systemFontOfSize:14];
//	CGSize constraintSize = CGSizeMake(200.0, MAXFLOAT);
//	CGSize labelSize = [cellText sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
    
    
   self.titleLabel.frame = CGRectMake(boundsX, boundsY, 100, contentRect.size.height - 2 * boundsY);
    
    
    self.desLabel.frame = CGRectMake(UI_IOS_WINDOW_WIDTH - 30 - 200, boundsY, 200.0, contentRect.size.height - 2 * boundsY);
    
    self.sepV.frame = CGRectMake(10, contentRect.size.height - 1, UI_IOS_WINDOW_WIDTH-10, 1);

    self.accessoryImageView.frame = CGRectMake(UI_IOS_WINDOW_WIDTH - 30 - 25, (contentRect.size.height - 25)/2, 25, 25);
}

+(CGFloat)GetCellHeight:(NSString *)Msg width:(int)width
{
	CGFloat blank = 5;
    
	blank += 5;
	NSString *cellText = Msg;
	
	//字体高度
	UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMidLess];
	CGSize constraintSize = CGSizeMake(200.0, MAXFLOAT);
	CGSize labelSize = [cellText sizeWithFont:cellFont constrainedToSize:constraintSize];
	int fonthg = labelSize.height + 31;
	
	return fonthg;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
