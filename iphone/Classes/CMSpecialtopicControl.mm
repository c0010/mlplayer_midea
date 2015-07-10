    //
//  CMBrowserControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import "CMSpecialtopicControl.h"

@implementation CMSpecialtopicControl
@synthesize SpecialtopicID;

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];

	CGRect f = [[self view] bounds];
	
	specialtopicview = [[CMSpecialtopicView alloc] initWithFrame:f];
	[self.view addSubview:specialtopicview];	
	[specialtopicview LoadData:SpecialtopicID];
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
