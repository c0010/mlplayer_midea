//
//  ReplyCommentCell.m
//  MLPlayer
//
//  Created by sunjj on 13-8-15.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMReplyTableViewCell.h"

@implementation CMReplyTableViewCell
@synthesize LeftImageView,lblcomment,lbltime,sep;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
        LeftImageView = [[UIImageView alloc]init];
		LeftImageView.clipsToBounds = YES;
		LeftImageView.contentMode = UIViewContentModeScaleAspectFill;
        
        lblcomment = [[UILabel alloc]init];
		lblcomment.textAlignment = UITextAlignmentLeft;
		lblcomment.font = [UIFont systemFontOfSize:16];
		lblcomment.textColor=[UIColor grayColor];
		[lblcomment setBackgroundColor:[UIColor clearColor]];
        
        lbltime = [[UILabel alloc]init];
		lbltime.font = [UIFont systemFontOfSize:12];
		lbltime.textColor=[UIColor grayColor];
		[lbltime setBackgroundColor:[UIColor clearColor]];
        
        sep = [[UIImageView alloc]init];
        [sep setImage:[UIImage imageNamed:@"replybrief_sep"]];
        
        [self addSubview:LeftImageView];
        [self addSubview:lblcomment];
        [self addSubview:lbltime];
        [self addSubview:sep];
        }
    return self;
}

-(void)setcellinfo:(TRepalymentItem&)item{
    self.lblcomment.text=[NSString   stringWithFormat:@"%@: %@",[NSString stringWithUTF8String:item.sFullName],[NSString stringWithUTF8String:item.sComment.c_str()]] ;
    
    if([[NSString stringWithUTF8String:item.sDatetime]  isEqualToString:@""])
        self.lbltime.text=I(@"刚刚");
    else
        self.lbltime.text=[NSString stringWithUTF8String:item.sDatetime] ;
    
//    if(item.nStatus==1)
//        self.lbltime.text=I(@"发送中...");
//    if(item.nStatus==2)
//        self.lbltime.text=I(@"发送失败");
    
    UIImage* Image = [UIImage imageNamed:@"head"];
    NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:item.sHeadImage]];
    
    [self.LeftImageView sd_setImageWithURL:url placeholderImage:Image];
}


+(CGFloat)calculateCellHeight:(NSString*)str
{
    CGSize lblsize=[str sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(230, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
    
    return lblsize.height+50.0f;
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    //CGRect contentRect = self.bounds;
	CGFloat boundsX = 5;
	CGFloat boundsY = 5;
	//CGFloat X = 0;
	//CGFloat Y = 0;
    LeftImageView.frame = CGRectMake(boundsX+10, boundsY+10, 40, 40);
    //评论内容
    boundsX += 60;
    boundsY += 10;

    
    CGSize lblsize=[lblcomment.text sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(230,MAXFLOAT ) lineBreakMode:NSLineBreakByWordWrapping];
	[lblcomment setNumberOfLines:0];
	[lblcomment setFrame:CGRectMake(boundsX, boundsY, lblsize.width, lblsize.height)];
	   
    boundsY += lblsize.height;

    boundsY += 10;
    //时间
    CGRect frame = CGRectMake(boundsX,boundsY, 150, 12);
	lbltime.frame = frame;
    [lbltime setTextAlignment:NSTextAlignmentLeft];

    
    [sep setFrame:CGRectMake(10, self.frame.size.height-1,300, 1)];
 
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
