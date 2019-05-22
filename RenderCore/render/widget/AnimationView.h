//
// Created by furture on 2019/1/4.
//

#ifndef WEEX_UIKIT_ANIMATIONVIEW_H
#define WEEX_UIKIT_ANIMATIONVIEW_H
#include "View.h"
#include <render/gesture/animation/AnimationController.h>

namespace weexuikit {

    class AnimationView : public View , weexuikit::ListenVoidCallback{
        public:
            AnimationView(UIContext *context, Node *node);


        public:
            void attachRenderObject(blink::RenderObject* parent, int index) override;

            virtual void onListenEvent() override;

        private:

            std::shared_ptr<weexuikit::AnimationTicker> animationTicker;
    };

}

#endif //WEEX_UIKIT_ANIMATIONVIEW_H
