//
//  CMBrowserView.m
//  MLPlayer
//设置-个人中心-学习记录
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMRecentView.h"
#import "CMNavgateItem.h"
#import "CMLearnRecordCell.h"

@implementation CMRecentView
@synthesize Contenthandler = m_pContenthandler;

#define kCellIdentifier @"com.apple.CMItemView.CellIdentifier"

-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:false];
	if(self != nil)
	{
		//init
		m_pContenthandler = nil;
		if (!m_pGetImageListener) 
			m_pGetImageListener = new CMRecentGetImageListener();
		if (!m_pWebImage)
		{
			m_pWebImage=new CMWebImage(m_pGetImageListener);
			m_pWebImage->SetUserData(BridgeObjectToC(self));
		}
        
       //  [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(clickRefresh) on:bgview];
		
		m_pUpdataDataListerner = NULL;
	}
	return self;
}

- (void)clickRefresh{
    if (CMGlobal::TheOne().IsExistNetwork()) {
        [self LoadData];
    }
}


-(void)LoadData
{
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMRecentUpdateDataListener();
	if(!self.Contenthandler)
	{
		CMRecentContent* pRecentContent = new CMRecentContent(m_pUpdataDataListerner);
		pRecentContent->SetUserData(BridgeObjectToC(self));
		self.Contenthandler = pRecentContent;
	}
	CMRecentContent* pRecentContent = (CMRecentContent*)self.Contenthandler;
    pRecentContent->SetUserData(BridgeObjectToC(self));

    pRecentContent->SetListener(m_pUpdataDataListerner, NULL);
    
    [tool ShowActivityIndicator:self];

	if(pRecentContent->Update())
	{
		self.HasMore = false;
	}
}

#pragma mark -
#pragma mark UITableView delegate methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if(!m_pContenthandler)
		return 0;
	if (![self HasMore] || SETTING.GetAutoLoadMore()) {
		return m_pContenthandler->GetItemCount();
	}
	return m_pContenthandler->GetItemCount()+1;
}

//- (NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath{
//    CMLearnRecordCell *cell = (CMLearnRecordCell *)[tableView cellForRowAtIndexPath:indexPath];
//    
//    UIImage *selectedImage = [UIImage imageNamed:@"learnrecord_pop_bg_s"];
//    selectedImage = [selectedImage resizableImageWithCapInsets:UIEdgeInsetsMake(30, 40, 6, 6)];
//    cell.popBackgroundView.image = selectedImage;
//    [cell.popBackgroundView setNeedsDisplay];
//    
//    return indexPath;
//}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {

    
	if (indexPath.row == m_pContenthandler->GetItemCount()) {
		return;
	}
	
    TBrowserItem* item= NULL;
    
    if(m_pContenthandler->GetItemModel(indexPath.row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
        
    }

	m_pContenthandler->GetItem(indexPath.row, item);
	
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
	int selrow = indexPath.row;
	if(_stricmp(item->sFlag,"course") == 0)
		selrow = -1;
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
	[nav NavgateItem:(UIViewController*)nextResponder item:*item];
    
    SAFEDELETE(item);
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
    });
    
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{       
    if(indexPath.row == m_pContenthandler->GetItemCount())
		return 44;
    TBrowserItem* item= NULL;
    
    if(m_pContenthandler->GetItemModel(indexPath.row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
        
    }
    
    TBrowserItem* prebrowserItem= NULL;
    
    NSUInteger preIndex = indexPath.row - 1;
    NSString *_timestr = nil;
    if (preIndex != -1) {
        
        if(m_pContenthandler->GetItemModel(preIndex)==0)
        {
            prebrowserItem = new TClassItem();
        }
        else
        {
            prebrowserItem = new TCoursewareItem();
        }
        
        m_pContenthandler->GetItem(preIndex, prebrowserItem);
        
        _timestr = [NSString stringWithUTF8String:prebrowserItem->sPubdate];
        
    }
    m_pContenthandler->GetItem(indexPath.row, item);
    
    CGFloat tempf = [CMLearnRecordCell GetCellHeight:*item width:self.frame.size.width withPreString:_timestr];
    
    SAFEDELETE(item);
    SAFEDELETE(prebrowserItem);
    
    return tempf;
}



// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	if (indexPath.row == m_pContenthandler->GetItemCount() &&  m_pContenthandler->GetItemCount()!= 0)
		return [super tableView:tableView cellForRowAtIndexPath:indexPath];

	CMLearnRecordCell *cell = (CMLearnRecordCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	
	if (cell == nil) {
		cell = [[CMLearnRecordCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
	}
	
    TBrowserItem* browserItem= NULL;
    
    if(m_pContenthandler->GetItemModel(indexPath.row)==0)
    {
        browserItem = new TClassItem();
    }
    else
    {
        browserItem = new TCoursewareItem();
        
    }
    TBrowserItem* prebrowserItem= NULL;
    
    NSUInteger preIndex = indexPath.row - 1;
    NSString *timestr = nil;
    if (preIndex != -1) {
        
        if(m_pContenthandler->GetItemModel(preIndex)==0)
        {
            prebrowserItem = new TClassItem();
        }
        else
        {
            prebrowserItem = new TCoursewareItem();
        }
        
        m_pContenthandler->GetItem(preIndex, prebrowserItem);
        
       timestr = [NSString stringWithUTF8String:prebrowserItem->sPubdate];

    }
	m_pContenthandler->GetItem(indexPath.row, browserItem);
	
    [cell setcellinfo:*browserItem perTimeString:timestr];
	    
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    SAFEDELETE(browserItem);
    SAFEDELETE(prebrowserItem);
	return cell;		
}

-(void)RefreshList
{
	[self LoadData];
	
}

-(BOOL)RefreshMore
{
	if([self HasMore])
	{
		CMRecentContent* pRecentContent = (CMRecentContent*) self.Contenthandler;
        
        if(!m_pUpdataDataListerner)
            m_pUpdataDataListerner = new CMRecentUpdateDataListener();
        pRecentContent->SetListener(m_pUpdataDataListerner, NULL);

		return pRecentContent->RequestMore();
	}

    return NO;
}

- (void)dealloc {
	
	SAFEDELETE(m_pUpdataDataListerner);
	SAFEDELETE(self->m_pContenthandler);
	
	SAFEDELETE(m_pGetImageListener);
	SAFEDELETE(m_pWebImage);

}


@end

