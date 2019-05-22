//
// Created by furture on 2018/10/11.
//

#include "GestureHandlerContext.h"

namespace weexuikit {


    GestureHandlerContext::GestureHandlerContext() {
        pointerRouter = new PointerRouter();
        gestureArena = new GestureArenaManager();
        timerManager = new TimerManager();
    }

    GestureHandlerContext::~GestureHandlerContext() {
        if (pointerRouter != nullptr) {
            delete pointerRouter;
            pointerRouter = nullptr;
        }

        if (gestureArena != nullptr) {
            delete gestureArena;
            gestureArena = nullptr;
        }
        if (timerManager != nullptr) {
            delete timerManager;
            timerManager = nullptr;
        }
    }

    void GestureHandlerContext::handleEvent(const PointerEvent &event) {
        pointerRouter->route(event);
        if (event.isDownEvent()) {
            gestureArena->close(event.pointer);
        } else if (event.isUpEvent()) {
            gestureArena->sweep(event.pointer);
        }
    }


    void GestureHandlerContext::checkTimer(int64_t now) {
        if (timerManager != nullptr) {
            timerManager->checkTimer(now);
        }
    }
}