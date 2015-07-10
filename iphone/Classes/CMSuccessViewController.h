//
//  CMSuccessViewController.h
//  MLPlayer
//
//  Created by wmgwd on 13-12-5.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMViewController.h"
#import <MessageUI/MessageUI.h>

@interface CMSuccessViewController : CMViewController
<UINavigationControllerDelegate,MFMailComposeViewControllerDelegate>


@property (nonatomic, strong) NSString *strMail;
@end
