//
//  CMHomeControl.h
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmcommon.h"
#import "CMImage.h"
#import "CMQListView.h"
#import "cmqacategory.h"         //新增，支持获取问题类别

class CMQAListCategoryUpdateDataListener;

@interface CMQaControl: CMViewController<UITableViewDataSource,UITableViewDelegate> {
	CMQListView* qlistview;
    
    CMQACategory *m_pQcategory;
    
    CMQAListCategoryUpdateDataListener *m_pUpdataDataListerner;
    
    
}

//问题分类下拉列表
@property(nonatomic,strong)UITableView *categoryList;
@property(nonatomic,strong)UIButton* lblCategoryList;
@property(nonatomic,strong)UIImageView* downListIndicator;
@property(nonatomic,strong)UIButton* lblBack;
-(void)refreshCategoryLit;
@end



class CMQAListCategoryUpdateDataListener: public IMUpdateDataListener             //新增，支持获取问题类别
{
public:
	CMQAListCategoryUpdateDataListener(){};
	~CMQAListCategoryUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        //CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMSurveyUpdateDataListener OnUpdateDataFinish Result=%d",Result);
		
		CMQaControl* control = (__bridge CMQaControl*)UserData;
        
		if(Result == TResult::ESuccess )
		{
            
            [control refreshCategoryLit];
		}else if (Result == TResult::ENothing) {
            [control refreshCategoryLit];

		}else {
            [tool DisimissActivityIndicator];
			[tool ShowError:Result];
		}
	}
    
};
