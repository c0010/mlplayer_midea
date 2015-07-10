//
//  CMSegmentedControl.h
//  MLPlayer
//
//  Created by water on 14-8-14.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^SegmentedListener)(NSInteger index);
@interface CMSegmentedControl : UIView{
    UIButton *leftButton;
    UIButton *rightButton;
}

@property(nonatomic,strong) SegmentedListener segmentedListener;

- (id)initWithFrame:(CGRect)frame leftTitle:(NSString *)leftTitle rightTitle:(NSString *)rightTitle didSelectedIndex:(SegmentedListener)listener;
@end
