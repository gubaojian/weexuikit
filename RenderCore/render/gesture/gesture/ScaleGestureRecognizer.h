//
// Created by furture on 2018/10/19.
//

#ifndef WEEX_UIKIT_GESTURE_SCALEGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_SCALEGESTURERECOGNIZER_H
#include "OneSequenceGestureRecognizer.h"
#include "../geometry/VelocityTracker.h"
#include "GestureConfig.h"
#include <memory>
#include <map>
#include <set>

namespace weexuikit {
/// The possible states of a [ScaleGestureRecognizer].
    enum class ScaleState {
        /// The recognizer is ready to start recognizing a gesture.
                ready,

        /// The sequence of pointer events seen thus far is consistent with a scale
        /// gesture but the gesture has not been accepted definitively.
                possible,

        /// The sequence of pointer events seen thus far has been accepted
        /// definitively as a scale gesture.
                accepted,

        /// The sequence of pointer events seen thus far has been accepted
        /// definitively as a scale gesture and the pointers established a focal point
        /// and initial scale.
                started,
    };

/// Details for [GestureScaleStartCallback].
    struct ScaleStartDetails {
        /// The initial focal point of the pointers in contact with the screen.
        /// Reported in global coordinates.
        Offset focalPoint;
    };

/// Details for [GestureScaleUpdateCallback].
    struct ScaleUpdateDetails {
        /// The scale implied by the pointers in contact with the screen. A value
        /// greater than or equal to zero.
        double scale;

        /// The focal point of the pointers in contact with the screen. Reported in
        /// global coordinates.
        Offset focalPoint;


        /// The angle implied by the first two pointers to enter in contact with
        /// the screen. Expressed in radians.
        double rotation;
    };

/// Details for [GestureScaleEndCallback].
    struct ScaleEndDetails {
        /// The velocity of the last pointer to be lifted off of the screen.
        Velocity velocity;
    };

/// Signature for when the pointers in contact with the screen have established
/// a focal point and initial scale of 1.0.
    using GestureScaleStartCallback = std::function<void(const ScaleStartDetails &)>;

/// Signature for when the pointers in contact with the screen have indicated a
/// new focal point and/or scale.
    using GestureScaleUpdateCallback = std::function<void(const ScaleUpdateDetails &)>;

/// Signature for when the pointers are no longer in contact with the screen.
    using GestureScaleEndCallback = std::function<void(const ScaleEndDetails &)>;



/// Defines a line between two pointers on screen.
///
/// [_LineBetweenPointers] is an abstraction of a line between two pointers in
/// contact with the screen. Used to track the rotation of a scale gesture.
    struct LineBetweenPointers {
        // The location and the id of the pointer that marks the start of the line.
        int pointerStartId;
        Offset pointerStartLocation;

        // The location and the id of the pointer that marks the end of the line.
        int pointerEndId;
        Offset pointerEndLocation;
        bool hasValue;
    };

/// Recognizes a scale gesture.
///
/// [ScaleGestureRecognizer] tracks the pointers in contact with the screen and
/// calculates their focal point, indicated scale and rotation. When a focal pointer is
/// established, the recognizer calls [onStart]. As the focal point, scale, rotation
/// change, the recognizer calls [onUpdate]. When the pointers are no longer in
/// contact with the screen, the recognizer calls [onEnd].
    class ScaleGestureRecognizer : public OneSequenceGestureRecognizer {
    public:
        ScaleGestureRecognizer(GestureHandlerContext *gestureContext);

    public:
        /// The pointers in contact with the screen have established a focal point and
        /// initial scale of 1.0.
        GestureScaleStartCallback onStart;

        /// The pointers in contact with the screen have indicated a new focal point
        /// and/or scale.
        GestureScaleUpdateCallback onUpdate;

        /// The pointers are no longer in contact with the screen.
        GestureScaleEndCallback onEnd;

        ScaleState mScaleState = ScaleState::ready;
        Offset mInitialFocalPoint;
        Offset mCurrentFocalPoint;
        double mInitialSpan;
        double mCurrentSpan;
        LineBetweenPointers mInitialLine;
        LineBetweenPointers mCurrentLine;
        std::map<int, Offset> mPointerLocations;
        std::vector<int> mPointerQueue; /// A queue to sort pointers in order of entrance

