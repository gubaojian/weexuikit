//
// Created by furture on 2018/10/30.
//

#ifndef WEEX_UIKIT_GESTURE_POINTEREVENTLISTENER_H
#define WEEX_UIKIT_GESTURE_POINTEREVENTLISTENER_H
#include "PointerEvent.h"

namespace weexuikit {

    class PointerEventListener {

    public:
        virtual void onPointerEvent(PointerEvent &pointerEvent)=0;
    };
}


#endif //WEEX_UIKIT_GESTURE_POINTEREVENTLISTENER_H
