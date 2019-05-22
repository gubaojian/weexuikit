//
//  RenderView.m
//  RenderiOS
//
//  Created by qz on 10/29/18.
//  Copyright © 2018 Taobao. All rights reserved.
//

#import "RenderView.h"
#import <GLKit/GLKView.h>
#include "OpenGL_ios.h"
#include <render/frame/RenderFrame.h>
#include <render/frame/RenderFrameView.h>
#include <render/public/RendererEngine.h>
#include <render/core/parser/Screen.h>
#include <render/gesture/gesture/PointerEvent.h>

@interface RenderView()
{
    weexrender::RenderFrameView* frameview;
    weexrender::IOSOpenGLSkiaRender* render;
}
@end

@implementation RenderView
- (instancetype )initWithFrame:(CGRect)frame jsonName:(NSString *)name
{
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor whiteColor];
        render = new weexrender::IOSOpenGLSkiaRender();
        render->create((CAEAGLLayer*)self.layer);
        
        blink::initEngine();
        weexrender::Screen::mDeviceDensity = [[UIScreen mainScreen] scale];
        weexrender::Screen::mDeviceWidth = [UIScreen mainScreen].bounds.size.width * weexrender::Screen::mDeviceDensity;
        weexrender::Screen::mDeviceHeight = [UIScreen mainScreen].bounds.size.height * weexrender::Screen::mDeviceDensity;
    
        frameview = new weexrender::RenderFrameView();
        frameview -> createRenderFrame();
        [self parseJSON:name];
        frameview->layoutFrame();
        frameview->paintFrame(render, true);
        render->drawFrame(true);
        render->swapBuffers();
        
        [self performVsync];
    }
    return self;
}

- (void)parseJSON:(NSString *)name
{
    NSString *jsonPath = [[NSBundle mainBundle] pathForResource:name ofType:@"json"];
    NSData *data = [NSData dataWithContentsOfFile:jsonPath];
    if(!data)
    {
        return;
    }
    NSError *error = nil;
    id result = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
    
    std::map<std::string, std::string> *attrs = new std::map<std::string, std::string>();
    std::map<std::string, std::string> *styles = new std::map<std::string, std::string>();
    std::set<std::string> *events = new std::set<std::string>();
    
    std::string ref = std::string([result[@"ref"] UTF8String]);
    std::string type = std::string([result[@"type"] UTF8String]);
    
    NSDictionary *ocstyle = result[@"style"];
    [ocstyle enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        std::string styleKey = std::string([key UTF8String]);
        if ([obj isKindOfClass:[NSNumber class]]) {
            obj = [NSString stringWithFormat:@"%@",obj];
        }
        std::string styleVal = std::string([obj UTF8String]);
        styles->insert({styleKey,styleVal});
    }];
    
    NSDictionary *ocattr = result[@"attr"];
    [ocattr enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        std::string styleKey = std::string([key UTF8String]);
        std::string styleVal = std::string([obj UTF8String]);
        attrs->insert({styleKey,styleVal});
    }];
    styles->insert({"backgroundColor","white"});
    
    frameview->getRenderFrame()->actionCreateBody(ref, styles, attrs, events);
    [self parseChildren:result[@"children"] parent:result[@"ref"]];
}

- (void)parseChildren:(NSArray *)children parent:(NSString *)parendRef
{
    std::set<std::string> *events = new std::set<std::string>();
    
    [children enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        NSString *ocref = obj[@"ref"];
        std::string ref = std::string([obj[@"ref"] UTF8String]);
        std::string type = std::string([obj[@"type"] UTF8String]);
        std::string parentref = std::string([parendRef UTF8String]);
        int index = (int)idx;
        
        std::map<std::string, std::string> *styles = new std::map<std::string, std::string>();
        NSDictionary *ocstyle = obj[@"style"];
        [ocstyle enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
            std::string styleKey = std::string([key UTF8String]);
            if ([obj isKindOfClass:[NSNumber class]]) {
                obj = [NSString stringWithFormat:@"%@",obj];
            }
            std::string styleVal = std::string([obj UTF8String]);
            styles->insert({styleKey,styleVal});
        }];
        
        std::map<std::string, std::string> *attrs = new std::map<std::string, std::string>();
        NSDictionary *ocattr = obj[@"attr"];
        [ocattr enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
            std::string styleKey = std::string([key UTF8String]);
            std::string styleVal = std::string([obj UTF8String]);
            attrs->insert({styleKey,styleVal});
        }];
        self->frameview->getRenderFrame()->actionAddElement(ref, type, parentref, index, styles, attrs, events);
        if (obj[@"children"]) {
            [self parseChildren:obj[@"children"] parent:ocref];
        }
    }];
}

