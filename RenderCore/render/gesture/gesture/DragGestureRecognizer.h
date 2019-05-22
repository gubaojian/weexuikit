//
// Created by furture on 2018/10/18.
//

#ifndef WEEX_UIKIT_GESTURE_DRAGGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_DRAGGESTURERECOGNIZER_H
#include "OneSequenceGestureRecognizer.h"
#include "../geometry/Geometry.h"
#include "../geometry/VelocityTracker.h"
#include "GestureConfig.h"
#include <map>
#include <set>

namespace weexuikit {
    enum class DragState {
        ready,
        possible,
        accepted,
    };
/// Details object for callbacks that use [GestureDragDownCallback].
///
/// See also:
///
///  * [DragGestureRecognizer.onDown], which uses [GestureDragDownCallback].
///  * [DragStartDetails], the details for [GestureDragStartCallback].
///  * [DragUpdateDetails], the details for [GestureDragUpdateCallback].
///  * [DragEndDetails], the details for [GestureDragEndCallback].

    struct DragDownDetails {
        /// The global position at which the pointer contacted the screen.
        ///
        /// Defaults to the origin if not specified in the constructor.
        Offset globalPosition;
    };

/// Signature for when a pointer has contacted the screen and might begin to
/// move.
///
/// The `details` object provides the position of the touch.
///
/// See [DragGestureRecognizer.onDown].
    using GestureDragDownCallback = std::function<void(const DragDownDetails &)>;


/// Details object for callbacks that use [GestureDragStartCallback].
///
/// See also:
///
///  * [DragGestureRecognizer.onStart], which uses [GestureDragStartCallback].
///  * [DragDownDetails], the details for [GestureDragDownCallback].
///  * [DragUpdateDetails], the details for [GestureDragUpdateCallback].
///  * [DragEndDetails], the details for [GestureDragEndCallback].
    struct DragStartDetails {
        /// Recorded timestamp of the source pointer event that triggered the drag
        /// event.
        ///
        /// Could be null if triggered from proxied events such as accessibility.
        int64_t sourceTimeStamp;

        /// The global position at which the pointer contacted the screen.
        ///
        /// Defaults to the origin if not specified in the constructor.
        Offset globalPosition;
    };


/// Signature for when a pointer has contacted the screen and has begun to move.
///
/// The `details` object provides the position of the touch when it first
/// touched the surface.
///
/// See [DragGestureRecognizer.onStart].
    using GestureDragStartCallback = std::function<void(const DragStartDetails &)>;



/// Details object for callbacks that use [GestureDragUpdateCallback].
///
/// See also:
///
///  * [DragGestureRecognizer.onUpdate], which uses [GestureDragUpdateCallback].
///  * [DragDownDetails], the details for [GestureDragDownCallback].
///  * [DragStartDetails], the details for [GestureDragStartCallback].
///  * [DragEndDetails], the details for [GestureDragEndCallback].
    struct DragUpdateDetails {

        // Recorded timestamp of the source pointer event that triggered the drag
        /// event.
        ///
        /// Could be null if triggered from proxied events such as accessibility.
        int64_t sourceTimeStamp;

        /// The amount the pointer has moved since the previous update.
        ///
        /// If the [GestureDragUpdateCallback] is for a one-dimensional drag (e.g.,
        /// a horizontal or vertical drag), then this offset contains only the delta
        /// in that direction (i.e., the coordinate in the other direction is zero).
        ///
        /// Defaults to zero if not specified in the constructor.
        Offset delta;

        /// The amount the pointer has moved along the primary axis since the previous
        /// update.
        ///
        /// If the [GestureDragUpdateCallback] is for a one-dimensional drag (e.g.,
        /// a horizontal or vertical drag), then this value contains the component of
        /// [delta] along the primary axis (e.g., horizontal or vertical,
        /// respectively). Otherwise, if the [GestureDragUpdateCallback] is for a
        /// two-dimensional drag (e.g., a pan), then this value is null.
        ///
        /// Defaults to null if not specified in the constructor.
        double primaryDelta;

        /// The pointer's global position when it triggered this update.
        Offset globalPosition;
    };

/// Signature for when a pointer that is in contact with the screen and moving
/// has moved again.
///
/// The `details` object provides the position of the touch and the distance it
/// has travelled since the last update.
///
/// See [DragGestureRecognizer.onUpdate].
    using GestureDragUpdateCallback = std::function<void(const DragUpdateDetails &)>;


/// Details object for callbacks that use [GestureDragEndCallback].
///
/// See also:
///
///  * [DragGestureRecognizer.onEnd], which uses [GestureDragEndCallback].
///  * [DragDownDetails], the details for [GestureDragDownCallback].
///  * [DragStartDetails], the details for [GestureDragStartCallback].
///  * [DragUpdateDetails], the details for [GestureDragUpdateCallback].
    struct DragEndDetails {
        /// The velocity the pointer was moving when it stopped contacting the screen.
        ///
        /// Defaults to zero if not specified in the constructor.
        Velocity velocity;

