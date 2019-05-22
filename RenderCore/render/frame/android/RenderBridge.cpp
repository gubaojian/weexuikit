#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <EGL/egl.h>
#include <render/public/RendererEngine.h>
#include <third_party/skia/include/core/SkBitmap.h>
#include <third_party/skia/include/core/SkImage.h>
#include <third_party/skia/include/codec/SkCodec.h>
#include <third_party/skia/src/core/SkMakeUnique.h>
#include <third_party/skia/src/core/SkColorTable.h>
#include <render/platform/common/log.h>
#include <render/core/parser/Screen.h>
#include <render/frame/android/RenderJava.h>
#include <render/frame/FramePipeline.h>
#include <render/frame/SkiaShareContext.h>
#include <third_party/skia/include/core/SkTypeface.h>
#include <render/frame/SkiaFontSelector.h>
#include <render/gesture/gesture/PointerEvent.h>
#include <render/frame/TaskRunners.h>
#include <render/core/node/NodeStyles.h>
#include <render/frame/UIEngine.h>
#include <render/wml/message_loop.h>
#include <render/wml/thread.h>
#include <render/platform/common/common.h>
#include <render/frame/android/string/LocalJStringUTF8.h>
#include "AndroidSkiaRender.h"
#include "render/frame/android/string/LocalCStringUTF8.h"


#define convert_long_to_frame_view(ptr)   ((weexuikit::FramePipeline*)((intptr_t)ptr))

struct SurfaceWindow{
    int64_t windowRender;
    EGLNativeWindowType nativeWindow;
};

static weexuikit::SkiaShareContext* skiaShareContext;


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    RenderJava::onLoad(vm);
    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    RenderJava::onUnload(vm);
}



extern "C" JNIEXPORT jstring JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeHitTestEvent(JNIEnv *env, jobject instance,
                                                      jlong mNativeFrame, jint type, jint x, jint y) {
    /**
    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(mNativeFrame);
    weexuikit::Node* node = renderFrameView->hitTest(type, x, y);
    if(node == nullptr){
        return nullptr;
    }
    jstring  ref = env->NewStringUTF(node->ref().c_str());
    return ref;
     */
    return nullptr;
}


extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionTouchEvent(JNIEnv *env,
                                                                                                         jobject instance,
                                                                                                         jstring pageId_,
                                                                                                         jint action, jint pointerId,
                                                                                                         jfloat x, jfloat y,jlong timeStamp) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::PointerEvent::PointerAction pointerAction = (weexuikit::PointerEvent::PointerAction)action;
    weexuikit::UIEngine::getInstance()->getPlatformBridge()->onPageTouchEvent(pageId.getChars(),
    pointerAction, pointerId, x, y, timeStamp);
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionDestroyPage(JNIEnv *env, jobject instance, jstring pageId_) {

    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->destroyPage(pageId.getChars());
}





extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionCreateBody(JNIEnv *env, jobject instance,
                                                                                                   jstring pageId_, jstring ref_,
                                                                 jlong styles_, jlong attrs_, jlong events_) {

    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    std::map<std::string,std::string>* style = (std::map<std::string,std::string>*)((intptr_t)styles_);
    std::map<std::string,std::string>* attrs = (std::map<std::string,std::string>*)((intptr_t)attrs_);
    std::set<std::string>* events = (std::set<std::string>*)((intptr_t)events_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->createBody(pageId.getChars(), ref.getChars(), weexuikit::Html::Tag::DIV, style, attrs, events);

}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionAddElement(JNIEnv *env,
                                                                       jobject instance, jstring pageId_,
                                                                       jstring ref_, jstring type_,
                                                                       jstring parentRef_,
                                                                       jint index, jlong styles_,
                                                                       jlong attrs_,
                                                                       jlong events_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    weexuikit::LocalCStringUTF8 type(env, type_);
    weexuikit::LocalCStringUTF8 parentRef(env, parentRef_);
    std::map<std::string,std::string>* style = (std::map<std::string,std::string>*)((intptr_t)styles_);
    std::map<std::string,std::string>* attrs = (std::map<std::string,std::string>*)((intptr_t)attrs_);
    std::set<std::string>* events = (std::set<std::string>*)((intptr_t)events_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->addElement(pageId.getChars(),
    ref.getChars(), type.getChars(), parentRef.getChars(), index, style, attrs, events);
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionUpdateAttrs(JNIEnv *env,
                                                                                                          jobject instance, jstring pageId_,
                                                                                                          jstring ref_, jlong attrs_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    std::map<std::string,std::string>* attrs = (std::map<std::string,std::string>*)((intptr_t)attrs_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->updateAttrs(pageId.getChars(), ref.getChars(), attrs);

}



extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionUpdateStyles(JNIEnv *env,
                                                                         jobject instance, jstring pageId_, jstring ref_, jlong styles_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    std::map<std::string,std::string>* styles = (std::map<std::string,std::string>*)((intptr_t)styles_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->updateStyles(pageId.getChars(), ref.getChars(), styles);
}



extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionAddEvent(JNIEnv *env, jobject instance,
                                                                                                       jstring pageId_, jstring ref_, jstring event_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    weexuikit::LocalCStringUTF8 event(env, event_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->addEvent(pageId.getChars(), ref.getChars(), event.getChars());
}


extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionRemoveEvent(JNIEnv *env,
                                                                                                          jobject instance,
                                                                                                          jstring pageId_,
                                                                                                          jstring ref_,
                                                                                                          jstring event_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    weexuikit::LocalCStringUTF8 event(env, event_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->removeEvent(pageId.getChars(), ref.getChars(), event.getChars());

}


extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionMoveElement(JNIEnv *env,
                                                                                                          jobject instance,
                                                                                                          jstring pageId_,
                                                                                                          jstring ref_,
                                                                                                          jstring parentRef_, jint index) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    weexuikit::LocalCStringUTF8 parentRef(env, parentRef_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->moveElement(pageId.getChars(), ref.getChars(), parentRef.getChars(), index);

}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionRemoveElement(JNIEnv *env,
                                                                                                            jobject instance,
                                                                                                            jstring pageId_,
                                                                                                            jstring ref_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->removeElement(pageId.getChars(), ref.getChars());

}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeRefreshFont(JNIEnv *env, jobject instance,
                                                                                                    jstring pageId_,
                                                                                                    jstring fontFamilyName_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 fontFamilyName(env, fontFamilyName_);
    weexuikit::UIEngine::getInstance()->getDomBridge()->refreshFont(pageId.getChars(), fontFamilyName.getChars());
}

extern "C" JNIEXPORT jlong JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeNewMap(JNIEnv *env, jobject instance) {
    std::map<std::string,std::string>* map = new std::map<std::string,std::string>();
    return ((jlong)((intptr_t)map));
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeMapPut(JNIEnv *env, jobject instance,
                                                             jlong ptr, jstring key_,
                                                             jstring value_) {
    const char *key = env->GetStringUTFChars(key_, 0);
    const char *value = env->GetStringUTFChars(value_, 0);
    std::map<std::string,std::string>* map = (std::map<std::string,std::string>*)((intptr_t)ptr);
    map->insert({key, value});
    env->ReleaseStringUTFChars(key_, key);
    env->ReleaseStringUTFChars(value_, value);
}

extern "C" JNIEXPORT jlong JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeNewSet(JNIEnv *env, jobject instance) {
    std::set<std::string>* set  = new std::set<std::string>();
    return ((jlong)((intptr_t)set));
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeSetAdd(JNIEnv *env, jobject instance,
                                                             jlong ptr, jstring value_) {
    const char *value = env->GetStringUTFChars(value_, 0);
    std::set<std::string>* set = (std::set<std::string>*)((intptr_t)ptr);
    std::string valueStr(value);
    set->insert(valueStr);
    env->ReleaseStringUTFChars(value_, value);
}

extern "C" JNIEXPORT bool JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeInitSDK(JNIEnv *env, jobject instance,
                                                              jint screenWidth, jint screenHeight,
                                                              jfloat density) {
    std::map<std::string, std::string> params;
    weexuikit::UIEngine::getInstance()->init(params, screenWidth, screenHeight, density);
    return true;
}


extern "C" JNIEXPORT jint JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeRenderFrameWidth(JNIEnv *env, jobject instance, jlong ptr) {
    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    return renderFrameView->getRenderFrameWidth();
}

extern "C" JNIEXPORT jint JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeRenderFrameHeight(JNIEnv *env, jobject instance, jlong ptr) {

    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    return renderFrameView->getRenderFrameHeight();
}




extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeLayoutFrame(JNIEnv *env, jobject instance,
                                                                                                    jstring pageId_) {
   // LOGE("Weex", "Weex nativeLayoutIfNeed %lld", ptr);
    //weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    //renderFrameView->flushLayout();
    //LOGE("Weex", "Weex nativeLayoutend %lld", ptr);
}



extern "C" JNIEXPORT jint JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeGetBlockLayout(JNIEnv *env, jobject instance,
                                                                jlong ptr, jstring ref_,
                                                                jint edge) {
    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    const char *ref = env->GetStringUTFChars(ref_, 0);
    std::string refStr = ref;
    int result = renderFrameView->getRenderFrame()->getBlockLayout(refStr, edge);
    env->ReleaseStringUTFChars(ref_, ref);
    return result;
}


extern "C" JNIEXPORT jbyteArray JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeGetNodeAttr(JNIEnv *env, jobject instance,
                                                              jlong ptr, jstring ref_,
                                                              jstring key_) {
    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    const char *ref = env->GetStringUTFChars(ref_, 0);
    const char *key = env->GetStringUTFChars(key_, 0);

    std::string refStr = ref;
    std::string keyStr = key;
    std::string  result = renderFrameView->getRenderFrame()->getAttrs(refStr, keyStr);
    env->ReleaseStringUTFChars(ref_, ref);
    env->ReleaseStringUTFChars(key_, key);
    if(result.length() > 0){
        jbyte * bts =  (jbyte*) result.c_str();
        jbyteArray byteArray = env->NewByteArray(result.length());
        env->SetByteArrayRegion(byteArray, 0, result.length(), bts);
        return byteArray;
    }
    return nullptr;
}

extern "C" JNIEXPORT jstring JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeGetNodeType(JNIEnv *env, jobject instance,
                                                                  jlong ptr, jstring ref_) {
    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    const char *ref = env->GetStringUTFChars(ref_, 0);
    std::string refStr = ref;
    weexuikit::Node* node  = renderFrameView->getRenderFrame()->getNode(refStr);
    env->ReleaseStringUTFChars(ref_, ref);
    if(node != nullptr && node->type().length() > 0){
        return env->NewStringUTF(node->type().c_str());
    }
    return nullptr;
}


extern "C" JNIEXPORT jboolean JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeNodeContainsEvent(JNIEnv *env,
                                                                        jobject instance, jlong ptr,
                                                                        jstring ref_,
                                                                        jstring event_) {
    weexuikit::FramePipeline* renderFrameView = convert_long_to_frame_view(ptr);
    const char *ref = env->GetStringUTFChars(ref_, 0);
    const char *event = env->GetStringUTFChars(event_, 0);
    std::string refStr = ref;
    std::string eventStr = event;
    weexuikit::Node* node  = renderFrameView->getRenderFrame()->getNode(refStr);
    env->ReleaseStringUTFChars(ref_, ref);
    env->ReleaseStringUTFChars(event_, event);
    if(node == nullptr){
        return false;
    }
    return node->events()->find(eventStr) != node->events()->end();
}


extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeAddFont(JNIEnv *env, jobject instance, jstring fontFamilyName_, jstring fontPath_) {
    if(fontFamilyName_ == nullptr || fontPath_ == nullptr){
        return;
    }
    const char *fontFamilyName = env->GetStringUTFChars(fontFamilyName_, 0);
    const char *fontPath = env->GetStringUTFChars(fontPath_, 0);
    std::string fontFamilyNameStr =  fontFamilyName;
    std::string fontPathStr = fontPath;

    PassRefPtr<blink::FontSelector> fontSelectorRef = blink::Platform::current()->fontSelector();
    weexuikit::SkiaFontSelector* fontSelector = (weexuikit::SkiaFontSelector *) fontSelectorRef.get();
    fontSelector->addFont(fontFamilyNameStr, fontPathStr);

    env->ReleaseStringUTFChars(fontFamilyName_, fontFamilyName);
    env->ReleaseStringUTFChars(fontPath_, fontPath);
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeHasFont(JNIEnv *env, jobject instance,
                                                              jstring fontFamilyName_,
                                                              jstring fontPath_) {
    const char *fontFamilyName = env->GetStringUTFChars(fontFamilyName_, 0);
    const char *fontPath = env->GetStringUTFChars(fontPath_, 0);

    std::string fontFamilyNameStr =  fontFamilyName;
    std::string fontPathStr = fontPath;
    PassRefPtr<blink::FontSelector> fontSelectorRef = blink::Platform::current()->fontSelector();
    weexuikit::SkiaFontSelector* fontSelector = (weexuikit::SkiaFontSelector *) fontSelectorRef.get();
    bool hasFont = fontSelector->hasFont(fontFamilyNameStr, fontPathStr);

    env->ReleaseStringUTFChars(fontFamilyName_, fontFamilyName);
    env->ReleaseStringUTFChars(fontPath_, fontPath);
    return hasFont;
}


extern "C" JNIEXPORT jlong JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeFrameRenderAttach(JNIEnv *env,
                                                                        jobject instance,
                                                                        jstring pageId_, jobject surface, jboolean isSurfaceView,jint width, jint height) {

    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    EGLNativeWindowType nativeWindowType = ANativeWindow_fromSurface(env, surface);
    SurfaceWindow* surfaceWindow = new SurfaceWindow();
    int64_t  windowRender = weexuikit::UIEngine::getInstance()->getPlatformBridge()->onWindowCreate(pageId.getChars(), nativeWindowType, isSurfaceView, width, height);
    surfaceWindow->nativeWindow = nativeWindowType;
    surfaceWindow->windowRender = windowRender;
    DEBUG_LOG("OpenGLSkiaRender","OpenGLSkiaRender::onWindowCreated %d %d ", width, height);
    return convert_ptr_to_long(surfaceWindow);
}



extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeFrameRenderSizeChanged(JNIEnv *env,
                                                                                                               jobject instance, jstring pageId_, jint width, jint height) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::UIEngine::getInstance()->getPlatformBridge()->onWindowSizeChange(pageId.getChars(), width, height);
    DEBUG_LOG("OpenGLSkiaRender","OpenGLSkiaRender::sizeChanged %d %d ", width, height);
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeFrameRenderDettach(JNIEnv *env,
                                                                                                           jobject instance,
                                                                                                           jlong nativeWindowPtr,
                                                                                                           jstring pageId_,
                                                                                                           jobject surface) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    SurfaceWindow* surfaceWindow = (SurfaceWindow*)((intptr_t)nativeWindowPtr);
    //FIXME For List Fast Scroll
    weexuikit::UIEngine::getInstance()->getPlatformBridge()->onWindowDestroy(pageId.getChars());
    ANativeWindow_release(surfaceWindow->nativeWindow);
    delete  surfaceWindow;
    surfaceWindow = nullptr;
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeFrameRenderOnVsync(JNIEnv *env,
                                                                                                           jobject instance, jstring pageId_, jlong frameTimeMs) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::UIEngine::getInstance()->getPlatformBridge()->onWindowVsync(pageId.getChars(),
                                                                            frameTimeMs);
}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeFrameRenderOnResume(JNIEnv *env,
                                                                          jobject instance,
                                                                          jstring pageId_) {
   weexuikit::LocalCStringUTF8 pageId(env, pageId_);
   weexuikit::UIEngine::getInstance()->getPlatformBridge()->onWindowResume(pageId.getChars());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_taobao_weex_render_bridge_RenderBridge_nativeFrameRenderOnPause(JNIEnv *env,
                                                                         jobject instance,
                                                                         jstring pageId_) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::UIEngine::getInstance()->getPlatformBridge()->onWindowPause(pageId.getChars());
}


extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeActionOnLoadImage(JNIEnv *env,
                                                                        jobject instance,
                                                                        jobject jbitmap,
                                                                        jstring pageId_,
                                                                        jstring ref_, jstring url_,
                                                                        jint width, jint height,
                                                                        jlong callbackId) {
    weexuikit::LocalCStringUTF8 pageId(env, pageId_);
    weexuikit::LocalCStringUTF8 ref(env, ref_);
    weexuikit::LocalCStringUTF8 url(env, url_);
    SkBitmap skBitmap;
    RenderJava::convertJBitmapToSkBitmap(env, jbitmap, skBitmap);
    weexuikit::RequestImage requestImage;
    requestImage.pageId = pageId.getChars();
    requestImage.ref = ref.getChars();
    requestImage.url = url.getChars();
    requestImage.width = width;
    requestImage.height = height;
    requestImage.callbackId = callbackId;
    weexuikit::UIEngine::getInstance()->getImageBridge()->onGetImage(requestImage, skBitmap);

}

extern "C" JNIEXPORT void JNICALL Java_com_taobao_weex_render_bridge_RenderBridge_nativeOnLowMemory(JNIEnv *env, jobject instance) {

    weexuikit::UIEngine::getInstance()->getImageBridge()->onLowMemory();

}