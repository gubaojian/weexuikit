//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_TICKERPROVIDER_H
#define WEEX_UIKIT_GESTURE_TICKERPROVIDER_H
#include <functional>
#include <vector>
#include <algorithm>
#include <mutex>
#include <memory>
#include <render/platform/common/log.h>

namespace weexuikit {
/// Signature for the callback passed to the [Ticker] class's constructor.
///
/// The argument is the time that the object had spent enabled so far
/// at the time of the callback being called.
    class TickerCallback {

    public:
        virtual void onTick(const int64_t elapsed) {

        }
    };


/// Calls its callback once per animation frame.
///
/// When created, a ticker is initially disabled. Call [start] to
/// enable the ticker.
///
/// A [Ticker] can be silenced by setting [muted] to true. While silenced, time
/// still elapses, and [start] and [stop] can still be called, but no callbacks
/// are called.
///
/// By convention, the [start] and [stop] methods are used by the ticker's
/// consumer, and the [muted] property is controlled by the [TickerProvider]
/// that created the ticker.
///
/// Tickers are driven by the [SchedulerBinding]. See
/// [SchedulerBinding.scheduleFrameCallback].
    class Ticker {

        /// Creates a ticker that will call the provided callback once per frame while
        /// running.
        ///
        /// An optional label can be provided for debugging purposes. That label
        /// will appear in the [toString] output in debug builds.
    public:
        Ticker(std::shared_ptr<TickerCallback> onTick) {
            this->_onTick = onTick;
            this->firstTicket = 0;
            this->isCanceled = false;
            this->isActive = false;
            this->isDone = false;
        };

    public:
        bool isActive;
        bool isCanceled;
        bool isDone;
        int64_t firstTicket;
    public:
        std::shared_ptr<TickerCallback> _onTick;

        void start() {
            isActive = true;
            isCanceled = false;
        }

        void fireTick(const int64_t clockTimeMs) {
            if (isDone) {
                return;
            }
            if (isCanceled) {
                return;
            }
            if (firstTicket <= 0) {
                firstTicket = clockTimeMs;
                return;
            }

            if (_onTick != nullptr) {
                int64_t elapsed = clockTimeMs - firstTicket;
                _onTick->onTick(elapsed);
            }
        }

        void stop(bool canceled = false) {
            isCanceled = canceled;
            isActive = false;
        }
    };


    using VoidTickerCallback = std::function<void()>;

    class DelayTicker : public TickerCallback {

    public:
        virtual void onTick(const int64_t elapsed) override {
            if (firstTick == 0) {
                firstTick = elapsed;
            }
            if ((elapsed - firstTick) > delayTime) {
                delayTickerCallback();
                if (ticker != nullptr) {
                    ticker->isDone = true;
                    ticker->isCanceled = true;
                    ticker = nullptr;
                }
            }
        }

    public:
        int64_t delayTime;
        int64_t firstTick;
        std::shared_ptr<Ticker> ticker;
        VoidTickerCallback delayTickerCallback;
    };


    using AnimationTickerCallback = std::function<void(float value)>;


    class AnimationTicker : public TickerCallback {

    public:
        AnimationTicker() {
            mFirstTick = 0;
            mTicker = nullptr;
            duration = 0;
        }

    public:
        virtual void onTick(const int64_t elapsed) override {
            if (mFirstTick == 0) {
                mFirstTick = elapsed;
            }
            int64_t time = elapsed - mFirstTick;
            if (time >= duration) {
                onAnimation(1.0f);
                if (mTicker != nullptr) {
                    mTicker->isDone = true;
                    mTicker->isCanceled = true;
                    mTicker = nullptr;
                }
                return;
            } else {
                onAnimation(((float) time) / duration);
            }

        }

    public:
        int64_t duration;
        std::shared_ptr<Ticker> mTicker;
        AnimationTickerCallback onAnimation;

    private:
        int64_t mFirstTick;
    };

/// An interface implemented by classes that can vend [Ticker] objects.
///
/// Tickers can be used by any object that wants to be notified whenever a frame
/// triggers, but are most commonly used indirectly via an
/// [AnimationController]. [AnimationController]s need a [TickerProvider] to
/// obtain their [Ticker]. If you are creating an [AnimationController] from a
/// [State], then you can use the [TickerProviderStateMixin] and
/// [SingleTickerProviderStateMixin] classes to obtain a suitable
/// [TickerProvider]. The widget test framework [WidgetTester] object can be
/// used as a ticker provider in the context of tests. In other contexts, you
/// will have to either pass a [TickerProvider] from a higher level (e.g.
/// indirectly from a [State] that mixes in [TickerProviderStateMixin]), or
/// create a custom [TickerProvider] subclass.
    class TickerProvider {

    public:
        TickerProvider() {
            mTickerList = new std::vector<std::shared_ptr<Ticker>>();
        }

        ~TickerProvider() {
            if (mTickerList != nullptr) {
                delete mTickerList;
                mTickerList = nullptr;
            }
        }

    private:
        std::vector<std::shared_ptr<Ticker>> *mTickerList;

    public:
        void checkTicker(const int64_t clockTimeMS);

        /// Creates a ticker with the given callback.
        ///
        /// The kind of ticker provided depends on the kind of ticker provider.
        std::shared_ptr<Ticker> createTicker(std::shared_ptr<TickerCallback> onTick);

        void removeTicker(std::shared_ptr<Ticker> ticker);
    };

}


#endif //WEEX_UIKIT_GESTURE_TICKERPROVIDER_H
