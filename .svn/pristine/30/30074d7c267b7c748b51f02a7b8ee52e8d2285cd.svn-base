//
//  CMImage.m
//  MLPlayer
//
//  Created by sunjj on 11-6-21.
//  Copyright 2011 w. All rights reserved.
//

#import "CMImage.h"
#import "tool.h"
@implementation CMImage

- (id)initWithContentsOfResolutionIndependentFile:(NSString *)path
{
	float f_scale = 1.0;
	
	if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
        f_scale = [[UIScreen mainScreen] scale];
	}

	if ( [[[UIDevice currentDevice] systemVersion] intValue] >= 4 &&  f_scale == 2.0 ) {
		
		if ( [[NSFileManager defaultManager] fileExistsAtPath:path] ) {
			return [self initWithCGImage:[[UIImage imageWithData:[NSData dataWithContentsOfFile:path]] CGImage] scale:2.0 orientation:UIImageOrientationUp];
		}
	}
	return [self initWithData:[NSData dataWithContentsOfFile:path]];
}

+ (UIImage*)imageWithContentsOfResolutionIndependentFile:(NSString *)path {
	UIImage* loadImage = [[CMImage alloc] initWithContentsOfResolutionIndependentFile:path];
	return loadImage;
}


-(UIImage*)init:(NSInteger)m_indexid image:(NSString * )sImage
{
	if(m_pWebImage != NULL && m_pWebImage->GetFromUrl(m_indexid,[sImage UTF8String]))	{	
		NSData *imageData = [NSData dataWithContentsOfFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath([sImage UTF8String])]];
		UIImage *m_image = [[UIImage alloc]initWithData:imageData];
		return m_image;
	}
	return nil;
}

-(UIImage*)imageWithImage:(UIImage*)image scaledToSize:(CGSize)newSize;
{
	// Create a graphics image context
	UIGraphicsBeginImageContext(newSize);
	
	// Tell the old image to draw in this new context, with the desired
	// new size
	[image drawInRect:CGRectMake(0,0,newSize.width,newSize.height)];
	
	// Get the new image from the context
	UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
	
	// End the context
	UIGraphicsEndImageContext();
	
	// Return the new image.
	return newImage;
}

-(UIImage*)scaleToSize:(CGSize)size 
{
	CGFloat width = self.size.width;
    CGFloat height = self.size.height;
	
	float verticalRadio = size.height*1.0/height; 
	float horizontalRadio = size.width*1.0/width;
	
	float radio = 1;
	if(verticalRadio>1 && horizontalRadio>1)
	{
		radio = verticalRadio > horizontalRadio ? horizontalRadio : verticalRadio;	
	}
	else
	{
		radio = verticalRadio < horizontalRadio ? verticalRadio : horizontalRadio;	
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

+ (UIImage*) imageWithColor: (UIColor*) color

{
    CGRect rect=CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage*theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

@end
