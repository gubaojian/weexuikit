//
// Created by furture on 2018/7/23.
//


#include <third_party/skia/include/gpu/gl/GrGLInterface.h>
#include <third_party/skia/include/gpu/GrContext.h>
#include <third_party/skia/src/gpu/gl/GrGLDefines.h>
#include <third_party/skia/include/gpu/GrBackendSurface.h>
#include <third_party/skia/include/core/SkPaint.h>
#include <third_party/skia/include/core/SkFontStyle.h>
#include <third_party/skia/include/core/SkTypeface.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <render/platform/graphics/GraphicsContext.h>
#include <render/core/rendering/PaintInfo.h>
#include <render/core/rendering/LayerPaintingInfo.h>
#include <render/core/rendering/HitTestRequest.h>
#include <render/core/rendering/HitTestResult.h>
#include <render/platform/common/log.h>
#include <third_party/skia/src/core/SkPictureRecord.h>
#include <third_party/skia/include/core/SkPictureRecorder.h>
#include <render/core/parser/Screen.h>
#include <render/wml/time/time_point.h>
#include <render/frame/Window.h>
#include "FramePipeline.h"
#include "RenderBodyHelper.h"
#include "Timing.h"


namespace weexuikit{


    FramePipeline::FramePipeline(Frame* frame,FrameView* frameView) {
        mFrame = frame;
        mFrameView = frameView;
    }

    FramePipeline::~FramePipeline() {
        if(mFrame != nullptr){
            mFrame = nullptr;
        }
        if(mFrameView != nullptr){
            mFrameView = nullptr;
        }
        if(mWindow != nullptr){
            mWindow->dettachPage();
            mWindow = nullptr;
        }
    }


    void FramePipeline::onFrame() {
        flushTicket();
        flushLayout();
        flushPaintFrame();
    }

    bool FramePipeline::flushPaintFrame() {
        if(mWindow == nullptr || !mWindow->isWindowValid()){
            return false;
        }
        Window* window = mWindow;
        if(!window->isWindowValid()){
            return false;
        }
        if(!hasRenderFrame()){
            return false;
        }
        needsPaint |= mFrame->getUIContext()->needsPaint();
        if(!needsPaint){
            return false;
        }
        TIME_METHOD();
        mFrame->getUIContext()->setHasPaint();
        blink::RenderView* renderView = mFrame->getRenderView();
        int windowWidth = window->getWindowWidth();
        int windowHeight = window->getWindowHeight();

        renderView->setFrameViewSize({windowWidth, windowHeight});


        SkPictureRecorder framePictureRecorder;
        SkCanvas* canvas = framePictureRecorder.beginRecording(windowWidth, windowHeight, nullptr, 0);
        blink::GraphicsContext context(canvas);
        blink::LayoutRect diryRect = {0, 0, windowWidth, windowHeight};
        blink::LayoutSize layoutSize;
        blink::LayerPaintingInfo layerPaintingInfo(renderView->layer(), diryRect, layoutSize);
        renderView->paintLayer(&context, layerPaintingInfo);

        sk_sp<SkPicture> frameRecords = framePictureRecorder.finishRecordingAsPicture();
        PaintFrame paintFrame;
        paintFrame.frameRecords = frameRecords;
        paintFrame.synViews = (*context.getSynViews());
        window->setWindowPaintFrame(paintFrame);
        needsPaint = false;
        return true;
    }




    void FramePipeline::setWindow(Window *window) {
        mWindow  = window;
    }



    void FramePipeline::flushTicket() {
        if(mFrame == nullptr || !mFrame->hasRenderView()){
            return;
        }
        int64_t  time = wml::TimePoint::Now().ToEpochDelta().ToMilliseconds();
        mFrame->getUIContext()->getTickerProvider()->checkTicker(time);
    }

    void FramePipeline::flushLayout() {
        if(mFrame == nullptr){
            return;
        }
        if(!mFrame->hasRenderView()){
            return;
        }
        blink::RenderView* renderView = mFrame->getRenderView();
        if(mWindow != nullptr){
            mFrame->setBodyHeight(mWindow->getWindowHeight());
        }
        bool needLayout = renderView->needsLayout();
        needsPaint |= needLayout;
        if(needLayout){
            TIME_METHOD();
            renderView->layoutIfNeeded();
        }
    }


    void FramePipeline::markDiry() {
        needsPaint = true;
    }



}
