//
//  CMFavoriteUI.m
//  OCplusplus
//
//  Created by sunjj on 11-4-27.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMFavoriteControl.h"

@implementation CMFavoriteControl

-(CMContenthandler*)GetContenthandler
{
    return CMFavorites::GetInstance();
}


-(void)viewWillAppear:(BOOL)animated 
{ 
	[super viewWillAppear:animated];
	MLPlayerAppDelegate *appDelegate = [UIApplication sharedApplication].delegate;
	appDelegate.navigationController.navigationBarHidden = YES;
	self.navigationController.navigationBarHidden = NO;
    [favoriteview refreshView];
}
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.titleLabel.text = self.navigationItem.title;
	
	CGRect f = [[self view] bounds];
	f.size.height -= 44;
    if (__iOS7) {
        f.size.height -= 20;
    }
    
	favoriteview = [[CMFavoriteView alloc] initWithFrame:f];
	[self.view addSubview:favoriteview];
	[favoriteview LoadData];

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
