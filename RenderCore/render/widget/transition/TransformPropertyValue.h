//
// Created by furture on 2019/2/20.
//

#ifndef WEEX_UIKIT_TRANSFORMPROPERTY_H
#define WEEX_UIKIT_TRANSFORMPROPERTY_H

#include <render/platform/transforms/TransformOperations.h>
#include <render/core/rendering/style/RenderStyle.h>
#include "Transition.h"
#include "PropertyValue.h"

namespace weexuikit {

    class TransformPropertyValue : public PropertyValue {

        public:
            TransformPropertyValue(Transition* transition, blink::TransformOperations from,  blink::TransformOperations to);


        public:
        virtual void blendToStyle(double progress, blink::RenderStyle* renderStyle) override;

        private:
            blink::TransformOperations mFrom;
            blink::TransformOperations mTo;
            Transition* mTransition;
    };
}



#endif //WEEX_UIKIT_TRANSFORMPROPERTY_H
