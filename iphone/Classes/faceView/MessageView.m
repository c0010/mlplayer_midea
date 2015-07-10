//
//  MessageView.m
//  FaceBoardDome
//
//  Created by kangle1208 on 13-12-12.
//  Copyright (c) 2013年 Blue. All rights reserved.
//

#import "MessageView.h"
#import <CoreText/CoreText.h>

#import "FaceBoard.h"
#import "NSArray+CBExtension.h"
#import "tool.h"
//@"\\[[\\w]{1,3}\\]"
#define FACE_ICON_NAME      @"^[0][0-8][0-5]$"
#define EmotionItemPattern         @"\\[[a-zA-Z0-9\\u4e00-\\u9fa5]+\\]"
#define BEGIN_FLAG @"["
#define END_FLAG @"]"
#define PlaceHolder                 @" "
#define EmotionFileType             @"png"
#define AttributedImageNameKey      @"ImageName"

#define EmotionImageWidth           21
#define FontHeight                  16
#define ImageLeftPadding            0.0
#define ImageTopPadding             2.0


@implementation MessageView{
    dispatch_queue_t queue;
    dispatch_group_t group;
    CTTypesetterRef typesetter;
}

@synthesize text,messageSize;
@synthesize faceMap = _faceMap;
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        ;
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame emotionString:(NSString *)emotionString
{
    self = [super initWithFrame:frame];
    if (self) {
        text = [[NSString alloc]initWithString:emotionString];
        [self setup];
    }
    return self;
}

- (id)init
{
    @synchronized(self) {
        self = [super init];
        _emotionNames = [[NSMutableArray alloc]initWithCapacity:10];
        queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        group = dispatch_group_create();
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        if ([defaults objectForKey:@"FaceMap"]) {
            _faceMap = [defaults objectForKey:@"FaceMap"];
        }
        else{
           _faceMap = [[NSDictionary alloc]initWithContentsOfFile:[[NSBundle mainBundle]pathForResource:@"faceMap_ch" ofType:@"plist"]];
       }
        self.opaque = NO;
        return self;
    }
}

- (void)setText:(NSString *)message {
    if (!message) {
        return;
    }
    else{
        text = [[NSString alloc] initWithString:message];
        [self setup];
    }
}

- (void)setup
{
    [self prepare];
}

- (void)prepare
{
    if (_emotionNames) {
        [_emotionNames removeAllObjects];
    }
    if (_emotionRanges) {
        _emotionRanges = nil;
    }
    if (_messageRange) {
        [_messageRange removeAllObjects];
        _messageRange = nil;;
    }
    _messageRange = [[NSMutableArray alloc] init];
    
    [self cookEmotionString];
}


#pragma mark - Cook the emotion string
- (void)cookEmotionString
{
    [self getMessageRange:text :_messageRange];
    [self setNeedsDisplay];

}



#pragma mark - Drawing
- (void)drawRect:(CGRect)rect
{
//    if( [_messageRange count]==1){
//        if (![text hasPrefix:BEGIN_FLAG] && ![text hasSuffix:END_FLAG])
//            [super drawRect:rect];
//        return;
//    }
    if ( _messageRange ) {
        
        UIFont *font = [UIFont systemFontOfSize:FontHeight];
        
        isLineReturn = NO;
        
        upX = VIEW_LEFT;
        upY = VIEW_TOP;
        
		for (int index = 0; index < [_messageRange count]; index++) {
            
			NSString *str = [_messageRange objectAtIndex:index];
			if ( [str hasPrefix:BEGIN_FLAG] && [str hasSuffix:END_FLAG]) {
                
				//NSString *imageName = [str substringWithRange:NSMakeRange(1, str.length - 2)];
                
                NSArray *imageNames = [_faceMap allKeysForObject:str];
                NSString *imageName = nil;
                
                if ( imageNames.count > 0 ) {
                    
                    imageName = [imageNames objectAtIndex:0];
                }
                
                UIImage *image = [UIImage imageNamed:imageName];
                
                if ( image ) {
                    
                    if ( upX > ( VIEW_WIDTH_MAX - EmotionImageWidth ) ) {
                        
                        isLineReturn = YES;
                        
                        upX = VIEW_LEFT;
                        upY += VIEW_LINE_HEIGHT;
                    }
                    
                    [image drawInRect:CGRectMake(upX, upY - 2, EmotionImageWidth, EmotionImageWidth)];
                    
                    upX += EmotionImageWidth;
                    
                    lastPlusSize = EmotionImageWidth;
                }
                else {
                    [self drawText:str withFont:font index:index];
                }
			}
            else {
                
                [self drawText:str withFont:font index:index];
			}
        }
	}

}

