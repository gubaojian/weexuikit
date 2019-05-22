//
// Created by furture on 2018/10/19.
//

#include "HorizontalDragGestureRecognizer.h"

namespace weexuikit {
    HorizontalDragGestureRecognizer::HorizontalDragGestureRecognizer(
            GestureHandlerContext *gestureContext)
            : DragGestureRecognizer(gestureContext) {

    }


    HorizontalDragGestureRecognizer::~HorizontalDragGestureRecognizer() {
        dispose();
    }
}