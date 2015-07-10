//
//  CMApplicationControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-16.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableView.h"
#include "cmcategory.h"

@interface CMApplicationControl : CMViewController <UITableViewDelegate,UITableViewDataSource,UINavigationControllerDelegate,UICollectionViewDelegate,UICollectionViewDataSource,UICollectionViewDelegateFlowLayout>{
	CMCategoryItem* m_pCategoryItem;
    
    int nSurveyCount;
    int nExamCount;
    int nNoSignCount;
    
    UICollectionView *collectionViewList;
    
    NSInteger nSelectRow;
}

@property(nonatomic,assign)NSUInteger Parentid;
@property(nonatomic,weak)NSString *strTitle;
- (void)surveycountchanged:(id)sender;
@end
