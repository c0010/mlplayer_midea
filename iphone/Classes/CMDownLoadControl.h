//
//  CMDownLoadControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-19.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMTableView.h"
#import "CMTableViewCell.h"
#import "CMViewController.h"
#import "cmcoursedownload.h"
#import "cmcourseinfo.h"
#import "cmwebimage.h"
#import "CMPlayerControl.h"
#import "CMDownLoadTableViewCell.h"
#import "CMImage.h"
#import "CMNavgateItem.h"

class CMNDownLoadGetImageListener;
class CMDownLoadProgressListener;


@interface CMDownLoadControl : CMViewController<UITableViewDelegate,UITableViewDataSource,CMNavgateItemDelegate> {

	
	NSMutableArray *openItemArray;
	NSMutableArray *RepeatItemArray;
	NSTimer *downTime0;
	
	UIScrollView *scrollView;
	NSIndexPath *selectedCellIndexPath;
	
	CMNDownLoadGetImageListener *m_pGetImageListener;
	CMWebImage * m_pWebImage;
    
    CMDownLoadProgressListener * m_pProgressListener;
    
    
    UIView* bgview;
    
@public
	CMTableView *TableViewList;
    NSMutableArray *itemArray ;
    
    int nProgressRate;

}

@property(nonatomic,strong) NSMutableArray* itemArray ;
@property(nonatomic,strong) NSMutableArray* openItemArray;
@property(nonatomic,strong) NSMutableArray *RepeatItemArray;


-(void)readPlistToArray;
@end

class CMNDownLoadGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {			
				//CMNewsInfo* cmLearnControl = (CMNewsInfo*)UserData;
				//[cmLearnControl GetBrowserList];
		}else {
			//[tool ShowError:Result];
		}
	}
};



class CMDownLoadProgressListener:public IMUpdateDataListener
{
   void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
        CMDownLoadControl* control=(__bridge CMDownLoadControl*)UserData;
        
        control->nProgressRate=nPercent;
//        [control->TableViewList performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:YES];
        for (NSDictionary *dict in control->itemArray) {
            if ([[dict objectForKey:@"iscomplete"] isEqualToString:@"0"]) {
                int integer = [[dict objectForKey:@"indexid"] intValue] + [[dict objectForKey:@"parentid"] intValue] + 1;
                NSIndexPath *indexPath = [NSIndexPath indexPathForRow:integer inSection:0];
                [control->TableViewList reloadRowsAtIndexPaths:[NSArray arrayWithObjects:indexPath, nil] withRowAnimation:UITableViewRowAnimationNone];
                return;
            }
        }

    };
    
    void OnUpdateDataFinish(void* UserData, int Result)
    {
        
        CMDownLoadControl* control=(__bridge CMDownLoadControl*)UserData;

        [control performSelectorOnMainThread:@selector(readPlistToArray) withObject:nil waitUntilDone:YES];
        [control->TableViewList performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:YES];

        
//        [control readPlistToArray];
//        [control->TableViewList reloadData];
        

        
    };

};

