//
//  CMImageDetailViewControl.m
//  MLPlayer
//
//  Created by hushengwu on 13-8-16.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMImageDetailViewControl.h"

@interface CMImageDetailViewControl ()

@end

@implementation CMImageDetailViewControl
@synthesize previewView = _previewView;
@synthesize isURL;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    if (isURL) {
        [self initPreviewImageURL];
    }
    else{
        [self initPreviewImage];
    } 
	// Do any additional setup after loading the view.
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initPreviewImageURL{
    _previewView = [[CMImagePreviewView alloc] init];
    _previewView.delegate = self;
    [self.view addSubview:_previewView];
    [_previewView initImageWithURL:_imageURL thumbURL:_thumbURL];
}

- (void)initPreviewImage
{
    _previewView = [[CMImagePreviewView alloc] init];
    _previewView.delegate = self;
    [self.view addSubview:_previewView];
    if (self.isShowLocationImage) {
        [_previewView initImage:_image withFrame:self.view.bounds];
    }
    else
        [_previewView initImage:_image];
}

#pragma mark - CMImagePreviewView delegate method

- (void)didTapPreviewView
{
//    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationFade];
    
    [self dismissModalViewControllerAnimated:YES];
  //  [self dismissViewControllerAnimated:YES completion:nil];
}
#pragma mark - Public method
- (void)setCMImageURL:(NSString *)url thumbURL:(NSString *)thumburl
{
    _imageURL = @"";
    _imageURL = url;
    _thumbURL = thumburl;
}

- (void)setImage:(UIImage *)image{
    _image = image;
}
- (void)setImage:(UIImage *)image withFrame:(CGRect)frame{
    _image = image;
    _frame = frame;
}



@end
