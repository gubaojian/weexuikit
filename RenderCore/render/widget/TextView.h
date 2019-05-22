//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_TEXT_H
#define WEEXRENDERER_TEXT_H
#include <render/core/rendering/RenderText.h>
#include "View.h"

namespace weexuikit {

    class TextView : public View {

    public:
        TextView(UIContext *context, Node *node);

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


#endif //WEEXRENDERER_TEXTCOMPONENT_H
