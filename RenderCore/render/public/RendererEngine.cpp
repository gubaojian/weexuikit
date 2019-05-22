//
// Created by furture on 2018/4/17.
//
#include "RendererEngine.h"
#include <render/wtf/WTF.h>
#include <render/wtf/MainThread.h>
#include <render/wtf/text/TextEncoding.h>
#include "render/core/CoreInitializer.h"
#include "render/wtf/StdLibExtras.h"
#include <ICUCompatible.h>
#ifdef __ANDROID__
  #include <render/frame/android/PlatformAndroid.h>
#endif
#include <render/frame/SkiaFontSelector.h>
#ifdef __APPLE__
#include <render/frame/ios/Platform_ios.h>
#endif

namespace blink{

    static Platform* platformImpl = nullptr;

    void initEngine(){
        if(platformImpl != nullptr){
            return;
        }
#ifdef __ANDROID__
        initICU();
#endif
        WTF::initialize();
        WTF::initializeMainThread();

        DEFINE_STATIC_LOCAL(CoreInitializer, initializer, ());
        initializer.init();
        WTF::UTF8Encoding();

#ifdef __ANDROID__
        platformImpl = new PlatformAndroid();
        platformImpl->setFontSelector(weexuikit::SkiaFontSelector::create());
        platformImpl->initialize(platformImpl);
#endif

#ifdef  __APPLE__
        platformImpl = new PlatformIOS();
        platformImpl->setFontSelector(weexuikit::SkiaFontSelector::create());
        platformImpl->initialize(platformImpl);
#endif




    }

// Once shutdown, the Platform passed to initialize will no longer
// be accessed. No other WebKit objects should be in use when this function is
// called. Any background threads created by WebKit are promised to be
// terminated by the time this function returns.
    void shutdownEngine(){
        CoreInitializer::shutdown();
        WTF::shutdown();
        Platform::shutdown();

        if(platformImpl != nullptr){
           delete platformImpl;
           platformImpl = nullptr;
        }
    }
}
