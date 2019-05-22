//
// Created by furture on 2018/10/29.
//

#ifndef WEEX_UIKIT_SCROLLER_H
#define WEEX_UIKIT_SCROLLER_H

#include "View.h"
#include "UIContext.h"
#include <render/core/rendering/RenderScrollView.h>
#include <render/gesture/gesture/VerticalDragGestureRecognizer.h>
#include <render/gesture/gesture/HorizontalDragGestureRecognizer.h>
#include <render/gesture/widget/ScrollPhysics.h>
#include <render/gesture/widget/ScrollableState.h>
#include <render/gesture/widget/ScrollPosition.h>
#include <render/gesture/widget/ScrollPositionWithSingleContext.h>
#include <render/gesture/foundation/Listenable.h>


namespace weexuikit{

    class ScrollerView : public View, public weexuikit::ListenVoidCallback{

        
    public:
        ScrollerView(UIContext *context, Node *node);

        ~ScrollerView();

        virtual void applyDefault(blink::RenderObject* parent) override;
        
        virtual void onPointerEvent(weexuikit::PointerEvent& pointerEvent) override;
        virtual void onListenEvent() override;

    public:
        const std::string& getScrollDirection();

    public:
        blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) override;



    private:
        weexuikit::DragGestureRecognizer* mDragGestureRecognizer;
        blink::RenderScrollView* mScrollView;
        weexuikit::ScrollPhysics* mScrollPhysics;
        weexuikit::ScrollableState* mScrollableState;
        weexuikit::ScrollPosition* mScrollPosition;
        std::shared_ptr<weexuikit::Drag> mDrag = nullptr;
        std::shared_ptr<weexuikit::ScrollHoldController> mHold = nullptr;
    };
    
    
}




#endif //WEEX_UIKIT_SCROLLER_H
