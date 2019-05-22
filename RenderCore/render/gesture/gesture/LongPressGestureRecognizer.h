//
// Created by furture on 2018/10/22.
//

#ifndef WEEX_UIKIT_GESTURE_LONGPRESSGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_LONGPRESSGESTURERECOGNIZER_H



/// Signature for when a pointer has remained in contact with the screen at the
/// same location for a long period of time.
#include "PointerEvent.h"
#include "PrimaryPointerGestureRecognizer.h"

namespace weexuikit {


    using GestureLongPressCallback = std::function<void(const PointerEvent &)>;
/// Recognizes when the user has pressed down at the same location for a long
/// period of time.

    class LongPressGestureRecognizer : public PrimaryPointerGestureRecognizer {
    public:
        LongPressGestureRecognizer(GestureHandlerContext *gestureContext);

        /// Called when a long-press is recognized.
        GestureLongPressCallback onLongPress;


        virtual void didExceedDeadline() override;

        virtual void handlePrimaryPointer(const PointerEvent &event) override;
    };
}


#endif //WEEX_UIKIT_GESTURE_LONGPRESSGESTURERECOGNIZER_H
