//
//  CMInteractTableViewCell.h
//  MLPlayer
//
//  Created by sunjj on 11-11-7.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "tool.h"

@interface CMInteractMyInfoTableViewCell : UITableViewCell  {
	UILabel *lblauthor;
	UILabel *lbldesc;
	UIImageView *LeftImageView;
	UILabel* lblfrom;
	UILabel* lblcomment;
	UILabel* lbltime;
}

@property(nonatomic,retain)UILabel *lblauthor;
@property(nonatomic,retain)UILabel *lbldesc;
@property(nonatomic,retain)UILabel* lblfrom;
@property(nonatomic,retain)UILabel* lblcomment;
@property(nonatomic,retain)UILabel* lbltime;

@property(nonatomic,retain)UIImageView *LeftImageView;

@end
