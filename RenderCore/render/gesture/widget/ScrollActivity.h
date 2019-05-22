//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLACTIVITY_H
#define WEEX_UIKIT_GESTURE_SCROLLACTIVITY_H
#include "../foundation/BasicTypes.h"
#include "ScrollMetrics.h"
#include "Drag.h"
#include "../foundation/TickerProvider.h"
#include "../physics/Simulation.h"
#include "../animation/AnimationController.h"


namespace weexuikit {
    using VoidCallback = std::function<void()>;
/// A backend for a [ScrollActivity].
///
/// Used by subclasses of [ScrollActivity] to manipulate the scroll view that
/// they are acting upon.
///
/// See also:
///
///  * [ScrollActivity], which uses this class as its delegate.
///  * [ScrollPositionWithSingleContext], the main implementation of this interface.

    class ScrollActivityDelegate {

    public:
        /// The direction in which the scroll view scrolls.
        virtual AxisDirection axisDirection()=0;

        /// Update the scroll position to the given pixel value.
        ///
        /// Returns the overscroll, if any. See [ScrollPosition.setPixels] for more
        /// information.
        virtual double setPixels(double pixels)=0;

        /// Updates the scroll position by the given amount.
        ///
        /// Appropriate for when the user is directly manipulating the scroll
        /// position, for example by dragging the scroll view. Typically applies
        /// [ScrollPhysics.applyPhysicsToUserOffset] and other transformations that
        /// are appropriate for user-driving scrolling.
        virtual void applyUserOffset(double delta)=0;

        /// Terminate the current activity and start an idle activity.
        virtual void goIdle()=0;

        /// Terminate the current activity and start a ballistic activity with the
        /// given velocity.
        virtual void goBallistic(double velocity)=0;
    };

/// Base class for scrolling activities like dragging and flinging.
///
/// See also:
///
///  * [ScrollPosition], which uses [ScrollActivity] objects to manage the
///    [ScrollPosition] of a [Scrollable].
    class ScrollActivity {

    public:
        ScrollActivity() {}

        ~ScrollActivity() {}

    public:
        /// Initializes [delegate] for subclasses.
        ScrollActivity(ScrollActivityDelegate *delegate) : mDelegate(delegate) {

        };

        /// The delegate that this activity will use to actuate the scroll view.
        ScrollActivityDelegate *getDelegate() {
            return mDelegate;
        }

        /// Updates the activity's link to the [ScrollActivityDelegate].
        ///
        /// This should only be called when an activity is being moved from a defunct
        /// (or about-to-be defunct) [ScrollActivityDelegate] object to a new one.
        void updateDelegate(ScrollActivityDelegate *value) {
            assert(mDelegate != value);
            mDelegate = value;
        }

        /// Called by the [ScrollActivityDelegate] when it has changed type (for
        /// example, when changing from an Android-style scroll position to an
        /// iOS-style scroll position). If this activity can differ between the two
        /// modes, then it should tell the position to restart that activity
        /// appropriately.
        ///
        /// For example, [BallisticScrollActivity]'s implementation calls
        /// [ScrollActivityDelegate.goBallistic].
        virtual void resetActivity() {}

        /// Dispatch a [ScrollStartNotification] with the given metrics.
        virtual void dispatchScrollStartNotification(ScrollMetrics *metrics) {
            //ScrollStartNotification(metrics, context).dispatch(context);
        }

        /// Dispatch a [ScrollUpdateNotification] with the given metrics and scroll delta.
        virtual void dispatchScrollUpdateNotification(ScrollMetrics *metrics, double scrollDelta) {
            //ScrollUpdateNotification(metrics, context, scrollDelta).dispatch(context);
        }

        /// Dispatch an [OverscrollNotification] with the given metrics and overscroll.
        virtual void dispatchOverscrollNotification(ScrollMetrics *metrics, double overscroll) {
            //OverscrollNotification(metrics, context, overscroll).dispatch(context);
        }

        /// Dispatch a [ScrollEndNotification] with the given metrics and overscroll.
        virtual void dispatchScrollEndNotification(ScrollMetrics *metrics) {
            //ScrollEndNotification(metrics, context).dispatch(context);
        }

        /// Called when the scroll view that is performing this activity changes its metrics.
        virtual void applyNewDimensions() {}

        /// Whether the scroll view should ignore pointer events while performing this
        /// activity.
        virtual bool shouldIgnorePointer() {
            return false;
        }

