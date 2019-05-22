//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_DURATION_H
#define WEEX_UIKIT_GESTURE_DURATION_H
#include<inttypes.h>

namespace weexuikit {


    namespace Duration {

        static const int64_t microsecondsPerMillisecond = 1000;
        static const int64_t millisecondsPerSecond = 1000;
        static const int64_t secondsPerMinute = 60;
        static const int64_t minutesPerHour = 60;
        static const int64_t hoursPerDay = 24;

        static const int64_t microsecondsPerSecond =
                microsecondsPerMillisecond * millisecondsPerSecond;
        static const int64_t microsecondsPerMinute =
                microsecondsPerSecond * secondsPerMinute;
        static const int64_t microsecondsPerHour = microsecondsPerMinute * minutesPerHour;
        static const int64_t microsecondsPerDay = microsecondsPerHour * hoursPerDay;

        static const int64_t millisecondsPerMinute =
                millisecondsPerSecond * secondsPerMinute;
        static const int64_t millisecondsPerHour = millisecondsPerMinute * minutesPerHour;
        static const int64_t millisecondsPerDay = millisecondsPerHour * hoursPerDay;

        static const int64_t secondsPerHour = secondsPerMinute * minutesPerHour;
        static const int64_t secondsPerDay = secondsPerHour * hoursPerDay;

        static const int64_t minutesPerDay = minutesPerHour * hoursPerDay;
    }
}

#endif //WEEX_UIKIT_GESTURE_DURATION_H
