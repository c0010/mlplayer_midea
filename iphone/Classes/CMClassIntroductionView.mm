//
//  CMClassIntroductionView.m
//  MLPlayer
//
//  Created by wangjianbin on 15/6/12.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMClassIntroductionView.h"

@interface CMClassIntroductionView()
{
    UIScrollView *backScrollView;
    
    UITextField *textFieldAuthorName;
    UITextField *textFieldLanguage;
    UITextField *textFieldClassType;
    UITextField *textFieldClassLevel;
    UITextField *textFieldDevelopTime;
    UITextField *textFieldVersionCode;
    
    UILabel *labelIntroduction;
}

@end
@implementation CMClassIntroductionView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = kColorBackground;
        backScrollView = [[UIScrollView alloc]initWithFrame:frame];
        backScrollView.backgroundColor = [UIColor clearColor];
        backScrollView.scrollEnabled = YES;
        backScrollView.showsVerticalScrollIndicator = NO;
        [self addSubview:backScrollView];
        
        CGFloat edgeSpace = 21.0;
        UIFont *textFont = [UIFont systemFontOfSize:14];
        NSString *calStr = @"咔咔咔咔咔";
        CGSize labelSize = [calStr sizeWithFont:textFont];
        
        CGFloat yoff;
        
        yoff = edgeSpace;
        UILabel *labelAuthoName = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labelSize.width, labelSize.height)];
        labelAuthoName.font = textFont;
        labelAuthoName.textColor = [UIColor blackColor];
        labelAuthoName.text = I(@"作者：");
        
        
        textFieldAuthorName = [[UITextField alloc]initWithFrame:CGRectMake(edgeSpace, yoff, frame.size.width/2 - edgeSpace + 10, labelSize.height)];
        textFieldAuthorName.textColor = kColorGrayText;
        textFieldAuthorName.font = textFont;
        textFieldAuthorName.backgroundColor = [UIColor clearColor];
        textFieldAuthorName.enabled = NO;
        textFieldAuthorName.borderStyle = UITextBorderStyleNone;
        textFieldAuthorName.text = I(@"德玛西亚");
        
        textFieldAuthorName.leftView = labelAuthoName;
        textFieldAuthorName.leftViewMode = UITextFieldViewModeAlways;
        
        [backScrollView addSubview:textFieldAuthorName];
        
        UILabel *labelLanguage = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labelSize.width, labelSize.height)];
        labelLanguage.font = textFont;
        labelLanguage.textColor = [UIColor blackColor];
        labelLanguage.text = I(@"语言：");
        
        
        textFieldLanguage = [[UITextField alloc]initWithFrame:CGRectMake(textFieldAuthorName.frame.origin.x + textFieldAuthorName.frame.size.width, textFieldAuthorName.frame.origin.y, frame.size.width/2 - edgeSpace - 10, labelSize.height)];
        textFieldLanguage.font = textFont;
        textFieldLanguage.textColor = kColorGrayText;
        textFieldLanguage.backgroundColor = [UIColor clearColor];
        textFieldLanguage.enabled = NO;
        textFieldLanguage.borderStyle = UITextBorderStyleNone;
        textFieldLanguage.text = I(@"德玛西亚");
        
        textFieldLanguage.leftView = labelLanguage;
        textFieldLanguage.leftViewMode = UITextFieldViewModeAlways;
        
        [backScrollView addSubview:textFieldLanguage];
        
        
        yoff = yoff + labelSize.height + edgeSpace;
        UILabel *labelClassType = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labelSize.width, labelSize.height)];
        labelClassType.font = textFont;
        labelClassType.textColor = [UIColor blackColor];
        labelClassType.text = I(@"课程类别：");
        
        textFieldClassType = [[UITextField alloc]initWithFrame:CGRectMake(edgeSpace, yoff, frame.size.width/2 - edgeSpace + 10, labelSize.height)];
        textFieldClassType.textColor = kColorGrayText;
        textFieldClassType.font = textFont;
        textFieldClassType.backgroundColor = [UIColor clearColor];
        textFieldClassType.enabled = NO;
        textFieldClassType.borderStyle = UITextBorderStyleNone;
        textFieldClassType.text = I(@"德玛西亚");
        
        textFieldClassType.leftView = labelClassType;
        textFieldClassType.leftViewMode = UITextFieldViewModeAlways;
        
        [backScrollView addSubview:textFieldClassType];
        
        UILabel *labelClassLevel = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labelSize.width, labelSize.height)];
        labelClassLevel.font = textFont;
        labelClassLevel.textColor = [UIColor blackColor];
        labelClassLevel.text = I(@"课程级别：");
        
        
        textFieldClassLevel = [[UITextField alloc]initWithFrame:CGRectMake(textFieldClassType.frame.origin.x + textFieldClassType.frame.size.width, textFieldClassType.frame.origin.y, frame.size.width/2 - edgeSpace - 10, labelSize.height)];
        textFieldClassLevel.textColor = kColorGrayText;
        textFieldClassLevel.font = textFont;
        textFieldClassLevel.backgroundColor = [UIColor clearColor];
        textFieldClassLevel.enabled = NO;
        textFieldClassLevel.borderStyle = UITextBorderStyleNone;
        textFieldClassLevel.text = I(@"德玛西亚");
        
        textFieldClassLevel.leftView = labelClassLevel;
        textFieldClassLevel.leftViewMode = UITextFieldViewModeAlways;
        
        [backScrollView addSubview:textFieldClassLevel];
        
        
        yoff = yoff + labelSize.height + edgeSpace;
        UILabel *labelDevelopTime = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labelSize.width, labelSize.height)];
        labelDevelopTime.font = textFont;
        labelDevelopTime.textColor = [UIColor blackColor];
        labelDevelopTime.text = I(@"开发时间：");
        
        textFieldDevelopTime = [[UITextField alloc]initWithFrame:CGRectMake(edgeSpace, yoff, frame.size.width/2 - edgeSpace + 10, labelSize.height)];
        textFieldDevelopTime.textColor = kColorGrayText;
        textFieldDevelopTime.font = textFont;
        textFieldDevelopTime.backgroundColor = [UIColor clearColor];
        textFieldDevelopTime.enabled = NO;
        textFieldDevelopTime.borderStyle = UITextBorderStyleNone;
        textFieldDevelopTime.text = I(@"德玛西亚");
        
        textFieldDevelopTime.leftView = labelDevelopTime;
        textFieldDevelopTime.leftViewMode = UITextFieldViewModeAlways;
        
        [backScrollView addSubview:textFieldDevelopTime];
        
        UILabel *labelVersionCode = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labelSize.width, labelSize.height)];
        labelVersionCode.font = textFont;
        labelVersionCode.textColor = [UIColor blackColor];
        labelVersionCode.text = I(@"版本号：");
        
        
        textFieldVersionCode = [[UITextField alloc]initWithFrame:CGRectMake(textFieldDevelopTime.frame.origin.x + textFieldDevelopTime.frame.size.width, textFieldDevelopTime.frame.origin.y, frame.size.width/2 - edgeSpace - 10, labelSize.height)];
        textFieldVersionCode.textColor = kColorGrayText;
        textFieldVersionCode.font = textFont;
        textFieldVersionCode.backgroundColor = [UIColor clearColor];
        textFieldVersionCode.enabled = NO;
        textFieldVersionCode.borderStyle = UITextBorderStyleNone;
        textFieldVersionCode.text = I(@"德玛西亚");
        
        textFieldVersionCode.leftView = labelVersionCode;
        textFieldVersionCode.leftViewMode = UITextFieldViewModeAlways;
        
        [backScrollView addSubview:textFieldVersionCode];
        
        
        yoff = yoff + labelSize.height + edgeSpace;
        UILabel *introLabel = [[UILabel alloc]initWithFrame:CGRectMake(edgeSpace, yoff, labelSize.width, labelSize.height)];
        introLabel.text = I(@"简介：");
        introLabel.textColor = [UIColor blackColor];
        introLabel.font = textFont;
        
        [backScrollView addSubview:introLabel];
        
        
        yoff = yoff + labelSize.height + edgeSpace;
        labelIntroduction = [[UILabel alloc]initWithFrame:CGRectMake(edgeSpace, yoff, frame.size.width - edgeSpace * 2, frame.size.height)];
        labelIntroduction.textColor = kColorGrayText;
        labelIntroduction.font = textFont;
        labelIntroduction.numberOfLines = 0;
        labelIntroduction.backgroundColor = [UIColor clearColor];
        labelIntroduction.text = I(@"德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚德玛西亚");
        
        [backScrollView addSubview:labelIntroduction];
    }
    return self;
}

