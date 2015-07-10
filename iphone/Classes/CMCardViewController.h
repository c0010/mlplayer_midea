//
//  CMCardViewController.h
//  MLPlayer
//
//  Created by wmgwd on 13-12-9.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMViewController.h"
#import "cmcommon.h"

class CMWrongQuestion;
class CMExam;
class CMExamSimpleResultListener;

@interface CMCardViewController : CMViewController
<UITableViewDelegate, UITableViewDataSource>
{
    CMWrongQuestion *mWrongQuestion;
    NSString *mType;
    NSString *mQestionID;
    
    NSInteger nPassTime;
    
    CMExamSimpleResultListener *m_pSimpleListener;
}

- (void)setHandler:(CMWrongQuestion *)hanler questionType:(NSString *)type questionId:(NSString *)qID;
- (void)setPassTime:(NSInteger)count;
- (void)sendResult:(int)result;

@end

class CMExamSimpleResultListener : public IMSimpleResultListener {
	
public:
	CMExamSimpleResultListener(){};
	~CMExamSimpleResultListener(){};
	
	void OnRequestFinish(void* UserData, int Result)
	{
        NSLog(@"CMExamInfoSimpleResultListener OnRequestFinish Result = %d",Result);
        
		CMCardViewController* listView = (__bridge CMCardViewController*)UserData;
        
        [listView 	sendResult:Result];
	}
};