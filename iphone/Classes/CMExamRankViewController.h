//
//  CMExamRankViewController.h
//  MLPlayer
//
//  Created by wmgwd on 13-11-13.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMWebView.h"
@interface CMExamRankViewController : CMViewController<UIWebViewDelegate>
{
    CMWebView *m_pWebView;
    
    UIView *bgview;
}

@property (nonatomic, strong) NSString *strURL;

@end
