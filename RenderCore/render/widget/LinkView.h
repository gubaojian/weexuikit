//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_A_H
#define WEEXRENDERER_A_H
#include "View.h"

namespace weexuikit {

    class LinkView : public View {
    public:
        LinkView(UIContext *context, Node *node);

        void applyDefault(blink::RenderObject* parent) override;

    public:
        blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) override;

    };
}



#endif //WEEXRENDERER_ACOMPONENT_H
