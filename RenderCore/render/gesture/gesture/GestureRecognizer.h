//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_GESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_GESTURERECOGNIZER_H
#include "GestureArenaMember.h"
#include "PointerEvent.h"
#include "GestureHandlerContext.h"


namespace weexuikit {

    class GestureRecognizer : public GestureArenaMember {


    public:
        GestureRecognizer(GestureHandlerContext *gestureContext) : mGestureHandlerContext(
                gestureContext) {

        };

    protected:
        GestureHandlerContext *mGestureHandlerContext;


    public:


        /// Registers a new pointer that might be relevant to this gesture
        /// detector.
        ///
        /// The owner of this gesture recognizer calls addPointer() with the
        /// PointerDownEvent of each pointer that should be considered for
        /// this gesture.
        ///
        /// It's the GestureRecognizer's responsibility to then add itself
        /// to the global pointer router (see [PointerRouter]) to receive
        /// subsequent events for this pointer, and to add the pointer to
        /// the global gesture arena manager (see [GestureArenaManager]) to track
        /// that pointer. the PointerEvent must should be pointer event
        virtual void addPointer(const PointerEvent &event) = 0;


        /// Releases any resources used by the object.
        ///
        /// This method is called by the owner of this gesture recognizer
        /// when the object is no longer needed (e.g. when a gesture
        /// recognizer is being unregistered from a [GestureDetector], the
        /// GestureDetector widget calls this method).
        void dispose() {}


    };
}

#endif //WEEX_UIKIT_GESTURE_GESTURERECOGNIZER_H
