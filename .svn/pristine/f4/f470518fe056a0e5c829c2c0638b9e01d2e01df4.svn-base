//
//  CMGroupControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-26.
//  Copyright 2011 w. All rights reserved.
//
#include "stdafx.h"
#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMQuestionDetailView.h"
#include "cmqalist.h"

@interface CMQuestionDetailControl : CMViewController<UINavigationControllerDelegate,UIImagePickerControllerDelegate>{


	CMQuestionDetailView* questiondetailview;
	
	TQAItem curqaItem;
@public
    CMQAList* m_pQalist;

}
@property(nonatomic,strong)CMQuestionDetailView* questiondetailview;

-(void)SetQuestionItem:(TQAItem&)item;
-(void)GetBrowserList;
@end




