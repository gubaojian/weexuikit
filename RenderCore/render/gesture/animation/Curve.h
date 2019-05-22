//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_CURVE_H
#define WEEX_UIKIT_GESTURE_CURVE_H
#include <algorithm>
#include <cmath>
#include <math.h>
#include <cassert>
#include "../foundation/StandardExtension.h"

namespace weexuikit {


/// A mapping of the unit interval to the unit interval.
///
/// A curve must map t=0.0 to 0.0 and t=1.0 to 1.0.
///
/// See [Curves] for a collection of common animation curves.
    class Curve {

    public:
        Curve() {};

    public:
        /// Returns the value of the curve at point `t`.
        ///
        /// The value of `t` must be between 0.0 and 1.0, inclusive. Subclasses should
        /// assert that this is true.
        ///
        /// A curve must map t=0.0 to 0.0 and t=1.0 to 1.0.
        virtual double transform(double t) {
            return t;
        };

    };


/// The identity map over the unit interval.
///
/// See [Curves.linear] for an instance of this class.
    class Linear : public Curve {

    public:
        Linear() {};

    public:
        virtual double transform(double t) override {
            return t;
        }
    };


/// A sawtooth curve that repeats a given number of times over the unit interval.
///
/// The curve rises linearly from 0.0 to 1.0 and then falls discontinuously back
/// to 0.0 each iteration.
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_sawtooth.mp4}
    class SawTooth : public Curve {


    public:
        /// Creates a sawtooth curve.
        ///
        /// The [count] argument must not be null.
        SawTooth(int c) : mCount(c) {}

    public:
        /// The number of repetitions of the sawtooth pattern in the unit interval.
        int mCount;

        virtual double transform(double t) override {
            if (t == 1.0)
                return 1.0;
            t *= mCount;
            return t - trunc(t);
        }

    };


/// A curve that is 0.0 until [begin], then curved (according to [curve] from
/// 0.0 to 1.0 at [end], then 1.0.
///
/// An [Interval] can be used to delay an animation. For example, a six second
/// animation that uses an [Interval] with its [begin] set to 0.5 and its [end]
/// set to 1.0 will essentially become a three-second animation that starts
/// three seconds later.
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_interval.mp4}
    class Interval : public Curve {

    public:
        /// Creates an interval curve.
        ///
        /// The arguments must not be null.
        Interval(double begin, double end, Curve cur) {
            this->mBegin = begin;
            this->mEnd = end;
            this->mCurve = cur;
        }

    public:
        /// The largest value for which this interval is 0.0.
        ///
        /// From t=0.0 to t=`begin`, the interval's value is 0.0.
        double mBegin;

        /// The smallest value for which this interval is 1.0.
        ///
        /// From t=`end` to t=1.0, the interval's value is 1.0.
        double mEnd;

        /// The curve to apply between [begin] and [end].
        Curve mCurve;

        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            assert(mBegin >= 0.0);
            assert(mBegin <= 1.0);
            assert(mEnd >= 0.0);
            assert(mEnd <= 1.0);
            assert(mEnd >= mBegin);
            if (t == 0.0 || t == 1.0)
                return t;
            t = std::clamp(((t - mBegin) / (mEnd - mBegin)), 0.0, 1.0);
            if (t == 0.0 || t == 1.0)
                return t;
            return mCurve.transform(t);
        }

    };

/// A curve that is 0.0 until it hits the threshold, then it jumps to 1.0.
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_threshold.mp4}
    class Threshold : public Curve {

    public:
        /// Creates a threshold curve.
        ///
        /// The [threshold] argument must not be null.
        Threshold(double _threshold) : mThreshold(_threshold) {

        }

        /// The value before which the curve is 0.0 and after which the curve is 1.0.
        ///
        /// When t is exactly [threshold], the curve has the value 1.0.
        double mThreshold;


        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            assert(mThreshold >= 0.0);
            assert(mThreshold <= 1.0);
            if (t == 0.0 || t == 1.0)
                return t;
            return t < mThreshold ? 0.0 : 1.0;
        }
    };


