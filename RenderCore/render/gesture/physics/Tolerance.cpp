//
// Created by furture on 2018/10/23.
//

#include "Tolerance.h"

namespace weexuikit {
    Tolerance *Tolerance::defaultTolerance = nullptr;

    Tolerance::Tolerance() {
        this->distance = _epsilonDefault;
        this->time = _epsilonDefault;
        this->velocity = _epsilonDefault;
    }

    Tolerance::Tolerance(double distance, double time, double velocity) {
        this->distance = distance;
        this->time = time;
        this->velocity = velocity;
    }

    Tolerance *Tolerance::getDefaultTolerance() {
        if (defaultTolerance == nullptr) {
            defaultTolerance = new Tolerance();
        }
        return defaultTolerance;
    }
}