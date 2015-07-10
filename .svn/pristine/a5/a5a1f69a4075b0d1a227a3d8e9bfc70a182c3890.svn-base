//
//  CMImagePreviewView.m
//  MLPlayer
//
//  Created by hushengwu on 13-8-16.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMImagePreviewView.h"
#import <QuartzCore/QuartzCore.h>
#import "SDWebImage/UIImageView+WebCache.h"
#import "SDWebImage/SDImageCache.h"
#import "CMViewController.h"

#define kDeviceWidth                [UIScreen mainScreen].bounds.size.width
#define KDeviceHeight               [UIScreen mainScreen].bounds.size.height
@implementation CMImagePreviewView
@synthesize toolbar = _toolbar;
@synthesize delegate = _delegate;
@synthesize isShowToolbar;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        //self.frame = CGRectMake(0, 0, kScreenWidth, kScreenHeight);
        _imageScrollView = [[UIScrollView alloc] init];
        _imageScrollView.delegate = self;
        _imageScrollView.bounces = YES;
        _imageScrollView.showsHorizontalScrollIndicator = NO;
        _imageScrollView.showsVerticalScrollIndicator = NO;
        //_imageScrollView.frame = CGRectMake(0, 0, kScreenWidth, kScreenHeight);
        _imageScrollView.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.9];
        [self addTapGesture];
        [self addSubview:_imageScrollView];
        _previewImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
        _previewImageView.contentMode = UIViewContentModeScaleAspectFit;
        [_imageScrollView addSubview:_previewImageView];
    }
    return self;
}

#pragma mark - InitView methods

- (void)initPreivewImageView
{
    [self resetLayoutByPreviewImageView];
}

- (void)initToolBar
{
    _toolbar = [[UIView alloc]initWithFrame:CGRectMake(0.0, KDeviceHeight - 70.0, 320.0, 50.0)];
    _toolbar.backgroundColor = [UIColor clearColor];
    
    UIImageView *bg_img = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"photo_toolbar"]];
    bg_img.userInteractionEnabled = YES;
    [_toolbar addSubview:bg_img];
    
    UIButton *back_btn = [[UIButton alloc]initWithFrame:CGRectMake(15.0, 10.0, 49.0, 30.0)];
    [back_btn setBackgroundImage:[UIImage imageNamed:@"goback_normal"] forState:UIControlStateNormal];
    [back_btn setBackgroundImage:[UIImage imageNamed:@"goback_select"] forState:UIControlStateHighlighted];
    [back_btn.titleLabel setFont:[UIFont systemFontOfSize:15.0]];
    [back_btn setTitle:I(@"返回") forState:UIControlStateNormal];
    [back_btn addTarget:self action:@selector(handleSingleTap:) forControlEvents:UIControlEventTouchUpInside];
    [_toolbar addSubview:back_btn];
    
    UIButton *delect_btn = [[UIButton alloc]initWithFrame:CGRectMake(270.0, 10.0, 30.0, 30.0)];
    [delect_btn setBackgroundImage:[UIImage imageNamed:@"delect_normal"] forState:UIControlStateNormal];
    [delect_btn setBackgroundImage:[UIImage imageNamed:@"delect_select"] forState:UIControlStateHighlighted];
    [delect_btn addTarget:self action:@selector(delectPreviewImage:) forControlEvents:UIControlEventTouchUpInside];
    [_toolbar addSubview:delect_btn];

    [self addSubview:_toolbar];
  

}
//在图片上加tap，点击后退出预览
- (void)addTapGesture
{
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleSingleTap:)];
    [_imageScrollView addGestureRecognizer:tapGesture];
}
- (void)initImageWithURL:(NSString *)url thumbURL:(NSString *)thumburl{
    _previewWidth = kDeviceWidth;
    
    if (__iOS7)
    {
        _previewHeight = KDeviceHeight;
    }
    else
    {
        _previewHeight = KDeviceHeight - 20;
    }
    
    [self initPreivewImageView];
    CGPoint center = self.center;
    activityview = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    activityview.center = center;
    [self addSubview:activityview];
    [activityview startAnimating];

    SDWebImageManager *manager = [SDWebImageManager sharedManager];
    UIImage *thumbImage = [[SDImageCache sharedImageCache] imageFromMemoryCacheForKey:thumburl];
    _previewImageView.image = thumbImage;
    
    UIImage *cachedImage =[[SDImageCache sharedImageCache] imageFromMemoryCacheForKey:url];// 将需要缓存的图片加载进来
    if (cachedImage) {
        [activityview stopAnimating];
        _previewImageView.image = cachedImage;
        [self configPreviewImageViewWithImage:_previewImageView.image];

    }else {
        // 如果Cache没有命中，则去下载指定网络位置的图片，并且给出一个委托方法
        // Start an async download
       // _previewImageView.image = [UIImage imageNamed:@"placeholder_loading"];
       // [manager downloadWithURL:[NSURL URLWithString:url] delegate:self];
        __weak typeof(self) blockSelf = self;
        [manager downloadImageWithURL:[NSURL URLWithString:url] options:0 progress:nil completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, BOOL finished, NSURL *imageURL) {
            dispatch_main_sync_safe(^{

                if (!blockSelf) {
                    return ;
                }
                [activityview stopAnimating];
                if (image) {
                    _previewImageView.image = image;
                    [blockSelf configPreviewImageViewWithImage:image];
                }
            });
        }];
    }

}
- (void)initImage:(UIImage *)image{
    _previewWidth = kDeviceWidth;
    
    if (__iOS7)
    {
        _previewHeight = KDeviceHeight - 50.0;
    }
    else
    {
        _previewHeight = KDeviceHeight - 70.0;
    }
    
    
    [self initPreivewImageView];
    [self initToolBar];

    [_previewImageView setImage:image];
    [self configPreviewImageViewWithImage:image];
}
- (void)initImage:(UIImage *)image withFrame:(CGRect)frame{
    _previewWidth = kDeviceWidth;
    
    if (__iOS7)
    {
        _previewHeight = KDeviceHeight;
    }
    else
    {
        _previewHeight = KDeviceHeight - 20;
    }
    
    [self initPreivewImageView];

    [_previewImageView setImage:image];
    
    [self configPreviewImageViewWithImage:image];
}

