//
// Created by furture on 2018/12/29.
//

#ifndef WEEX_UIKIT_FRAMEMANAGER_H
#define WEEX_UIKIT_FRAMEMANAGER_H
#include "Page.h"


namespace weexuikit{

    using PageAction = std::function<void(Page* page)>;

    class PageManager {

    public:
        PageManager();
        ~PageManager();

    public:
        void dispatchCreatePageAction(const std::string &pageId, const PageAction &action);
        void dispatchPageAction(const std::string& pageId, const PageAction& action);
        void dispatchAllPageAction(const PageAction& action);

    public:
        void destroyPage(const std::string &pageId);

    public:
        Page* getPageUnSafe(const std::string& pageId);

    private:
        std::map<std::string,Page*>* mPages;

    };
}


#endif //WEEX_UIKIT_FRAMEMANAGER_H
