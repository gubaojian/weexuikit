//
// Created by furture on 2018/10/22.
//

#ifndef WEEX_UIKIT_GESTURE_TIMER_H
#define WEEX_UIKIT_GESTURE_TIMER_H
#include <cstdint>
#include <set>


namespace weexuikit {
/**
 * Timer fired depends on application implemation, application should call checkTimer(int64_t now)
 * to fire timer task.
 * */
    class TimerManager;

    class TimerTask {
    public:
        virtual void fireTimer()=0;
    };

    class Timer {

    public:
        /**
         * deadline is timer interval since now
         * */
        Timer(TimerManager *timerManager, int64_t _deadline, TimerTask *timerTask);

        ~Timer();

        void cancel();

        void fire();

        inline bool isExpired(int64_t now) {
            return (mStartTime + mDeadline) < now;
        }

    private:
        int64_t mDeadline;
        int64_t mStartTime;
        bool mIsCancel;
        TimerManager *mTimerManager;
        TimerTask *mTimerTask;
    };


    class TimerManager {

    public:
        TimerManager();

        ~TimerManager();

        int64_t clock();

        void addTimer(Timer *timer);

        void removeTimer(Timer *timer);

        void checkTimer(int64_t now);

    private:
        std::set<Timer *> mTimers;
    };

}

#endif //WEEX_UIKIT_GESTURE_TIMER_H
