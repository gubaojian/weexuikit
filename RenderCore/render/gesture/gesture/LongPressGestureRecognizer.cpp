//
// Created by furture on 2018/10/22.
//

#include "LongPressGestureRecognizer.h"
#include "GestureConfig.h"

namespace weexuikit {
    LongPressGestureRecognizer::LongPressGestureRecognizer(GestureHandlerContext *gestureContext)
            : PrimaryPointerGestureRecognizer(gestureContext) {
        this->mDeadline = kLongPressTimeout;
    }


    void LongPressGestureRecognizer::didExceedDeadline() {
        resolve(GestureDisposition::accepted);
        if (onLongPress != nullptr) {
            onLongPress(mInitialEvent);
        }
    }

    void LongPressGestureRecognizer::handlePrimaryPointer(const PointerEvent &event) {
        if (event.isUpEvent()) {
            resolve(GestureDisposition::rejected);
        }
    }
}