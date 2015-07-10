//
//  FaceBoard.m
//
//  Created by blue on 12-9-26.
//  Copyright (c) 2012年 blue. All rights reserved.
//  Email - 360511404@qq.com
//  http://github.com/bluemood

#import "FaceBoard.h"

#define TSEMOJIVIEW_COLUMNS 7
#define TSEMOJIVIEW_KEYTOP_WIDTH 87
#define TSEMOJIVIEW_KEYTOP_HEIGHT 112
#define TSKEYTOP_SIZE 55
#define TSEMOJI_SIZE 45
//==============================================================================
// FaceButtonLayer
//==============================================================================
@interface FaceButtonLayer : CALayer {
@private
    CGImageRef _keytopImage;;
}
@property (nonatomic, strong) UIImage* emoji;
@end

@implementation FaceButtonLayer
@synthesize emoji = _emoji;

- (id)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)dealloc
{
    _keytopImage = nil;
}

- (void)drawInContext:(CGContextRef)context
{
    //从后台返回需要重新获取图片,Fixes Bug
    _keytopImage = [[UIImage imageNamed:@"emoji_touch"] CGImage];
    
    UIGraphicsBeginImageContext(CGSizeMake(TSEMOJIVIEW_KEYTOP_WIDTH, TSEMOJIVIEW_KEYTOP_HEIGHT));
    CGContextTranslateCTM(context, 0.0, TSEMOJIVIEW_KEYTOP_HEIGHT);
    CGContextScaleCTM(context, 1.0, -1.0);
    CGContextDrawImage(context, CGRectMake(0, 2, TSEMOJIVIEW_KEYTOP_WIDTH, TSEMOJIVIEW_KEYTOP_HEIGHT), _keytopImage);
    UIGraphicsEndImageContext();
    
    //
    UIGraphicsBeginImageContext(CGSizeMake(TSKEYTOP_SIZE, TSKEYTOP_SIZE));
    CGContextDrawImage(context, CGRectMake((TSEMOJIVIEW_KEYTOP_WIDTH - TSKEYTOP_SIZE) / 2 , 45, TSKEYTOP_SIZE, TSKEYTOP_SIZE), [_emoji CGImage]);
    UIGraphicsEndImageContext();
}

@end

@interface FaceBoard() {
    NSInteger _touchedIndex;
    FaceButtonLayer *_emojiPadLayer;
}
@end

@implementation FaceBoard
@synthesize inputTextField = _inputTextField;
@synthesize inputTextView = _inputTextView;
@synthesize delegate;


+ (FaceBoard*)sharedFaceBoard
{
    static FaceBoard *sharedFB;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedFB = [[self alloc] init];
    });
    
    return sharedFB;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:CGRectMake(0, 0, 320, 216)];
    if (self) {
        self.backgroundColor = [UIColor colorWithRed:243.0/255.0 green:243.0/255.0 blue:243.0/255.0 alpha:1];
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
  
        _faceMap = [NSDictionary dictionaryWithContentsOfFile:[[NSBundle mainBundle]pathForResource:@"faceMap_ch" ofType:@"plist"]];
        [defaults setObject:_faceMap forKey:@"FaceMap"];

        //表情盘
        faceView = [[UIScrollView alloc]initWithFrame:CGRectMake(0, 10, 320, 190)];
        faceView.pagingEnabled = YES;
        faceView.contentSize = CGSizeMake((85/28+1)*320, 190);
        faceView.showsHorizontalScrollIndicator = NO;
        faceView.showsVerticalScrollIndicator = NO;
        faceView.delegate = self;
        

        FaceButton *faceButton = [[FaceButton alloc]init];
        [faceButton preparEmojiImages];

        
            //计算每一个表情按钮的坐标和在哪一屏
          //  faceButton.frame = CGRectMake((((i-1)%28)%7)*44+6+((i-1)/28*320), (((i-1)%28)/7)*44+8, 44, 44);
        faceButton.frame = CGRectMake(0.0, 0.0, (85/28+1)*320, 190);
        faceButton.delegate = self;
           // [faceButton setImage:[UIImage imageNamed:[NSString stringWithFormat:@"%03d",i]] forState:UIControlStateNormal];
           // faceButton.image = [UIImage imageNamed:[NSString stringWithFormat:@"%03d",i]];
            [faceView addSubview:faceButton];
       // }
        
        //添加PageControl
        facePageControl = [[GrayPageControl alloc]initWithFrame:CGRectMake(110, 190, 100, 20)];
        
        [facePageControl addTarget:self
                            action:@selector(pageChange:)
                  forControlEvents:UIControlEventValueChanged];
        
        facePageControl.numberOfPages = 85/28+1;
        facePageControl.currentPage = 0;
        [self addSubview:facePageControl];
        
        //添加键盘View
        [self addSubview:faceView];
        
        //删除键
        UIButton *back = [UIButton buttonWithType:UIButtonTypeCustom];
        [back setTitle:I(@"删除") forState:UIControlStateNormal];
        [back setImage:[UIImage imageNamed:@"backFace"] forState:UIControlStateNormal];
        [back setImage:[UIImage imageNamed:@"backFaceSelect"] forState:UIControlStateSelected];
        [back addTarget:self action:@selector(backFace) forControlEvents:UIControlEventTouchUpInside];
        back.frame = CGRectMake(270, 185, 38, 27);
//        [self addSubview:back];
        
        //点击Layer
        _emojiPadLayer = [FaceButtonLayer layer];
        [self.layer addSublayer:_emojiPadLayer];
        
    }
    return self;
}

