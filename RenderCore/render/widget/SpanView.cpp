//
// Created by furture on 2018/8/25.
//
#include <render/core/parser/StyleUpdater.h>
#include <render/core/rendering/RenderParagraph.h>
#include "SpanView.h"

namespace weexuikit {


    SpanView::SpanView(UIContext *context, Node *node) : View(context, node) {

    }

    blink::RenderObject* SpanView::createRenderObject(blink::RenderObject *parent, RefPtr<blink::RenderStyle> renderStyle) {
        if(parent->isRenderParagraph() || parent->isRenderInline()){
            WTF::String string = getRenderText();
            renderText = new blink::RenderText(string.impl());
            RefPtr<blink::RenderStyle> textStyle = StyleUpdater::createRenderStyle(renderStyle, mNode->styles());
            renderText->setStyle(textStyle);
            renderText->setNode(mNode);
            blink::RenderInline* renderInline = new blink::RenderInline();
            renderInline->setStyle(renderStyle);
            renderInline->addChild(renderText);
            mRenderContainer = renderInline;
            return renderInline;
        }else{
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
            mRenderContainer = paragraph;
            return paragraph;
        }
    }

    void SpanView::updateAttr(const std::string& key, const std::string& value) {
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

    void SpanView::updateStyles(std::map<std::string, std::string> *styles) {
         View::updateStyles(styles);
         RefPtr<blink::RenderStyle>  renderStyle = StyleUpdater::newRenderStyleUpdates(renderText->style(), styles);
         renderText->setStyle(renderStyle);
         renderText->setNeedsLayoutAndPrefWidthsRecalc();
         markParentNeedLayout(mRenderObject);
    }

    WTF::String SpanView::getRenderText() {
        std::string cstring = getText();
        const char* text = cstring.c_str();
        int length = cstring.length();
        WTF::String string = WTF::String::fromUTF8(text, length);
        if(isSpaceRidOne()){//rid space two to one
            string.replace("  ", " ");
        }
        return string;
    }


    const std::string SpanView::getText() {
        if(mNode->attrs() != nullptr){
            std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_VALUE);
            if(it != mNode->attrs()->end()){
                return it->second;
            }
        }
        return "";
    }

    bool SpanView::isSpaceRidOne(){
        if(mNode->attrs() != nullptr) {
            std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_SPACE_RID_ONE);
            if (it != mNode->attrs()->end()) {
                return it->second == Html::Attr::Value::ATTR_VALUE_TRUE;
            }
        }
        return  false;
    }



}
