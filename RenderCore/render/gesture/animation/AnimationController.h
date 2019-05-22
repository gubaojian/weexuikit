//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_ANIMATIONCONTROLLER_H
#define WEEX_UIKIT_GESTURE_ANIMATIONCONTROLLER_H

#include <memory>
#include <render/platform/common/log.h>
#include "Animation.h"
#include "../foundation/TickerProvider.h"
#include "../foundation/Duration.h"
#include "../physics/Simulation.h"
#include "Curve.h"
#include "../foundation/BasicTypes.h"


namespace weexuikit {
/// The direction in which an animation is running.
    enum class AnimationDirection {
        /// The animation is running from beginning to end.
                forward,

        /// The animation is running backwards, from end to beginning.
                reverse,
    };


/// Configures how an [AnimationController] behaves when animations are disabled.
///
/// When [AccessibilityFeatures.disableAnimations] is true, the device is asking
/// flutter to reduce or disable animations as much as possible. To honor this,
/// we reduce the duration and the corresponding number of frames for animations.
/// This enum is used to allow certain [AnimationController]s to opt out of this
/// behavior.
///
/// For example, the [AnimationController] which controls the physics simulation
/// for a scrollable list will have [AnimationBehavior.preserve] so that when
/// a user attempts to scroll it does not jump to the end/beginning too quickly.
    enum class AnimationBehavior {
        /// The [AnimationController] will reduce its duration when
        /// [AccessibilityFeatures.disableAnimations] is true.
                normal,

        /// The [AnimationController] will preserve its behavior.
        ///
        /// This is the default for repeating animations in order to prevent them from
        /// flashing rapidly on the screen if the widget does not take the
        /// [AccessibilityFeatures.disableAnimations] flag into account.
                preserve,
    };


    class InterpolationSimulation : public Simulation {

    public:
        InterpolationSimulation(double begin, double end, int64_t duration, const Curve &curve,
                                double scale) {
            this->mBegin = begin;
            this->mEnd = end;
            this->mDuration = duration;
            this->mDurationInSeconds = (duration * scale) / Duration::microsecondsPerSecond;
            this->mCurve = curve;
            this->mScale = scale;
        }

        virtual double x(double timeInSeconds) override {
            double t = std::clamp((timeInSeconds / mDurationInSeconds), 0.0, 1.0);
            if (t == 0.0)
                return mBegin;
            else if (t == 1.0)
                return mEnd;
            else
                return mBegin + (mEnd - mBegin) * mCurve.transform(t);
        }


        virtual double dx(double timeInSeconds) override {
            double epsilon = mTolerance->time;
            return (x(timeInSeconds + epsilon) - x(timeInSeconds - epsilon)) / (2 * epsilon);
        }


        virtual bool isDone(double timeInSeconds) override {
            return timeInSeconds > mDurationInSeconds;
        }

    public:
        double mDuration;
        double mScale;
        double mDurationInSeconds;
        double mBegin;
        double mEnd;
        Curve mCurve;
    };

/// A controller for an animation.
///
/// This class lets you perform tasks such as:
///
/// * Play an animation [forward] or in [reverse], or [stop] an animation.
/// * Set the animation to a specific [value].
/// * Define the [upperBound] and [lowerBound] values of an animation.
/// * Create a [fling] animation effect using a physics simulation.
///
/// By default, an [AnimationController] linearly produces values that range
/// from 0.0 to 1.0, during a given duration. The animation controller generates
/// a new value whenever the device running your app is ready to display a new
/// frame (typically, this rate is around 60 values per second).
///
/// An AnimationController needs a [TickerProvider], which is configured using
/// the `vsync` argument on the constructor. If you are creating an
/// AnimationController from a [State], then you can use the
/// [TickerProviderStateMixin] and [SingleTickerProviderStateMixin] classes to
/// obtain a suitable [TickerProvider]. The widget test framework [WidgetTester]
/// object can be used as a ticker provider in the context of tests. In other
/// contexts, you will have to either pass a [TickerProvider] from a higher
/// level (e.g. indirectly from a [State] that mixes in
/// [TickerProviderStateMixin]), or create a custom [TickerProvider] subclass.
///
/// The methods that start animations return a [TickerFuture] object which
/// completes when the animation completes successfully, and never throws an
/// error; if the animation is canceled, the future never completes. This object
/// also has a [TickerFuture.orCancel] property which returns a future that
/// completes when the animation completes successfully, and completes with an
/// error when the animation is aborted.
///
/// This can be used to write code such as:
///
/// ```dart
/// Future<Null> fadeOutAndUpdateState() async {
///   try {
///     await fadeAnimationController.forward().orCancel;
///     await sizeAnimationController.forward().orCancel;
///     setState(() {
///       dismissed = true;
///     });
///   } on TickerCanceled {
///     // the animation got canceled, probably because we were disposed
///   }
/// }
/// ```
///
/// ...which asynchronously runs one animation, then runs another, then changes
/// the state of the widget, without having to verify [State.mounted] is still
/// true at each step, and without having to chain futures together explicitly.
/// (This assumes that the controllers are created in [State.initState] and
/// disposed in [State.dispose].)
    class AnimationEndListener {

