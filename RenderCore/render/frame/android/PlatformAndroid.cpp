//
// Created by furture on 2018/7/24.
//

#include "PlatformAndroid.h"
#include <render/wtf/WTF.h>
#include <render/wtf/MainThread.h>
#include <render/wtf/StdLibExtras.h>
#include <render/wtf/text/TextEncoding.h>
#include <third_party/skia/include/core/SkStream.h>
#include <third_party/skia/include/codec/SkCodec.h>
#include <third_party/skia/include/core/SkBitmap.h>
#include <third_party/skia/include/core/SkPixelRef.h>
#include <third_party/skia/include/core/SkImage.h>
#include <third_party/skia/src/core/SkMakeUnique.h>
#include <third_party/skia/src/core/SkColorTable.h>
#include <iostream>
#include <string>
#include <render/frame/FramePipeline.h>
#include <android/bitmap.h>
#include <render/frame/UIEngine.h>
#include "RenderJava.h"



namespace blink {


    std::string PlatformAndroid::defaultLocale() {
        return "zh-CN";
    }

    void PlatformAndroid::getImageBitmap(const weexuikit::RequestImage& requestImage) {
        JNIEnv* env = RenderJava::get_java_jni_env();
        RenderJava::getImageBitmap(env,  requestImage.pageId, requestImage.ref, requestImage.url, requestImage.width, requestImage.height, requestImage.callbackId);
    }


    void PlatformAndroid::paintPlatformView(blink::PaintPlatformView &viewInfo) {
        RenderJava::paintPlatformView(viewInfo.pageId, viewInfo.ref,
                                      viewInfo.paintRect.pixelSnappedX(),
                                      viewInfo.paintRect.pixelSnappedY(),
                                      viewInfo.paintRect.pixelSnappedWidth(),
                                      viewInfo.paintRect.pixelSnappedHeight(),
                                      viewInfo.attached);
    }


    void PlatformAndroid::createPlatformView(const std::string &pageId, const std::string &ref, const std::string &type,
                                             const std::map<std::string, std::string>& attrs,
                                             const std::map<std::string, std::string>& style,
                                             const std::set<std::string>& events) {
        RenderJava::createPlatformView(pageId, ref, type, attrs, style, events);
    }


    void PlatformAndroid::createExternalTexture(const std::string &pageId, const std::string &ref,const std::string &type,
                                                const std::map<std::string, std::string> &attr,
                                                const std::map<std::string, std::string> &style,
                                                const std::set<std::string> &events) {
        RenderJava::createExternalTexture(pageId, ref, type, attr, style, events);

    }


    void PlatformAndroid::paintExternalTexture(const std::string &pageId, const std::string &ref, SkCanvas *canvas, const LayoutRect& paintRect) {

        SkAutoCanvasRestore autoRestore(canvas, true);
        canvas->translate(paintRect.pixelSnappedX(), paintRect.pixelSnappedY());
        canvas->scale(paintRect.pixelSnappedWidth(), paintRect.pixelSnappedHeight());
        //if (!mTextureTransform.isIdentity()) {
           // SkMatrix transformAroundCenter(mTextureTransform);
           // transformAroundCenter.preTranslate(-0.5, -0.5);
            //transformAroundCenter.postScale(1, -1);
            //transformAroundCenter.postTranslate(0.5, 0.5);
            //canvas->concat(transformAroundCenter);
       // }
        //canvas->drawImage(mTextureImage, 0, 0);
    }


    void PlatformAndroid::deleteExternalTexture(const std::string &pageId,
                                                const std::string &ref) {

    }

}
