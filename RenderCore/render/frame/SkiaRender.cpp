//
// Created by furture on 2018/10/23.
//

#include "SkiaRender.h"
#include "SkiaShareContext.h"
#include "Timing.h"
#include <third_party/skia/include/core/SkSurface.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <third_party/skia/src/core/SkPictureRecord.h>
#include <third_party/skia/include/core/SkPictureRecorder.h>
#include <third_party/skia/include/core/SkRefCnt.h>
#include <third_party/skia/include/gpu/gl/GrGLInterface.h>
#include <third_party/skia/include/gpu/GrContext.h>
#include <third_party/skia/src/gpu/gl/GrGLDefines.h>
#include <render/platform/common/log.h>
#include <memory>
#include <render/frame/android/AndroidSkiaRender.h>
#include <GLES2/gl2.h>
#include <render/public/platform/Platform.h>
#include <render/core/parser/Screen.h>

namespace weexuikit {


    // These are common defines present on all OpenGL headers. However, we don't
    // want to perform GL header reasolution on each platform we support. So just
    // define these upfront. It is unlikely we will need more. But, if we do, we can
    // add the same here.
    #define GPU_GL_RGBA8 0x8058
    #define GPU_GL_RGBA4 0x8056
    #define GPU_GL_RGB565 0x8D62
    #define GPU_GL_VERSION 0x1F02



    SkiaRender::SkiaRender() {
        mIsSurfaceFlinger = false;
    }


    SkiaRender* SkiaRender::createRender(EGLNativeWindowType nativeWindow, bool isSurfaceFlinger,  int width, int height) {
#ifdef __ANDROID__
        weexuikit::AndroidSkiaRender* skiaRender = new weexuikit::AndroidSkiaRender();
        skiaRender->setNativeWindow(nativeWindow);
        skiaRender->setIsSurfaceFlinger(isSurfaceFlinger);
        skiaRender->attachEGL(skiaRender->getNativeWindow(),
                              width, height, weexuikit::SkiaShareContext::getInstance()->getElgManager()->getEglContext());
        skiaRender->clearBuffer();
        skiaRender->swapBuffers();
        return skiaRender;
#endif
    }


    void SkiaRender::drawPlatformViews(std::vector<blink::PaintPlatformView> &platformViews) {
        if(platformViews.size() == 0 && mLastPaintPlatformViews.size() == 0){
            return;
        }
        for(blink::PaintPlatformView& synView : platformViews){
            synView.attached = true;
            blink::Platform::current()->paintPlatformView(synView);
        }
        //handle disappear not draw view.
        for(blink::PaintPlatformView& lastSynView : mLastPaintPlatformViews){
            bool  hasSyned = false;
            for(blink::PaintPlatformView& synView : platformViews){
                if(synView.ref == lastSynView.ref){
                    hasSyned = true;
                    break;
                }
            }
            if(hasSyned){
                continue;
            }
            lastSynView.attached = false;
            if(lastSynView.paintRect.pixelSnappedY() < 0){
                //move out of screen
                lastSynView.paintRect.setY(-SYN_VIEW_OFFSET + lastSynView.paintRect.pixelSnappedY() - lastSynView.paintRect.pixelSnappedHeight());
            }else{
                //move out of screen
                lastSynView.paintRect.setY(SYN_VIEW_OFFSET + Screen::mDeviceHeight);
            }
            blink::Platform::current()->paintPlatformView(lastSynView);
        }
        mLastPaintPlatformViews = platformViews;
    }



    void SkiaRender::setPaintFrame(weexuikit::PaintFrame &paintFrame) {
        if(mIsSurfaceFlinger){
            drawPlatformViews(paintFrame.synViews);
        }
        mFrames.push(paintFrame);
        mLastFrameRecord = paintFrame;
    }

    bool SkiaRender::drawFrame(bool dirty, OnFrameStartCallback onFrameStartCallback) {
        if(!dirty && mFrames.size() == 0){
            onFrameStartCallback();
            return false;
        }
        if(mFrames.size() == 0 && mLastFrameRecord.frameRecords.get() == nullptr){
            onFrameStartCallback();
            makeCurrent();
            clearBuffer();
            swapBuffers();
            return true;
        }
        PaintFrame paintFrame;
        if(mFrames.size() > 0){
            paintFrame= mFrames.front();
        }else{
            paintFrame = mLastFrameRecord;
        }
        onFrameStartCallback();
        TIME_METHOD();
        sk_sp<SkPicture> picture = paintFrame.frameRecords;
        makeCurrent(); //FIXME
        clearFrameBuffer();
        SkCanvas* canvas = getSurface()->getCanvas();
        canvas->drawPicture(picture);
        canvas->flush();
        if(mFrames.size() > 0){
            mFrames.pop();
        }

        if(!mIsSurfaceFlinger) {
           drawPlatformViews(paintFrame.synViews);
        }
        swapBuffers();
        return true;
    }

    void SkiaRender::clearFrameBuffer() {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glStencilMask(0xff);
        glDisable(GL_SCISSOR_TEST);
        glClearStencil(0);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }


    SkColorType FirstSupportedColorType(GrContext* context,
                                               GrGLenum* format) {
#define RETURN_IF_RENDERABLE(x, y)                 \
          if (context->colorTypeSupportedAsSurface((x))) { \
            *format = (y);                                 \
            return (x);                                    \
          }
        RETURN_IF_RENDERABLE(kRGBA_8888_SkColorType, GPU_GL_RGBA8);
        RETURN_IF_RENDERABLE(kARGB_4444_SkColorType, GPU_GL_RGBA4);
        RETURN_IF_RENDERABLE(kRGB_565_SkColorType, GPU_GL_RGB565);
        return kUnknown_SkColorType;
    }
}
