//
// Created by furture on 2018/10/25.
//

#include "ScrollPhysics.h"

namespace weexuikit {
    static int devicePixelRatio = 1;


    SpringDescription *ScrollPhysics::kDefaultSpring = SpringDescription::withDampingRatio(0.5,
                                                                                           100.0,
                                                                                           1.1);

    Tolerance *ScrollPhysics::kDefaultTolerance = new Tolerance(1.0 / devicePixelRatio, 0,
                                                                1.0 / (0.050 * devicePixelRatio));


    ScrollPhysics::ScrollPhysics(ScrollPhysics *parent) {
        this->mParent = parent;
    }
}