/// A cubic polynomial mapping of the unit interval.
///
/// The [Curves] class contains some commonly used cubic curves:
///
///  * [Curves.ease]
///  * [Curves.easeIn]
///  * [Curves.easeOut]
///  * [Curves.easeInOut]
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_in.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_in_out.mp4}
///
/// The [Cubic] class implements third-order Bézier curves.
    class Cubic : public Curve {

    public:
        /// Creates a cubic curve.
        ///
        /// Rather than creating a new instance, consider using one of the common
        /// cubic curves in [Curves].
        ///
        /// The [a], [b], [c], and [d] arguments must not be null.
        Cubic(double a, double b, double c, double d) {
            this->a = a;
            this->b = b;
            this->c = c;
            this->d = d;
        }

    public:
        /// The x coordinate of the first control point.
        ///
        /// The line through the point (0, 0) and the first control point is tangent
        /// to the curve at the point (0, 0).
        double a;

        /// The y coordinate of the first control point.
        ///
        /// The line through the point (0, 0) and the first control point is tangent
        /// to the curve at the point (0, 0).
        double b;

        /// The x coordinate of the second control point.
        ///
        /// The line through the point (1, 1) and the second control point is tangent
        /// to the curve at the point (1, 1).
        double c;

        /// The y coordinate of the second control point.
        ///
        /// The line through the point (1, 1) and the second control point is tangent
        /// to the curve at the point (1, 1).
        double d;

        static constexpr double kCubicErrorBound = 0.001;

        double _evaluateCubic(double a, double b, double m) {
            return 3 * a * (1 - m) * (1 - m) * m +
                   3 * b * (1 - m) * m * m +
                   m * m * m;
        }

        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            double start = 0.0;
            double end = 1.0;
            while (true) {
                double midpoint = (start + end) / 2;
                double estimate = _evaluateCubic(a, c, midpoint);
                if (std::abs(t - estimate) < kCubicErrorBound)
                    return _evaluateCubic(b, d, midpoint);
                if (estimate < t)
                    start = midpoint;
                else
                    end = midpoint;
            }
        }

    };

/// A curve that is the reversed inversion of its given curve.
///
/// This curve evaluates the given curve in reverse (i.e., from 1.0 to 0.0 as t
/// increases from 0.0 to 1.0) and returns the inverse of the given curve's value
/// (i.e., 1.0 minus the given curve's value).
///
/// This is the class used to implement the [flipped] getter on curves.
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_in.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_flipped_curve.mp4}
    class FlippedCurve : public Curve {

    public:
        /// Creates a flipped curve.
        ///
        /// The [curve] argument must not be null.
        FlippedCurve(Curve cur) : mCurve(cur) {

        };

        /// The curve that is being flipped.
        Curve mCurve;


        virtual double transform(double t) override {
            return 1.0 - mCurve.transform(1.0 - t);
        }
    };


/// A curve where the rate of change starts out quickly and then decelerates; an
/// upside-down `f(t) = t²` parabola.
///
/// This is equivalent to the Android `DecelerateInterpolator` class with a unit
/// factor (the default factor).
///
/// See [Curves.decelerate] for an instance of this class.
    class DecelerateCurve : public Curve {

    public:
        DecelerateCurve() {}

        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            // Intended to match the behavior of:
            // https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/view/animation/DecelerateInterpolator.java
            // ...as of December 2016.
            t = 1.0 - t;
            return 1.0 - t * t;
        }
    };


// BOUNCE CURVES

    inline double _bounce(double t) {
        if (t < 1.0 / 2.75) {
            return 7.5625 * t * t;
        } else if (t < 2 / 2.75) {
            t -= 1.5 / 2.75;
            return 7.5625 * t * t + 0.75;
        } else if (t < 2.5 / 2.75) {
            t -= 2.25 / 2.75;
            return 7.5625 * t * t + 0.9375;
        }
        t -= 2.625 / 2.75;
        return 7.5625 * t * t + 0.984375;
    }


/// An oscillating curve that grows in magnitude.
///
/// See [Curves.bounceIn] for an instance of this class.
    class BounceInCurve : public Curve {

    public:
        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            return 1.0 - _bounce(1.0 - t);
        }
    };

/// An oscillating curve that shrink in magnitude.
///
/// See [Curves.bounceOut] for an instance of this class.
    class BounceOutCurve : public Curve {

    public:
        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            return _bounce(t);
        }
    };

/// An oscillating curve that first grows and then shrink in magnitude.
///
/// See [Curves.bounceInOut] for an instance of this class.
    class BounceInOutCurve : public Curve {

    public:
        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            if (t < 0.5)
                return (1.0 - _bounce(1.0 - t)) * 0.5;
            else
                return _bounce(t * 2.0 - 1.0) * 0.5 + 0.5;
        }
    };


// ELASTIC CURVES

/// An oscillating curve that grows in magnitude while overshooting its bounds.
///
/// An instance of this class using the default period of 0.4 is available as
/// [Curves.elasticIn].
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_in.mp4}
    class ElasticInCurve : public Curve {

    public:
        /// Creates an elastic-in curve.
        ///
        /// Rather than creating a new instance, consider using [Curves.elasticIn].
        ElasticInCurve(double period = 0.4) {
            this->mPeriod = period;
        }

    public:
        /// The duration of the oscillation.
        double mPeriod;


        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            double s = mPeriod / 4.0;
            t = t - 1.0;
            return -std::pow(2.0, 10.0 * t) * std::sin((t - s) * (M_PI * 2.0) / mPeriod);
        }
    };


