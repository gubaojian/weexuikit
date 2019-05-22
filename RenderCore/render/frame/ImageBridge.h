//
// Created by furture on 2019/1/1.
//

#ifndef WEEX_UIKIT_IMAGEBRIDGE_H
#define WEEX_UIKIT_IMAGEBRIDGE_H

#include "PageManager.h"
#include "RequestImage.h"

namespace weexuikit{

    class ImageBridge {


        public:
            ImageBridge(PageManager* pageManager);
            ~ImageBridge();

        public:
            void onGetImage(const RequestImage& requestImage, const SkBitmap& bitmap);

            void onLowMemory();


        private:
            PageManager* mPageManager;
    };
}



#endif //WEEX_UIKIT_IMAGEBRIDGE_H
