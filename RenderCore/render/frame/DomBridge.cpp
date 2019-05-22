//
// Created by furture on 2018/12/29.
//

#include "DomBridge.h"

namespace weexuikit{


    DomBridge::DomBridge(PageManager* pageManager) {
        mPageManager = pageManager;
    }

    DomBridge::~DomBridge() {

    }

    void DomBridge::createBody(const std::string &pageId, const std::string &ref,
                               const std::string &type, std::map<std::string, std::string> *styles,
                               std::map<std::string, std::string> *attrs,
                               std::set<std::string> *events) {
        mPageManager->dispatchCreatePageAction(pageId, [=](Page *page){
            page->getFrame()->actionCreateBody(ref, type, styles, attrs, events);
        });
    }

    void DomBridge::addElement(const std::string &pageId, const std::string &ref,
                               const std::string &type, const std::string &parentRef, int index,
                               std::map<std::string, std::string> *styles,
                               std::map<std::string, std::string> *attrs,
                               std::set<std::string> *events) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionAddElement(ref, type, parentRef, index, styles, attrs, events);
        });
    }

    void DomBridge::updateAttrs(const std::string &pageId, const std::string &ref,
                                std::map<std::string, std::string> *attrs) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionUpdateAttrs(ref,  attrs);
            delete  attrs;
        });
    }


    void DomBridge::updateStyles(const std::string &pageId, const std::string &ref,
                                 std::map<std::string, std::string> *styles) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionUpdateStyles(ref, styles);
            delete  styles;
        });
    }


    void DomBridge::addEvent(const std::string &pageId, const std::string &ref,
                             const std::string &event) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionAddEvent(ref, event);
        });
    }

    void DomBridge::removeEvent(const std::string &pageId, const std::string &ref,
                                const std::string &event) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionRemoveEvent(ref, event);
        });
    }

    void DomBridge::removeElement(const std::string &pageId, const std::string &ref) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionRemoveElement(ref);
        });
    }

    void DomBridge::moveElement(const std::string &pageId, const std::string &ref,
                                const std::string &parentRef, int index) {
        mPageManager->dispatchPageAction(pageId, [=](Page *page){
            page->getFrame()->actionMoveElement(ref, parentRef, index);
        });
    }

    void DomBridge::destroyPage(const std::string &pageId) {
        mPageManager->destroyPage(pageId);
    }


    void DomBridge::refreshFont(const std::string &pageId, const std::string &fontFaimly) {
        mPageManager->dispatchPageAction(pageId, [=](Page* page){
            page->getFrame()->refreshFont(fontFaimly);
        });
    }
}