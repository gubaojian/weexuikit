//
// Created by furture on 2018/7/31.
//

#ifndef WEEX_UIKIT_OPENGLRENDER_H
#define WEEX_UIKIT_OPENGLRENDER_H
#include <EGL/eglplatform.h>
#include <EGL/egl.h>
#include <third_party/skia/include/core/SkSurface.h>
#include <third_party/skia/include/core/SkColorFilter.h>
#include <third_party/skia/include/gpu/GrContextOptions.h>
#include <third_party/skia/include/gpu/gl/GrGLTypes.h>
#include <third_party/skia/include/gpu/GrContext.h>
#include <render/frame/SkiaRender.h>
#include "EglManager.h"

namespace weexuikit{

    class AndroidSkiaRender : public  SkiaRender {

    public:
        AndroidSkiaRender();
        ~AndroidSkiaRender();
        void attachEGL(EGLNativeWindowType nativeWindow,
                       int width, int height,EGLContext share_context);
        void sizeChanged(int width, int height);
        virtual void makeCurrent() override ;
        virtual bool hasSurface() override ;
        virtual bool swapBuffers() override ;
        void destroy();

        EGLNativeWindowType getNativeWindow(){
            return nativeWindow;
        }
        EGLNativeWindowType setNativeWindow(EGLNativeWindowType window){
            this->nativeWindow = window;
        }

        virtual int getWindowWidth() override {
            return windowWidth;
        }

        virtual int getWindowHeight() override {
            return windowHeight;
        }

        sk_sp<SkSurface> getSurface(){
            return skSurface;
        }

        sk_sp<GrContext> getGrContext(){
            return grContext;
        }

        void clearBuffer();

    private:
        int windowWidth = 0;
        int windowHeight = 0;
        EglManager* eglManager;
        GrGLFramebufferInfo glFramebufferInfo;
        EGLNativeWindowType nativeWindow;

        sk_sp<GrContext> grContext;
        sk_sp<SkSurface> skSurface;
        SkColorType         fColorType = kN32_SkColorType;
        sk_sp<SkColorSpace> fColorSpace;
    };
}



#endif //WEEX_UIKIT_OPENGLRENDER_H
