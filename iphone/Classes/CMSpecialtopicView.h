//
//  CMBrowserView.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMItemView.h"
#include "cmspecialtopic.h"

class CMItemGetImageListener;
class CMSpecialtopicUpdateDataListener;
@interface CMSpecialtopicView : CMItemView {
	CMSpecialtopicUpdateDataListener* m_pUpdataDataListerner;
	
	UIImageView *TopImage;
}

-(id)initWithFrame:(CGRect)frame;
-(void)LoadData:(NSString*)sID;
@end

class CMSpecialtopicUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		CMSpecialtopicView* specialtopicview = (__bridge CMSpecialtopicView*)UserData;
		[tool CancelWait];
        [tool DisimissActivityIndicator];
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {	
			[specialtopicview GetBrowserList];
		}else {
			[tool ShowError:Result];			
		}
		
	}	
};
