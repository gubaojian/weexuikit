//
// Created by furture on 2018/12/29.
//

#include "UIEngine.h"
#include "TaskRunners.h"
#include "SkiaShareContext.h"
#include <mutex>
#include <render/public/RendererEngine.h>
#include <render/core/parser/Screen.h>
#include <render/wml/message_loop.h>

namespace weexuikit{


    namespace TaskRunners{
        wml::RefPtr<wml::TaskRunner> mImageTaskRunner;
        wml::RefPtr<wml::TaskRunner> mFrameTaskRunner;
        std::shared_ptr<wml::Thread> mImageTaskThread;
    }
    static UIEngine* engine = nullptr;


    UIEngine* UIEngine::getInstance() {
        static std::once_flag engine_once_flag;
        std::call_once(engine_once_flag, []{
            engine = new UIEngine();
        });
        return engine;
    }

    UIEngine::UIEngine() {
        mWindowManager = new WindowManager();
        mPageManager = new PageManager();
        mDomBridge = new DomBridge(mPageManager);
        mImageBridge = new ImageBridge(mPageManager);
        mPlatformBridge = new PlatformBridge(mPageManager, mWindowManager);
    }


    UIEngine::~UIEngine() {
        if(mDomBridge != nullptr){
            delete mDomBridge;
            mDomBridge = nullptr;
        }
        if(mPageManager != nullptr){
            delete  mPageManager;
            mPageManager = nullptr;
        }
        if(mWindowManager != nullptr){
            delete mWindowManager;
            mWindowManager = nullptr;
        }
    }

    void UIEngine::init(std::map<std::string, std::string> params, int screenWidth, int screenHeight, float density) {
        blink::initEngine();
        weexuikit::Screen::mDeviceWidth = screenWidth;
        weexuikit::Screen::mDeviceHeight = screenHeight;
        weexuikit::Screen::mDeviceDensity = density;
        wml::MessageLoop::EnsureInitializedForCurrentThread();
        weexuikit::TaskRunners::mFrameTaskRunner = wml::MessageLoop::GetCurrent().GetTaskRunner();
        std::shared_ptr<wml::Thread> imageThread = std::make_shared<wml::Thread>("ImageTextureThread");
        weexuikit::TaskRunners::mImageTaskRunner = imageThread->GetTaskRunner();
        weexuikit::TaskRunners::mImageTaskThread = imageThread;
        imageThread->GetTaskRunner()->PostTask([]{
            weexuikit::SkiaShareContext::getInstance();
        });
    }

    DomBridge* UIEngine::getDomBridge() {
        return mDomBridge;
    }

    WindowManager* UIEngine::getWindowManager() {
        return mWindowManager;
    }

    PageManager* UIEngine::getPageManager() {
        return mPageManager;
    }

    ImageBridge* UIEngine::getImageBridge() {
        return mImageBridge;
    }

    PlatformBridge* UIEngine::getPlatformBridge() {
        return mPlatformBridge;
    }

    void UIEngine::destroy() {
        if(engine != nullptr){
            delete  engine;
            TaskRunners::mImageTaskThread.reset();
            blink::shutdownEngine();
            engine = nullptr;
        }
    }

}