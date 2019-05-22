//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_IMAGE_H
#define WEEXRENDERER_IMAGE_H
#include "View.h"
#include <render/core/rendering/RenderImage.h>

namespace weexuikit {

    class ImageView : public View {

    public:
        ImageView(UIContext *context, Node *node);


        virtual void applyDefault(blink::RenderObject* parent) override;

        void updateAttr(const std::string& key, const std::string& value) override;




        const std::string getSrc();
        const std::string getPlaceHolder();
        const blink::ImageScaleType getImageScaleType();


    public:
        blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) override;

    private:
        blink::RenderImage* renderImage;
    };
}

#endif //WEEXRENDERER_IMAGE_H
