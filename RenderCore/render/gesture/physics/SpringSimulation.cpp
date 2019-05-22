//
// Created by furture on 2018/10/25.
//

#include "SpringSimulation.h"
#include "../foundation/BasicTypes.h"


namespace weexuikit {

    SpringSimulation::SpringSimulation(SpringDescription *spring,
                                       double start, double end,
                                       double velocity,
                                       Tolerance *tolerance) {
        this->mEndPosition = end;
        this->mTolerance = tolerance;
        this->mSolution = SpringSolution::makeSpringSolution(spring, start - end, velocity);
    }


    SpringType SpringSimulation::getType() {
        return mSolution->getType();
    }

    double SpringSimulation::x(double time) {
        return mEndPosition + mSolution->x(time);
    }

    double SpringSimulation::dx(double time) {
        return mSolution->dx(time);
    }

    bool SpringSimulation::isDone(double time) {
        return nearZero(mSolution->x(time), mTolerance->distance) &&
               nearZero(mSolution->dx(time), mTolerance->velocity);
    }

    SpringSolution* SpringSolution::makeSpringSolution(SpringDescription *spring, double initialPosition,
                                        double initialVelocity) {
        assert(spring != nullptr);
        double cmk = spring->mDamping * spring->mDamping - 4 * spring->mass * spring->stiffness;
        if (cmk == 0.0)
            return CriticalSolution::makeCriticalSolution(spring, initialPosition,
                                                           initialVelocity);
        if (cmk > 0.0)
            return OverdampedSolution::makeOverdampedSolution(spring, initialPosition,
                                                               initialVelocity);
        return UnderdampedSolution::makeUnderdampedSolution(spring, initialPosition,
                                                             initialVelocity);
    }
}