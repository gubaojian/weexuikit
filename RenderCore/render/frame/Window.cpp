//
// Created by furture on 2018/12/30.
//

#include <render/platform/common/common.h>
#include <render/wml/synchronization/waitable_event.h>
#include "Window.h"
#include "SkiaRender.h"
#include "UIEngine.h"
#include "TextureManager.h"

namespace weexuikit{

    /**
     * Priority Is Set In WML::Thread By Name
     * */
    #define GPU_THREAD_NAME  "GpuThread"

    Window::Window(const std::string& pageId) {
        mPageId = pageId;
        mSkiaRender = nullptr;
        mPage = nullptr;
        mGpuThread.reset();
        isValid = false;
    }

    Window::~Window() {
        isValid = false;
        onWindowDestroy();
    }

    void Window::onWindowCreate(EGLNativeWindowType nativeWindow, bool isSurfaceFlinger, int width, int height) {
        if(mSkiaRender != nullptr){
            LOGE("Window", "Window has Been Created, please call destroy Window First");
            return;
        }
        mWindowHeight = height;
        mWindowWidth = width;
        mPaintingFlag = false;
        mGpuThread = std::make_shared<wml::Thread>(GPU_THREAD_NAME);
        mGpuTaskRunner = mGpuThread->GetTaskRunner();
        Window* weakThis = this;
        isValid = true;
        mGpuTaskRunner->PostTask([nativeWindow, isSurfaceFlinger, width, height, weakThis]{
            if(weakThis->isValid){
                weakThis->mSkiaRender = SkiaRender::createRender(nativeWindow, isSurfaceFlinger, width, height);
                if(weakThis->mPage == nullptr){
                    weakThis->attachPage();
                }
            }
        });
    }

    void Window::onWindowSizeChange(int width, int height) {
        if(!isValid){
            return;
        }
        mWindowHeight = height;
        mWindowWidth = width;
        Window* weakThis = this;
        mGpuTaskRunner->PostTask([width, height, weakThis]{
            if(weakThis->isValid){// use fast fail flag, when scroll quick reject waste update
                SkiaRender* skiaRender = weakThis->mSkiaRender;
                if(skiaRender == nullptr){
                    return;
                }
                if(skiaRender->getWindowHeight() == height
                   && skiaRender->getWindowWidth() == width){
                    return;
                }
                skiaRender->makeCurrent();
                skiaRender->sizeChanged(width, height);
                if(!weakThis->isValid){
                    return;
                }

                skiaRender->drawFrame(true, []{});
                if(!weakThis->isValid){
                    return;
                }

                skiaRender->drawFrame(true, []{});
                if(!weakThis->isValid){
                    return;
                }
            }
        });
    }



    /**
     * FIXME ENABLE ASYNC Destroy
     * */
    void Window::onWindowDestroy() {
        if(mSkiaRender == nullptr){
            return;
        }
        if(mPage != nullptr){
            mPage->getFramePipeline()->setWindow(nullptr);
            mPage = nullptr;
        }
        Window* weakThis = this;
        isValid = false;
        wml::AutoResetWaitableEvent latch;
        mGpuTaskRunner->PostTask([&latch,  weakThis]{
            SkiaRender* skiaRender = weakThis->mSkiaRender;
            skiaRender->destroy();
            delete skiaRender;
            weakThis->mSkiaRender = nullptr;
            latch.Signal();
        });
        latch.WaitWithTimeout(wml::TimeDelta::FromMicroseconds(16*8));
        mGpuThread.reset();
    }

    void Window::attachPage() {
        if(mPage != nullptr){
            return;
        }
        PageManager* pageManager = UIEngine::getInstance()->getPageManager();
        Window* weakThis = this;
        pageManager->dispatchCreatePageAction(mPageId,[weakThis](Page* page){
            if(weakThis->isValid){
                page->getFramePipeline()->setWindow(weakThis);
                page->getFramePipeline()->markDiry();
                page->getFrameController()->requestFrame();
                weakThis->mPage = page;
            }
        });
    }

    void Window::requestNextFrame() {
        mPaintingFlag = false;
        if(mPage != nullptr){
            mPage->getFrameController()->requestFrame();
        }
    }

    void Window::onWindowInvalidate(bool forceDirty) {
        Window* weakThis = this;
        forceDirty |=mDirtyFlag;
        mPaintingFlag = true;
        mGpuTaskRunner->PostTask([forceDirty, weakThis]{
            if(!weakThis->isValid){
                return;
            }
            weakThis->mDirtyFlag = false;
            SkiaRender* skiaRender = weakThis->mSkiaRender;
            skiaRender->drawFrame(forceDirty, [weakThis]{
                if(!weakThis->isValid){
                    return;
                }
                weakThis->requestNextFrame();
            });
        });
    }

    void Window::dirtyWindow(bool dirty) {
        mDirtyFlag = dirty;
    }

    int Window::getWindowHeight() {
        return mWindowHeight;
    }

    int Window::getWindowWidth() {
        return mWindowWidth;
    }

    void Window::onVsync(int64_t frameTimeNanos) {
        if(mPaintingFlag){
            return;
        }
        onWindowInvalidate(mDirtyFlag);
    }

    void Window::setWindowPaintFrame(PaintFrame& paintFrame) {
        if(mSkiaRender != nullptr){
            mSkiaRender->setPaintFrame(paintFrame);
        }
        mDirtyFlag = true;
    }

    void Window::dettachPage() {
        if(mPage != nullptr){
            mPage = nullptr;
        }
    }

    bool Window::isWindowValid() {
        return isValid && mSkiaRender != nullptr;
    }

    void Window::onWindowPause() {
        mDirtyFlag = true;
    }

    void Window::onWindowResume() {
        mDirtyFlag = true;
    }
}