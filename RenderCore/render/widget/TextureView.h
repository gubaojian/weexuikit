//
// Created by furture on 2019/1/15.
//

#ifndef WEEX_UIKIT_TEXTUREVIEW_H
#define WEEX_UIKIT_TEXTUREVIEW_H
#include <render/core/rendering/RenderText.h>
#include <render/core/rendering/RenderTexture.h>
#include "View.h"

namespace weexuikit{

    /**
     * Render External OpenGL Texture On Platform
     * */
    class TextureView : public View  {

        public:
            TextureView(UIContext *context, Node *node);

        public:
            virtual blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle);


        private:
            blink::RenderTexture* mRenderTexture;
    };


}



#endif //WEEX_UIKIT_TEXTUREVIEW_H
