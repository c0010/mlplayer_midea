//
//  CMLearnRecordCell.m
//  MLPlayer
//
//  Created by hushengwu on 13-9-25.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMLearnRecordCell.h"
#import "tool.h"
@implementation CMLearnRecordCell
@synthesize lbltitle = _lbltitle;
@synthesize lbltime  = _lbltime;
//@synthesize typeImageView = _typeImageView;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor clearColor];// UIColorRGB(0xf8f8f8);
        _lbltitle = [[UILabel alloc]init];
        _lbltitle.backgroundColor = [UIColor clearColor];
        _lbltitle.numberOfLines = 3;
        _lbltitle.textAlignment = UITextAlignmentLeft;
		_lbltitle.font = [UIFont systemFontOfSize:kTextSizeBigLess];
		_lbltitle.textColor = UIColorRGB(0x3a3a3a);
        
        self.popBackgroundView = [[UIImageView alloc] init];
        UIImage *image = [UIImage imageNamed:@"learnrecord_pop_bg"];
        image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(30, 40, 6, 6)];
        self.popBackgroundView.image = image;
        
        self.titleView = [[UIView alloc] initWithFrame:CGRectMake(0, 10, UI_IOS_WINDOW_WIDTH, 20)];
        self.titleView.backgroundColor = [UIColor clearColor];
        
        UIImageView *leftItemV = [[UIImageView alloc] initWithFrame:CGRectMake(16, 4.5, 11, 11)];
        leftItemV.image = [UIImage imageNamed:@"learnrecord_left_dot"];
        
        _lbltime = [[UILabel alloc]init];
        _lbltime.frame = CGRectMake(46, 0, 250, 20);
		_lbltime.font = [UIFont systemFontOfSize:kTextSizeSml];
		_lbltime.textColor= UIColorRGB(0x999999);
		[_lbltime setBackgroundColor:[UIColor clearColor]];
		_lbltime.textAlignment = UITextAlignmentLeft;
        
        self.leftLineImageView = [[UIImageView alloc] init];
        image = [UIImage imageNamed:@"learnrecord_left_line"];
        image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(2, 0, 2, 0)];
        self.leftLineImageView.image = image;
//        _typeImageView = [[UIImageView alloc]init];
//        _typeImageView.image = [UIImage imageNamed:@"classMark"];
        
        [self.titleView addSubview:_lbltime];
        [self.contentView addSubview:self.popBackgroundView];
        [self.popBackgroundView addSubview:_lbltitle];
        //[self.contentView addSubview:_typeImageView];
        [self.contentView addSubview:self.leftLineImageView];
        [self.titleView addSubview:leftItemV];
        [self.contentView addSubview:self.titleView];
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    
    if (selected) {
        UIImage *selectedImage = [UIImage imageNamed:@"learnrecord_pop_bg_s"];
        selectedImage = [selectedImage resizableImageWithCapInsets:UIEdgeInsetsMake(30, 40, 6, 6)];
        self.popBackgroundView.image = selectedImage;
        [self.popBackgroundView setNeedsDisplay];
    }
    else {
        UIImage *image = [UIImage imageNamed:@"learnrecord_pop_bg"];
        image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(30, 40, 6, 6)];
        self.popBackgroundView.image = image;
        [self.popBackgroundView setNeedsDisplay];
    }
    

    // Configure the view for the selected state
}


//获取cell高度
+(CGFloat)GetCellHeight:(TBrowserItem&)browserItem  width:(int)width  withPreString:(NSString*)pretimestr{
    CGFloat hg = 0; //cell 间距
    
    NSString *cellText = [NSString stringWithUTF8String:browserItem.sTitle];
    NSString *timestr = [NSString stringWithUTF8String:browserItem.sPubdate];
	//字体高度
	CGSize constraintSize = CGSizeMake(230, MAXFLOAT);
    
	CGSize labelSize = [cellText sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
    if (labelSize.height < 32) {
        hg += 32;
    }
    else
        hg += labelSize.height; // subtitle height
    
    if (pretimestr) {
        if (![pretimestr isEqualToString:timestr]) {
             hg += 35;
        }
    }
    else{
         hg += 35;
    }
    hg += 16; // time height
    //判断同系列
	
	return hg;
}

-(void)setcellinfo:(TBrowserItem&)browserItem perTimeString:(NSString*)pertimestr{
    self.lbltitle.text = [NSString stringWithUTF8String:browserItem.sTitle];//标题
    
    NSString *timestr = [NSString stringWithUTF8String:browserItem.sPubdate];
    
    if (pertimestr) {
        if (![pertimestr isEqualToString:timestr]) {
            isShowTimeItem = YES;
        }
        else{
            isShowTimeItem = NO;
        }
    }
    else{
        isShowTimeItem = YES;
    }
    
    if ([timestr length] > 5) {
        timestr = [timestr substringFromIndex:5];
    }
    
	self.lbltime.text = timestr;//发布时间
    
//	if(browserItem.nModel==0){
//        self.typeImageView.hidden = YES;
//    }
//    else{
//        self.typeImageView.hidden = YES;
//    }

}


//绘制
- (void)layoutSubviews{
    [super layoutSubviews];
    //CGFloat boundsX = 5;
	CGFloat boundsY = 8;
    
    CGFloat h = 5;
    
    if (isShowTimeItem) {
        h += 30;
        self.titleView.hidden = NO;
    }
    else{
        self.titleView.hidden = YES;
    }
    CGSize size = CGSizeMake(230,MAXFLOAT);
	CGSize labelsize = [_lbltitle.text sizeWithFont:_lbltitle.font constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
    if (labelsize.height < 32) {
        labelsize.height = 32;
    }
    self.popBackgroundView.frame = CGRectMake(35, h, labelsize.width + 30, labelsize.height + 8);
    
    self.leftLineImageView.frame = CGRectMake(20, 0, 3, self.bounds.size.height);
    
    _lbltitle.frame = CGRectMake(20, 4, labelsize.width, labelsize.height);
    boundsY += labelsize.height;
    
//    CGSize labelSize=[_lbltime.text sizeWithFont:_lbltime.font forWidth:150 lineBreakMode:UILineBreakModeWordWrap];
//    _lbltime.frame = CGRectMake(10.0, boundsY, labelSize.width, 25.0);
    
//    _typeImageView.frame = CGRectMake(CGRectGetMaxX(_lbltime.frame) + 15.0, boundsY + 5.0, _typeImageView.image.size.width, _typeImageView.image.size.height);
}


@end
