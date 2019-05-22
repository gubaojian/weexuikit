//
// Created by furture on 2018/10/19.
//

#ifndef WEEX_UIKIT_GESTURE_VERTICALDRAGGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_VERTICALDRAGGESTURERECOGNIZER_H
#include "DragGestureRecognizer.h"

/// Recognizes movement in the vertical direction.
///
/// Used for vertical scrolling.
///
/// See also:
///
///  * [HorizontalDragGestureRecognizer], for a similar recognizer but for
///    horizontal movement.
///  * [MultiDragGestureRecognizer], for a family of gesture recognizers that
///    track each touch point independently.
namespace weexuikit {

    class VerticalDragGestureRecognizer : public DragGestureRecognizer {
    public:
        VerticalDragGestureRecognizer(GestureHandlerContext *gestureContext);

        ~VerticalDragGestureRecognizer();


        virtual bool _isFlingGesture(VelocityEstimate *estimate) override;

        virtual Offset _getDeltaForDetails(const Offset &delta) override;

        virtual double _getPrimaryValueFromOffset(const Offset &value) override {
            return value.dy;
        }

        virtual bool getHasSufficientPendingDragDeltaToAccept() override {
            return std::abs(mPendingDragOffset.dy) > kTouchSlop;
        }
    };
}


#endif //WEEX_UIKIT_GESTURE_VERTICALDRAGGESTURERECOGNIZER_H
