//
// Created by furture on 2019/1/9.
//
#include <render/frame/TextureManager.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <render/platform/common/log.h>
#include <render/public/platform/Platform.h>
#include "RenderTexture.h"
#include "PaintInfo.h"

namespace blink{

    RenderTexture::RenderTexture(){

    }

    RenderTexture::~RenderTexture(){
        weexuikit::Node* node = getNode();
        if(node != nullptr){

        }
    }

    void RenderTexture::paintReplaced(PaintInfo& paintInfo, const LayoutPoint& paintOffset){
        LayoutRect paintRect = contentBoxRect();
        paintRect.moveBy(paintOffset);



        weexuikit::Node* node = getNode();
        SkCanvas* canvas = paintInfo.context->canvas();
        blink::Platform::current()->paintExternalTexture(
                node->getPageId(), node->ref(),
                canvas,
                paintRect);
    }



}