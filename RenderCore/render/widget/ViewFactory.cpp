//
// Created by furture on 2018/8/25.
//

#include <render/core/parser/Screen.h>
#include <render/core/parser/StyleUpdater.h>
#include "ViewFactory.h"
#include "TextView.h"
#include "ImageView.h"
#include "SpanView.h"
#include "ParaView.h"
#include "LinkView.h"
#include "AnimationView.h"
#include "ScrollerView.h"
#include "PlatformView.h"
#include "TextureView.h"
#include "SliderView.h"

namespace weexuikit {

    View* ViewFactory::createView(const std::string& pageId, const std::string &ref, const std::string &type,
                                   std::map<std::string, std::string> *styles,
                                   std::map<std::string, std::string> *attrs,
                                   std::set<std::string> *events,
                                   UIContext *context, blink::RenderObject *parent, int index) {

        Node* node = new Node(pageId, ref, type, styles, attrs, events);
        View* widget = nullptr;
        if(type == Html::Tag::DIV){
            widget = new View(context, node);
        }else if(type == Html::Tag::TEXT){
            widget = new TextView(context, node);
        }else if(type == Html::Tag::IMAGE || type == Html::Tag::IMG){
            widget = new ImageView(context, node);
        }else if(type == Html::Tag::SPAN){
            widget = new SpanView(context, node);
        }else if(type == Html::Tag::P || type == Html::Tag::PARAGRAPH){
            widget = new ParaView(context, node);
        }else if(type == Html::Tag::A){
            widget = new LinkView(context, node);
        }else if(type == Html::Tag::SCROLLER){
            widget = new ScrollerView(context, node);
        }else if(type == Html::Tag::LIST){
            widget = new ScrollerView(context, node);
        }else if(type == Html::Tag::INPUT){
            widget = new PlatformView(context, node);
        }else if(type == Html::Tag::WEB){
            widget = new PlatformView(context, node);
        }else if(type == Html::Tag::VIDEO){
            widget = new PlatformView(context, node);
        }else if(type == Html::Tag::WWEB){
            widget = new TextureView(context, node);
        }else if(type == Html::Tag::ANIMATION){
            widget = new AnimationView(context, node);
        }else if(type == Html::Tag::SLIDER){
            widget = new SliderView(context, node);
        }

        if(widget == nullptr){
            widget = new View(context, node);
        }

        widget->applyDefault(parent);
        widget->initView(parent);

        blink::RenderObject* child = widget->getRenderObject();
        if(child == nullptr){
            delete widget;
            return nullptr;
        }
        widget->attachRenderObject(parent, index);
        return widget;
    }
}
