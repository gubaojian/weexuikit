//
// Created by furture on 2018/7/31.
//

#ifndef WEEX_UIKIT_LOG_H
#define WEEX_UIKIT_LOG_H
#include <time.h>
#ifdef __ANDROID__
    #include <android/log.h>
#endif

#define RENDER_DEBUG true

#ifdef RENDER_DEBUG
     #ifdef __ANDROID__
        #include <android/log.h>
        #define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG, TAG,__VA_ARGS__)
        #define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR, TAG,__VA_ARGS__)
        #define DEBUG_LOG(TAG,...)  LOGE(TAG, __VA_ARGS__)
    #endif
#endif

#ifndef DEBUG_LOG
   #define DEBUG_LOG(TAG,...)
#endif
#ifndef LOGD
#define LOGD(TAG,...)
#endif
#ifndef LOGE
   #define LOGE(TAG,...)
#endif


static double now_ms(void) {
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
}

#endif //WEEX_UIKIT_CONFIG_H
