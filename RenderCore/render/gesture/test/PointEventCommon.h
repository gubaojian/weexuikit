//
// Created by furture on 2018/10/19.
//

#ifndef WEEX_UIKIT_GESTURE_POINTEVENTCOMMON_H
#define WEEX_UIKIT_GESTURE_POINTEVENTCOMMON_H

#include "../gesture/PointerEvent.h"

PointerEvent createPointerEvent(PointerEvent::PointerAction action){
    PointerEvent pointerEvent;
    pointerEvent.action =action;
    pointerEvent.position = makeOffset(10, 10);
    if(action != PointerEvent::ActionPointerDown){
        pointerEvent.delta.dx = 10;
        pointerEvent.delta.dy = 10;
    }else{
        pointerEvent.delta.dx = 0;
        pointerEvent.delta.dy = 0;
    }
    pointerEvent.pointer = 0;
    pointerEvent.timeStamp  = 1;
    return pointerEvent;
}

PointerEvent movePointetEvent(PointerEvent& pointerEvent, double dx, double dy){
    pointerEvent.timeStamp += 8;
    Offset position = pointerEvent.position;
    pointerEvent.position.dx += dx;
    pointerEvent.position.dy +=dy;
    pointerEvent.delta.dx = dx;
    pointerEvent.delta.dy = dy;
    return pointerEvent;
}


PointerEvent createPointerStep(PointerEvent::PointerAction action){
    PointerEvent pointerEvent;
    pointerEvent.action =action;
    pointerEvent.position = makeOffset(100, 100);
    pointerEvent.pointer = 0;
    pointerEvent.delta.dx = 100;
    pointerEvent.delta.dy = 100;
    pointerEvent.timeStamp  = 1;
    return pointerEvent;
}

#endif //WEEX_UIKIT_GESTURE_POINTEVENTCOMMON_H
