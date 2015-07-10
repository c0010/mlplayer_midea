//
//  cmitemcontroller.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMItemView.h"
#import "cmsettings.h"
#import "CMBrowserControl.h"

#import "CMMarkViewController.h"


@implementation CMItemView

@synthesize HasDelete      = m_bHasDelete;
@synthesize Contenthandler = m_pContenthandler;
@synthesize m_pWebImage    = m_pWebImage;
@synthesize newscell;
@synthesize isSearchMode;
#define kCellIdentifier @"com.apple.CMItemView.CellIdentifier"

#pragma mark -
#pragma mark View init


-(id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh
{
	self = [super initWithFrame:frame refresh:brefresh];
	if(self != nil)
	{
        model=0;// 0为课程显示，1为课件显示
		//init
		m_bHasDelete = false;
        isSearchMode = false;
		m_pContenthandler = nil;
		if (!m_pGetImageListener)
			m_pGetImageListener = new CMItemGetImageListener();
		if (!m_pWebImage)
		{
			m_pWebImage=new CMWebImage(m_pGetImageListener);
			m_pWebImage->SetUserData((__bridge void*)self);
		}

        self.willRefreshList = YES;
	}
	return self;
}

-(void)GetBrowserList
{
	if(m_pContenthandler->GetHeadItemCount() > 0)
	{
		if(headCell == nil)
		{
			CGRect frame = CGRectMake(0,0,tableviewlist.frame.size.width,44);
			headCell = [[XLCycleScrollView alloc] initWithFrame:frame];
			headCell.delegate = self;
			headCell.datasource = self;
		}
		[headCell reloadData];
	}
	[super GetBrowserList];
}


#pragma mark -
#pragma mark UITableView delegate methods


- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{
	if([self HasDelete])
		return UITableViewCellEditingStyleDelete;
	else
		return UITableViewCellEditingStyleNone;
}

- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return  I(@"删除");
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle
forRowAtIndexPath:(NSIndexPath *)indexPath
{
	if(!m_pContenthandler)
		return;
	// If row is deleted, remove it from the list.
	if (editingStyle == UITableViewCellEditingStyleDelete)
	{
		((CMFavorites*)m_pContenthandler)->RemoveItem(indexPath.row);
		[self GetBrowserList];
	}
	else if(editingStyle == UITableViewCellEditingStyleInsert)
	{
	}
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    
	if(!m_pContenthandler)
    {
        
      //  tableviewlist.separatorStyle =UITableViewCellSeparatorStyleNone;
		return 0;
    }
	int head = 0;
    
    if(m_pContenthandler->GetHeadItemCount()>0)
        head = 1;
    
    if(m_pContenthandler->GetItemCount()>0)
    {
        
      //  tableviewlist.separatorStyle =UITableViewCellSeparatorStyleNone;
    }else
    {
      //  tableviewlist.separatorStyle =     UITableViewCellSeparatorStyleSingleLine;
        
        
    }
    
	if (![self HasMore] || SETTING.GetAutoLoadMore()) {
		return m_pContenthandler->GetItemCount()+head;
	}
	return m_pContenthandler->GetItemCount()+head+1;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
	int row = indexPath.row;

    //需要判断
    TBrowserItem* item = NULL;
    
    if(m_pContenthandler->GetHeadItemCount() > 0)
    {
        if(row == 0)
            return;
        else
            row--;
    }
    
    if(m_pContenthandler->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();

    }
    
	if (row == m_pContenthandler->GetItemCount())
    {
        SAFEDELETE(item);
		return;
    }
	m_pContenthandler->GetItem(row, item);
   // NSString * strFlag = [NSString stringWithUTF8String:item->sFlag];
    [self selItem:*item];
    
    SAFEDELETE(item);
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    TBrowserItem* browserItem = NULL;
    int row = indexPath.row;

	if(m_pContenthandler->GetHeadItemCount() > 0)
	{
		if(row == 0)
		{
			headheight = [UIImage imageNamed:@"headbg"].size.height;
            headheight=170;
			for(int i=0;i<m_pContenthandler->GetHeadItemCount();i++)
			{

                TBrowserItem *headitem = new TClassItem();
				m_pContenthandler->GetHeadItem(i,headitem);
				if(m_pWebImage->GetFromUrl(0,headitem->sThumbs))
				{
			
				}

                SAFEDELETE(headitem);
			}
            return headheight;
		}
		else
			row --;
	}

    if(m_pContenthandler->GetItemModel(row)==0)
    {
        browserItem = new TClassItem();
    }
    else
    {
        browserItem = new TCoursewareItem();
    }
    

    if(row == m_pContenthandler->GetItemCount())
    {
        SAFEDELETE(browserItem);
		return 44;
    }
	m_pContenthandler->GetItem(row, browserItem);
    
    NSString * strFlag = [NSString stringWithUTF8String:browserItem->sFlag];

    if([strFlag isEqualToString:@"news"])
    {
        
        SAFEDELETE(browserItem);
        return 92;
    }
    else
    {
        CGFloat tempf =[CMClassTableViewCell GetCellHeight:*browserItem webimage:NULL width:self.frame.size.width];
        
        
        SAFEDELETE(browserItem);

        
        return tempf;
    }
    
    
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
	int row = indexPath.row;
	if(m_pContenthandler->GetHeadItemCount() > 0)
	{
		if(row == 0)
		{

            if(headCell == nil)
            {
                CGRect frame = CGRectMake(0,0,tableviewlist.frame.size.width,44);
                headCell = [[XLCycleScrollView alloc] initWithFrame:frame];
                headCell.delegate = self;
                headCell.datasource = self;
            }

			[headCell loadData];
			headCell.accessoryType = UITableViewCellAccessoryNone;
			headCell.selectionStyle = UITableViewCellSelectionStyleNone;
			return headCell;
            
		}
		else
			row --;
	}
    
    //更多
	if (row == m_pContenthandler->GetItemCount() &&  m_pContenthandler->GetItemCount()!= 0)
		return [super tableView:tableView cellForRowAtIndexPath:indexPath];
    
    TBrowserItem* browserItem = NULL;
    
    if(m_pContenthandler->GetItemModel(row)==0)
    {
     
        browserItem = new TClassItem();

    }
    else
    {
        browserItem = new TCoursewareItem();
    }

	m_pContenthandler->GetItem(row, browserItem);
   	
	NSString * strFlag = [NSString stringWithUTF8String:browserItem->sFlag];
	   
    UITableViewCell* basecell;
    
    if([strFlag isEqualToString:@"news"])
    {
        CMNewsCell* cell;
        basecell = (CMNewsCell*)[tableviewlist dequeueReusableCellWithIdentifier:kCellIdentifier];
        if (basecell == nil) {
#if ! __has_feature(objc_arc)
            basecell = [[[CMNewsCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] autorelease];
# else
            basecell = [[CMNewsCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
# endif
        }
        
        cell=(CMNewsCell*)basecell;
        [cell setcellinfo:*browserItem];
        
        if (isSearchMode) {
            
            if([self viewController].title == nil )
            {
                    [cell.lbltitle setAllKeyWordTextArray:[NSArray arrayWithObjects:nil] WithFont:[UIFont systemFontOfSize:17] AndColor:UIColorRGB(0xff7800)];
                
                   [cell.contentLabel setAllKeyWordTextArray:[NSArray arrayWithObjects:nil] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0xff7800)];
            }
            else
            {
            [cell.lbltitle setAllKeyWordTextArray:[NSArray arrayWithObjects:[self viewController].title,nil] WithFont:[UIFont systemFontOfSize:17] AndColor:UIColorRGB(0xff7800)];
            
            [cell.contentLabel setAllKeyWordTextArray:[NSArray arrayWithObjects:[self viewController].title,nil] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0xff7800)];
            }
            
        }

        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        basecell=cell;

    }
    else
    {
       browserItem->Refresh();

       CMClassTableViewCell* cell;
    
       basecell = (CMClassTableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
        
        cell=(CMClassTableViewCell*)basecell;

        
        if (cell == nil) {
# if ! __has_feature(objc_arc)
            cell = [[[CMClassTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] autorelease];
# else
            cell = [[CMClassTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier];
# endif
        }

        [cell setcellinfo:*browserItem webimage:nil];
        
        [cell.btnproject addTarget:self action:@selector(searchByMarkid:event:) forControlEvents:UIControlEventTouchUpInside];

        [cell.subtitleView addTarget:self action:@selector(gotoDetail:) forControlEvents:UIControlEventTouchUpInside];
        
        if (isSearchMode) {
            
            if([self viewController].title == nil )
            {
                [cell.lbltitle setAllKeyWordTextArray:[NSArray arrayWithObjects:nil] WithFont:[UIFont systemFontOfSize:17] AndColor:UIColorRGB(0xff7800)];
                
                [cell.lbsubtitle setAllKeyWordTextArray:[NSArray arrayWithObjects:nil] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0xff7800)];
            }
            else
            {
                [cell.lbltitle setAllKeyWordTextArray:[NSArray arrayWithObjects:[self viewController].title,nil] WithFont:[UIFont systemFontOfSize:17] AndColor:UIColorRGB(0xff7800)];
                
                [cell.lbsubtitle setAllKeyWordTextArray:[NSArray arrayWithObjects:[self viewController].title,nil] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0xff7800)];
            }

        }
        
        [cell.seriesView addTarget:self action:@selector(gotoClassdetail:event:) forControlEvents:UIControlEventTouchUpInside];

        if(!m_bHasDelete)
            cell.lbltime.text = [NSString stringWithUTF8String:browserItem->sPubdate];//发布时间
        
        
        if(m_bHasDelete)
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        else
            cell.accessoryType = UITableViewCellAccessoryNone;
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
        
        
        basecell=cell;
    }
    
    SAFEDELETE(browserItem);
	return basecell;
}


/**
  *	获取当前view的 viewController
  *
  *	@param	sender
  *	@param	event
  */
- (UIViewController*)viewController {
    for (UIView* next = [self superview]; next; next =
         next.superview) {
        UIResponder* nextResponder = [next nextResponder];
        if ([nextResponder isKindOfClass:[UIViewController
                                         class]]) {
            return (UIViewController*)nextResponder;
        }
    }
    return nil;
}

-(void)searchByMarkid:(id)sender event:(id)event
{
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:tableviewlist];
    
    int row =[tableviewlist indexPathForRowAtPoint:touchPoint].row;
    
    TBrowserItem* item = NULL;
    
    if(m_pContenthandler->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
        
    }

    
	if (row == m_pContenthandler->GetItemCount())
    {
        SAFEDELETE(item);
		return;
    }
	m_pContenthandler->GetItem(row, item);
    
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]] && ![nextResponder isKindOfClass:[CMBrowserControl class]]) {
			break;
		}
	}
	if(!nextResponder)
    {
	    SAFEDELETE(item);

        return;
        
    }
    
    UIViewController *viewControl = (UIViewController *)nextResponder;
    
    CMMarkViewController* markviewControl=[[CMMarkViewController alloc]init];
    markviewControl.hidesBottomBarWhenPushed=YES;
    UIButton *btn          = (UIButton *)sender;
    markviewControl.title  = btn.titleLabel.text;
    markviewControl.MarkID = [NSString stringWithUTF8String:item->sMarkID];
    [viewControl.navigationController pushViewController:markviewControl animated:YES];
    self.willRefreshList = NO;//返回的时候不刷新
    CMRELEASE(markviewControl);
    //......
    
    SAFEDELETE(item);
    
}

