//
// Created by furture on 2018/12/25.
//

#ifndef WEEX_UIKIT_EGLMANAGER_H
#define WEEX_UIKIT_EGLMANAGER_H

#include <EGL/egl.h>

namespace weexuikit {

    class EglManager {

    public:
        EglManager();
        ~EglManager();

    public:
        void eglInitContext(bool window, EGLContext share_context);

        void createWindowSurface(EGLNativeWindowType nativeWindow);

        void createPBufferSurface();

        void makeCurrent();

        void fence();

        bool swapBuffer();

        void destory();

        EGLContext getEglContext(){
            return mEglContext;
        }

    private:
        EGLConfig mSurfaceConfig = NULL;
        EGLContext mEglContext;
        EGLSurface mEglSureface;
        EGLDisplay mEglDisplay;
        bool mHasMakeCurrent;
        bool mEglSwapFailed;
    };
}


#endif //WEEX_UIKIT_EGLMANAGER_H
