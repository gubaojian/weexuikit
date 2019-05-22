//
// Created by furture on 2019/3/6.
//

#ifndef WEEX_UIKIT_SLIDERVIEW_H
#define WEEX_UIKIT_SLIDERVIEW_H

#include <render/core/rendering/RenderSlider.h>
#include <render/gesture/gesture/DragGestureRecognizer.h>
#include <render/gesture/widget/Scrollable.h>
#include "View.h"

namespace weexuikit {

    class SliderView  : public View {


       public:
           SliderView(UIContext *context, Node *node);

       public:
          virtual blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) override;
          virtual void applyDefault(blink::RenderObject* parent) override;

       public:
          virtual void onPointerEvent(weexuikit::PointerEvent& pointerEvent);

       private:
            void startInteraction(const weexuikit::DragStartDetails& startDetails);
            void updateInteraction(const weexuikit::DragUpdateDetails& updateDetails);
            void endInteraction();

       private:
            std::shared_ptr<weexuikit::DragGestureRecognizer> mDragGestureRecognizer;
            std::shared_ptr<weexuikit::Scrollable> mScrollable;
            float mItemOffset;
            blink::RenderSlider* mRenderSlider;


    };
}


#endif //WEEX_UIKIT_SLIDERVIEW_H