- (void)layoutSubviews
{
    textFieldAuthorName.text = self.authorName.length == 0 ? I(@"无") : self.authorName;
    textFieldLanguage.text = self.language.length == 0 ? I(@"无") : self.language;
    textFieldClassType.text = self.classType.length == 0 ? I(@"无") : self.classType;
    textFieldClassLevel.text = self.classLevel.length == 0 ? I(@"无") : self.classLevel;
    textFieldDevelopTime.text = self.developTime.length == 0 ? I(@"无") : self.developTime;
    textFieldVersionCode.text = self.versionCode.length == 0 ? I(@"无") : self.versionCode;
    labelIntroduction.text = self.introduction.length == 0 ? I(@"无") : self.introduction;
    
    CGSize textViewSize = [labelIntroduction.text sizeWithFont:[UIFont systemFontOfSize:14] constrainedToSize:CGSizeMake(self.frame.size.width - 42, MAXFLOAT) lineBreakMode:NSLineBreakByCharWrapping];
    CGRect f = labelIntroduction.frame;
    f.size = textViewSize;
    labelIntroduction.frame = f;
    
    CGSize scrollSize = CGSizeMake(CGRectGetWidth(backScrollView.frame), CGRectGetMaxY(labelIntroduction.frame));
    backScrollView.contentSize = scrollSize;
    
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
