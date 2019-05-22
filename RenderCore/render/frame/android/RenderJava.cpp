//
// Created by furture on 2018/7/24.
//
#include <render/frame/android/string/LocalJStringUTF8.h>
#include <android/bitmap.h>
#include <third_party/skia/include/core/SkImageInfo.h>
#include <third_party/skia/include/core/SkBitmap.h>
#include <third_party/skia/include/gpu/gl/GrGLTypes.h>
#include <third_party/skia/include/gpu/GrBackendSurface.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <render/frame/SkiaShareContext.h>
#include <render/platform/common/log.h>
#include "RenderJava.h"

namespace  RenderJava{

    static pthread_key_t jni_env_key;
    static JavaVM*  jvm;
    static jclass  renderBridgeClass;
    static jmethodID getImageMethodID;
    static JavaContext* jniCtx;


    double now_ms(void) {
        struct timespec res;
        clock_gettime(CLOCK_REALTIME, &res);
        return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
    }

    void clean_jni_env(void* ptr){
        JNIEnv* env = (JNIEnv*)ptr;
        if(env && env != NULL){
            jvm->DetachCurrentThread();
        }
    }

    void deleteGlobalRefClass(JNIEnv* env, jclass object){
        env->DeleteGlobalRef(object);
    }


    jclass findGlobalRefClass(JNIEnv* env, const char* className){
            jclass cls = env->FindClass(className);
            jclass global_ref_class = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);
            return global_ref_class;
   }

    JNIEnv*  get_java_jni_env(){
        JNIEnv* env;
        env = (JNIEnv *) pthread_getspecific(jni_env_key);
        if(env != NULL){
            return env;
        }
        JavaVMAttachArgs args = {JNI_VERSION_1_4, 0, 0};
        jvm->AttachCurrentThread(&env, &args);
        if(env == NULL){
            return NULL;
        }
        pthread_setspecific(jni_env_key, env);
        return env;
    }

    JavaContext* getJavaCtx(){
        return jniCtx;
    }

    void onLoad(JavaVM *vm) {
        RenderJava::jvm = vm;
        pthread_key_create (&jni_env_key, clean_jni_env);
        JNIEnv*  env = RenderJava::get_java_jni_env();
        RenderJava::renderBridgeClass = RenderJava::findGlobalRefClass(env, "com/taobao/weex/render/bridge/RenderBridge");
        RenderJava::getImageMethodID = env->GetStaticMethodID(RenderJava::renderBridgeClass, "getImage", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIJ)V");
        jniCtx = new JavaContext();
        jniCtx->jvm = jvm;
        jniCtx->renderBridgeClass = renderBridgeClass;
        jniCtx->getImageMethodID = getImageMethodID;
        jniCtx->isImagePremultipliedMethodId = env->GetStaticMethodID(RenderJava::renderBridgeClass, "isImagePremultiplied", "(Landroid/graphics/Bitmap;)Z");
        jniCtx->createPlatformViewMethodID = env->GetStaticMethodID(RenderJava::renderBridgeClass, "createPlatformView", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;Ljava/util/Map;Ljava/util/List;)V");
        jniCtx->paintPlatformViewMethodID = env->GetStaticMethodID(RenderJava::renderBridgeClass, "paintPlatformView", "(Ljava/lang/String;Ljava/lang/String;IIIIZ)V");
        jniCtx->createExternalTextureMethodID = env->GetStaticMethodID(RenderJava::renderBridgeClass, "createExternalTexturePresentation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;Ljava/util/Map;Ljava/util/List;)V");
        jniCtx->updateExternalTexturePresentationMethodID = env->GetStaticMethodID(RenderJava::renderBridgeClass, "updateExternalTexturePresentation", "(Ljava/lang/String;Ljava/lang/String;)I");
        jniCtx->deleteExternalTexturePresentationMethodID = env->GetStaticMethodID(RenderJava::renderBridgeClass, "deleteExternalTexturePresentation", "(Ljava/lang/String;Ljava/lang/String;)V");
        jniCtx->testTextureMethodId = env->GetStaticMethodID(RenderJava::renderBridgeClass, "testTexture", "()I");
    }

    void onUnload(JavaVM* vm){
        JNIEnv*  env = RenderJava::get_java_jni_env();
        if(renderBridgeClass != nullptr){
            deleteGlobalRefClass(env, renderBridgeClass);
            renderBridgeClass = nullptr;
        }
        if(jniCtx != nullptr){
            delete  jniCtx;
            jniCtx = nullptr;
        }
    }

    jobject toJavaMap(const std::map<std::string, std::string>& attrs){
        JNIEnv* env = get_java_jni_env();
        static jclass jHashMapClass= (jclass)(env->NewGlobalRef(env->FindClass("java/util/HashMap")));
        static jmethodID jHashMapInit = env->GetMethodID(jHashMapClass, "<init>", "(I)V");
        static jmethodID jHashMapPutMethod = env->GetMethodID(jHashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");


        jobject jMapObj = env->NewObject(jHashMapClass, jHashMapInit, attrs.size());
        for (auto it : attrs)
        {

            jstring  key = env->NewStringUTF(it.first.c_str());
            jstring  value = env->NewStringUTF(it.second.c_str());
            env->CallObjectMethod(jMapObj, jHashMapPutMethod, key, value);
            env->DeleteLocalRef(key);
            env->DeleteLocalRef(value);
        }
        return jMapObj;
    }

    jobject toJavaList(const std::set<std::string>& events){
        JNIEnv* env = get_java_jni_env();
        static jclass jArrayListClass = (jclass)(env->NewGlobalRef(env->FindClass("java/util/ArrayList")));
        static jmethodID jArrayListConstructor = env->GetMethodID(jArrayListClass, "<init>", "(I)V");
        static jmethodID jArrayListAddMethodId = env->GetMethodID(jArrayListClass, "add", "(Ljava/lang/Object;)Z");;
        jobject result = env->NewObject(jArrayListClass, jArrayListConstructor, events.size());
        for (std::string event : events) {
            jstring eventJStr = env->NewStringUTF(event.c_str());
            env->CallBooleanMethod(result, jArrayListAddMethodId, eventJStr);
            env->DeleteLocalRef(eventJStr);
        }
        return result;

    }

    void getImageBitmap(JNIEnv* env, const std::string& pageId_, const std::string& ref_,
                           const std::string& url_, int width,
                           const int height, const int64_t  callbackId){
        if(url_.length() <= 0){
            return;
        }
        weexuikit::LocalJStringUTF8 pageId(env, pageId_);
        weexuikit::LocalJStringUTF8 ref(env, ref_);
        weexuikit::LocalJStringUTF8 url(env, url_);
        env->CallStaticVoidMethod(RenderJava::getJavaCtx()->renderBridgeClass, RenderJava::getJavaCtx()->getImageMethodID,
                pageId.getJStr(), ref.getJStr(), url.getJStr(), width, height, callbackId);
    }




    bool  isImageBitmapPremultiplied(JNIEnv* env, jobject bitmap){
        if(bitmap == nullptr){
            return true;
        }
        jboolean  result = env->CallStaticBooleanMethod(RenderJava::getJavaCtx()->renderBridgeClass, RenderJava::getJavaCtx()->isImagePremultipliedMethodId, bitmap);
        return result;
    }


    static void releaseJBitmapPixels(void* pixels, void* context){
        jobject  jbitmap = (jobject) context;
        JNIEnv* env = RenderJava::get_java_jni_env();
        if(pixels){
            AndroidBitmap_unlockPixels(env, jbitmap);
        }
        env->DeleteGlobalRef(jbitmap);
    }

    void convertJBitmapToSkBitmap(JNIEnv* env, jobject jbitmap, SkBitmap &bitmap){
        if(jbitmap == nullptr){
            return;
        }
        AndroidBitmapInfo  info;
        void*              pixels;
        int bitmapInfoResult = AndroidBitmap_getInfo(env, jbitmap, &info);
        if(bitmapInfoResult != ANDROID_BITMAP_RESULT_SUCCESS){
            return;
        }
        int pixelsResult = AndroidBitmap_lockPixels(env, jbitmap, &pixels);
        if(pixelsResult != ANDROID_BITMAP_RESULT_SUCCESS || pixels == nullptr){
            return;
        }
        SkColorType  colorType = kN32_SkColorType;
        switch (info.format) {
            case ANDROID_BITMAP_FORMAT_RGBA_8888:
                colorType = kN32_SkColorType;
                break;
            case ANDROID_BITMAP_FORMAT_RGB_565:
                colorType = kRGB_565_SkColorType;
                break;
            case ANDROID_BITMAP_FORMAT_RGBA_4444:
                colorType = kARGB_4444_SkColorType;
                break;
            case ANDROID_BITMAP_FORMAT_A_8:
                colorType = kAlpha_8_SkColorType;
                break;
            default:
                colorType = kUnknown_SkColorType;
                break;
        }
        if(kUnknown_SkColorType == colorType){
            AndroidBitmap_unlockPixels(env, jbitmap);
            return;
        }

        SkAlphaType alphaType = kPremul_SkAlphaType;
        if(!RenderJava::isImageBitmapPremultiplied(env, jbitmap)){
            alphaType = kUnpremul_SkAlphaType;
        }
        SkImageInfo skImageInfo = SkImageInfo::Make(info.width, info.height, colorType, alphaType);
        bitmap.installPixels(skImageInfo, pixels, info.stride, &releaseJBitmapPixels, env->NewGlobalRef(jbitmap));
    }


    void createPlatformView(const std::string &pageId_, const std::string &ref_, const std::string &type_,
                            const std::map<std::string, std::string>& attrs_,
                            const std::map<std::string, std::string>& style_,
                            const std::set<std::string>& events_) {
        JNIEnv* env = get_java_jni_env();
        weexuikit::LocalJStringUTF8 pageId(env, pageId_);
        weexuikit::LocalJStringUTF8 ref(env, ref_);
        weexuikit::LocalJStringUTF8 type(env, type_);
        jobject  attrMap = toJavaMap(attrs_);
        jobject  styleMap = toJavaMap(style_);
        jobject  eventList = toJavaList(events_);
        env->CallStaticVoidMethod(RenderJava::getJavaCtx()->renderBridgeClass, RenderJava::getJavaCtx()->createPlatformViewMethodID,
                                  pageId.getJStr(), ref.getJStr(),  type.getJStr(), attrMap, styleMap, eventList);
        if(attrMap){
            env->DeleteLocalRef(attrMap);
        }
        if(styleMap){
            env->DeleteLocalRef(styleMap);
        }
        if(eventList){
            env->DeleteLocalRef(eventList);
        }
    }

    void paintPlatformView(std::string &pageId_, std::string &ref_, int x, int y, int width,
                           int height,  bool attached){
        JNIEnv* env = get_java_jni_env();
        weexuikit::LocalJStringUTF8 pageId(env, pageId_);
        weexuikit::LocalJStringUTF8 ref(env, ref_);
        env->CallStaticVoidMethod(RenderJava::getJavaCtx()->renderBridgeClass, RenderJava::getJavaCtx()->paintPlatformViewMethodID,
                                  pageId.getJStr(), ref.getJStr(), x, y, width, height, attached);
    }

    void createExternalTexture(const std::string &pageId_, const std::string &ref_,const std::string &type_,
                               const std::map<std::string, std::string> &attr_,
                               const std::map<std::string, std::string> &style_,
                               const std::set<std::string> &events_){
        JNIEnv* env = get_java_jni_env();
        weexuikit::LocalJStringUTF8 pageId(env, pageId_);
        weexuikit::LocalJStringUTF8 ref(env, ref_);
        weexuikit::LocalJStringUTF8 type(env, type_);
        jobject  attrMap = toJavaMap(attr_);
        jobject  styleMap = toJavaMap(style_);
        jobject  eventList = toJavaList(events_);
        env->CallStaticVoidMethod(RenderJava::getJavaCtx()->renderBridgeClass, RenderJava::getJavaCtx()->createExternalTextureMethodID,
                                  pageId.getJStr(), ref.getJStr(),  type.getJStr(), attrMap, styleMap, eventList);
        if(attrMap){
            env->DeleteLocalRef(attrMap);
        }
        if(styleMap){
            env->DeleteLocalRef(styleMap);
        }
        if(eventList){
            env->DeleteLocalRef(eventList);
        }
    }

    sk_sp<SkImage> textureTest(const std::string &pageId_, const std::string &ref_,
                               GrContext* context){
        weexuikit::SkiaShareContext::getInstance()->getElgManager()->makeCurrent();

        JNIEnv* env = get_java_jni_env();

        weexuikit::LocalJStringUTF8 pageId(env, pageId_);
        weexuikit::LocalJStringUTF8 ref(env, ref_);

        int textureId = env->CallStaticIntMethod(RenderJava::getJavaCtx()->renderBridgeClass,
        RenderJava::getJavaCtx()->testTextureMethodId);

        LOGE("Weex", "Weex Weex RenderTexture::paintReplaced return %d",
            textureId);

        GrGLTextureInfo textureInfo;
        textureInfo.fTarget = GL_TEXTURE_EXTERNAL_OES;
        textureInfo.fID = textureId;
        textureInfo.fFormat = GL_RGBA8_OES;

        GrBackendTexture backendTexture(1, 1, GrMipMapped::kNo, textureInfo);
        sk_sp<SkImage> image = SkImage::MakeFromTexture(context, backendTexture, kTopLeft_GrSurfaceOrigin,
                kRGBA_8888_SkColorType, kPremul_SkAlphaType, nullptr);


        LOGE("Weex", "Weex Weex RenderTexture::paintReplaced %d",
             textureInfo.fID);

        return image;
    }


}