- (void)webImageManager:(SDWebImageManager *)imageManager didFinishWithImage:(UIImage *)image
{
    [activityview stopAnimating];
    _previewImageView.image = image;
    [self configPreviewImageViewWithImage:image];
}

- (void)webImageManager:(SDWebImageManager *)imageManager didFailWithError:(NSError *)error
{
    [activityview stopAnimating];
}


#pragma mark - UIScrollView delegate methods

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
    return _previewImageView;
}

- (void)scrollViewDidZoom:(UIScrollView *)scrollView
{
    //当捏或移动时，需要对center重新定义以达到居中显示位置
    [self centerPreviewImageView];
}
#pragma mark - private methods

//重置Scrollview
- (void)resetLayoutByPreviewImageView
{
    self.frame = CGRectMake(0, 0, _previewWidth, KDeviceHeight);
    _imageScrollView.frame = CGRectMake(0, 0, _previewWidth, _previewHeight);
    _toolbar.frame = CGRectMake(0.0, _previewHeight, 320.0, 50.0);
    _imageScrollView.zoomScale = _imageScrollView.maximumZoomScale = _imageScrollView.minimumZoomScale = 1;
    
    CGRect bounds = _imageScrollView.bounds;
    CGRect imageFrame = _previewImageView.frame;
    
    CGFloat xScale = CGRectGetWidth(bounds) / CGRectGetWidth(imageFrame);
    CGFloat yScale = CGRectGetHeight(bounds) / CGRectGetHeight(imageFrame);
    CGFloat minScale = MIN(xScale, yScale);
    
    CGFloat width = CGRectGetWidth(imageFrame);
    CGFloat height = CGRectGetHeight(imageFrame);
    CGFloat top = MAX(0, floorf((CGRectGetHeight(bounds) - height) / 2));
    CGFloat left = MAX(0, floorf((CGRectGetWidth(bounds) - width) / 2));
    [_previewImageView setFrame:CGRectMake(left, top, width, height)];
    
    _imageScrollView.contentSize = CGSizeMake(width, height);
    _imageScrollView.contentOffset =  CGPointZero;
    _imageScrollView.maximumZoomScale = MAX(2, 2 * minScale);
    _imageScrollView.minimumZoomScale = minScale;
    _imageScrollView.zoomScale = minScale;
}

//使图像始终在屏幕正中央
- (void)centerPreviewImageView
{
    CGSize boundsSize = _imageScrollView.bounds.size;
    CGRect frameToCenter = _previewImageView.frame;
    
    if (frameToCenter.size.width < boundsSize.width) {
        frameToCenter.origin.x = floorf((boundsSize.width - frameToCenter.size.width) / 2);
    } else {
        frameToCenter.origin.x = 0;
    }
    if (frameToCenter.size.height < boundsSize.height) {
        frameToCenter.origin.y = floorf((boundsSize.height - frameToCenter.size.height) / 2);
    } else {
        frameToCenter.origin.y = 0;
    }
    //center
    if (!CGRectEqualToRect(_previewImageView.frame, frameToCenter)) {
        _previewImageView.frame = frameToCenter;
    }
}

/**
 * @brief 加载图片成功后设置image's frame
 */
- (void)configPreviewImageViewWithImage:(UIImage *)image
{
    CGRect rect = _previewImageView.frame;
    rect.size.width = image.size.width;
    rect.size.height = image.size.height;
    _previewImageView.frame = rect;
    [self resetLayoutByPreviewImageView];
}

//接收点击图片事件
- (void)handleSingleTap:(UITapGestureRecognizer *)gesture
{
        if (_delegate && [_delegate respondsToSelector:@selector(didTapPreviewView)]) {
            [_delegate didTapPreviewView];
        }
}
/**
 * @brief delect image
 */
- (void)delectPreviewImage:(UIButton *)sender{
    
    [UIView animateWithDuration:0.3 animations:^(void){
        _previewImageView.frame = CGRectMake(kDeviceWidth - 30.0, KDeviceHeight - 50.0, 1.0, 1.0);
        _previewImageView.alpha = 0.0;
    } completion:^(BOOL finish){
        [[NSNotificationCenter defaultCenter] postNotificationName:@"image_delect" object:nil];
        [_previewImageView removeFromSuperview];
        [_delegate didTapPreviewView];
    }];

}




/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
