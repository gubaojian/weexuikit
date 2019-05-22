//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_CLAMPEDSIMULATION_H
#define WEEX_UIKIT_GESTURE_CLAMPEDSIMULATION_H
#include "Simulation.h"
#include "../foundation/StandardExtension.h"
#include <algorithm>



namespace weexuikit {
/// A simulation that applies limits to another simulation.
///
/// The limits are only applied to the other simulation's outputs. For example,
/// if a maximum position was applied to a gravity simulation with the
/// particle's initial velocity being up, and the acceleration being down, and
/// the maximum position being between the initial position and the curve's
/// apogee, then the particle would return to its initial position in the same
/// amount of time as it would have if the maximum had not been applied; the
/// difference would just be that the position would be reported as pinned to
/// the maximum value for the times that it would otherwise have been reported
/// as higher.
    class ClampedSimulation : public Simulation {


    public:
        /// The simulation being clamped. Calls to [x], [dx], and [isDone] are
        /// forwarded to the simulation.
        Simulation *simulation;

        /// The minimum to apply to [x].
        double xMin;

        /// The maximum to apply to [x].
        double xMax;

        /// The minimum to apply to [dx].
        double dxMin;

        /// The maximum to apply to [dx].
        double dxMax;


        virtual double x(double time) override {
            return std::clamp(simulation->x(time), xMin, xMax);
        }

        virtual double dx(double time) override {
            return std::clamp(simulation->dx(time), dxMin, dxMax);
        }


        bool isDone(double time) override {
            return simulation->isDone(time);
        }
    };

}

#endif //WEEX_UIKIT_GESTURE_CLAMPEDSIMULATION_H
