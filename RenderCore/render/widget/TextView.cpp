//
// Created by furture on 2018/8/25.
//

#include <render/core/rendering/RenderParagraph.h>
#include <render/core/parser/StyleUpdater.h>

#include "TextView.h"
namespace weexuikit {



    TextView::TextView(UIContext *context, Node *node) : View(context, node) {


    }


    blink::RenderObject* TextView::createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) {
        WTF::String string = getRenderText();
        RefPtr<blink::RenderStyle> textStyle = StyleUpdater::createRenderStyle(renderStyle, mNode->styles());
        renderText = new blink::RenderText(string.impl());
        renderText->setStyle(textStyle);
        renderText->setNode(mNode);
        renderText->setNeedsLayoutAndPrefWidthsRecalc();

        blink::RenderParagraph* paragraph = new blink::RenderParagraph();
        paragraph->setStyle(renderStyle);
        paragraph->addChild(renderText);
        paragraph->setNeedsLayoutAndPrefWidthsRecalc();
        return paragraph;
    }

    void TextView::updateAttr(const std::string& key, const std::string& value) {
        if(Html::Attr::ATTR_VALUE == key || Html::Attr::ATTR_SPACE_RID_ONE == key){
            WTF::String string = getRenderText();
            renderText->setText(string.impl());
            renderText->setNeedsLayoutAndPrefWidthsRecalc();
            mRenderObject->setNeedsLayoutAndPrefWidthsRecalc();
            markParentNeedLayout(mRenderObject);
            return;
        }
        View::updateAttr(key, value);
    }

    void TextView::updateStyles(std::map<std::string, std::string> *styles) {
        View::updateStyles(styles);
        RefPtr<blink::RenderStyle>  renderStyle = StyleUpdater::newRenderStyleUpdates(renderText->style(), styles);
        renderText->setStyle(renderText->style());
        renderText->setNeedsLayoutAndPrefWidthsRecalc();
        markParentNeedLayout(mRenderObject);
    }

    WTF::String TextView::getRenderText() {
        std::string cstring = getText();
        const char* text = cstring.c_str();
        int length = cstring.length();
        WTF::String string = WTF::String::fromUTF8(text, length);
        if(isSpaceRidOne()){
           string.replace("  ", " ");
        }
        return string;
    }


    const std::string TextView::getText() {
        if(mNode->attrs() != nullptr){
            std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_VALUE);
            if(it != mNode->attrs()->end()){
                return it->second;
            }
        }
        return "";
    }

    bool TextView::isSpaceRidOne(){
        if(mNode->attrs() != nullptr) {
            std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_SPACE_RID_ONE);
            if (it != mNode->attrs()->end()) {
                return it->second == Html::Attr::Value::ATTR_VALUE_TRUE;
            }
        }
        return  false;
    }
}
