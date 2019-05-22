//
// Created by furture on 2018/10/24.
//

#ifndef WEEX_UIKIT_GESTURE_DRAG_H
#define WEEX_UIKIT_GESTURE_DRAG_H

#include "../gesture/DragGestureRecognizer.h"


namespace weexuikit {

/// Interface for objects that receive updates about drags.
///
/// This interface is used in various ways. For example,
/// [MultiDragGestureRecognizer] uses it to update its clients when it
/// recognizes a gesture. Similarly, the scrolling infrastructure in the widgets
/// library uses it to notify the [DragScrollActivity] when the user drags the
/// scrollable.
    class Drag {


    public:
        /// The pointer has moved.
        virtual void update(const DragUpdateDetails &details) {}

        /// The pointer is no longer in contact with the screen.
        ///
        /// The velocity at which the pointer was moving when it stopped contacting
        /// the screen is available in the `details`.
        virtual void end(const DragEndDetails &details) {}

        /// The input from the pointer is no longer directed towards this receiver.
        ///
        /// For example, the user might have been interrupted by a system-modal dialog
        /// in the middle of the drag.
        virtual void cancel() {}
    };

}
#endif //WEEX_UIKIT_GESTURE_DRAG_H
