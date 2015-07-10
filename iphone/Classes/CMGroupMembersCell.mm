//
//  CMGroupMembersCell.m
//  MLPlayer
//
//  Created by water on 14-7-10.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupMembersCell.h"
#import "CMInteractConfig.h"

@implementation CMGroupMembersCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        
        
        self.headButton = [CMButton buttonWithType:UIButtonTypeCustom];
        [self.headButton setFrame:CGRectMake(10, 7.5, 40, 40)];
        [self.headButton setImage:DefaultHeaderImage];

        [self addSubview:self.headButton];
        
        self.optionButton= [CMButton buttonWithType:UIButtonTypeCustom];
        [self.optionButton setFrame:CGRectMake(255, 12.5, 55, 30)];
        [self addSubview:self.optionButton];
        
        self.titlelabel = [[UILabel alloc]initWithFrame:CGRectMake(60, 15, 200, 25)];
        self.titlelabel.backgroundColor = [UIColor clearColor];
        self.titlelabel.font = [UIFont systemFontOfSize:16.f];
        [self addSubview:self.titlelabel];
        
        self.accessoryLabel = [[UILabel alloc]initWithFrame:self.optionButton.frame];
        self.accessoryLabel.backgroundColor = [UIColor clearColor];
        self.accessoryLabel.textColor = [UIColor lightGrayColor];
        self.accessoryLabel.textAlignment = UITextAlignmentRight;
        self.accessoryLabel.font = [UIFont systemFontOfSize:16.f];
        [self addSubview:self.accessoryLabel];
        
        self.markButton= [CMButton buttonWithType:UIButtonTypeCustom];
        [self.markButton setFrame:CGRectMake(280, 15, 25, 25)];
        [self.markButton setImage:[UIImage imageNamed:@"interact_checkbox_normal"] forState:UIControlStateNormal];
        [self.markButton setImage:[UIImage imageNamed:@"interact_checkbox_selected"] forState:UIControlStateSelected];
        [self.markButton setImage:[UIImage imageNamed:@"interact_checkbox_selected"] forState:UIControlStateHighlighted];
        [self.markButton setImage:[UIImage imageNamed:@"interact_checkbox_disabled"] forState:UIControlStateDisabled];

        [self addSubview:self.markButton];
    }
    return self;
}

- (void)setCellType:(enum CMGroupMembersCellType)cellType{

    switch (cellType) {
        case CMGroupMembersCellTypeMain:
        {
            self.optionButton.hidden = YES;
            self.accessoryLabel.hidden = NO;
            self.markButton.hidden = YES;
        }
            break;
        case CMGroupMembersCellTypeManager:
        {
            self.optionButton.hidden = YES;
            self.accessoryLabel.hidden = NO;
            self.markButton.hidden = YES;
        }
            break;
        case CMGroupMembersCellTypeMemberDefault:
        {
            self.optionButton.hidden = YES;
            self.accessoryLabel.hidden = YES;
            self.markButton.hidden = YES;
        }
            break;
        case CMGroupMembersCellTypeMemberEdit:
        {
            self.optionButton.hidden = NO;
            self.accessoryLabel.hidden = YES;
            self.markButton.hidden = YES;
        }
            break;
        case CMGroupMembersCellTypeMemberMark:
        {
            self.optionButton.hidden = YES;
            self.accessoryLabel.hidden = YES;
            self.markButton.hidden = NO;
        }
            break;
        default:
            break;
    }
}

- (void)awakeFromNib
{
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
