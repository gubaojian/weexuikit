//
// Created by furture on 2018/10/20.
//

#include "EagerGestureRecognizer.h"

namespace weexuikit {
    EagerGestureRecognizer::EagerGestureRecognizer(GestureHandlerContext *gestureContext)
            : OneSequenceGestureRecognizer(gestureContext) {

    }

    void EagerGestureRecognizer::addPointer(const PointerEvent &event) {
        // We call startTrackingPointer as this is where OneSequenceGestureRecognizer joins the arena.
        startTrackingPointer(event.pointer);
        resolve(GestureDisposition::accepted);
        stopTrackingPointer(event.pointer);
    }

    EagerGestureRecognizer::~EagerGestureRecognizer() {
        dispose();
    }
}