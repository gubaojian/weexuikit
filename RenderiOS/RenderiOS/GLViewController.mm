//
//  GLViewController.m
//  RenderiOS
//
//  Created by qz on 10/28/18.
//  Copyright © 2018 Taobao. All rights reserved.
//

#import "GLViewController.h"
#import "RenderView.h"


@interface GLViewController ()

@end

@implementation GLViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    self.navigationController.navigationBar.translucent = NO;
    self.edgesForExtendedLayout = UIRectEdgeNone;
    self.title = _name;
    
    RenderView *renderview = [[RenderView alloc]initWithFrame:self.view.bounds jsonName:_name];
    [self.view addSubview:renderview];
}


@end
