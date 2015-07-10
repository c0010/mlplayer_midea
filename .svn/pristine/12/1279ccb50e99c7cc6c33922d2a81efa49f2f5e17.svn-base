//
//  CMSysMessageCell.m
//  MLPlayer
//
//  Created by water on 14-6-24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMSysMessageCell.h"
#import "tool.h"
#import "CMInteractViewController.h"

@implementation CMSysMessageCell
@synthesize titleLabel,middleLabel,descrLabel,agreeButton,agreeLabel;
@synthesize cellDelegate;
@synthesize cellType = _cellType;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    
    if (self) {

        self.titleLabel = [[CMLabel alloc]initWithFrame:CGRectMake(10, 8, 220, 21)];
        self.titleLabel.backgroundColor = [UIColor clearColor];
        self.titleLabel.font = [UIFont systemFontOfSize:13.f];
        self.titleLabel.numberOfLines = 0;
        self.titleLabel.lineBreakMode = NSLineBreakByWordWrapping | NSLineBreakByTruncatingTail;
        [self.contentView addSubview:self.titleLabel];
        
        self.middleLabel = [[CMLabel alloc]initWithFrame:CGRectMake(10, 30, 220, 21)];
        self.middleLabel.backgroundColor = [UIColor clearColor];
        self.middleLabel.numberOfLines = 0;
        self.middleLabel.lineBreakMode = NSLineBreakByWordWrapping | NSLineBreakByTruncatingTail;
        self.middleLabel.font = [UIFont systemFontOfSize:13.f];
        [self.contentView addSubview:self.middleLabel];
        
        self.descrLabel = [[CMLabel alloc]initWithFrame:CGRectMake(10, 32, 220, 21)];
        self.descrLabel.backgroundColor = [UIColor clearColor];
        self.descrLabel.textColor = [UIColor lightGrayColor];
        self.descrLabel.numberOfLines = 1;
        self.descrLabel.font = [UIFont systemFontOfSize:13.f];
        [self.contentView addSubview:self.descrLabel];
        
        self.agreeLabel = [[CMLabel alloc]initWithFrame:CGRectMake(234, 25, 56, 30)];
        self.agreeLabel.backgroundColor = [UIColor clearColor];
        self.agreeLabel.textColor = [UIColor lightGrayColor];
        self.agreeLabel.textAlignment = UITextAlignmentCenter;
        self.agreeLabel.font = [UIFont systemFontOfSize:13.f];
        [self.contentView addSubview:self.agreeLabel];
        
        self.agreeButton = [[UIButton alloc]initWithFrame:self.agreeLabel.frame];
        self.agreeButton.titleLabel.font = [UIFont systemFontOfSize:13.f];
        [self.agreeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [self.agreeButton setTitle:I(@"同意") forState:UIControlStateNormal];
        [self.agreeButton setBackgroundImage:[UIImage imageNamed:@"interact_agree_btn_normal"] forState:UIControlStateNormal];
        [self.agreeButton setBackgroundImage:[UIImage imageNamed:@"interact_agree_btn_highlight"] forState:UIControlStateHighlighted];
        [self.agreeButton addTarget:self action:@selector(agreeButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.contentView addSubview:self.agreeButton];
        
    }
    return self;
}

- (void)awakeFromNib
{

}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (IBAction)agreeButtonPressed:(UIButton *)sender{
    if ([cellDelegate respondsToSelector:@selector(CMSysMessageCell:didSelectedAtIndex:)]) {
        [cellDelegate CMSysMessageCell:self didSelectedAtIndex:sender.tag];
    }
}

- (void)setItem:(CMMessageItem *)item{

    if(item.type == CMInteractSystemMessageTypeCreate){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(0, roomName.length) WithFont:self.middleLabel.font AndColor:UIColorRGB(0x083E73)];
        
    }else if(item.type == CMInteractSystemMessageTypeQuit){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:self.middleLabel.font AndColor:UIColorRGB(0x083E73)];
        [self.middleLabel setKeyWordRange:NSMakeRange(0, item.sysmessage.rawSenderName.length) WithFont:self.middleLabel.font AndColor:UIColorRGB(0x083E73)];
    }else if(item.type == CMInteractSystemMessageTypeRefuse){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        
        NSString *roomName = item.sysmessage.roomName;
        NSString *content = item.content;
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:self.titleLabel.font AndColor:UIColorRGB(0x083E73)];
        
    }else if(item.type == CMInteractSystemMessageTypeInvite){
        self.selectionStyle = UITableViewCellSelectionStyleGray;

        switch (item.sysmessage.state) {
            case CMSysMessageStateAgree:
            {
                self.agreeButton.hidden = YES;
                self.agreeLabel.hidden = NO;
                self.agreeLabel.text = I(@"已同意");
                self.selectionStyle = UITableViewCellSelectionStyleNone;
                self.cellType = CMSysMessageCellSingleType;
                self.agreeLabel.hidden = NO;

            }
                break;
            case CMSysMessageStateRefuse:
            {
                self.agreeButton.hidden = YES;
                self.agreeLabel.hidden = NO;
                self.agreeLabel.text = I(@"已拒绝");
                self.selectionStyle = UITableViewCellSelectionStyleNone;
                self.cellType = CMSysMessageCellSingleType;
                
                self.agreeLabel.hidden = NO;

            }
                break;
            default:
                self.cellType = CMSysMessageCellSingleTypeEdit;
                break;
        }
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:self.middleLabel.font AndColor:UIColorRGB(0x083E73)];
        [self.middleLabel setKeyWordRange:NSMakeRange(0, item.sysmessage.rawSenderName.length) WithFont:self.middleLabel.font AndColor:UIColorRGB(0x083E73)];

    }else if(item.type == CMInteractSystemMessageTypeApply){
        self.selectionStyle = UITableViewCellSelectionStyleGray;

        switch (item.sysmessage.state) {
            case CMSysMessageStateAgree:
            {
                self.agreeButton.hidden = YES;
                self.agreeLabel.hidden = NO;
                self.agreeLabel.text = I(@"已同意");
                self.selectionStyle = UITableViewCellSelectionStyleNone;
                self.cellType = CMSysMessageCellDoubleType;
                
                self.agreeLabel.hidden = NO;
            }
                break;
            case CMSysMessageStateRefuse:
            {
                self.agreeButton.hidden = YES;
                self.agreeLabel.hidden = NO;
                self.agreeLabel.text = I(@"已拒绝");
                self.selectionStyle = UITableViewCellSelectionStyleNone;
                self.cellType = CMSysMessageCellDoubleType;
                
                self.agreeLabel.hidden = NO;
            }
                break;
            default:
                self.cellType = CMSysMessageCellDoubleTypeEdit;
                break;
        }
        NSString *roomName = item.sysmessage.roomName;
        self.titleLabel.text = item.content;
        [self.titleLabel setKeyWordRange:NSMakeRange(item.content.length - roomName.length, roomName.length) WithFont:self.titleLabel.font AndColor:UIColorRGB(0x083E73)];
        [self.titleLabel setKeyWordRange:NSMakeRange(0, item.sysmessage.rawSenderName.length) WithFont:self.titleLabel.font AndColor:UIColorRGB(0x083E73)];
        self.descrLabel.text = [NSString stringWithFormat:I(@"验证信息：%@"),item.sysmessage.key.length > 0 ? item.sysmessage.key : I(@"无")];
    }else if(item.type == CMInteractSystemMessageTypeSetManager){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(6, roomName.length) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0x083E73)];
    }else if(item.type == CMInteractSystemMessageTypeCancelManager){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(7, roomName.length) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0x083E73)];
        
    }else if(item.type == CMInteractSystemMessageTypeDisBand){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(0, roomName.length) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0x083E73)];
        
    }else if(item.type == CMInteractSystemMessageTypeRefuse){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text =  [NSString stringWithFormat:I(@"您已被拒绝加入群 %@"),roomName];
        [self.middleLabel setKeyWordRange:NSMakeRange(0, roomName.length) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0x083E73)];
        
    }else if(item.type == CMInteractSystemMessageTypePassApply){
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0x083E73)];
        
    }else{
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        self.cellType = CMSysMessageCellSingleType;
        NSString *content = item.content;
        NSString *roomName = item.sysmessage.roomName;
        
        self.middleLabel.text = content;
        [self.middleLabel setKeyWordRange:NSMakeRange(content.length - roomName.length, roomName.length) WithFont:[UIFont systemFontOfSize:13] AndColor:UIColorRGB(0x083E73)];
    }
}

