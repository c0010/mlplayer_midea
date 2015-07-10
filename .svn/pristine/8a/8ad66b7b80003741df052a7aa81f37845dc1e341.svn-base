//
//  CMSearchModel.h
//  MLPlayer
//
//  Created by water on 14-9-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cmcontacts.h"
#import "CMInteractModel.h"

@interface CMSearchModel : NSObject

@property(nonatomic,assign)NSInteger no;//数组中得序号
@property(nonatomic,assign)NSInteger type; // 0为用户，1为群组;

@property(nonatomic,strong)NSString* name;
@property(nonatomic,strong)NSString* icon;
@property(nonatomic,strong)NSString* phoneNum;
@property(nonatomic,strong)NSString* desc;
@property(nonatomic,strong)NSString* uid;
@property(nonatomic,assign)int manager;
@property(nonatomic,strong)NSString* jid;

+ (id)model;

//从联系人组装
- (CMSearchModel *)toCModel:(TContactsItem)item index:(int)index;

//从群组缓存组装
- (CMSearchModel *)toGModel:(CMGroupItem *)item index:(int)index;

//从会话缓存组装
- (CMSearchModel *)toDModel:(CMDialogueItem *)item index:(int)index;

//从群成员缓存缓存组装
- (CMSearchModel *)toMModel:(CMMemberItem *)item index:(int)index;
@end
