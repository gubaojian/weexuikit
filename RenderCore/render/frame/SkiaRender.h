//
// Created by furture on 2018/10/23.
//

#ifndef WEEXRENDER_SKIARENDER_H
#define WEEXRENDER_SKIARENDER_H
#include <third_party/skia/include/core/SkSurface.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <third_party/skia/src/core/SkPictureRecord.h>
#include <third_party/skia/include/core/SkPictureRecorder.h>
#include <third_party/skia/include/core/SkRefCnt.h>
#include <render/platform/common/log.h>
#include <memory>
#include <queue>
#include <third_party/skia/include/gpu/gl/GrGLTypes.h>
#include <EGL/eglplatform.h>
#include "PaintFrame.h"

namespace weexuikit {

    /**
     * Use OnFrameStartCallback To Request NextFrame When GPU Render
     * */
    using OnFrameStartCallback = std::function<void()>;

    class SkiaRender {

        public:
            SkiaRender();

        public:
            static SkiaRender* createRender(EGLNativeWindowType nativeWindow,
                                            bool isSurfaceFlinger, int width, int height);


        public:
            virtual void sizeChanged(int width, int height)=0;
            virtual void destroy()=0;
            virtual void makeCurrent() = 0;
            virtual bool swapBuffers() = 0;
            virtual bool hasSurface() = 0;
            virtual sk_sp<SkSurface> getSurface() = 0;
            virtual int getWindowWidth() = 0;
            virtual int getWindowHeight() = 0;
            virtual void clearBuffer()=0;

            virtual bool drawFrame(bool dirty, OnFrameStartCallback onFrameStartCallback);

            void drawPlatformViews(std::vector<blink::PaintPlatformView> &platformViews);

            void setPaintFrame(PaintFrame& paintFrame);

            inline void setIsSurfaceFlinger(bool isSurfaceFlinger){
                mIsSurfaceFlinger = isSurfaceFlinger;
            }


        protected:
            std::vector<blink::PaintPlatformView> mLastPaintPlatformViews;
            std::queue<PaintFrame> mFrames;
            PaintFrame mLastFrameRecord;
            bool mIsSurfaceFlinger;

        private:
             void clearFrameBuffer();
        };




    SkColorType FirstSupportedColorType(GrContext* context, GrGLenum* format);


}



#endif //WEEX_UIKIT_SKIARENDER_H