-(void)gotoClassdetail:(id)sender event:(id)event
{
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:tableviewlist];
    
    int row =[tableviewlist indexPathForRowAtPoint:touchPoint].row;
    
    //需要判断
    TBrowserItem* item= NULL;
    
	if (row == m_pContenthandler->GetItemCount())
		return;
    
    if(m_pContenthandler->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
    }
    
	m_pContenthandler->GetItem(row, item);
    
    TBrowserItem *bitem = new TBrowserItem();
    bitem->nModel = 0;
    strcpy(bitem->sID, ((TCoursewareItem*)item)->sSetID);
    strcpy(bitem->sFlag, item->sFlag);

    
    SAFEDELETE(item);
	
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
	
    
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
	[nav NavgateItem:(UIViewController*)nextResponder item:*bitem];
    self.willRefreshList = NO;//返回不刷新
    CMRELEASE(nav);
    SAFEDELETE(bitem);
    [tableviewlist deselectRowAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0] animated:NO];

    
}

-(BOOL)RefreshMore
{
    
}

// set marktitle
- (void)setMarkTitle:(NSString *)marktitle markId:(NSInteger)markid withTableViewCell:(CMClassTableViewCell *)cell{
    
    if (!markid) {
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateHighlighted];
    }
    else if([marktitle isEqualToString:@"精品"]){
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_Boutique_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_Boutique_select"] forState:UIControlStateHighlighted];
    }
    else if ([marktitle isEqualToString:@"热点"]){
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_hot_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_hot_select"] forState:UIControlStateHighlighted];
    }
    else if (markid == 500){//500 mark id
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_teacher_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_teacher_select"] forState:UIControlStateHighlighted];
    }
    else if([marktitle isEqualToString:@"默认"]){
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_project_normal"] forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:[UIImage imageNamed:@"learn_project_select"] forState:UIControlStateHighlighted];
    }
    if (marktitle == nil || [marktitle length] <= 0) {
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateNormal];
        [cell.btnproject setBackgroundImage:nil forState:UIControlStateHighlighted];
        
        cell.isShowMark = NO;

    }
    else{
        cell.isShowMark = YES;
    }
    cell.btnproject.tag = markid;
    [cell.btnproject setTitle:marktitle forState:UIControlStateNormal];

}

