//
//  RenderView.h
//  RenderiOS
//
//  Created by qz on 10/29/18.
//  Copyright © 2018 Taobao. All rights reserved.
//

#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RenderView : GLKView
- (instancetype )initWithFrame:(CGRect)frame jsonName:(NSString *)name;
@end

NS_ASSUME_NONNULL_END
