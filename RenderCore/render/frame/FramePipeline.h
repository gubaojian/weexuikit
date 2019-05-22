//
// Created by furture on 2018/7/23.
//

#ifndef WEEX_UIKIT_FRAME_PIPELINE_H
#define WEEX_UIKIT_FRAME_PIPELINE_H

#include <render/core/rendering/RenderView.h>
#include <third_party/skia/include/core/SkSurface.h>
#include <third_party/skia/include/core/SkColorFilter.h>
#include <third_party/skia/include/gpu/GrContextOptions.h>
#include <third_party/skia/include/gpu/gl/GrGLTypes.h>
#include <render/gesture/gesture/PointerEvent.h>
#include <render/widget/UIContext.h>
#include <render/frame/Frame.h>

#include <map>
#include "FrameView.h"

namespace weexuikit{

    class Window;

    class FramePipeline{

    public:
        FramePipeline(Frame* frame, FrameView* frameView);
        ~FramePipeline();

        void markDiry();

    public:
        void onFrame();

    public:
        void flushTicket();
        void flushLayout();
        bool flushPaintFrame();


    public:
        void setWindow(Window* window);


        bool  hasRenderFrame(){
            return mFrame != nullptr && mFrame->getRenderView() != nullptr;
        }

        int getRenderFrameHeight(){
            if(mFrame != nullptr
               && mFrame->getRenderView() != nullptr
               && mFrame->getRenderView()->children() != nullptr
               && mFrame->getRenderView()->children()->firstChild() != nullptr){
                blink::RenderBox* renderBox = (blink::RenderBox *) mFrame->getRenderView()->children()->firstChild();
                if(renderBox){
                     if(renderBox->hasRenderOverflow()){
                         return renderBox->pixelSnappedLayoutOverflowRect().height();
                     }
                     return renderBox->pixelSnappedHeight();
                }
            }
            return -1;
        }

        int getRenderFrameWidth(){
            if(mFrame != nullptr
               && mFrame->getRenderView() != nullptr
               && mFrame->getRenderView()->children() != nullptr
               && mFrame->getRenderView()->children()->firstChild() != nullptr){
                blink::RenderBox* renderBox = (blink::RenderBox *) mFrame->getRenderView()->children()->firstChild();
                if(renderBox){
                   if(renderBox->hasRenderOverflow()){
                       return renderBox->pixelSnappedLayoutOverflowRect().width();
                   }
                   return renderBox->pixelSnappedWidth();
                }
            }
            return -1;
        }


        Frame* getRenderFrame(){
            if(mFrame == nullptr){
                mFrame = new Frame();
            }
            return mFrame;
        }

        inline void setRenderFrameKey(int64_t renderFrameKey){
            this->mRenderFrameKey = renderFrameKey;
        }

        inline int64_t getRenderFrameKey(){
            return this->mRenderFrameKey;
        }

    private:
        Window* mWindow;
        Frame* mFrame;
        FrameView* mFrameView;
        weexuikit::PointerEvent lastPointerEvent;
        int64_t  mRenderFrameKey;
        std::set<blink::RenderObject*> hitTestPathEntrys;
        bool needsPaint;
    };
}


#endif //WEEX_UIKIT_SKIASURFACERENDER_H
