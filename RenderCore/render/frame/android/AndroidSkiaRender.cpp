//
// Created by furture on 2018/7/31.
//
#include "AndroidSkiaRender.h"
#include <third_party/skia/include/gpu/gl/GrGLInterface.h>
#include <third_party/skia/include/gpu/GrContext.h>
#include <third_party/skia/src/gpu/gl/GrGLDefines.h>
#include <third_party/skia/include/gpu/GrBackendSurface.h>
#include <GLES2/gl2.h>
#include <third_party/skia/src/gpu/GrResourceCache.h>
#include <render/platform/common/log.h>


namespace weexuikit{


    // Default maximum number of budgeted resources in the cache.
    static const int kGrCacheMaxCount = 8192;

// Default maximum number of bytes of GPU memory of budgeted resources in the
// cache.
    static const size_t kGrCacheMaxByteSize = 512 * (1 << 20);

    AndroidSkiaRender::AndroidSkiaRender() {
        nativeWindow = nullptr;
        skSurface.reset(nullptr);
        grContext.reset(nullptr);
        windowWidth = 0;
        windowHeight = 0;
        eglManager = NULL;
    }

    AndroidSkiaRender::~AndroidSkiaRender() {
        destroy();
    }

    void AndroidSkiaRender::attachEGL(EGLNativeWindowType nativeWindow, int width, int height, EGLContext share_context) {
        destroy();
        this->nativeWindow = nativeWindow;

        eglManager = new EglManager();
        eglManager->eglInitContext(true, share_context);
        eglManager->createWindowSurface(nativeWindow);
        eglManager->makeCurrent();

        sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
        GrContextOptions options;
        options.fAvoidStencilBuffers = true;
        options.fDisableGpuYUVConversion = true;
        grContext  = GrContext::MakeGL(interface, options);



        /**we should not cache any resource, because bitmap has been cached, use
         * cache may slow down performance and waste memory. and cause image render not right. we should
         * later use share context architure, to cache resource and texture in share context
         * */
        grContext->setResourceCacheLimits(kGrCacheMaxCount, kGrCacheMaxByteSize);

        GrGLint bufferId;
        interface->fFunctions.fGetIntegerv(GR_GL_FRAMEBUFFER_BINDING, &bufferId);
        glFramebufferInfo.fFBOID = bufferId;
        glFramebufferInfo.fFormat = grContext->caps()->srgbSupport() && false ? GR_GL_SRGB8_ALPHA8 : GR_GL_RGBA8;

        sizeChanged(width, height);
        DEBUG_LOG("OpenGLSkiaRender","OpenGLSkiaRender::attachEGL %d %d", width, height);
    }



    void AndroidSkiaRender::sizeChanged(int width, int height) {
        this->windowWidth = width;
        this->windowHeight = height;
        glViewport(0, 0, windowWidth, windowHeight);


        GrBackendRenderTarget grBackendRenderTarget(width,
                                                    height,
                                                    0,
                                                    0,
                                                    glFramebufferInfo);
        SkSurfaceProps      fSurfaceProps(SkSurfaceProps::kLegacyFontHost_InitType);
        GrGLenum format;
        const SkColorType color_type = FirstSupportedColorType(grContext.get(), &format);
        skSurface = SkSurface::MakeFromBackendRenderTarget(grContext.get(), grBackendRenderTarget,
                                                           kBottomLeft_GrSurfaceOrigin,
                                                           color_type,
                                                           fColorSpace,
                                                           &fSurfaceProps);
    }

    void AndroidSkiaRender::makeCurrent() {
        if (eglManager != nullptr) {
            return  eglManager->makeCurrent();
        }
    }

    bool AndroidSkiaRender::hasSurface() {
        return (eglManager != nullptr);
    }


    bool AndroidSkiaRender::swapBuffers() {
        if (eglManager != nullptr) {
            return  eglManager->swapBuffer();
        }
    }


    void AndroidSkiaRender::destroy() {
        skSurface.reset(nullptr);
        grContext.reset(nullptr);
        if(eglManager != nullptr){
            eglManager->destory();
            delete  eglManager;
            eglManager = nullptr;
        }
    }

    void AndroidSkiaRender::clearBuffer() {
        makeCurrent();
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glStencilMask(0xff);
        glClearStencil(0);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glFlush();
    }

}
