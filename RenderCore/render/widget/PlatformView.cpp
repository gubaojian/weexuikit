//
// Created by furture on 2019/1/9.
//

#include <render/public/platform/Platform.h>
#include "PlatformView.h"

namespace weexuikit {

    PlatformView::PlatformView(UIContext *context, weexuikit::Node *node) : View(context,node) {

    }


    blink::RenderObject* PlatformView::createRenderObject(blink::RenderObject *parent,
                                                       RefPtr<blink::RenderStyle> renderStyle) {
        renderPlatformView = new blink::RenderPlatformView();
        renderPlatformView->setStyle(renderStyle);
        if(renderStyle->width().isAuto()){
            renderStyle->setWidth({blink::LengthType::FillAvailable});
        }
        if(renderStyle->height().isAuto()){
            renderStyle->setHeight({blink::LengthType::FillAvailable});
        }
        renderPlatformView->setNode(mNode);
        blink::Platform::current()->createPlatformView(mNode->getPageId(), mNode->ref(), mNode->type(),
                                                       *mNode->attrs(),
                                                       *mNode->styles(),
                                                       *mNode->events());
        return renderPlatformView;
    }
}
