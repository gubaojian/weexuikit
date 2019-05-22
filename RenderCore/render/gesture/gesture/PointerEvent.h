//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_POINTEREVENT_H
#define WEEX_UIKIT_GESTURE_POINTEREVENT_H
#include <inttypes.h>
#include "../geometry/Geometry.h"

namespace weexuikit {

    class PointerEvent {

    public:
        enum class PointerAction {
            ActionPointerDown = 0,
            ActionPointerMove = 1,
            ActionPointerUp = 2,
            ActionPointerCancel = 3,
        };


    public:
        PointerEvent() {
            toolType = 0;
            timeStamp = 0;
            position.dx = 0;
            position.dy = 0;
            delta.dx = 0;
            delta.dy = 0;
            synthesized = 0;
            pressure = 0;
        }

        inline bool isUpEvent() const {
            return action == PointerAction::ActionPointerUp;
        }

        inline bool isMoveEvent() const {
            return action == PointerAction::ActionPointerMove;
        }

        inline bool isCancelEvent() const {
            return action == PointerAction::ActionPointerCancel;
        }

        inline bool isDownEvent() const {
            return action == PointerAction::ActionPointerDown;
        }

    public:
        PointerAction action;
        int64_t timeStamp;
        int toolType;
        int pointer;

        /// Coordinate of the position of the pointer, in logical pixels in the global
        /// coordinate space.
        Offset position;

        /// Distance in logical pixels that the pointer moved since the last
        /// PointerMoveEvent. Always 0.0 for down, up, and cancel events.
        Offset delta;

        double pressure;
        float axisX;
        float axisY;
        float toolMajor;
        float toolMinor;

        /// We occasionally synthesize PointerEvents that aren't exact translations
        /// of [ui.PointerData] from the engine to cover small cross-OS discrepancies
        /// in pointer behaviors.
        ///
        /// For instance, on end events, Android always drops any location changes
        /// that happened between its reporting intervals when emitting the end events.
        ///
        /// On iOS, minor incorrect location changes from the previous move events
        /// can be reported on end events. We synthesize a [PointerEvent] to cover
        /// the difference between the 2 events in that case.
        bool synthesized;
    };

}

#endif //WEEX_UIKIT_GESTURE_POINTEREVENT_H
