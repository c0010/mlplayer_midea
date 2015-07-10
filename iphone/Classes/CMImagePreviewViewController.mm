//
//  CMImagePreviewViewController.m
//  MLPlayer
//
//  Created by water on 14-8-7.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMImagePreviewViewController.h"
#import "CMMsgManager.h"
#import "tool.h"
#import "CMMsgBlock.h"

@interface CMImagePreviewViewController ()

@end

@implementation CMImagePreviewViewController
@synthesize delegate;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    CGRect frame = self.view.bounds;
    frame.size.height -= 64;
    
    self.imageview = [[UIImageView alloc]initWithFrame:frame];
    self.imageview.contentMode = UIViewContentModeScaleAspectFit;
    self.imageview.userInteractionEnabled = YES;
    [self.view addSubview:self.imageview];
    
    
    UIButton *commitButton = [UIButton buttonWithType:UIButtonTypeCustom];
    commitButton.frame = CGRectMake(0, 0, 40, 44);
    [commitButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [commitButton setTitleColor:[UIColor blackColor] forState:UIControlStateHighlighted];
    commitButton.titleLabel.font = [UIFont boldSystemFontOfSize:18.f];
    [commitButton addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:commitButton];
    
    if (!self.selectedImage) {
        CMImageMessageItem *imageMessageItem = MBlock.imagemessage(self.currItem);
        
        if (imageMessageItem.url  && imageMessageItem.thumb_url) {
            UIImage *oralImage = [[SDImageCache sharedImageCache] imageFromDiskCacheForKey:imageMessageItem.url];
            
            if (!oralImage) {
                UIImage *thumbImage = [[SDImageCache sharedImageCache] imageFromDiskCacheForKey:imageMessageItem.thumb_url];
                self.imageview.image = thumbImage;
                
                [tool ShowActivityIndicator:self.imageview];
                [[CMMsgManager manager] downloadImageWithUrl:MBlock.imagemessage(self.currItem).url download:^(UIImage *image) {
                    [tool DisimissActivityIndicator];
                    self.imageview.image = image;
                }];
            }else{
                self.imageview.image = oralImage;
            }
        }else{
            self.imageview.image = [UIImage imageWithContentsOfFile:MBlock.content(self.currItem)];
        }
//        [commitButton setTitle:I(@"保存") forState:UIControlStateNormal];
        self.navigationItem.rightBarButtonItem = nil;
    }else{
        self.imageview.image = self.selectedImage;
        [commitButton setTitle:I(@"发送") forState:UIControlStateNormal];
        self.navigationItem.rightBarButtonItem = rightItem;
    }
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapGestureRecognizerPressed:)];
    tapGesture.numberOfTapsRequired = 1;
    
    [self.imageview addGestureRecognizer:tapGesture];
}

-(void)buttonPressed:(UIButton *)sender
{
    if (!self.selectedImage) {
        [self saveImageToPhotos:self.imageview.image];
    }else{
        if (__iOS7)
        {
           // [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
            MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
            appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
        }
        
        [[UIApplication sharedApplication] setStatusBarHidden:NO];
        
        [self.navigationController dismissViewControllerAnimated:YES completion:^{
            if (self.delegate) {
                [self.delegate didSendMessage:self.selectedImage];
            }
        }];
    }
}

- (void)saveImageToPhotos:(UIImage*)savedImage
{
    UIImageWriteToSavedPhotosAlbum(savedImage, self, @selector(image:didFinishSavingWithError:contextInfo:), NULL);
}
// 指定回调方法
- (void)image: (UIImage *) image didFinishSavingWithError: (NSError *) error contextInfo: (void *) contextInfo
{
    NSString *msg = nil ;
    if(error != NULL){
        msg = I(@"保存图片失败") ;
    }else{
        msg = I(@"保存图片成功") ;
    }
    [tool ShowAlert:msg];
}


- (void)singleTapGestureRecognizerPressed:(UITapGestureRecognizer *)gestureRecognizer{
    
//    self.navigationController.navigationBarHidden = !self.navigationController.navigationBarHidden;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
