//
//  ViewController.m
//  RenderiOS
//
//  Created by qz on 10/18/18.
//  Copyright © 2018 Taobao. All rights reserved.
//

#import "ViewController.h"
#import "GLViewController.h"
#import "CardListViewController.h"

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>
{
    NSArray *_listData;
}
@end

@implementation ViewController

-(void)viewDidLoad
{
    self.title = @"Render Demos";
    self.view.backgroundColor = [UIColor whiteColor];
    _listData = @[@"native-list",
                  @"bench12948",
                  @"card",
                  @"weexlist",
                  @"786",
                  @"absolute",
                  @"backgroundLinear",
                  @"boxshadow",
                  @"card3",
                  @"card4",
                  @"card5",
                  @"cardback",
                  @"carditem2",
                  @"imagetext",
                  @"picture",
                  @"richtext"
                  ];
    UITableView *tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStyleGrouped];
    CGRect frame = CGRectMake(0, 0, 0, CGFLOAT_MIN);
    tableView.tableHeaderView = [[UIView alloc]initWithFrame:frame];
    tableView.dataSource = self;
    tableView.delegate = self;
    tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    tableView.rowHeight = 50;
    [self.view addSubview:tableView];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier =@"identifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.textLabel.text = _listData[indexPath.row];
    }
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return _listData.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *name = _listData[indexPath.row];
    if (![name isEqualToString:@"native-list"]) {
        GLViewController *vc = [GLViewController new];
        vc.name = name;
        [self.navigationController pushViewController:vc animated:YES];
    }
    else
    {
        CardListViewController *vc = [CardListViewController new];
        [self.navigationController pushViewController:vc animated:YES];
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

@end



