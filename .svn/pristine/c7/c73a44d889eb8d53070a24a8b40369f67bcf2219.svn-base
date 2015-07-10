//
//  UISwitch+JGLabel.m
//  JGSwitch
//
//  Created by sl on 15/4/11.
//  Copyright (c) 2015年 Madordie. All rights reserved.
//

#import "UISwitch+JGLabel.h"
#import <objc/runtime.h>

static const void *onTitleKey = &onTitleKey;
static const void *offTitleKey = &offTitleKey;
#define JGGetOnTitle                objc_getAssociatedObject(self, onTitleKey )
#define JGGetOffTitle               objc_getAssociatedObject(self, offTitleKey)
#define JGSetOnTitle(JLabel)        objc_setAssociatedObject(self, onTitleKey,  JLabel, OBJC_ASSOCIATION_RETAIN_NONATOMIC)
#define JGSetOffTitle(JLabel)       objc_setAssociatedObject(self, offTitleKey, JLabel, OBJC_ASSOCIATION_RETAIN_NONATOMIC)

@implementation UISwitch (JGLabel)

#pragma mark - getter
- (UILabel *)onTitle {
    UILabel *_onTitle = JGGetOnTitle;
    if (_onTitle) {
        return _onTitle;
    }
    _onTitle = [self JGMakeLabel];
    [self.subviews enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        UIView *view = obj;
        if ([view isKindOfClass:NSClassFromString(@"_UISwitchInternalViewNeueStyle1")]) {
            [view.subviews enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
                UIView *aview = obj;
                
                if ([aview isKindOfClass:[UIImageView class]]) {
                    [view insertSubview:_onTitle belowSubview:aview];
                }
            }];
        }
    }];
    JGSetOnTitle(_onTitle);
    return _onTitle;
}

- (UILabel *)offTitle {
    UILabel *_offTitle = JGGetOffTitle;
    if (_offTitle) {
        return _offTitle;
    }
    _offTitle = [self JGMakeLabel];
    [self insertSubview:_offTitle atIndex:0];
    [_offTitle setTextAlignment:NSTextAlignmentRight];
    JGSetOffTitle(_offTitle);
    return _offTitle;
}

#pragma mark - tools
- (UILabel *)JGMakeLabel {
    UILabel *label = [[UILabel alloc] init];
    [label setBackgroundColor:[UIColor clearColor]];
    label.textColor = [UIColor blackColor];
    CGRect frame = self.bounds;
    frame.origin.x = 4;
    frame.size.width -= 8;
    label.frame = frame;
    return label;
}

@end

