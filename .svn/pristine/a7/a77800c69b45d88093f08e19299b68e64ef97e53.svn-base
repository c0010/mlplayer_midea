//
//  CMImageDetailViewControl.h
//  MLPlayer
//
//  Created by hushengwu on 13-8-16.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMImagePreviewView.h"
#import "CMViewController.h"

@interface CMImageDetailViewControl : CMViewController<CMImagePreviewViewDelegate>{
    CMImagePreviewView *_previewView;
    NSString *_imageURL;
    NSString *_thumbURL;
    UIImage *_image;
    CGRect _frame;
    BOOL isURL;
}
@property(nonatomic,assign) BOOL isURL;
@property(nonatomic,assign) BOOL isShowLocationImage;
@property(nonatomic,strong) CMImagePreviewView *previewView;
- (void)setCMImageURL:(NSString *)url thumbURL:(NSString *)thumburl;
- (void)setImage:(UIImage *)image;
- (void)setImage:(UIImage *)image withFrame:(CGRect)frame;
@end
