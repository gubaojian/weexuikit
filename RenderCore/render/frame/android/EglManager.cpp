//
// Created by furture on 2018/12/25.
//

#include <render/platform/common/log.h>
#include "EglManager.h"
#include <GLES2/gl2.h>


namespace weexuikit {


    EglManager::EglManager() {
        mEglSureface = EGL_NO_SURFACE;
        mEglContext = EGL_NO_CONTEXT;
        mEglDisplay = EGL_NO_DISPLAY;
        mSurfaceConfig = NULL;
        mEglSwapFailed = false;
        mHasMakeCurrent = false;
    }

    EglManager::~EglManager() {
        destory();
    }


    void EglManager::eglInitContext(bool window, EGLContext share_context){
        mEglDisplay = EGL_NO_DISPLAY;
        mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        EGLint eglMajVers, eglMinVers;
        if(!eglInitialize(mEglDisplay, &eglMajVers, &eglMinVers)){
            LOGE("EglManager", "EglManager eglInitialize failed");
            return;
        }

        eglBindAPI(EGL_OPENGL_ES_API);
        EGLint  totalNumConfig;
        if (eglGetConfigs(mEglDisplay, NULL, 0, &totalNumConfig) == EGL_FALSE) {
            LOGE("EglManager", "EglManager eglGetConfigs failed");
            return;
        }


        if(window){
            const EGLint configAttribs[] = {
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                    EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_DEPTH_SIZE, 0,
                    EGL_STENCIL_SIZE, 0,
                    EGL_NONE
            };
            int numConfigs;
            if (!eglChooseConfig(mEglDisplay, configAttribs, &mSurfaceConfig, 1, &numConfigs)) {
                LOGE("OpenGLSkiaRender", "OpenGLSkiaRender eglChooseConfig failed");
                return;
            }
        } else{
            const EGLint configAttribs[] = {
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                    EGL_SURFACE_TYPE,    EGL_PBUFFER_BIT,
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_DEPTH_SIZE, 0,
                    EGL_STENCIL_SIZE, 0,
                    EGL_NONE
            };
            int numConfigs;
            if (!eglChooseConfig(mEglDisplay, configAttribs, &mSurfaceConfig, 1, &numConfigs)) {
                LOGE("OpenGLSkiaRender", "OpenGLSkiaRender eglChooseConfig failed");
                return;
            }
        }


        int kEGLContextAttribsForOpenGLES[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL_NONE
        };
        mEglContext = eglCreateContext(mEglDisplay, mSurfaceConfig, share_context, kEGLContextAttribsForOpenGLES);
    }

    void EglManager::createWindowSurface(EGLNativeWindowType nativeWindow) {
        const EGLint attribs[] = {EGL_NONE, EGL_NONE, EGL_NONE};
        mEglSureface = eglCreateWindowSurface(mEglDisplay, mSurfaceConfig, nativeWindow,  attribs);
        if (eglGetError() != EGL_SUCCESS) {
            LOGE("OpenGLSkiaRender", "OpenGLSkiaRender  eglCreateWindowSurface Failed %d",
                 eglGetError());
            return;
        }
        if (EGL_NO_SURFACE == mEglSureface && attribs) {
            // Try again without sRGB
            mEglSureface = eglCreateWindowSurface(mEglDisplay, mSurfaceConfig, nativeWindow, nullptr);
        }

    }


    void EglManager::createPBufferSurface() {
        if (mEglSureface  == EGL_NO_SURFACE) {
            EGLint attribs[] = {EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE};
            mEglSureface = eglCreatePbufferSurface(mEglDisplay, mSurfaceConfig, attribs);
        }
    }


    void EglManager::makeCurrent() {
        if(mHasMakeCurrent){
            return;
        }
        if (mEglDisplay != EGL_NO_DISPLAY && mEglContext != EGL_NO_CONTEXT && mEglSureface != EGL_NO_SURFACE) {
            eglMakeCurrent(mEglDisplay, mEglSureface, mEglSureface, mEglContext);
            mHasMakeCurrent = true;
        }
    }

    void EglManager::fence() {
        glFinish();
    }

    bool EglManager::swapBuffer() {
        if (mEglDisplay != EGL_NO_DISPLAY
            && mEglContext != EGL_NO_CONTEXT
            && mEglSureface != EGL_NO_SURFACE) {
            if(mEglSwapFailed){
               return false;
            }
            EGLBoolean result = eglSwapBuffers(mEglDisplay, mEglSureface);
            if(result != EGL_TRUE){
                mEglSwapFailed = true;
            }
            return result == EGL_TRUE;
        }
    }

    void EglManager::destory() {
        if(mEglDisplay != EGL_NO_DISPLAY){
            eglDestroySurface(mEglDisplay, mEglSureface);
            eglDestroyContext(mEglDisplay, mEglContext);
            eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            mEglSureface = EGL_NO_SURFACE;
            mEglContext = EGL_NO_CONTEXT;
            mEglDisplay = EGL_NO_DISPLAY;
        }
    }
}