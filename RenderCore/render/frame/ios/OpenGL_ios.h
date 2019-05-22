//
//  OpenGL_ios.hpp
//  weexuikit
//
//  Created by qz on 10/24/18.
//

#ifndef OpenGL_ios_hpp
#define OpenGL_ios_hpp

#include <stdio.h>

#import <GLKit/GLKit.h>
#import <GLKit/GLKView.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <QuartzCore/CAEAGLLayer.h>

#include <render/frame/SkiaRender.h>

namespace weexuikit {
    
    class IOSOpenGLSkiaRender : public  SkiaRender{
        
    public:
        IOSOpenGLSkiaRender();
        ~IOSOpenGLSkiaRender();
        
        void create(CAEAGLLayer *layer);
        void destroy();
        void clearBuffer();
        
        virtual void makeCurrent() override;
        virtual bool swapBuffers() override;
        virtual bool hasSurface() override;
        virtual sk_sp<SkSurface> getSurface() override;
        virtual int getWindowWidth() override;
        virtual int getWindowHeight() override;
        
    private:
        GLuint framebuffer_;
        GLuint renderbuffer_;
        EAGLContext *context_;
        sk_sp<GrContext> grContext_;
        sk_sp<SkColorSpace> color_space_;
        sk_sp<SkSurface> surface_;
        int width_;
        int height_;
    };
    
    
    
}



#endif /* OpenGL_ios_hpp */
