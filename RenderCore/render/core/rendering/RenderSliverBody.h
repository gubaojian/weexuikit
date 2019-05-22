//
// Created by furture on 2019/1/8.
//

#ifndef WEEX_UIKIT_RENDERCONTENT_H
#define WEEX_UIKIT_RENDERCONTENT_H

#include "RenderFlexibleBox.h"

namespace blink{

    class RenderSliverBody : public RenderFlexibleBox {

        public:
            RenderSliverBody();
            virtual ~RenderSliverBody();

        public:
            void layoutBody();

        public:
            void setScrollOffset(float x, float y){
                mmTransformOffset.set(x, y);
            }

        public:
            void paintLayerContents(GraphicsContext*, const LayerPaintingInfo&) override;

        private:
            FloatPoint mmTransformOffset;

    };
}



#endif //WEEX_UIKIT_RENDERCONTENT_H
