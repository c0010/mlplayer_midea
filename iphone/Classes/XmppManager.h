//
//  XmppManager.h
//  MLPlayer
//
//  Created by water on 14-9-17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XMPP.h"

@interface XmppManager : NSObject

@property(nonatomic,strong)XMPPStream * xmppStream;

@end
