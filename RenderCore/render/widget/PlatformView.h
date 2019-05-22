//
// Created by furture on 2019/1/9.
//

#ifndef WEEX_UIKIT_INPUTVIEW_H
#define WEEX_UIKIT_INPUTVIEW_H
#include <render/core/rendering/RenderPlatformView.h>
#include "View.h"

namespace weexuikit {

    class PlatformView : public View {

        public:
            PlatformView(UIContext *context, Node *node);


        public:
            virtual blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle);


        private:
             blink::RenderPlatformView* renderPlatformView;
   };

}

#endif //WEEX_UIKIT_INPUTVIEW_H
