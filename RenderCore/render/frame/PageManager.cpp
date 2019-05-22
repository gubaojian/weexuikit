//
// Created by furture on 2018/12/29.
//

#include "PageManager.h"
#include "TaskRunners.h"

namespace weexuikit{


    PageManager::PageManager() {
        mPages = new std::map<std::string, Page*>();
    }

    PageManager::~PageManager() {
        if(mPages != nullptr){
            delete mPages;
            mPages = nullptr;
        }
    }



    void PageManager::dispatchPageAction(const std::string &pageId, const PageAction &action) {
           TaskRunners::ui()->PostTask([=]{
                 auto it = mPages->find(pageId);
                 if(it == mPages->end()){
                     return;
                 }
                 Page* page = it->second;
                 if(page == nullptr){
                     return;
                 }
                 action(page);
           });
    }

    void PageManager::dispatchCreatePageAction(const std::string &pageId, const PageAction &action) {
        TaskRunners::ui()->PostTask([=]{
            auto it = mPages->find(pageId);
            Page* page = nullptr;
            if(it == mPages->end()){
                page = new Page();
                mPages->insert({pageId, page});
            }else{
                page = it->second;
            }
            page->setPageId(pageId);
            page->getFrame()->setPageId(pageId);
            action(page);
            LOGE("Weex", "Page Create %s", pageId.c_str());
        });
    }

    void PageManager::dispatchAllPageAction(const PageAction &action) {
        TaskRunners::ui()->PostTask([=]{
            for(auto it = mPages->begin(); it != mPages->end(); it++){
                action(it->second);
            }
        });
    }

    void PageManager::destroyPage(const std::string &pageId) {
        TaskRunners::ui()->PostTask([=]{
            auto it = mPages->find(pageId);
            if(it == mPages->end()){
                return;
            }
            Page* page = it->second;
            if(page != nullptr){
                delete  page;
            }
            mPages->erase(pageId);
            LOGE("Weex", "Page Remove %s", pageId.c_str());
        });
    }

    Page* PageManager::getPageUnSafe(const std::string &pageId) {
        auto it = mPages->find(pageId);
        if(it == mPages->end()){
            return nullptr;
        }
        Page* page = it->second;
        return page;
    }



}