        /// Whether performing this activity constitutes scrolling.
        ///
        /// Used, for example, to determine whether the user scroll direction is
        /// [ScrollDirection.idle].
        virtual bool isScrolling() {
            return false;
        }

        /// If applicable, the velocity at which the scroll offset is currently
        /// independently changing (i.e. without external stimuli such as a dragging
        /// gestures) in logical pixels per second for this activity.
        virtual double velocity() {
            return 0.0;
        }

        /// Called when the scroll view stops performing this activity.
        virtual void dispose() {
            mDelegate = nullptr;
        }

    public:
        ScrollActivityDelegate *mDelegate;
    };


/// A scroll activity that does nothing.
///
/// When a scroll view is not scrolling, it is performing the idle activity.
///
/// If the [Scrollable] changes dimensions, this activity triggers a ballistic
/// activity to restore the view.
    class IdleScrollActivity : public ScrollActivity {


    public:
        /// Creates a scroll activity that does nothing.
        IdleScrollActivity(ScrollActivityDelegate *delegate) : ScrollActivity(delegate) {

        }

        virtual void applyNewDimensions() override {
            getDelegate()->goBallistic(0.0);
        }

        virtual bool shouldIgnorePointer() override {
            return false;
        }


        virtual bool isScrolling() override {
            return false;
        }


        virtual double velocity() override {
            return 0.0;
        }
    };


/// Interface for holding a [Scrollable] stationary.
///
/// An object that implements this interface is returned by
/// [ScrollPosition.hold]. It holds the scrollable stationary until an activity
/// is started or the [cancel] method is called.
    class ScrollHoldController {

    public:
        /// Release the [Scrollable], potentially letting it go ballistic if
        /// necessary.
        virtual void cancel()=0;
    };


/// A scroll activity that does nothing but can be released to resume
/// normal idle behavior.
///
/// This is used while the user is touching the [Scrollable] but before the
/// touch has become a [Drag].
///
/// For the purposes of [ScrollNotification]s, this activity does not constitute
/// scrolling, and does not prevent the user from interacting with the contents
/// of the [Scrollable] (unlike when a drag has begun or there is a scroll
/// animation underway).

    class HoldScrollActivity : public ScrollActivity, public ScrollHoldController {

    public:
        /// Creates a scroll activity that does nothing.
        HoldScrollActivity(ScrollActivityDelegate *delegate, std::function<void()> onHoldCanceled)
                : ScrollActivity(delegate) {
            this->onHoldCanceled = onHoldCanceled;
        }

    public:
        /// Called when [dispose] is called.
        std::function<void()> onHoldCanceled;


        virtual bool shouldIgnorePointer() override {
            return false;
        }


        virtual bool isScrolling() override {
            return false;
        }


        virtual double velocity() override {
            return 0.0;
        }


        virtual void cancel() override {
            mDelegate->goBallistic(0.0);
        }


        virtual void dispose() override {
            if (onHoldCanceled != nullptr)
                onHoldCanceled();
            ScrollActivity::dispose();
        }
    };


/// Scrolls a scroll view as the user drags their finger across the screen.
///
/// See also:
///
///  * [DragScrollActivity], which is the activity the scroll view performs
///    while a drag is underway.

    class ScrollDragController : public Drag {


    public:
        /// Creates an object that scrolls a scroll view as the user drags their
        /// finger across the screen.
        ///
        /// The [delegate] and `details` arguments must not be null.
        ScrollDragController(ScrollActivityDelegate *delegate,
                             const DragStartDetails &details,
                             const VoidCallback onDragCanceled,
                             double carriedVelocity,
                             double motionStartDistanceThreshold) {
            assert(delegate != nullptr);
            this->onDragCanceled = onDragCanceled;
            this->carriedVelocity = carriedVelocity;
            this->motionStartDistanceThreshold = motionStartDistanceThreshold;
            mDelegate = delegate,
                    mLastDragStartDetails = details;
            mRetainMomentum = carriedVelocity != 0 && carriedVelocity != 0.0;
            mLastNonStationaryTimestamp = details.sourceTimeStamp,
                    mOffsetSinceLastStop = motionStartDistanceThreshold;
        }

    public:
        /// The object that will actuate the scroll view as the user drags.
        ScrollActivityDelegate *getDelegate() {
            return mDelegate;
        }

        ScrollActivityDelegate *mDelegate;

        /// Called when [dispose] is called.
        VoidCallback onDragCanceled;

        /// Velocity that was present from a previous [ScrollActivity] when this drag
        /// began.
        double carriedVelocity;

