//
// Created by furture on 2019/2/20.
//

#ifndef WEEX_UIKIT_FLOATPROPERTYVALUE_H
#define WEEX_UIKIT_FLOATPROPERTYVALUE_H
#include "PropertyValue.h"

namespace weexuikit{

    using OnFloatPropertyUpdate = std::function<void(blink::RenderStyle* renderStyle, float value)>;

    class FloatPropertyValue : public PropertyValue{

       public:
            FloatPropertyValue(float from, float to, OnFloatPropertyUpdate onFloatPropertyUpdate);

       public:
           virtual void blendToStyle(double progress, blink::RenderStyle* renderStyle)override;


       private:
            float  mFrom;
            float mTo;
            OnFloatPropertyUpdate mOnFloatPropertyUpdate;
    };
}



#endif //WEEX_UIKIT_FLOATPROPERTYVALUE_H
