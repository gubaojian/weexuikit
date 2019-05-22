//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_P_H
#define WEEXRENDERER_P_H
#include "View.h"


namespace weexuikit {

    class ParaView : public View {

    protected:
    public:
        ParaView(UIContext *context, Node *node);

    public:
        blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) override;

    };
}


#endif //WEEXRENDERER_P_H