        /// Amount of pixels in either direction the drag has to move by to start
        /// scroll movement again after each time scrolling came to a stop.
        double motionStartDistanceThreshold;

        int64_t mLastNonStationaryTimestamp;
        bool mRetainMomentum;
        /// Null if already in motion or has no [motionStartDistanceThreshold].
        double mOffsetSinceLastStop;

        /// Maximum amount of time interval the drag can have consecutive stationary
        /// pointer update events before losing the momentum carried from a previous
        /// scroll activity.
        static const int64_t mMomentumRetainStationaryDurationThreshold = 20;

        /// Maximum amount of time interval the drag can have consecutive stationary
        /// pointer update events before needing to break the
        /// [motionStartDistanceThreshold] to start motion again.
        static const int64_t mMotionStoppedDurationThreshold = 50;

        /// The drag distance past which, a [motionStartDistanceThreshold] breaking
        /// drag is considered a deliberate fling.
        static constexpr double mBigThresholdBreakDistance = 24.0;

        virtual bool _reversed() {
            return axisDirectionIsReversed(mDelegate->axisDirection());
        };

        /// Updates the controller's link to the [ScrollActivityDelegate].
        ///
        /// This should only be called when a controller is being moved from a defunct
        /// (or about-to-be defunct) [ScrollActivityDelegate] object to a new one.
        void updateDelegate(ScrollActivityDelegate *value) {
            assert(mDelegate != value);
            mDelegate = value;
        }

        /// Determines whether to lose the existing incoming velocity when starting
        /// the drag.
        void _maybeLoseMomentum(double offset, int64_t timestamp) {
            if (mRetainMomentum &&
                offset == 0.0 &&
                (timestamp - mLastNonStationaryTimestamp >
                 mMomentumRetainStationaryDurationThreshold)) {
                // If pointer is stationary for too long, we lose momentum.
                mRetainMomentum = false;
            }
        }

        /// If a motion start threshold exists, determine whether the threshold needs
        /// to be broken to scroll. Also possibly apply an offset adjustment when
        /// threshold is first broken.
        ///
        /// Returns `0.0` when stationary or within threshold. Returns `offset`
        /// transparently when already in motion.
        double _adjustForScrollStartThreshold(double offset, int64_t timestamp) {
            if (timestamp < 0) {
                // If we can't track time, we can't apply thresholds.
                // May be null for proxied drags like via accessibility.
                return offset;
            }

            if (offset == 0.0) {
                if (timestamp - mLastNonStationaryTimestamp > mMotionStoppedDurationThreshold) {
                    // Enforce a new threshold.
                    mOffsetSinceLastStop = 0.0;
                }
                // Not moving can't break threshold.
                return 0.0;
            } else {
                if (mOffsetSinceLastStop == 0.0) {
                    // Already in motion or no threshold behavior configured such as for
                    // Android. Allow transparent offset transmission.
                    return offset;
                } else {
                    mOffsetSinceLastStop += offset;
                    if (std::abs(mOffsetSinceLastStop) > motionStartDistanceThreshold) {
                        // Threshold broken.
                        mOffsetSinceLastStop = 0.0;
                        if (std::abs(offset) > mBigThresholdBreakDistance) {
                            // This is heuristically a very deliberate fling. Leave the motion
                            // unaffected.
                            return offset;
                        } else {
                            // This is a normal speed threshold break.
                            return std::min(
                                    // Ease into the motion when the threshold is initially broken
                                    // to avoid a visible jump.
                                    motionStartDistanceThreshold / 3.0,
                                    std::abs(offset)
                            ) * math_sign(offset);
                        }
                    } else {
                        return 0.0;
                    }
                }
            }
        }


        virtual void update(const DragUpdateDetails &details) override {
            mLastDragUpdateDetails = details;
            double offset = details.primaryDelta;
            if (offset != 0.0) {
                mLastNonStationaryTimestamp = details.sourceTimeStamp;
            }
            // By default, iOS platforms carries momentum and has a start threshold
            // (configured in [BouncingScrollPhysics]). The 2 operations below are
            // no-ops on Android.
            _maybeLoseMomentum(offset, details.sourceTimeStamp);
            offset = _adjustForScrollStartThreshold(offset, details.sourceTimeStamp);
            if (offset == 0.0) {
                return;
            }
            if (_reversed()) // e.g. an AxisDirection.up scrollable
                offset = -offset;
            getDelegate()->applyUserOffset(offset);
        }


