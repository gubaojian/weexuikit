//
// Created by furture on 2019/2/20.
//

#include <render/core/node/NodeStyles.h>
#include "LengthPropertyValue.h"

namespace weexuikit {


    LengthPropertyValue::LengthPropertyValue(blink::Length from,
                                             blink::Length to, OnLengthPropertyUpdate onValueUpdate):mFrom(from),mTo(to), mOnLengthValueUpdate(onValueUpdate){

    }

    void LengthPropertyValue::blendToStyle(double progress, blink::RenderStyle *renderStyle) {
        blink::Length length = mTo.blend(mFrom, progress, blink::ValueRange::ValueRangeAll);
        if(mOnLengthValueUpdate != nullptr){
            mOnLengthValueUpdate(renderStyle, length);
        }
    }

}