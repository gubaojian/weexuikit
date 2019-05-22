//
// Created by furture on 2019/2/20.
//

#ifndef WEEX_UIKIT_COLORPROPERTYVALUE_H
#define WEEX_UIKIT_COLORPROPERTYVALUE_H
#include "PropertyValue.h"

namespace weexuikit{

    using OnColorPropertyUpdate = std::function<void(blink::RenderStyle* renderStyle, const blink::Color& color)>;

    class ColorPropertyValue : public PropertyValue {

        public:
           ColorPropertyValue(blink::Color from, blink::Color to, OnColorPropertyUpdate colorPropertyUpdate);


        public:
           virtual void blendToStyle(double progress, blink::RenderStyle* renderStyle)override;

        private:
            blink::Color mFrom;
            blink::Color mTo;
            OnColorPropertyUpdate mOnColorPropertyUpdate;
    };

}



#endif //WEEX_UIKIT_COLORPROPERTYVALUE_H
