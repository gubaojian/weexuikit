//
// Created by furture on 2018/10/16.
//

#ifndef WEEX_UIKIT_GESTURE_POINTERROUTE_H
#define WEEX_UIKIT_GESTURE_POINTERROUTE_H
#include "PointerEvent.h"
#include <functional>

namespace weexuikit {
    class PointerRoute {

    public:
        virtual void route(const PointerEvent &event) = 0;
    };
}


#endif //WEEX_UIKIT_GESTURE_POINTERROUTE_H
