//
//  CMImage.h
//  MLPlayer
//
//  Created by sunjj on 11-6-21.
//  Copyright 2011 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cmwebimage.h"

@interface CMImage : UIImage {

	CMWebImage * m_pWebImage;
	
}
-(UIImage*)scaleToSize:(CGSize)size;
-(UIImage*)imageWithImage:(UIImage*)image scaledToSize:(CGSize)newSize;
- (id)initWithContentsOfResolutionIndependentFile:(NSString *)path; 
+ (UIImage*)imageWithContentsOfResolutionIndependentFile:(NSString *)path;

+ (UIImage*) imageWithColor: (UIColor*) color;
@end
