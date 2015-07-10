//
//  CMTextView.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-4-18.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTextView.h"
#import <CoreText/CoreText.h>
#import "tool.h"
@implementation CMTextView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];

    if (self) {
        if(__iOS5)
            isShowColor = NO;
        else
            isShowColor = YES;
        // Initialization code
        self.isLineFeed = YES;
    }
    return self;
    
}

-(void)setText:(NSString *)text
{
    [super setText:text];
    
    int len = [text length];
    
    if(text==nil)
        self.attriString = [[NSMutableAttributedString alloc]init];
    else
        self.attriString = [[NSMutableAttributedString alloc]initWithString:text];
    
    if (__iOS6) {
        if(self.textColor == nil)
            [self.attriString addAttribute:NSForegroundColorAttributeName value:[UIColor blackColor] range:NSMakeRange(0, len)];
        else
            [self.attriString addAttribute:NSForegroundColorAttributeName value:self.textColor range:NSMakeRange(0, len)];
        
        [self.attriString addAttribute:NSFontAttributeName value:self.font range:NSMakeRange(0, len)];
        self.attributedText = self.attriString;
    }
    else
    {
        [self.attriString addAttribute:(NSString *)(kCTForegroundColorAttributeName) value:(id)self.textColor.CGColor range:NSMakeRange(0, len)];
        CTFontRef ctFont2 = CTFontCreateWithName(( CFStringRef)self.font.fontName, self.font.pointSize,NULL);
        [self.attriString addAttribute:(NSString *)(kCTFontAttributeName) value:(__bridge  id)ctFont2 range:NSMakeRange(0, len)];
        CFRelease(ctFont2);
    }
    
}


-(void)setText:(NSString *)text WithFont:(UIFont *)font AndColor:(UIColor *)color{
    
    [super setText:text];
    
    [super setFont:font];
    
    int len = [text length];
    self.attriString = [[NSMutableAttributedString alloc]initWithString:text];
    
    if (__iOS6) {
        [self.attriString addAttribute:NSForegroundColorAttributeName value:color range:NSMakeRange(0, len)];
        
        [self.attriString addAttribute:NSFontAttributeName value:font range:NSMakeRange(0, len)];
        self.attributedText = self.attriString;
    }
    else
    {
        [self.attriString addAttribute:(NSString *)(kCTForegroundColorAttributeName) value:(id)color.CGColor range:NSMakeRange(0, len)];
        CTFontRef ctFont2 = CTFontCreateWithName(( CFStringRef)font.fontName, font.pointSize,NULL);
        [self.attriString addAttribute:(NSString *)(kCTFontAttributeName) value:(__bridge  id)ctFont2 range:NSMakeRange(0, len)];
        CFRelease(ctFont2);
    }
    
}
//只会变色第一次出现的keyword
-(void)setKeyWordTextArray:(NSArray *)keyWordArray WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor{
    
    
    NSMutableArray *rangeArray = [[NSMutableArray alloc]init];
    for (int i = 0; i < [keyWordArray count]; i++) {
        NSString *keyString = [keyWordArray objectAtIndex:i];
        NSRange range = [self.text rangeOfString:keyString];
        NSValue *value = [NSValue valueWithRange:range];
        if (range.length > 0) {
            [rangeArray addObject:value];
        }
    }
    
    if (!__iOS6) {
        for (NSValue *value in rangeArray) {
            NSRange keyRange = [value rangeValue];
            [self.attriString addAttribute:(NSString *)(kCTForegroundColorAttributeName) value:(id)keyWordColor.CGColor range:keyRange];
            CTFontRef ctFont1 = CTFontCreateWithName(( CFStringRef)font.fontName, font.pointSize,NULL);
            [self.attriString addAttribute:(NSString *)(kCTFontAttributeName) value:(__bridge  id)ctFont1 range:keyRange];
            CFRelease(ctFont1);
            }
        }
    else{
        for (NSValue *value in rangeArray) {
            NSRange keyRange = [value rangeValue];
            [self.attriString addAttribute:NSForegroundColorAttributeName value:keyWordColor range:keyRange];
            [self.attriString addAttribute:NSFontAttributeName value:font
                                     range:keyRange];
            
        }
        self.attributedText = self.attriString;
    }
    
    CMRELEASE(keyWordArray);
    
}
//会变色所有keyword
-(void)setAllKeyWordTextArray:(NSArray *)keyWordArray WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor{
    
    
    NSMutableArray *rangeArray = [[NSMutableArray alloc]init];
    NSString *sText = [[NSString stringWithString:self.text] lowercaseString];
    
    for (int i = 0; i < [keyWordArray count]; i++) {
        NSString *keyString = [[keyWordArray objectAtIndex:i] lowercaseString];
        
        NSArray * array = [sText componentsSeparatedByString:keyString];
        NSRange srange;
        srange.location = 0;
        srange.length   = [self.text length];
        
        //循环 累加计算 keyword 在self.text里的所有range
        for (int j = 0; j < [array count] - 1; j ++) {
            NSRange range  = [self.text rangeOfString:keyString options:NSCaseInsensitiveSearch range:srange];
            NSValue *value = [NSValue valueWithRange:range];
            if (range.length > 0) {
                [rangeArray addObject:value];
                srange.location = range.location + range.length;
                srange.length   = self.text.length - srange.location;
            }
        }
    }
    if (!__iOS6) {
        for (NSValue *value in rangeArray) {
            NSRange keyRange = [value rangeValue];
            [self.attriString addAttribute:(NSString *)(kCTForegroundColorAttributeName) value:(id)keyWordColor.CGColor range:keyRange];
            CTFontRef ctFont1 = CTFontCreateWithName(( CFStringRef)font.fontName, font.pointSize,NULL);
            [self.attriString addAttribute:(NSString *)(kCTFontAttributeName) value:(__bridge  id)ctFont1 range:keyRange];
            CFRelease(ctFont1);
        }
        
        //设置是否使用连字属性，这里设置为0，表示不使用连字属性。标准的英文连字有FI,FL.默认值为1，既是使用标准连字。也就是当搜索到f时候，会把fl当成一个文字。
        int nNumType = 0;
        CFNumberRef cfNum = CFNumberCreate(NULL, kCFNumberIntType, &nNumType);
        [self.attriString addAttribute:(NSString *)kCTLigatureAttributeName
                                 value:(__bridge id)cfNum
                                 range:NSMakeRange(0, self.text.length)];
        
        CFRelease(cfNum);
    }
    else{
        
        NSRange allRange;
        allRange.location=0;
        allRange.length=[self.text length];
        
        [self.attriString removeAttribute:NSForegroundColorAttributeName range:allRange];


        for (NSValue *value in rangeArray) {
            NSRange keyRange  = [value rangeValue];
            
            [self.attriString addAttribute:NSForegroundColorAttributeName value:keyWordColor range:keyRange];
            [self.attriString addAttribute:NSFontAttributeName value:font range:keyRange];
            
        }
        
        self.attributedText = self.attriString;
    }
    
    CMRELEASE(keyWordArray);
    
}