- (void)setSubViewsFrame:(NSString *)content{
    
    switch (self.cellType) {
        case CMSysMessageCellDoubleTypeEdit:
        {
            CGSize size = [content sizeWithFont:self.titleLabel.font constrainedToSize:CGSizeMake(220, 100) lineBreakMode:NSLineBreakByWordWrapping];
            
            [self.titleLabel setFrameY:UP Height:size.height];
            
            [self.descrLabel setFrameY:CGRectGetMaxY(self.titleLabel.frame) + 10];
            
            [self.agreeButton setCenterY:(CGRectGetMaxY(self.descrLabel.frame) + UP)/2];
        }
            break;
        case CMSysMessageCellDoubleType:
        {
            CGSize size = [content sizeWithFont:self.titleLabel.font constrainedToSize:CGSizeMake(220, 100) lineBreakMode:NSLineBreakByWordWrapping];
            
            [self.titleLabel setFrameY:UP Height:size.height];
            
            [self.descrLabel setFrameY:CGRectGetMaxY(self.titleLabel.frame) + 10];
            
            [self.agreeLabel setCenterY:(CGRectGetMaxY(self.descrLabel.frame) + UP)/2];
            
        }
            break;
        case CMSysMessageCellSingleTypeEdit:
        {
            CGSize size = [content sizeWithFont:self.titleLabel.font constrainedToSize:CGSizeMake(220, 100) lineBreakMode:NSLineBreakByWordWrapping];
            
            [self.middleLabel setFrameHeight:size.height];
            
            [self.middleLabel setCenterY:(size.height + UP * 3)/2];
            [self.agreeButton setCenterY:(size.height + UP * 3)/2];
        }
            break;
        case CMSysMessageCellSingleType:
        {
            CGSize size = [content sizeWithFont:self.titleLabel.font constrainedToSize:CGSizeMake(220, 100) lineBreakMode:NSLineBreakByWordWrapping];
            
            [self.middleLabel setFrameHeight:size.height];
            
            [self.middleLabel setCenterY:(size.height + UP * 3)/2];
            [self.agreeLabel setCenterY:(size.height + UP * 3)/2];
        }
            break;
        default:
            break;
    }
}