        virtual void end(const DragEndDetails &details) override {
            // We negate the velocity here because if the touch is moving downwards,
            // the scroll has to move upwards. It's the same reason that update()
            // above negates the delta before applying it to the scroll offset.
            double velocity = -details.primaryVelocity;
            if (_reversed()) // e.g. an AxisDirection.up scrollable
                velocity = -velocity;
            mLastDragEndDetails = details;
            // Build momentum only if dragging in the same direction.
            if (mRetainMomentum && math_sign(velocity) == math_sign(carriedVelocity))
                velocity += carriedVelocity;
            getDelegate()->goBallistic(velocity);
        }


        virtual void cancel() override {
            getDelegate()->goBallistic(0.0);
        }

        /// Called by the delegate when it is no longer sending events to this object.
        virtual void dispose() {
            if (onDragCanceled != nullptr)
                onDragCanceled();
        }

        /// The most recently observed [DragStartDetails], [DragUpdateDetails], or
        /// [DragEndDetails] object.
        DragEndDetails mLastDragEndDetails;
        DragStartDetails mLastDragStartDetails;
        DragUpdateDetails mLastDragUpdateDetails;
        /// The most recently observed [DragStartDetails], [DragUpdateDetails], or
        /// [DragEndDetails] object.
    };


/// The activity a scroll view performs when a the user drags their finger
/// across the screen.
///
/// See also:
///
///  * [ScrollDragController], which listens to the [Drag] and actually scrolls
///    the scroll view.
    class DragScrollActivity : public ScrollActivity {

    public:
        /// Creates an activity for when the user drags their finger across the
        /// screen.
        DragScrollActivity(ScrollActivityDelegate *delegate,
                           std::shared_ptr<ScrollDragController> controller) : mController(
                controller), ScrollActivity(delegate) {

        }

        std::shared_ptr<ScrollDragController> mController;

    public:
        virtual void dispatchScrollStartNotification(ScrollMetrics *metrics) override {
            DragStartDetails lastDetails = mController->mLastDragStartDetails;
            //ScrollStartNotification(metrics,  context, lastDetails).dispatch(context);
        }

        virtual void
        dispatchScrollUpdateNotification(ScrollMetrics *metrics, double scrollDelta) override {
            DragUpdateDetails lastDetails = mController->mLastDragUpdateDetails;
            //ScrollUpdateNotification(metrics, context, scrollDelta, lastDetails).dispatch(context);
        }


        virtual void
        dispatchOverscrollNotification(ScrollMetrics *metrics, double overscroll) override {
            //DragUpdateDetails lastDetails = mController->lastDragUpdateDetails;
            //OverscrollNotification(metrics, context, overscroll, lastDetails).dispatch(context);
        }

        virtual void dispatchScrollEndNotification(ScrollMetrics *metrics) override {
            // We might not have DragEndDetails yet if we're being called from beginActivity.
            DragEndDetails lastDetails = mController->mLastDragEndDetails;
            // ScrollEndNotification(metrics, context, lastDetails).dispatch(context);
        }


        virtual bool shouldIgnorePointer() override {
            return true;
        }


        virtual bool isScrolling() override {
            return true;
        }

        // DragScrollActivity is not independently changing velocity yet
        // until the drag is ended.
        virtual double velocity() override {
            return 0.0;
        }


        virtual void dispose() override {
            mController = nullptr;
            ScrollActivity::dispose();
        }
    };


/// An activity that animates a scroll view based on a physics [Simulation].
///
/// A [BallisticScrollActivity] is typically used when the user lifts their
/// finger off the screen to continue the scrolling gesture with the current velocity.
///
/// [BallisticScrollActivity] is also used to restore a scroll view to a valid
/// scroll offset when the geometry of the scroll view changes. In these
/// situations, the [Simulation] typically starts with a zero velocity.
///
/// See also:
///
///  * [DrivenScrollActivity], which animates a scroll view based on a set of
///    animation parameters.
    class BallisticScrollActivity : public ScrollActivity, public ListenVoidCallback, public AnimationEndListener {


    public:
        /// Creates an activity that animates a scroll view based on a [simulation].
        ///
        /// The [delegate], [simulation], and [vsync] arguments must not be null.
        BallisticScrollActivity(ScrollActivityDelegate *delegate, std::shared_ptr<Simulation> simulation,
                                TickerProvider *vsyncProvider) : ScrollActivity(delegate) {
            mController = AnimationController::sharePtrAnimationController(0, 0, vsyncProvider,
                                                                           AnimationBehavior::normal);
            mController->addListener(this);
            mController->animateWith(simulation);
            mController->whenComplete(this);
            // won't trigger if we dispose _controller first
        }


