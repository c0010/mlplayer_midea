//
//  CMFileUtils.m
//  MLPlayer
//
//  Created by water on 14-9-26.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMFileUtils.h"
#import "NSDate+Helper.h"

@implementation CMFileUtils

static OriginalPathCallBack originalPathCallBack;

+ (BOOL) makeAndFetchOriginalWithImage:(UIImage *)OrigImage done:(OriginalPathCallBack)callback
{
    originalPathCallBack = callback;
    
    CGFloat image_w = OrigImage.size.width;
    CGFloat image_h = OrigImage.size.height;
    
    BOOL isVertical;
    if(image_w >= image_h)
    {
        isVertical = NO;
        image_h = (image_h > Original_H) ? Original_H : image_h;
        image_w = (image_w > Original_W) ? Original_W : image_w;
    }else
    {
        isVertical = YES;
        
        image_w = (image_w > Original_H) ? Original_H : image_w;
        image_h = (image_h > Original_W) ? Original_W : image_h;
    }
    
    //裁剪图片
    UIImage *editImg = [[self class] scaleFromImage:OrigImage toSize:CGSizeMake(image_w, image_h)];
    NSError* err=nil;
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *cachesDir = [paths objectAtIndex:0];
    NSString *strDate = [[NSDate date] stringWithFormat:@"yyyyMMddHHmmss"];
    
    NSString *strImageName = [cachesDir stringByAppendingPathComponent:[strDate stringByAppendingString:@".png"]];
    
    if(![UIImagePNGRepresentation(editImg) writeToFile:strImageName options:NSDataWritingAtomic error:&err]){
        NSLog(@"oralImg save file failed :err%@",[err localizedFailureReason]);
        
       
        return NO;
    }else{
        originalPathCallBack(strImageName,isVertical);
        originalPathCallBack = nil;
    }
    
    return YES;
}

//生成缩略图
+ (BOOL) makeThumbnail:(NSString *)path
{
    
    UIImage *oralImg = [UIImage imageWithContentsOfFile:path];
    
    double image_w = oralImg.size.width;
    double image_h = oralImg.size.height;
    
    if(image_w >= image_h)
    {
        image_h = (image_h > Thumbnail_H) ? Thumbnail_H : image_h;
        image_w = (image_w > Thumbnail_W) ? Thumbnail_W : image_w;
    }else
    {
        image_w = (image_w > Thumbnail_H) ? Thumbnail_H : image_w;
        image_h = (image_h > Thumbnail_W) ? Thumbnail_W : image_h;
    }
    
    UIImage *editImg = [[self class] scaleFromImage:oralImg toSize:CGSizeMake(image_w, image_h)];
    NSError* err=nil;
    
    if(![UIImagePNGRepresentation(editImg) writeToFile:path options:NSDataWritingAtomic error:&err]){
        NSLog(@"save file failed :err%@",[err localizedFailureReason]);
        return NO;
    }
    
    return YES;
}

+ (UIImage *) scaleFromImage: (UIImage *) image toSize: (CGSize) size
{
    UIGraphicsBeginImageContext(size);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

@end
