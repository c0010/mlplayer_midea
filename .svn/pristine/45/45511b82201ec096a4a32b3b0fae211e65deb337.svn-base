    //
//  CMHomeControl.m
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import "CMQaSearchControl.h"
#import "CMQaCategoryControl.h"
@implementation CMQaSearchControl

@synthesize key,qlistview,lbltxt;

#pragma mark system function
-(void)viewWillAppear:(BOOL)animated 
{ 
		// 显示外部NavBar，隐藏内部NavBar
	
	appDelegate.navigationController.navigationBarHidden = YES;
	self.navigationController.navigationBarHidden = NO;
	[super viewWillAppear:animated]; 
	
}

- (void) viewWillDisappear:(BOOL)animated {

}


-(void)onAppFocus:(BOOL)isForeground
{
	[self viewDidLoad];
	
}
#pragma mark searchbar function
// return NO to not become first responder
- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar
{
	return YES;
}
// called when text starts editing
- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar
{
	searchBar.showsCancelButton=YES;
}
 // called when text ends editing
- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar
{
	searchBar.text = @"";		
}
// called when text changes (including clear)
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{
	
}

- (BOOL)searchBar:(UISearchBar *)searchBar shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
	if([text isEqualToString:@"\n"])
	{
		[self searchBarSearchButtonClicked:searchBar];		
		return NO;
	}
	if(range.location >= 12)
		return NO;
	return YES;
}

// called when keyboard search button pressed
- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
	searchBar.showsCancelButton=NO;
	qlistview.key = searchBar.text;
	[qlistview Search];
	[searchBar endEditing:YES];
}
 // called when cancel button pressed
-(void)searchBarCancelButtonClicked:(UISearchBar *)SearchBars
{
	SearchBars.showsCancelButton=NO;
	[SearchBars resignFirstResponder];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {	
	
	[super viewDidLoad];
    
    self.titleLabel.text = self.navigationItem.title;
	
	//数据列表
	//f.origin.y += 30;
    CGRect frame = self.view.bounds;
    frame.size.height -= 44.0;
    if (__iOS7) {
        frame.size.height -= 20;
    }

	qlistview = [[CMQListView alloc] initWithFrame:frame refresh:false];
	[[self view] addSubview:qlistview];
	qlistview.key = self.key;
    qlistview.isSearchMode = YES;    
	[qlistview Search];
}
- (void) recivefunc:(NSNotification*)note
{
	qlistview.category = [[note userInfo] objectForKey:@"category"] ;
	self.lbltxt.text = [[note userInfo] objectForKey:@"title"];
}
-(void)gotocategory
{
	CMQaCategoryControl* qacategorycontrol = [[CMQaCategoryControl alloc] init];
	qacategorycontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	qacategorycontrol.navigationController.navigationBarHidden = NO;
	qacategorycontrol.tabBarController.tabBar.hidden = YES;
	qacategorycontrol.hidesBottomBarWhenPushed = YES;
	//qasearchcontrol.navigationController.delegate = self;
	qacategorycontrol.view.backgroundColor = [UIColor clearColor];
	qacategorycontrol.type = 2;
	[self.navigationController pushViewController:qacategorycontrol animated:YES];
}
/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/


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
