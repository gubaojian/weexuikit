//
// Created by furture on 2019/1/9.
//

#include <render/platform/common/log.h>
#include <render/platform/graphics/PaintPlatformView.h>
#include "RenderPlatformView.h"
#include "PaintInfo.h"

namespace blink{

    RenderPlatformView::RenderPlatformView() {

    }

    RenderPlatformView::~RenderPlatformView() {

    }


    
    void RenderPlatformView::paintReplaced(blink::PaintInfo &paintInfo, const blink::LayoutPoint& paintOffset) {
        LayoutRect viewRect = contentBoxRect();
        FloatPoint floatPoint;
        floatPoint = localToAbsolute(floatPoint, UseTransforms);
        viewRect.moveBy({floatPoint.x(), floatPoint.y()});

        blink::PaintPlatformView platformView;
        platformView.ref = getNode()->ref();
        platformView.pageId = getNode()->getPageId();
        platformView.paintRect = viewRect;
        paintInfo.context->addSynView(platformView);

        LayoutRect clipRect = contentBoxRect();
        clipRect.moveBy(paintOffset);
        GraphicsContext* context = paintInfo.context;
        SkCanvas* canvas = context->canvas();
        SkRect rect =  IntRect(clipRect.pixelSnappedLocation(), clipRect.pixelSnappedSize());
        canvas->save();
        canvas->clipRect(rect);
        canvas->clear(SK_ColorTRANSPARENT);
        canvas->restore();
    }

}