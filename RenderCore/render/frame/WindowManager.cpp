//
// Created by furture on 2018/12/30.
//

#include <render/platform/common/common.h>
#include "WindowManager.h"
#include "UIEngine.h"

namespace weexuikit{


    WindowManager::WindowManager() {
        mWindows = new std::map<std::string, Window*>();
    }

    WindowManager::~WindowManager() {
        if(mWindows != nullptr){
            ASSERT(mWindows->size() == 0);
            delete mWindows;
            mWindows == nullptr;
        }
    }

    int64_t WindowManager::onWindowCreate(const std::string &pageId,
                                          EGLNativeWindowType nativeWindow,
                                          bool  isSurfaceFlinger, int width, int height) {
        auto it = mWindows->find(pageId);
        Window* window = nullptr;
        if(it != mWindows->end()){
            window = it->second;
            window->onWindowDestroy();
            delete  window;
            mWindows->erase(pageId);
            window = nullptr;
        }

        window = new Window(pageId);
        window->onWindowCreate(nativeWindow, isSurfaceFlinger, width, height);
        mWindows->insert({pageId, window});
        return convert_ptr_to_long(window);
    }


    void WindowManager::onWindowSizeChange(const std::string &pageId, int width, int height) {
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->onWindowSizeChange(width, height);
    }

    void WindowManager::onWindowDestroy(const std::string &pageId) {
        LOGE("Window", "Window onWindowDestroy %s", pageId.c_str());
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->onWindowDestroy();
        mWindows->erase(pageId);
        delete window;
    }


    void WindowManager::onWindowInvalidate(const std::string &pageId, bool forceDirty) {
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->onWindowInvalidate(forceDirty);
    }


    void WindowManager::onWindowDirty(const std::string &pageId, bool dirtyFlag) {
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->dirtyWindow(dirtyFlag);
    }


    void WindowManager::onWindowVsync(const std::string &pageId, int64_t frameTimeNanos) {
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->onVsync(frameTimeNanos);
    }

    void WindowManager::onWindowPause(const std::string &pageId) {
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->onWindowPause();
    }

    void WindowManager::onWindowResume(const std::string &pageId) {
        auto it = mWindows->find(pageId);
        if(it == mWindows->end()){
            return;
        }
        Window* window = it->second;
        if(window == nullptr){
            return;
        }
        window->onWindowResume();
    }

}