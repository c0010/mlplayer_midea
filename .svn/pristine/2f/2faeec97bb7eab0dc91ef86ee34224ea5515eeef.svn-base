    //
//  CMCourseTableViewCell.m
//  MLPlayer
//
//  Created by sunjj on 11-9-21.
//  Copyright 2011 w. All rights reserved.
//

#import "CMCommentTableViewCell.h"
#import "tool.h"
#import "CMImage.h"
#import "SDWebImage/UIImageView+WebCache.h"

@implementation CMCommentTableViewCell
@synthesize lblauthor,lblcomment,LeftImageView;
@synthesize lbltime,imgpv,lblpv,imgreplycount,lblreplycount,lblsepview;
@synthesize btnComment,btnLike;
@synthesize replyBriefView;
@synthesize sep;

-(id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
	if (self =[super initWithStyle:style reuseIdentifier:reuseIdentifier]) { 
		
        //分隔符
            sep=[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"replybrief_sep"]];
        
        //喜欢按钮
        btnLike=[[UIButton alloc]init];
        [btnLike setBounds:CGRectMake(0, 0, 55, 23)];
        [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_nor"] forState:UIControlStateNormal];
        [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateHighlighted];
        [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateSelected];

        
        [btnLike setImage:[UIImage imageNamed:@"like_nor"] forState:UIControlStateNormal];
        [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateHighlighted];
        [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateSelected];
        [btnLike setAdjustsImageWhenDisabled:NO];
        [btnLike setAdjustsImageWhenHighlighted:NO];
        [btnLike setReversesTitleShadowWhenHighlighted:NO];
        
        btnLike.imageEdgeInsets=UIEdgeInsetsMake(0, -25, 0, 0);
        
        [btnLike setTag:kBtnLikeTag];

        //评论按钮
        btnComment=[[UIButton alloc]init];
        [btnComment setBounds:CGRectMake(0, 0, 55, 23)];
        [btnComment setBackgroundImage:[UIImage imageNamed:@"btn_nor"] forState:UIControlStateNormal];
        [btnComment setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateHighlighted];
        
        [btnComment setTag:kBtnCommentTag];
        [btnComment setImage:[UIImage imageNamed:@"comment_nor"] forState:UIControlStateNormal];
//        [btnComment setImage:[UIImage imageNamed:@"comment_sel"] forState:UIControlStateHighlighted];
        
        btnComment.imageEdgeInsets=UIEdgeInsetsMake(0, -25, 0, 0);
        
		lblauthor = [[UILabel alloc]init];
		lblauthor.textAlignment = UITextAlignmentLeft;
		lblauthor.font = [UIFont systemFontOfSize:kTextSizeMid];
		lblauthor.textColor = [UIColor colorWithRed:157.0/255.0f green:157.0/255.0f blue:157.0/255.0f alpha:1];
        [lblauthor setBackgroundColor:[UIColor clearColor]];
		
		lblcomment = [[UILabel alloc]init];
		lblcomment.textAlignment = UITextAlignmentLeft;
		lblcomment.font = [UIFont systemFontOfSize:17];
		lblcomment.textColor=kTextColorDark;
		[lblcomment setBackgroundColor:[UIColor clearColor]];
		
		LeftImageView = [[UIImageView alloc]init];
		LeftImageView.clipsToBounds = YES;
		LeftImageView.contentMode = UIViewContentModeScaleAspectFill; 
		
        //喜欢图
		imgpv = [[UIImageView alloc]init];
		imgpv.clipsToBounds = YES;
		imgpv.contentMode = UIViewContentModeScaleAspectFill; 
		UIImage* image = [UIImage imageNamed:@"like_nor"];
		imgpv.image = image;
		imgpv.frame = CGRectMake(0,0,image.size.width,image.size.width);
        
		//回复图
		imgreplycount = [[UIImageView alloc]init];
		imgreplycount.clipsToBounds = YES;
		imgreplycount.contentMode = UIViewContentModeScaleAspectFill; 
		image = [UIImage imageNamed:@"comment_nor"];
		imgreplycount.image = image;
		imgpv.frame = CGRectMake(0,0,image.size.width,image.size.width);
				
		lbltime = [[UILabel alloc]init];			
		lbltime.font = [UIFont systemFontOfSize:kTextSizeSml];
		lbltime.textColor=kTextColorNormal;
		[lbltime setBackgroundColor:[UIColor clearColor]];
		
		lblpv = [[UILabel alloc]init];			
		lblpv.font = [UIFont systemFontOfSize:kTextSizeSml];
		lblpv.textColor=kTextColorNormal;
		[lblpv setBackgroundColor:[UIColor clearColor]];
        [lblpv setTag:kLblPvTag];
		
		lblreplycount = [[UILabel alloc]init];			
		lblreplycount.font = [UIFont systemFontOfSize:kTextSizeSml];
		lblreplycount.textColor=kTextColorNormal;
		[lblreplycount setBackgroundColor:[UIColor clearColor]];
		
		lblsepview = [[UIView alloc] init];
		lblsepview.backgroundColor = UIColorRGB(0xcbcbcb);
        
        replyBriefView=nil;
        
        
        [self addSubview:btnComment];
        [self addSubview:btnLike];
		[self addSubview:LeftImageView];
	//	[self addSubview:imgreplycount];
	//	[self addSubview:imgpv];
		[self addSubview:lblauthor];
		[self addSubview:lblcomment];
		[self addSubview:lbltime];
		[self addSubview:lblpv];
		[self addSubview:lblreplycount];
		[self addSubview:lblsepview];
    
		self.selectionStyle = UITableViewCellSelectionStyleNone;
		self.accessoryType = UITableViewCellAccessoryNone;
		//self.detailTextLabel.adjustsFontSizeToFitWidth = YES;
		
	}
	return self;	
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
	
	[super setSelected:selected animated:animated];
}
//计算评论背景高度
+(CGFloat)calculateReplyBriefViewHeight:(TCommentItem*)item
{
    if(!item)
        return 0;
    
    if(item->GetChildItemCount()==0)
        return 0;
    
    //up 7
    //mid 3/2
    //down 3
    //评论数高度 20
    //评论时间 *2 40
    
    //间隔 20
    CGFloat totalheight=0;
    totalheight +=7;
    
    if(item->GetChildItemCount()>=1)
    {
        TCommentItem *tempItem= new TCommentItem();
        item->GetChildItem(0, *tempItem);
        
        totalheight +=12+5;//replyCount高度

        NSString *content=[NSString stringWithFormat:@"%@: %@",[NSString stringWithUTF8String:tempItem->sUsername],[NSString stringWithUTF8String:tempItem->sComment.c_str()]];
                
        CGSize replysize=[content sizeWithFont:[UIFont systemFontOfSize:14] constrainedToSize:CGSizeMake(230, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap] ;
        totalheight += replysize.height;//第一条消息高度
        
        totalheight += 5;//间距
        totalheight += 12;//发送时间高度
        totalheight += 5;//间距
        
        SAFEDELETE(tempItem);

    }
    
    if(item->GetChildItemCount()>=2)
    {
        TCommentItem *tempItem=new TCommentItem();
        item->GetChildItem(1, *tempItem);

        
        totalheight += 5;//间距
        totalheight += 2;//分隔符高度

        totalheight += 5;//间距

        
        NSString *content=[NSString stringWithFormat:@"%@: %@",[NSString stringWithUTF8String:tempItem->sUsername],[NSString stringWithUTF8String:tempItem->sComment.c_str()]];
        
        CGSize replysize=[content sizeWithFont:[UIFont systemFontOfSize:14] constrainedToSize:CGSizeMake(230, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
        
        totalheight += replysize.height;
        totalheight += 5;//间距
        totalheight += 12;//发送时间高度
        totalheight += 5;//间距
        
        SAFEDELETE(tempItem);


        
    }
    
    return totalheight;
    
    
}

+(CGFloat)GetCellHeight:(TCommentItem&)item webimage:(CMWebImage*)pWebImage width:(int)width
{
	CGFloat hg = 0 ;
	CGFloat wd = 0 ;
	CGFloat blank = 10;
    
	if(pWebImage->GetFromUrl(0,item.sHeadImage))
	{	
	//	UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:pWebImage->GetFilePath(item.sHeadImage)]];
	//	hg = loadImage.size.height;
	//	wd = loadImage.size.width;
        hg = 40;
        wd = 40;
	}
    else
	{
		//UIImage* lImage = [UIImage imageNamed:@"head"];
		//hg = lImage.size.height;
		//wd = lImage.size.width;
        hg = 40;
        wd = 40;
	}
	blank += 5;
	NSString *cellText = [NSString stringWithUTF8String:item.sComment.c_str()];
	
	//字体高度
	UIFont *cellFont = [UIFont systemFontOfSize:17];
	CGSize constraintSize = CGSizeMake(width-wd-2*blank, MAXFLOAT);
	CGSize labelSize = [cellText sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
	int fonthg = labelSize.height + 16*2 + 16+[CMCommentTableViewCell calculateReplyBriefViewHeight:&item];
	
	hg = MAX(hg+10,fonthg);
    hg +=35;
    
	return fonthg+20;
}

-(void)setcellinfo:(TCommentItem&)item webimage:(CMWebImage*)pWebImage
{
	if(pWebImage->GetFromUrl(0,item.sHeadImage))
	{	
		UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:pWebImage->GetFilePath(item.sHeadImage)]];
		LeftImageView.image = loadImage;
	}
	else
	{
		UIImage* lImage = [UIImage imageNamed:@"head"];
		LeftImageView.image = lImage;
	}
    
	CGRect cellFrame = self.frame;
	[self setFrame:cellFrame];
	lblauthor.text = [NSString stringWithUTF8String:item.sFullName];
	lbltime.text = [NSString stringWithUTF8String:item.sDatetime];
	lblpv.text = [NSString stringWithFormat:@"%d",item.npv];
	lblreplycount.text = [NSString stringWithFormat:@"%d",item.nreply];
	lblcomment.text = [NSString stringWithUTF8String:item.sComment.c_str()];
    
	self.accessoryType = UITableViewCellAccessoryNone;

    
    UIView *oldView=[self  viewWithTag:11];
    if(oldView)
        [oldView removeFromSuperview];
    
    replyBriefView=[self setUpReplyView:&item];
    [replyBriefView setTag:11];
    if (replyBriefView) {
        [self addSubview:replyBriefView];
    }
}

-(void)layoutSubviews
{
	[super layoutSubviews];
	CGRect contentRect = self.bounds;
	CGFloat boundsX = 8;
	CGFloat boundsY = 5;
	CGFloat X = 0;
	CGFloat Y = 0;
    LeftImageView.frame = CGRectMake(boundsX, boundsY, 40, 40);

	X = 40;
	
	boundsX = boundsX + X + 10;
	X = contentRect.size.width-boundsX;
	Y = 15;	
	
	//用户名
	CGRect frame = CGRectMake(boundsX ,boundsY, X, Y + 3);
	lblauthor.frame = frame;
	
	//时间
	frame = CGRectMake(boundsX+105 ,boundsY, 150, Y);
	lbltime.frame = frame;
    [lbltime setTextAlignment:NSTextAlignmentRight];
    
	boundsY+= 15;

	[lblcomment setNumberOfLines:0];
	CGSize size = CGSizeMake(contentRect.size.width - 70,MAXFLOAT);
	CGSize labelsize = [lblcomment.text sizeWithFont:lblcomment.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
	
	[lblcomment setFrame:CGRectMake(boundsX, boundsY+10, labelsize.width, labelsize.height)];
	
	lblsepview.frame = CGRectMake(0, contentRect.size.height-1, contentRect.size.width, 1);
    
    [replyBriefView setFrame:CGRectMake(320-270+10,  boundsY+15+labelsize.height, replyBriefView.frame.size.width, replyBriefView.frame.size.height)];

    boundsY=boundsY+15+labelsize.height+replyBriefView.frame.size.height;
    //评论按钮
    [btnLike setFrame:CGRectMake(boundsX+130, boundsY+5, 55, 23)];
    
    //喜欢按钮
    [btnComment setFrame:CGRectMake(boundsX+55+15+130, boundsY+5, 55, 23)];
    
    //喜欢
	lblreplycount.frame = CGRectMake(boundsX+55+15+35+130,boundsY+10, 30, Y);
	
	//回复
	lblpv.frame = CGRectMake(boundsX+35+130,boundsY+10, 30, Y);
    
}

-(UIImageView*)setUpReplyView:(TCommentItem*)item
{
    if(item->GetChildItemCount()==0)
        return nil;
    
    UIImage *upImage=[UIImage imageNamed:@"replybrief_up.png"];
    UIImage *midImage=[UIImage imageNamed:@"replybrief_mid.png"];
    UIImage *downImage=[UIImage imageNamed:@"replybrief_down.png"];
    
    CGFloat viewheight=0;

    viewheight=[CMCommentTableViewCell calculateReplyBriefViewHeight:item];

    CGFloat viewwidth= 252.0f;
    
    //拼接图片
    UIGraphicsBeginImageContextWithOptions(CGSizeMake(viewwidth,viewheight), NO, 2) ;
    
    // Draw up
    [upImage drawInRect:CGRectMake(0, 0, viewwidth, 7)];
    
    // Draw mid
    [midImage drawAsPatternInRect:CGRectMake(0, 7, viewwidth, viewheight-7-3)];
    
    // Draw right
    [downImage drawInRect:CGRectMake(0, viewheight-3, viewwidth , 3)];
    
    UIImage *resultingImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    UIImageView* temp_replyBrief=[[UIImageView alloc]initWithImage:resultingImage];
    [temp_replyBrief setFrame:CGRectMake(0, 0, viewwidth, viewheight)];
    
    CGFloat upHeight=7;
    if(item->GetChildItemCount()>=1)
    {
        TCommentItem *tempItem= new TCommentItem();
        item->GetChildItem(0, *tempItem);
        
        //添加消息记录
        UILabel *replyCount=[[UILabel alloc]initWithFrame:CGRectMake(120, upHeight+4, 100, 12)];
        replyCount.text=[NSString stringWithFormat:@"%d条回复",item->nreply];
        [replyCount setBackgroundColor:[UIColor clearColor]];
        [replyCount setTextAlignment:NSTextAlignmentRight];
        [replyCount setFont:[UIFont systemFontOfSize:12]];
        [replyCount setTextColor:[UIColor colorWithRed:168.0/255.0f green:168.0/255.0f blue:168.0/255.0f alpha:1]];
        [temp_replyBrief addSubview:replyCount];
        
        upHeight+=replyCount.frame.size.height;
        
        NSString *content=[NSString stringWithFormat:@"%@: %@",[NSString stringWithUTF8String:tempItem->sFullName],[NSString stringWithUTF8String:tempItem->sComment.c_str()]];
        
        //添加文字
        CGSize lblsize=[content sizeWithFont:[UIFont systemFontOfSize:14] constrainedToSize:CGSizeMake(230, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
        
        UILabel* replylbl1=[[UILabel alloc]initWithFrame:CGRectMake(10, upHeight+5, 230, lblsize.height)];
        [replylbl1 setBackgroundColor:[UIColor clearColor]];
        [replylbl1 setFont:[UIFont systemFontOfSize:14]];

        //多行显示
        [replylbl1 setNumberOfLines:0];
        [replylbl1 setLineBreakMode:UILineBreakModeWordWrap];
        
        replylbl1.text=content;
        [temp_replyBrief addSubview:replylbl1];
        
        upHeight+=5;//间距
        upHeight+=replylbl1.frame.size.height;
        
        //添加发送时间
        UILabel *replyDate=[[UILabel alloc]initWithFrame:CGRectMake(10, upHeight+5, 100, 12)];
        replyDate.text=[NSString stringWithUTF8String:tempItem->sDatetime];
        [replyDate setBackgroundColor:[UIColor clearColor]];
        [replyDate setTextAlignment:NSTextAlignmentLeft];
        [replyDate setFont:[UIFont systemFontOfSize:12]];
        [replyDate setTextColor:[UIColor colorWithRed:168.0/255.0f green:168.0/255.0f blue:168.0/255.0f alpha:1]];
        [temp_replyBrief addSubview:replyDate];
        
        
        upHeight+=replyDate.frame.size.height;
        upHeight+=10;//间隔
        SAFEDELETE(tempItem);        
    }
        
    if(item->GetChildItemCount()>=2)
    {
        TCommentItem *tempItem= new TCommentItem();
        item->GetChildItem(1, *tempItem);
        
        //加入分隔符
        
        [sep setFrame:CGRectMake(10, upHeight,230, 2)];
//        [temp_replyBrief addSubview:sep];
//        [sep release];
        
        upHeight += sep.frame.size.height;
        upHeight += 5;//间隔
        
        NSString *content=[NSString stringWithFormat:@"%@: %@",[NSString stringWithUTF8String:tempItem->sFullName],[NSString stringWithUTF8String:tempItem->sComment.c_str()]];
        
        
        //加入第二条消息
        CGSize lblsize=[content sizeWithFont:[UIFont systemFontOfSize:14] constrainedToSize:CGSizeMake(230, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
        
        UILabel* replylbl2=[[UILabel alloc]initWithFrame:CGRectMake(10, upHeight, 230, lblsize.height)];
        //多行显示
        [replylbl2 setNumberOfLines:0];
        [replylbl2 setLineBreakMode:UILineBreakModeWordWrap];

        [replylbl2 setBackgroundColor:[UIColor clearColor]];
        replylbl2.text=content;
        [replylbl2 setFont:[UIFont systemFontOfSize:14]];
        [temp_replyBrief addSubview:replylbl2];
        
        upHeight += replylbl2.frame.size.height;
        upHeight += 5;//间隔

        //添加发送时间
        UILabel *replyDate=[[UILabel alloc]initWithFrame:CGRectMake(10, upHeight, 100, 12)];
        replyDate.text=[NSString stringWithUTF8String:tempItem->sDatetime];
        [replyDate setBackgroundColor:[UIColor clearColor]];
        [replyDate setTextAlignment:NSTextAlignmentLeft];
        [replyDate setFont:[UIFont systemFontOfSize:12]];
        [replyDate setTextColor:[UIColor colorWithRed:168.0/255.0f green:168.0/255.0f blue:168.0/255.0f alpha:1]];
        [temp_replyBrief addSubview:replyDate];
        
        SAFEDELETE(tempItem);

    }
    return temp_replyBrief;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:self];
    if (point.x >= btnLike.frame.origin.x && point.y >= btnLike.frame.origin.y) {
        return;
    }
    
    [super touchesBegan:touches withEvent:event];
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    
    [super touchesEnded:touches withEvent:event];
    
}



@end