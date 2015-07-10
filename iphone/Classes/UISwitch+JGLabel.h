//
//  UISwitch+JGLabel.h
//  JGSwitch
//
//  Created by sl on 15/4/11.
//  Copyright (c) 2015年 Madordie. All rights reserved.
//

//
//  说明：
//      1.给UISwitch添加开关标签
//      2.可根据需要调整标签的相关属性
//      3.类别实现，不用更改代码即可添加
//
//
//  代码出处：http://www.cnblogs.com/madordie/
//
//  思路：
//      1.找到对应View添加两个Label
//

#import <UIKit/UIKit.h>

@interface UISwitch (JGLabel)

/**
 *  设置开关标题文字
 *      1.根据自己需要设置字体内容、大小、字体颜色等属性。
 *      2.不建议在此设置背景颜色，如需设置，调用父类方法设置。
 *      3.根据需要可手动调整Label的frame，以使你的Label更加美观。
 */

#pragma mark - 标题
- (UILabel *)onTitle;
- (UILabel *)offTitle;

@end

/**
 *备注：
 *      1.offTitle对齐方式默认右对齐。
 *      2.onTitle默认左对齐
 *      3.么有了
 */


//示例代码：
/*
 
 //初始化属性，可IB定制
 UISwitch *mySwitch = [[UISwitch alloc] init];
 mySwitch.center = self.view.center;
 mySwitch.transform = CGAffineTransformMakeScale(2.0f, 2.0f);
 [self.view addSubview:mySwitch];
 
 //设置标题属性（当作UILabel使用）
 mySwitch.offTitle.text = @"off";
 mySwitch.onTitle.text  =@"on";
 
 */