//
// Created by furture on 2018/10/26.
//

#ifndef WEEX_UIKIT_GESTURE_BOUNCINGSCROLLSIMULATION_H
#define WEEX_UIKIT_GESTURE_BOUNCINGSCROLLSIMULATION_H
#include "../physics/Simulation.h"
#include "../physics/FrictionSimulation.h"
#include "../physics/SpringSimulation.h"
#include "../foundation/StandardExtension.h"
#include <cmath>

namespace weexuikit {
/// An implementation of scroll physics that matches iOS.
///
/// See also:
///
///  * [ClampingScrollSimulation], which implements Android scroll physics.
    class BouncingScrollSimulation : public Simulation {

        /// Creates a simulation group for scrolling on iOS, with the given
        /// parameters.
        ///
        /// The position and velocity arguments must use the same units as will be
        /// expected from the [x] and [dx] methods respectively (typically logical
        /// pixels and logical pixels per second respectively).
        ///
        /// The leading and trailing extents must use the unit of length, the same
        /// unit as used for the position argument and as expected from the [x]
        /// method (typically logical pixels).
        ///
        /// The units used with the provided [SpringDescription] must similarly be
        /// consistent with the other arguments. A default set of constants is used
        /// for the `spring` description if it is omitted; these defaults assume
        /// that the unit of length is the logical pixel.

    public:
        BouncingScrollSimulation(double position, double velocity, double leadingExtent,
                                 double trailingExtent, SpringDescription *spring,
                                 Tolerance *tolerance = Tolerance::getDefaultTolerance())
                : Simulation(tolerance) {
            this->mLeadingExtent = leadingExtent;
            this->mTrailingExtent = trailingExtent;
            this->mSpring = spring;
            if (position < leadingExtent) {
                mSpringSimulation = underscrollSimulation(position, velocity);
                mSpringTime = -INFINITY;
            } else if (position > trailingExtent) {
                mSpringSimulation = overscrollSimulation(position, velocity);
                mSpringTime = -INFINITY;
            } else {
                mFrictionSimulation = new FrictionSimulation(0.135, position, velocity);
                double finalX = mFrictionSimulation->finalX();
                if (velocity > 0.0 && finalX > trailingExtent) {
                    mSpringTime = mFrictionSimulation->timeAtX(trailingExtent);
                    mSpringSimulation = overscrollSimulation(
                            trailingExtent,
                            std::min(mFrictionSimulation->dx(mSpringTime),
                                     maxSpringTransferVelocity));
                } else if (velocity < 0.0 && finalX < leadingExtent) {
                    mSpringTime = mFrictionSimulation->timeAtX(leadingExtent);
                    mSpringSimulation = underscrollSimulation(
                            leadingExtent,
                            std::min(mFrictionSimulation->dx(mSpringTime),
                                     maxSpringTransferVelocity));
                } else {
                    mSpringTime = INFINITY;
                }
            }
        }

    public:
        /// The maximum velocity that can be transferred from the inertia of a ballistic
        /// scroll into overscroll.
        static double maxSpringTransferVelocity;

        /// When [x] falls below this value the simulation switches from an internal friction
        /// model to a spring model which causes [x] to "spring" back to [leadingExtent].
        double mLeadingExtent;

        /// When [x] exceeds this value the simulation switches from an internal friction
        /// model to a spring model which causes [x] to "spring" back to [trailingExtent].
        double mTrailingExtent;

        /// The spring used used to return [x] to either [leadingExtent] or [trailingExtent].
        SpringDescription *mSpring;

        FrictionSimulation *mFrictionSimulation;
        Simulation *mSpringSimulation;
        double mSpringTime;
        double mTimeOffset = 0.0;

        Simulation* underscrollSimulation(double x, double dx) {
            return new ScrollSpringSimulation(mSpring, x, mLeadingExtent, dx);
        }

        Simulation* overscrollSimulation(double x, double dx) {
            return new ScrollSpringSimulation(mSpring, x, mTrailingExtent, dx);
        }

        Simulation* simulation(double time) {
            Simulation *simulation;
            if (time > mSpringTime) {
                mTimeOffset = std::isfinite(mSpringTime) ? mSpringTime : 0.0;
                simulation = mSpringSimulation;
            } else {
                mTimeOffset = 0.0;
                simulation = mFrictionSimulation;
            }
            if (simulation->mTolerance == nullptr) {
                simulation->mTolerance = mTolerance;
            }
            return simulation;
        }


