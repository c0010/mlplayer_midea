//
//  CMNewGroupViewController.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-16.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmcommon.h"
#import "cmgroup.h"
#import "cmfileinfo.h"
#import "GlobalAlertCenter.h"
#import "cmupload.h"
#import "CMViewController.h"

class CMGroupDataUpdateListener;
@class PlaceholderTextView;

@interface CMNewGroupViewController : CMViewController<UITextFieldDelegate,UITableViewDataSource,UITableViewDelegate,UIActionSheetDelegate,UITextViewDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate,UITextFieldDelegate>
{

    CMGroup* m_pGroup;
    CMGroupDataUpdateListener* m_pCmGroupDataListener;

    int poisition;
    
    NSUInteger input_words_num;
    UILabel* words_Num;

    NSString *nameText;
    NSString *imagePath;
    
    UITableView *thetableView;

    BOOL endEdit;
}
@property(nonatomic,strong) NSArray *verArray;
@property(nonatomic,strong) UITextField *nameTextfield;
@property(nonatomic,strong) PlaceholderTextView *descTextView;
@property(nonatomic,strong) UIImage *currImage;
@property (nonatomic, strong) UILabel *titleLabel;

@end


class CMGroupDataUpdateListener:public IMUpdateDataListener {

public:

    CMGroupDataUpdateListener(){};
    ~CMGroupDataUpdateListener(){};

    void OnUpdateDataProgress(void* UserData, int nPercent)
    {

        NSLog(@"finish;");

    }

    void  OnUpdateDataFinish(void* UserData, int Result)
    {

        NSLog(@"finish;");
    }
};

//自定义带Placeholder的textview
@interface PlaceholderTextView : UITextView

@property (nonatomic, weak) NSString *placeholder;

@end