//
// Created by furture on 2019/2/20.
//

#ifndef WEEX_UIKIT_LENGTHPROPERTY_H
#define WEEX_UIKIT_LENGTHPROPERTY_H
#include "PropertyValue.h"

namespace weexuikit {


    using OnLengthPropertyUpdate =  std::function<void(blink::RenderStyle* renderStyle, const blink::Length&)>;

    class LengthPropertyValue : public PropertyValue{

      public:
         LengthPropertyValue(blink::Length from, blink::Length to, OnLengthPropertyUpdate onValueUpdate);

      public:
            virtual void blendToStyle(double progress, blink::RenderStyle* renderStyle)override;

       private:
         blink::Length mFrom;
         blink::Length mTo;
         OnLengthPropertyUpdate mOnLengthValueUpdate;
    };
}



#endif //WEEX_UIKIT_LENGTHPROPERTY_H