- (void)parseStyle:(NSDictionary *)styles
{
    std::map<std::string, std::string> *styles_ = new std::map<std::string, std::string>();
    [styles enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        std::string key_ = std::string([key UTF8String]);
        if ([obj isKindOfClass:[NSNumber class]]) {
            obj = [NSString stringWithFormat:@"%@",obj];
        }
        std::string obj_ = std::string([obj UTF8String]);
        styles_->insert({key_,obj_});
    }];
    if (!styles[@"backgroundColor"]) {
        styles_->insert({"backgroundColor","white"});
    }
}

- (void )parseAttr:(NSDictionary *)attr
{
    std::map<std::string, std::string> *attr_ = new std::map<std::string, std::string>();
    [attr enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) {
        std::string key_ = std::string([key UTF8String]);
        std::string obj_ = std::string([obj UTF8String]);
        attr_->insert({key_,obj_});
    }];
}




- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    //pointerCount++;
    float scale = 1; //[UIScreen mainScreen].scale;
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.superview];
    frameview->onTouch(PointerEvent::PointerAction::ActionPointerDown, 0, location.x * scale, location.y * scale,  (int64_t)([touch timestamp]*1000));
    
    /**
    PointerEvent down = createPointerEvent(PointerAction::ActionPointerDown);

    down.pointer = pointerCount;
    down.axisX = location.x * scale;
    down.axisY = location.y * scale;
    down.position.dx = 0;//location.x* scale;
    down.position.dy = 0;//location.y* scale;
    down.timeStamp = ([touch timestamp]*1000);
    documentview->dispatchTouchEvent(down);
    originallocation = [touch locationInView:self.superview];
     */
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    float scale =  1;// [UIScreen mainScreen].scale;
    CGPoint location = [touch locationInView:self.superview];
    frameview->onTouch(PointerEvent::PointerAction::ActionPointerMove, 0, location.x * scale, location.y * scale,  (int64_t)([touch timestamp]*1000));
    
    
    
    /**
    
    move.pointer = pointerCount;
    move.position.dx = location.x* scale;
    move.position.dy = location.y* scale;
    move.delta.dx =   location.x* scale -originallocation.x* scale;
    move.delta.dy =  location.y* scale - originallocation.y* scale;
    move.timeStamp = ([touch timestamp]*1000);
    
    //    NSLog(@"%f----qianzhi",location.y);
    documentview->dispatchTouchEvent(move);
    moveEvent = move;
    //    [self performSelector:@selector(performMovement) withObject:nil afterDelay:1.0/1000];
    //    [self performMovement];
    //    documentview->dispatchTouchEvent(movePointetEvent(moveEvent, 0, -1));
    originallocation = location;*/
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    float scale = 1;// [UIScreen mainScreen].scale;
    CGPoint location = [touch locationInView:self.superview];
    frameview->onTouch(PointerEvent::PointerAction::ActionPointerUp, 0, location.x * scale, location.y * scale,  (int64_t)([touch timestamp]*1000));
    
    /**
    end.pointer = pointerCount;
    end.position.dx = location.x* scale;
    end.position.dy = location.y* scale;
    end.timeStamp = ([touch timestamp]*1000);
    
    documentview->dispatchTouchEvent(end);
    // pointerCount--;*/
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event{
    [self touchesEnded:touches withEvent:event];
}


-(void) performVsync{
    int64_t interval = ([NSDate timeIntervalSinceReferenceDate]*1000);
    frameview->getTickerProvider()->checkTicker(interval);
    frameview->layoutFrame();
    frameview->paintFrame(render, true);
    render->drawFrame(true);
    render->swapBuffers();
    NSTimeInterval used = ([NSDate timeIntervalSinceReferenceDate]*1000) - interval;
    NSTimeInterval delay = (16 - used - 1);
    if(delay < 0){
        delay = 0.1;
    }
    [self performSelector:@selector(performVsync) withObject:nil afterDelay:delay/1000];
    
    //NSLog(@"Frame userd %f ",  used) ;
}




- (void)dealloc
{
    delete(frameview);
    delete(render);
}



@end

