//
// Created by furture on 2018/10/22.
//

#include "Timer.h"
#include <chrono>


namespace weexuikit {

    Timer::Timer(TimerManager *timerManager, int64_t deadline, TimerTask *timerTask) {
        this->mTimerManager = timerManager;
        this->mDeadline = deadline;
        this->mTimerTask = timerTask;
        this->mStartTime = timerManager->clock();
        this->mTimerManager->addTimer(this);
    }

    void Timer::cancel() {
        mIsCancel = true;
        if (mTimerTask != nullptr) {
            mTimerManager->removeTimer(this);
            mTimerTask = nullptr;
            mIsCancel = true;
        }
    }

    void Timer::fire() {
        if (mIsCancel) {
            return;
        }
        if (mTimerTask != NULL) {
            mTimerTask->fireTimer();
            mTimerTask = nullptr;
        }
    }

    Timer::~Timer() {
        cancel();
    }

    TimerManager::TimerManager() {

    }

    int64_t TimerManager::clock() {
        std::chrono::system_clock::duration now = std::chrono::system_clock::now().time_since_epoch();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now);
        return ms.count();
    }

    void TimerManager::addTimer(Timer *timer) {
        mTimers.insert(timer);
    }

    void TimerManager::checkTimer(int64_t now) {
        for (auto it = mTimers.begin(); it != mTimers.end();) {
            Timer *timer = *it;
            if (timer->isExpired(now)) {
                timer->fire();
                it = mTimers.erase(it);
            } else {
                it++;
            }
        }
    }

    void TimerManager::removeTimer(Timer *timer) {
        mTimers.erase(timer);
    }

    TimerManager::~TimerManager() {
        mTimers.clear();
    }
}