- (void)gotoDetail:(UIButton *)button{
    
    UITableViewCell *cell = nil;
    
    //ios7.0 多了一层view
    for (UIView* next = [button superview]; next; next = next.superview) {
        if ([next isKindOfClass:[UITableViewCell class]]) {
            cell = (UITableViewCell*)next;
            break;
        }
    }
    NSIndexPath *indexPath = [self.tableviewlist indexPathForCell:cell];

	int row = indexPath.row;
    //需要判断
    
    TBrowserItem* item = NULL;
    
    if(m_pContenthandler->GetItemModel(row)==0)
    {
        item = new TClassItem();
    }
    else
    {
        item = new TCoursewareItem();
        
    }
	
    if (row == m_pContenthandler->GetItemCount())
    {
        SAFEDELETE(item);
		return;
    }
	m_pContenthandler->GetItem(row, item);
	[self selItem:*item];
    
    SAFEDELETE(item);
}

-(void)selItem:(TBrowserItem&)item
{
	UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]] && ![nextResponder isKindOfClass:[CMBrowserControl class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
	
	int selrow = 0;
	if(_stricmp(item.sFlag,"course") == 0)
		selrow = -1;
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];

	[nav NavgateItem:(UIViewController*)nextResponder item:item];
    self.willRefreshList = NO;//返回不刷新


    CMRELEASE(nav);
	
}
- (NSInteger)numberOfPages
{
    return m_pContenthandler->GetHeadItemCount();
}

