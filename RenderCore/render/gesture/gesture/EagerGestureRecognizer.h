//
// Created by furture on 2018/10/20.
//

#ifndef WEEX_UIKIT_GESTURE_EAGERGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_EAGERGESTURERECOGNIZER_H
#include "OneSequenceGestureRecognizer.h"


namespace weexuikit {
/// A gesture recognizer that eagerly claims victory in all gesture arenas.
///
/// This is typically passed in [AndroidView.gestureRecognizers] in order to immediately dispatch
/// all touch events inside the view bounds to the embedded Android view.
/// See [AndroidView.gestureRecognizers] for more details.

    class EagerGestureRecognizer : public OneSequenceGestureRecognizer {

    public:
        EagerGestureRecognizer(GestureHandlerContext *gestureContext);

        ~EagerGestureRecognizer();

        void addPointer(const PointerEvent &event) override;

        virtual void didStopTrackingLastPointer(int pointer) override {}

        virtual void handleEvent(const PointerEvent &event) override {}

    };
}


#endif //WEEX_UIKIT_GESTURE_EAGERGESTURERECOGNIZER_H
