//
// Created by furture on 2019/1/15.
//

#include <render/frame/android/RenderJava.h>
#include <mutex>
#include <render/platform/common/log.h>
#include <render/public/platform/Platform.h>
#include <render/frame/TaskRunners.h>
#include <set>
#include "TextureManager.h"
#include "SkiaShareContext.h"

namespace weexuikit {


    TextureManager* TextureManager::getInstance() {
        static TextureManager* instance  = nullptr;
        static std::once_flag oflag;
        std::call_once(oflag, [&](){
            instance = new TextureManager();
        });
        return instance;
    }

    TextureManager::TextureManager() {

    }

    void TextureManager::createTexture(const std::string& pageId,  const std::string& ref,
                                       const std::string& type,
                                       const std::map<std::string, std::string>* attrs,
                                       const std::map<std::string, std::string>* styles,
                                       const std::set<std::string> * events) {

        std::map<std::string, std::string> attrsClone = *attrs;
        std::map<std::string, std::string> stylesClone = *styles;
        std::set<std::string> eventsClone  = *events;
        TaskRunners::io()->PostTask([=]{
            blink::Platform::current()->createExternalTexture(pageId, ref, type, attrsClone, stylesClone, eventsClone);
        });
    }


    void TextureManager::destoryTexture(const std::string &pageId, const std::string &ref) {

    }

    sk_sp<SkImage> TextureManager::getTextureImage(const std::string &pageId,
                                                   const std::string &ref) {
        sk_sp<SkImage> nullImage;
        std::lock_guard<std::mutex> lock(mMutex);
        auto  it = mTextureImages.find(ref);
        if(it != mTextureImages.end()){
            return it->second;
        }
        return nullImage;
    }


}