/// An oscillating curve that shrinks in magnitude while overshooting its bounds.
///
/// An instance of this class using the default period of 0.4 is available as
/// [Curves.elasticOut].
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_out.mp4}
    class ElasticOutCurve : public Curve {


    public:
        /// Creates an elastic-out curve.
        ///
        /// Rather than creating a new instance, consider using [Curves.elasticOut].
        ElasticOutCurve(double period = 0.4) {
            this->mPeriod = period;
        }

        /// The duration of the oscillation.
        double mPeriod;

        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            double s = mPeriod / 4.0;
            return std::pow(2.0, -10 * t) * std::sin((t - s) * (M_PI * 2.0) / mPeriod) + 1.0;
        }
    };

/// An oscillating curve that grows and then shrinks in magnitude while
/// overshooting its bounds.
///
/// An instance of this class using the default period of 0.4 is available as
/// [Curves.elasticInOut].
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_in_out.mp4}
    class ElasticInOutCurve : public Curve {

    public:
        /// Creates an elastic-in-out curve.
        ///
        /// Rather than creating a new instance, consider using [Curves.elasticInOut].
        ElasticInOutCurve(double period = 0.4) {
            this->mPeriod = period;
        }

        /// The duration of the oscillation.
        double mPeriod;

        virtual double transform(double t) override {
            assert(t >= 0.0 && t <= 1.0);
            double s = mPeriod / 4.0;
            t = 2.0 * t - 1.0;
            if (t < 0.0)
                return -0.5 * std::pow(2.0, 10.0 * t) * std::sin((t - s) * (M_PI * 2.0) / mPeriod);
            else
                return std::pow(2.0, -10.0 * t) * std::sin((t - s) * (M_PI * 2.0) / mPeriod) * 0.5 +
                       1.0;
        }
    };

/// A collection of common animation curves.
///
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_in.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_in_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_decelerate.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_in.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_in_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_in.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_in_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_out.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_fast_out_slow_in.mp4}
/// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_linear.mp4}
///
/// See also:
///
///  * [Curve], the interface implemented by the constants available from the
///    [Curves] class.
    namespace Curves {
        /// A linear animation curve.
        ///
        /// This is the identity map over the unit interval: its [Curve.transform]
        /// method returns its input unmodified. This is useful as a default curve for
        /// cases where a [Curve] is required but no actual curve is desired.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_linear.mp4}
        static const Curve linear = Linear();

        /// A curve where the rate of change starts out quickly and then decelerates; an
        /// upside-down `f(t) = t²` parabola.
        ///
        /// This is equivalent to the Android `DecelerateInterpolator` class with a unit
        /// factor (the default factor).
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_decelerate.mp4}
        static const Curve decelerate = DecelerateCurve();

        /// A cubic animation curve that speeds up quickly and ends slowly.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease.mp4}
        static const Cubic ease = Cubic(0.25, 0.1, 0.25, 1.0);

        /// A cubic animation curve that starts slowly and ends quickly.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_in.mp4}
        static const Cubic easeIn = Cubic(0.42, 0.0, 1.0, 1.0);

        /// A cubic animation curve that starts quickly and ends slowly.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_out.mp4}
        static const Cubic easeOut = Cubic(0.0, 0.0, 0.58, 1.0);

        /// A cubic animation curve that starts slowly, speeds up, and then and ends slowly.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_ease_in_out.mp4}
        static const Cubic easeInOut = Cubic(0.42, 0.0, 0.58, 1.0);

        /// A curve that starts quickly and eases into its final position.
        ///
        /// Over the course of the animation, the object spends more time near its
        /// final destination. As a result, the user isn’t left waiting for the
        /// animation to finish, and the negative effects of motion are minimized.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_fast_out_slow_in.mp4}
        static const Cubic fastOutSlowIn = Cubic(0.4, 0.0, 0.2, 1.0);

        /// An oscillating curve that grows in magnitude.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_in.mp4}
        static const Curve bounceIn = BounceInCurve();

        /// An oscillating curve that first grows and then shrink in magnitude.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_out.mp4}
        static const Curve bounceOut = BounceOutCurve();

        /// An oscillating curve that first grows and then shrink in magnitude.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_bounce_in_out.mp4}
        static const Curve bounceInOut = BounceInOutCurve();

        /// An oscillating curve that grows in magnitude while overshooting its bounds.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_in.mp4}
        static const ElasticInCurve elasticIn = ElasticInCurve();

        /// An oscillating curve that shrinks in magnitude while overshooting its bounds.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_out.mp4}
        static const ElasticOutCurve elasticOut = ElasticOutCurve(0.4);

        /// An oscillating curve that grows and then shrinks in magnitude while overshooting its bounds.
        ///
        /// {@animation 464 192 https://flutter.github.io/assets-for-api-docs/assets/animation/curve_elastic_in_out.mp4}
        static const ElasticInOutCurve elasticInOut = ElasticInOutCurve();
    };

}

#endif //WEEX_UIKIT_GESTURE_CURVE_H
