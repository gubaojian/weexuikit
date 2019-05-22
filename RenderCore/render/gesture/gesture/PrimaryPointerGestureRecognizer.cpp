//
// Created by furture on 2018/10/11.
//

#include "PrimaryPointerGestureRecognizer.h"
#include "GestureConfig.h"
#include <math.h>

namespace weexuikit {

    PrimaryPointerGestureRecognizer::PrimaryPointerGestureRecognizer(
            GestureHandlerContext *gestureContext)
            : OneSequenceGestureRecognizer(gestureContext) {

    }


    void PrimaryPointerGestureRecognizer::addPointer(const PointerEvent &event) {
        startTrackingPointer(event.pointer);
        if (state == GestureRecognizerState::ready) {
            state = GestureRecognizerState::possible;
            mPrimaryPointer = event.pointer;
            mInitialEvent = event;
            if (mDeadline > 0) {
                mTimer = new Timer(mGestureHandlerContext->timerManager, mDeadline, this);
            }
        }
    }


    void PrimaryPointerGestureRecognizer::handleEvent(const PointerEvent &event) {
        assert(state != GestureRecognizerState::ready);
        if (state == GestureRecognizerState::possible && event.pointer == mPrimaryPointer) {
            // TODO(abarth): Maybe factor the slop handling out into a separate class?
            if (event.isMoveEvent() && _getDistance(event) > kTouchSlop) {
                resolve(GestureDisposition::rejected);
                stopTrackingPointer(mPrimaryPointer);
            } else {
                handlePrimaryPointer(event);
            }
        }
        stopTrackingIfPointerNoLongerDown(event);
    }

    void PrimaryPointerGestureRecognizer::didExceedDeadline() {
        assert(mDeadline > 0);
    }

    void PrimaryPointerGestureRecognizer::fireTimer() {
        didExceedDeadline();
    }

    void PrimaryPointerGestureRecognizer::rejectGesture(int pointer) {
        if (pointer == mPrimaryPointer && state == GestureRecognizerState::possible) {
            _stopTimer();
            state = GestureRecognizerState::defunct;
        }
    }

    void PrimaryPointerGestureRecognizer::didStopTrackingLastPointer(int pointer) {
        assert(state != GestureRecognizerState::ready);
        _stopTimer();
        state = GestureRecognizerState::ready;
    }

    void PrimaryPointerGestureRecognizer::dispose() {
        _stopTimer();
        OneSequenceGestureRecognizer::dispose();
    }


    double PrimaryPointerGestureRecognizer::_getDistance(PointerEvent event) {
        float dx = event.position.dx - mInitialEvent.position.dx;
        float dy = event.position.dy - mInitialEvent.position.dy;
        return sqrt(dx * dx + dy * dy);
    }


    void PrimaryPointerGestureRecognizer::_stopTimer() {
        if (mTimer != nullptr) {
            mTimer->cancel();
            delete mTimer;
            mTimer = nullptr;
        }
    }
}