//
//  CMImagePreviewView.h
//  MLPlayer
//
//  Created by hushengwu on 13-8-16.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SDWebImage/SDWebImageManager.h"

@protocol CMImagePreviewViewDelegate <NSObject>

@optional
- (void)didTapPreviewView;

@end


@interface CMImagePreviewView : UIView<UIScrollViewDelegate,SDWebImageManagerDelegate>
{
    UIScrollView *_imageScrollView;
    UIImageView *_previewImageView;
    UIView *_toolbar;
    CGFloat _previewWidth;
    CGFloat _previewHeight;
    CGRect _frame;
    NSArray *buttons;
    BOOL viewIsIn;
    BOOL isShowToolbar;
    UIActivityIndicatorView *activityview;
}

@property (nonatomic, weak) id<CMImagePreviewViewDelegate> delegate;
@property (nonatomic, strong) UIView *toolbar;
@property (nonatomic, assign) BOOL isShowToolbar;
- (void)initImageWithURL:(NSString *)url thumbURL:(NSString *)thumburl;
- (void)resetLayoutByPreviewImageView;
- (void)initImage:(UIImage *)image;
- (void)initImage:(UIImage *)image withFrame:(CGRect)frame;

@end
