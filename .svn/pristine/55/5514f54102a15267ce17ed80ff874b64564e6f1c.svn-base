//
//  CMFileUtils.h
//  MLPlayer
//  获取保存图片
//  Created by water on 14-9-26.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>

#define Thumbnail_W 144
#define Thumbnail_H 90

#define Original_W Thumbnail_W * 3
#define Original_H Thumbnail_H * 3

typedef void (^OriginalPathCallBack)(NSString *,BOOL);

@interface CMFileUtils : NSObject

//生成原图并返回路径
+ (BOOL) makeAndFetchOriginalWithImage:(UIImage *)OrigImage done:(OriginalPathCallBack)callback;

//生成缩略图
+ (BOOL) makeThumbnail:(NSString *)path;

+ (UIImage *) scaleFromImage: (UIImage *) image toSize: (CGSize) size;


@end
