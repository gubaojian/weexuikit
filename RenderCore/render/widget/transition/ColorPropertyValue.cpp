//
// Created by furture on 2019/2/20.
//

#include "ColorPropertyValue.h"

namespace weexuikit{


    ColorPropertyValue::ColorPropertyValue(blink::Color from, blink::Color to, weexuikit::OnColorPropertyUpdate colorPropertyUpdate): mFrom(from), mTo(to), mOnColorPropertyUpdate(colorPropertyUpdate){

    }


    void ColorPropertyValue::blendToStyle(double progress, blink::RenderStyle *renderStyle) {
        blink::Color color = blink::blend(mFrom, mTo, progress);
        if(mOnColorPropertyUpdate != nullptr){
            mOnColorPropertyUpdate(renderStyle, color);
        }
    }

}