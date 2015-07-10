//
//  FaceButton.m
//
//  Created by blue on 12-9-26.
//  Copyright (c) 2012年 blue. All rights reserved.
//  Email - 360511404@qq.com
//  http://github.com/bluemood
//

#import "FaceButton.h"
#define TSEMOJIVIEW_COLUMNS 7
#define TSKEYTOP_SIZE 55
#define TSEMOJI_SIZE 30

@interface FaceButton()

@end

@implementation FaceButton
@synthesize image       = _image;
@synthesize delegate = _delegate;
@synthesize touchedIndex = _touchedIndex;
@synthesize emojiImages = _emojiImages;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
      //  _emojiDictionary = [[NSUserDefaults standardUserDefaults] objectForKey:@"FaceMap"];

        //背景透明
        [self setBackgroundColor:[UIColor clearColor]];
    }
    return self;
}

- (void)dealloc
{
    _delegate = nil;

}

- (void)drawRect:(CGRect)rect
{
    for (int i = 1; i <= 89; i++) {
        UIImage *image;
        
        if ((i % 28 ) == 0 || i == 89) {
            image = [UIImage imageNamed:@"backFace"];
        }else{
            int mul = i/28;
        
            NSInteger index = i - mul - 1;
            
            if (index >= 0 && index < [_emojiImages count]) {
                image = [_emojiImages objectAtIndex:index];//[UIImage imageNamed:[NSString stringWithFormat:@"%03d",i - mul]];
            }

        }
 
      [image drawInRect:CGRectMake((((i-1)%28)%7)*45+8+((i-1)/28*320), (((i-1)%28)/7)*45+8, 30, 30)];
       
    }
}

- (void)preparEmojiImages{
    if (_emojiImages) {
        _emojiImages = nil;
    }
    _emojiImages = [[NSMutableArray alloc] initWithCapacity:85];
    for (int i = 0; i<85; i++) {

        UIImage *image = [UIImage imageNamed:[NSString stringWithFormat:@"%03d",i + 1]];
        
        if (image) {
            [_emojiImages addObject:image];
        }
    }
}

#pragma mark -
#pragma mark Actions
- (NSUInteger)indexWithEvent:(UIEvent*)event
{
    UITouch* touch = [[event allTouches] anyObject];
    CGFloat touchX = [touch locationInView:self].x;
    CGFloat touchY = [touch locationInView:self].y;
    if (touchY > 173.0) {
        touchY = 170.0;
    }
   
    NSUInteger multipleX = touchX/320;
    CGFloat    remainderX = (NSUInteger)touchX%320;
 //   NSLog(@"mul x:%d, remainder x:%f",multipleX,remainderX);
    
    NSUInteger x = remainderX / (320.0 / TSEMOJIVIEW_COLUMNS) + multipleX * 28;
    NSUInteger y = touchY / (320.0 / TSEMOJIVIEW_COLUMNS);
  //  NSLog(@"mul y:%f, remainder y:%d",[touch locationInView:self].y,y);

    return x + (y * TSEMOJIVIEW_COLUMNS);
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSUInteger index = [self indexWithEvent:event];  //图片从001开始
    if(index < 89) {
        
//        if ((index % 28 ) == 0) {
//        }else{
//            int mul = index/28;
//            index = mul - 1;
//        }
        
        _touchedIndex = index;
        if ([self.delegate respondsToSelector:@selector(didTouchEmojiViewBeganIndex:)]) {
            [self.delegate didTouchEmojiViewBeganIndex:index];
        }

    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSUInteger index = [self indexWithEvent:event];
    if (_touchedIndex >= 0 && index != _touchedIndex && index < 89) {
        
//        if ((index % 28 ) == 0) {
//        }else{
//            int mul = index/28;
//            index = mul - 1;
//        }
        
        
        _touchedIndex = index;

        if ([self.delegate respondsToSelector:@selector(didTouchEmojiViewMovedIndex:)]) {
            [self.delegate didTouchEmojiViewMovedIndex:index];
        }
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.delegate && _touchedIndex >= 0) {
        if ([self.delegate respondsToSelector:@selector(didTouchEmojiView:touchedEmoji:)]) {
            [self.delegate didTouchEmojiView:self touchedEmoji:nil];
        }
    }
    _touchedIndex = -1;
    [self setNeedsDisplay];
}

@end
