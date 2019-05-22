
//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_SPAN_H
#define WEEXRENDERER_SPAN_H
#include "View.h"
#include <render/core/rendering/RenderInline.h>
#include <render/core/rendering/RenderText.h>

namespace weexuikit {

    class SpanView : public View {

    public:
        SpanView(UIContext *context, Node *node);

        void updateAttr(const std::string& key, const std::string& value) override;
        void updateStyles(std::map<std::string, std::string> *styles) override;
        WTF::String getRenderText();

        const std::string getText();
        bool isSpaceRidOne();

    public:
        blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) override;

    private:
        blink::RenderText* renderText;

    };
}


#endif //WEEXRENDERER_SPAN_H
