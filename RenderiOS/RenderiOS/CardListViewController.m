//
//  CardListViewController.m
//  RenderiOS
//
//  Created by qz on 10/29/18.
//  Copyright © 2018 Taobao. All rights reserved.
//

#import "CardListViewController.h"
#import "CardCell.h"

@interface CardListViewController ()<UITableViewDelegate,UITableViewDataSource>
@end

@implementation CardListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"native-list";
    UITableView *tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStyleGrouped];
    CGRect frame = CGRectMake(0, 0, 0, CGFLOAT_MIN);
    tableView.tableHeaderView = [[UIView alloc]initWithFrame:frame];
    tableView.dataSource = self;
    tableView.delegate = self;
    tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    tableView.rowHeight = 240;
    [self.view addSubview:tableView];
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier =@"identifier2";
    CardCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (!cell) {
        cell = [[CardCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
    }
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 200;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

@end
