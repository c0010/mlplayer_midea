//
//  CMSearchControl.m
//  OCplusplus
//
//  Created by sunjj on 11-4-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CMSearchControl.h"
#import "CMNavgateItem.h"
#import "cmsettings.h"

@implementation CMSearchControl
@synthesize type,key,title,isCategorySearch;

- (CMContenthandler *)GetContenthandler{
    for( UIView * view in self.view.subviews )
    {
        if([view isKindOfClass:[CMRefreshMoreView class]])
        {
            
            if([view isKindOfClass:[CMSearchView class]])
            {
                CMSearchView* itemview = (CMSearchView*)view;
                return itemview.Contenthandler;
            }
            
        }
        
        
    }
    return NULL;
}

-(void)closeBackGround:(id)state
{
	[myGroundView removeFromSuperview];
}

-(void)backindex
{
	[self.navigationController  popViewControllerAnimated: YES];
}

- (void)passValue:(NSString *)value{
	if (value)
	{
		searchBar.text = value;
		[self setSugestListHidden:YES];
	}
}
#pragma mark search
- (void)setSugestListHidden:(BOOL)hidden 
{
	NSInteger height = hidden ? 0 : suggList.matchedStrings.count*30;
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:.2];
	[suggList.view setFrame:CGRectMake(30, 36, 200, MIN(height,150))];
	[UIView commitAnimations];
}
- (void)searchBar:(UISearchBar *)searchBars textDidChange:(NSString *)searchText;   // called when text changes (including clear)
{
	[self setSugestListHidden:![suggList ChangeText:searchText]];
}

-(BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBars
{
	//NSLog(@"searchBarShouldEndEditing");	
	searchBars.text=@"";
	return YES;
}

//search operator
- (void)searchBarSearchButtonClicked:(UISearchBar *)SearchBars {
	
	[self setSugestListHidden:YES];
	// When the search button is tapped, add the search term to recents and conduct the search.
	SearchBars.showsCancelButton = FALSE;
	
	[self gotoSearch:SearchBars.text];
	
	
	[self hidKeyBoard];
		
}

- (void)searchBarTextDidBeginEditing:(UISearchBar *)SearchBars {
	
	SearchBars.showsCancelButton=YES;	
}

-(void)searchBarCancelButtonClicked:(UISearchBar *)SearchBars
{
	[self setSugestListHidden:YES];
	SearchBars.showsCancelButton=NO;
	[SearchBars resignFirstResponder];
}

-(void) searchBarResultsListButtonClicked:(UISearchBar *)searchBars
{
	searchBars.showsCancelButton=NO;
	[searchBars resignFirstResponder];
	
	NSLog(@"searchBarResultsListButtonClicked");
	//CGRect f = [[self view] bounds ];
	
	//CGRect myframe =[[UIScreen mainScreen]bounds];
	myGroundView = [[UIView alloc] init];
	myGroundView.frame =CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT);
	
	myGroundView.backgroundColor=[UIColor blackColor];
	myGroundView.alpha= 0.8;
	
	//CMShowLayer *myView =[[CMShowLayer alloc] init];
	
		//myView.custom2ControlDelegate=self;
	//myView.bgView = myGroundView;
	
	[self.view.window addSubview:myGroundView];		
	
}

-(void)displaySearchCancleBtn
{
	for(id cc in [searchBar subviews])		
	{		
		if([cc isKindOfClass:[UIButton class]])			
		{		
			UIButton *btn = (UIButton *)cc;			
			btn.hidden=NO;
			[btn setTitle:I(@"取消") forState:UIControlStateNormal];
			[btn addTarget:self action:@selector(hidKeyBoard) forControlEvents:UIControlEventTouchUpInside];
		}		
	}
}
-(void)hidSearchCancleBtn
{
	for(id cc in [searchBar subviews])		
	{		
		if([cc isKindOfClass:[UIButton class]])			
		{			
			UIButton *btn = (UIButton *)cc;			
			btn.hidden=YES;
		}		
	}
}

-(void)hidKeyBoard
{
	//[self hidSearchCancleBtn];
	[searchBar endEditing:YES];
	//[searchBar resignFirstResponder];
}

//goto search
-(void)gotoSearch:(NSString *)value
{
	NSLog(@"this searchValue=[%@]",value);
	
	if(searchview)
		[searchview Search:[type UTF8String] value:[value UTF8String]];
	searchBar.text = value;
	suggList.stringsArray = [self GetAutoList];
}
#pragma mark syscall
- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	//[searchview Search:[type UTF8String] value:[key UTF8String]];
}
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.titleLabel.text = self.navigationItem.title;
    
	CGRect f = [[self view] bounds];
    f.size.height -= 44.0;
    
    if (__iOS7) {
        f.size.height -= 20;
    }

	searchview = [[CMSearchView alloc] initWithFrame:f];
	[[self view] addSubview:searchview];
	searchview.tableviewlist.separatorColor = [UIColor clearColor];
    searchview.isSearchMode = TRUE;
    if (isCategorySearch) {
        [searchview Search:[type UTF8String] value:[key UTF8String] title:[title UTF8String]];
    }
    else{
        [searchview Search:[type UTF8String] value:[key UTF8String]];
    }
 //   [searchview setGeneratePlaceholderView:isCategorySearch type:type value:key title:title];
	
}
-(NSMutableArray*)GetAutoList
{
	if(!autoarray)
		autoarray = [[NSMutableArray alloc] init];
	[autoarray removeAllObjects];
	CMSearch* pSearch = (CMSearch*)searchview.Contenthandler;
	if(pSearch)
	{
		for(int i=0; i<pSearch->GetRecentKeyCount();i++)
		{
			const char* pkey = pSearch->GetRecentKeyItem(i);
			if(pkey)
				[autoarray addObject:[NSString stringWithUTF8String:pkey]];		
		}
	}	
	return autoarray;
}
-(void)getSearchValue:(id)sender
{
	searchBar.text = [[sender userInfo] objectForKey:@"name"];
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