        virtual double x(double time) override {
            return simulation(time)->x(time - mTimeOffset);
        }


        virtual double dx(double time) override {
            return simulation(time)->dx(time - mTimeOffset);
        }


        virtual bool isDone(double time) override {
            return simulation(time)->isDone(time - mTimeOffset);
        }

    };

/// An implementation of scroll physics that matches Android.
///
/// See also:
///
///  * [BouncingScrollSimulation], which implements iOS scroll physics.
//
// This class is based on Scroller.java from Android:
//   https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/widget
//
// The "See..." comments below refer to Scroller methods and values. Some
// simplifications have been made.
    class ClampingScrollSimulation : public Simulation {

    public:
        /// Creates a scroll physics simulation that matches Android scrolling.
        ClampingScrollSimulation(double position, double velocity, double friction = 0.015,
                                 Tolerance *tolerance = Tolerance::getDefaultTolerance())
                : Simulation(tolerance) {
            assert(_flingVelocityPenetration(0.0) == _initialVelocityPenetration);
            this->mPosition = position;
            this->mVelocity = velocity;
            this->mFriction = friction;
            this->mDuration = flingDuration(velocity);
            this->mDistance = std::abs((velocity * mDuration / _initialVelocityPenetration));
        }

        // See computeDeceleration().
        static double decelerationForFriction(double friction) {
            return friction * 61774.04968;
        }

        // See getSplineFlingDuration(). Returns a value in seconds.
        double flingDuration(double velocity) {
            // See mPhysicalCoeff
            double scaledFriction = mFriction * decelerationForFriction(0.84);

            // See getSplineDeceleration().
            double deceleration = std::log(0.35 * std::abs(velocity) / scaledFriction);

            return std::exp(deceleration / (mKDecelerationRate - 1.0));
        }

        // Based on a cubic curve fit to the Scroller.computeScrollOffset() values
        // produced for an initial velocity of 4000. The value of Scroller.getDuration()
        // and Scroller.getFinalY() were 686ms and 961 pixels respectively.
        //
        // Algebra courtesy of Wolfram Alpha.
        //
        // f(x) = scrollOffset, x is time in milliseconds
        // f(x) = 3.60882×10^-6 x^3 - 0.00668009 x^2 + 4.29427 x - 3.15307
        // f(x) = 3.60882×10^-6 x^3 - 0.00668009 x^2 + 4.29427 x, so f(0) is 0
        // f(686ms) = 961 pixels
        // Scale to f(0 <= t <= 1.0), x = t * 686
        // f(t) = 1165.03 t^3 - 3143.62 t^2 + 2945.87 t
        // Scale f(t) so that 0.0 <= f(t) <= 1.0
        // f(t) = (1165.03 t^3 - 3143.62 t^2 + 2945.87 t) / 961.0
        //      = 1.2 t^3 - 3.27 t^2 + 3.065 t
        static constexpr double _initialVelocityPenetration = 3.065;

        static double _flingDistancePenetration(double t) {
            return (1.2 * t * t * t) - (3.27 * t * t) + (_initialVelocityPenetration * t);
        }

        // The derivative of the _flingDistancePenetration() function.
        static double _flingVelocityPenetration(double t) {
            return (3.6 * t * t) - (6.54 * t) + _initialVelocityPenetration;
        }


        virtual double x(double time) override {
            double t = std::clamp((time / mDuration), 0.0, 1.0);
            return mPosition + mDistance * _flingDistancePenetration(t) * math_sign(mVelocity);
        }


        virtual double dx(double time) override {
            double t = std::clamp((time / mDuration), 0.0, 1.0);
            return mDistance * _flingVelocityPenetration(t) * math_sign(mVelocity) / mDuration;
        }


        virtual bool isDone(double time) override {
            return time >= mDuration;
        }

    public:
        /// The position of the particle at the beginning of the simulation.
        double mPosition;

        /// The velocity at which the particle is traveling at the beginning of the
        /// simulation.
        double mVelocity;

        /// The amount of friction the particle experiences as it travels.
        ///
        /// The more friction the particle experiences, the sooner it stops.
        double mFriction;

        double mDuration;
        double mDistance;

        // See DECELERATION_RATE.
        static double mKDecelerationRate;
    };
}


#endif //WEEX_UIKIT_GESTURE_BOUNCINGSCROLLSIMULATION_H
