//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_HANDLER_GESTURECONTEXT_H
#define WEEX_UIKIT_GESTURE_HANDLER_GESTURECONTEXT_H
#include "PointerRouter.h"
#include "GestureArenaManager.h"
#include "Timer.h"

namespace weexuikit {
    class GestureHandlerContext {

    public:
        GestureHandlerContext();

        ~GestureHandlerContext();

        void handleEvent(const PointerEvent &event);

        void checkTimer(int64_t now);

    public:
        PointerRouter *pointerRouter;
        GestureArenaManager *gestureArena;
        TimerManager *timerManager;
        /// State for all pointers which are currently down.
        ///
    };

}

#endif //WEEX_UIKIT_GESTURE_GESTURECONTEXT_H