        /// The velocity the pointer was moving along the primary axis when it stopped
        /// contacting the screen, in logical pixels per second.
        ///
        /// If the [GestureDragEndCallback] is for a one-dimensional drag (e.g., a
        /// horizontal or vertical drag), then this value contains the component of
        /// [velocity] along the primary axis (e.g., horizontal or vertical,
        /// respectively). Otherwise, if the [GestureDragEndCallback] is for a
        /// two-dimensional drag (e.g., a pan), then this value is null.
        ///
        /// Defaults to null if not specified in the constructor.
        double primaryVelocity;
    };

/// Signature for when a pointer that was previously in contact with the screen
/// and moving is no longer in contact with the screen.
///
/// The velocity at which the pointer was moving when it stopped contacting
/// the screen is available in the `details`.
///
/// See [DragGestureRecognizer.onEnd].
    using GestureDragEndCallback = std::function<void(const DragEndDetails &)>;



/// Signature for when the pointer that previously triggered a
/// [GestureDragDownCallback] did not complete.
///
/// See [DragGestureRecognizer.onCancel].
    using GestureDragCancelCallback = std::function<void()>;


/// Recognizes movement.
///
/// In contrast to [MultiDragGestureRecognizer], [DragGestureRecognizer]
/// recognizes a single gesture sequence for all the pointers it watches, which
/// means that the recognizer has at most one drag sequence active at any given
/// time regardless of how many pointers are in contact with the screen.
///
/// [DragGestureRecognizer] is not intended to be used directly. Instead,
/// consider using one of its subclasses to recognize specific types for drag
/// gestures.
///
/// See also:
///
///  * [HorizontalDragGestureRecognizer], for left and right drags.
///  * [VerticalDragGestureRecognizer], for up and down drags.
///  * [PanGestureRecognizer], for drags that are not locked to a single axis.
    class DragGestureRecognizer : public OneSequenceGestureRecognizer {
    public:
        DragGestureRecognizer(GestureHandlerContext *gestureContext);

    public:
        /// A pointer has contacted the screen and might begin to move.
        ///
        /// The position of the pointer is provided in the callback's `details`
        /// argument, which is a [DragDownDetails] object.
        GestureDragDownCallback onDown;

        /// A pointer has contacted the screen and has begun to move.
        ///
        /// The position of the pointer is provided in the callback's `details`
        /// argument, which is a [DragStartDetails] object.
        GestureDragStartCallback onStart;

        /// A pointer that is in contact with the screen and moving has moved again.
        ///
        /// The distance travelled by the pointer since the last update is provided in
        /// the callback's `details` argument, which is a [DragUpdateDetails] object.
        GestureDragUpdateCallback onUpdate;


        /// A pointer that was previously in contact with the screen and moving is no
        /// longer in contact with the screen and was moving at a specific velocity
        /// when it stopped contacting the screen.
        ///
        /// The velocity is provided in the callback's `details` argument, which is a
        /// [DragEndDetails] object.
        GestureDragEndCallback onEnd;

        /// The pointer that previously triggered [onDown] did not complete.
        GestureDragCancelCallback onCancel;


    public:
        void setMaxFlingVelocity(double maxVelocity) {
            this->mMaxFlingVelocity = maxVelocity;
        }


    protected:
        /// The minimum distance an input pointer drag must have moved to
        /// to be considered a fling gesture.
        ///
        /// This value is typically compared with the distance traveled along the
        /// scrolling axis. If null then [kTouchSlop] is used.
        double mMinFlingDistance = kTouchSlop;

        /// The minimum velocity for an input pointer drag to be considered fling.
        ///
        /// This value is typically compared with the magnitude of fling gesture's
        /// velocity along the scrolling axis. If null then [kMinFlingVelocity]
        /// is used.
        double mMinFlingVelocity = kMinFlingVelocity;

        /// Fling velocity magnitudes will be clamped to this value.
        ///
        /// If null then [kMaxFlingVelocity] is used.
        double mMaxFlingVelocity = kMaxFlingVelocity;


        DragState mDragState = DragState::ready;
        Offset mInitialPosition;
        Offset mPendingDragOffset;
        int64_t mLastPendingEventTimestamp;
        std::map<int, std::shared_ptr<VelocityTracker>> mVelocityTrackers;


    public:
        virtual bool _isFlingGesture(VelocityEstimate *estimate)=0;

