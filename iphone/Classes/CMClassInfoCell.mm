//
//  CMClassInfoCell.m
//  MLPlayer
//
//  Created by sunjj on 13-4-10.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMClassInfoCell.h"
#import "tool.h"

@implementation CMClassInfoCell
@synthesize className=_className;
@synthesize typeImage=_typeImage;
@synthesize isLearned=_isLearned;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        
        // Initialization code
      //  NSArray *nib=[[NSBundle mainBundle] loadNibNamed:@"CMClassInfoCellView" owner:self options:nil];
        self.contentView.backgroundColor=UIColorMakeRGBA(242.0f, 242.0f, 242.0f, 1);
       // self.backgroundColor=UIColorMakeRGBA(242.0f, 242.0f, 242.0f, 1);
        //self.className.text=@"hello";
    }
    return self;
}

-(id)initWithFrame:(CGRect)frame
{
    
    self = [super initWithFrame:frame];
    if (self) {
        
        // Initialization code
        //  NSArray *nib=[[NSBundle mainBundle] loadNibNamed:@"CMClassInfoCellView" owner:self options:nil];
        self.contentView.backgroundColor=UIColorMakeRGBA(242.0f, 242.0f, 242.0f, 1);
        self.backgroundColor=UIColorMakeRGBA(242.0f, 242.0f, 242.0f, 1);
        //self.className.text=@"hello";
    }
    return self;
    
    
}

-(void)setcellinfo:(TCoursewareItem&)citem{
    NSString*sType = [NSString stringWithUTF8String:citem.sType];
    
	if([sType rangeOfString:@"text"].location != NSNotFound)
		self.typeImage.image = [UIImage imageNamed:@"txt_icon"];
	else if([sType rangeOfString:@"video"].location != NSNotFound)
		self.typeImage.image = [UIImage imageNamed:@"video_icon"];
	else
		self.typeImage.image = [UIImage imageNamed:@"audio_icon"];
    
    self.isLearned.text = I(@"已学");
    self.isLearned.hidden = YES;
    self.isLearned.textColor=UIColorRGB(0xa7a7a7);
    
    if (citem.bIsLearned)
        self.isLearned.hidden = NO;
    
    self.className.text=[NSString stringWithUTF8String:citem.sTitle];
    


}


- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
