//
// Created by furture on 2018/12/26.
//

#include <mutex>
#include <sstream>
#include <render/core/node/Node.h>
#include "ImageManager.h"
#include "render/platform/graphics/ImageInfo.h"
#include "render/public/platform/Platform.h"
#include "UIContextImpl.h"
#include "TaskRunners.h"
#include "PageManager.h"
#include "UIEngine.h"

namespace weexuikit{

    #define  MAX_IMG_LRU_CACHE_SIZE 128

    ImageManager* ImageManager::getInstance() {
        static ImageManager* instance  = nullptr;
        static std::once_flag oflag;
        std::call_once(oflag, [&](){
            instance = new ImageManager();
        });
        return instance;
    }

    ImageManager::ImageManager(){
        mImageLRUCache = new android::LruCache<uint32_t, std::shared_ptr<ImageTexture>>(MAX_IMG_LRU_CACHE_SIZE);
    }


    ImageManager::~ImageManager() {
       if(mImageLRUCache != nullptr){
           mImageLRUCache->clear();
           delete mImageLRUCache;
           mImageLRUCache = nullptr;
       }
    }

    void ImageManager::onGetImageBitmap(const RequestImage& requestImage, const SkBitmap &bitmap) {
        ImageManager* wealSelf = this;
        TaskRunners::io()->PostTask([=]{
            std::shared_ptr<ImageTexture> entry;
            {
                std::lock_guard<std::mutex> lk(mLock);
                entry = mImageLRUCache->get(requestImage.callbackId);
            }
            if(entry.get() == nullptr){
                return;
            }
            if(bitmap.isNull()){ //FIXME Notify APPEAR, Disappear
                entry->setState(ImageState::Failed);
                return;
            }
            weexuikit::SkiaShareContext* shareGRContext = weexuikit::SkiaShareContext::getInstance();
            sk_sp<SkImage> texturedImage = SkImage::MakeCrossContextFromPixmap(shareGRContext->getGRContext().get(), bitmap.pixmap(), false, nullptr);
            shareGRContext->getGRContext()->flush();
            (entry)->setImage(texturedImage);
            entry->setState(ImageState::Textured);
            wealSelf->notifyPagesGetImage(entry);
        });
    }


    void ImageManager::notifyPagesGetImage(const std::shared_ptr<ImageTexture>& image) {
        std::set<std::string> pageIds = image->getWatchPageIds();
        PageManager* pageManager = UIEngine::getInstance()->getPageManager();
        for(const std::string& pageId : pageIds){
            pageManager->dispatchPageAction(pageId,[=](Page* page){
                page->getFramePipeline()->markDiry();
            });
        }
        image->clearWatchPageIds();
    }




    sk_sp<SkImage> ImageManager::getImage(blink::ImageInfo *imageInfo) {
        static sk_sp<SkImage> nullImage;
        if(imageInfo->getImageUrl().length() <= 0 && imageInfo->getPlaceholder().length()<=0){
            return nullImage;
        }
        if(imageInfo->getImageUrl().length() > 0){
            sk_sp<SkImage> image = getImageFromCache(imageInfo->getImageKey(), imageInfo->getImageHashKey(), imageInfo, false);
            if(image.get() != nullptr){
                return image;
            }
        }
        if(imageInfo->getPlaceholder().length() <= 0){
            return nullImage;
        }
        return getImageFromCache(imageInfo->getPlaceHolderKey(), imageInfo->getPlaceHolderHashKey(), imageInfo, true);
    }




    //we should use skia lru cache to achive small binary size.
    sk_sp<SkImage> ImageManager::getImageFromCache(std::string &imageKey, uint32_t imageHashKey, blink::ImageInfo *imageInfo, bool placeholder){
        static sk_sp<SkImage> nullImage;
        weexuikit::Node* node = (Node *)(imageInfo->getNode());
        std::shared_ptr<ImageTexture> entry;
        {
            std::lock_guard<std::mutex> lk(mLock);
            entry = mImageLRUCache->get(imageHashKey);
        }
        if(entry != nullptr){
            if(entry.get() != nullptr){
                if(entry->getImageKey() == imageKey){
                    if((entry)->getState() == ImageState::Textured
                         && (entry)->getImage().get() != nullptr){
                        return  (entry)->getImage();
                    }
                    if((entry)->getState() == ImageState::Loading) {
                        entry->addWatchPageId(node->getPageId());
                        return nullImage;
                    }
                }
            }
        }

        if(entry == nullptr || entry.get() == nullptr || (entry)->getState() != ImageState::Loading){
            std::shared_ptr<ImageTexture> imageTexture = std::make_shared<ImageTexture>();
            imageTexture->setImageKey(imageKey);
            imageTexture->addWatchPageId(node->getPageId());
            {
                std::lock_guard<std::mutex> lk(mLock);
                mImageLRUCache->put(imageHashKey, imageTexture);
            }
            if(entry != nullptr && entry.get() != nullptr){
                std::set<std::string> pageIds = entry->getWatchPageIds();
                for(const std::string& pageId : pageIds) {
                    imageTexture->addWatchPageId(pageId);
                }
            }
            asynGetImageFromPlatform(imageHashKey, imageInfo, placeholder);
        }
        return nullImage;
    }


    void ImageManager::asynGetImageFromPlatform(uint32_t cacheKey, blink::ImageInfo *imageInfo,
                                                bool placeholder) {
        blink::ImageInfo copyImageInfo = (*imageInfo);
        //use method in widget
        weexuikit::Node* node = static_cast<Node *>(imageInfo->getNode());
        RequestImage requestImage;
        requestImage.pageId = node->getPageId();
        requestImage.ref = node->ref();
        if(placeholder){
            requestImage.url = imageInfo->getPlaceholder();;
        }else{
            requestImage.url = imageInfo->getImageUrl();
        }
        requestImage.width = imageInfo->getContentSize().width();
        requestImage.height = imageInfo->getContentSize().height();
        requestImage.callbackId = cacheKey;
        TaskRunners::io()->PostTask([=]{
            ImageManager::getInstance()->requestPlatformImage(requestImage);
        });
    }

    void ImageManager::requestPlatformImage(const RequestImage &requestImage){
        blink::Platform::current()->getImageBitmap(requestImage);
    }

    void ImageManager::onLowMemory() {
        TaskRunners::io()->PostTask([=]{
            {
                std::lock_guard<std::mutex> lk(mLock);
                int cleanCacheSize = mImageLRUCache->size();
                for(int i=0; i<cleanCacheSize; i++){
                    mImageLRUCache->removeOldest();
                }
            }
            {
                weexuikit::SkiaShareContext* shareGRContext = weexuikit::SkiaShareContext::getInstance();
                shareGRContext->getGRContext()->freeGpuResources();
                shareGRContext->getGRContext()->flush();
            }
        });
    }

}