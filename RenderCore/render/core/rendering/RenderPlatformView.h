//
// Created by furture on 2019/1/9.
//

#ifndef WEEX_UIKIT_RENDERPLATFORM_H
#define WEEX_UIKIT_RENDERPLATFORM_H
#include "RenderReplaced.h"

namespace blink{


    class RenderPlatformView : public RenderReplaced {
        public:
            RenderPlatformView();
            ~RenderPlatformView();

        public:
            virtual void paintReplaced(PaintInfo&, const LayoutPoint&) override;
            
    };
}



#endif //WEEX_UIKIT_RENDERPLATFORM_H
