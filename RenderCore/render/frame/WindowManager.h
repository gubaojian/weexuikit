//
// Created by furture on 2018/12/30.
//

#ifndef WEEX_UIKIT_WINDOWMANAGER_H
#define WEEX_UIKIT_WINDOWMANAGER_H
#include <string>
#include <map>
#include <EGL/eglplatform.h>
#include "Window.h"
#include "PageManager.h"

namespace weexuikit{

    class WindowManager {

        public:
            WindowManager();
            ~WindowManager();

        public:
            int64_t onWindowCreate(const std::string& pageId, EGLNativeWindowType nativeWindow,  bool  isSurfaceFlinger, int width, int height);

            void onWindowSizeChange(const std::string& pageId, int width, int height);

            void onWindowDestroy(const std::string& pageId);

            void onWindowInvalidate(const std::string& pageId, bool forceDirty);

            void onWindowDirty(const std::string& pageId, bool dirtyFlag);

            void onWindowVsync(const std::string &pageId, int64_t frameTimeNanos);

            void onWindowPause(const std::string &pageId);

            void onWindowResume(const std::string &pageId);


        private:
            std::map<std::string, Window*>* mWindows;
    };
}



#endif //WEEX_UIKIT_WINDOWMANAGER_H
