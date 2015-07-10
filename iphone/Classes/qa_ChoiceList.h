//
//  qa_ChoiceList.h
//  MLPlayer
//
//  Created by hushengwu on 13-8-7.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface qa_ChoiceListItem : NSObject{
    UIImage *_image;
    NSString *_title;
    id _target;
    SEL _action;
    UIColor *_foreColor;
    NSTextAlignment _alignment;
    CGAffineTransform _transform;
}
@property (nonatomic, strong) UIImage *image;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) id target;
@property (nonatomic) SEL action;
@property (nonatomic, strong) UIColor *foreColor;
@property (nonatomic) NSTextAlignment alignment;
@property (nonatomic, assign) CGAffineTransform transform;

+ (instancetype) menuItem:(NSString *) title
                    image:(UIImage *) image
                   target:(id)target
                   action:(SEL) action;
//适应屏幕旋转
+ (instancetype) menuItem:(NSString *) title
                    image:(UIImage *) image
                   target:(id)target
                   action:(SEL) action
                   transform:(CGAffineTransform)transform;

@end

@interface qa_ChoiceList : NSObject

+ (void) showMenuInView:(UIView *)view
               fromRect:(CGRect)rect
              menuItems:(NSArray *)menuItems;
//适应屏幕旋转
+ (void) showMenuInView:(UIView *)view
               fromRect:(CGRect)rect
              menuItems:(NSArray *)menuItems
              transform:(CGAffineTransform)transform;

+ (void) dismissMenu;

+ (UIColor *) tintColor;
+ (void) setTintColor: (UIColor *) tintColor;

+ (UIFont *) titleFont;
+ (void) setTitleFont: (UIFont *) titleFont;

@end
