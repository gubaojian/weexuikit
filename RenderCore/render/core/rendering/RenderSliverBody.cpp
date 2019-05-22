//
// Created by furture on 2019/1/8.
//

#include <render/platform/transforms/TranslateTransformOperation.h>
#include <third_party/skia/include/core/SkPictureRecorder.h>
#include <render/platform/graphics/GraphicsContext.h>
#include <render/platform/common/log.h>
#include <third_party/skia/include/core/SkImage.h>
#include <third_party/skia/include/core/SkSurface.h>
#include "RenderSliverBody.h"
#include "LayerPaintingInfo.h"

namespace blink{

   RenderSliverBody::RenderSliverBody() {
      RefPtr<RenderStyle> renderStyle = RenderStyle::createDefaultStyle();
      renderStyle->setDisplay(EDisplay::FLEX);
      renderStyle->setPosition(EPosition::RelativePosition);
      renderStyle->setFlexDirection(EFlexDirection::FlowColumn);
      TransformOperations operations;
      operations.operations().append(TranslateTransformOperation::create({0, LengthType::Fixed},
                                                                         {0, LengthType::Fixed},
                                                                         TransformOperation::OperationType::Translate));
      renderStyle->setTransform(operations);
      setStyle(renderStyle);
   }

   RenderSliverBody::~RenderSliverBody() {

   }


   void RenderSliverBody::layoutBody() {
       RefPtr<RenderStyle> renderStyle  = RenderStyle::clone(style());
       TransformOperations operations;
       operations.operations().append(TranslateTransformOperation::create({mmTransformOffset.x(), LengthType::Fixed},
                                                                          {mmTransformOffset.y(), LengthType::Fixed},
                                                                          TransformOperation::OperationType::Translate));
       renderStyle->setTransform(operations);
       setStyle(renderStyle);
       layoutIfNeeded();
   }


    void RenderSliverBody::paintLayerContents(blink::GraphicsContext *context, const blink::LayerPaintingInfo &info) {
        blink::LayerPaintingInfo sliverBodyPaintInfo = info;
        if(style()->flexDirection() == EFlexDirection::FlowRow){
            sliverBodyPaintInfo.paintDirtyRect.setHeight(sliverBodyPaintInfo.paintDirtyRect.width()
                                                          + sliverBodyPaintInfo.paintDirtyRect.width());
        }else{
            sliverBodyPaintInfo.paintDirtyRect.setHeight(sliverBodyPaintInfo.paintDirtyRect.height()
                                                    + sliverBodyPaintInfo.paintDirtyRect.width());
        }
        RenderBox::paintLayerContents(context, sliverBodyPaintInfo);
    }


}
