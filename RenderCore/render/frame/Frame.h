//
// Created by furture on 2018/8/7.
//

#ifndef WEEX_UIKIT_FRAME_H
#define WEEX_UIKIT_FRAME_H
#include <render/widget/View.h>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include "UIContextImpl.h"

namespace weexuikit{


    /**
     * RenderFrame Mean One Page or iframe
     * */
    class Frame {

        public:
            Frame();
            ~Frame();

            /**
             * params styles attrs events will be moved to node, your should not delete it.
             * */
            void actionCreateBody(const std::string& ref, const std::string& type, std::map<std::string, std::string> *styles, std::map<std::string, std::string> *attrs, std::set<std::string> *events);

            /**
             * params styles attrs events will be moved to node, your should not delete it.
             * */
            void actionAddElement(const std::string& ref, const std::string& type, const std::string& parentRef, int index,
                                  std::map<std::string, std::string> *styles, std::map<std::string, std::string> *attrs, std::set<std::string> *events);

            void actionUpdateAttrs(const std::string& ref,std::map<std::string, std::string> *attrs);

            void actionUpdateStyles(const std::string& ref,std::map<std::string, std::string> *styles);

            void actionAddEvent(const std::string& ref, const std::string& event);

            void actionRemoveEvent(const std::string& ref, const std::string& event);

            void actionRemoveElement(const std::string& ref);

            void actionMoveElement(const std::string& ref, const std::string& parentRef, int index);

            void refreshFont(const std::string& fontFaimly);

            int getBlockLayout(const std::string &ref, int edge);

            std::string getAttrs(const std::string& ref, const std::string& key);

            Node* getNode(const std::string& ref);

            blink::RenderView* getRenderView(){
                return renderView;
            }

            blink::Color getBackgroundColor();

            UIContextImpl* getUIContext(){
                return mContext;
            }

           void fireEvent(weexuikit::Node* node, const std::string& event, const std::map<std::string,std::string>& params);


    public:
            bool hasRenderView();
            void setBodyHeight(int bodyHeight);


       public:
            inline void setPageId(const std::string& pageId){
                mPageId = pageId;
            }

            inline std::string& getPageId(){
                return mPageId;
            }



    private:
        void destoryRenderView();
        View* GetWidget(const std::string &ref);
        blink::RenderView*  renderView;
        std::map<std::string, View*> widgetRegistry;
        UIContextImpl* mContext;
        View* mBody;
        std::string ref;
        std::string mPageId;
    };
}



#endif //WEEX_UIKIT_DOCUMENT_H
