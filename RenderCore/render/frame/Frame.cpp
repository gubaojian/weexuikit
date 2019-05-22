//
// Created by furture on 2018/8/7.
//
#include "Frame.h"
#include "SkiaFontSelector.h"
#include "RenderBodyHelper.h"
#include <render/platform/text/LocaleToScriptMapping.h>
#include <render/platform/Partitions.h>
#include <render/core/rendering/RenderView.h>
#include <render/core/rendering/RenderText.h>
#include <render/core/rendering/RenderImage.h>
#include <render/core/rendering/RenderImageResource.h>
#include <render/core/rendering/RenderParagraph.h>
#include <render/core/rendering/RenderInline.h>
#include <render/platform/geometry/IntSize.h>
#include <render/core/rendering/SubtreeLayoutScope.h>
#include <render/core/rendering/RenderBlock.h>
#include <render/core/rendering/style/RenderStyle.h>
#include <render/core/rendering/RenderFlexibleBox.h>
#include <render/public/platform/Platform.h>
#include <render/core/parser/StyleUpdater.h>
#include <render/core/parser/Screen.h>
#include <render/core/parser/StyleParser.h>
#include <render/widget/ViewFactory.h>

namespace weexuikit{


    Frame::Frame() {
        this->renderView = nullptr;
        this->mBody = nullptr;
        this->mContext = new UIContextImpl(this);
    }

    Frame::~Frame() {
        destoryRenderView();
    }

    void Frame::destoryRenderView() {
        if(widgetRegistry.size() > 0){
            std::map<std::string, View*>::iterator it = widgetRegistry.begin();
            for(;it != widgetRegistry.end(); it++){
                if(it->second != nullptr){
                    delete it->second;
                    it->second = nullptr;
                }
            }
            widgetRegistry.clear();
        }
        if(renderView != nullptr){
            renderView->destroy();
            renderView = nullptr;
        }
        mBody = nullptr;
    }



    void Frame::actionCreateBody(const std::string& ref, const std::string& type, std::map<std::string, std::string> *styles, std::map<std::string, std::string> *attrs, std::set<std::string> *events){
        destoryRenderView();
        Body::cleanBoxOuterStyle(styles);
        if(renderView == nullptr){
            int width = 0;
            std::map<std::string, std::string>::iterator it = styles->find(Html::Style::STYLE_WIDTH);
            if(it != styles->end()){
                width = weexuikit::StyleParser::parseStringByViewPortUnit(it->second);
            }
            renderView = Body::createRenderView(width, 0);
        }
        this->ref = ref;
        std::string bodyType = Html::Tag::DIV;

        View* widget = ViewFactory::createView(mPageId, ref, type, styles, attrs, events, getUIContext(),
                                               renderView, -1);
        mBody  = widget;
        if(widget != nullptr){
            widgetRegistry.insert({ref, widget});
        }
    }

    void Frame::actionAddElement(const std::string& ref, const std::string& type, const std::string& parentRef,
                                    int index, std::map<std::string, std::string> *styles,
                                    std::map<std::string, std::string> *attrs,
                                    std::set<std::string> *events) {
        View* parentView = GetWidget(parentRef);
        if(parentView == nullptr){
            return;
        }
        blink::RenderObject* parent = parentView->getRenderContainer();
        if(parent == nullptr){
            return;
        }
        View* child = ViewFactory::createView(mPageId, ref, type, styles, attrs, events, getUIContext(),
                                              parent, index);
        if(child != nullptr){
            widgetRegistry.insert({ref, child});
        }
    }

