//
// Created by furture on 2018/10/26.
//

#include "BouncingScrollSimulation.h"

namespace weexuikit {
    double ClampingScrollSimulation::mKDecelerationRate = std::log(0.78) / std::log(0.9);

    double BouncingScrollSimulation::maxSpringTransferVelocity = 5000.0;
//double ClampingScrollSimulation::_initialVelocityPenetration = 3.065;

}
