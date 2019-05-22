//
// Created by furture on 2019/2/3.
//

#include <pthread.h>
#include "JavaEnv.h"


namespace {
    static JavaVM *g_jvm = nullptr;
    static pthread_key_t g_jni_env_pthread_key;
}


namespace WeexCore {

    namespace JavaEnv {

  

        void cleanCurrentThreadEnv(void *ptr){
            JNIEnv* env = (JNIEnv*)ptr;
            if(env && env != NULL){
               (g_jvm)->DetachCurrentThread();
            }
        }

        JNIEnv*  getCurrentJavaEnv(){
            JNIEnv* env;
            env = (JNIEnv*)pthread_getspecific(g_jni_env_pthread_key);
            if(env != NULL){
                return env;
            }
            JavaVMAttachArgs args = {JNI_VERSION_1_4, 0, 0};
            (g_jvm)->AttachCurrentThread(&env, &args);

            jint ret = g_jvm->AttachCurrentThread(&env, &args);
            if(ret != JNI_OK) {
                return NULL;
            }
            pthread_setspecific(g_jni_env_pthread_key, env);
            return env;
        }
        
        
        void InitVM(JavaVM *vm) {
            g_jvm = vm;
            pthread_key_create(&g_jni_env_pthread_key, cleanCurrentThreadEnv);
        }
        
        JavaVM* getJVM(){
            return g_jvm;
        }



    }
}
