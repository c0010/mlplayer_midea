//
//  CMSearchModel.m
//  MLPlayer
//
//  Created by water on 14-9-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMSearchModel.h"

@implementation CMSearchModel


+ (id)model{
    return [[CMSearchModel alloc] init];
}

- (CMSearchModel *)toCModel:(TContactsItem)item index:(int)index{
    
    self.type = 0;
    self.no = index;
    self.name = [NSString stringWithUTF8String:item.sName.c_str()];
    self.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
    self.uid = [NSString stringWithUTF8String:item.sID.c_str()];
    self.desc = [NSString stringWithUTF8String:item.sDep.c_str()];
    self.manager = item.nIsManager;
    self.phoneNum = [NSString stringWithUTF8String:item.sMobilenumber.c_str()];

    self.jid = [NSString stringWithUTF8String:item.sJid.c_str()];
    return self;
}

- (CMSearchModel *)toGModel:(CMGroupItem *)item index:(int)index{
    
    self.type = 1;
    self.no = index;
    self.name = item.roomName;
    self.icon = item.icon;
    self.desc = I(@"来自群组");
    
    return self;
}

- (CMSearchModel *)toDModel:(CMDialogueItem *)item index:(int)index{
    
    self.type = 1;
    self.no = index;
    self.name = item.fromName;
    self.icon = item.icon;
    self.uid = item.fromID;

    return self;
}

- (CMSearchModel *)toMModel:(CMMemberItem *)item index:(int)index{
    
    self.type = 0;
    self.no = index;
    self.name = item.name;
    self.icon = item.icon;
    self.uid = item.uid;
    self.manager = [item.type intValue];

    return self;
}
@end
