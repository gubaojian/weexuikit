//
// Created by furture on 2018/10/19.
//

#ifndef WEEX_UIKIT_GESTURE_PANGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_PANGESTURERECOGNIZER_H
#include "DragGestureRecognizer.h"

namespace weexuikit {


    class PanGestureRecognizer : public DragGestureRecognizer {


    public:
        PanGestureRecognizer(GestureHandlerContext *gestureContext);


        virtual bool _isFlingGesture(VelocityEstimate *estimate) override {
            double minVelocity = mMinFlingVelocity;
            double minDistance = mMinFlingDistance;
            return estimate->pixelsPerSecond.distanceSquared() > minVelocity * minVelocity
                   && estimate->offset.distanceSquared() > minDistance * minDistance;
        }

        virtual Offset _getDeltaForDetails(const Offset &delta) override {
            return delta;
        }

        virtual double _getPrimaryValueFromOffset(const Offset &value) override {
            return 0;
        }

        virtual bool getHasSufficientPendingDragDeltaToAccept() override {
            return mPendingDragOffset.distance() > kPanSlop;
        }

    };
}


#endif //WEEX_UIKIT_GESTURE_PANGESTURERECOGNIZER_H
