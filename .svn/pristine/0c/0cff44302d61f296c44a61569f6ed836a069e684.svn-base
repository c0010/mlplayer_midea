    //
//  CMBrowserControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import "CMRecentControl.h"

@implementation CMRecentControl
-(CMContenthandler*)GetContenthandler
{
    for( UIView * view in self.view.subviews )
    {
        if([view isKindOfClass:[CMRefreshMoreView class]])
        {
         
           if([view isKindOfClass:[CMRecentView class]])
            {
                CMRecentView* itemview = (CMRecentView*)view;
                return itemview.Contenthandler;
            }
            
        }
        
        
    }
    return NULL;
}
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];

    self.titleLabel.text = self.navigationItem.title;
    
    self.navigationController.navigationBarHidden = NO;
    
	CGRect f = [[self view] bounds];
	f.size.height -= 44;
    if (__iOS7) {
        f.size.height -= 20;
    }
    self.view.backgroundColor = [UIColor whiteColor];
	recentview = [[CMRecentView alloc] initWithFrame:f];
    recentview.tableviewlist.separatorStyle = UITableViewCellSeparatorStyleNone;
    //recentview.tableviewlist.separatorColor = UIColorRGB(0xf8f8f8);
    recentview.backgroundColor = [UIColor clearColor];//UIColorRGB(0xf8f8f8);
    recentview.tableviewlist.backgroundColor = [UIColor clearColor];
    UIImageView *leftLineImageView = [[UIImageView alloc] init];
    UIImage *image = [UIImage imageNamed:@"learnrecord_left_line"];
    image = [image resizableImageWithCapInsets:UIEdgeInsetsMake(2, 0, 2, 0)];
    leftLineImageView.image = image;
    leftLineImageView.frame = CGRectMake(20, 0, 3, UI_IOS_WINDOW_HEIGHT);
    [self.view addSubview:leftLineImageView];
	[self.view addSubview:recentview];
    
	[recentview LoadData];
}

//iOS8上 cell分割线置顶
-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    if ([recentview.tableviewlist respondsToSelector:@selector(setSeparatorInset:)]) {
        [recentview.tableviewlist setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([recentview.tableviewlist respondsToSelector:@selector(setLayoutMargins:)]) {
        [recentview.tableviewlist setLayoutMargins:UIEdgeInsetsZero];
    }
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}




@end
