//
// Created by furture on 2019/2/20.
//

#include "TransformPropertyValue.h"
#include <render/widget/View.h>
#include <render/platform/transforms/ScaleTransformOperation.h>

namespace weexuikit {

    TransformPropertyValue::TransformPropertyValue(weexuikit::Transition *transition,
                                         blink::TransformOperations from,
                                         blink::TransformOperations to):mTransition(transition),mFrom(from),mTo(to){

    }

    void TransformPropertyValue::blendToStyle(double progress, blink::RenderStyle *renderStyle) {
        blink::TransformOperations transformOperations = mTo.blend(mFrom, progress);
        renderStyle->setTransform(transformOperations);
    }
}