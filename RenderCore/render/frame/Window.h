//
// Created by furture on 2018/12/30.
//

#ifndef WEEX_UIKIT_WINDOW_H
#define WEEX_UIKIT_WINDOW_H

/**
 * which is used render skia records
 * */
#include <render/wml/thread.h>
#include <EGL/eglplatform.h>
#include "Page.h"
#include "SkiaRender.h"
#include "PaintFrame.h"

/**
 * every window has one gpu thread.
 * */
namespace weexuikit{

    class Window {

        public:
                Window(const std::string& pageId);
                ~Window();

            void onWindowPause();

            void onWindowResume();

       public:
            void onWindowCreate(EGLNativeWindowType nativeWindow, bool mIsSurfaceFlinger, int width, int height);

            void onWindowSizeChange(int width, int height);

            /**
            * FIXME ENABLE ASYNC Destroy, For List Fast Scroll
            * */
            void onWindowDestroy();

            void onWindowInvalidate(bool forceDirty);

            void dirtyWindow(bool dirty);

            void onVsync(int64_t frameTimeNanos);

        public:
            int getWindowWidth();
            int getWindowHeight();

        public:
            void setWindowPaintFrame(PaintFrame& paintFrame);
            void dettachPage();

        public:
             bool isWindowValid();

        private:
            void requestNextFrame();
            void attachPage();

    private:
            int mWindowWidth;
            int mWindowHeight;
            std::string mPageId;
            Page* mPage;
            weexuikit::SkiaRender* mSkiaRender;
            std::shared_ptr<wml::Thread> mGpuThread;
            wml::RefPtr<wml::TaskRunner> mGpuTaskRunner;
            volatile bool mDirtyFlag;
            volatile bool mPaintingFlag;
            volatile bool isValid;

    };
}



#endif //WEEX_UIKIT_WINDOW_H