        std::map<int, std::shared_ptr<VelocityTracker>> mVelocityTrackers;

        inline double getScaleFactor() {
            return mInitialSpan > 0.0 ? mCurrentSpan / mInitialSpan : 1.0;
        }

        double _computeRotationFactor() {
            if (!mInitialLine.hasValue || !mCurrentLine.hasValue) {
                return 0.0;
            }
            double fx = mInitialLine.pointerStartLocation.dx;
            double fy = mInitialLine.pointerStartLocation.dy;
            double sx = mInitialLine.pointerEndLocation.dx;
            double sy = mInitialLine.pointerEndLocation.dy;

            double nfx = mCurrentLine.pointerStartLocation.dx;
            double nfy = mCurrentLine.pointerStartLocation.dy;
            double nsx = mCurrentLine.pointerEndLocation.dx;
            double nsy = mCurrentLine.pointerEndLocation.dy;

            double angle1 = std::atan2(fy - sy, fx - sx);
            double angle2 = std::atan2(nfy - nsy, nfx - nsx);

            return angle2 - angle1;
        }


        virtual void addPointer(const PointerEvent &event) override {
            startTrackingPointer(event.pointer);
            mVelocityTrackers[event.pointer] = std::make_shared<VelocityTracker>();
            if (mScaleState == ScaleState::ready) {
                mScaleState = ScaleState::possible;
                mInitialSpan = 0.0;
                mCurrentSpan = 0.0;
                mPointerLocations.clear();
                mPointerQueue.clear();
            }
        }


        /// Updates [_initialLine] and [_currentLine] accordingly to the situation of
        /// the registered pointers
        void _updateLines() {
            int count = mPointerLocations.size();
            assert(mPointerQueue.size() >= count);
            /// In case of just one pointer registered, reconfigure [_initialLine]
            if (count < 2) {
                mInitialLine = mCurrentLine;
            } else if (mInitialLine.hasValue &&
                       mInitialLine.pointerStartId == mPointerQueue[0] &&
                       mInitialLine.pointerEndId == mPointerQueue[1]) {
                /// Rotation updated, set the [_currentLine]


                mCurrentLine = LineBetweenPointers{
                        mPointerQueue[0],
                        mPointerLocations.at(mPointerQueue[0]),
                        mPointerQueue[1],
                        mPointerLocations[mPointerQueue[1]],
                        true
                };
            } else {
                /// A new rotation process is on the way, set the [_initialLine]
                mInitialLine = LineBetweenPointers{
                        mPointerQueue[0],
                        mPointerLocations[mPointerQueue[0]],
                        mPointerQueue[1],
                        mPointerLocations[mPointerQueue[1]],
                        true
                };
                mCurrentLine.hasValue = false;
            }
        }

        bool _isFlingGesture(Velocity &velocity) {
            double speedSquared = velocity.pixelsPerSecond.distanceSquared();
            return speedSquared > kMinFlingVelocity * kMinFlingVelocity;
        }

        bool _reconfigure(int pointer) {
            mInitialFocalPoint = mCurrentFocalPoint;
            mInitialSpan = mCurrentSpan;
            mInitialLine = mCurrentLine;
            if (mScaleState == ScaleState::started) {
                if (onEnd != nullptr) {
                    std::shared_ptr<VelocityTracker> tracker = mVelocityTrackers[pointer];
                    assert(tracker.get() != nullptr);

                    Velocity velocity = tracker->getVelocity();
                    if (_isFlingGesture(velocity)) {
                        Offset pixelsPerSecond = velocity.pixelsPerSecond;
                        if (pixelsPerSecond.distanceSquared() >
                            kMaxFlingVelocity * kMaxFlingVelocity) {
                            pixelsPerSecond = (pixelsPerSecond / pixelsPerSecond.distance()) *
                                              kMaxFlingVelocity;
                        }
                        velocity = Velocity{pixelsPerSecond};
                        ScaleEndDetails scaleEndDetails = {velocity};
                        onEnd(scaleEndDetails);
                    } else {
                        velocity = Velocity{makeOffset(0, 0)};
                        ScaleEndDetails scaleEndDetails = {velocity};
                        onEnd(scaleEndDetails);
                    }
                }
                mScaleState = ScaleState::accepted;
                return false;
            }
            return true;
        }

