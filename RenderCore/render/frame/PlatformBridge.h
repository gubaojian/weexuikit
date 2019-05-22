//
// Created by furture on 2018/12/30.
//

#ifndef WEEX_UIKIT_PLATFORMBRIDGE_H
#define WEEX_UIKIT_PLATFORMBRIDGE_H


#include "PageManager.h"
#include "WindowManager.h"

namespace weexuikit {

    class PlatformBridge {

        public:
           PlatformBridge(PageManager* pageManager, WindowManager* windowManager);
           ~PlatformBridge();

        public:
           void onWindowVsync(const std::string &pageId, int64_t frameTimeNanos);

           void onWindowResume(const std::string& pageId);

           void onWindowPause(const std::string& pageId);

           int64_t onWindowCreate(const std::string& pageId, EGLNativeWindowType nativeWindow, bool  isSurfaceFlinger, int width, int height);

           void onWindowSizeChange(const std::string& pageId, int width, int height);

           void onWindowDestroy(const std::string& pageId);

       public:
           void  onPageTouchEvent(const std::string &pageId, weexuikit::PointerEvent::PointerAction action, int pointerId, float x, float y, int64_t timeStamp);


        private:
            WindowManager* mWindowManager;
            PageManager* mPageManager;
    };
}




#endif //WEEX_UIKIT_PLATFORMBRIDGE_H
