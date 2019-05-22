//
// Created by furture on 2019/1/23.
//

#ifndef WEEX_PROJECT_TIMING_H
#define WEEX_PROJECT_TIMING_H
#include <sys/time.h>
#include <platform/common/log.h>

#define TIME_METHOD() MethodTimer __method_timer(__func__)

class MethodTimer {
public:
    explicit MethodTimer(const char* name) : mMethodName(name) { gettimeofday(&mStart, nullptr); }
    ~MethodTimer() {
        struct timeval stop;
        gettimeofday(&stop, nullptr);
        long long elapsed = (stop.tv_sec * 1000000) - (mStart.tv_sec * 1000000) +
                            (stop.tv_usec - mStart.tv_usec);
        LOGD("MethodTimer", "%s took %.2fms", mMethodName, elapsed / 1000.0);
    }
private:
    const char* mMethodName;
    struct timeval mStart;
};


#endif //WEEX_PROJECT_TIMING_H
