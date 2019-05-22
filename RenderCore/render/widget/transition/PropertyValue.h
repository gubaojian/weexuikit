//
// Created by furture on 2019/2/18.
//

#ifndef WEEX_UIKIT_ANIMATION_H
#define WEEX_UIKIT_ANIMATION_H
#include <functional>
#include <render/core/rendering/style/RenderStyle.h>

namespace weexuikit {


    class  Transition;


    class PropertyValue {

        public:
            PropertyValue();

        public:
            virtual void blendToStyle(double progress, blink::RenderStyle* renderStyle)=0;

    };
}


#endif //WEEX_UIKIT_ANIMATION_H
