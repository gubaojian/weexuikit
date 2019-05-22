//
// Created by furture on 2019/2/20.
//

#include "FloatPropertyValue.h"
#include <render/platform/animation/AnimationUtilities.h>

namespace weexuikit{


    FloatPropertyValue::FloatPropertyValue(float from, float to, OnFloatPropertyUpdate onFloatPropertyUpdate):mFrom(from),mTo(to),mOnFloatPropertyUpdate(onFloatPropertyUpdate){

    }


    void FloatPropertyValue::blendToStyle(double progress, blink::RenderStyle *renderStyle) {
        float value = blink::blend(mFrom, mTo, progress);
        if(mOnFloatPropertyUpdate != nullptr){
            mOnFloatPropertyUpdate(renderStyle, value);
        }
    }
}