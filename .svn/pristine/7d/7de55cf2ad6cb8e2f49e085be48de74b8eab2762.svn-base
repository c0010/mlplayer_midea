//
//  CMAddressInfoControl.h
//  MLPlayer
//
//  Created by sunjj on 12-2-21.
//  Copyright 2012 w. All rights reserved.
//

#import "stdafx.h"
#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmcontacts.h"
#include "cmwebimage.h"

class CMAddressInfoGetImageListener;
@interface CMAddressInfoControl : CMViewController <UITableViewDelegate,UITableViewDataSource>{
	
    CMContacts* m_pContacts;
	
	UITableView* ListTableView;
	TContactsItem m_TContactsItem;
	
	CMWebImage* m_pWebImage;
	CMAddressInfoGetImageListener* m_pImageListener;
}
@property(nonatomic,strong)UITableView* ListTableView;
@property(nonatomic,assign)BOOL isFromChat;
@property(nonatomic,assign)BOOL isOwner;

-(void)getAddItem:(TContactsItem)item;
@end
class CMAddressInfoGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMAddressInfoControl* addresscontrol = (__bridge CMAddressInfoControl*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[addresscontrol.ListTableView reloadData];
		}else {
			//[tool ShowError:Result];			
		}
	}
};
