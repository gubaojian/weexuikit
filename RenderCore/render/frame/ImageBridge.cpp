//
// Created by furture on 2019/1/1.
//

#include "ImageBridge.h"
#include "ImageManager.h"

namespace weexuikit{

    ImageBridge::ImageBridge(weexuikit::PageManager *pageManager) {
        mPageManager = pageManager;
    }

    ImageBridge::~ImageBridge() {

    }


    void ImageBridge::onGetImage(const weexuikit::RequestImage &requestImage,const SkBitmap& bitmap) {
        ImageManager::getInstance()->onGetImageBitmap(requestImage, bitmap);
    }

    void ImageBridge::onLowMemory() {
        ImageManager::getInstance()->onLowMemory();
    }

}