    public:
        virtual void onAnimationEnd()=0;
    };

    class AnimationController :
            public ValueListenable<double>,
            public Animation,
            public AnimationEagerListenerMixin,
            public AnimationLocalListenersMixin,
            public AnimationLocalStatusListenersMixin,
            public TickerCallback {


    public:
        /// Creates an animation controller.
        ///
        /// * [value] is the initial value of the animation. If defaults to the lower
        ///   bound.
        ///
        /// * [duration] is the length of time this animation should last.
        ///
        /// * [debugLabel] is a string to help identify this animation during
        ///   debugging (used by [toString]).
        ///
        /// * [lowerBound] is the smallest value this animation can obtain and the
        ///   value at which this animation is deemed to be dismissed. It cannot be
        ///   null.
        ///
        /// * [upperBound] is the largest value this animation can obtain and the
        ///   value at which this animation is deemed to be completed. It cannot be
        ///   null.
        ///
        /// * `vsync` is the [TickerProvider] for the current context. It can be
        ///   changed by calling [resync]. It is required and must not be null. See
        ///   [TickerProvider] for advice on obtaining a ticker provider.
        AnimationController(double value, int64_t duration, double lowerBound = 0.0,
                            double upperBound = 1.0,
                            AnimationBehavior animationBehavior = AnimationBehavior::normal,
                            TickerProvider *vsync = nullptr) {
            assert(upperBound >= lowerBound),
                    assert(vsync != nullptr),
                    mDirection = AnimationDirection::forward;
            this->mVsync = vsync;
            if (value == 0) {
                value = lowerBound;
            }
            internalSetValue(value);
        }

        /// Creates an animation controller with no upper or lower bound for its value.
        ///
        /// * [value] is the initial value of the animation.
        ///
        /// * [duration] is the length of time this animation should last.
        ///
        /// * [debugLabel] is a string to help identify this animation during
        ///   debugging (used by [toString]).
        ///
        /// * `vsync` is the [TickerProvider] for the current context. It can be
        ///   changed by calling [resync]. It is required and must not be null. See
        ///   [TickerProvider] for advice on obtaining a ticker provider.
        ///
        /// This constructor is most useful for animations that will be driven using a
        /// physics simulation, especially when the physics simulation has no
        /// pre-determined bounds.
        AnimationController(double value, int64_t duration, TickerProvider *vsync,
                            AnimationBehavior animationBehavior) {
            assert(vsync != nullptr),
                    mLowerBound = -INFINITY;
            mUpperBound = INFINITY,
                    mDirection = AnimationDirection::forward;
            this->mVsync = vsync;
            internalSetValue(value);
        }

    public:
        static std::shared_ptr<AnimationController>
        sharePtrAnimationController(double value, int64_t duration, double lowerBound = 0.0,
                                    double upperBound = 1.0,
                                    AnimationBehavior animationBehavior = AnimationBehavior::normal,
                                    TickerProvider *vsync = nullptr) {
            std::shared_ptr<AnimationController> controller = std::make_shared<AnimationController>(
                    value, duration, lowerBound,
                    upperBound, animationBehavior, vsync);
            controller->mVsync = vsync;
            controller->mTicker = vsync->createTicker(controller);
            return controller;
        }

        static std::shared_ptr<AnimationController>
        sharePtrAnimationController(double value, int64_t duration, TickerProvider *vsync,
                                    AnimationBehavior animationBehavior) {
            std::shared_ptr<AnimationController> controller = std::make_shared<AnimationController>(
                    value, duration, vsync, animationBehavior);
            controller->mVsync = vsync;
            controller->mTicker = vsync->createTicker(controller);
            return controller;
        }


        ~AnimationController() {

        }

        virtual void dispose() override {  //despose, timer and controller is belong to
            if (mTicker != nullptr) {
                mVsync->removeTicker(mTicker);
                mTicker = nullptr;
            }
        }


    public:

        /// Returns an [Animation<double>] for this animation controller, so that a
        /// pointer to this object can be passed around without allowing users of that
        /// pointer to mutate the [AnimationController] state.
        AnimationController *getView() {
            return this;
        }

        virtual double value() override {
            return mValue;
        }


        /// Stops the animation controller and sets the current value of the
        /// animation.
        ///
        /// The new value is clamped to the range set by [lowerBound] and [upperBound].
        ///
        /// Value listeners are notified even if this does not change the value.
        /// Status listeners are notified if the animation was previously playing.
        ///
        /// The most recently returned [TickerFuture], if any, is marked as having been
        /// canceled, meaning the future never completes and its [TickerFuture.orCancel]
        /// derivative future completes with a [TickerCanceled] error.
        ///
        /// See also:
        ///
        ///  * [reset], which is equivalent to setting [value] to [lowerBound].
        ///  * [stop], which aborts the animation without changing its value or status
        ///    and without dispatching any notifications other than completing or
        ///    canceling the [TickerFuture].
        ///  * [forward], [reverse], [animateTo], [animateWith], [fling], and [repeat],
        ///    which start the animation controller.
        void setValue(double newValue) {
            stop();
            internalSetValue(newValue);
            notifyListeners();
            checkStatusChanged();
        }

        /// Sets the controller's value to [lowerBound], stopping the animation (if
        /// in progress), and resetting to its beginning point, or dismissed state.
        ///
        /// The most recently returned [TickerFuture], if any, is marked as having been
        /// canceled, meaning the future never completes and its [TickerFuture.orCancel]
        /// derivative future completes with a [TickerCanceled] error.
        ///
        /// See also:
        ///
        ///  * [value], which can be explicitly set to a specific value as desired.
        ///  * [forward], which starts the animation in the forward direction.
        ///  * [stop], which aborts the animation without changing its value or status
        ///    and without dispatching any notifications other than completing or
        ///    canceling the [TickerFuture].
        void reset() {
            setValue(mLowerBound);
        }


        /// Whether this animation is currently animating in either the forward or reverse direction.
        ///
        /// This is separate from whether it is actively ticking. An animation
        /// controller's ticker might get muted, in which case the animation
        /// controller's callbacks will no longer fire even though time is continuing
        /// to pass. See [Ticker.muted] and [TickerMode].
        bool isAnimating() {
            return mTicker != nullptr && mTicker->isActive;
        }


        /// The rate of change of [value] per second.
        ///
        /// If [isAnimating] is false, then [value] is not changing and the rate of
        /// change is zero.
        double velocity() {
            if (!isAnimating())
                return 0.0;
            return mSimulation->dx((double) mLastElapsedDuration / Duration::microsecondsPerSecond);
        }

        void internalSetValue(double newValue) {
            mValue = std::clamp(newValue, mLowerBound, mUpperBound);
            if (mValue == mLowerBound) {
                mStatus = AnimationStatus::dismissed;
            } else if (mValue == mUpperBound) {
                mStatus = AnimationStatus::completed;
            } else {
                mStatus = (mDirection == AnimationDirection::forward) ?
                          AnimationStatus::forward :
                          AnimationStatus::reverse;
            }
        }


        void checkStatusChanged() {
            AnimationStatus newStatus = status();
            if (mLastReportedStatus != newStatus) {
                mLastReportedStatus = newStatus;
                notifyStatusListeners(newStatus);
            }
        }

        virtual AnimationStatus status() override {
            return mStatus;
        }

        /// Starts running this animation forwards (towards the end).
        ///
        /// Returns a [TickerFuture] that completes when the animation is complete.
        ///
        /// The most recently returned [TickerFuture], if any, is marked as having been
        /// canceled, meaning the future never completes and its [TickerFuture.orCancel]
        /// derivative future completes with a [TickerCanceled] error.
        ///
        /// During the animation, [status] is reported as [AnimationStatus.forward],
        /// which switches to [AnimationStatus.completed] when [upperBound] is
        /// reached at the end of the animation.
        void forward(double from) {
            mDirection = AnimationDirection::forward;
            setValue(from);
            animateToInternal(mUpperBound, mDuration, Curves::linear, animationBehavior);
        }


        /// Drives the animation from its current value to target.
        ///
        /// Returns a [TickerFuture] that completes when the animation is complete.
        ///
        /// The most recently returned [TickerFuture], if any, is marked as having been
        /// canceled, meaning the future never completes and its [TickerFuture.orCancel]
        /// derivative future completes with a [TickerCanceled] error.
        ///
        /// During the animation, [status] is reported as [AnimationStatus.forward]
        /// regardless of whether `target` > [value] or not. At the end of the
        /// animation, when `target` is reached, [status] is reported as
        /// [AnimationStatus.completed].
        void animateTo(double target, int64_t duration, Curve curve = Curves::linear) {
            mDirection = AnimationDirection::forward;
            animateToInternal(target, duration, curve);
        }


        void animateToInternal(double target, int64_t duration, const Curve &curve,
                               AnimationBehavior animationBehavior = AnimationBehavior::normal) {
            AnimationBehavior behavior = animationBehavior;
            double scale = 1.0;
            int64_t simulationDuration = duration;
            if (simulationDuration <= 0) {
                double range = mUpperBound - mLowerBound;
                double remainingFraction = std::isfinite(range) ? std::abs(target - mValue) / range
                                                                : 1.0;
                simulationDuration = this->mDuration * remainingFraction;
            } else if (target == value()) {
                // Already at target, don't animate.
                simulationDuration = 0;
            }
            stop();
            if (simulationDuration == 0) {
                if (value() != target) {
                    mValue = std::clamp(target, mLowerBound, mUpperBound);
                    notifyListeners();
                }
                mStatus = (mDirection == AnimationDirection::forward) ?
                          AnimationStatus::completed :
                          AnimationStatus::dismissed;
                checkStatusChanged();
                if (mAnimationEndListener != nullptr) {
                    mAnimationEndListener->onAnimationEnd();
                }
                return;
            }
            assert(simulationDuration > 0);
            assert(!isAnimating());
            std::shared_ptr<Simulation> simulation(new InterpolationSimulation(mValue, target, simulationDuration,
                                                                 curve, scale));
            startSimulation(simulation);
        }


        /// Drives the animation according to the given simulation.
        ///
        /// Returns a [TickerFuture] that completes when the animation is complete.
        ///
        /// The most recently returned [TickerFuture], if any, is marked as having been
        /// canceled, meaning the future never completes and its [TickerFuture.orCancel]
        /// derivative future completes with a [TickerCanceled] error.
        void animateWith(std::shared_ptr<Simulation>& simulation) {
            stop();
            return startSimulation(simulation);
        }

        void whenComplete(AnimationEndListener *animationEndListener) {
            this->mAnimationEndListener = animationEndListener;
        }

    public:
        AnimationEndListener *mAnimationEndListener;

        void startSimulation(std::shared_ptr<Simulation>& simulation) {
            assert(!isAnimating());
            assert(mTicker != nullptr);
            mSimulation = simulation;
            mLastElapsedDuration = 0;
            mValue = std::clamp(simulation->x(0.0), mLowerBound, mUpperBound);
            mTicker->start();
            mStatus = (mDirection == AnimationDirection::forward) ?
                      AnimationStatus::forward :
                      AnimationStatus::reverse;
            checkStatusChanged();
        }

        /// Stops running this animation.
        ///
        /// This does not trigger any notifications. The animation stops in its
        /// current state.
        ///
        /// By default, the most recently returned [TickerFuture] is marked as having
        /// been canceled, meaning the future never completes and its
        /// [TickerFuture.orCancel] derivative future completes with a [TickerCanceled]
        /// error. By passing the `canceled` argument with the value false, this is
        /// reversed, and the futures complete successfully.
        ///
        /// See also:
        ///
        ///  * [reset], which stops the animation and resets it to the [lowerBound],
        ///    and which does send notifications.
        ///  * [forward], [reverse], [animateTo], [animateWith], [fling], and [repeat],
        ///    which restart the animation controller.
        void stop(bool canceled = true) {
            assert(mTicker != nullptr);
            mLastElapsedDuration = -1;
            mTicker->stop(canceled);
        }


        void onAnimationTick(const int64_t elapsed) {
            mLastElapsedDuration = elapsed;
            double elapsedInSeconds = ((double) elapsed) / Duration::millisecondsPerSecond;
            assert(elapsedInSeconds >= 0.0);
            mValue = std::clamp(mSimulation->x(elapsedInSeconds), mLowerBound, mUpperBound);
            if (mSimulation->isDone(elapsedInSeconds)) {
                mStatus = (mDirection == AnimationDirection::forward) ?
                          AnimationStatus::completed :
                          AnimationStatus::dismissed;
                stop(false);
                if (mAnimationEndListener != nullptr) {
                    mAnimationEndListener->onAnimationEnd();
                }
                if (mTicker != nullptr) {
                    mVsync->removeTicker(mTicker);
                    mTicker = nullptr;
                }
            }
            notifyListeners();
            checkStatusChanged();
        }

        virtual void onTick(const int64_t elapsed) {
            onAnimationTick(elapsed);
        }

    public:
        /// The value at which this animation is deemed to be dismissed.
        double mLowerBound;
        /// The value at which this animation is deemed to be completed.
        double mUpperBound;
        /// The behavior of the controller when [AccessibilityFeatures.disableAnimations]
        /// is true.
        ///
        /// Defaults to [AnimationBehavior.normal] for the [new AnimationController]
        /// constructor, and [AnimationBehavior.preserve] for the
        /// [new AnimationController.unbounded] constructor.
        AnimationBehavior animationBehavior;
        /// The length of time this animation should last.
        int64_t mDuration;
        std::shared_ptr<Ticker> mTicker;
        TickerProvider *mVsync;
        std::shared_ptr<Simulation> mSimulation;
        /// The current value of the animation.
        ///
        /// Setting this value notifies all the listeners that the value
        /// changed.
        ///
        /// Setting this value also stops the controller if it is currently
        /// running; if this happens, it also notifies all the status
        /// listeners.
        double mValue;
        AnimationStatus mStatus;
        /// The amount of time that has passed between the time the animation started
        /// and the most recent tick of the animation.
        ///
        int64_t mLastElapsedDuration = -1;
        AnimationStatus mLastReportedStatus = AnimationStatus::dismissed;
        AnimationDirection mDirection;

    };


    class RepeatingSimulation : public Simulation {

    public:
        RepeatingSimulation(double min, double max, int64_t period) {
            mMax = max;
            mMin = min;
            mPeriodInSeconds = period / Duration::microsecondsPerSecond;
            assert(mPeriodInSeconds > 0.0);
        }

    public:
        virtual double x(double timeInSeconds) override {
            assert(timeInSeconds >= 0.0);
            double t = std::fmod((timeInSeconds / mPeriodInSeconds), 1.0);
            return lerpDouble(mMin, mMax, t);
        }


        virtual double dx(double timeInSeconds) override {
            return (mMax - mMin) / mPeriodInSeconds;
        }

        virtual bool isDone(double timeInSeconds) override {
            return false;
        }

    public:
        double mMin;
        double mMax;
        double mPeriodInSeconds;

    };

}


#endif //WEEX_UIKIT_GESTURE_ANIMATIONCONTROLLER_H
