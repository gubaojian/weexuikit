//
// Created by furture on 2018/10/19.
//

#ifndef WEEX_UIKIT_GESTURE_HORIZONTALDRAGGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_HORIZONTALDRAGGESTURERECOGNIZER_H
#include "DragGestureRecognizer.h"


namespace weexuikit {
/// Recognizes movement in the horizontal direction.
///
/// Used for horizontal scrolling.
///
/// See also:
///
///  * [VerticalDragGestureRecognizer], for a similar recognizer but for
///    vertical movement.
///  * [MultiDragGestureRecognizer], for a family of gesture recognizers that
///    track each touch point independently.
    class HorizontalDragGestureRecognizer : public DragGestureRecognizer {
    public:
        HorizontalDragGestureRecognizer(GestureHandlerContext *gestureContext);

        ~HorizontalDragGestureRecognizer();


        virtual bool _isFlingGesture(VelocityEstimate *estimate) override {
            double minVelocity = mMinFlingVelocity;
            double minDistance = mMinFlingDistance;
            return std::abs(estimate->pixelsPerSecond.dx) > minVelocity &&
                   std::abs(estimate->offset.dx) > minDistance;

        }

        virtual Offset _getDeltaForDetails(const Offset &delta) override {
            return Offset(delta.dx, 0.0);
        }

        virtual double _getPrimaryValueFromOffset(const Offset &value) override {
            return value.dx;
        }

        virtual bool getHasSufficientPendingDragDeltaToAccept() override {
            return std::abs(mPendingDragOffset.dx) > kTouchSlop;
        }

    };

}


#endif //WEEX_UIKIT_GESTURE_HORIZONTALDRAGGESTURERECOGNIZER_H
