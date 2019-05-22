//
//  OpenGL_ios.cpp
//  weexuikit
//
//  Created by qz on 10/24/18.
//

#include "OpenGL_ios.h"

#include <UIKit/UIKit.h>

#include "third_party/skia/include/gpu/GrContextOptions.h"
#include "third_party/skia/include/gpu/gl/GrGLInterface.h"
#include "third_party/skia/src/gpu/gl/GrGLUtil.h"
#include "third_party/skia/include/gpu/GrContext.h"
#include "third_party/skia/include/gpu/GrBackendSurface.h"
#include "third_party/skia/include/core/SkCanvas.h"

namespace weexuikit {
    
    IOSOpenGLSkiaRender::IOSOpenGLSkiaRender(){
        surface_.reset(nullptr);
        grContext_.reset(nullptr);
    }
    
    IOSOpenGLSkiaRender::~IOSOpenGLSkiaRender(){
        destroy();
    }
    
    void IOSOpenGLSkiaRender::create(CAEAGLLayer *layer){
        
        context_ = [[EAGLContext alloc]initWithAPI:kEAGLRenderingAPIOpenGLES2];
        [EAGLContext setCurrentContext:context_];
        
        glGenFramebuffers(1, &framebuffer_);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
        
        glGenRenderbuffers(1, &renderbuffer_);
        glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer_);
        
        [context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)layer];

        color_space_ = SkColorSpace::MakeSRGB();
        if (@available(iOS 10, *)) {
            UIDisplayGamut displayGamut = [UIScreen mainScreen].traitCollection.displayGamut;
            switch (displayGamut) {
                case UIDisplayGamutP3:
                    color_space_ = SkColorSpace::MakeRGB(SkColorSpace::kSRGB_RenderTargetGamma,
                                                         SkColorSpace::kDCIP3_D65_Gamut);
                    break;
                default:
                    break;
            }
        }
        
        auto interface = GrGLMakeNativeInterface();
        
        grContext_ = GrContext::MakeGL(interface);
        GrGLint buffer;
        GR_GL_GetIntegerv(interface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
        GrGLFramebufferInfo info;
        info.fFBOID = (GrGLuint) buffer;
        SkColorType colorType;
        info.fFormat = GR_GL_RGBA8;
        colorType = kRGBA_8888_SkColorType;
        
        width_ =  [UIScreen mainScreen].scale * layer.bounds.size.width;
        height_ =  [UIScreen mainScreen].scale * layer.bounds.size.height;
        
        GrBackendRenderTarget target(width_, height_, 0, 8, info);
        
        SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);
        surface_ = SkSurface::MakeFromBackendRenderTarget(grContext_.get(), target,
                                                                        kBottomLeft_GrSurfaceOrigin,
                                                                        colorType, nullptr, &props);
    }
    
    void IOSOpenGLSkiaRender:: makeCurrent() {
        [EAGLContext setCurrentContext:context_];
    };
    bool IOSOpenGLSkiaRender:: swapBuffers() {
        [context_ presentRenderbuffer:GL_RENDERBUFFER];
        return true;
    };
    bool IOSOpenGLSkiaRender:: hasSurface() {
        return true;
    };
    sk_sp<SkSurface> IOSOpenGLSkiaRender:: getSurface() {
        return surface_;
    };
    int IOSOpenGLSkiaRender:: getWindowWidth() {
        return width_;
    };
    int IOSOpenGLSkiaRender:: getWindowHeight() {
        return height_;
    };
    
    void IOSOpenGLSkiaRender::destroy(){
        surface_.reset(nullptr);
        grContext_.reset(nullptr);
        color_space_.reset(nullptr);
        context_ = nil;
    };
    
    void IOSOpenGLSkiaRender::clearBuffer() {
        makeCurrent();
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    };
    
}
