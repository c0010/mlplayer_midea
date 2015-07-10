    //
//  CMHomeControl.m
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import "CMQContentControl.h"
#import "CMQaSearchControl.h"
#import "CMQaCategoryControl.h"
#import "CMQuestionControl.h"


@implementation CMQContentControl
@synthesize qlistview,category;

#pragma mark system function
-(void)viewWillAppear:(BOOL)animated 
{ 
	[super viewWillAppear:animated]; 
}

- (void) viewWillDisappear:(BOOL)animated {

}


-(void)onAppFocus:(BOOL)isForeground
{
	[self viewDidLoad];
	
}
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {	
	
	[super viewDidLoad];	
	
	CGRect f = [[self view] bounds];
	f.origin.y -= 30;
	f.size.height += 30;
	//数据列表
	qlistview = [[CMQListView alloc] initWithFrame:f refresh:true];
	[[self view] addSubview:qlistview];
	qlistview.category = category;
	[qlistview GetCategory];
	
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
