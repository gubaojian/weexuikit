//
// Created by furture on 2018/12/30.
//

#include <EGL/eglplatform.h>
#include <render/platform/common/common.h>
#include "PlatformBridge.h"
namespace weexuikit {


    PlatformBridge::PlatformBridge(weexuikit::PageManager *pageManager, WindowManager* windowManager) {
        mPageManager = pageManager;
        mWindowManager = windowManager;
    }

    PlatformBridge::~PlatformBridge() {
        mPageManager = nullptr;
        mWindowManager = nullptr;
    }

    void PlatformBridge::onWindowVsync(const std::string &pageId, int64_t frameTimeNanos) {
        if(mWindowManager == nullptr){
            return;
        }
        mWindowManager->onWindowVsync(pageId, frameTimeNanos);
    }


    void PlatformBridge::onWindowResume(const std::string &pageId) {
        if(mWindowManager == nullptr){
            return;
        }
        mWindowManager->onWindowResume(pageId);
    }


    void PlatformBridge::onWindowPause(const std::string &pageId) {
        if(mWindowManager == nullptr){
            return;
        }
        mWindowManager->onWindowPause(pageId);
    }




    int64_t PlatformBridge::onWindowCreate(const std::string &pageId, EGLNativeWindowType nativeWindow,
                                           bool  isSurfaceFlinger, int width, int height) {
        return mWindowManager->onWindowCreate(pageId, nativeWindow, isSurfaceFlinger, width, height);
    }


    void PlatformBridge::onWindowSizeChange(const std::string &pageId, int width, int height) {
        mWindowManager->onWindowSizeChange(pageId, width, height);
    }

    void PlatformBridge::onWindowDestroy(const std::string &pageId) {
        mWindowManager->onWindowDestroy(pageId);
    }



    void PlatformBridge::onPageTouchEvent(const std::string &pageId,
                                          weexuikit::PointerEvent::PointerAction action, int pointerId, float x, float y, int64_t timeStamp) {
        mPageManager->dispatchPageAction(pageId, [=](Page* page){
            page->getFrameView()->onTouch(action, pointerId, x, y, timeStamp);
        });
    }
}