        void _dispatchOnStartCallbackIfNeeded() {
            assert(mScaleState == ScaleState::started);
            if (onStart != nullptr) {
                ScaleStartDetails scaleStartDetails = {mCurrentFocalPoint};
                onStart(scaleStartDetails);
            }
        }

        void _advanceStateMachine(bool shouldStartIfAccepted) {
            if (mScaleState == ScaleState::ready)
                mScaleState = ScaleState::possible;

            if (mScaleState == ScaleState::possible) {
                double spanDelta = std::abs(mCurrentSpan - mInitialSpan);
                double focalPointDelta = (mCurrentFocalPoint - mInitialFocalPoint).distance();
                if (spanDelta > kScaleSlop || focalPointDelta > kPanSlop)
                    resolve(GestureDisposition::accepted);
            } else if (mScaleState >= ScaleState::accepted) {
                resolve(GestureDisposition::accepted);
            }

            if (mScaleState == ScaleState::accepted && shouldStartIfAccepted) {
                mScaleState = ScaleState::started;
                _dispatchOnStartCallbackIfNeeded();
            }

            if (mScaleState == ScaleState::started && onUpdate != nullptr) {
                ScaleUpdateDetails scaleUpdateDetails = {getScaleFactor(), mCurrentFocalPoint,
                                                         _computeRotationFactor()};
            }
        }

        void _update() {
            int count = mPointerLocations.size();

            // Compute the focal point
            Offset focalPoint = makeOffset(0, 0);
            for (auto &kv : mPointerLocations) {
                int pointer = kv.first;
                focalPoint += mPointerLocations[pointer];
            }
            mCurrentFocalPoint = count > 0 ? focalPoint / count : makeOffset(0, 0);

            // Span is the average deviation from focal point
            double totalDeviation = 0.0;
            for (auto &kv : mPointerLocations) {
                int pointer = kv.first;
                totalDeviation += (mCurrentFocalPoint - mPointerLocations[pointer]).distance();
            }
            mCurrentSpan = count > 0 ? totalDeviation / count : 0.0;
        }

        virtual void handleEvent(const PointerEvent &event) override {
            assert(mScaleState != ScaleState::ready);
            bool didChangeConfiguration = false;
            bool shouldStartIfAccepted = false;

            if (event.isMoveEvent()) {
                std::shared_ptr<VelocityTracker> tracker = mVelocityTrackers[event.pointer];
                assert(tracker.get() != nullptr);
                if (!event.synthesized)
                    tracker->addPosition(event.timeStamp, event.position);
                mPointerLocations[event.pointer] = event.position;
                shouldStartIfAccepted = true;
            } else if (event.isDownEvent()) {
                mPointerLocations[event.pointer] = event.position;
                mPointerQueue.push_back(event.pointer);
                didChangeConfiguration = true;
                shouldStartIfAccepted = true;
            } else if (event.isUpEvent() || event.isCancelEvent()) {
                mPointerLocations.erase(event.pointer); //.remove(event.pointer);
                std::remove(mPointerQueue.begin(), mPointerQueue.end(), event.pointer);
                didChangeConfiguration = true;
            }

            _updateLines();
            _update();

            if (!didChangeConfiguration || _reconfigure(event.pointer))
                _advanceStateMachine(shouldStartIfAccepted);
            stopTrackingIfPointerNoLongerDown(event);
        }


        virtual void acceptGesture(int pointer) override {
            if (mScaleState == ScaleState::possible) {
                mScaleState = ScaleState::started;
                _dispatchOnStartCallbackIfNeeded();
            }
        }

        virtual void rejectGesture(int pointer) override {
            stopTrackingPointer(pointer);
        }

        virtual void didStopTrackingLastPointer(int pointer) override {
            switch (mScaleState) {
                case ScaleState::possible:
                    resolve(GestureDisposition::rejected);
                    break;
                case ScaleState::ready:
                    assert(false); // We should have not seen a pointer yet
                    break;
                case ScaleState::accepted:
                    break;
                case ScaleState::started:
                    assert(false); // We should be in the accepted state when user is done
                    break;
            }
            mScaleState = ScaleState::ready;
        }

        virtual void dispose() override {
            mVelocityTrackers.clear();
            OneSequenceGestureRecognizer::dispose();
        }

    };
}


#endif //WEEX_UIKIT_GESTURE_SCALEGESTURERECOGNIZER_H