- (CGFloat)getCellHeight:(CMMessageItem *)item
{
    CGFloat cellHeight;
    
    if(item.type == CMInteractSystemMessageTypeApply){
        cellHeight =  CGRectGetMaxY(self.descrLabel.frame) + UP;
    }else{
        cellHeight =  CGRectGetHeight(self.middleLabel.frame) + UP * 3;
    }
    
    return cellHeight;
}

- (void) setCellType:(enum CMSysMessageCellType)cellType{
    _cellType = cellType;
    if (_cellType == CMSysMessageCellDoubleTypeEdit) {
        //双行
        self.middleLabel.hidden = YES;
        self.agreeLabel.hidden = YES;
        self.titleLabel.hidden = NO;
        self.descrLabel.hidden = NO;
        self.agreeButton.hidden = NO;
        
        [self.agreeButton setFrameY:15];
        [self.agreeLabel setFrameY:15];
    }else if(_cellType == CMSysMessageCellDoubleType){
        self.middleLabel.hidden = YES;
        self.agreeLabel.hidden = YES;
        self.titleLabel.hidden = NO;
        self.descrLabel.hidden = NO;
        self.agreeButton.hidden = YES;
    }else if(_cellType == CMSysMessageCellSingleType){
        self.middleLabel.hidden = NO;
        self.agreeLabel.hidden = YES;
        self.titleLabel.hidden = YES;
        self.descrLabel.hidden = YES;
        self.agreeButton.hidden = YES;
    }else if(_cellType == CMSysMessageCellSingleTypeEdit){
        self.middleLabel.hidden = NO;
        self.agreeLabel.hidden = YES;
        self.titleLabel.hidden = YES;
        self.descrLabel.hidden = YES;
        self.agreeButton.hidden = NO;
    }
}

@end
