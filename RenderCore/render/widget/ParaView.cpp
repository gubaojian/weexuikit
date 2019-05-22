//
// Created by furture on 2018/8/25.
//

#include <render/core/rendering/RenderParagraph.h>
#include "ParaView.h"

namespace weexuikit {


    ParaView::ParaView(UIContext *context, Node *node) : View(context, node) {

    }


    blink::RenderObject* ParaView::createRenderObject(blink::RenderObject* parent,
                               RefPtr<blink::RenderStyle> renderStyle) {
        blink::RenderParagraph* paragraph = new blink::RenderParagraph();
        paragraph->setStyle(renderStyle);
        mRenderContainer = paragraph;
        return paragraph;
    }

}