//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_PRIMARYPOINTERGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_PRIMARYPOINTERGESTURERECOGNIZER_H
#include "OneSequenceGestureRecognizer.h"


namespace weexuikit {
/// The possible states of a [PrimaryPointerGestureRecognizer].
///
/// The recognizer advances from [ready] to [possible] when starts tracking a
/// primary pointer. When the primary pointer is resolve (either accepted or
/// or rejected), the recognizers advances to [defunct]. Once the recognizer
/// has stopped tracking any remaining pointers, the recognizer returns to
/// [ready].
    enum GestureRecognizerState {
        /// The recognizer is ready to start recognizing a gesture.
                ready,

        /// The sequence of pointer events seen thus far is consistent with the
        /// gesture the recognizer is attempting to recognize but the gesture has not
        /// been accepted definitively.
                possible,

        /// Further pointer events cannot cause this recognizer to recognize the
        /// gesture until the recognizer returns to the [ready] state (typically when
        /// all the pointers the recognizer is tracking are removed from the screen).
                defunct,
    };

    class PrimaryPointerGestureRecognizer : public OneSequenceGestureRecognizer, public TimerTask {

    public:
        PrimaryPointerGestureRecognizer(GestureHandlerContext *gestureContext);


    public:
        // If non-null, the recognizer will call [didExceedDeadline] after this
        /// amount of time has elapsed since starting to track the primary pointer.
        int64_t mDeadline = -1;
        Timer *mTimer;
        /// The current state of the recognizer.
        ///
        /// See [GestureRecognizerState] for a description of the states.
        GestureRecognizerState state = GestureRecognizerState::ready;

        /// The ID of the primary pointer this recognizer is tracking.
        int mPrimaryPointer;

        /// The global location at which the primary pointer contacted the screen.
        PointerEvent mInitialEvent;


        void addPointer(const PointerEvent &event) override;

        void handleEvent(const PointerEvent &event) override;

        virtual void handlePrimaryPointer(const PointerEvent &event)=0;

        virtual void didExceedDeadline();

        virtual void fireTimer() override;

        virtual void rejectGesture(int pointer) override;

        virtual void didStopTrackingLastPointer(int pointer) override;

        virtual void dispose() override;

        double _getDistance(PointerEvent event);

        void _stopTimer();


    };
}


#endif //WEEX_UIKIT_GESTURE_PRIMARYPOINTERGESTURERECOGNIZER_H
