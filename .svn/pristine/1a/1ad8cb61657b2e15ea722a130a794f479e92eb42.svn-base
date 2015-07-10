//
//  CMClassTopView.h
//  MLPlayer
//
//  Created by wangjianbin on 15/6/25.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMItemView.h"
class CMUpdateTopDataListener;
@interface CMClassTopView : CMItemView
{
    CMUpdateTopDataListener *m_pListener;
    
    char m_courseid[64];
    NSString* m_type;
}
- (void)setCourseID:(const char*)courseid type:(NSString*)type;
- (void)loadData;

@end

class CMUpdateTopDataListener : public IMUpdateDataListener
{
public:
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        [tool DisimissActivityIndicator];
        CMClassTopView *classTop = (CMClassTopView*)BridgeObjectToOC(UserData);
        [classTop setHasMore:NO];
        [classTop GetBrowserList];
        if (Result == TResult::ESuccess || Result == TResult ::ENothing)
        {
            
        }
        else
        {
            [tool ShowError:Result];
        }
    }
};