        virtual Offset _getDeltaForDetails(const Offset &delta)=0;

        virtual double _getPrimaryValueFromOffset(const Offset &value)=0;

        virtual bool getHasSufficientPendingDragDeltaToAccept()=0;

        virtual void addPointer(const PointerEvent &event) override {
            startTrackingPointer(event.pointer);
            mVelocityTrackers[event.pointer] = std::make_shared<VelocityTracker>();
            if (mDragState == DragState::ready) {
                mDragState = DragState::possible;
                mInitialPosition = event.position;
                mPendingDragOffset = makeOffset(0, 0);
                mLastPendingEventTimestamp = event.timeStamp;
                if (onDown != nullptr) {
                    DragDownDetails dragDownDetails = {mInitialPosition};
                    onDown(dragDownDetails);
                }
            } else if (mDragState == DragState::accepted) {
                resolve(GestureDisposition::accepted);
            }
        }


        virtual void handleEvent(const PointerEvent &event) override {
            assert(mDragState != DragState::ready);
            if (!event.synthesized
                && (event.isDownEvent() || event.isMoveEvent())) {
                std::shared_ptr<VelocityTracker> tracker = mVelocityTrackers[event.pointer];
                assert(tracker.get() != nullptr);
                tracker->addPosition(event.timeStamp, event.position);
            }

            if (event.isMoveEvent()) {
                Offset delta = event.delta;
                if (mDragState == DragState::accepted) {
                    if (onUpdate != nullptr) {
                        DragUpdateDetails dragUpdateDetails{
                                event.timeStamp,
                                _getDeltaForDetails(delta),
                                _getPrimaryValueFromOffset(delta),
                                event.position
                        };
                        onUpdate(dragUpdateDetails);
                    }
                } else {
                    mPendingDragOffset += delta;
                    mLastPendingEventTimestamp = event.timeStamp;
                    if (getHasSufficientPendingDragDeltaToAccept())
                        resolve(GestureDisposition::accepted);
                }
            }
            stopTrackingIfPointerNoLongerDown(event);
        }


        virtual void acceptGesture(int pointer) override {
            if (mDragState != DragState::accepted) {
                mDragState = DragState::accepted;
                Offset delta = mPendingDragOffset;
                int64_t timestamp = mLastPendingEventTimestamp;
                mPendingDragOffset = makeOffset(0, 0);
                mLastPendingEventTimestamp = 0;
                if (onStart != nullptr) {
                    DragStartDetails dragStartDetails = {timestamp, mInitialPosition};
                    onStart(dragStartDetails);
                }
                if (!delta.isZero() && onUpdate != nullptr) {
                    Offset deltaForDetails = _getDeltaForDetails(delta);
                    DragUpdateDetails dragUpdateDetails = {timestamp, deltaForDetails,
                                                           _getPrimaryValueFromOffset(delta),
                                                           mInitialPosition + deltaForDetails};
                    onUpdate(dragUpdateDetails);
                }
            }
        }

        virtual void rejectGesture(int pointer) override {
            stopTrackingPointer(pointer);
        }


        virtual void didStopTrackingLastPointer(int pointer) override {
            if (mDragState == DragState::possible) {
                resolve(GestureDisposition::rejected);
                mDragState = DragState::ready;
                if (onCancel != nullptr) {
                    onCancel();
                }
                return;
            }
            bool wasAccepted = mDragState == DragState::accepted;
            mDragState = DragState::ready;
            if (wasAccepted && onEnd != nullptr) {
                std::shared_ptr<VelocityTracker> tracker = mVelocityTrackers[pointer];
                assert(tracker.get() != nullptr);

                VelocityEstimate *estimate = tracker->getVelocityEstimate();
                if (estimate != nullptr && _isFlingGesture(estimate)) {
                    Velocity velocity = {estimate->pixelsPerSecond};
                    velocity = velocity.clampMagnitude(mMinFlingVelocity, mMaxFlingVelocity);
                    DragEndDetails dragEndDetails = {velocity, _getPrimaryValueFromOffset(
                            velocity.pixelsPerSecond)};
                    onEnd(dragEndDetails);
                } else {
                    Velocity velocity = {makeOffset(0, 0)};
                    DragEndDetails dragEndDetails = {velocity, 0};
                    onEnd(dragEndDetails);
                }
                if (estimate != nullptr) {
                    delete estimate;
                }
            }
            mVelocityTrackers.clear();
        }


        virtual void dispose() override {
            mVelocityTrackers.clear();
            OneSequenceGestureRecognizer::dispose();
        }
    };
}


#endif //WEEX_UIKIT_GESTURE_DRAGGESTURERECOGNIZER_H