- (UIView *)pageAtIndex:(NSInteger)index//画出头条标题
{
	if(curView)
        CMRELEASE(curView);
	curView = [[UIView alloc]init];
	UIImageView* bgImageView = [[UIImageView alloc] init];
    TBrowserItem* browserItem;
    
    if(m_pContenthandler->GetHeadItemModel(index)==0)
    {
        TClassItem temp;
        browserItem = &temp;
    }
    else
    {
        TCoursewareItem temp;
        browserItem = &temp;
    }
    
	m_pContenthandler->GetHeadItem(index,browserItem);
    
    NSString *url = [NSString stringWithUTF8String:browserItem->sLargeimage];
    
    if (!url || [url isEqualToString:@""] || [url length] == 0) {
        url = [NSString stringWithUTF8String:browserItem->sImage];
    }
    
    [bgImageView sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:[UIImage imageNamed:@"headbg"]];
    
	CGRect rc = CGRectMake(0, 0, tableviewlist.frame.size.width, headheight);
	headCell.frame = rc;
	curView.frame = rc;
	bgImageView.frame = rc;
	
	NSArray *subViews = [curView subviews];
	if([subViews count] != 0)
		[subViews makeObjectsPerformSelector:@selector(removeFromSuperview)];
	
	UIImage* image = [UIImage imageNamed:@"head_bottom"];
	rc.origin.y = headheight-image.size.height;
	rc.size.height = image.size.height;
	UIImageView* ImageView = [[UIImageView alloc] init];
	ImageView.frame = rc;
	image = [image stretchableImageWithLeftCapWidth:2 topCapHeight:1];
	ImageView.image = image;
	
	UILabel* lbtxt = [[UILabel alloc] init];
	lbtxt.text = [NSString stringWithUTF8String:browserItem->sTitle];
    lbtxt.numberOfLines = 0;
    lbtxt.lineBreakMode=NSLineBreakByTruncatingTail;
	lbtxt.font = [UIFont systemFontOfSize:kTextSizeSml];
	lbtxt.backgroundColor = [UIColor clearColor];
	lbtxt.textColor = [UIColor whiteColor];
    
	
    rc.origin.x   = 5;
    rc.size.width = 320-[headCell.datasource numberOfPages]*20;//头条的文字长度
    lbtxt.frame   = rc;
	
	[curView addSubview:bgImageView];
	//curView.backgroundColor = [UIColor colorWithRed:233.0/255.0 green:232.0/255.0 blue:232.0/255.0 alpha:1];
	[curView addSubview:ImageView];
	[curView addSubview:lbtxt];
    CMRELEASE(bgImageView);
    CMRELEASE(ImageView);
    CMRELEASE(lbtxt);
	return curView;
}

- (void)didClickPage:(XLCycleScrollView *)csView atIndex:(NSInteger)index
{
	if(index < 0 || index > m_pContenthandler->GetHeadItemCount())
		return;
    
    TBrowserItem* browserItem = NULL;
    
    if(m_pContenthandler->GetHeadItemModel(index)==0)
    {
        browserItem = new TClassItem;
    }
    else
    {
        browserItem = new TCoursewareItem;
    }
	m_pContenthandler->GetHeadItem(index,browserItem);
	[self selItem:*browserItem];
    SAFEDELETE(browserItem);
}
- (void)dealloc
{
    CMRELEASE(curView);
    CMRELEASE(headCell);
	SAFEDELETE(m_pGetImageListener);
	SAFEDELETE(m_pWebImage);
    
# if ! __has_feature(objc_arc)
    [super dealloc];
#endif
}

@end