    void Frame::actionUpdateAttrs(const std::string& ref, std::map<std::string, std::string> *attrs) {
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return;
        }
        widget->updateAttrs(attrs);
    }

    void Frame::actionUpdateStyles(const std::string& ref,std::map<std::string, std::string> *styles){
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return;
        }
        if(this->ref == ref){
            Body::cleanBoxOuterStyle(styles);
        }
        widget->updateStyles(styles);
    }

    void Frame::actionAddEvent(const std::string& ref, const std::string& event) {
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return;
        }
        Node* node = widget->getNode();
        node->events()->insert(event);
    }

    void Frame::actionRemoveEvent(const std::string& ref, const std::string& event) {
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return;
        }
        Node* node = widget->getNode();
        node->events()->erase(event);
    }

    void Frame::actionRemoveElement(const std::string& ref) {
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return;
        }
        blink::RenderObject* renderObject = widget->getRenderObject();
        widget->dettachRenderObject();
        renderObject->destroy();
        widgetRegistry.erase(ref);
        delete  widget;
    }


    void Frame::actionMoveElement(const std::string& ref, const std::string& parentRef, int index) {
        View* view = GetWidget(ref);
        View* parentView = GetWidget(parentRef);
        if(view == nullptr
           || parentView == nullptr
           || parentView->getRenderContainer() == nullptr){
            return;
        }
        view->dettachRenderObject();
        view->attachRenderObject(parentView->getRenderContainer(), index);
    }

    static void refreshRenderObjectFont(blink::RenderObject* renderObject, const WTF::AtomicString& fontFaimly){
        if(renderObject->style()->fontDescription().family().family() == fontFaimly){
            StyleUpdater::updateRenderStyleFontFamily(renderObject->style(), fontFaimly);
            renderObject->setNeedsLayoutAndPrefWidthsRecalc();
        }
        blink::RenderObjectChildList* childList =  renderObject->virtualChildren();
        if(!childList){
            return;
        }
        for (blink::RenderObject* child = childList->firstChild(); child;  child = child->nextSibling()) {
            refreshRenderObjectFont(child, fontFaimly);
        }
    }

    void Frame::refreshFont(const std::string& fontFaimly) {
        if(renderView == nullptr){
            return;
        }
        WTF::AtomicString fontFaimlyName = WTF::String::fromUTF8(fontFaimly.c_str());
        refreshRenderObjectFont(renderView, fontFaimlyName);
    }



    int Frame::getBlockLayout(const std::string &ref, int edge) {
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return -1;
        }
        blink::RenderObject* renderObject = widget->getRenderObject();
        if(renderObject == nullptr){
            return -1;
        }
        blink::RenderBox* renderBox = (blink::RenderBox *) renderObject->containingBlock();
        if(edge == NODE_LAYOUT_EDGE_LEFT){
            return renderBox->absoluteContentBox().x();
        }

        if(edge == NODE_LAYOUT_EDGE_TOP){
            return renderBox->absoluteContentBox().y();
        }

        if(edge == NODE_LAYOUT_EDGE_WIDTH){
            return renderBox->pixelSnappedWidth();
        }

        if(edge == NODE_LAYOUT_EDGE_HEIGHT){
            return renderBox->pixelSnappedHeight();
        }
        return  renderBox->pixelSnappedHeight();
    }

    View* Frame::GetWidget(const std::string &ref) {
        std::map<std::string, View*>::iterator iter = widgetRegistry.find(ref);
        if (iter != widgetRegistry.end()) {
            return iter->second;
        } else {
            return nullptr;
        }
    }

    void Frame::fireEvent(weexuikit::Node *node, const std::string &event, const std::map<std::string, std::string> &params) {
        if(node->getAttr("type") != "starBucks"){
            return;
        }
        {
            std::string offsetStr = params.at(Html::Event::SCROLL_OFFSET);
            float offset  = StyleParser::parseStringToFloat(offsetStr.data());
            std::string isFold = node->getAttr("isFold");
            std::string scrollRef = "5";
            std::string navWrapRef = "6";
            std::string navRef = "26";
            std::string minNavRef = "1028926";
            if(offset < -200 && isFold != "isFold"){
                node->updateAttr("isFold", "isFold");
                std::map<std::string, std::string> scrollerMap = {
                        {"transform", "translateY(-320px)"}
                };
                actionUpdateStyles(scrollRef, &scrollerMap);

                std::map<std::string, std::string> navWrapMap = {
                        {"height", "108px"}
                };
                actionUpdateStyles(navWrapRef, &navWrapMap);


                std::map<std::string, std::string> navMap = {
                        {"opacity", "0"}
                };
                actionUpdateStyles(navRef, &navMap);


                std::map<std::string, std::string> minNavMap = {
                        {"opacity", "1"}
                };
                actionUpdateStyles(minNavRef, &minNavMap);
            }
            if(offset > -100 && isFold == "isFold"){
                node->updateAttr("isFold", "");
                std::map<std::string, std::string> scrollerMap = {
                        {"transform", "translateY(0px)"}
                };
                actionUpdateStyles(scrollRef, &scrollerMap);

                std::map<std::string, std::string> navWrapMap = {
                        {"height", "380px"}
                };
                actionUpdateStyles(navWrapRef, &navWrapMap);

                std::map<std::string, std::string> navMap = {
                        {"opacity", "1"}
                };
                actionUpdateStyles(navRef, &navMap);

                std::map<std::string, std::string> minNavMap = {
                        {"opacity", "0"}
                };
                actionUpdateStyles(minNavRef, &minNavMap);
            }
        }
    }

    bool Frame::hasRenderView() {
        return renderView != nullptr;
    }

    blink::Color Frame::getBackgroundColor() {
        if(renderView != nullptr && renderView->children() != nullptr
           && renderView->children()->firstChild() != nullptr
           && renderView->children()->firstChild()->style() != nullptr){
            blink::RenderStyle* style = renderView->children()->firstChild()->style();
            blink::Color color = style->backgroundColor().color();
            if(color.rgb() != 0){
                return style->backgroundColor().color();
            }
        }
        return blink::Color::white;
    }

    Node *Frame::getNode(const std::string &ref) {
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return nullptr;
        }
        Node* node = widget->getNode();
        return node;
    }

    std::string Frame::getAttrs(const std::string& ref, const std::string& key){
        View* widget = GetWidget(ref);
        if(widget == nullptr){
            return "";
        }
        Node* node = widget->getNode();
        if(key == Html::Attr::ATTR_ARIA_LABEL){
            return node->getAccessibility();
        }
        std::map<std::string,std::string>::iterator it = node->attrs()->find(key);
        if(it != node->attrs()->end()){
            return it->second;
        }
        return "";
    }

    void Frame::setBodyHeight(int bodyHeight) {
        if(mBody == nullptr){
            return;
        }
        if(bodyHeight <= 0){
            return;
        }
        blink::RenderObject* renderObject = mBody->getRenderObject();
        if(bodyHeight == renderObject->style()->height().intValue()
                && renderObject->style()->height().isFixed()){
            return;
        }
        PassRefPtr<blink::RenderStyle> renderStyle = blink::RenderStyle::clone(renderObject->style());
        renderStyle->setLogicalHeight({bodyHeight, blink::LengthType::Fixed});
        renderObject->setStyle(renderStyle);
    }


}
