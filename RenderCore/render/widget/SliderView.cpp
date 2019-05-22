//
// Created by furture on 2019/3/6.
//

#include <render/gesture/gesture/HorizontalDragGestureRecognizer.h>
#include <render/core/parser/Screen.h>
#include "SliderView.h"

namespace weexuikit {


    SliderView::SliderView(UIContext *context, Node *node) : View(context, node) {

    }


    blink::RenderObject* SliderView::createRenderObject(blink::RenderObject *parent,
                                                        RefPtr<blink::RenderStyle> renderStyle) {
        blink::RenderSlider* renderObject =  new blink::RenderSlider();
        renderObject->setStyle(renderStyle);
        mRenderContainer = renderObject;
        mRenderSlider = renderObject;
        
        mScrollable = std::make_shared<weexuikit::Scrollable>(mContext->getTickerProvider());
        mDragGestureRecognizer = std::make_shared<weexuikit::HorizontalDragGestureRecognizer>(mContext->getGestureHandlerContext());
        mDragGestureRecognizer->setMaxFlingVelocity(weexuikit::kMaxFlingVelocity/2);
        mDragGestureRecognizer->onStart = [&](weexuikit::DragStartDetails details){
            startInteraction(details);
        };
        mDragGestureRecognizer->onUpdate = [&](const weexuikit::DragUpdateDetails& details){
            updateInteraction(details);
        };

        mDragGestureRecognizer->onEnd = [&](const weexuikit::DragEndDetails& dragEndDetails){
            endInteraction();
        };
        mDragGestureRecognizer->onCancel = [&](){
            endInteraction();
        };
        return renderObject;
    }

    void SliderView::applyDefault(blink::RenderObject *parent) {
        mNode->styles()->insert({Html::Style::STYLE_OVERFLOW, Html::Style::STYLE_OVERFLOW_HIDDEN});
        View::applyDefault(parent);
    }

    void SliderView::onPointerEvent(weexuikit::PointerEvent &pointerEvent) {
        View::onPointerEvent(pointerEvent);
        if(pointerEvent.isDownEvent()){
            mDragGestureRecognizer->addPointer(pointerEvent);
        }
    }

    void SliderView::startInteraction(const weexuikit::DragStartDetails &startDetails) {
        LOGE("Weex", "SliderView::startInteraction %f %f",
        startDetails.globalPosition.dx, startDetails.globalPosition.dy);
        mItemOffset = mRenderSlider->getCurrentOffset();

    }

    void SliderView::updateInteraction(const weexuikit::DragUpdateDetails &updateDetails) {
        float pixels = Screen::dpiToDevicePixels(updateDetails.primaryDelta);
        mItemOffset += pixels/mRenderSlider->pixelSnappedWidth();
        mRenderSlider->setCurrentOffset(mItemOffset);
        LOGE("Weex", "SliderView::updateInteraction %f %f",
             updateDetails.primaryDelta, mItemOffset);
    }

    void SliderView::endInteraction() {
        int currentIndex = mRenderSlider->getCurrentIndex();

        LOGE("Weex", "SliderView::endInteraction %d %f", currentIndex, mItemOffset);
        if(mItemOffset >  0.5){
            currentIndex--;
        }else if(mItemOffset < -0.5){
            currentIndex++;
        }
        if(currentIndex < 0){
            currentIndex = 2;
        }
        if(currentIndex > 3){
            currentIndex = 0;
        }
        LOGE("Weex", "SliderView::endInteraction %d %f", currentIndex, mItemOffset);

        mItemOffset = 0;
        mRenderSlider->setCurrentIndex(currentIndex);
        mRenderSlider->setCurrentOffset(mItemOffset);
    }


}