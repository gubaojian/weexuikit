//
// Created by furture on 2018/12/29.
//

#ifndef WEEX_UIKIT_UIENGINE_H
#define WEEX_UIKIT_UIENGINE_H

#include <string>
#include <map>
#include "PageManager.h"
#include "PageManager.h"
#include "DomBridge.h"
#include "PlatformBridge.h"
#include "WindowManager.h"
#include "ImageBridge.h"

namespace weexuikit{


    /**
     * some logic move to one application.
     * */
    class UIEngine {

        public:
            static UIEngine* getInstance();

        public:
            void init(std::map<std::string, std::string> params,
                      int screenWidth, int screenHeight,
                      float density);

            DomBridge* getDomBridge();

            PlatformBridge* getPlatformBridge();

            WindowManager* getWindowManager();

            PageManager*  getPageManager();

            ImageBridge* getImageBridge();


            void destroy();


        private:
            UIEngine();
            ~UIEngine();

        private:
           WindowManager* mWindowManager;
           PageManager* mPageManager;
           DomBridge* mDomBridge;
           ImageBridge* mImageBridge;
           PlatformBridge* mPlatformBridge;

    };
}



#endif //WEEX_UIKIT_UIENGINE_H
