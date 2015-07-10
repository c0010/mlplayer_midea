//
//  AKButton.h
//  MLPlayer
//
//  Created by hushengwu on 13-8-12.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
@class AKButton;
typedef enum : NSUInteger{
    AKListOpen,
    AkListClose
}AKButtonType;
@protocol AKButtonDelegate <NSObject>
@optional

- (void)didSelectButtonControl:(NSSet*)touches withEvent:(UIEvent *)event;


@end

@interface AKButton : UIView{
    UIImageView *bg;
    UIImageView *arrows;
    id<AKButtonDelegate> __weak delegate;
    AKButtonType selectType;
    BOOL  isOpen;
}
@property (nonatomic, strong) UIImageView *bg;
@property (nonatomic, strong) UIImageView *arrows;
@property (nonatomic, weak) id<AKButtonDelegate> delegate;
@property (nonatomic, assign) AKButtonType selectType;
@property (nonatomic, assign) BOOL isOpen;

- (void)setAKButtonStatus:(BOOL)statue;
- (void)CloseAnimaon;
- (void)OpenAnimaon;
@end
