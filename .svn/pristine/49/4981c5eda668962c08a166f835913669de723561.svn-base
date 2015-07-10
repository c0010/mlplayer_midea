//
//  CMBrowserView.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMItemView.h"
#include "cmfavorites.h"

@interface CMFavoriteView : UIView
<UITableViewDelegate,UITableViewDataSource>
{
    CMFavorites *m_pCMFavorite;
    
	CMTableView *m_pTableView;
    UIView* bgview;

}

- (void)LoadData;
-(void)refreshView;
@end
