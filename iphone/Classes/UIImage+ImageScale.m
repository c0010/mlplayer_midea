//
//  UIImage+ImageScale.m
//  MLPlayer
//
//  Created by ray on 13/4/15.
//  Copyright (c) 2015 w. All rights reserved.
//

#import <Foundation/Foundation.h>


@implementation UIImage(ImageScale)

//截取部分图像
-(UIImage*)getSubImage:(CGRect)rect
{
    CGImageRef subImageRef = CGImageCreateWithImageInRect(self.CGImage, rect);
    CGRect smallBounds = CGRectMake(0, 0, CGImageGetWidth(subImageRef), CGImageGetHeight(subImageRef));
    
    UIGraphicsBeginImageContext(smallBounds.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextDrawImage(context, smallBounds, subImageRef);
    UIImage* smallImage = [UIImage imageWithCGImage:subImageRef];
    UIGraphicsEndImageContext();
	   
    CGImageRelease(subImageRef);
    
    //    subImageRef->
    
    return smallImage;
}
- (UIImage*)imageByScalingAndCroppingForSize:(UIImage *)image
{
    float actualHeight = image.size.height;
    float actualWidth = image.size.width;
    float imgRatio = actualWidth/actualHeight;
    float maxRatio = 236.0/275.0;
    if(imgRatio!=maxRatio){
        if(imgRatio < maxRatio){
            imgRatio = 275.0 / actualHeight;
            actualWidth = imgRatio * actualWidth;
            actualHeight = 275.0;
        }
        else
        {
            imgRatio = 236.0 / actualWidth;
            actualHeight = imgRatio * actualHeight;
            actualWidth = 236.0;
        }
    }
    CGRect rect = CGRectMake(0.0, 0.0, actualWidth, actualHeight);
    UIGraphicsBeginImageContext(rect.size);
    [image drawInRect:rect];
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

//等比例缩放
-(UIImage*)scaleToSize:(CGSize)size
{
    CGFloat width = self.size.width;
    CGFloat height = self.size.height;
    
    
    float heightRadio = size.height*1.0/height;
    float widthRadio = size.width*1.0/width;
    
    float radio = 1;
    if(heightRadio>1 && widthRadio>1)
    {
        
        radio = heightRadio > widthRadio ? widthRadio : heightRadio;
        
    }
    else
    {
        radio = heightRadio < widthRadio ? heightRadio : widthRadio;
    }
    
    width = width*radio;
    height = height*radio;
    
    int xPos = (size.width - width)/2;
    int yPos = (size.height-height)/2;
    
    // 创建一个bitmap的context
    // 并把它设置成为当前正在使用的context
    UIGraphicsBeginImageContext(size);
    
    // 绘制改变大小的图片
    [self drawInRect:CGRectMake(xPos, yPos, width, height)];
    
    // 从当前context中创建一个改变大小后的图片
    UIImage* scaledImage = UIGraphicsGetImageFromCurrentImageContext();
    
    // 使当前的context出堆栈
    UIGraphicsEndImageContext();
    
    // 返回新的改变大小后的图片
    return scaledImage;
}
@end
