//
//  CMNewsCell.m
//  MLPlayer
//
//  Created by sunjj on 13-7-29.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMNewsCell.h"
#import "tool.h"


@implementation CMNewsCell
@synthesize LeftImageView,lbltitle,viewCountLabel,contentLabel;
@synthesize lbltime;
@synthesize separatorLine;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}


- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        lbltitle.textColor = UIColorRGB(0x000000);
        contentLabel.textColor = [UIColor grayColor];

      
        LeftImageView = [[UIImageView alloc]init];
        
        lbltitle = [[CMLabel alloc]init];
        lbltitle.backgroundColor = [UIColor clearColor];
        lbltitle.font = [UIFont systemFontOfSize:17.0];
        
        contentLabel = [[CMLabel alloc]init];
        contentLabel.backgroundColor = [UIColor clearColor];
        contentLabel.numberOfLines = 2;
        contentLabel.font = [UIFont systemFontOfSize:14.0];
        contentLabel.textColor = [UIColor colorWithRed:102/255.0 green:102/255.0 blue:102/255.0 alpha:1.0];
        
        viewCountLabel = [[UILabel alloc]init];
        viewCountLabel.backgroundColor = [UIColor clearColor];
        viewCountLabel.textColor = [UIColor colorWithRed:102/255.0 green:102/255.0 blue:102/255.0 alpha:1.0];
        viewCountLabel.font = [UIFont systemFontOfSize:12.0];
        
        lbltime = [[UILabel alloc]init];
        lbltime.backgroundColor = [UIColor clearColor];
        lbltime.textColor = [UIColor colorWithRed:102/255.0 green:102/255.0 blue:102/255.0 alpha:1.0];
        lbltime.font = [UIFont systemFontOfSize:12.0];
        
        self.separatorLine = [[UIImageView alloc] init];
        self.separatorLine.contentMode = UIViewContentModeScaleAspectFit;
        [self.separatorLine setImage:[UIImage imageNamed:@"learn_cell_sep"]];
        
        [self.contentView addSubview:lbltitle];
        [self.contentView addSubview:contentLabel];
        [self.contentView addSubview:LeftImageView];
        [self.contentView addSubview:lbltime];
        [self.contentView addSubview:viewCountLabel];
        [self.contentView addSubview:separatorLine];
        
    }
    return self;
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)layoutSubviews
{
    // Drawing code
    [super layoutSubviews];
    double boundsX = 10.0;
    double boundsY = 5.0;
    if (LeftImageView.image == nil) {
        LeftImageView.frame = CGRectZero;
    }
    else
        LeftImageView.frame = CGRectMake(UI_IOS_WINDOW_WIDTH - boundsX - Course_News_LeftImageView_Height, boundsX, Course_News_LeftImageView_Height, Course_News_LeftImageView_Height);
    lbltitle.frame = CGRectMake(boundsX, boundsY, UI_IOS_WINDOW_WIDTH - 2 * boundsX - LeftImageView.frame.size.width, 20);
    contentLabel.frame = CGRectMake(boundsX, CGRectGetMaxY(lbltitle.frame), CGRectGetWidth(lbltitle.frame), 40);
    
    CGSize labelSize=[viewCountLabel.text sizeWithFont:viewCountLabel.font forWidth:150.0 lineBreakMode:UILineBreakModeWordWrap];
    viewCountLabel.frame = CGRectMake(boundsX, CGRectGetMaxY(contentLabel.frame), labelSize.width, 20.0);
    lbltime.frame = CGRectMake(CGRectGetMaxX(viewCountLabel.frame) + 8.0, CGRectGetMaxY(contentLabel.frame), 150.0, 20.0);
    
    self.separatorLine.frame = CGRectMake(0, self.bounds.size.height - 1, UI_IOS_WINDOW_WIDTH, 1);
}

-(void)setcellinfo:(TBrowserItem&)browserItem{
    NSString *url = [NSString stringWithUTF8String:browserItem.sImage];
    if(browserItem.sImage && browserItem.sImage != '\0' && ![url isEqualToString:@""])
    {
        UIImage*lImage = [UIImage imageNamed:@"ulp"];
        
        [self.LeftImageView sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:lImage];
    }
    else
        self.LeftImageView.image = nil;
    
    
    //标题
    [self.lbltitle setText:[NSString stringWithUTF8String:browserItem.sTitle] WithFont:[UIFont systemFontOfSize:17.0] AndColor:UIColorRGB(0x000000)];
    self.lbltitle.isLineFeed = NO;
    
    [self.contentLabel setText:[NSString stringWithUTF8String:browserItem.sBrief] WithFont:[UIFont systemFontOfSize:14] AndColor:[UIColor colorWithRed:102/255.0 green:102/255.0 blue:102/255.0 alpha:1.0]];
    
    self.viewCountLabel.text=[NSString stringWithFormat:@"%d%@",browserItem.nVC,I(@"浏览") ];

}

- (void)dealloc{
    CMRELEASE(lbltime);
    CMRELEASE(lbltitle);
    CMRELEASE(contentLabel);
    CMRELEASE(viewCountLabel);
    CMRELEASE(LeftImageView);
    CMRELEASE(self.separatorLine);

}

@end