- (void)drawText:(NSString *)string withFont:(UIFont *)font index:(NSInteger)_index{
    for ( int index = 0; index < string.length; index++) {
        
        NSString *character = [string substringWithRange:NSMakeRange( index, 1 )];
        
        CGSize size = [character sizeWithFont:font];
        
        NSString *key = [NSString stringWithFormat:@"%d%d",_index,index];

        if ([_emojiRanges objectForKey:key]) {
            NSRange range = [[_emojiRanges objectForKey:key] rangeValue];
            character = [string substringWithRange:NSMakeRange( range.location, range.length)];

            if (range.length == 2) {
                index ++;
            }
            size = [character sizeWithFont:font];
          //  size.width = 20;
        }

        if ( upX > ( VIEW_WIDTH_MAX -  size.width ) ) {
            
            isLineReturn = YES;
            
            upX = VIEW_LEFT;
            upY += VIEW_LINE_HEIGHT;
        }
        [self.textColor set];

        [character drawInRect:CGRectMake(upX, upY, size.width, self.bounds.size.height) withFont:font];
        
        upX += size.width;
        
        lastPlusSize = size.width;
    }
}



/**
 * 解析输入的文本
 *
 * 根据文本信息分析出哪些是表情，哪些是文字
 */
- (void)getMessageRange:(NSString*)message :(NSMutableArray*)array {
    NSRange range=[message rangeOfString: BEGIN_FLAG];
    NSRange range1=[message rangeOfString: END_FLAG];
    //判断当前字符串是否还有表情的标志。
    if (range.length>0 && range1.length>0 && range.location < range1.location) {
        if (range.location > 0) {
            
            [array addObject:[message substringToIndex:range.location]];
            [array addObject:[message substringWithRange:NSMakeRange(range.location, range1.location+1-range.location)]];
            NSString *str=[message substringFromIndex:range1.location+1];
            [self getMessageRange:str :array];
        }else {
            NSString *nextstr=[message substringWithRange:NSMakeRange(range.location, range1.location+1-range.location)];
            //排除文字是“”的
            if (![nextstr isEqualToString:@""]) {
                [array addObject:nextstr];
                NSString *str=[message substringFromIndex:range1.location+1];
                [self getMessageRange:str :array];
            }else {
                return;
            }
        }
        
    } else if (message != nil) {
        [array addObject:message];
    }
}


/**
 *  获取文本尺寸
 */
- (CGSize)getContentSizeWithMessage:(NSString *)message {
    
    @synchronized ( self ) {
        if (!message || [message length] == 0) {
            return CGSizeZero;
        }
        
        NSMutableArray *messageRange = _messageRange;

        CGFloat _upX;
        
        CGFloat _upY;
        
        CGFloat _lastPlusSize;
        
        CGFloat _viewWidth;
        
        CGFloat _viewHeight;
        
        BOOL _isLineReturn;
        
        
//        CFTimeInterval startTime = CACurrentMediaTime();

        UIFont *font = [UIFont systemFontOfSize:FontHeight];
        
        _isLineReturn = NO;
        
        _upX = VIEW_LEFT;
        _upY = VIEW_TOP;
        
        for (int index = 0; index < [messageRange count]; index++) {
            
            NSString *str = [messageRange objectAtIndex:index];
            [self getstringContainsEmojiCount:str index:index];
            if ( [str hasPrefix:BEGIN_FLAG] && [str hasSuffix:END_FLAG]) {
                
                NSArray *imageNames = [_faceMap allKeysForObject:str];
                NSString *imageName = nil;
                NSString *imagePath = nil;
                
                if ( imageNames.count > 0 ) {
                    
                    imageName = [NSString stringWithFormat:@"%@@2x",[imageNames objectAtIndex:0]];
                    imagePath = [[NSBundle mainBundle] pathForResource:imageName ofType:@"png"];
                }
                
                if ( imagePath ) {
                    
                    if ( _upX > ( VIEW_WIDTH_MAX - EmotionImageWidth ) ) {
                        
                        _isLineReturn = YES;
                        
                        _upX = VIEW_LEFT;
                        _upY += VIEW_LINE_HEIGHT;
                    }
                    
                    _upX += EmotionImageWidth;
                    
                    _lastPlusSize = EmotionImageWidth;
                }
                else {
                    for ( int i = 0; i < str.length; i++) {
                        
                        NSString *character = [str substringWithRange:NSMakeRange( i, 1 )];
                        
                        CGSize size = [character sizeWithFont:font
                                            ];
                        
                        NSString *key = [NSString stringWithFormat:@"%d%d",index,i];
                        if ([_emojiRanges objectForKey:key]) {
                            NSRange range = [[_emojiRanges objectForKey:key] rangeValue];
                            character = [str substringWithRange:NSMakeRange( range.location, range.length)];
                            
                            if (range.length == 2) {
                                i ++;
                            }
                            size = [character sizeWithFont:font];

                        }
                        
                        //ios7以下，emoji表情宽度无法计算,避免布局混乱，强行给他18的宽度
                        if (size.width == 0) {
                            size.width = KFacialSizeWidth;
                        }
                        if ( _upX > ( VIEW_WIDTH_MAX - size.width ) ) {
                            
                            _isLineReturn = YES;
                            
                            _upX = VIEW_LEFT;
                            _upY += VIEW_LINE_HEIGHT;
                        }
                      
                        
                        _upX += size.width;
                        
                        _lastPlusSize = size.width;
                    }
                }
            }
            else {

                for ( int i = 0; i < str.length; i++) {
                    NSString *character = [str substringWithRange:NSMakeRange( i, 1 )];
                    
                    CGSize size = [character sizeWithFont:font
                                   ];
                    
                    NSString *key = [NSString stringWithFormat:@"%d%d",index,i];

                    if ([_emojiRanges objectForKey:key]) {
                        NSRange range = [[_emojiRanges objectForKey:key] rangeValue];
                        character = [str substringWithRange:NSMakeRange( range.location, range.length)];

                        if (range.length == 2) {
                            i ++;
                        }
                        size = [character sizeWithFont:font];
                    }
                    
                    //ios7一下，emoji表情宽度无法计算,避免布局混乱，强行给他18的宽度
                    if (size.width == 0) {
                        size.width = KFacialSizeWidth;
                    }
                    if ( _upX > ( VIEW_WIDTH_MAX - size.width ) ) {
                        
                        _isLineReturn = YES;
                        
                        _upX = VIEW_LEFT;
                        _upY += VIEW_LINE_HEIGHT;
                    }
                   
                    
                    _upX += size.width;
                    
                    _lastPlusSize = size.width;
                }
            }
        }
        
        if ( _isLineReturn ) {
            
            _viewWidth = VIEW_WIDTH_MAX + VIEW_LEFT * 2;
        }
        else {
            
            _viewWidth = _upX + VIEW_LEFT;
        }
        
        _viewHeight = _upY + VIEW_LINE_HEIGHT - VIEW_TOP;
        
        NSValue *sizeValue = [NSValue valueWithCGSize:CGSizeMake( _viewWidth, _viewHeight )];
        
//        CFTimeInterval endTime = CACurrentMediaTime();
        msgSize = [sizeValue CGSizeValue];
        
        
        return msgSize;
    }
}

