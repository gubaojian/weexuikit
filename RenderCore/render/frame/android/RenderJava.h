//
// Created by furture on 2018/7/24.
//

#ifndef WEEX_UIKIT_JNIUTILS_H
#define WEEX_UIKIT_JNIUTILS_H
#include <jni.h>
#include <string>
#include <pthread.h>
#include <android/log.h>
#include <map>
#include <third_party/skia/include/core/SkImage.h>
#include <set>

/**
 * call java from c++ use reflection
 * */
namespace  RenderJava {

    struct JavaContext{
        JavaVM*  jvm;
        jclass  renderBridgeClass;
        jmethodID getImageMethodID;
        jmethodID isImagePremultipliedMethodId;
        jmethodID createPlatformViewMethodID;
        jmethodID paintPlatformViewMethodID;
        jmethodID createExternalTextureMethodID;
        jmethodID updateExternalTexturePresentationMethodID;
        jmethodID deleteExternalTexturePresentationMethodID;
        jmethodID testTextureMethodId;
    };

    void deleteGlobalRefClass(JNIEnv* env, jclass object);
    jclass findGlobalRefClass(JNIEnv* env, const char* className);
    JNIEnv*  get_java_jni_env();
    JavaContext* getJavaCtx();
    double now_ms(void);

    void onLoad(JavaVM* vm);
    void onUnload(JavaVM* vm);


    jobject toJavaMap(const std::map<std::string, std::string>& attrs);

    jobject toJavaList(const std::set<std::string>& events);

    void convertJBitmapToSkBitmap(JNIEnv* env, jobject jbitmap, SkBitmap &bitmap);


    void getImageBitmap(JNIEnv* env, const std::string& pageId, const std::string& ref,
                           const std::string& url, const int width,
                           const int height, const int64_t callbackId);


    bool  isImageBitmapPremultiplied(JNIEnv* env, jobject bitmap);


    void createPlatformView(const std::string &pageId, const std::string &ref, const std::string &type,
                            const std::map<std::string, std::string>& attrs,
                            const std::map<std::string, std::string>& style,
                            const std::set<std::string>& events);

    void paintPlatformView(std::string &pageId, std::string &ref, int x, int y, int width, int height, bool attached);


    void createExternalTexture(const std::string &pageId, const std::string &ref,const std::string &type,
                          const std::map<std::string, std::string> &attr,
                          const std::map<std::string, std::string> &style,
                          const std::set<std::string> &events);



    sk_sp<SkImage> textureTest(const std::string &pageId, const std::string &ref,  GrContext* context);

};


#endif //WEEX_UIKIT_JNIUTILS_H
