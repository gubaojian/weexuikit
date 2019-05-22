//
// Created by furture on 2018/8/25.
//

#include "LinkView.h"
#include "View.h"
#include <render/core/node/NodeStyles.h>
#include <render/core/rendering/RenderParagraph.h>
#include <render/core/rendering/RenderFlexibleBox.h>
#include <render/core/rendering/RenderInline.h>
#include <render/core/rendering/RenderText.h>
#include <render/core/parser/StyleUpdater.h>

namespace weexuikit {

    LinkView::LinkView(UIContext *context, Node *node) : View(context, node) {

    }


    void LinkView::applyDefault(blink::RenderObject* parent) {
        View::applyDefault(parent);
        std::map<std::string, std::string>::iterator it =  mNode->styles()->find(Html::Style::STYLE_COLOR);
        if(it == mNode->styles()->end()){
            mNode->styles()->insert({Html::Style::STYLE_COLOR, Html::Color::STYLE_COLOR_A_LINK});
        }
        mNode->events()->insert(Html::Event::CLICK);
    }


    blink::RenderObject* LinkView::createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) {
        if(renderStyle->display() == blink::EDisplay::INLINE){
            blink::RenderInline* renderInline = new blink::RenderInline();
            renderInline->setStyle(renderStyle);
            mRenderContainer = renderInline;
            return renderInline;
        }else{
            blink::RenderFlexibleBox* paragraph = new blink::RenderFlexibleBox();
            paragraph->setStyle(renderStyle);
            mRenderContainer = paragraph;
            return paragraph;
        }
    }


}