//
// Created by furture on 2018/10/19.
//

#include "VerticalDragGestureRecognizer.h"

namespace weexuikit {

    VerticalDragGestureRecognizer::VerticalDragGestureRecognizer(
            GestureHandlerContext *gestureContext)
            : DragGestureRecognizer(gestureContext) {

    }


    bool VerticalDragGestureRecognizer::_isFlingGesture(VelocityEstimate *estimate) {
        double minVelocity = mMinFlingVelocity;
        double minDistance = mMinFlingDistance;
        return std::abs(estimate->pixelsPerSecond.dy) > minVelocity &&
               std::abs(estimate->offset.dy) > minDistance;
    }


    Offset VerticalDragGestureRecognizer::_getDeltaForDetails(const Offset &delta) {
        return Offset(0.0, delta.dy);
    }


    VerticalDragGestureRecognizer::~VerticalDragGestureRecognizer() {
        dispose();
    }

}