//
// Created by furture on 2018/10/27.
//

#ifndef WEEX_UIKIT_GESTURE_FRICTIONSIMULATION_H
#define WEEX_UIKIT_GESTURE_FRICTIONSIMULATION_H
#include "Simulation.h"
#include "../foundation/BasicTypes.h"
#include "../foundation/StandardExtension.h"
#include <cmath>
#include <algorithm>



namespace weexuikit {
/// A simulation that applies a drag to slow a particle down.
///
/// Models a particle affected by fluid drag, e.g. air resistance.
///
/// The simulation ends when the velocity of the particle drops to zero (within
/// the current velocity [tolerance]).
    class FrictionSimulation : public Simulation {


    public:
/// Creates a [FrictionSimulation] with the given arguments, namely: the fluid
/// drag coefficient, a unitless value; the initial position, in the same
/// length units as used for [x]; and the initial velocity, in the same
/// velocity units as used for [dx].
        FrictionSimulation(double drag, double position, double velocity,
                           Tolerance *tolerance = Tolerance::getDefaultTolerance()) {
            _drag = drag;
            _dragLog = std::log(drag);
            _x = position;
            _v = velocity;
            this->mTolerance = tolerance;
        }


/// Creates a new friction simulation with its fluid drag coefficient set so
/// as to ensure that the simulation starts and ends at the specified
/// positions and velocities.
///
/// The positions must use the same units as expected from [x], and the
/// velocities must use the same units as expected from [dx].
///
/// The sign of the start and end velocities must be the same, the magnitude
/// of the start velocity must be greater than the magnitude of the end
/// velocity, and the velocities must be in the direction appropriate for the
/// particle to start from the start position and reach the end position.
        FrictionSimulation *
        FrictionSimulationThrough(double startPosition, double endPosition, double startVelocity,
                                  double endVelocity) {
            assert(startVelocity == 0.0 || endVelocity == 0.0 ||
                   math_sign(startVelocity) == math_sign(endVelocity));
            assert(std::abs(startVelocity) >= std::abs(endVelocity));
            assert(math_sign(endPosition - startPosition) == math_sign(startVelocity));

            Tolerance *tolerance = new Tolerance();
            tolerance->velocity = std::abs(endVelocity);
            return new FrictionSimulation(
                    _dragFor(startPosition, endPosition, startVelocity, endVelocity),
                    startPosition,
                    startVelocity,
                    tolerance);
        }

    public:
        double _drag;
        double _dragLog;
        double _x;
        double _v;

// Return the drag value for a FrictionSimulation whose x() and dx() values pass
// through the specified start and end position/velocity values.
//
// Total time to reach endVelocity is just: (log(endVelocity) / log(startVelocity)) / log(_drag)
// or (log(v1) - log(v0)) / log(D), given v = v0 * D^t per the dx() function below.
// Solving for D given x(time) is trickier. Algebra courtesy of Wolfram Alpha:
// x1 = x0 + (v0 * D^((log(v1) - log(v0)) / log(D))) / log(D) - v0 / log(D), find D
        static double _dragFor(double startPosition, double endPosition, double startVelocity,
                               double endVelocity) {
            return std::pow(M_E, (startVelocity - endVelocity) / (startPosition - endPosition));
        }


        virtual double x(double time) override {
            return _x + _v * std::pow(_drag, time) / _dragLog - _v / _dragLog;
        }

        virtual double dx(double time) override {
            return _v * std::pow(_drag, time);
        }

/// The value of [x] at `double.infinity`.
        virtual double finalX() {
            return _x - _v / _dragLog;
        }

/// The time at which the value of `x(time)` will equal [x].
///
/// Returns `double.infinity` if the simulation will never reach [x].
        double timeAtX(double x) {
            if (x == _x)
                return 0.0;
            if (_v == 0.0 || (_v > 0 ? (x < _x || x > finalX()) : (x > _x || x < finalX())))
                return INFINITY;
            return std::log(_dragLog * (x - _x) / _v + 1.0) / _dragLog;
        }


        virtual bool isDone(double time) override {
            return std::abs(dx(time)) < mTolerance->velocity;
        }
    };

/// A [FrictionSimulation] that clamps the modeled particle to a specific range
/// of values.
    class BoundedFrictionSimulation : public FrictionSimulation {


    public:
        /// Creates a [BoundedFrictionSimulation] with the given arguments, namely:
        /// the fluid drag coefficient, a unitless value; the initial position, in the
        /// same length units as used for [x]; the initial velocity, in the same
        /// velocity units as used for [dx], the minimum value for the position, and
        /// the maximum value for the position. The minimum and maximum values must be
        /// in the same units as the initial position, and the initial position must
        /// be within the given range.
        BoundedFrictionSimulation(
                double drag,
                double position,
                double velocity, double minX, double maxX) : FrictionSimulation(drag, position,
                                                                                velocity) {
            assert(std::clamp(position, minX, maxX) == position);
            this->_minX = minX;
            this->_maxX = maxX;
        }

    public:
        double _minX;
        double _maxX;


        virtual double x(double time) override {
            return std::clamp(FrictionSimulation::x(time), _minX, _maxX);
        }


        virtual bool isDone(double time) override {
            return FrictionSimulation::isDone(time) ||
                   std::abs(x(time) - _minX) < mTolerance->distance ||
                   std::abs(x(time) - _maxX) < mTolerance->distance;
        }
    };

}


#endif //WEEX_UIKIT_GESTURE_FRICTIONSIMULATION_H
