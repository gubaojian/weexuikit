//
//  CardCell.m
//  RenderiOS
//
//  Created by qz on 10/29/18.
//  Copyright © 2018 Taobao. All rights reserved.
//

#import "CardCell.h"
#import "RenderView.h"


@interface CardCell()
@property (nonatomic, strong) RenderView *renderView;
@end

@implementation CardCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
    }
    return self;
}

- (void)layoutSubviews
{
    [self.contentView addSubview:self.renderView];
}

- (RenderView *)renderView
{
    if (!_renderView) {
        _renderView = [[RenderView alloc]initWithFrame:self.contentView.bounds jsonName:@"card"];
    }
    return _renderView;
}

@end
