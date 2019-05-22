//
// Created by furture on 2018/12/26.
//

#ifndef WEEX_UIKIT_IMAGEMANAGER_H
#define WEEX_UIKIT_IMAGEMANAGER_H

#include <third_party/skia/src/core/SkLRUCache.h>
#include <render/platform/graphics/ImageInfo.h>
#include "SkiaShareContext.h"
#include "ImageTexture.h"
#include "LruCache.h"
#include "JenkinsHash.h"
#include "RequestImage.h"


namespace weexuikit{

    class ImageManager {

    public:
        static ImageManager* getInstance();

    public:
        sk_sp<SkImage> getImage(blink::ImageInfo *imageInfo);

        void onGetImageBitmap(const RequestImage& requestImage, const SkBitmap &bitmap);

    public:
        void onLowMemory();

    private:
        sk_sp<SkImage> getImageFromCache(std::string &imageKey, uint32_t hashKey, blink::ImageInfo *imageInfo, bool placeholder);
        void asynGetImageFromPlatform(uint32_t cacheKey, blink::ImageInfo *imageInfo,
                                      bool placeholder);
        void requestPlatformImage(const RequestImage &requestImage);
        void notifyPagesGetImage(const std::shared_ptr<ImageTexture>& image);

    private:
        ImageManager();
        ~ImageManager();



    private:
        SkiaShareContext* mSkiaShareContext;
        std::mutex              mLock;
        android::LruCache<uint32_t, std::shared_ptr<ImageTexture>>* mImageLRUCache;

    };
}



#endif //WEEX_UIKIT_IMAGEMANAGER_H
