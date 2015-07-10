//
//  CMGroupNameViewController.h
//  MLPlayer
//
//  Created by kyp on 14-6-21.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "CMTextView.h"
#import "cmgroup.h"

enum CMGroupEditType{
    CMGroupEditNameType = 0,
    CMGroupEditDescType = 1
};

@interface CMGroupNameViewController : CMViewController<UITextViewDelegate>
{
    CMTextView* theTextView;
    UILabel* words_Num;//字数提示
    NSUInteger input_words_num;
    BOOL isBeyond;//是否超过限制
    
    NSString* textContent;
    
    int totalNum;
    UIButton *commitBtn;
}

@property(strong,nonatomic) CMTextView* textView;
@property(strong,nonatomic) UILabel* words_Num;
@property(strong,nonatomic) NSString* textContent;
@property(assign,nonatomic) enum CMGroupEditType editType;

@property(strong,nonatomic) NSString* roomID;

- (id)initWithGroupItem:(NSString *)info;
@end
