//
// Created by furture on 2018/12/30.
//

#include <render/core/rendering/HitTestResult.h>
#include <render/core/rendering/RenderView.h>
#include <render/core/parser/Screen.h>
#include "FrameView.h"

namespace weexuikit{

    FrameView::FrameView(weexuikit::Frame *frame) {
        mFrame = frame;
    }

    FrameView::~FrameView() {
        mFrame = nullptr;
    }

    Node* FrameView::hitTestNode(int type, int x, int y) {
        blink::RenderObject* renderObject = hitTestRenderObject(type, x, y);
        if(renderObject == nullptr){
            return nullptr;
        }
        return renderObject->getNode();
    }


    blink::RenderObject* FrameView::hitTestRenderObject(int type, int x, int y) {
        if(!mFrame->hasRenderView()){
            return nullptr;
        }
        blink::RenderView* renderView = mFrame->getRenderView();
        blink::HitTestRequest::HitTestRequestType requestType = blink::HitTestRequest::RequestType::Active || blink::HitTestRequest::RequestType::ReadOnly || blink::HitTestRequest::RequestType::Release;
        blink::HitTestRequest hitTestRequest(requestType, type);
        blink::LayoutPoint  layoutPoint = {x, y};
        blink::HitTestResult  hitTestResult(layoutPoint);
        renderView->hitTest(hitTestRequest, hitTestResult);
        return hitTestResult.renderer();
    }


    void FrameView::onTouch(weexuikit::PointerEvent::PointerAction action, int pointerId, float x,
                            float y, int64_t timeStamp) {
        if(!mFrame->hasRenderView()){
            return;
        }
        weexuikit::PointerEvent pointerEvent;
        pointerEvent.action = action;
        pointerEvent.pointer = pointerId;
        pointerEvent.axisX = x;
        pointerEvent.axisY = y;
        pointerEvent.position = weexuikit::makeOffset(x, y);
        pointerEvent.timeStamp = timeStamp;
        dispatchTouchEvent(pointerEvent);
    }


    void FrameView::dispatchTouchEvent(weexuikit::PointerEvent &pointerEvent) {
        int pointerId = pointerEvent.pointer;
        if(pointerEvent.isDownEvent()){
            mTouchDispatchPaths[pointerId] = hitTestRenderObject(Event::RequestEventType::HITTEST,
                    pointerEvent.axisX*Screen::mDeviceDensity, pointerEvent.axisY*Screen::mDeviceDensity);
        }else{
            std::pair<float, float>& locations = mTouchPointerLocations[pointerId];
            pointerEvent.delta = weexuikit::makeOffset(pointerEvent.axisX - locations.first,
                                            pointerEvent.axisY - locations.second);
        }

        for(blink::RenderObject* renderObject = mTouchDispatchPaths[pointerId]; renderObject != nullptr; renderObject = renderObject->parent()){
            renderObject->onPointerEvent(pointerEvent);
        }

        mFrame->getUIContext()->getGestureHandlerContext()->handleEvent(pointerEvent);
        if(pointerEvent.isUpEvent() || pointerEvent.isCancelEvent()){
            mTouchDispatchPaths[pointerId] = nullptr;
        }
        mTouchPointerLocations[pointerId] = std::make_pair(pointerEvent.axisX, pointerEvent.axisY);
     }

}