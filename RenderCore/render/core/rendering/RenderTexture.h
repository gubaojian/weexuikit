#ifndef WEEX_UIKIT_RENDERTEXTURE_H
#define WEEX_UIKIT_RENDERTEXTURE_H

#include <third_party/skia/include/core/SkImage.h>
#include "RenderReplaced.h"


namespace blink{
   
   class RenderTexture : public RenderReplaced{
       public:
          RenderTexture();
          ~RenderTexture();

        public:
          void paintReplaced(PaintInfo&, const LayoutPoint&) override;

        private:
             sk_sp<SkImage> mTextureImage;
             SkMatrix mTextureTransform;
   };

}


#endif