//
// Created by furture on 2018/8/25.
//

#include <render/core/rendering/RenderParagraph.h>
#include <render/core/rendering/RenderInline.h>
#include <render/core/rendering/RenderFlexibleBox.h>
#include <render/core/parser/StyleUpdater.h>
#include <render/platform/common/log.h>
#include "View.h"
#include "UIContext.h"


namespace weexuikit {


    View::View(UIContext* context, Node* node)
            :mContext(context),
             mNode(node),
             mRenderObject(nullptr),
             mRenderContainer(nullptr),
             mChildList(nullptr),
             mTransition(nullptr),
             mParent(nullptr){
    }

    View::~View() {
        if(mChildList != nullptr){
            mChildList->clear();
            mChildList->shrink_to_fit();
            delete mChildList;
            mChildList = nullptr;
        }
        if(mNode != nullptr){
            delete  mNode;
            mNode = nullptr;
        }
        if(mRenderObject != nullptr){
            mRenderObject = nullptr;
        }
        if(mTransition != nullptr){
            delete  mTransition;
            mTransition = nullptr;
        }
    }

    void View::applyDefault(blink::RenderObject* parent) {
        if(parent->isRenderParagraph() || parent->isRenderInline()){
            mNode->styles()->insert({Html::Style::STYLE_DISPLAY, Html::Style::STYLE_DISPLAY_INLINE});
        }else{
            mNode->styles()->insert({Html::Style::STYLE_POSITION, Html::Style::STYLE_POSITION_RELATIVE});
        }
    }

    void View::initView(blink::RenderObject *parent) {
        RefPtr<blink::RenderStyle> renderStyle = StyleUpdater::createRenderStyle(parent->style(), mNode->styles());
        mRenderObject = createRenderObject(parent, renderStyle);
        if(mRenderObject->getNode() == nullptr){
            mRenderObject->setNode(mNode);
        }
        mTransition = Transition::fromStyle(mNode->styles(), this);
        mRenderObject->mPointerEventListener = this;
    }

    blink::RenderObject* View::createRenderObject(blink::RenderObject* parent,  RefPtr<blink::RenderStyle> renderStyle) {
        blink::RenderObject* renderObject =  new blink::RenderFlexibleBox();
        renderObject->setStyle(renderStyle);
        mRenderContainer = renderObject;
        return renderObject;
    }


    void View::attachRenderObject(blink::RenderObject *parent, int index) {
        blink::RenderObject* beforeChild = nullptr;
        if(index >= 0){
            beforeChild = parent->childAt(index);
        }
        parent->addChild(mRenderObject, beforeChild);
        markWidgetNeedLayout();
    }

    void View::dettachRenderObject() {
        markParentNeedLayout(mRenderObject);
        mRenderObject->remove();
    }




    blink::RenderObject* View::getRenderObject() {
        return mRenderObject;
    }

    blink::RenderObject* View::getRenderContainer() {
        return mRenderContainer;
    }

    void View::updateAttrs(std::map<std::string, std::string> *attrs) {
        std::map<std::string, std::string>::iterator it = attrs->begin();
        for(;it != attrs->end(); it++){
            mNode->updateAttr(it->first, it->second);
            updateAttr(it->first, it->second);
        }
    }

    void View::updateAttr(const std::string& key, const std::string& value){

    }



    void View::updateStyles(std::map<std::string, std::string> *styles) {
        if(mTransition == nullptr){
            mTransition = Transition::fromStyle(styles, this);
        }
        if(mTransition != nullptr){
            mTransition->updateTranstionParams(styles);
            if(mTransition->hasTransitionProperty(styles)){
                mTransition->startTransition(styles);
            }
        }
        if(styles->size() <= 0){
            return;
        }
        mNode->updateStyles(styles);
        RefPtr<blink::RenderStyle> renderStyle = StyleUpdater::newRenderStyleUpdates(mRenderObject->style(), styles);
        mRenderObject->setStyle(renderStyle);
        markWidgetNeedLayout();
    }



    void View::markParentNeedLayout(blink::RenderObject* renderObject) {
        blink::RenderObject* parent = renderObject->parent();
        while (parent){
            parent->setNeedsLayout();
            parent->setChildNeedsLayout();
            parent = parent->parent();
        }
    }

    void View::markChildNeedLayout(blink::RenderObject *renderObject) {
        blink::RenderObjectChildList* childList =  renderObject->virtualChildren();
        if(!childList){
            return;
        }
        for (blink::RenderObject* child = childList->firstChild(); child;  child = child->nextSibling()) {
            if(!child->needsLayout()){
                child->setNeedsLayout();
                child->setChildNeedsLayout();
                markChildNeedLayout(child);
            }
        }
    }

    void View::markWidgetNeedLayout() {
        mRenderObject->setNeedsLayout();
        mRenderObject->setChildNeedsLayout();
        markParentNeedLayout(mRenderObject);
        markChildNeedLayout(mRenderObject);
    }

    Node* View::getNode() {
        return mNode;
    }

    UIContext* View::getUIContext() {
        return mContext;
    }


    void View::remove(weexuikit::View *child) {
        if(mChildList == nullptr){
            return;
        }
        mChildList->erase(std::remove(mChildList->begin(), mChildList->end(), child), mChildList->end());
    }


    void View::addChild(View *child, int index){
        if(mChildList == nullptr){
            mChildList = new std::vector<View*>();
        }
        if(child->Parent() != nullptr){
            child->Parent()->remove(child);
        }
        child->setParent(mParent);
        if(index >= mChildList->size()){
            mChildList->push_back(child);
        }else{
            mChildList->insert(mChildList->begin() + index, child);
        }
    }

    void View::setParent(weexuikit::View *parent) {
        mParent = parent;
    }


    const std::string& View::getAttr(const std::string &key) {
        auto it =  mNode->attrs()->find(key);
        if(it != mNode->attrs()->end()){
            return it->second;
        }
        return EMPTY_STRING;
    }

    void View::onPointerEvent(weexuikit::PointerEvent &pointerEvent) {
        if(mRenderObject->style()->affectedByActive()){
            if(pointerEvent.isDownEvent()){
                std::map<std::string, std::string>* styles =  mNode->getActiveStyle();
                updateStyles(styles);
                mContext->markNeedsPaint();
            }else if(pointerEvent.isCancelEvent() || pointerEvent.isUpEvent()){
                if(mNode->getResetStyle() != nullptr){
                    updateStyles(mNode->getResetStyle());
                    mContext->markNeedsPaint();
                }
            }
        }
    }

}
