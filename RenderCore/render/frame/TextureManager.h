//
// Created by furture on 2019/1/15.
//

#ifndef WEEX_UIKIT_TEXTUREMANAGER_H
#define WEEX_UIKIT_TEXTUREMANAGER_H

#include <string>
#include <set>
#include <third_party/skia/src/gpu/GrDrawOpTest.h>
#include <third_party/skia/include/core/SkImage.h>
#include <map>
#include <mutex>

namespace weexuikit {



    class TextureManager {

       public:
          static TextureManager* getInstance();

       private:
           TextureManager();


       public:
          void createTexture(const std::string& pageId,  const std::string& ref, const std::string& type,
                             const std::map<std::string, std::string>* attrs,
                             const std::map<std::string, std::string>* styles,
                             const std::set<std::string>  *events);

          sk_sp<SkImage> getTextureImage(const std::string& pageId, const std::string& ref);

          void destoryTexture(const std::string& pageId,  const std::string& ref);

    private:
           std::map<std::string, sk_sp<SkImage>> mTextureImages;
           std::mutex mMutex;

    };

}



#endif //WEEX_UIKIT_TEXTUREMANAGER_H
