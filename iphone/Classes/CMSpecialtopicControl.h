//
//  CMBrowserControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMSpecialtopicView.h"

@interface CMSpecialtopicControl : CMViewController{
	CMSpecialtopicView* specialtopicview;
	
	NSString * SpecialtopicID;
}
@property(nonatomic,copy)NSString *SpecialtopicID;
@end