//判断是否有emoji表情
- (NSUInteger)getstringContainsEmojiCount:(NSString *)string index:(NSInteger)_index{
    __block BOOL returnValue = NO;
    __block NSInteger count = 0;
    if (_emojiRanges) {
        [_emojiRanges removeAllObjects];
        _emojiRanges = nil;
    }
    _emojiRanges = [[NSMutableDictionary alloc] init];
    
    [string enumerateSubstringsInRange:NSMakeRange(0, [string length]) options:NSStringEnumerationByComposedCharacterSequences usingBlock:
     ^(NSString *substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop) {
         const unichar hs = [substring characterAtIndex:0];
         if (0xd800 <= hs && hs <= 0xdbff) {
             if (substring.length > 1) {
                 const unichar ls = [substring characterAtIndex:1];
                 const int uc = ((hs - 0xd800)*0x400) + (ls - 0xdc00) + 0x10000;
                 if (0x1d000 <= uc && uc <= 0x1f77f) {
                     returnValue = YES;
                     count++;
                     NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                     [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
                 }
             }
         }
         else if (substring.length > 1){
             const unichar ls = [substring characterAtIndex:1];
             if (ls == 0x20e3) {
                 returnValue = YES;
                 count++;
                 NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                 [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
             }
         }
         else{
             if (0x2100 <= hs && hs <= 0x27ff) {
                 returnValue = YES;
                 count++;
                 NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                 [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
             }
             else if (0x2B05 <= hs && hs <= 0x2b07){
                 returnValue = YES;
                 count++;
                 NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                 [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
             }
             else if (0x2934 <= hs && hs <= 0x2935){
                 returnValue = YES;
                 count++;
                 NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                 [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
                 
             }
             else if (0x3297 <= hs && hs <= 0x3299){
                 returnValue = YES;
                 count++;
                 NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                 [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
             }
             else if (hs == 0xa9 || hs == 0xae || hs == 0x303d || hs == 0x3030 || hs == 0x2b55 || hs == 0x2b1c || hs == 0x2b1b || hs == 0x2b50){
                 returnValue = YES;
                 count++;
                 NSString *key = [NSString stringWithFormat:@"%d%d",_index,substringRange.location];
                 [_emojiRanges setObject:[NSValue valueWithRange:substringRange] forKey:key];
             }
         }
     }];
    return count;
}


/**
 * 判断字符串是否有效
 */
- (BOOL)isStrValid:(NSString *)srcStr forRule:(NSString *)ruleStr {
    
    NSRegularExpression *regularExpression = [[NSRegularExpression alloc] initWithPattern:ruleStr
                                                                                  options:NSRegularExpressionCaseInsensitive
                                                                                    error:nil];
    
    NSUInteger numberOfMatch = [regularExpression numberOfMatchesInString:srcStr
                                                                  options:NSMatchingReportProgress
                                                                    range:NSMakeRange(0, srcStr.length)];
    
    return ( numberOfMatch > 0 );
}

- (void)dealloc {
    if (typesetter) {
        CFRelease(typesetter);
    }
//    if (!__iOS6) {
//        dispatch_release(group);    // iOS 6.0 以下需要手动释放
//    }
}

@end