- (void)didTouchEmojiViewBeganIndex:(NSInteger)index{
    if ((index+1)%28 != 0 && index != 88) {
        [CATransaction begin];
        [CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];
        faceView.scrollEnabled = NO;
        [self updateWithIndex:index];
        [CATransaction commit];
    }
}

- (void)didTouchEmojiViewMovedIndex:(NSInteger)index{
    [self updateWithIndex:index];
}

- (void)didTouchEmojiView:(FaceButton*)emojiView touchedEmoji:(NSString*)string{
    faceView.scrollEnabled = YES;
    _emojiPadLayer.opacity = 0.0;
    [_emojiPadLayer setNeedsDisplay];

    int i = emojiView.touchedIndex + 1;
    if (i%28 == 0 || i == 89) {
        [self backFace];
    }else{
        
        i = i - (i/28);

        if (self.inputTextField) {
            NSMutableString *faceString = [[NSMutableString alloc]initWithString:self.inputTextField.text];
            [faceString appendString:[_faceMap objectForKey:[NSString stringWithFormat:@"%03d",i]]];
            self.inputTextField.text = faceString;
        }
        if (self.inputTextView) {
            NSMutableString *faceString = [[NSMutableString alloc]initWithString:self.inputTextView.text];
            [faceString appendString:[_faceMap objectForKey:[NSString stringWithFormat:@"%03d",i]]];
            self.inputTextView.text = faceString;
            
            [delegate textViewDidChange:self.inputTextView];
        }
    }
    
}

- (void)updateWithIndex:(NSUInteger)index
{

    if (_emojiPadLayer.opacity != 1.0) {
        _emojiPadLayer.opacity = 1.0;
    }
    
    NSUInteger page = (index + 1)%28 - 1;
    if (page == -1) {
        page = 27;
    }
    
    float originX = (320 / TSEMOJIVIEW_COLUMNS) * (index % TSEMOJIVIEW_COLUMNS) + ((320 / TSEMOJIVIEW_COLUMNS) - TSEMOJI_SIZE ) / 2;
    float originY = (page / TSEMOJIVIEW_COLUMNS) * (320 / TSEMOJIVIEW_COLUMNS) + ((320 / TSEMOJIVIEW_COLUMNS) - TSEMOJI_SIZE ) / 2;
    
    
    index = index - (index/28);

    [_emojiPadLayer setEmoji:[UIImage imageNamed:[NSString stringWithFormat:@"%03d",index + 1]]];
    [_emojiPadLayer setFrame:CGRectMake(originX - (TSEMOJIVIEW_KEYTOP_WIDTH - TSEMOJI_SIZE) / 2, originY - (TSEMOJIVIEW_KEYTOP_HEIGHT - TSEMOJI_SIZE), TSEMOJIVIEW_KEYTOP_WIDTH, TSEMOJIVIEW_KEYTOP_HEIGHT)];

    [_emojiPadLayer setNeedsDisplay];
}

//停止滚动的时候
-(void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView{
    [facePageControl setCurrentPage:faceView.contentOffset.x/320];
    [facePageControl updateCurrentPageDisplay];
}

- (void)pageChange:(id)sender {
    [faceView setContentOffset:CGPointMake(facePageControl.currentPage*320, 0) animated:YES];
    [facePageControl setCurrentPage:facePageControl.currentPage];
}



- (void)faceButton:(id)sender {

}

- (void)backFace{
    NSString *inputString;
    inputString = self.inputTextField.text;
    if (self.inputTextView) {
        inputString = self.inputTextView.text;
    }
    
    NSString *string = nil;
    NSInteger stringLength = inputString.length;
    if (stringLength > 0) {
        if ([@"]" isEqualToString:[inputString substringFromIndex:stringLength-1]]) {
            if ([inputString rangeOfString:@"["].location == NSNotFound){
                string = [inputString substringToIndex:stringLength - 1];
            } else {
                NSString *bStr = [inputString substringFromIndex:[inputString rangeOfString:@"[" options:NSBackwardsSearch].location];
                if ( [_faceMap.allValues containsObject:bStr] ) {
                    
                    string = [inputString substringToIndex:[inputString rangeOfString:@"[" options:NSBackwardsSearch].location];
                }else{
                    
                    string = [inputString substringToIndex:stringLength - 1];
                }
            }
        }
        else {
            string = [inputString substringToIndex:stringLength - 1];
        }
        if ( self.inputTextField ) {
            
            self.inputTextField.text = string;
        }
        
        if ( self.inputTextView ) {
            
            self.inputTextView.text = string;
            
            [delegate textViewDidChange:self.inputTextView];
        }
    }
    //    self.inputTextField.text = string;
    //    self.inputTextView.text = string;
}

@end
