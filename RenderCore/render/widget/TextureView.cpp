//
// Created by furture on 2019/1/15.
//

#include <render/core/rendering/RenderTexture.h>
#include <render/frame/TextureManager.h>
#include "TextureView.h"

namespace weexuikit{

    TextureView::TextureView(UIContext *context, weexuikit::Node *node) : View(context,node) {

    }


    blink::RenderObject* TextureView::createRenderObject(blink::RenderObject *parent,
                                                         RefPtr<blink::RenderStyle> renderStyle) {
        mRenderTexture = new blink::RenderTexture();
        mRenderTexture->setStyle(renderStyle);
        if(renderStyle->width().isAuto()){
            renderStyle->setWidth({blink::LengthType::FillAvailable});
        }
        if(renderStyle->height().isAuto()){
            renderStyle->setHeight({blink::LengthType::FillAvailable});
        }
        mRenderTexture->setNode(mNode);


        TextureManager::getInstance()->createTexture(mNode->getPageId(), mNode->ref(),
        mNode->type(),
        mNode->attrs(), mNode->styles(), mNode->events());


        return mRenderTexture;
    }
}
