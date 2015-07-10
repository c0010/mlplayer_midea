//
//  CMBrowserView.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMFavoriteView.h"
#import "CMNavgateItem.h"
#import "CMMyFavoriteCell.h"


@implementation CMFavoriteView

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame])
    {
        m_pTableView = [[CMTableView alloc] initWithFrame:frame];
        m_pTableView.backgroundColor = kColorBackground;
        m_pTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
        [self addSubview:m_pTableView];
        
        
        bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, m_pTableView.bounds.size.width, m_pTableView.bounds.size.height)];
        [bgview addSubview:[tool generatePlaceholderView:Placeholder_NoDataText on:bgview]];
        [m_pTableView addSubview:bgview];
        [bgview setBackgroundColor:[UIColor whiteColor]];
        
        bgview.userInteractionEnabled=NO;
        bgview.hidden = YES;
        

    }
    
    return self;
}


-(void)LoadData
{
    //[tool Wait];
    
    m_pCMFavorite = CMFavorites::GetInstance();
    
    m_pCMFavorite->LoadFromDB();
        
    m_pTableView.delegate = self;
    m_pTableView.dataSource = self;
    [m_pTableView reloadData];
}


-(void)refreshView
{
    
    [m_pTableView reloadData];

    
}




#pragma mark -
#pragma mark UITableView delegate methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(m_pCMFavorite->GetItemCount()==0)
    {
        bgview.hidden=NO;
        tableView.separatorStyle =UITableViewCellSeparatorStyleNone;
        
    }else
    {
        tableView.separatorStyle =     UITableViewCellSeparatorStyleSingleLine;
        
        bgview.hidden=YES;
    }

	if (m_pCMFavorite->IsEnd())
    {
		return m_pCMFavorite->GetItemCount();
	}
	return m_pCMFavorite->GetItemCount()+1;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	if (indexPath.row == m_pCMFavorite->GetItemCount()) {
		return;
	}
	
    TBrowserItem* item = NULL;
    
    if(m_pCMFavorite->GetItemModel(indexPath.row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
        
    }
    
	m_pCMFavorite->GetItem(indexPath.row, item);
	
	UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
    {
        SAFEDELETE(item);

		return;
    }

	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
	[nav NavgateItem:(UIViewController*)nextResponder item:*item];
    SAFEDELETE(item);
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(indexPath.row == m_pCMFavorite->GetItemCount())
		return 44;
 
    
    TBrowserItem* item = NULL;
    
    if(m_pCMFavorite->GetItemModel(indexPath.row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
        
    }
    
    m_pCMFavorite->GetItem(indexPath.row, item);
    
    CGFloat tempf= [CMMyFavoriteCell GetCellHeight:*item width:self.frame.size.width];
    
    SAFEDELETE(item);
    
    return tempf;
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
    
	CMMyFavoriteCell *cell = (CMMyFavoriteCell*)[tableView dequeueReusableCellWithIdentifier:@"favoritecell"];
	
	if (cell == nil) {
		cell = [[CMMyFavoriteCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"favoritecell"];
	}
	
    TBrowserItem* browserItem = NULL;
    
    if(m_pCMFavorite->GetItemModel(indexPath.row)==0)
    {
        browserItem = new TClassItem();
    }
    else
    {
        browserItem = new TCoursewareItem();
        
    }
	
	m_pCMFavorite->GetItem(indexPath.row, browserItem);
	
	
	NSString * strFlag = [NSString stringWithUTF8String:browserItem->sFlag];
    
	[cell setcellinfo:*browserItem];
    
    if(browserItem->nModel==0 && [strFlag isEqualToString:@"course"]){
        cell.typeImageView.hidden = NO;
    }
    else{
        cell.typeImageView.hidden = YES;
    }
	
	cell.selectionStyle = UITableViewCellSelectionStyleGray;
    
    SAFEDELETE(browserItem);
	return cell;		
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row < m_pCMFavorite->GetItemCount())
    {
        if (editingStyle == UITableViewCellEditingStyleDelete)
        {
            m_pCMFavorite->RemoveItem(indexPath.row);
            [m_pTableView reloadData];
        }
    }
}
- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return  I(@"删除");
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row < m_pCMFavorite->GetItemCount())
    {
        return UITableViewCellEditingStyleDelete;
    }
    else
    {
        return UITableViewCellEditingStyleNone;
    }
}

@end

