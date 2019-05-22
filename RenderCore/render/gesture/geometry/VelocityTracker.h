//
// Created by furture on 2018/10/18.
//

#ifndef WEEX_UIKIT_GESTURE_VELOCITYTRACKER_H
#define WEEX_UIKIT_GESTURE_VELOCITYTRACKER_H
#include <inttypes.h>
#include <cstdint>
#include <vector>
#include <memory>
#include "Geometry.h"
#include "LeastSquaresSolver.h"


namespace weexuikit {
/// A velocity in two dimensions.
    struct Velocity {
        /// The number of pixels per second of velocity in the x and y directions.
        Offset pixelsPerSecond;

        /// Return a velocity whose magnitude has been clamped to [minValue]
        /// and [maxValue].
        ///
        /// If the magnitude of this Velocity is less than minValue then return a new
        /// Velocity with the same direction and with magnitude [minValue]. Similarly,
        /// if the magnitude of this Velocity is greater than maxValue then return a
        /// new Velocity with the same direction and magnitude [maxValue].
        ///
        /// If the magnitude of this Velocity is within the specified bounds then
        /// just return this.
        Velocity clampMagnitude(double minValue, double maxValue) {
            assert(minValue >= 0.0);
            assert(maxValue >= 0.0 && maxValue >= minValue);
            double valueSquared = pixelsPerSecond.distanceSquared();
            if (valueSquared > maxValue * maxValue) {
                Offset velocityOffset = (pixelsPerSecond / pixelsPerSecond.distance()) * maxValue;
                Velocity velocity = {velocityOffset};
                return velocity;
            }
            if (valueSquared < minValue * minValue) {
                Velocity velocity = {(pixelsPerSecond / pixelsPerSecond.distance()) * minValue};
                return velocity;
            }
            return *this;
        }

    };


/// A two dimensional velocity estimate.
///
/// VelocityEstimates are computed by [VelocityTracker.getVelocityEstimate]. An
/// estimate's [confidence] measures how well the velocity tracker's position
/// data fit a straight line, [duration] is the time that elapsed between the
/// first and last position sample used to compute the velocity, and [offset]
/// is similarly the difference between the first and last positions.
///
/// See also:
///
///  * VelocityTracker, which computes [VelocityEstimate]s.
///  * Velocity, which encapsulates (just) a velocity vector and provides some
///    useful velocity operations.
    struct VelocityEstimate {
        /// The number of pixels per second of velocity in the x and y directions.
        Offset pixelsPerSecond;

        /// A value between 0.0 and 1.0 that indicates how well [VelocityTracker]
        /// was able to fit a straight line to its position data.
        ///
        /// The value of this property is 1.0 for a perfect fit, 0.0 for a poor fit.
        double confidence;

        /// The time that elapsed between the first and last position sample used
        /// to compute [pixelsPerSecond].
        int64_t duration;

        /// The difference between the first and last position sample used
        /// to compute [pixelsPerSecond].
        Offset offset;
    };


    struct PointAtTime {
        int64_t time;
        Offset point;
    };

/// Computes a pointer's velocity based on data from [PointerMoveEvent]s.
///
/// The input data is provided by calling [addPosition]. Adding data is cheap.
///
/// To obtain a velocity, call [getVelocity] or [getVelocityEstimate]. This will
/// compute the velocity based on the data added so far. Only call these when
/// you need to use the velocity, as they are comparatively expensive.
///
/// The quality of the velocity estimation will be better if more data points
/// have been received.

    class VelocityTracker {

        static const int mAssumePointerMoveStoppedMilliseconds = 40;
        static const int mHistorySize = 20;
        static const int mHorizonMilliseconds = 100;
        static const int mMinSampleSize = 3;

    public:
        VelocityTracker();

        ~VelocityTracker();

        /// Adds a position as the given time to the tracker.
        void addPosition(int64_t time, Offset position);


        /// Returns an estimate of the velocity of the object being tracked by the
        /// tracker given the current information available to the tracker.
        ///
        /// Information is added using [addPosition].
        ///
        /// Returns null if there is no data on which to base an estimate.
        VelocityEstimate *getVelocityEstimate();

        /// Computes the velocity of the pointer at the time of the last
        /// provided data point.
        ///
        /// This can be expensive. Only call this when you need the velocity.
        ///
        /// Returns [Velocity.zero] if there is no data from which to compute an
        /// estimate or if the estimated velocity is zero.
        Velocity getVelocity();

    private:
        PointAtTime **mSamples;
        int mIndex = 0;

    };
}


#endif //WEEX_UIKIT_GESTURE_VELOCITYTRACKER_H