//当一段文字中可能有重复文字时 需要指定变色文字的范围 指定内容可能出现实际变色的文字和你想要的变色的文字不符合
-(void)setKeyWordRange:(NSRange)range WithFont:(UIFont *)font AndColor:(UIColor *)keyWordColor
{
    if (!__iOS6) {
        if (self.text.length >= range.location + range.length)
        {
            [self.attriString addAttribute:(NSString *)(kCTForegroundColorAttributeName) value:(id)keyWordColor.CGColor range:range];
            CTFontRef ctFont1 = CTFontCreateWithName(( CFStringRef)font.fontName, font.pointSize,NULL);
            [self.attriString addAttribute:(NSString *)(kCTFontAttributeName) value:(__bridge  id)ctFont1 range:range];
            CFRelease(ctFont1);
        }
    }
    else{
        if (self.text.length >= range.location + range.length)
        {
            [self.attriString addAttribute:NSForegroundColorAttributeName value:keyWordColor range:range];
            [self.attriString addAttribute:NSFontAttributeName value:font range:range];
        }
        self.attributedText = self.attriString;
    }
}


- (void)drawRect:(CGRect)rect
{
    
    if(isShowColor == NO)
    {
        [super drawRect:rect];
        return;
    }
    
    // Drawing code
    if (__iOS6) {
        [super drawRect:rect];
        return;
    }
    
    if (self.text !=nil && ![self.text isEqualToString:@""]) {
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSaveGState(context);
        CGContextTranslateCTM(context, 0.0, 0.0);//move
        CGContextScaleCTM(context, 1.0, -1.0);
        
        
        
        //创建文本行间距
        CGFloat lineSpace=2.0;//间距数据
        CTParagraphStyleSetting lineSpaceStyle;
        lineSpaceStyle.spec=kCTParagraphStyleSpecifierLineSpacing;//指定为行间距属性
        
        
        
        lineSpaceStyle.valueSize=sizeof(lineSpace);
        lineSpaceStyle.value=&lineSpace;
        
        //创建样式数组
        CTParagraphStyleSetting settings[]={
            lineSpaceStyle
        };
        
        //设置样式
        CTParagraphStyleRef paragraphStyle1 = CTParagraphStyleCreate(settings, sizeof(settings));
        
        //给字符串添加样式attribute
        [self.attriString addAttribute:(id)kCTParagraphStyleAttributeName
                                 value:(__bridge id)paragraphStyle1
                                 range:NSMakeRange(0, [self.text length])];
        
        CFRelease(paragraphStyle1);
        
        
        CGFloat widthValue = -1.0;
        
        CFNumberRef strokeWidth = CFNumberCreate(NULL,kCFNumberFloatType,&widthValue);
        
        [self.attriString addAttribute:(NSString*)(kCTStrokeWidthAttributeName) value:(__bridge id)strokeWidth range:NSMakeRange(0,[self.text length])];
        
        [self.attriString addAttribute:(NSString*)(kCTStrokeColorAttributeName) value:(id)[[UIColor whiteColor]CGColor] range:NSMakeRange(0,[self.text length])];
        
        
        CFRelease(strokeWidth);
        
        CTFramesetterRef framesetter = CTFramesetterCreateWithAttributedString((  CFAttributedStringRef)self.attriString);
        CGMutablePathRef pathRef = CGPathCreateMutable();
        CGPathAddRect(pathRef,NULL , CGRectMake(0, -1, self.bounds.size.width, self.bounds.size.height + 1));//const CGAffineTransform *m
        CTFrameRef frame = CTFramesetterCreateFrame(framesetter, CFRangeMake(0, 0), pathRef,NULL );//CFDictionaryRef frameAttributes
        CGContextTranslateCTM(context, 0, -self.bounds.size.height);
        CGContextSetTextPosition(context, 0, 0);
        
        
        
        
        CFArrayRef lines = CTFrameGetLines(frame);
        
        int lineNumber = CFArrayGetCount(lines);
        //一行显示不足时,末尾未...
        if (!self.isLineFeed) {
            CTLineRef line = CFArrayGetValueAtIndex(lines, 0);
            NSString * str = @"\u2026";
            NSMutableAttributedString *truncatedString = [[NSMutableAttributedString alloc]initWithString:str];
            [truncatedString addAttribute:(NSString *)(kCTForegroundColorAttributeName) value:(id)self.textColor.CGColor range:NSMakeRange(0, [str length])];
            
            CTFontRef ctFont2 = CTFontCreateWithName(( CFStringRef)self.font.fontName, self.font.pointSize,NULL);
            [truncatedString addAttribute:(NSString *)(kCTFontAttributeName) value:(__bridge  id)ctFont2 range:NSMakeRange(0, [str length])];
            CFRelease(ctFont2);
            
            CTLineRef token = CTLineCreateWithAttributedString((__bridge CFAttributedStringRef)truncatedString);
            
            
            CTLineTruncationType ltt = kCTLineTruncationEnd;
            
            CGPoint lineOrigin[0];
            
            CTLineRef newline = CTLineCreateTruncatedLine(line, self.bounds.size.width - 25, ltt, token);
            
            CGContextSetTextPosition(context,lineOrigin->x,lineOrigin->y + self.bounds.size.height - self.font.pointSize);
            
            CTLineDraw(newline,context);
        }
        else{
            CGPoint lineOrigins[lineNumber];
            
            CTFrameGetLineOrigins(frame,CFRangeMake(0,lineNumber), lineOrigins);
            
            for(int lineIndex = 0;lineIndex < lineNumber;lineIndex++){
                
                CGPoint lineOrigin = lineOrigins[lineIndex];
                
                CTLineRef line = CFArrayGetValueAtIndex(lines,lineIndex);
                
                CGContextSetTextPosition(context,lineOrigin.x,lineOrigin.y);
                
                CTLineDraw(line,context);
            }
        }
        
        
        
        CFRelease(frame);
        
        CGContextRestoreGState(context);
        CGPathRelease(pathRef);
        CFRelease(framesetter);
        UIGraphicsPushContext(context);
    }
    
}

-(void)dealloc
{
	self.attriString;
}


@end
