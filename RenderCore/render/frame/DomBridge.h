//
// Created by furture on 2018/12/29.
//

#ifndef WEEX_UIKIT_DOMBRIDGE_H
#define WEEX_UIKIT_DOMBRIDGE_H
#include "PageManager.h"


namespace weexuikit{

    class DomBridge {


    public:
        DomBridge(PageManager* pageManager);
        ~DomBridge();


    public:

        void createBody(
                const std::string& pageId,
                const std::string& ref,
                const std::string& type,
                std::map<std::string,std::string>* styles,
                std::map<std::string,std::string>* attrs,
                std::set<std::string>* events);

        void addElement(
                const std::string& pageId,
                const std::string& ref,
                const std::string& type,
                const std::string& parentRef,
                int index,
                std::map<std::string,std::string>* styles,
                std::map<std::string,std::string>* attrs,
                std::set<std::string>* events);

        void updateAttrs(
                const std::string &pageId,
                const std::string &ref,
                std::map<std::string, std::string> *attrs);

        void updateStyles(
                const std::string& pageId,
                const std::string& ref,
                std::map<std::string,std::string>* styles);

        void addEvent(
                const std::string& pageId,
                const std::string& ref,
                const std::string& event);

        void removeEvent(
                const std::string& pageId,
                const std::string& ref,
                const std::string& event);

        void moveElement(
                const std::string& pageId,
                const std::string& ref,
                const std::string& parentRef,
                int index);

        void removeElement(
                const std::string& pageId,
                const std::string& ref);


        void destroyPage(const std::string &pageId);


    public:
        void refreshFont(const std::string &pageId, const std::string& fontFaimly);

    private:
        PageManager* mPageManager;

    };

}



#endif //WEEX_UIKIT_DOMBRIDGE_H
