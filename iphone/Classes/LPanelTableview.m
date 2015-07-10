//
//  LPanelTableview.m
//  MLPlayer
//
//  左目录(单例)
//
//  Created by hfwang on 13-3-11.
//  Copyright 2013 w. All rights reserved.
//

#import "LPanelTableview.h"


@implementation LPanelTableview
@synthesize mytableview=_mytableview;
@synthesize dataArray=_dataArray;
@synthesize selected=_selected;

static  LPanelTableview * sharedLpanel =nil;

+(LPanelTableview *)sharedLpanel
{
	@synchronized(self){
		if(sharedLpanel == nil){
			sharedLpanel = [[self alloc] initWithFrame:CGRectMake(0, 10,[UIScreen mainScreen].bounds.size.width , [UIScreen mainScreen].bounds.size.height-20)];
		}
	}
	return sharedLpanel;
	
}
 

+(id)allocWithZone:(NSZone *)zone{
	@synchronized(self){
		if (sharedLpanel == nil) {
			sharedLpanel = [super allocWithZone:zone];
			return  sharedLpanel;
		}
	}
	return nil;
}


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
		
		
		//[self setBackgroundImage:[UIImage imageNamed:@"back_nodata"]];
	
		[self setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"back_nodata"]]];
		
		
		//UIImageView *backimg=[[UIImageView alloc]initWithFrame:self.bounds];
		//[backimg setImage:[UIImage imageNamed:@"back_nodata"]];
		//[self addSubview:backimg];
        
		
		NSMutableArray *tmparray=[[NSMutableArray alloc]init];
		self.dataArray=tmparray;
		
		
        UITableView *tb=[[UITableView alloc]initWithFrame:frame];
		self.mytableview=tb;
        
        [self.mytableview setDataSource:self];
        [self.mytableview setDelegate:self];
		[self.mytableview setSeparatorColor:[UIColor clearColor]];
		[self.mytableview  setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"back_nodata"]]  ];

		//[self.mytableview
		
        [self addSubview:self.mytableview];
        
    }
    return self;
}

#pragma mark -
#pragma mark Table view 

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	
	return [self.dataArray count];
}
// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
	static NSString *CustomCellIdentifier = @"CustomCellIdentifier";

	
	UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:CustomCellIdentifier];
	NSString *content= [self.dataArray objectAtIndex:indexPath.row];

	if (cell == nil) {
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CustomCellIdentifier];
		
		UIButton *back=[[UIButton alloc]initWithFrame:CGRectMake(0, 0, 320, 46)];

        //button文字靠左
		back.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
		back.contentEdgeInsets = UIEdgeInsetsMake(0,10, 0,0);

		
		[back setBackgroundImage:[UIImage imageNamed:@"back_normal"] forState:UIControlStateNormal];
		[back setBackgroundImage:[UIImage imageNamed:@"back_sel"] forState:UIControlStateSelected];
		[back setBackgroundImage:[UIImage imageNamed:@"back_sel"] forState:UIControlStateHighlighted];		

		[back setTitleColor:[UIColor blackColor] forState:UIControlStateNormal ];
		[back setTitleColor:[UIColor colorWithRed:27.0f/255.0f green:109.0f/255.0f blue:179.0f/255.0f alpha:1] forState:UIControlStateSelected];
		[back setTitleColor:[UIColor blackColor] forState:UIControlStateHighlighted];
        
        [back.titleLabel setFont:[UIFont systemFontOfSize:17]];
    
		[back addTarget:self action:@selector(pressCell:event:) forControlEvents:UIControlEventTouchUpInside];

		[back setTag:1];
		[cell.contentView addSubview:back];
		
	}
	
	UIButton *button=(UIButton *)[cell.contentView viewWithTag:1] ;
	[button setTitle:content forState:UIControlStateNormal];
	
	if(indexPath.row==self.selected)
	{
		[button setSelected:YES];
       // [button setFrame:CGRectMake(0, 0, self.bounds.size.width, 46)];
	
	}else {
        [button  setSelected:NO];

	}
	

	return cell;
}

-(void)pressCell:(id)sender event:(id)event
{
	NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:self.mytableview];
	
	self.selected=[self.mytableview indexPathForRowAtPoint:touchPoint].row;
	[self.mytableview reloadData];
	
	[[NSNotificationCenter defaultCenter] postNotificationName:@"reloadBrowserView" object:[NSNumber numberWithInteger:self.selected]];

	
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
	return 46;
} 


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	/*
	self.selected=indexPath.row;
	[tableView reloadData];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"reloadBrowserView" object:[[NSNumber alloc]initWithUnsignedInteger:indexPath.row]];
	 */
	
}



//-(LPanelTableview*)retain
//{
//	return self;
//}
//
//-(oneway void)release
//{
//}




@end
