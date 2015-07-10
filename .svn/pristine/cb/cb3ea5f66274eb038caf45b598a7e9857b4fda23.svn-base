//
//  cmitemcontroller.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMRefreshMoreView.h"
#include "cmcategory.h"
#include "cmcourseinfo.h"
#include "cmcontenthandler.h"
#include "cmfavorites.h"
#import "cmcommon.h"
#import "CMImage.h"
#import "XLCycleScrollView.h"
#import "CMNewsCell.h"
#import "CMNavgateItem.h"
#import "CMLabel.h"
#import <CoreText/CoreText.h>


class CMItemGetImageListener;

@interface CMItemView : CMRefreshMoreView<XLCycleScrollViewDatasource,XLCycleScrollViewDelegate>
{
	
    CMItemGetImageListener * m_pGetImageListener;
    CMWebImage             * m_pWebImage;
    CMContenthandler       * m_pContenthandler;
    BOOL                   m_bHasDelete;
    XLCycleScrollView      * headCell;
    UIView                 * curView;
    CGFloat                headheight;
    CMNewsCell             * newscell;


    int model;
}
@property (nonatomic,assign) BOOL                   HasDelete;
@property (nonatomic,assign) BOOL                   isSearchMode;
@property (nonatomic,assign) CMContenthandler     * Contenthandler;
@property (nonatomic,assign) CMWebImage           * m_pWebImage;
@property (nonatomic,strong) IBOutlet  CMNewsCell * newscell;
@property (nonatomic,assign)BOOL willRefreshList;//是否要重新读取数据，RequestType为1

-(id)initWithFrame:(CGRect)frame refresh:(BOOL)brefresh;
-(BOOL)RefreshMore;
-(void)selItem:(TBrowserItem&)item;
-(void)searchByMarkid:(id)sender event:(id)event;

@end

class CMItemGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMItemView* itemview = (__bridge CMItemView*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
			[itemview GetBrowserList];
		}else {
			//[tool ShowError:Result];
		}
	}
};