        ~BallisticScrollActivity() {
            if (mController != nullptr) {
                mController->dispose();
                mController.reset();
                mController = nullptr;
            }
        }


        virtual double velocity() override {
            return mController->velocity();
        }

        virtual void resetActivity() {
            getDelegate()->goBallistic(velocity());
        }


        virtual void applyNewDimensions() override {
            if (getDelegate() != nullptr) {
                getDelegate()->goBallistic(velocity());
            }
        }

        void _tick() {
            if (mController == nullptr
                || mController.get() == nullptr
                || !applyMoveTo(mController->value())) {
                if (getDelegate() != nullptr) {
                    getDelegate()->goIdle();
                }
            }
        }

        virtual void onListenEvent() override {
            _tick();
        }

        /// Move the position to the given location.
        ///
        /// If the new position was fully applied, returns true. If there was any
        /// overflow, returns false.
        ///
        /// The default implementation calls [ScrollActivityDelegate.setPixels]
        /// and returns true if the overflow was zero.
        virtual bool applyMoveTo(double value) {
            return getDelegate()->setPixels(value) == 0;
        }

        void _end() {
            getDelegate()->goBallistic(0.0);
        }


        virtual void
        dispatchOverscrollNotification(ScrollMetrics *metrics, double overscroll) override {
            //OverscrollNotification overscrollNotification = OverscrollNotification(metrics, context, overscroll);
            // overscrollNotification.mVelocity = velocity();
            // overscrollNotification.dispatch(context);
        }


        virtual bool shouldIgnorePointer() override {
            return true;
        }


        virtual bool isScrolling() override {
            return true;
        }


        virtual void dispose() override {
            if (mController != nullptr) {
                mController->dispose();
                mController.reset();
                mController = nullptr;
            }
            ScrollActivity::dispose();
        }

        virtual void onAnimationEnd() override {
            if (getDelegate() != nullptr) {
                getDelegate()->goBallistic(velocity());
            }
        }

    public:
        std::shared_ptr<AnimationController> mController;

    };


/// An activity that animates a scroll view based on animation parameters.
///
/// For example, a [DrivenScrollActivity] is used to implement
/// [ScrollController.animateTo].
///
/// See also:
///
///  * [BallisticScrollActivity], which animates a scroll view based on a
///    physics [Simulation].
    class DrivenScrollActivity : public ScrollActivity, public ListenVoidCallback {

    public:
        /// Creates an activity that animates a scroll view based on animation
        /// parameters.
        ///
        /// All of the parameters must be non-null.
        DrivenScrollActivity(ScrollActivityDelegate *_delegate, double from, double to,
                             int64_t duration, const Curve &curve, TickerProvider *vsync)
                : ScrollActivity(_delegate) {
            this->mDelegate = _delegate;
            this->mController = AnimationController::sharePtrAnimationController(from, 0, vsync,
                                                                                 AnimationBehavior::normal);
            this->mController->addListener(this);
            this->mController->animateTo(to, duration, curve);
        }

    public:

        /// A [Future] that completes when the activity stops.
        ///
        /// For example, this [Future] will complete if the animation reaches the end
        /// or if the user interacts with the scroll view in way that causes the
        /// animation to stop before it reaches the end.

        virtual double velocity() override {
            return mController->velocity();
        }

        virtual void _tick() {
            if (getDelegate()->setPixels(mController->value()) != 0.0)
                getDelegate()->goIdle();
        }

        virtual void onListenEvent() override {
            _tick();
        }

        virtual void _end() {
            if (getDelegate() != nullptr) {
                getDelegate()->goBallistic(velocity());
            }
        }


        virtual void
        dispatchOverscrollNotification(ScrollMetrics *metrics, double overscroll) override {
            //OverscrollNotification overscrollNotification =   OverscrollNotification(metrics,  context,  overscroll);
            //overscrollNotification.mVelocity = velocity();
            //overscrollNotification.dispatch(context);
        }


        virtual bool shouldIgnorePointer() override {
            return true;
        }


        virtual bool isScrolling() override {
            return true;
        }


        virtual void dispose() override {
            mController->dispose();
            ScrollActivity::dispose();
        }


    public:
        std::shared_ptr<AnimationController> mController;

    };

}


#endif //WEEX_UIKIT_GESTURE_SCROLLACTIVITY_H
