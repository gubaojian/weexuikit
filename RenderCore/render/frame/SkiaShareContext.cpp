//
// Created by furture on 2018/12/25.
//
#include <mutex>
#include <third_party/skia/include/gpu/gl/GrGLInterface.h>
#include "SkiaShareContext.h"
#include "ImageManager.h"


namespace weexuikit {


    static SkiaShareContext* instance  = nullptr;
    static std::once_flag oflag;

    SkiaShareContext* SkiaShareContext::getInstance() {
        std::call_once(oflag, [&](){
            instance = new SkiaShareContext();
        });
        return instance;
    }

    void SkiaShareContext::destroyInstance() {
        if(instance != nullptr){
            delete instance;
            instance = nullptr;
        }
    }

    SkiaShareContext::SkiaShareContext() {
        mEglManager = new EglManager();
        mEglManager->eglInitContext(false, nullptr);
        mEglManager->createPBufferSurface();
        mEglManager->makeCurrent();
        sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
        GrContextOptions options;
        options.fAvoidStencilBuffers = true;
        options.fDisableGpuYUVConversion = true;
        mGrContext  = GrContext::MakeGL(interface, options);
        // Do not cache textures created by the image decoder.  These textures
        // should be deleted when they are no longer referenced by an SkImage.
        mGrContext->setResourceCacheLimits(0, 0);
    }


    SkiaShareContext::~SkiaShareContext() {
        mGrContext.reset(nullptr);
        if(mEglManager != nullptr){
            mEglManager->destory();
            delete mEglManager;
        }
    }

    EglManager* SkiaShareContext::getElgManager() {
        return mEglManager;
    }

    sk_sp<GrContext> SkiaShareContext::getGRContext() {
        return mGrContext;
    }
}