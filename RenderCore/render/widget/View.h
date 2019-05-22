//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_WIDGET_H
#define WEEXRENDERER_WIDGET_H
#include "UIContext.h"
#include "transition/Transition.h"
#include <render/core/node/Node.h>
#include <render/core/rendering/RenderObject.h>
#include <render/gesture/gesture/PointerEventListener.h>
#include <string>
#include <set>
#include <map>

namespace weexuikit {

    class View : public weexuikit::PointerEventListener  {

    public:
        View(UIContext* context, Node* node);
        ~View();

        virtual void applyDefault(blink::RenderObject* parent);

        void initView(blink::RenderObject* parent);

        virtual blink::RenderObject* createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle);


        virtual void attachRenderObject(blink::RenderObject* parent, int index);

        void dettachRenderObject();

        void updateAttrs(std::map<std::string, std::string> *attrs);
        virtual void updateAttr(const std::string& key, const std::string& value);
        virtual void updateStyles(std::map<std::string, std::string> *styles);

        void markParentNeedLayout(blink::RenderObject* renderObject);
        void markChildNeedLayout(blink::RenderObject* renderObject);
        void markWidgetNeedLayout();

        /**
         * return root renderobject for the object
         * */
        blink::RenderObject* getRenderObject();

        /**
         * return the render container for the object,
         * if not supported add child, return null.
         * */
        blink::RenderObject* getRenderContainer();

        /**
         * return node object
         * */
        Node* getNode();

        /**
         * UIContext
         * */
        UIContext* getUIContext();

        /**
         * for furture use, becasue render object has a tree, widget tree is not necessary
         */
        void addChild(View* child, int index);
        void remove(View* child);
        View* Parent(){
            return mParent;
        }
        void setParent(View *pView);

    public:
        const std::string& getAttr(const std::string& key);

    public:
        virtual void onPointerEvent(weexuikit::PointerEvent& pointerEvent);


    protected:
        Node* mNode;
        UIContext* mContext;
        blink::RenderObject* mRenderObject;
        blink::RenderObject* mRenderContainer;
        std::vector<View*>* mChildList;
        Transition* mTransition;
        View* mParent;
    };
}



#endif //WEEXRENDERER_WIDGET_H
