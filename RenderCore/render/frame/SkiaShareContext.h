//
// Created by furture on 2018/12/25.
//

#ifndef WEEX_UIKIT_SKIASHARECONTEXT_H
#define WEEX_UIKIT_SKIASHARECONTEXT_H


#include <third_party/skia/include/gpu/GrContext.h>
#include <third_party/skia/include/core/SkSurface.h>
#include <third_party/skia/include/core/SkColorFilter.h>
#include <third_party/skia/include/gpu/GrContextOptions.h>
#include <third_party/skia/include/gpu/gl/GrGLTypes.h>
#include "android/EglManager.h"

namespace weexuikit {

    class SkiaShareContext {

    public:
        static SkiaShareContext* getInstance();
        static void destroyInstance();

    private:
        SkiaShareContext();
        ~SkiaShareContext();

    public:
        sk_sp<GrContext> getGRContext();
        EglManager* getElgManager();

    private:
        EglManager* mEglManager;
        sk_sp<GrContext> mGrContext;

    };
}


#endif //WEEX_UIKIT_SKIASHARECONTEXT_H
